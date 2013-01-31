
#include "ScriptPCH.h"
#include "WorldPacket.h"

#define Token		 44209
#define Reittier1	 28915 
#define Reittier2	 46171
#define Reittier3	 54860
#define Reittier4	 54069
#define Reittier5	 45801
#define Reittier6	 51954
#define Haustier1	 13583
#define Haustier2	 20371
#define Haustier3	 22114
#define Haustier4	 23713
#define Haustier5	 49646
#define FunItem1	 45178
#define FunItem2	 35223
#define FunItem3	 23162
#define FunItem4	 46780
#define FunItem5	 38301


class dt_shop : public CreatureScript
{
	public:
		dt_shop() : CreatureScript("dt_shop") {}

bool OnGossipHello(Player *player, Creature *creature)
{
	if (player->isInCombat())
	{
            creature->MonsterWhisper("Du bist in einen Kampf verwickelt. Komme wieder sobald du den Kampf beendet hast.", player->GetGUID());
            player->CLOSE_GOSSIP_MENU();
	}

	player->ADD_GOSSIP_ITEM(1, "Reittiere",				GOSSIP_SENDER_MAIN, 1);
	player->ADD_GOSSIP_ITEM(1, "Haustiere",				GOSSIP_SENDER_MAIN, 2);
	player->ADD_GOSSIP_ITEM(1, "Fun-Items",				GOSSIP_SENDER_MAIN, 3);
	player->ADD_GOSSIP_ITEM(0, "Aufwiedersehen",		GOSSIP_SENDER_MAIN, 500);
	player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
	return true;
}

bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 action)
{
	player->PlayerTalkClass->ClearMenus();
	if (GOSSIP_SENDER_MAIN)
	{
	switch (action)
	{
		case 1:
			player->ADD_GOSSIP_ITEM(1, "Dunkles Reittalbuk (100 Embleme)",					GOSSIP_SENDER_MAIN, 11);
			player->ADD_GOSSIP_ITEM(1, "Frostwyrm des w\303\274tenden Gladiators (400 Embleme)",	GOSSIP_SENDER_MAIN, 12);
			player->ADD_GOSSIP_ITEM(1, "X-53 Reiserakete (350 Embleme)",					GOSSIP_SENDER_MAIN, 13);
			player->ADD_GOSSIP_ITEM(1, "Flammender Hyppogryph (300 Embleme)",				GOSSIP_SENDER_MAIN, 14);
			player->ADD_GOSSIP_ITEM(1, "Eisenbeschlagener Protodrache (300 Embleme)",		GOSSIP_SENDER_MAIN, 15);
			player->ADD_GOSSIP_ITEM(1, "Blutgebadeter Frostwyrm (600 Embleme)",				GOSSIP_SENDER_MAIN, 16);
			player->ADD_GOSSIP_ITEM(1, "<<Zur\303\274ck",											GOSSIP_SENDER_MAIN, 499);
			player->ADD_GOSSIP_ITEM(0, "Aufwiedersehen",									GOSSIP_SENDER_MAIN, 500);
			player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;
		case 2:
			player->ADD_GOSSIP_ITEM(1, "Pandababy (50 Embleme)",							GOSSIP_SENDER_MAIN, 21);
			player->ADD_GOSSIP_ITEM(1, "Blauer Murloc (75 Embleme)",						GOSSIP_SENDER_MAIN, 22);
			player->ADD_GOSSIP_ITEM(1, "Rosa Murloc (75 Embleme)",							GOSSIP_SENDER_MAIN, 23);
			player->ADD_GOSSIP_ITEM(1, "Hippogryphenjunges (100 Embleme)",					GOSSIP_SENDER_MAIN, 24);
			player->ADD_GOSSIP_ITEM(1, "Kernhundwelpe (100 Embleme)",						GOSSIP_SENDER_MAIN, 25);
			player->ADD_GOSSIP_ITEM(1, "<<Zur\303\274ck",											GOSSIP_SENDER_MAIN, 499);
			player->ADD_GOSSIP_ITEM(0, "Aufwiedersehen",									GOSSIP_SENDER_MAIN, 500);
			player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;
		case 3:
			player->ADD_GOSSIP_ITEM(1, "Schaumstoffschwert (1 Emblem)",						GOSSIP_SENDER_MAIN, 31);
			player->ADD_GOSSIP_ITEM(1, "Papa Hummels traditionelles Leckerli (10 Embleme)",	GOSSIP_SENDER_MAIN, 32);
			player->ADD_GOSSIP_ITEM(1, "Forors Kiste der endlosen Wiederstandsausstattung (23 Embleme)", GOSSIP_SENDER_MAIN, 33);
			player->ADD_GOSSIP_ITEM(1, "Ogerpinata (30 Embleme)",							GOSSIP_SENDER_MAIN, 34);
			player->ADD_GOSSIP_ITEM(1, "D-I-S-C-O (75 Embleme)",							GOSSIP_SENDER_MAIN, 35);
			player->ADD_GOSSIP_ITEM(1, "<<Zur\303\274ck",											GOSSIP_SENDER_MAIN, 499);
			player->ADD_GOSSIP_ITEM(0, "Aufwiedersehen",									GOSSIP_SENDER_MAIN, 500);
			player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;
		case 500:
			player->CLOSE_GOSSIP_MENU();
			break;
	}
	}

	switch (action)
	{
	case 11:
		if (!player->HasItemCount(Token, 100))
		creature->MonsterWhisper("Du hast nicht genug Embleme von Darkthunder.", player->GetGUID());

		player->AddItem(Reittier1, 1);
		player->DestroyItemCount(Token, 100, true);
		break;

	case 12:
		if (!player->HasItemCount(Token, 400))
		creature->MonsterWhisper("Du hast nicht genug Embleme von Darkthunder.", player->GetGUID());

		player->AddItem(Reittier2, 1);
		player->DestroyItemCount(Token, 400, true);
		break;

	case 13:
		if (!player->HasItemCount(Token, 350))
		creature->MonsterWhisper("Du hast nicht genug Embleme von Darkthunder.", player->GetGUID());

		player->AddItem(Reittier3, 1);
		player->DestroyItemCount(Token, 350, true);
		break;

	case 14:
		if (!player->HasItemCount(Token, 300))
		creature->MonsterWhisper("Du hast nicht genug Embleme von Darkthunder.", player->GetGUID());

		player->AddItem(Reittier4, 1);
		player->DestroyItemCount(Token, 300, true);
		break;

	case 15:
		if (!player->HasItemCount(Token, 300))
		creature->MonsterWhisper("Du hast nicht genug Embleme von Darkthunder.", player->GetGUID());

		player->AddItem(Reittier5, 1);
		player->DestroyItemCount(Token, 300, true);
		break;

	case 16:
		if (!player->HasItemCount(Token, 600))
		creature->MonsterWhisper("Du hast nicht genug Embleme von Darkthunder.", player->GetGUID());

		player->AddItem(Reittier6, 1);
		player->DestroyItemCount(Token, 600, true);
		break;

	case 21:
		if (!player->HasItemCount(Token, 50))
		creature->MonsterWhisper("Du hast nicht genug Embleme von Darkthunder.", player->GetGUID());

		player->AddItem(Haustier1, 1);
		player->DestroyItemCount(Token, 50, true);
		break;

	case 22:
		if (!player->HasItemCount(Token, 75))
		creature->MonsterWhisper("Du hast nicht genug Embleme von Darkthunder.", player->GetGUID());

		player->AddItem(Haustier2, 1);
		player->DestroyItemCount(Token, 75, true);
		break;

	case 23:
		if (!player->HasItemCount(Token, 75))
		creature->MonsterWhisper("Du hast nicht genug Embleme von Darkthunder.", player->GetGUID());

		player->AddItem(Haustier3, 1);
		player->DestroyItemCount(Token, 75, true);
		break;

	case 24:
		if (!player->HasItemCount(Token, 100))
		creature->MonsterWhisper("Du hast nicht genug Embleme von Darkthunder.", player->GetGUID());

		player->AddItem(Haustier4, 1);
		player->DestroyItemCount(Token, 100, true);
		break;

	case 25:
		if (!player->HasItemCount(Token, 100))
		creature->MonsterWhisper("Du hast nicht genug Embleme von Darkthunder.", player->GetGUID());

		player->AddItem(Haustier5, 1);
		player->DestroyItemCount(Token, 100, true);
		break;

	case 31:
		if (!player->HasItemCount(Token, 1))
		creature->MonsterWhisper("Du hast nicht genug Embleme von Darkthunder.", player->GetGUID());

		player->AddItem(FunItem1, 1);
		player->DestroyItemCount(Token, 1, true);
		break;

	case 32:
		if (!player->HasItemCount(Token, 10))
		creature->MonsterWhisper("Du hast nicht genug Embleme von Darkthunder.", player->GetGUID());

		player->AddItem(FunItem2, 10);
		player->DestroyItemCount(Token, 10, true);
		break;

	case 33:
		if (!player->HasItemCount(Token, 23))
		creature->MonsterWhisper("Du hast nicht genug Embleme von Darkthunder.", player->GetGUID());

		player->AddItem(FunItem3, 1);
		player->DestroyItemCount(Token, 23, true);
		break;

	case 34:
		if (!player->HasItemCount(Token, 30))
		creature->MonsterWhisper("Du hast nicht genug Embleme von Darkthunder.", player->GetGUID());

		player->AddItem(FunItem4, 1);
		player->DestroyItemCount(Token, 30, true);
		break;

	case 35:
		if (!player->HasItemCount(Token, 75))
		creature->MonsterWhisper("Du hast nicht genug Embleme von Darkthunder.", player->GetGUID());

		player->AddItem(FunItem5, 1);
		player->DestroyItemCount(Token, 75, true);
		break;

	case 499:
		player->ADD_GOSSIP_ITEM(1, "Reittiere", GOSSIP_SENDER_MAIN, 1);
		player->ADD_GOSSIP_ITEM(1, "Haustiere", GOSSIP_SENDER_MAIN, 2);
		player->ADD_GOSSIP_ITEM(1, "Fun-Items", GOSSIP_SENDER_MAIN, 3);
		player->ADD_GOSSIP_ITEM(0, "Aufwiedersehen", GOSSIP_SENDER_MAIN, 500);
		player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		break;

	case 500:
		player->CLOSE_GOSSIP_MENU();
		break;

			return true;

}
}
};

void AddSC_dt_shop()
{
    new dt_shop();
}