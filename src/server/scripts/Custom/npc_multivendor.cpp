/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "GameEventMgr.h"
#include "Player.h"
#include "WorldSession.h"

class Vendor
{
private:
    int m_GUID;
    GossipOptionIcon m_Icon;
    std::string m_Message;
public:
    Vendor() {}
    Vendor(int guid, GossipOptionIcon icon, std::string message)
    {
        m_GUID = guid;
        m_Icon = icon;
        m_Message = message;
    }
    
    Vendor(int guid, GossipOptionIcon icon, std::string message, VendorItemData* item_list)
    {
        m_GUID = guid;
        m_Icon = icon;
        m_Message = message;
        for(int i = 0; i < item_list->GetItemCount(); i++)
            items.AddItem(item_list->m_items[i]->item, 0, 0, item_list->m_items[i]->ExtendedCost);
    }

    VendorItemData items;

    int getGuid() { return m_GUID; }
    void setGuid(int guid) { m_GUID = guid; }
    GossipOptionIcon getIcon() { return m_Icon; }
    void setIcon(GossipOptionIcon icon) { m_Icon = icon; }
    std::string getMessage() { return m_Message; }
    void setMessage(std::string message) { m_Message = message; }
};

class ItemList
{
public:
    ItemList() { /* Called while looping through vendors to find ours */ }

    ItemList(Vendor* myVendor)
    {
        m_vendor = Vendor(myVendor->getGuid(), myVendor->getIcon(), myVendor->getMessage());
    }

    ItemList(Vendor* myVendor, VendorItemData* item_list)
    {
        m_vendor = Vendor(myVendor->getGuid(), myVendor->getIcon(), myVendor->getMessage());
        for(int i = 0; i < item_list->GetItemCount(); i++)
            m_vendor.items.AddItem(item_list->m_items[i]->item, 0, 0, item_list->m_items[i]->ExtendedCost);
    }

    void AddItem(uint32 item_id, uint32 extended_cost = 0) { m_vendor.items.AddItem(item_id, 0, 0, extended_cost); }
    void RemoveItem(uint32 item_id) { m_vendor.items.RemoveItem(item_id); }
    uint8 GetItemCount() { return m_vendor.items.GetItemCount(); }
    Vendor GetVendor() { return m_vendor; }
private:
    Vendor m_vendor;
};

class SmsgListInventory
{
private:
    uint32 m_opcode;
    uint64 m_vendorGuid;
    uint8  m_itemCount;
    uint8  m_status;
    WorldSession* m_session;
    VendorItemData m_vendorItemData;
    VendorItemData m_completeVendorItemData;
    std::vector<ItemList> m_vendors;

    struct packetItem
    {
        uint32 m_slot;
        uint32 m_item;
        uint32 m_displayId;
        int32  m_inStock;
        uint32 m_price;
        uint32 m_durability;
        uint32 m_buyCount;
        uint32 m_extendedCost;
    };

    bool SkipItem(const ItemTemplate* item_template, Player* player, int slot)
    {
        /* Calculate relative slot position */
        if(m_vendors[0].GetItemCount() > 0)
        {
            if( (slot + 1) > (m_vendors[0].GetItemCount()))
            {
                int totalItemsChecked = 0;
                /* For each vendor */
                for(int i = 0; i < m_vendors.size(); i++)
                {
                    if((totalItemsChecked + m_vendors[i].GetItemCount()) < (slot + 1))
                    {
                        totalItemsChecked += m_vendors[i].GetItemCount();
                        continue;
                    }

                    slot -= totalItemsChecked;
                    break;
                }
            }
        }

        /* Account for duplicate items across vendors */
        if(VendorItem* vendor_item = m_vendorItemData.GetItem(slot))
        {
            if(vendor_item->item != item_template->ItemId)
                return true;
        }
        else
            return true; // the item doesn't even exist why would we send it

        /* GM's are exceptions */
        if(player->isGameMaster())
            return false;

        /* If the item is class specific and Bind on Pickup */
        if (!(item_template->AllowableClass & player->getClassMask()) && item_template->Bonding == BIND_WHEN_PICKED_UP)
            return true;
        
        /* If the item is faction specific and player is wrong faction */
        if ((item_template->Flags2 & ITEM_FLAGS_EXTRA_HORDE_ONLY && player->GetTeam() == ALLIANCE) || 
            (item_template->Flags2 == ITEM_FLAGS_EXTRA_ALLIANCE_ONLY && player->GetTeam() == HORDE))
            return true;

        /* Anything else */
        return false;
    }

public: SmsgListInventory(uint64 vendor_guid, WorldSession* player_session, VendorItemData* vendor_item_data, std::vector<ItemList> vendors)
        {
            m_opcode = SMSG_LIST_INVENTORY;
            m_vendorGuid = vendor_guid;
            m_itemCount = 0;
            for(int i = 0; i < vendors.size(); i++)
                m_itemCount += vendors[i].GetItemCount();

            m_status = 0;
            m_session = player_session;
            for(int i = 0; i < vendors.size(); i++)
                for(int i2 = 0; i2 < vendors[i].GetItemCount(); i2++)
                    m_completeVendorItemData.AddItem(vendors[i].GetVendor().items.m_items[i2]->item, 0, 0, vendors[i].GetVendor().items.m_items[i2]->ExtendedCost);

            for(int i = 0; i < vendor_item_data->GetItemCount(); i++)
                m_vendorItemData.AddItem(vendor_item_data->m_items[i]->item, 0, 0, vendor_item_data->m_items[i]->ExtendedCost);

            for(int i = 0; i < vendors.size(); i++)
                m_vendors.push_back(vendors[i]);
        }

        void Send(Creature* originalVendor, Player* player)
        {
            uint8 item_count = 0;
            std::vector<packetItem> items_to_send;
            ItemList item_list_to_send;
            bool haveUpdatedVendor = false;
            if(const VendorItemData* vendor_item_data = originalVendor->GetVendorItems())
                if(vendor_item_data->GetItemCount() > 0)
                    haveUpdatedVendor = true;

            for(int slot = 0; slot < m_itemCount; slot++)
                if(VendorItem const* item = m_completeVendorItemData.GetItem(slot))
                    if(ItemTemplate const* item_template = sObjectMgr->GetItemTemplate(item->item))
                    {
                        if(!haveUpdatedVendor)
                            sObjectMgr->AddVendorItem(originalVendor->GetEntry(), item->item, 0, 0, item->ExtendedCost, false);

                        if(SkipItem(item_template, player, slot))
                            continue;

                        item_list_to_send.AddItem(item->item, item->ExtendedCost);

                        item_count++;

                        int32 price = item->IsGoldRequired(item_template) ? uint32(item_template->BuyPrice) : 0;

                        packetItem packet;
                        packet.m_slot = slot + 1;
                        packet.m_item = item->item;
                        packet.m_displayId = item_template->DisplayInfoID;
                        packet.m_inStock = 0xFFFFFFFF;
                        packet.m_price = price;
                        packet.m_durability = item_template->MaxDurability;
                        packet.m_buyCount = item_template->BuyCount;
                        packet.m_extendedCost = item->ExtendedCost;
                        items_to_send.push_back(packet);
                    }

            WorldPacket packet(m_opcode, 8 + 1 + (m_itemCount > 0 ? m_itemCount * 8 * 4 : 1));
            packet << m_vendorGuid;
            packet << item_count;
            for(int i = 0; i < items_to_send.size(); i++)
            {
                packet << items_to_send[i].m_slot;
                packet << items_to_send[i].m_item;
                packet << items_to_send[i].m_displayId;
                packet << items_to_send[i].m_inStock;
                packet << items_to_send[i].m_price;
                packet << items_to_send[i].m_durability;
                packet << items_to_send[i].m_buyCount;
                packet << items_to_send[i].m_extendedCost;
            }
            m_session->SendPacket(&packet);
        }
};

class npc_multivendor : public CreatureScript
{
public:
    npc_multivendor() : CreatureScript("npc_multivendor"){ }

    std::vector<ItemList> GetVendorList()
    {
        std::vector<ItemList> itemlists;
        
        /* Nur Daten nach diesem Commentblock editieren!
         * Nicht anderes verändern!
         *
         * Example vendor:

        Vendor vendor_1(700000, GOSSIP_ICON_VENDOR, "Look at all the weapons I have");
        ItemList items_1(&vendor_1);
        items_1.AddItem(18582, 2); // Azzinoth
        items_1.AddItem(13262, 2); // Ashbringer
        itemlists.push_back(items_1);
        
        * Die erste Zeile erstellt ein "Vendor" Objekt mit:
        *     GUID 700000 (Muss verschieden zu allen anderen Vendoren sein)
        *     Zeigt das Händler Icon an
        *     Zeigt den Text "Look at all the weapons I have" an
        * 
        *Die zweite Zeile erstell eine Instanz vom ItemList Objekt mit Namen items_1
        *    
        * 
        * Die dritte und vierte Zeile sind Beispiele wie man Items zum Vendor hinzufügt(named items_1).
        *     Man kann ItemExtendedCost als zweiten Parameter hinzufügen
        *     Das Script unterstützt keine Zeitlimitierten oder respawnenden Items
        * 
        * Die letzte Zeile ist die wichtigste. Diese Zeile fügt deinen Vendor zur Liste der Vendoren hinzu.
        * 
        *
        * Ende der Erklärung
        * 
        */

        Vendor vendor_1(700000, GOSSIP_ICON_VENDOR, "Tier 7 Set-Teile");
        ItemList items_1(&vendor_1);
        items_1.AddItem(40415, 2); // 
        items_1.AddItem(40416, 2); // 
		items_1.AddItem(40417, 2); // 
		items_1.AddItem(40418, 2); // 
		items_1.AddItem(40419, 2); // 
		items_1.AddItem(40420, 2); // 
		items_1.AddItem(40421, 2); // 
		items_1.AddItem(40422, 2); // 
		items_1.AddItem(40423, 2); // 
		items_1.AddItem(40424, 2); // 
		items_1.AddItem(40445, 2); // 
		items_1.AddItem(40447, 2); // 
		items_1.AddItem(40448, 2); // 
		items_1.AddItem(40449, 2); // 
		items_1.AddItem(40450, 2); // 
		items_1.AddItem(40454, 2); // 
		items_1.AddItem(40456, 2); // 
		items_1.AddItem(40457, 2); // 
		items_1.AddItem(40458, 2); // 
		items_1.AddItem(40459, 2); // 
		items_1.AddItem(40460, 2); // 
		items_1.AddItem(40461, 2); // 
		items_1.AddItem(40462, 2); // 
		items_1.AddItem(40463, 2); // 
		items_1.AddItem(40465, 2); // 
		items_1.AddItem(40466, 2); // 
		items_1.AddItem(40467, 2); // 
		items_1.AddItem(40468, 2); // 
		items_1.AddItem(40469, 2); // 
		items_1.AddItem(40470, 2); // 
		items_1.AddItem(40471, 2); // 
		items_1.AddItem(40472, 2); // 
		items_1.AddItem(40473, 2); // 
		items_1.AddItem(40493, 2); // 
		items_1.AddItem(40494, 2); // 
		items_1.AddItem(40495, 2); // 
		items_1.AddItem(40496, 2); // 
		items_1.AddItem(40499, 2); // 
		items_1.AddItem(40500, 2); // 
		items_1.AddItem(40502, 2); // 
		items_1.AddItem(40503, 2); // 
		items_1.AddItem(40504, 2); // 
		items_1.AddItem(40505, 2); // 
		items_1.AddItem(40506, 2); // 
		items_1.AddItem(40507, 2); // 
		items_1.AddItem(40508, 2); // 
		items_1.AddItem(40509, 2); // 
		items_1.AddItem(40510, 2); // 
		items_1.AddItem(40512, 2); // 
		items_1.AddItem(40513, 2); // 
		items_1.AddItem(40514, 2); // 
		items_1.AddItem(40515, 2); // 
		items_1.AddItem(40516, 2); // 
		items_1.AddItem(40517, 2); // 
		items_1.AddItem(40518, 2); // 
		items_1.AddItem(40520, 2); // 
		items_1.AddItem(40521, 2); // 
		items_1.AddItem(40522, 2); // 
		items_1.AddItem(40523, 2); // 
		items_1.AddItem(40524, 2); // 
		items_1.AddItem(40525, 2); // 
		items_1.AddItem(40527, 2); // 
		items_1.AddItem(40528, 2); // 
		items_1.AddItem(40529, 2); // 
		items_1.AddItem(40530, 2); // 
		items_1.AddItem(40544, 2); // 
		items_1.AddItem(40545, 2); // 
		items_1.AddItem(40546, 2); // 
		items_1.AddItem(40547, 2); // 
		items_1.AddItem(40548, 2); // 
		items_1.AddItem(40550, 2); // 
		items_1.AddItem(40552, 2); // 
		items_1.AddItem(40554, 2); // 
		items_1.AddItem(40556, 2); // 
		items_1.AddItem(40557, 2); // 
		items_1.AddItem(40559, 2); // 
		items_1.AddItem(40563, 2); // 
		items_1.AddItem(40565, 2); // 
		items_1.AddItem(40567, 2); // 
		items_1.AddItem(40568, 2); // 
		items_1.AddItem(40569, 2); // 
		items_1.AddItem(40570, 2); // 
		items_1.AddItem(40571, 2); // 
		items_1.AddItem(40572, 2); // 
		items_1.AddItem(40573, 2); // 
		items_1.AddItem(40574, 2); // 
		items_1.AddItem(40575, 2); // 
		items_1.AddItem(40576, 2); // 
		items_1.AddItem(40577, 2); // 
		items_1.AddItem(40578, 2); // 
		items_1.AddItem(40579, 2); // 
		items_1.AddItem(40580, 2); // 
		items_1.AddItem(40581, 2); // 
		items_1.AddItem(40583, 2); // 
		items_1.AddItem(40584, 2); // 
        itemlists.push_back(items_1);

        Vendor vendor_2(700001, GOSSIP_ICON_VENDOR, "Tier 7 NonSets");
        ItemList items_2(&vendor_2);
        items_2.AddItem(39421, 2); // 
        items_2.AddItem(39425, 2); // 
		items_2.AddItem(39701, 2); // 
		items_2.AddItem(39702, 2); // 
		items_2.AddItem(39706, 2); // 
		items_2.AddItem(39717, 2); // 
		items_2.AddItem(39721, 2); // 
		items_2.AddItem(39722, 2); // 
		items_2.AddItem(39728, 2); // 
		items_2.AddItem(39729, 2); // 
		items_2.AddItem(39731, 2); // 
		items_2.AddItem(39734, 2); // 
		items_2.AddItem(39735, 2); // 
		items_2.AddItem(39757, 2); // 
		items_2.AddItem(39759, 2); // 
		items_2.AddItem(39762, 2); // 
		items_2.AddItem(39764, 2); // 
		items_2.AddItem(39765, 2); // 
		items_2.AddItem(40064, 2); // 
		items_2.AddItem(40065, 2); // 
		items_2.AddItem(40069, 2); // 
		items_2.AddItem(40071, 2); // 
		items_2.AddItem(40074, 2); // 
		items_2.AddItem(40075, 2); // 
		items_2.AddItem(40080, 2); // 
		items_2.AddItem(40107, 2); // 
		items_2.AddItem(40108, 2); // 
		items_2.AddItem(40184, 2); // 
		items_2.AddItem(40186, 2); // 
		items_2.AddItem(40187, 2); // 
		items_2.AddItem(40191, 2); // 
		items_2.AddItem(40198, 2); // 
		items_2.AddItem(40200, 2); // 
		items_2.AddItem(40205, 2); // 
		items_2.AddItem(40206, 2); // 
		items_2.AddItem(40207, 2); // 
		items_2.AddItem(40209, 2); // 
		items_2.AddItem(40236, 2); // 
		items_2.AddItem(40237, 2); // 
		items_2.AddItem(40241, 2); // 
		items_2.AddItem(40243, 2); // 
		items_2.AddItem(40246, 2); // 
		items_2.AddItem(40250, 2); // 
		items_2.AddItem(40251, 2); // 
		items_2.AddItem(40252, 2); // 
		items_2.AddItem(40253, 2); // 
		items_2.AddItem(40254, 2); // 
		items_2.AddItem(40255, 2); // 
		items_2.AddItem(40256, 2); // 
		items_2.AddItem(40257, 2); // 
		items_2.AddItem(40258, 2); // 
		items_2.AddItem(40259, 2); // 
		items_2.AddItem(40260, 2); // 
		items_2.AddItem(40263, 2); // 
		items_2.AddItem(40267, 2); // 
		items_2.AddItem(40268, 2); // 
		items_2.AddItem(40269, 2); // 
		items_2.AddItem(40270, 2); // 
		items_2.AddItem(40271, 2); // 
		items_2.AddItem(40272, 2); // 
		items_2.AddItem(40274, 2); // 
		items_2.AddItem(40275, 2); // 
		items_2.AddItem(40278, 2); // 
		items_2.AddItem(40282, 2); // 
		items_2.AddItem(40297, 2); // 
		items_2.AddItem(40301, 2); // 
		items_2.AddItem(40306, 2); // 
		items_2.AddItem(40317, 2); // 
		items_2.AddItem(40320, 2); // 
		items_2.AddItem(40321, 2); // 
		items_2.AddItem(40322, 2); // 
		items_2.AddItem(40323, 2); // 
		items_2.AddItem(40324, 2); // 
		items_2.AddItem(40325, 2); // 
		items_2.AddItem(40326, 2); // 
		items_2.AddItem(40327, 2); // 
		items_2.AddItem(40330, 2); // 
		items_2.AddItem(40332, 2); // 
		items_2.AddItem(40337, 2); // 
		items_2.AddItem(40338, 2); // 
		items_2.AddItem(40341, 2); // 
		items_2.AddItem(40342, 2); // 
		items_2.AddItem(40367, 2); // 
		items_2.AddItem(40369, 2); // 
		items_2.AddItem(40370, 2); // 
		items_2.AddItem(40371, 2); // 
		items_2.AddItem(40372, 2); // 
		items_2.AddItem(40373, 2); // 
		items_2.AddItem(40374, 2); // 
		items_2.AddItem(40375, 2); // 
		items_2.AddItem(40378, 2); // 
		items_2.AddItem(40382, 2); // 
		items_2.AddItem(40409, 2); // 
		items_2.AddItem(40410, 2); // 
		items_2.AddItem(40412, 2); // 
        itemlists.push_back(items_2);

		Vendor vendor_3(700002, GOSSIP_ICON_VENDOR, "Tier 7 Waffen");
        ItemList items_3(&vendor_3);
        items_3.AddItem(39712, 2); // 
        items_3.AddItem(39714, 2); // 
		items_3.AddItem(39730, 2); // 
		items_3.AddItem(39758, 2); // 
		items_3.AddItem(39763, 2); // 
		items_3.AddItem(39766, 2); // 
		items_3.AddItem(40192, 2); // 
		items_3.AddItem(40208, 2); // 
		items_3.AddItem(40233, 2); // 
		items_3.AddItem(40239, 2); // 
		items_3.AddItem(40244, 2); // 
		items_3.AddItem(40245, 2); // 
		items_3.AddItem(40264, 2); // 
		items_3.AddItem(40273, 2); // 
		items_3.AddItem(40280, 2); // 
		items_3.AddItem(40281, 2); // 
		items_3.AddItem(40284, 2); // 
		items_3.AddItem(40300, 2); // 
		items_3.AddItem(40335, 2); // 
		items_3.AddItem(40336, 2); // 
		items_3.AddItem(40343, 2); // 
		items_3.AddItem(40345, 2); // 
		items_3.AddItem(40346, 2); // 
		items_3.AddItem(40348, 2); // 
		items_3.AddItem(40350, 2); // 
		items_3.AddItem(40368, 2); // 
		items_3.AddItem(40369, 2); // 
		items_3.AddItem(40383, 2); // 
		items_3.AddItem(40384, 2); // 
		items_3.AddItem(40385, 2); // 
		items_3.AddItem(40386, 2); // 
		items_3.AddItem(40388, 2); // 
		items_3.AddItem(40395, 2); // 
		items_3.AddItem(40400, 2); // 
		items_3.AddItem(40401, 2); // 
		items_3.AddItem(40402, 2); // 
        itemlists.push_back(items_3);

        /* Verändere nicht was hier drunter steht
         * Dies ist das Ende des editierbaren Abschnitts
         * Verändere nur Dinge ÜBER diesem Commentblock, solange du nicht weißt was du tust!
         *
         * Peace out
         * Evilfairy~ */

        return itemlists;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        std::vector<ItemList> vendors = GetVendorList();

        /* DO NOT EDIT ANYTHING BELOW THIS LINE */
        for(int i = 0; i < vendors.size(); i++) // icon message sender guid
            player->ADD_GOSSIP_ITEM(vendors[i].GetVendor().getIcon(), vendors[i].GetVendor().getMessage(), GOSSIP_SENDER_MAIN, vendors[i].GetVendor().getGuid());

        player->TalkedToCreature(creature->GetEntry(), creature->GetGUID());
        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        player->CLOSE_GOSSIP_MENU();
        
        SendInventoryCustom(player, creature, action);
        
        return true;
    }

    void SendInventoryCustom(Player* player, Creature* vendor, int guid)
    {
        /* Remove Feign Death effects */
        if (player->HasUnitState(UNIT_STATE_DIED))
            player->RemoveAurasByType(SPELL_AURA_FEIGN_DEATH);

        /* Stop NPC moving */
        if (vendor->isMoving())
            vendor->StopMoving();

        std::vector<ItemList> vendors = GetVendorList();
        ItemList myVendor;
        for(int i = 0; i < vendors.size(); i++)
        {
            if(vendors[i].GetVendor().getGuid() == guid)
            {
                myVendor = ItemList(&vendors[i].GetVendor(), &vendors[i].GetVendor().items);
                break;
            }
        }

        SmsgListInventory inventory_packet(vendor->GetGUID(), player->GetSession(), &myVendor.GetVendor().items, vendors);
        inventory_packet.Send(vendor, player);
    }
};

class npc_multivendor_season : public CreatureScript
{
public:
    npc_multivendor_season() : CreatureScript("npc_multivendor_season"){ }

    std::vector<ItemList> GetVendorList()
    {
        std::vector<ItemList> itemlists;
        
        /* Nur Daten nach diesem Commentblock editieren!
         * Nicht anderes verändern!
         *
         * Example vendor:

        Vendor vendor_1(700000, GOSSIP_ICON_VENDOR, "Look at all the weapons I have");
        ItemList items_1(&vendor_1);
        items_1.AddItem(18582, 2); // Azzinoth
        items_1.AddItem(13262, 2); // Ashbringer
        itemlists.push_back(items_1);
        
        * Die erste Zeile erstellt ein "Vendor" Objekt mit:
        *     GUID 700000 (Muss verschieden zu allen anderen Vendoren sein)
        *     Zeigt das Händler Icon an
        *     Zeigt den Text "Look at all the weapons I have" an
        * 
        *Die zweite Zeile erstell eine Instanz vom ItemList Objekt mit Namen items_1
        *    
        * 
        * Die dritte und vierte Zeile sind Beispiele wie man Items zum Vendor hinzufügt(named items_1).
        *     Man kann ItemExtendedCost als zweiten Parameter hinzufügen
        *     Das Script unterstützt keine Zeitlimitierten oder respawnenden Items
        * 
        * Die letzte Zeile ist die wichtigste. Diese Zeile fügt deinen Vendor zur Liste der Vendoren hinzu.
        * 
        *
        * Ende der Erklärung
        * 
        */

        Vendor vendor_4(700003, GOSSIP_ICON_VENDOR, "Season 5 Set-Teile");
        ItemList items_4(&vendor_4);
        items_4.AddItem(37864, 0); // 
		items_4.AddItem(37865, 0); // 
		items_4.AddItem(40784, 0); // 
		items_4.AddItem(40785, 0); // 
		items_4.AddItem(40786, 0); // 
		items_4.AddItem(40804, 0); // 
		items_4.AddItem(40805, 0); // 
		items_4.AddItem(40806, 0); // 
		items_4.AddItem(40823, 0); // 
		items_4.AddItem(40824, 0); // 
		items_4.AddItem(40825, 0); // 
		items_4.AddItem(40844, 0); // 
		items_4.AddItem(40845, 0); // 
		items_4.AddItem(40846, 0); // 
		items_4.AddItem(40862, 0); // 
		items_4.AddItem(40863, 0); // 
		items_4.AddItem(40864, 0); // 
		items_4.AddItem(40905, 0); // 
		items_4.AddItem(40926, 0); // 
		items_4.AddItem(40932, 0); // 
		items_4.AddItem(40938, 0); // 
		items_4.AddItem(40962, 0); // 
		items_4.AddItem(40990, 0); // 
		items_4.AddItem(40991, 0); // 
		items_4.AddItem(41000, 0); // 
		items_4.AddItem(41006, 0); // 
		items_4.AddItem(41012, 0); // 
		items_4.AddItem(41018, 0); // 
		items_4.AddItem(41026, 0); // 
		items_4.AddItem(41032, 0); //
		items_4.AddItem(41037, 0); //
		items_4.AddItem(41043, 0); //
		items_4.AddItem(41080, 0); //
		items_4.AddItem(41086, 0); //
		items_4.AddItem(41136, 0); //
		items_4.AddItem(41142, 0); //
		items_4.AddItem(41150, 0); //
		items_4.AddItem(41156, 0); //
		items_4.AddItem(41198, 0); //
		items_4.AddItem(41204, 0); //
		items_4.AddItem(41210, 0); //
		items_4.AddItem(41216, 0); //
		items_4.AddItem(41274, 0); //
		items_4.AddItem(41280, 0); //
		items_4.AddItem(41286, 0); //
		items_4.AddItem(41292, 0); //
		items_4.AddItem(41297, 0); //
		items_4.AddItem(41303, 0); //
		items_4.AddItem(41309, 0); //
		items_4.AddItem(41315, 0); //
		items_4.AddItem(41320, 0); //
		items_4.AddItem(41326, 0); //
		items_4.AddItem(41649, 0); //
		items_4.AddItem(41654, 0); //
		items_4.AddItem(41660, 0); //
		items_4.AddItem(41666, 0); //
		items_4.AddItem(41671, 0); //
		items_4.AddItem(41677, 0); //
		items_4.AddItem(41682, 0); //
		items_4.AddItem(41714, 0); //
		items_4.AddItem(41766, 0); //
		items_4.AddItem(41772, 0); //
		items_4.AddItem(41853, 0); //
		items_4.AddItem(41858, 0); //
		items_4.AddItem(41863, 0); //
		items_4.AddItem(41868, 0); //
		items_4.AddItem(41873, 0); //
		items_4.AddItem(41914, 0); //
		items_4.AddItem(41920, 0); //
		items_4.AddItem(41926, 0); //
		items_4.AddItem(41933, 0); //
		items_4.AddItem(41939, 0); //
		items_4.AddItem(41945, 0); //
		items_4.AddItem(41951, 0); //
		items_4.AddItem(41958, 0); //
		items_4.AddItem(41964, 0); //
		items_4.AddItem(41970, 0); //
		items_4.AddItem(41992, 0); //
		items_4.AddItem(41997, 0); //
		items_4.AddItem(42004, 0); //
		items_4.AddItem(42010, 0); //
		items_4.AddItem(42016, 0); //
        itemlists.push_back(items_4);

        Vendor vendor_5(700004, GOSSIP_ICON_VENDOR, "Season 5 NonSets");
        ItemList items_5(&vendor_5);
        items_5.AddItem(40879, 0); // 
		items_5.AddItem(40880, 0); // 
		items_5.AddItem(40888, 0); // 
		items_5.AddItem(40974, 0); // 
		items_5.AddItem(40975, 0); // 
		items_5.AddItem(40982, 0); // 
		items_5.AddItem(41048, 0); // 
		items_5.AddItem(41054, 0); // 
		items_5.AddItem(41059, 0); // 
		items_5.AddItem(41064, 0); // 
		items_5.AddItem(41069, 0); // 
		items_5.AddItem(41074, 0); // 
		items_5.AddItem(41224, 0); // 
		items_5.AddItem(41229, 0); // 
		items_5.AddItem(41234, 0); // 
		items_5.AddItem(41616, 0); // 
		items_5.AddItem(41624, 0); // 
		items_5.AddItem(41629, 0); // 
		items_5.AddItem(41634, 0); // 
		items_5.AddItem(41639, 0); // 
		items_5.AddItem(41831, 0); // 
		items_5.AddItem(41835, 0); // 
		items_5.AddItem(41839, 0); // 
		items_5.AddItem(41880, 0); // 
		items_5.AddItem(41884, 0); // 
		items_5.AddItem(41892, 0); // 
		items_5.AddItem(41897, 0); // 
		items_5.AddItem(41902, 0); // 
		items_5.AddItem(41908, 0); // 
		items_5.AddItem(42027, 0); // 
		items_5.AddItem(42028, 0); //
		items_5.AddItem(42029, 0); //
		items_5.AddItem(42030, 0); //
		items_5.AddItem(42031, 0); //
		items_5.AddItem(42032, 0); //
		items_5.AddItem(42033, 0); //
		items_5.AddItem(42062, 0); //
		items_5.AddItem(42063, 0); //
		items_5.AddItem(42064, 0); //
		items_5.AddItem(42065, 0); //
		items_5.AddItem(42066, 0); //
		items_5.AddItem(42067, 0); //
		items_5.AddItem(42068, 0); //
		items_5.AddItem(42114, 0); //
		items_5.AddItem(42115, 0); //
		items_5.AddItem(42208, 0); //
		items_5.AddItem(42227, 0); //
		items_5.AddItem(42232, 0); //
		items_5.AddItem(42237, 0); //
		items_5.AddItem(42242, 0); //
		items_5.AddItem(42248, 0); //
		items_5.AddItem(42255, 0); //
		items_5.AddItem(42260, 0); //
		items_5.AddItem(42265, 0); //
		items_5.AddItem(42270, 0); //
		items_5.AddItem(42275, 0); //
		items_5.AddItem(42280, 0); //
		items_5.AddItem(42285, 0); //
		items_5.AddItem(42290, 0); //
		items_5.AddItem(42317, 0); //
		items_5.AddItem(42322, 0); //
		items_5.AddItem(42327, 0); //
		items_5.AddItem(42332, 0); //
		items_5.AddItem(42346, 0); //
		items_5.AddItem(42352, 0); //
		items_5.AddItem(42362, 0); //
		items_5.AddItem(42384, 0); //
		items_5.AddItem(42390, 0); //
		items_5.AddItem(42450, 0); //
		items_5.AddItem(42485, 0); //
		items_5.AddItem(42490, 0); //
		items_5.AddItem(42495, 0); //
		items_5.AddItem(42502, 0); //
		items_5.AddItem(42513, 0); //
		items_5.AddItem(42519, 0); //
		items_5.AddItem(42525, 0); //
		items_5.AddItem(42531, 0); //
		items_5.AddItem(42537, 0); //
		items_5.AddItem(42559, 0); //
		items_5.AddItem(42564, 0); //
		items_5.AddItem(42570, 0); //
		items_5.AddItem(42578, 0); //
		items_5.AddItem(42583, 0); //
		items_5.AddItem(42588, 0); //
		items_5.AddItem(42597, 0); //
		items_5.AddItem(42602, 0); //
		items_5.AddItem(42607, 0); //
		items_5.AddItem(42614, 0); //
		items_5.AddItem(42620, 0); //
		items_5.AddItem(42852, 0); //
		items_5.AddItem(44419, 0); //
		items_5.AddItem(44420, 0); //
        itemlists.push_back(items_5);

		Vendor vendor_6(700005, GOSSIP_ICON_VENDOR, "Season 6 Set-Teile");
        ItemList items_6(&vendor_6);
		items_6.AddItem(4(40787, 0); //
        items_6.AddItem(4(40788, 0); //
        items_6.AddItem(4(40789, 0); //
        items_6.AddItem(4(40807, 0); //
        items_6.AddItem(4(40808, 0); //
        items_6.AddItem(4(40809, 0); //
        items_6.AddItem(4(40826, 0); //
        items_6.AddItem(4(40827, 0); //
        items_6.AddItem(4(40828, 0); //
        items_6.AddItem(4(40847, 0); //
        items_6.AddItem(4(40848, 0); //
        items_6.AddItem(4(40849, 0); //
        items_6.AddItem(4(40866, 0); //
        items_6.AddItem(4(40868, 0); //
        items_6.AddItem(4(40869, 0); //
        items_6.AddItem(4(40907, 0); //
        items_6.AddItem(4(40927, 0); //
        items_6.AddItem(4(40933, 0); //
        items_6.AddItem(4(40939, 0); //
        items_6.AddItem(4(40963, 0); //
        items_6.AddItem(4(40992, 0); //
        items_6.AddItem(4(40993, 0); //
        items_6.AddItem(4(41001, 0); //
        items_6.AddItem(4(41007, 0); //
        items_6.AddItem(4(41013, 0); //
        items_6.AddItem(4(41019, 0); //
        items_6.AddItem(4(41027, 0); //
        items_6.AddItem(4(41033, 0); //
        items_6.AddItem(4(41038, 0); //
        items_6.AddItem(4(41044, 0); //
        items_6.AddItem(4(41081, 0); //
        items_6.AddItem(4(41087, 0); //
        items_6.AddItem(4(41137, 0); //
        items_6.AddItem(4(41143, 0); //
        items_6.AddItem(4(41151, 0); //
        items_6.AddItem(4(41157, 0); //
        items_6.AddItem(4(41199, 0); //
        items_6.AddItem(4(41205, 0); //
        items_6.AddItem(4(41211, 0); // 
        items_6.AddItem(4(41217, 0); //
        items_6.AddItem(4(41275, 0); //
        items_6.AddItem(4(41281, 0); //
        items_6.AddItem(4(41287, 0); //
        items_6.AddItem(4(41293, 0); //
        items_6.AddItem(4(41298, 0); //
        items_6.AddItem(4(41304, 0); //
        items_6.AddItem(4(41310, 0); //
        items_6.AddItem(4(41316, 0); //
        items_6.AddItem(4(41321, 0); //
        items_6.AddItem(4(41327, 0); //
        items_6.AddItem(4(41650, 0); //
        items_6.AddItem(4(41655, 0); //
        items_6.AddItem(4(41661, 0); //
        items_6.AddItem(4(41667, 0); //
        items_6.AddItem(4(41672, 0); //
        items_6.AddItem(4(41678, 0); //
        items_6.AddItem(4(41683, 0); //
        items_6.AddItem(4(41715, 0); //
        items_6.AddItem(4(41767, 0); //
        items_6.AddItem(4(41773, 0); //
        items_6.AddItem(4(41854, 0); //
        items_6.AddItem(4(41859, 0); //
        items_6.AddItem(4(41864, 0); //
        items_6.AddItem(4(41869, 0); //
        items_6.AddItem(4(41874, 0); //
        items_6.AddItem(4(41915, 0); //
        items_6.AddItem(4(41921, 0); //
        items_6.AddItem(4(41927, 0); //
        items_6.AddItem(4(41934, 0); //
        items_6.AddItem(4(41940, 0); //
        items_6.AddItem(4(41946, 0); //
        items_6.AddItem(4(41953, 0); //
        items_6.AddItem(4(41959, 0); //
        items_6.AddItem(4(41965, 0); //
        items_6.AddItem(4(41971, 0); //
        items_6.AddItem(4(41993, 0); //
        items_6.AddItem(4(41998, 0); //
        items_6.AddItem(4(42005, 0); //
        items_6.AddItem(4(42011, 0); //
        items_6.AddItem(4(42017, 0); //
        items_6.AddItem(4(42122, 0); //
        items_6.AddItem(4(42123, 0); //
         itemlists.push_back(items_6);

		Vendor vendor_7(700006, GOSSIP_ICON_VENDOR, "Season 6 NonSets");
        ItemList items_7(&vendor_7);
        items_7.AddItem(40881, 0); //
        items_7.AddItem(40882, 0); //
        items_7.AddItem(40889, 0); //
        items_7.AddItem(40976, 0); //
        items_7.AddItem(40977, 0); //
        items_7.AddItem(40983, 0); //
        items_7.AddItem(41051, 0); //
        items_7.AddItem(41055, 0); //
        items_7.AddItem(41060, 0); //
        items_7.AddItem(41065, 0); //
        items_7.AddItem(41070, 0); //
        items_7.AddItem(41075, 0); //
        items_7.AddItem(41225, 0); //
        items_7.AddItem(41230, 0); //
        items_7.AddItem(41235, 0); //
        items_7.AddItem(41617, 0); //
        items_7.AddItem(41621, 0); //
        items_7.AddItem(41625, 0); // 
        items_7.AddItem(41630, 0); // 
        items_7.AddItem(41635, 0); // 
        items_7.AddItem(41640, 0); //
        items_7.AddItem(41832, 0); //
        items_7.AddItem(41836, 0); //
        items_7.AddItem(41840, 0); //
        items_7.AddItem(41881, 0); //
        items_7.AddItem(41885, 0); //
        items_7.AddItem(41893, 0); //
        items_7.AddItem(41898, 0); //
        items_7.AddItem(41903, 0); //
        items_7.AddItem(41909, 0); //
        items_7.AddItem(42034, 0); //
        items_7.AddItem(42035, 0); //
        items_7.AddItem(42036, 0); //
        items_7.AddItem(42037, 0); //
        items_7.AddItem(42038, 0); //
        items_7.AddItem(42039, 0); //
        items_7.AddItem(42040, 0); //
        items_7.AddItem(42069, 0); //
        items_7.AddItem(42070, 0); //
        items_7.AddItem(42071, 0); //
        items_7.AddItem(42072, 0); //
        items_7.AddItem(42073, 0); //
        items_7.AddItem(42074, 0); //
        items_7.AddItem(42075, 0); //
        items_7.AddItem(42116, 0); //
        items_7.AddItem(42117, 0); //
        items_7.AddItem(42209, 0); //
        items_7.AddItem(42228, 0); //
        items_7.AddItem(42233, 0); //
        items_7.AddItem(42243, 0); //
        items_7.AddItem(42249, 0); //
        items_7.AddItem(42256, 0); //
        items_7.AddItem(42261, 0); //
        items_7.AddItem(42266, 0); //
        items_7.AddItem(42271, 0); //
        items_7.AddItem(42276, 0); //
        items_7.AddItem(42281, 0); //
        items_7.AddItem(42286, 0); //
        items_7.AddItem(42291, 0); //
        items_7.AddItem(42318, 0); //
        items_7.AddItem(42323, 0); //
        items_7.AddItem(42328, 0); //
        items_7.AddItem(42333, 0); //
        items_7.AddItem(42347, 0); //
        items_7.AddItem(42353, 0); //
        items_7.AddItem(42364, 0); //
        items_7.AddItem(42385, 0); //
        items_7.AddItem(42391, 0); //
        items_7.AddItem(42451, 0); //
        items_7.AddItem(42486, 0); //
        items_7.AddItem(42491, 0); //
        items_7.AddItem(42496, 0); //
        items_7.AddItem(42503, 0); //
        items_7.AddItem(42514, 0); //
        items_7.AddItem(42520, 0); //
        items_7.AddItem(42526, 0); //
        items_7.AddItem(42532, 0); //
        items_7.AddItem(42538, 0); //
        items_7.AddItem(42560, 0); //
        items_7.AddItem(42565, 0); //
        items_7.AddItem(42571, 0); //
        items_7.AddItem(42579, 0); //
        items_7.AddItem(42584, 0); //
        items_7.AddItem(42589, 0); //
        items_7.AddItem(42598, 0); //
        items_7.AddItem(42603, 0); //
        items_7.AddItem(42608, 0); //
        items_7.AddItem(42615, 0); //
        items_7.AddItem(42621, 0); //
        items_7.AddItem(42853, 0); //
        items_7.AddItem(44421, 0); //
        items_7.AddItem(44422, 0); //
        items_7.AddItem(45937, 0); //
        items_7.AddItem(45938, 0); //
        items_7.AddItem(45939, 0); //
        items_7.AddItem(45948, 0); //
        items_7.AddItem(45949, 0); //
        items_7.AddItem(45950, 0); //
        items_7.AddItem(45951, 0); //
        items_7.AddItem(45952, 0); //
        items_7.AddItem(45953, 0); //
        items_7.AddItem(45954, 0); //
        items_7.AddItem(45955, 0); //
        items_7.AddItem(45956, 0); //
        items_7.AddItem(45957, 0); //
        items_7.AddItem(45958, 0); //
        items_7.AddItem(45959, 0); //
        items_7.AddItem(45960, 0); //
        items_7.AddItem(45961, 0); //
        items_7.AddItem(45962, 0); //
        items_7.AddItem(45963, 0); //
        items_7.AddItem(45964, 0); //
        items_7.AddItem(45965, 0); //
        items_7.AddItem(45966, 0); //
        items_7.AddItem(45967, 0); //
        items_7.AddItem(45968, 0); //
        items_7.AddItem(45969, 0); //
        items_7.AddItem(45970, 0); //
        items_7.AddItem(45971, 0); //
        items_7.AddItem(46373, 0); //
		itemlists.push_back(items_7);

		Vendor vendor_8(700007, GOSSIP_ICON_VENDOR, "Season 7 Set-Teile");
        ItemList items_8(&vendor_8);
        items_8.AddItem(40790, 2960); //
        items_8.AddItem(40791, 2960); //
        items_8.AddItem(40792, 2960); //
        items_8.AddItem(40810, 2270); //
        items_8.AddItem(40811, 2270); //
        items_8.AddItem(40812, 2270); //
        items_8.AddItem(40829, 2960); //
        items_8.AddItem(40830, 2960); //
        items_8.AddItem(40831, 2960); //
        items_8.AddItem(40850, 2960); //
        items_8.AddItem(40851, 2960); //
        items_8.AddItem(40852, 2960); //
        items_8.AddItem(40870, 2960); //
        items_8.AddItem(40871, 2960); //
        items_8.AddItem(40872, 2960); //
        items_8.AddItem(40910, 2960); //
        items_8.AddItem(40928, 2270); //
        items_8.AddItem(40934, 2960); //
        items_8.AddItem(40940, 2960); //
        items_8.AddItem(40964, 2960); //
        items_8.AddItem(40994, 2960); //
        items_8.AddItem(40995, 2960); //
        items_8.AddItem(41002, 2270); //
        items_8.AddItem(41008, 2270); //
        items_8.AddItem(41014, 2960); //
        items_8.AddItem(41020, 2960); //
        items_8.AddItem(41028, 2960); //
        items_8.AddItem(41034, 2960); //
        items_8.AddItem(41039, 2960); //
        items_8.AddItem(41045, 2960); //
        items_8.AddItem(41082, 2960); //
        items_8.AddItem(41088, 2960); //
        items_8.AddItem(41138, 2270); //
        items_8.AddItem(41144, 2270); //
        items_8.AddItem(41152, 2960); //
        items_8.AddItem(41158, 2960); //
        items_8.AddItem(41200, 2960); //
        items_8.AddItem(41206, 2960); //
        items_8.AddItem(41212, 2960); //
        items_8.AddItem(41218, 2960); //
        items_8.AddItem(41276, 2960); //
        items_8.AddItem(41282, 2960); //
        items_8.AddItem(41288, 2270); //
        items_8.AddItem(41294, 2270); //
        items_8.AddItem(41299, 2960); //
        items_8.AddItem(41305, 2960); //
        items_8.AddItem(41311, 2960); //
        items_8.AddItem(41317, 2960); //
        items_8.AddItem(41322, 2960); //
        items_8.AddItem(41328, 2960); //
        items_8.AddItem(41651, 2960); //
        items_8.AddItem(41656, 2960); //
        items_8.AddItem(41662, 2960); //
        items_8.AddItem(41668, 2960); //
        items_8.AddItem(41673, 2960); //
        items_8.AddItem(41679, 2960); //
        items_8.AddItem(41684, 2960); //
        items_8.AddItem(41716, 2960); //
        items_8.AddItem(41768, 2270); //
        items_8.AddItem(41774, 2270); //
        items_8.AddItem(41855, 2960); //
        items_8.AddItem(41860, 2960); //
        items_8.AddItem(41865, 2960); //
        items_8.AddItem(41870, 2960); //
        items_8.AddItem(41875, 2270); //
        items_8.AddItem(41916, 2960); //
        items_8.AddItem(41922, 2960); //
        items_8.AddItem(41928, 2960); //
        items_8.AddItem(41935, 2960); //
        items_8.AddItem(41941, 2270); //
        items_8.AddItem(41947, 2960); //
        items_8.AddItem(41954, 2960); //
        items_8.AddItem(41960, 2960); //
        items_8.AddItem(41966, 2960); //
        items_8.AddItem(41972, 2270); //
        items_8.AddItem(41994, 2960); //
        items_8.AddItem(41999, 2960); //
        items_8.AddItem(42006, 2960); //
        items_8.AddItem(42012, 2960); //
        items_8.AddItem(42018, 2270); //
        items_8.AddItem(42124, 2965); //
        items_8.AddItem(42126, 2965); //
        items_8.AddItem(42133, 2966); //
        items_8.AddItem(42134, 2966); //
        items_8.AddItem(42135, 2966); //
        items_8.AddItem(42136, 2966); //
        items_8.AddItem(42137, 2966); //
        items_8.AddItem(45706, 2596); //
		itemlists.push_back(items_8);

		Vendor vendor_9(700008, GOSSIP_ICON_VENDOR, "Season 7 NonSets");
        ItemList items_9(&vendor_9);
		items_9.AddItem(40883, 2958); //
        items_9.AddItem(40884, 2958); //
        items_9.AddItem(40890, 2958); //
        items_9.AddItem(40978, 2958); //
        items_9.AddItem(40979, 2958); //
        items_9.AddItem(40984, 2958); //
        items_9.AddItem(41052, 2958); //
        items_9.AddItem(41056, 2958); //
        items_9.AddItem(41061, 2958); //
        items_9.AddItem(41066, 2958); //
        items_9.AddItem(41071, 2958); //
        items_9.AddItem(41076, 2958); //
        items_9.AddItem(41226, 2958); //
        items_9.AddItem(41231, 2958); //
        items_9.AddItem(41236, 2958); //
        items_9.AddItem(41618, 2958); //
        items_9.AddItem(41622, 2958); //
        items_9.AddItem(41626, 2958); //
        items_9.AddItem(41631, 2958); //
        items_9.AddItem(41636, 2958); //
        items_9.AddItem(41641, 2958); //
        items_9.AddItem(41833, 2958); //
        items_9.AddItem(41837, 2958); //
        items_9.AddItem(41841, 2958); //
        items_9.AddItem(41882, 2958); //
        items_9.AddItem(41886, 2958); //
        items_9.AddItem(41894, 2958); //
        items_9.AddItem(41899, 2958); //
        items_9.AddItem(41904, 2958); //
        items_9.AddItem(41910, 2958); //
        items_9.AddItem(42041, 2958); //
        items_9.AddItem(42042, 2958); //
        items_9.AddItem(42043, 2958); //
        items_9.AddItem(42044, 2958); //
        items_9.AddItem(42045, 2958); //
        items_9.AddItem(42046, 2958); //
        items_9.AddItem(42047, 2958); //
        items_9.AddItem(42076, 2958); //
        items_9.AddItem(42077, 2958); //
        items_9.AddItem(42078, 2958); //
        items_9.AddItem(42079, 2958); //
        items_9.AddItem(42080, 2958); //
        items_9.AddItem(42081, 2958); //
        items_9.AddItem(42082, 2958); //
        items_9.AddItem(42118, 2958); //
        items_9.AddItem(42119, 2958); //
        items_9.AddItem(42483, 2256); //
        items_9.AddItem(42504, 98); //
        items_9.AddItem(42515, 98); //
        items_9.AddItem(42521, 98); //
        items_9.AddItem(42527, 2967); //
        items_9.AddItem(42533, 2967); //
        items_9.AddItem(42539, 2967); //
        items_9.AddItem(42561, 2256); //
        items_9.AddItem(42566, 2256); //
        items_9.AddItem(42572, 2256); //
        items_9.AddItem(42580, 2969); //
        items_9.AddItem(42585, 2969); //
        items_9.AddItem(42591, 2969); //
        items_9.AddItem(42599, 2969); //
        items_9.AddItem(42604, 2969); //
        items_9.AddItem(42609, 2969); //
        items_9.AddItem(42616, 2969); //
        items_9.AddItem(42622, 2969); //
        items_9.AddItem(42854, 2969); //
        items_9.AddItem(46374, 2958); //
        items_9.AddItem(48402, 2965); //
        items_9.AddItem(48404, 2965); //
        items_9.AddItem(48406, 2965); //
        items_9.AddItem(48408, 2958); //
        items_9.AddItem(48410, 2965); //
        items_9.AddItem(48412, 2965); //
        items_9.AddItem(48414, 2965); //
        items_9.AddItem(48420, 2965); //
        items_9.AddItem(48422, 2965); //
        items_9.AddItem(48424, 2965); //
        items_9.AddItem(48426, 2561); //
        items_9.AddItem(48428, 2561); //
        items_9.AddItem(48432, 2561); //
        items_9.AddItem(48435, 2561); //
        items_9.AddItem(48438, 2561); //
        items_9.AddItem(48440, 2561); //
        items_9.AddItem(48442, 2561); //
        items_9.AddItem(48444, 2561); //
        items_9.AddItem(48507, 2958); //
        items_9.AddItem(48509, 2958); //
        items_9.AddItem(48511, 2958); //
        items_9.AddItem(48513, 2958); //
        items_9.AddItem(48515, 2958); //
        items_9.AddItem(48517, 2965); //
        items_9.AddItem(48519, 2958); //
        items_9.AddItem(48521, 2965); //
        items_9.AddItem(48523, 2965); //
        items_9.AddItem(49179, 2958); //
        items_9.AddItem(49181, 2958); //
        items_9.AddItem(49183, 2958); //
        items_9.AddItem(49185, 98); //
        items_9.AddItem(49187, 2967); //
        items_9.AddItem(49191, 2958); //

        itemlists.push_back(items_9);

        /* Verändere nicht was hier drunter steht
         * Dies ist das Ende des editierbaren Abschnitts
         * Verändere nur Dinge ÜBER diesem Commentblock, solange du nicht weißt was du tust!
         *
         * Peace out
         * Evilfairy~ */

        return itemlists;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        std::vector<ItemList> vendors = GetVendorList();

        /* DO NOT EDIT ANYTHING BELOW THIS LINE */
        for(int i = 0; i < vendors.size(); i++) // icon message sender guid
            player->ADD_GOSSIP_ITEM(vendors[i].GetVendor().getIcon(), vendors[i].GetVendor().getMessage(), GOSSIP_SENDER_MAIN, vendors[i].GetVendor().getGuid());

        player->TalkedToCreature(creature->GetEntry(), creature->GetGUID());
        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        player->CLOSE_GOSSIP_MENU();
        
        SendInventoryCustom(player, creature, action);
        
        return true;
    }

    void SendInventoryCustom(Player* player, Creature* vendor, int guid)
    {
        /* Remove Feign Death effects */
        if (player->HasUnitState(UNIT_STATE_DIED))
            player->RemoveAurasByType(SPELL_AURA_FEIGN_DEATH);

        /* Stop NPC moving */
        if (vendor->isMoving())
            vendor->StopMoving();

        std::vector<ItemList> vendors = GetVendorList();
        ItemList myVendor;
        for(int i = 0; i < vendors.size(); i++)
        {
            if(vendors[i].GetVendor().getGuid() == guid)
            {
                myVendor = ItemList(&vendors[i].GetVendor(), &vendors[i].GetVendor().items);
                break;
            }
        }

        SmsgListInventory inventory_packet(vendor->GetGUID(), player->GetSession(), &myVendor.GetVendor().items, vendors);
        inventory_packet.Send(vendor, player);
    }
};
void AddSC_npc_multivendor()
{
    new npc_multivendor;
	new npc_multivendor_season;
}
