#include "ScriptPCH.h"
#include "WorldPacket.h"

class npc_dtporter : public CreatureScript
{
public:
    npc_dtporter() : CreatureScript("npc_dtporter") { }

    bool OnGossipHello(Player *pPlayer, Creature *pCreature)
    {
        uint8 PlayerTeam = (pPlayer->GetTeam() == ALLIANCE) ? 0 : 1;
        uint32 NPCLevel = pCreature->getLevel(); //80 = horde & allianz, 81 = horde, 82 = allianz
        if ((NPCLevel == 81 && PlayerTeam != 1) || (NPCLevel == 82 && PlayerTeam != 0))
        {
            pCreature->MonsterWhisper("Verschwinde! Ich biete meine Dienste keinem Feind an!", pPlayer->GetGUID());
            return true;
        }
        /*
        QueryResult result;
        uint32 PlayerLevel = pPlayer->getLevel();
        uint8 PlayerKlasse = pPlayer->getClass();
        std::string kosten = (PlayerLevel <= 70) ? (PlayerLevel) + " Silber" : (PlayerLevel*10) + " Silber";
        
        result = WorldDatabase.PQuery("SELECT * FROM `dt_teleport` WHERE `enabled` = 1 AND `level` <= %i", PlayerLevel);

        if(result)
        {
            pPlayer->ADD_GOSSIP_ITEM( 10, "Teleportkosten:", GOSSIP_SENDER_MAIN, 9999);
            pPlayer->ADD_GOSSIP_ITEM( 10, "Level 1-70 -> Level*1 Silber", GOSSIP_SENDER_MAIN, 9999);
            pPlayer->ADD_GOSSIP_ITEM( 10, "Level 71-80 -> Level*10 Silber", GOSSIP_SENDER_MAIN, 9999);
            pPlayer->ADD_GOSSIP_ITEM( 10, " ", GOSSIP_SENDER_MAIN, 9999);

            do {
                Field *fields = result->Fetch();
                uint32 id = fields[0].GetUInt32();
                char const* text = fields[1].GetCString();
                uint8 team = fields[2].GetUInt8();
                uint8 klasse = fields[3].GetUInt8();

                if (klasse == 0 || klasse == PlayerKlasse)
                    if (team == 2 || team == PlayerTeam)
                        pPlayer->ADD_GOSSIP_ITEM(5, text, GOSSIP_SENDER_MAIN, id);
            } while (result->NextRow());
        } else {
            pPlayer->ADD_GOSSIP_ITEM(10, "Datenbank-Fehler! Bitte einem Admin melden!", GOSSIP_SENDER_MAIN, 9999);
        }*/

        uint32 PlayerLevel = pPlayer->getLevel();
        uint8 PlayerKlasse = pPlayer->getClass();
        std::string kosten = (PlayerLevel <= 70) ? (PlayerLevel) + " Silber" : (PlayerLevel*10) + " Silber";

		pPlayer->ADD_GOSSIP_ITEM( 10, "Teleportkosten:", GOSSIP_SENDER_MAIN, 6111);
 		pPlayer->ADD_GOSSIP_ITEM( 10, "Level 1-70 -> Level*1 Silber", GOSSIP_SENDER_MAIN, 6111);
   		pPlayer->ADD_GOSSIP_ITEM( 10, "Level 71-80 -> Level*10 Silber", GOSSIP_SENDER_MAIN, 6111);
		pPlayer->ADD_GOSSIP_ITEM( 10, " ", GOSSIP_SENDER_MAIN, 6111);

        if (ALLIANCE == pPlayer->GetTeam())
        {
		    pPlayer->ADD_GOSSIP_ITEM( 5, "Teleport nach Sturmwind", GOSSIP_SENDER_MAIN, 6201);
		    pPlayer->ADD_GOSSIP_ITEM( 5, "Teleport nach Eisenschmiede", GOSSIP_SENDER_MAIN, 6202);
		    pPlayer->ADD_GOSSIP_ITEM( 5, "Teleport nach Darnassus", GOSSIP_SENDER_MAIN, 6203);
		    pPlayer->ADD_GOSSIP_ITEM( 5, "Teleport zur Exodar", GOSSIP_SENDER_MAIN, 6204);
        } else
        {
		    pPlayer->ADD_GOSSIP_ITEM( 5, "Teleport nach Orgrimmar", GOSSIP_SENDER_MAIN, 6211);
		    pPlayer->ADD_GOSSIP_ITEM( 5, "Teleport nach Donnerfels", GOSSIP_SENDER_MAIN, 6212);
		    pPlayer->ADD_GOSSIP_ITEM( 5, "Teleport nach Unterstadt", GOSSIP_SENDER_MAIN, 6213);
		    pPlayer->ADD_GOSSIP_ITEM( 5, "Teleport nach Silbermond", GOSSIP_SENDER_MAIN, 6214);
        }
	    if(pPlayer->getClass()==6) //todesritter
	    {
		    pPlayer->ADD_GOSSIP_ITEM( 5, "Teleport zur Todesbresche", GOSSIP_SENDER_MAIN, 6206);
		    pPlayer->ADD_GOSSIP_ITEM( 5, "Teleport zur Acherus", GOSSIP_SENDER_MAIN, 6207);
	    }
	    if(PlayerLevel>=30)
		    pPlayer->ADD_GOSSIP_ITEM( 5, "Teleport zur Arena der Gurubashi", GOSSIP_SENDER_MAIN, 6200);
	    if(PlayerLevel>=58)
		    pPlayer->ADD_GOSSIP_ITEM( 5, "Teleport nach Shattrath", GOSSIP_SENDER_MAIN, 6208);
	    if(PlayerLevel>=65)
		    pPlayer->ADD_GOSSIP_ITEM( 5, "Teleport zur Insel von Quel'Danas", GOSSIP_SENDER_MAIN, 6209);
	    if(PlayerLevel>=70)
		    pPlayer->ADD_GOSSIP_ITEM( 5, "Teleport nach Dalaran", GOSSIP_SENDER_MAIN, 6210);

        if (ALLIANCE == pPlayer->GetTeam())
		    pPlayer->ADD_GOSSIP_ITEM( 5, "Teleport zum Allianz Playertreff", GOSSIP_SENDER_MAIN, 6402);
        else
		    pPlayer->ADD_GOSSIP_ITEM( 5, "Teleport zum Horde Playertreff", GOSSIP_SENDER_MAIN, 6401);

        pPlayer->ADD_GOSSIP_ITEM( 5, "Teleport zum Rennen (PvP Verbot)", GOSSIP_SENDER_MAIN, 6550);

        pPlayer->PlayerTalkClass->SendGossipMenu(2713,pCreature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player *pPlayer, Creature *pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
        /*uint8 PlayerLevel = pPlayer->getLevel();
        uint32 kosten = (PlayerLevel <= 70) ? (PlayerLevel*100) : (PlayerLevel*1000);

        if (pPlayer->GetMoney() < kosten)
        {
            pCreature->MonsterWhisper("Das kannst du dir leider nicht leisten!", pPlayer->GetGUID());
            return false;
        }

        QueryResult result;
        result = WorldDatabase.PQuery("SELECT `x`, `y`, `z`, `o`, `map` FROM `dt_teleport` WHERE `enabled` = 1 AND `id` = %i LIMIT 1", uiAction);

        if (result)
        {
            Field *fields = result->Fetch();
            float x = fields[0].GetFloat();
            float y = fields[1].GetFloat();
            float z = fields[2].GetFloat();
            float o = fields[3].GetFloat();
            uint32 map = fields[4].GetUInt32();

            pPlayer->ModifyMoney((kosten*(-1)));

            char* temp = "";
            switch (urand(1,5)) {
                case 1: temp = "Eine angenehme Reise!"; break;
                case 2: temp = "Und wieder ein zufriedener Kunde.."; break;
                case 3: temp = "Welch wundervolle Wahl"; break;
                case 4: temp = "Schneller als der Wind!"; break;
                case 5: temp = "Empfehlen Sie uns weiter!"; break;
            }
            char const* text = temp;

            pCreature->MonsterWhisper(text, pPlayer->GetGUID());
            pPlayer->TeleportTo(map, x, y, z, o);
        }*/

        switch (uiAction) {
		    case 6200: custom_porter_port(0, -13234.1f, 217.387f, 31.6759f, 1.06815f, pPlayer, pCreature); break; //guru
		    case 6201: custom_porter_port(0, -8908.96f, 556.3f, 93.5345f, 0.73f, pPlayer, pCreature); break; //stormwind
		    case 6202: custom_porter_port(0, -4821.6f, -1155.58f, 502.2345f, 3.33532f, pPlayer, pCreature); break; //eisenschmiede
		    case 6203: custom_porter_port(1, 9947.53f, 2604.15f, 1316.19f, 4.223f, pPlayer, pCreature); break; //darnassus
		    case 6204: custom_porter_port(530, -4054.75f, -11793.4f, 11.1139f, 1.51503f, pPlayer, pCreature); break; //exodar
		    case 6205: custom_porter_port(1, 45.951f, 1218.27f, 146.713f, 0.063138f, pPlayer, pCreature); break; //pt ally
		    case 6206: custom_porter_port(609, 2362.29f, -5693.76f, 153.922f, 3.77816f, pPlayer, pCreature); break; //todesbresche
		    case 6207: custom_porter_port(609, 2348.74f, -5694.94f, 384.088f, 3.90954f, pPlayer, pCreature); break; //acherus
		    case 6208: custom_porter_port(530, -1879.5f, 5409.46f, -12.4277f, 1.0332f, pPlayer, pCreature); break; //shattrath
		    case 6209: custom_porter_port(530, 13000.2f, -6907.51f, 12.0f, 1.06815f, pPlayer, pCreature); break; //queldanas
		    case 6210: custom_porter_port(571, 5814.2f, 446.337f, 659.201f, 1.41145f, pPlayer, pCreature); break; //dalaran
		    case 6211: custom_porter_port(1, 1677.91f, -4314.79f, 62.35f, 2.66969f, pPlayer, pCreature); break; //orgrimmar
		    case 6212: custom_porter_port(1, -1197.18f, 29.2706f, 179.755f, 2.9666f, pPlayer, pCreature); break; //donnerfels
		    case 6213: custom_porter_port(0, 1568.48f, 268.52f, -42.1384f, 1.69719f, pPlayer, pCreature); break; //unterstadt
		    case 6214: custom_porter_port(530, 9373.08f, -7166.07f, 11.4763f, 5.38653f, pPlayer, pCreature); break; //silbermond
		    case 6215: custom_porter_port(1, -1790.17f, 3055.44f, 9.35831f, 1.06815f, pPlayer, pCreature); break; //pt horde
		    case 6216: custom_porter_port(1, -11846.4f, -4756.91f, 6.25831f, 0.305114f, pPlayer, pCreature); break; //pt highrate

            case 6401: custom_porter_port(37, -30.2515f, 952.13f, 348.4f, 5.49992f, pPlayer, pCreature); break; //new hordept
            case 6402: custom_porter_port(37, 1100.61f, 298.099f, 338.7f, 3.11388f, pPlayer, pCreature); break; //new allypt

            case 6550: custom_porter_port(0, -7823.80f, -477.402f, 170.8f, 3.031973f, pPlayer, pCreature); break; //dt-renngebiet
	    }

        pPlayer->CLOSE_GOSSIP_MENU();
        return true;
    }
    void custom_porter_port(uint32 a, float b, float c, float d, float e, Player* pPlayer, Creature* pCreature)
    {
        uint8 PlayerLevel = pPlayer->getLevel();
        uint32 kosten = (PlayerLevel <= 70) ? (PlayerLevel*100) : (PlayerLevel*1000);

        if (pPlayer->GetMoney() < kosten)
        {
            pCreature->MonsterWhisper("Das kannst du dir leider nicht leisten!", pPlayer->GetGUID());
            return;
        }

	    pPlayer->ModifyMoney((kosten*(-1)));

        char* temp = "";
        switch (urand(1,5)) {
            case 1: temp = "Eine angenehme Reise!"; break;
            case 2: temp = "Und wieder ein zufriedener Kunde.."; break;
            case 3: temp = "Welch wundervolle Wahl"; break;
            case 4: temp = "Schneller als der Wind!"; break;
            case 5: temp = "Empfehlen Sie uns weiter!"; break;
        }
        char const* text = temp;

        pCreature->MonsterWhisper(text, pPlayer->GetGUID());

        pPlayer->TeleportTo(a,b,c,d,e);
        return;
    }
};

void AddSC_npc_dtporter()
{
    new npc_dtporter;
}