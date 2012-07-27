/* Author: Thainification | DarkThunder-WoW.net */
#include "ScriptPCH.h"

/*
	Vorraussetzungen:
	AchievementID1 = 1792, Och, ist das nicht s³¯?
	AchievementID2 = 1789, Tõgliche M³hen 
	AchievementID3 = 1788, Schlechtes Vorbild
	AchievementID4 = 1790, Hoch lebe der K÷nig, mein Kleiner
	AchievementID5 = 1791, Allein zuhaus
*/

class AV_NPC : public CreatureScript
{
public:
	AV_NPC() : CreatureScript("AV_NPC") {}
	
	bool OnGossipHello(Player* player, Creature* creature)
	{
		if (player->isInCombat())
		{
			creature->MonsterWhisper("Du bist im Kampf. Komme wieder sobald du den Kampf beendet hast.", player->GetGUID());
			player->CLOSE_GOSSIP_MENU();
		}
		
		player->ADD_GOSSIP_ITEM(1, "Erfolge", GOSSIP_SENDER_MAIN, 1);
		player->ADD_GOSSIP_ITEM(0, "Aufwiedersehen!", GOSSIP_SENDER_MAIN, 500);
		player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		return true;
	}
	
	bool OnGossipSelect(Player * player, Creature * creature, uint32 sender, uint32 action)
	{          
		if (sender == GOSSIP_SENDER_MAIN)
		{
			player->PlayerTalkClass->ClearMenus();
			
			if (action == 1)
			{	
				player->ADD_GOSSIP_ITEM(1, "Eine harte Schule", GOSSIP_SENDER_MAIN, 2);
				player->ADD_GOSSIP_ITEM(0, "Aufwiedersehen!", GOSSIP_SENDER_MAIN, 500);
				player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			};
		}										
		if (action == 2)
		{
			if (player->GetAchievementMgr().HasAchieved(1792) && player->GetAchievementMgr().HasAchieved(1789) && player->GetAchievementMgr().HasAchieved(1788) && player->GetAchievementMgr().HasAchieved(1790) && player->GetAchievementMgr().HasAchieved(1791))
			{
				AchievementEntry const* Erfolg = sAchievementStore.LookupEntry(1786);
				player->CompletedAchievement(Erfolg);
				creature->MonsterWhisper("Du hast den Erfolg 'Eine harte Schule' erhalten!", player->GetGUID());
				player->CLOSE_GOSSIP_MENU();
			}
			
			else
			{
				creature->MonsterWhisper("Du erf³llst leider nicht die Anforderungen!", player->GetGUID());
				player->CLOSE_GOSSIP_MENU();
			}
		}
		
		if (action == 500)
		{
			player->GetSession()->SendNotification("Bis zum nõchsten mal!");
			player->CLOSE_GOSSIP_MENU();
		}
		
		return true;
	}
};
void AddSC_AV_NPC()
{
	new AV_NPC();
}

/* DarkThunder WoW
CD reset nach einem Duell im Playertreff */

class DuelCD_Reset : public PlayerScript
{
public:
	DuelCD_Reset() : PlayerScript("DuelCD_Reset") {}

	void OnDuelEnd(Player *winner, Player *looser, DuelCompleteType type)
	{
		if (winner->GetAreaId() == 11 && type != DUEL_INTERRUPTED) 
		{
			winner->RemoveArenaSpellCooldowns();
			looser->RemoveArenaSpellCooldowns();
		}
	}
};

void AddSC_DuelCD_Reset()
{
	new DuelCD_Reset();
}

// Author: Roca | WoW-Studio.net
// Modified by: Thainification

class Morph_NPC : public CreatureScript
{
public:
	Morph_NPC() : CreatureScript("Morph_NPC") {}

	bool OnGossipHello(Player* player, Creature* creature)
	{
		player->ADD_GOSSIP_ITEM(5, "Fun",                                               GOSSIP_SENDER_MAIN,   1);
		player->ADD_GOSSIP_ITEM(5, "Bosse",                                             GOSSIP_SENDER_MAIN,   2);
		player->ADD_GOSSIP_ITEM(5, "Wichtige Personen",                                 GOSSIP_SENDER_MAIN,   3);
		player->ADD_GOSSIP_ITEM(5, "Standart-Morphs M\303\244nnlich",                   GOSSIP_SENDER_MAIN,   4);
		player->ADD_GOSSIP_ITEM(5, "Standart-Morphs Weiblich",                          GOSSIP_SENDER_MAIN,   5);
		player->ADD_GOSSIP_ITEM(5, "Kreaturen",                                         GOSSIP_SENDER_MAIN,   6);
		player->ADD_GOSSIP_ITEM(0, "Demorph",                                           GOSSIP_SENDER_MAIN,  500);
		player->ADD_GOSSIP_ITEM(0, "Bye",                                               GOSSIP_SENDER_MAIN, 600);
		player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
	{ 
		if (sender == GOSSIP_SENDER_MAIN)
		{
			player->PlayerTalkClass->ClearMenus();
			if (action == 1)
			{
				player->ADD_GOSSIP_ITEM(5, "Kuh",                        GOSSIP_SENDER_MAIN,  100);
				player->ADD_GOSSIP_ITEM(5, "Eichh\303\266rnchen",        GOSSIP_SENDER_MAIN,  102);
				player->ADD_GOSSIP_ITEM(5, "Schaf",                      GOSSIP_SENDER_MAIN,  103);
				player->ADD_GOSSIP_ITEM(5, "Murloc",                     GOSSIP_SENDER_MAIN,  104);
				player->ADD_GOSSIP_ITEM(5, "Zombie",                     GOSSIP_SENDER_MAIN,  105);
				player->ADD_GOSSIP_ITEM(5, "Banshee",                    GOSSIP_SENDER_MAIN,  106);
				player->ADD_GOSSIP_ITEM(5, "Zergling",                   GOSSIP_SENDER_MAIN,  107);
				player->ADD_GOSSIP_ITEM(5, "Pinguin",                    GOSSIP_SENDER_MAIN,  108);
				player->ADD_GOSSIP_ITEM(0, "Demorph",                    GOSSIP_SENDER_MAIN,  500);
				player->ADD_GOSSIP_ITEM(0, "[Auswahlfenster]",           GOSSIP_SENDER_MAIN,  900);
				player->ADD_GOSSIP_ITEM(0, "Bye",                        GOSSIP_SENDER_MAIN, 600);
				player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			};

			if (action == 2)
			{
				player->ADD_GOSSIP_ITEM(5, "Hogger",                     GOSSIP_SENDER_MAIN,  200);
				player->ADD_GOSSIP_ITEM(5, "Mutter Shahraz",             GOSSIP_SENDER_MAIN,  201);
				player->ADD_GOSSIP_ITEM(5, "Illidan",                    GOSSIP_SENDER_MAIN,  202);
				player->ADD_GOSSIP_ITEM(5, "Algalon",                    GOSSIP_SENDER_MAIN,  203);
				player->ADD_GOSSIP_ITEM(5, "Lich King",                  GOSSIP_SENDER_MAIN,  204);
				player->ADD_GOSSIP_ITEM(5, "Kel'Thuzad",                 GOSSIP_SENDER_MAIN,  205);
				player->ADD_GOSSIP_ITEM(5, "Kael'thas",                  GOSSIP_SENDER_MAIN,  206);
				player->ADD_GOSSIP_ITEM(5, "Gurtogg Siedeblut",          GOSSIP_SENDER_MAIN,  207);
				player->ADD_GOSSIP_ITEM(5, "Teron Blutschatten",         GOSSIP_SENDER_MAIN,  208);
				player->ADD_GOSSIP_ITEM(5, "Blutk\303\266nigin Lana'thel",      GOSSIP_SENDER_MAIN,  209);
				player->ADD_GOSSIP_ITEM(5, "Todesbringer Saurfang",      GOSSIP_SENDER_MAIN,  210);
				player->ADD_GOSSIP_ITEM(0, "Demorph",                    GOSSIP_SENDER_MAIN,  500);
				player->ADD_GOSSIP_ITEM(0, "[Auswahlfenster]",           GOSSIP_SENDER_MAIN,  900);
				player->ADD_GOSSIP_ITEM(0, "Bye",                        GOSSIP_SENDER_MAIN, 600);
				player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			};

			if (action == 3)
			{
				player->ADD_GOSSIP_ITEM(5, "Mc",                         GOSSIP_SENDER_MAIN,  307);
				player->ADD_GOSSIP_ITEM(5, "Arthas",                     GOSSIP_SENDER_MAIN,  300);
				player->ADD_GOSSIP_ITEM(5, "Thrall",                     GOSSIP_SENDER_MAIN,  301);
				player->ADD_GOSSIP_ITEM(5, "Sylvanas",                   GOSSIP_SENDER_MAIN,  302);
				player->ADD_GOSSIP_ITEM(5, "Varian Wrynn",               GOSSIP_SENDER_MAIN,  303);
				player->ADD_GOSSIP_ITEM(5, "Bronzebart",                 GOSSIP_SENDER_MAIN,  304);
				player->ADD_GOSSIP_ITEM(5, "Jaina Proudmoore",           GOSSIP_SENDER_MAIN,  305);
				player->ADD_GOSSIP_ITEM(5, "Alexstrasza",                GOSSIP_SENDER_MAIN,  306);
				player->ADD_GOSSIP_ITEM(0, "Demorph",                    GOSSIP_SENDER_MAIN,  500);
				player->ADD_GOSSIP_ITEM(0, "[Auswahlfenster]",           GOSSIP_SENDER_MAIN,  900);
				player->ADD_GOSSIP_ITEM(0, "Bye",                        GOSSIP_SENDER_MAIN, 600);
				player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			};

			if (action == 4)
			{
				player->ADD_GOSSIP_ITEM(5, "Blutelf Mann",               GOSSIP_SENDER_MAIN,  350);
				player->ADD_GOSSIP_ITEM(5, "Draenei Mann",               GOSSIP_SENDER_MAIN,  352);
				player->ADD_GOSSIP_ITEM(5, "Zwerg Mann",                 GOSSIP_SENDER_MAIN,  354);
				player->ADD_GOSSIP_ITEM(5, "Untoter Mann",               GOSSIP_SENDER_MAIN,  356);
				player->ADD_GOSSIP_ITEM(5, "Gnom Mann",                  GOSSIP_SENDER_MAIN,  357);
				player->ADD_GOSSIP_ITEM(5, "Mensch Mann",                GOSSIP_SENDER_MAIN,  360);
				player->ADD_GOSSIP_ITEM(5, "Nachtelf Mann",              GOSSIP_SENDER_MAIN,  362);
				player->ADD_GOSSIP_ITEM(5, "Orc Mann",                   GOSSIP_SENDER_MAIN,  363);
				player->ADD_GOSSIP_ITEM(5, "Tauren Mann",                GOSSIP_SENDER_MAIN,  365);		
				player->ADD_GOSSIP_ITEM(5, "Troll Mann",                 GOSSIP_SENDER_MAIN,  367);
				player->ADD_GOSSIP_ITEM(0, "Demorph",                     GOSSIP_SENDER_MAIN,  500);
				player->ADD_GOSSIP_ITEM(0, "[Auswahlfenster]",            GOSSIP_SENDER_MAIN,  900);
				player->ADD_GOSSIP_ITEM(0, "Bye",                         GOSSIP_SENDER_MAIN, 600);
				player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			};

			if (action == 5)
			{
				player->ADD_GOSSIP_ITEM(5, "Draenei Frau",               GOSSIP_SENDER_MAIN,  351);
				player->ADD_GOSSIP_ITEM(5, "Zwerg Frau",                 GOSSIP_SENDER_MAIN,  353);
				player->ADD_GOSSIP_ITEM(5, "Untoter Frau",               GOSSIP_SENDER_MAIN,  355);
				player->ADD_GOSSIP_ITEM(5, "Gnom Frau",                  GOSSIP_SENDER_MAIN,  358);
				player->ADD_GOSSIP_ITEM(5, "Mensch Frau",                GOSSIP_SENDER_MAIN,  359);
				player->ADD_GOSSIP_ITEM(5, "Nachtelf Frau",              GOSSIP_SENDER_MAIN,  361);
				player->ADD_GOSSIP_ITEM(5, "Orc Frau",                   GOSSIP_SENDER_MAIN,  364);
				player->ADD_GOSSIP_ITEM(5, "Tauren Frau",                GOSSIP_SENDER_MAIN,  366);
				player->ADD_GOSSIP_ITEM(5, "Troll Frau",                 GOSSIP_SENDER_MAIN,  368);
				player->ADD_GOSSIP_ITEM(0, "Demorph",                     GOSSIP_SENDER_MAIN,  500);
				player->ADD_GOSSIP_ITEM(0, "[Auswahlfenster]",            GOSSIP_SENDER_MAIN,  900);
				player->ADD_GOSSIP_ITEM(0, "Bye",                         GOSSIP_SENDER_MAIN,  600);
				player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			};

			if (action == 6)
			{
				player->ADD_GOSSIP_ITEM(5, "Tiere",                                              GOSSIP_SENDER_MAIN,   7);
				player->ADD_GOSSIP_ITEM(5, "Humanoide",                                          GOSSIP_SENDER_MAIN,   8);
				player->ADD_GOSSIP_ITEM(5, "Elementare",                                         GOSSIP_SENDER_MAIN,   9);
				player->ADD_GOSSIP_ITEM(0, "[Auswahlfenster]",                                   GOSSIP_SENDER_MAIN,  900);
				player->ADD_GOSSIP_ITEM(0, "Bye",                                                GOSSIP_SENDER_MAIN, 600);
				player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			};

			if (action == 7)
			{
				player->ADD_GOSSIP_ITEM(5, "Wolf",                                               GOSSIP_SENDER_MAIN, 400);
				player->ADD_GOSSIP_ITEM(5, "Eber",                                               GOSSIP_SENDER_MAIN, 401);
				player->ADD_GOSSIP_ITEM(5, "Spinne",                                             GOSSIP_SENDER_MAIN, 402);
				player->ADD_GOSSIP_ITEM(5, "Tiger",                                              GOSSIP_SENDER_MAIN, 403);
				player->ADD_GOSSIP_ITEM(5, "Panther",                                            GOSSIP_SENDER_MAIN, 404);
				player->ADD_GOSSIP_ITEM(5, "Gorilla",                                            GOSSIP_SENDER_MAIN, 405);
				player->ADD_GOSSIP_ITEM(5, "Raptor",                                             GOSSIP_SENDER_MAIN, 406);
				player->ADD_GOSSIP_ITEM(5, "Skorpion",                                           GOSSIP_SENDER_MAIN, 407);
				player->ADD_GOSSIP_ITEM(5, "Hy\303\244ne",                                       GOSSIP_SENDER_MAIN, 408);
				player->ADD_GOSSIP_ITEM(5, "Basilisk",                                           GOSSIP_SENDER_MAIN, 409);
				player->ADD_GOSSIP_ITEM(0, "Demorph",                                             GOSSIP_SENDER_MAIN, 500);
				player->ADD_GOSSIP_ITEM(0, "[Auswahlfenster]",                                    GOSSIP_SENDER_MAIN, 900);
				player->ADD_GOSSIP_ITEM(0, "Bye",                                                 GOSSIP_SENDER_MAIN, 600);
				player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			};

			if (action == 8)
			{
				player->ADD_GOSSIP_ITEM(5, "Defias",                                             GOSSIP_SENDER_MAIN, 410);
				player->ADD_GOSSIP_ITEM(5, "Mondkin",                                            GOSSIP_SENDER_MAIN, 411);
				player->ADD_GOSSIP_ITEM(5, "Zentaure",                                           GOSSIP_SENDER_MAIN, 412);
				player->ADD_GOSSIP_ITEM(5, "Oger",                                               GOSSIP_SENDER_MAIN, 413);
				player->ADD_GOSSIP_ITEM(5, "Goblin",                                             GOSSIP_SENDER_MAIN, 414);
				player->ADD_GOSSIP_ITEM(5, "Worg",                                               GOSSIP_SENDER_MAIN, 415);
				player->ADD_GOSSIP_ITEM(5, "H\303\266llenorc",                                   GOSSIP_SENDER_MAIN, 416);
				player->ADD_GOSSIP_ITEM(5, "Naga",                                               GOSSIP_SENDER_MAIN, 417);
				player->ADD_GOSSIP_ITEM(5, "Trogg",                                              GOSSIP_SENDER_MAIN, 418);
				player->ADD_GOSSIP_ITEM(0, "Demorph",                                             GOSSIP_SENDER_MAIN, 500);
				player->ADD_GOSSIP_ITEM(0, "[Auswahlfenster]",                                    GOSSIP_SENDER_MAIN, 900);
				player->ADD_GOSSIP_ITEM(0, "Bye",                                                 GOSSIP_SENDER_MAIN, 600);
				player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			};

			if (action == 9)
			{
				player->ADD_GOSSIP_ITEM(5, "Wasserelementar",                                    GOSSIP_SENDER_MAIN, 419);
				player->ADD_GOSSIP_ITEM(5, "Erdelementar",                                       GOSSIP_SENDER_MAIN, 420);
				player->ADD_GOSSIP_ITEM(5, "Luftelementar",                                      GOSSIP_SENDER_MAIN, 421);
				player->ADD_GOSSIP_ITEM(5, "Feuerelementar",                                     GOSSIP_SENDER_MAIN, 422);
				player->ADD_GOSSIP_ITEM(0, "Demorph",                                             GOSSIP_SENDER_MAIN, 500);
				player->ADD_GOSSIP_ITEM(0, "[Auswahlfenster]",                                    GOSSIP_SENDER_MAIN, 900);
				player->ADD_GOSSIP_ITEM(0, "Bye",                                                 GOSSIP_SENDER_MAIN, 600);
				player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			};


			if (action == 900)
			{
				player->ADD_GOSSIP_ITEM(5, "Fun",                                               GOSSIP_SENDER_MAIN,   1);
				player->ADD_GOSSIP_ITEM(5, "Bosse",                                             GOSSIP_SENDER_MAIN,   2);
				player->ADD_GOSSIP_ITEM(5, "Wichtige Personen",                                 GOSSIP_SENDER_MAIN,   3);
				player->ADD_GOSSIP_ITEM(5, "Standart-Morphs M\303\244nnlich",                   GOSSIP_SENDER_MAIN,   4);
				player->ADD_GOSSIP_ITEM(5, "Standart-Morphs Weiblich",                          GOSSIP_SENDER_MAIN,   5);
				player->ADD_GOSSIP_ITEM(5, "Kreaturen",                                         GOSSIP_SENDER_MAIN,   6);
				player->ADD_GOSSIP_ITEM(0, "Demorph",                                           GOSSIP_SENDER_MAIN,  500);
				player->ADD_GOSSIP_ITEM(0, "Bye",                                               GOSSIP_SENDER_MAIN, 600);
				player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			};
		}

        if (action > 9 && action != 900)
        player->RemoveAura(16595);
        player->RemoveAura(16591);

		if (action == 100)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(1060); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 102)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(134); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 103)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(856); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 104)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(441); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 105)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(10973); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 106)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(10728); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.7f);
		}
		if (action == 107)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(10993); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.1f);
		}
		if (action == 108)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(24978); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.1f);
		}
		if (action == 200)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(175); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.1f);
		}
		if (action == 201)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(21252); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.2f);
		}		
		if (action == 202)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(27571); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.4f);
		}                                                             
		if (action == 203)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(28641); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.2f);
		}
		if (action == 204)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(30721); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.4f);
		}
		if (action == 205)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(15945); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.2f);
		}
		if (action == 206)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(20023); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.3f);
		}
		if (action == 207)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(21443); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.3f);
		}
		if (action == 208)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(21576); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.7f);
		}
		if (action == 209)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(31165); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.4f);
		}
		if (action == 210)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(30790); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.8f);
		}
		if (action == 300)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(24949); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.8f);
		}
		if (action == 301)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(4527); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.8f);
		}
		if (action == 302)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(28213); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.9f);
		}
		if (action == 303)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(28127); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.8f);
		}
		if (action == 304)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(3597); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 305)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(30865); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.9f);
		}
		if (action == 306)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(28227); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.7f);
		}
		if (action == 307)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(30821); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.6f);
		}
		if (action == 350)
		{
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51551, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 351)
		{
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51542, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 352)
		{
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51541, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 353)
		{
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51537, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 354)
		{
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51538, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 355)
		{
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51550, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 356)
		{
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51549, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 357)
		{
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51539, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 358)
		{
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51540, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 359)
		{
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51534, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 360)
		{
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51520, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 361)
		{
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51536, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 362)
		{
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51535, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 363)
		{
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51543, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 364)
		{
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51544, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 365)
		{
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51547, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 366)
		{
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51548, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 367)
		{
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51546, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 368)
		{
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51545, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 600)
		{
			player->CLOSE_GOSSIP_MENU();
		}
		if (action == 500)
		{
			player->CLOSE_GOSSIP_MENU(); player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->RemoveAura(51551);
			player->RemoveAura(51542);
			player->RemoveAura(51541);
			player->RemoveAura(51537);
			player->RemoveAura(51538);
			player->RemoveAura(51550);
			player->RemoveAura(51549); 
			player->RemoveAura(51540);
			player->RemoveAura(51539);
			player->RemoveAura(51534);
			player->RemoveAura(51520);
			player->RemoveAura(51536);
			player->RemoveAura(51535);
			player->RemoveAura(51544);
			player->RemoveAura(51543);
			player->RemoveAura(51548);
			player->RemoveAura(51547);
			player->RemoveAura(51545);
			player->RemoveAura(51546);
		}
		if (action == 400)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(903); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 401)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(3027); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 402)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(368); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 403)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(598); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 404)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(2437); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 405)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(845); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 406)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(11317); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 407)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(10986); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 408)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(1536); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 409)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(7344); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 410)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(4418); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 411)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(5927); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 412)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(9409); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 413)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(1122); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 414)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(7247); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 415)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(11180); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 416)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(18859); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 417)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(11255); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 418)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(726); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 419)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(5562); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 420)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(9587); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 421)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(14503); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.8f);
		}
		if (action == 422)
		{
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(1405); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}

		return true;
	}       
};

void AddSC_Morph_NPC()
{
	new Morph_NPC();
}