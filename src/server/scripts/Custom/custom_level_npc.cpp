// Author: Thainification @DarkThunder-WoW.net

#include "ScriptPCH.h"

class LEVEL_NPC : public CreatureScript
{
    public: LEVEL_NPC() : CreatureScript("LEVEL_NPC") {}

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->isInCombat())
        {
            creature->MonsterWhisper("Du bist in einen Kampf verwickelt. Komme wieder sobald du den Kampf beendet hast.", player->GetGUID());
            player->CLOSE_GOSSIP_MENU();
        }
        player->ADD_GOSSIP_ITEM(1, "Erreiche das Maxiumlevel und erhalte zus\303\244tzlich 25.000 Gold!", GOSSIP_SENDER_MAIN, 2);
        player->ADD_GOSSIP_ITEM(0, "Viel Erfolg und Spa\303\237!", GOSSIP_SENDER_MAIN, 500);
        player->PlayerTalkClass->SendGossipMenu(950000, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();  
         
        if (action == 2)
        {
            uint32 acc = player->GetSession()->GetAccountId();
            QueryResult result;
            result = LoginDatabase.PQuery("SELECT `account` FROM `account_maxlvl` WHERE `account`='%u'", acc);
            
            if(!result)
            {
                QueryResult checklvl = CharacterDatabase.PQuery("SELECT count(*) FROM `characters` WHERE `level`=80 AND `account`='%u'", acc);
                uint32 count = 0;
                if (checklvl)
                {
                    Field* fields = checklvl->Fetch();
                    count = fields[0].GetUInt32();
                }                  
                
                if(count == 0 && player->getLevel() >= 15 && player->getLevel() !=80)
                {
                    player->ModifyMoney(+250000000);
                    player->SetLevel(80);
                    creature->MonsterWhisper("Herzlichen Gl\303\274ckwunsch und viel Spa\303\237 auf DarkThunder-WoW!", player->GetGUID());
                    player->CLOSE_GOSSIP_MENU();
                    LoginDatabase.PExecute("INSERT INTO `account_maxlvl` (`account`) VALUES ('%u')", acc);
                } 
                else
                {
                    creature->MonsterWhisper("Tut mir leid, aber ich helfe nur den Bed\303\274rftigen.", player->GetGUID());
                    player->CLOSE_GOSSIP_MENU();
                }
            }
            else
            {
               creature->MonsterWhisper("Dieser Service ist einmalig!", player->GetGUID());
               player->CLOSE_GOSSIP_MENU();
            }
        }
            
        if (action == 500)
        {
            player->GetSession()->SendNotification("Bis zum n\303\244chsten mal!");
            creature->MonsterWhisper("Bis zum n\303\244chsten mal!", player->GetGUID());
            player->CLOSE_GOSSIP_MENU();
        }
        return true;
    }
};

void AddSC_LEVEL_NPC()
{
    new LEVEL_NPC();
}

class CHANGE_NPC : public CreatureScript
{
    public:
    CHANGE_NPC() : CreatureScript("CHANGE_NPC") {}

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->isInCombat())
        {
            creature->MonsterWhisper("Du bist in einen Kampf verwickelt. Komme wieder sobald du den Kampf beendet hast.", player->GetGUID());
            player->CLOSE_GOSSIP_MENU();
        }
        player->ADD_GOSSIP_ITEM(5, "Fraktionswechsel", GOSSIP_SENDER_MAIN, 2);
		player->ADD_GOSSIP_ITEM(5, "Rassenwechsel", GOSSIP_SENDER_MAIN, 3);
		player->ADD_GOSSIP_ITEM(5, "Charakter anpassen", GOSSIP_SENDER_MAIN, 4);
        player->ADD_GOSSIP_ITEM(0, "Aufwiedersehen!", GOSSIP_SENDER_MAIN, 500);
        player->PlayerTalkClass->SendGossipMenu(950001, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();  
         
        if (action == 2)
        {
            uint32 guid = player->GetGUID();
            QueryResult result;
            result = LoginDatabase.PQuery("SELECT `guid` FROM `account_factionchange` WHERE `guid`='%u'", guid);
            
            if(!result)
            {
                    player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
                    creature->MonsterWhisper("Bei deinem n\303\244chsten Login kannst du die Fraktion wechseln.", player->GetGUID());
                    player->CLOSE_GOSSIP_MENU();
                    LoginDatabase.PExecute("INSERT INTO `account_factionchange` (`guid`) VALUES ('%u')", guid);
            }
            else
            {
               creature->MonsterWhisper("Dieser Service ist einmalig!", player->GetGUID());
               player->CLOSE_GOSSIP_MENU();
            }
        }

		if (action == 3)
        {
            uint32 guid = player->GetGUID();
            QueryResult result;
            result = LoginDatabase.PQuery("SELECT `guid` FROM `account_racechange` WHERE `guid`='%u'", guid);
            
            if(!result)
            {
                    player->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
                    creature->MonsterWhisper("Bei deinem n\303\244chsten Login kannst du die Rasse wechseln.", player->GetGUID());
                    player->CLOSE_GOSSIP_MENU();
                    LoginDatabase.PExecute("INSERT INTO `account_racechange` (`guid`) VALUES ('%u')", guid);
            }
            else
            {
               creature->MonsterWhisper("Dieser Service ist einmalig!", player->GetGUID());
               player->CLOSE_GOSSIP_MENU();
            }
        }

		if (action == 4)
		{
			player->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
			creature->MonsterWhisper("Bei deinem n\303\244chsten Login kannst du deinen Charakter anpassen.", player->GetGUID());
			player->CLOSE_GOSSIP_MENU();
		}
            
        if (action == 500)
        {
            player->GetSession()->SendNotification("Bis zum n\303\244chsten mal!");
            creature->MonsterWhisper("Bis zum n\303\244chsten mal!", player->GetGUID());
            player->CLOSE_GOSSIP_MENU();
        }
        return true;
    }
};

void AddSC_CHANGE_NPC()
{
    new CHANGE_NPC();
}