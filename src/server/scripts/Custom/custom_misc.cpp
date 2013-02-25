/* Author: Thainification | DarkThunder-WoW.net */
#include "ScriptPCH.h"

/*
	Vorraussetzungen:
	AchievementID1 = 1792, Och, ist das nicht s��?
	AchievementID2 = 1789, T�gliche M�hen 
	AchievementID3 = 1788, Schlechtes Vorbild
	AchievementID4 = 1790, Hoch lebe der K�nig, mein Kleiner
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
			if (player->HasAchieved(1792) && player->HasAchieved(1789) && player->HasAchieved(1788) && player->HasAchieved(1790) && player->HasAchieved(1791))
			{
				AchievementEntry const* Erfolg = sAchievementStore.LookupEntry(1786);
				player->CompletedAchievement(Erfolg);
				creature->MonsterWhisper("Du hast den Erfolg 'Eine harte Schule' erhalten!", player->GetGUID());
				player->CLOSE_GOSSIP_MENU();
			}
			
			else
			{
				creature->MonsterWhisper("Du erfllst leider nicht die Anforderungen!", player->GetGUID());
				player->CLOSE_GOSSIP_MENU();
			}
		}
		
		if (action == 500)
		{
			player->GetSession()->SendNotification("Bis zum nchsten mal!");
			player->CLOSE_GOSSIP_MENU();
		}
		
		return true;
	}
};

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
			winner->SetHealth(winner->GetMaxHealth());
            if ( winner->getPowerType() == POWER_MANA )
                 winner->SetPower(POWER_MANA, winner->GetMaxPower(POWER_MANA));
            looser->SetHealth(looser->GetMaxHealth());
            if ( looser->getPowerType() == POWER_MANA )
                 looser->SetPower(POWER_MANA, looser->GetMaxPower(POWER_MANA));
		}
	}
};



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
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(1060); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 102)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(134); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 103)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(856); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);

		}
		if (action == 104)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(441); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 105)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(10973); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 106)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(10728); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.7f);
		}
		if (action == 107)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(10993); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.1f);
		}
		if (action == 108)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(24978); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.1f);
		}
		if (action == 200)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(175); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.1f);
		}
		if (action == 201)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(21252); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.2f);
		}		
		if (action == 202)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(27571); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.4f);
		}                                                             
		if (action == 203)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(28641); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.2f);
		}
		if (action == 204)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(30721); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.4f);
		}
		if (action == 205)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(15945); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.2f);
		}
		if (action == 206)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(20023); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.3f);
		}
		if (action == 207)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(21443); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.3f);
		}
		if (action == 208)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(21576); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.7f);
		}
		if (action == 209)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(31165); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.4f);
		}
		if (action == 210)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(30790); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.8f);
		}
		if (action == 300)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(24949); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.8f);
		}
		if (action == 301)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(4527); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.8f);
		}
		if (action == 302)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(28213); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.9f);
		}
		if (action == 303)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(28127); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.8f);
		}
		if (action == 304)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(3597); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 305)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(30865); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.9f);
		}
		if (action == 306)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(28227); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.7f);
		}
		if (action == 307)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(30821); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.6f);
		}
		if (action == 350)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51551, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 351)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51542, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 352)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51541, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 353)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51537, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 354)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51538, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 355)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51550, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 356)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51549, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 357)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51539, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 358)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51540, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 359)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51534, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 360)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51520, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 361)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51536, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 362)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51535, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 363)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51543, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 364)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51544, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 365)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51547, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 366)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51548, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 367)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->AddAura(51546, player); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 368)
		{
			player->DeMorph(); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
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
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(903); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 401)
		{
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(3027); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 402)
		{
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(368); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 403)
		{
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(598); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 404)
		{
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(2437); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 405)
		{
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(845); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 406)
		{
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(11317); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 407)
		{
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(10986); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 408)
		{
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(1536); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 409)
		{
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(7344); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 410)
		{
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(4418); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 411)
		{
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(5927); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 412)
		{
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(9409); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 413)
		{
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(1122); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 414)
		{
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(7247); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 415)
		{
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(11180); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 416)
		{
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(18859); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 417)
		{
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(11255); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 418)
		{
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(726); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 419)
		{
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(5562); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 420)
		{
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(9587); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}
		if (action == 421)
		{
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(14503); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.8f);
		}
		if (action == 422)
		{
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
			player->CLOSE_GOSSIP_MENU(); player->SetDisplayId(1405); player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
		}

		return true;
	}       
};

class npc_startup : public CreatureScript
{
public: npc_startup() : CreatureScript("npc_startup") { }

		bool OnGossipHello(Player* player, Creature* creature)
		{
		if (player->isInCombat())
		{
			creature->MonsterWhisper("Du bist im Kampf. Komme wieder sobald du den Kampf beendet hast.", player->GetGUID());
			player->CLOSE_GOSSIP_MENU();
		}

		if (player->getClass()==1)		// Krieger
		{
			player->ADD_GOSSIP_ITEM(9, "Schaden", GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM(9, "Tank", GOSSIP_SENDER_MAIN, 2);
			player->ADD_GOSSIP_ITEM(0, "Aufwiedersehen", GOSSIP_SENDER_MAIN, 50);
		}

		if (player->getClass()==2)		// Paladin
		{
			player->ADD_GOSSIP_ITEM(9, "Schaden", GOSSIP_SENDER_MAIN, 3);
			player->ADD_GOSSIP_ITEM(9, "Tank", GOSSIP_SENDER_MAIN, 4);
			player->ADD_GOSSIP_ITEM(9, "Heilung", GOSSIP_SENDER_MAIN, 5);
			player->ADD_GOSSIP_ITEM(0, "Aufwiedersehen", GOSSIP_SENDER_MAIN, 50);
		}

		if (player->getClass()==3)		//J�ger
		{
			player->ADD_GOSSIP_ITEM(9, "Schaden", GOSSIP_SENDER_MAIN, 6);
			player->ADD_GOSSIP_ITEM(0, "Aufwiedersehen", GOSSIP_SENDER_MAIN, 50);
		}

		if (player->getClass()==4)		// Schurke
		{
			player->ADD_GOSSIP_ITEM(9, "Schaden", GOSSIP_SENDER_MAIN, 7);
			player->ADD_GOSSIP_ITEM(0, "Aufwiedersehen", GOSSIP_SENDER_MAIN, 50);
		}

		if (player->getClass()==5)		// Priester
		{
			player->ADD_GOSSIP_ITEM(9, "Schaden", GOSSIP_SENDER_MAIN, 8);
			player->ADD_GOSSIP_ITEM(9, "Heilung", GOSSIP_SENDER_MAIN, 9);
			player->ADD_GOSSIP_ITEM(0, "Aufwiedersehen", GOSSIP_SENDER_MAIN, 50);
		}

		if (player->getClass()==6)		// Todesritter
		{
			player->ADD_GOSSIP_ITEM(9, "Schaden", GOSSIP_SENDER_MAIN, 10);
			player->ADD_GOSSIP_ITEM(9, "Tank", GOSSIP_SENDER_MAIN, 11);
			player->ADD_GOSSIP_ITEM(0, "Aufwiedersehen", GOSSIP_SENDER_MAIN, 50);
		}

		if (player->getClass()==7)		// Schamane
		{
			player->ADD_GOSSIP_ITEM(9, "Schaden (Elementar)", GOSSIP_SENDER_MAIN, 12);
			player->ADD_GOSSIP_ITEM(9, "Schaden (Verst\303\244rkung", GOSSIP_SENDER_MAIN, 13);
			player->ADD_GOSSIP_ITEM(9, "Heilung", GOSSIP_SENDER_MAIN, 14);
			player->ADD_GOSSIP_ITEM(0, "Aufwiedersehen", GOSSIP_SENDER_MAIN, 50);
		}

		if (player->getClass()==8)		// Magier
		{
			player->ADD_GOSSIP_ITEM(9, "Schaden", GOSSIP_SENDER_MAIN, 15);
			player->ADD_GOSSIP_ITEM(0, "Aufwiedersehen", GOSSIP_SENDER_MAIN, 50);
		}

		if (player->getClass()==9)		// Hexenmeister
		{
			player->ADD_GOSSIP_ITEM(9, "Schaden", GOSSIP_SENDER_MAIN, 16);
			player->ADD_GOSSIP_ITEM(0, "Aufwiedersehen", GOSSIP_SENDER_MAIN, 50);
		}

		if (player->getClass()==11)		//Druide
		{
			player->ADD_GOSSIP_ITEM(9, "Schaden (Gleichgewicht)", GOSSIP_SENDER_MAIN, 17);
			player->ADD_GOSSIP_ITEM(9, "Schaden (Wilder Kampf)", GOSSIP_SENDER_MAIN, 18);
			player->ADD_GOSSIP_ITEM(9, "Heilung", GOSSIP_SENDER_MAIN, 19);
			player->ADD_GOSSIP_ITEM(9, "Tank", GOSSIP_SENDER_MAIN, 20);
			player->ADD_GOSSIP_ITEM(0, "Aufwiedersehen", GOSSIP_SENDER_MAIN, 50);
		}
		player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		return true;
}

		bool OnGossipSelect(Player * player, Creature * creature, uint32 /*sender*/, uint32 action)
		{
			switch (action)
			{
				case 1:								// Krieger DD
					if (player->GetMoney()<6000000)
					{
						creature->MonsterWhisper("Das kannst du dir leider nicht leisten.", player->GetGUID());
					}

					break;
				case 2:								// Krieger Tank
					if (player->GetMoney()<6000000)
					{
						creature->MonsterWhisper("Das kannst du dir leider nicht leisten.", player->GetGUID());
					}
					break;
				case 3:								// Pala DD
					if (player->GetMoney()<6000000)
					{
						creature->MonsterWhisper("Das kannst du dir leider nicht leisten.", player->GetGUID());
					}
					break;
				case 4:								// Pala Tank
					if (player->GetMoney()<6000000)
					{
						creature->MonsterWhisper("Das kannst du dir leider nicht leisten.", player->GetGUID());
					}
					else
					{
						player->ModifyMoney(-6000000);
						player->AddItem(40583, 1);
						player->AddItem(40584, 1);
						player->AddItem(40580, 1);
						player->AddItem(40579, 1);
						player->AddItem(40581, 1);
						player->AddItem(40400, 1);
						player->AddItem(40345, 1);
						player->AddItem(39717, 1);
						player->AddItem(39759, 1);
						player->AddItem(39764, 1);
						player->AddItem(40107, 1);
						player->AddItem(40069, 1);
						player->AddItem(40252, 1);
						player->AddItem(40257, 1);
						player->AddItem(40372, 1);
						player->AddItem(40337, 1);
					}
					break;
				case 5:								// Pala Heal
					if (player->GetMoney()<6000000)
					{
						creature->MonsterWhisper("Das kannst du dir leider nicht leisten.", player->GetGUID());
					}
					else
					{
						player->ModifyMoney(-6000000);
						player->AddItem(40569, 1);
						player->AddItem(40570, 1);
						player->AddItem(40571, 1);
						player->AddItem(40573, 1);
						player->AddItem(40401, 1);
						player->AddItem(40395, 1);
						player->AddItem(39425, 1);
						player->AddItem(40187, 1);
						player->AddItem(40241, 1);
						player->AddItem(40268, 1);
						player->AddItem(40274, 1);
						player->AddItem(40375, 1);
						player->AddItem(40374, 1);
						player->AddItem(40258, 1);
						player->AddItem(40108, 1);
						player->AddItem(40382, 1);
					}
					break;
				case 6:								// Hunter
					if (player->GetMoney()<6000000)
					{
						creature->MonsterWhisper("Das kannst du dir leider nicht leisten.", player->GetGUID());
					}
					break;
				case 7:								// Schurke
					if (player->GetMoney()<6000000)
					{
						creature->MonsterWhisper("Das kannst du dir leider nicht leisten.", player->GetGUID());
					}
					else
					{
						player->ModifyMoney(-6000000);
						player->AddItem(40495, 1);
						player->AddItem(40496, 1);
						player->AddItem(40499, 1);
						player->AddItem(40500, 1);
						player->AddItem(40502, 1);
						player->AddItem(40369, 1);
						player->AddItem(40250, 1);
						player->AddItem(40186, 1);
						player->AddItem(40205, 1);
						player->AddItem(40243, 1);
						player->AddItem(40074, 1);
						player->AddItem(40075, 1);
						player->AddItem(40256, 1);
						player->AddItem(40371, 1);
						player->AddItem(40383, 1);
						player->AddItem(40239, 1);
						player->AddItem(40385, 1);
					}
					break;
				case 8:								// Priester Schaden
					if (player->GetMoney()<6000000)
					{
						creature->MonsterWhisper("Das kannst du dir leider nicht leisten.", player->GetGUID());
					}
					break;
				case 9:								// Priester Heal
					if (player->GetMoney()<6000000)
					{
						creature->MonsterWhisper("Das kannst du dir leider nicht leisten.", player->GetGUID());
					}
					break;
				case 11:							// DK Schaden
					if (player->GetMoney()<6000000)
					{
						creature->MonsterWhisper("Das kannst du dir leider nicht leisten.", player->GetGUID());
					}
					break;
					case 12:							// DK Tank
					if (player->GetMoney()<6000000)
					{
						creature->MonsterWhisper("Das kannst du dir leider nicht leisten.", player->GetGUID());
					}
					break;
					case 13:							// Schami Ele
					if (player->GetMoney()<6000000)
					{
						creature->MonsterWhisper("Das kannst du dir leider nicht leisten.", player->GetGUID());
					}
					break;
					case 14:							// Schami VS
					if (player->GetMoney()<6000000)
					{
						creature->MonsterWhisper("Das kannst du dir leider nicht leisten.", player->GetGUID());
					}
					break;
					case 15:							// Schami Heal
					if (player->GetMoney()<6000000)
					{
						creature->MonsterWhisper("Das kannst du dir leider nicht leisten.", player->GetGUID());
					}
					break;
					case 16:							// Mage
					if (player->GetMoney()<6000000)
					{
						creature->MonsterWhisper("Das kannst du dir leider nicht leisten.", player->GetGUID());
					}
					break;
					case 17:							// Hexer
					if (player->GetMoney()<6000000)
					{
						creature->MonsterWhisper("Das kannst du dir leider nicht leisten.", player->GetGUID());
					}
					else
					{
						player->ModifyMoney(-6000000);
						player->AddItem(40421, 1);
						player->AddItem(40374, 1);
						player->AddItem(40424, 1);
						player->AddItem(40251, 1);
						player->AddItem(40423, 1);
						player->AddItem(40325, 1);
						player->AddItem(40420, 1);
						player->AddItem(40301, 1);
						player->AddItem(40422, 1);
						player->AddItem(40246, 1);
						player->AddItem(40375, 1);
						player->AddItem(40108, 1);
						player->AddItem(40373, 1);
						player->AddItem(40255, 1);
						player->AddItem(40336, 1);
						player->AddItem(40273, 1);
						player->AddItem(39712, 1);
					}
					break;
					case 18:							// Dudu Moonkin
					if (player->GetMoney()<6000000)
					{
						creature->MonsterWhisper("Das kannst du dir leider nicht leisten.", player->GetGUID());
					}
					break;
					case 19:							// Dudu Feral DD
					if (player->GetMoney()<6000000)
					{
						creature->MonsterWhisper("Das kannst du dir leider nicht leisten.", player->GetGUID());
					}
					break;
					case 20:							// Dudu Feral Tank
					if (player->GetMoney()<6000000)
					{
						creature->MonsterWhisper("Das kannst du dir leider nicht leisten.", player->GetGUID());
					}
					break;
				case 50:
					player->CLOSE_GOSSIP_MENU();
					break;
			}
			return true;
		}

};

#include <cstring>
#define t9_token			 44209
#define nonset_token		 44209
#define racechange_token	 44209
#define factionchange_token	 44209

class npc_donation : public CreatureScript
{
public: npc_donation() : CreatureScript("npc_donation") { }

		bool OnGossipHello(Player* player, Creature* creature)
			{
				if (player->isInCombat())
					{
						creature->MonsterWhisper("Du bist im Kampf. Komme wieder sobald du den Kampf beendet hast.", player->GetGUID());
						player->CLOSE_GOSSIP_MENU();
					}

				player->ADD_GOSSIP_ITEM(0, "Fraktionswechsel", GOSSIP_SENDER_MAIN, 1);
				player->ADD_GOSSIP_ITEM(0, "Rassenwechsel", GOSSIP_SENDER_MAIN, 2);
				player->ADD_GOSSIP_ITEM(0, "Tier 9 Set", GOSSIP_SENDER_MAIN, 3);
				player->ADD_GOSSIP_ITEM_EXTENDED(0, "ItemID eingeben (maximal 258er Gegenstandsstufe)", GOSSIP_SENDER_MAIN, 4, "", 0, true);
				player->ADD_GOSSIP_ITEM(0, "Aufwiedersehen...", GOSSIP_SENDER_MAIN, 50);
				player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				return true;
			}

		bool OnGossipSelect(Player * player, Creature * creature, uint32 /*sender*/, uint32 action)
		{
			switch(action)
			{
			case 1:
				if (player->HasItemCount(factionchange_token, 1))
				{

				}
				else
				{
					creature->MonsterWhisper("Du hast nicht die ben\303\266tigten Gegenst\303\244nde.", player->GetGUID());
				}
				break;
			case 2:
				break;
			case 3:
				break;
			case 50:
				player->CLOSE_GOSSIP_MENU();
				break;
			}
			return true;
		}

		bool OnGossipSelectCode(Player *player, Creature *creature, uint32 sender, uint32 action, const char *ent)
		{
			switch (action)
			{
			case 4:
				if (player->HasItemCount(nonset_token, 1))
				{
					QueryResult result;
					result = WorldDatabase.PQuery("SELECT `entry` FROM `item_template`  WHERE `entry` = 'ent'", ent);
					
					if (result)
					{
						QueryResult result2;
						result2 = WorldDatabase.PQuery("SELECT `ItemLevel` FROM `item_template` WHERE `entry`='result'", result);

						if (result2 > 258)
						{
							creature->MonsterWhisper("Dieser Gegenstand hat eine zu hohe Gegenstandsstufe.", player->GetGUID());
						}

						else
						{
							player->AddItem(result, 1);
						}
					}
					else
					{
						creature->MonsterWhisper("Ung�ltige Item ID.", player->GetGUID());
					}
				}

				else
				{
					creature->MonsterWhisper("Du hast nicht die ben\303\266tigten Gegenst\303\244nde.", player->GetGUID());
				}
				break;
			}
			return false;
		}
};

#include "ScriptPch.h"
#include <cstring>
#include <stdio.h>
#include <time.h>

#define OFFSET_THEME 10000 

int GetLastThemeTime()
{
  	QueryResult result;
	  result = WorldDatabase.PQuery("SELECT `time` FROM `gurubashi_lastspawned`");

	  if (result)
	  {
	   Field *fields = result->Fetch();
	   return fields[0].GetInt32();
	  }
	  else 
		  return 0;

}

void GossipObjects(Player *player, Creature *m_creature)
{
   if (GetLastThemeTime() + 600 <= time (NULL))
    {
        QueryResult result;
    	  result = WorldDatabase.PQuery("SELECT `id`, `name` FROM `gurubashi_themes`");
        if (result)
        {
        	do
          {
          	Field *fields = result->Fetch();
          	player->ADD_GOSSIP_ITEM(4, fields[1].GetString(), GOSSIP_SENDER_MAIN, OFFSET_THEME + fields[0].GetInt32());
          }
          while (result->NextRow());
        }
    }
    else
    {
        char msg[100];
      	int time2 = GetLastThemeTime() + 600 - time (NULL);
      	if (time2 < 60)
          sprintf(msg, "N\303\244chster Wechsel in unter einer Minute m\303\266glich.");
        else
          sprintf(msg, "N\303\244chster Wechsel in %u Minuten m\303\266glich.", time2 / 60);		  
          player->ADD_GOSSIP_ITEM(0, msg, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    }
    player->ADD_GOSSIP_ITEM(0, "Aufwiedersehen...", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    player->SEND_GOSSIP_MENU(1,m_creature->GetGUID());
}


class Theme_NPC : public CreatureScript
{
	public:
		Theme_NPC() : CreatureScript("Theme_NPC") {}
		
		bool OnGossipHello(Player * pPlayer, Creature * pCreature)
        {
			GossipObjects(pPlayer, pCreature);
			return true;
		}
		
		bool OnGossipSelect(Player *player, Creature * m_creature, uint32 sender, uint32 action)
		{
			if (action > OFFSET_THEME)
			{
				QueryResult result;
				result = WorldDatabase.PQuery("DELETE FROM `gurubashi_lastspawned`");
				result = WorldDatabase.PQuery("INSERT INTO `gurubashi_lastspawned` VALUES (%u)", time (NULL));
				result = WorldDatabase.PQuery("SELECT `x`, `y`, `z`, `o`, `entry` FROM `gurubashi_spawns` WHERE `theme` = %u", action - OFFSET_THEME);
				if (result)
				{
					m_creature->MonsterSay("Gameobjekte werden gespawnt...", LANG_UNIVERSAL, player->GetGUID());
					do
					{
						Field *fields = result->Fetch();
						m_creature->SummonGameObject(fields[4].GetInt32(), fields[0].GetFloat(), fields[1].GetFloat(), fields[2].GetFloat(), fields[3].GetFloat(), 0, 0, 0, 0, 600); 
					}
					while (result->NextRow());
				}
				else
				{
					m_creature->MonsterSay("Keine Gameobjekte gefunden.", LANG_UNIVERSAL, player->GetGUID());
				}
				player->PlayerTalkClass->SendCloseGossip();
			}
			else
			{
				switch (action)
				{
				case GOSSIP_ACTION_INFO_DEF + 1:
					player->PlayerTalkClass->SendCloseGossip();
					break;
				case GOSSIP_ACTION_INFO_DEF + 2:
					GossipObjects(player, m_creature);
					break;
				}
			}
			return true;
		}
};

void AddSC_custom_misc()
{
	new AV_NPC();
	new DuelCD_Reset();
	new Morph_NPC();
	new npc_startup();
	new npc_donation();
	new Theme_NPC();
}
