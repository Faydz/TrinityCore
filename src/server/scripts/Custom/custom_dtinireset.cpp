#include "ScriptPCH.h"
#include "WorldPacket.h"

#define DTIniReset_Item 100001 //eventmarke

class npc_dtinireset : public CreatureScript
{
public:
    npc_dtinireset() : CreatureScript("npc_dtinireset") { }

    uint32 npc_dtinireset_do(Player *pPlayer)
    {
        Player* pl = pPlayer->GetSession()->GetPlayer();
        uint32 counter = 0;
        for (uint8 i = 0; i < MAX_DIFFICULTY; ++i)
        {
            Player::BoundInstancesMap &binds = pl->GetBoundInstances(Difficulty(i));
            for (Player::BoundInstancesMap::iterator itr = binds.begin(); itr != binds.end();)
            {
                if (itr->first != pl->GetMapId())
                {
                    pl->UnbindInstance(itr, Difficulty(i));
                    counter++;
                }
                else
                    ++itr;
            }
        }

        return counter;
    }
    /*
                        InstanceSave *save = itr->second.save;
                        std::string timeleft = GetTimeString(save->GetResetTime() - time(NULL));
                        PSendSysMessage("unbinding map: %d inst: %d perm: %s diff: %d canReset: %s TTR: %s", itr->first, save->GetInstanceId(), itr->second.perm ? "yes" : "no",  save->GetDifficulty(), save->CanReset() ? "yes" : "no", timeleft.c_str());
                        player->UnbindInstance(itr, Difficulty(i));
                        counter++;
    */
    bool OnGossipHello(Player *pPlayer, Creature *pCreature)
    {
        pPlayer->ADD_GOSSIP_ITEM(5, "Instanzenreset (1 Eventmarke)", GOSSIP_SENDER_MAIN, 6002);

        pPlayer->ADD_GOSSIP_ITEM(10, "Auf Wiedersehen!", GOSSIP_SENDER_MAIN, 9999);
        pPlayer->PlayerTalkClass->SendGossipMenu(2713,pCreature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player *pPlayer, Creature *pCreature, uint32 uiSender, uint32 uiAction)
    {
        if (uiAction != 6002)
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            return true;
        }

        char* text = "Du hast leider nicht genug Marken.";

        if (!pPlayer->HasItemCount(DTIniReset_Item,1,false))
        {
            pCreature->MonsterWhisper(text,pPlayer->GetGUID());
            pPlayer->CLOSE_GOSSIP_MENU();
            return true;
        }

        uint32 counter = this->npc_dtinireset_do(pPlayer);

        if (!counter)
            return true;

        if (counter == 0)
            text = "Ich konnte keine Instanzen finden..";
        else
        {
            pPlayer->DestroyItemCount(DTIniReset_Item,1,true,false);
            sprintf(text, "Es wurden %u Instanzen resetted. Beehren Sie uns bald wieder!", counter);
        }

        pCreature->MonsterWhisper(text,pPlayer->GetGUID());
        pPlayer->CLOSE_GOSSIP_MENU();
        return true;
    }
};

void AddSC_npc_dtinireset()
{
    new npc_dtinireset;
}
