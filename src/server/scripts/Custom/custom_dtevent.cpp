#include "ScriptPCH.h"

class custom_dtevent_netz : public ItemScript
{
public:
    custom_dtevent_netz() : ItemScript("custom_dtevent_netz") {}

    bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
    {
        if (Unit* tar = player->GetSelectedUnit())
            if (tar->GetEntry())
            {
                switch (tar->GetEntry())
                {
                    case 27438: //Regenbogenforelle
                        player->AddItem(988000,1);
                        break;
                    case 26369: //Kaiseradler
                        player->AddItem(988001,1);
                        break;
                    case 26363: //Großhornhirsch
                        player->AddItem(988002,1);
                        break;
                    case 25679: //Dampffrosch
                        player->AddItem(988003,1);
                        break;
                    case 31685: //Boreanisches Murmeltier
                        player->AddItem(988004,1);
                        break;
                    case 25677: //Boreanischer Frosch
                        player->AddItem(988005,1);
                        break;
                    default:
                        break;
                }
            }
        return true;
    }
};


#define SPELL_ENRAGE 61715
#define QUEST_OSTERHASE 989001

class custom_dtevent_osterhase : public CreatureScript
{
public:
    custom_dtevent_osterhase() : CreatureScript("custom_dtevent_osterhase") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new custom_dtevent_osterhaseAI(pCreature);
    }

    struct custom_dtevent_osterhaseAI : public ScriptedAI
    {
        custom_dtevent_osterhaseAI(Creature *c) : ScriptedAI(c) {}
    
        void Reset()
        {
            me->RemoveAurasDueToSpell(SPELL_ENRAGE);
            me->RestoreFaction();
            me->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.5f);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_UNK_15);
        }

        void ActivateCombat(Player* pPlayer)
        {
            me->setFaction(14);
            me->SetFloatValue(OBJECT_FIELD_SCALE_X, 2.7f);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_UNK_15);
            me->CastSpell(me, SPELL_ENRAGE, true);

            AttackStart(pPlayer);
        }

        void JustDied(Unit* killer)
        {
            if (Player* pKiller = killer->ToPlayer())
                pKiller->CompleteQuest(QUEST_OSTERHASE);
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (pPlayer->GetQuestStatus(QUEST_OSTERHASE) == QUEST_STATUS_INCOMPLETE)
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Hallo?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        pPlayer->SEND_GOSSIP_MENU(989001, pCreature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();

        switch (uiAction)
        {
            case GOSSIP_ACTION_INFO_DEF+1:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Koennt ihr mich verstehen?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                pPlayer->SEND_GOSSIP_MENU(989002, pCreature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+2:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Der Nachtelf dort fragte sich, woher ihr alle kommt..", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
                pPlayer->SEND_GOSSIP_MENU(989003, pCreature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+3:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Wenn ihr zu den Nobelgartenhasen gehoert, koennt ihr mir doch sicher bei der Suche behilflich sein, oder? Gegen eine kleine Gegenleistung, versteht sich.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
                pPlayer->SEND_GOSSIP_MENU(989004, pCreature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+4:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Koennt ihr mir dann wenigstens ein wenig Schokolade ueberlassen?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
                pPlayer->SEND_GOSSIP_MENU(989005, pCreature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+5:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Du bist doch nur ein kleiner, wehrloser Hase also gib mir einfach die Schokolade und wir vergessen das Ganze.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+6);
                pPlayer->SEND_GOSSIP_MENU(989006, pCreature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+6:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Na warte! Du wirst schon sehen!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+7);
                pPlayer->SEND_GOSSIP_MENU(989007, pCreature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+7:
                if (custom_dtevent_osterhaseAI* pHase = CAST_AI(custom_dtevent_osterhase::custom_dtevent_osterhaseAI, pCreature->AI()))
                {
                    pHase->ActivateCombat(pPlayer);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
                break;
        }

        return true;
    }
};

#define ITEM_OSTEREI 989000
class custom_dtevent_osterei : public CreatureScript
{
public:
        custom_dtevent_osterei() : CreatureScript("custom_dtevent_osterei") { }

        bool OnGossipHello(Player* pPlayer, Creature* pCreature)
        {
            QuestStatus status = pPlayer->GetQuestStatus(pCreature->GetEntry()-10);
            if (status != QUEST_STATUS_INCOMPLETE)
                return false;

            ItemPosCountVec dest;
            InventoryResult msg = pPlayer->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_OSTEREI, 1);
            if (msg != EQUIP_ERR_OK)
            {
                pPlayer->SendEquipError(msg, NULL, NULL, ITEM_OSTEREI);
                return false;
            }
            
            Item* newitem = pPlayer->StoreNewItem(dest, ITEM_OSTEREI, true);
            pPlayer->SendNewItem(newitem, 1, true, false);

            pPlayer->RemoveActiveQuest(pCreature->GetEntry()-10);
            pPlayer->SaveToDB();

            pCreature->DestroyForNearbyPlayers();
            if (pCreature->isAlive())
                pCreature->setDeathState(JUST_DIED);
            pCreature->RemoveCorpse(true);

            return false;
        }
};

void AddSC_custom_dtevent()
{
    new custom_dtevent_netz();
    new custom_dtevent_osterhase();
    new custom_dtevent_osterei();
}