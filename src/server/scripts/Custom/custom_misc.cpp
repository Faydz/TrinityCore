#include "ScriptPCH.h"


enum ID
{
	ID_HONORTOKEN		= 900002,
	ID_JUSTICETOKEN		= 900001,
	ID_VIPTOKEN			= 900003
};

class Vote_NPC : public CreatureScript
{
public:
		Vote_NPC() : CreatureScript("Vote_NPC") {}
		
		bool OnGossipHello(Player* player, Creature* creature)
		{
			if (player->HasItemCount(ID_JUSTICETOKEN, 1))
			{
				player->ADD_GOSSIP_ITEM(0, "Gerechtigkeitspunktetoken eintauschen", GOSSIP_SENDER_MAIN, 1);
			}
			
			if (player->HasItemCount(ID_HONORTOKEN, 1))
			{
				player->ADD_GOSSIP_ITEM(0, "Ehrentoken eintauschen", GOSSIP_SENDER_MAIN, 2);
			}
			
			if (player->HasItemCount(ID_VIPTOKEN, 1))
			{
				player->ADD_GOSSIP_ITEM(0, "VIP Token eintauschen", GOSSIP_SENDER_MAIN, 3);
			}
			player->ADD_GOSSIP_ITEM(0, "Aufwiedersehen...", GOSSIP_SENDER_MAIN, 10);
			player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			return true;
		}
		
		bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
		{
			uint32 acc = player->GetSession()->GetAccountId();
			switch(action)
			{
			case 1:
				player->ModifyCurrency(395, 400000, true);
				player->DestroyItemCount(ID_JUSTICETOKEN, 1, true);
				creature->MonsterWhisper("Vielen Dank, dass du f\303\274r DarkThunder WoW gevotet hast!", player->GetGUID());
				break;
			case 2:
				player->ModifyCurrency(392, 400000, true);
				player->DestroyItemCount(ID_HONORTOKEN, 1, true);
				creature->MonsterWhisper("Vielen Dank, dass du f\303\274r DarkThunder WoW gevotet hast!", player->GetGUID());
				break;
			case 3:
			LoginDatabase.PExecute("INSERT INTO `rbac_account_groups` (`accountId`, `groupId`, `realmId`) VALUES ('%u', '2', '-1')", acc);
			LoginDatabase.PExecute("INSERT INTO `vip_days` (`accountID`) VALUES ('%u')", acc);
			player->DestroyItemCount(ID_VIPTOKEN, 1, true);
			creature->MonsterWhisper("Vielen Dank, dass du f\303\274r DarkThunder WoW gevotet hast! Dein VIP Account ist jetzt f\303\274r 3 Tage aktiv.", player->GetGUID());
				break;
			case 10:
				player->CLOSE_GOSSIP_MENU();
				break;
			}
			return true;			
		}
		
};

void AddSC_custom_misc()
{
	new Vote_NPC();
}