#include "ScriptPCH.h"

/*
    npcflag = 128 (für vendor) und 1 (für gossip)
            also => 129 z.B.
    Hauptsache 128 und 1 sind inner Bitmask enthalten

    ScriptName = npc_dtvipvendor
*/
class npc_dtvipvendor : public CreatureScript
{
public:
    npc_dtvipvendor() : CreatureScript("npc_dtvipvendor") { }

    bool OnGossipHello(Player *pPlayer, Creature *pCreature)
    {
        if (pPlayer->GetSession()->GetSecurity() > SEC_PLAYER)
            pPlayer->GetSession()->SendListInventory(pCreature->GetGUID());
        else
            pCreature->MonsterWhisper("Verschwinde, $N! Mein Angebot ist sehr exklusiv.",pPlayer->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player *pPlayer, Creature *pCreature, uint32 sender, uint32 action)
    {
        // Nicht im Kampf
        if(!pPlayer->getAttackers().empty())
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->MonsterWhisper("Nicht im Kampf, $N!",pPlayer->GetGUID());
        }
        return true;
    }
};

void AddSC_npc_dtvipvendor()
{
    new npc_dtvipvendor;
}
