#include "ScriptPCH.h"
#include "WorldPacket.h"

#define DTIniReset_Item 44209 //eventmarke

class npc_dtinireset : public CreatureScript
{
public:
    npc_dtinireset() : CreatureScript("npc_dtinireset") { }

    /*uint32 npc_dtinireset_do(Player *player)
    {
        Player* pl = player->GetSession()->GetPlayer();
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
	*/
    /*
                        InstanceSave *save = itr->second.save;
                        std::string timeleft = GetTimeString(save->GetResetTime() - time(NULL));
                        PSendSysMessage("unbinding map: %d inst: %d perm: %s diff: %d canReset: %s TTR: %s", itr->first, save->GetInstanceId(), itr->second.perm ? "yes" : "no",  save->GetDifficulty(), save->CanReset() ? "yes" : "no", timeleft.c_str());
                        player->UnbindInstance(itr, Difficulty(i));
                        counter++;
    */
    bool OnGossipHello(Player *player, Creature *creature)
    {
        player->ADD_GOSSIP_ITEM(5, "Eiskronenzitadelle 10 Heroisch (10 Embleme von Darkthunder)", GOSSIP_SENDER_MAIN, 6002);

        player->ADD_GOSSIP_ITEM(10, "Auf Wiedersehen!", GOSSIP_SENDER_MAIN, 9999);
        player->PlayerTalkClass->SendGossipMenu(2713,creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 action)
    {
		player->PlayerTalkClass->ClearMenus();

		if(sender != GOSSIP_SENDER_MAIN)
			return false;

		switch(action)
		{
		case 6002:


			if(!player->HasItemCount(DTIniReset_Item,10,false))
			{
				creature->MonsterWhisper("Du hast leider nicht genug Embleme.",player->GetGUID());
				player->CLOSE_GOSSIP_MENU();
				return true;
			}

			if(player->GetBoundInstance(631, RAID_DIFFICULTY_10MAN_HEROIC) == false)
			{
				creature->MonsterWhisper("Du hast keine ID von dieser Instanz.",player->GetGUID());
				player->CLOSE_GOSSIP_MENU();
				return true;
			}

			else
			{
				player->DestroyItemCount(DTIniReset_Item,10,true,false);
				player->UnbindInstance(631, RAID_DIFFICULTY_10MAN_HEROIC, true); 
				creature->MonsterWhisper("Die Instanzen ID von Eiskronenzitadelle 10 Heroisch wurde erfolgreich zur\303\274ckgesetzt",player->GetGUID());
				return true;
			}
			break;
			
		case 9999:
			player->CLOSE_GOSSIP_MENU();
			return true;
			break;

		}
       /* if (action != 6002)
        {
            player->CLOSE_GOSSIP_MENU();
            return true;
        }

        char* text = "Du hast leider nicht genug Marken.";

        if (!player->HasItemCount(DTIniReset_Item,10,false))
        {
            creature->MonsterWhisper(text,player->GetGUID());
            player->CLOSE_GOSSIP_MENU();
            return true;
        }

        uint32 counter = this->npc_dtinireset_do(player);

        if (!counter)
            return true;

        if (counter == 0)
            text = "Ich konnte keine Instanzen finden..";
        else
        {
            player->DestroyItemCount(DTIniReset_Item,10,true,false);
            sprintf(text, "Es wurden %u Instanzen resetted. Beehren Sie uns bald wieder!", counter);
        }

        creature->MonsterWhisper(text,player->GetGUID());
        player->CLOSE_GOSSIP_MENU();
        return true; */
    }
};

void AddSC_npc_dtinireset()
{
    new npc_dtinireset;
}
