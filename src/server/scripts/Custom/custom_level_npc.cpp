// Author: Thainification @DarkThunder-WoW.net

#include "ScriptPCH.h"

class LEVEL_NPC : public CreatureScript
{
    public:
    LEVEL_NPC() : CreatureScript("LEVEL_NPC") {}

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
                
                if(count <= 1 && player->getLevel() >= 15 && player->getLevel() !=80)
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