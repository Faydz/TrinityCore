#include "ScriptPCH.h"
#include "WorldPacket.h"

class npc_dtlostskills : public CreatureScript
{
public:
    npc_dtlostskills() : CreatureScript("npc_dtlostskills") { }

    bool OnGossipHello(Player *pPlayer, Creature *pCreature)
    {
        QueryResult result;
        uint32 PlayerLevel = pPlayer->getLevel();
        uint8 PlayerClass = pPlayer->getClass();
        uint8 PlayerTeam = (pPlayer->GetTeam() == ALLIANCE) ? 0 : 1;

        result = WorldDatabase.PQuery("SELECT * FROM `dt_lostskills` WHERE `enabled` = 1 AND level <= %u AND (`class` = 0 OR `class` = %u) AND (`team` = 2 OR `team` = %u)", PlayerLevel, PlayerClass, PlayerTeam);

        if (result)
        {
            do {
                Field *fields = result->Fetch();
                uint32 id = fields[0].GetUInt32();
                char const* name = fields[1].GetCString();
                uint32 spellid = fields[2].GetUInt32();

                if (!pPlayer->HasSpell(spellid))
                    pPlayer->ADD_GOSSIP_ITEM(5, name, GOSSIP_SENDER_MAIN, id);
            } while (result->NextRow());
        } else {
            pPlayer->ADD_GOSSIP_ITEM(10, "Datenbank-Fehler! Bitte einem Admin melden!", GOSSIP_SENDER_MAIN, 9999);
        }

        pPlayer->ADD_GOSSIP_ITEM(10, "Auf Wiedersehen!", GOSSIP_SENDER_MAIN, 9999);
        pPlayer->PlayerTalkClass->SendGossipMenu(2713,pCreature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player *pPlayer, Creature *pCreature, uint32 uiSender, uint32 uiAction)
    {
        QueryResult result;
        uint32 PlayerLevel = pPlayer->getLevel();
        uint8 PlayerClass = pPlayer->getClass();
        uint8 PlayerTeam = (pPlayer->GetTeam() == ALLIANCE) ? 0 : 1;

        result = WorldDatabase.PQuery("SELECT * FROM `dt_lostskills` WHERE `enabled` = 1 AND `id` = %u LIMIT 1", uiAction);
        if (result)
        {
            Field *fields = result->Fetch();
            uint32 spellid = fields[2].GetUInt32();
            uint32 skillid = fields[5].GetUInt32();
            uint16 skilllevel = fields[6].GetUInt32();
            uint32 repfactionid = fields[8].GetUInt32();
            uint32 reputation = fields[9].GetUInt32();
            uint32 costs = fields[10].GetUInt32();
            bool check_passed_skill = true;
            bool check_passed_rep = true;

            if (skillid > 0 && skilllevel > 0)
                if (!pPlayer->HasSkill(skillid) || pPlayer->GetSkillValue(skillid) < skilllevel)
                    check_passed_skill = false;

            if (repfactionid > 0 && reputation > 0)
                if (pPlayer->GetReputation(repfactionid) < reputation)
                    check_passed_rep = false;

            if (pPlayer->GetMoney() < costs)
            {
                pCreature->MonsterWhisper("Du hast leider nicht genug Geld!", pPlayer->GetGUID());
                pPlayer->CLOSE_GOSSIP_MENU();
                return true;
            } 
            else {
                if (check_passed_rep && check_passed_skill)
                {
                    pPlayer->ModifyMoney((costs*(-1)));
                    pPlayer->learnSpell(spellid,false);
                }
                else if (check_passed_rep && !check_passed_skill)
                    pCreature->MonsterWhisper("Deine Fertigkeiten reichen leider nicht aus!", pPlayer->GetGUID());
                else if (!check_passed_rep && check_passed_skill)
                    pCreature->MonsterWhisper("Du hast leider nicht genug Ruf!", pPlayer->GetGUID());
                else
                    pCreature->MonsterWhisper("Deine Fertigkeiten reichen nicht aus und du hast nicht genug Ruf!", pPlayer->GetGUID());
            }
        }
        
        pPlayer->CLOSE_GOSSIP_MENU();
        return true;
    }
};

void AddSC_npc_dtlostskills()
{
    new npc_dtlostskills;
}
