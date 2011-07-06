#include "ScriptPCH.h"

#define C_RACEMOB_COUNT 6
#define SPELL_FIREWORK 11544

const uint32 RaceMobIDs[] =
{
    801002, //cat
    801003, //2
    801004, //3
    801005, //4
    801006, //5
    801007, //6
};

const Position PosMobStart[] =
{
    {-7860.0f, -500.0f, 170.8f, 3.12f},
    {-7860.0f, -490.0f, 170.8f, 3.12f},
    {-7860.0f, -480.0f, 170.8f, 3.12f},
    {-7860.0f, -470.0f, 170.8f, 3.12f},
    {-7860.0f, -460.0f, 170.8f, 3.12f},
    {-7860.0f, -450.0f, 170.8f, 3.12f},
};

const Position PosMobEnd[] =
{
    {-7900.0f, -500.0f, 170.8f, 3.12f},
    {-7900.0f, -490.0f, 170.8f, 3.12f},
    {-7900.0f, -480.0f, 170.8f, 3.12f},
    {-7900.0f, -470.0f, 170.8f, 3.12f},
    {-7900.0f, -460.0f, 170.8f, 3.12f},
    {-7900.0f, -450.0f, 170.8f, 3.12f},
};

struct DTWette
{
    Player* m_plr;
    uint32 m_wette;
    uint8 m_mob;
};

class custom_dtrace_controler : public CreatureScript
{
public:
    custom_dtrace_controler() : CreatureScript("custom_dtrace_controler") { }

    struct custom_dtrace_controlerAI : public ScriptedAI
    {
        custom_dtrace_controlerAI(Creature* pCreature) : ScriptedAI(pCreature)
        {
            for (uint32 i = 0; i < C_RACEMOB_COUNT; ++i)
                if (Creature *mob = me->SummonCreature(RaceMobIDs[i], PosMobStart[i], TEMPSUMMON_MANUAL_DESPAWN, 0, 0))
                    RaceMobs.push_back(mob);
        }

        std::vector<Creature*> RaceMobs;
        std::vector<DTWette> Wetten;

        bool bStarted;
        bool bReset;
        bool bAnnounce1, bAnnounce3, bAnnounce0;
        uint64 uiWinner;
        uint64 uiWinnerIdx;

        uint32 uiRace_Timer;
        uint32 uiReset_Timer;

        void Reset()
        {
            bStarted = false;
            bReset = true;
            bAnnounce1 = false;
            bAnnounce3 = false;
            bAnnounce0 = false;
            uiWinner = 0;
            uiWinnerIdx = 0;
            uiRace_Timer = 4*MINUTE*IN_MILLISECONDS;
            uiReset_Timer = 20*IN_MILLISECONDS;
        }

        void UpdateAI(const uint32 diff)
        {
            if (uiRace_Timer <= diff)
            {
                StartRace();
                uiRace_Timer = 4*MINUTE*IN_MILLISECONDS;
            } else uiRace_Timer -= diff;

            if (uiRace_Timer <= 3*MINUTE*IN_MILLISECONDS && !bAnnounce3)
            {
                me->MonsterSay("DT-Rennen: Das Rennen beginnt in 3 Minuten.", LANG_UNIVERSAL, NULL);
                bAnnounce3 = true;
            }
            else if (uiRace_Timer <= 1*MINUTE*IN_MILLISECONDS && !bAnnounce1)
            {
                me->MonsterSay("DT-Rennen: Das Rennen beginnt in 1 Minute.", LANG_UNIVERSAL, NULL);
                bAnnounce1 = true;
            }
            else if (uiRace_Timer <= 10*IN_MILLISECONDS && !bAnnounce0)
            {
                me->MonsterSay("DT-Rennen: Das Rennen beginnt in 10 Sekunden.", LANG_UNIVERSAL, NULL);
                bAnnounce0 = true;
            }

            if (!bReset)
                if (uiReset_Timer <= diff)
                {
                    ResetRace();
                    bReset = true;
                    uiReset_Timer = 20*IN_MILLISECONDS;
                } else uiReset_Timer -= diff;
        }

        void AddWette(Player* plr, uint32 money, uint32 mob)
        {
            if (!GetWette(plr))
            {
                DTWette dtw;
                dtw.m_plr = plr;
                dtw.m_wette = money;
                dtw.m_mob = (uint8)mob;

                Wetten.push_back(dtw);
            }
            else
                me->MonsterWhisper("Du kannst nur auf einen Teilnehmer wetten!", plr->GetGUID(), false);
        }

        uint32 GetWette(Player* plr)
        {
            for (std::vector<DTWette>::const_iterator itr = Wetten.begin(); itr != Wetten.end(); ++itr)
                if ((*itr).m_plr == plr)
                    return (*itr).m_wette;

            return 0;
        }

        uint32 GetMobWette(Player* plr)
        {
            for (std::vector<DTWette>::const_iterator itr = Wetten.begin(); itr != Wetten.end(); ++itr)
                if ((*itr).m_plr == plr)
                    return (*itr).m_mob;

            return 0;
        }

        void ProcessWetten(uint32 winner)
        {
            for (std::vector<DTWette>::const_iterator itr = Wetten.begin(); itr != Wetten.end(); ++itr)
                if (Player* plr = (*itr).m_plr)
                    if (plr && (*itr).m_mob == winner)
                        RewardWette(plr);

            ClearWetten(); // Alle löschen
        }

        void RewardWette(Player* plr)
        {
            if (uint32 wette = GetWette(plr))
                if (wette > 0)
                {
                    uint32 itemchancef = wette/50;
                    if (itemchancef > 45)
                        itemchancef = 45; // Max. 45%

                    bool item = (urand(0, 100) <= itemchancef) ? true : false;

                    if (!item) // Kein Item = Geld senden
                    {
                        int32 money = (int32)(wette * 1.3333333333f + (int32)wette/10)*10000;
                        std::string subject = "DT-Rennen";
                        std::string text    = "Sie haben beim DT-Rennen einen Geldpreis gewonnen!";

                        MailSender sender(me);
                        SQLTransaction trans = CharacterDatabase.BeginTransaction();

                        MailDraft(subject, text)
                            .AddMoney(money)
                            .SendMailTo(trans, MailReceiver(plr, GUID_LOPART(plr->GetGUID())), sender);

                        CharacterDatabase.CommitTransaction(trans);
                    }
                    else
                    {
                        uint32 chance = urand(0, 100);
                        uint32 item_id = 0;

                        if (chance <= 13)
                            item_id = 23162; // Forors Kiste der endlosen Wiederstandsausrüstung
                        else
                            switch (urand(1,3))
                            {
                                case 1:
                                    item_id = 988880; // Rot
                                    break;
                                case 2:
                                    item_id = 988881; // Gruen
                                    break;
                                case 3:
                                    item_id = 988882; // Blau
                                    break;
                            }

                        std::string subject = "DT-Rennen";
                        std::string text    = "Sie haben beim DT-Rennen einen Sachpreis gewonnen!";

                        MailSender sender(me);
                        MailDraft draft(subject, text);

                        SQLTransaction trans = CharacterDatabase.BeginTransaction();

                        if (Item* item = Item::CreateItem(item_id, 1, plr))
                        {
                            item->SaveToDB(trans);
                            draft.AddItem(item);
                        }

                        draft.SendMailTo(trans, MailReceiver(plr, GUID_LOPART(plr->GetGUID())), sender);
                        CharacterDatabase.CommitTransaction(trans);
                    }

                    plr->SaveToDB();

                    // belohnung NIY
                    char buff[2048];
                    sprintf(buff, "DT-Rennen: %s hat etwas gewonnen.", plr->GetName());
                    me->MonsterSay(buff, LANG_UNIVERSAL, NULL);
                }
        }

        void ClearWetten()
        {
            Wetten.clear();    
        }

        void StartRace()
        {
            bStarted = true;
            int i = 0;
            for (std::vector<Creature*>::const_iterator itr = RaceMobs.begin(); itr != RaceMobs.end(); ++itr)
            {
                if (!(*itr))
                    continue;
                
                float speed = (rand()/(float(RAND_MAX)+1)) * (2.4f - 0.12f) + 0.12f;//* (max - min) + min;

                (*itr)->SetHomePosition(PosMobEnd[i].GetPositionX(), PosMobEnd[i].GetPositionY(), PosMobEnd[i].GetPositionZ(), 3.12f);
                (*itr)->SetSpeed(MOVE_WALK, speed, true);
                (*itr)->SetSpeed(MOVE_RUN, speed, true);

                /*char buff[2048];
                sprintf(buff, "%s %f", (*itr)->GetName(), speed);
                me->MonsterSay(buff, LANG_UNIVERSAL, NULL);*/

                (*itr)->GetMotionMaster()->MoveTargetedHome();
                ++i;
            }
        }

        void StopRace()
        {
            bStarted = false;
            for (std::vector<Creature*>::const_iterator itr = RaceMobs.begin(); itr != RaceMobs.end(); ++itr)
            {
                if (!(*itr))
                    continue;

                (*itr)->GetMotionMaster()->Clear(true);
                (*itr)->StopMoving();
            }
        }

        void ResetRace()
        {
            bStarted = false;

            int i = 0;
            for (std::vector<Creature*>::const_iterator itr = RaceMobs.begin(); itr != RaceMobs.end(); ++itr)
            {
                if (!(*itr))
                    continue;

                (*itr)->SetHomePosition(PosMobStart[i].GetPositionX(),PosMobStart[i].GetPositionY(),PosMobStart[i].GetPositionZ(), 3.12f);
                (*itr)->GetMotionMaster()->MoveTargetedHome();
                ++i;
            }
        }

        void Reached(uint64 uiGUID, uint32 uiEntry)
        {
            for (std::vector<Creature*>::const_iterator itr = RaceMobs.begin(); itr != RaceMobs.end(); ++itr)
            {
                if (!(*itr))
                    continue;

                if (uiGUID == (*itr)->GetGUID() && bStarted)
                {
                    StopRace();
                    uiWinner = uiGUID;

                    switch (uiEntry) //creature_template entries
                    {
                        case 801002: // Gypsi
                            uiWinnerIdx = 1;
                            break;
                        case 801003: // Schnakentöter
                            uiWinnerIdx = 2;
                            break;
                        case 801004: // Ornulf Flinkpaddel
                            uiWinnerIdx = 3;
                            break;
                        case 801005: // Spyro
                            uiWinnerIdx = 4;
                            break;
                        case 801006: // Mmmrrrggglll
                            uiWinnerIdx = 5;
                            break;
                        case 801007: // Tyrael
                            uiWinnerIdx = 6;
                            break;
                        default:
                            uiWinnerIdx = 0;
                            break;
                    }

                    (*itr)->CastSpell((*itr), SPELL_FIREWORK, true);

                    char buff[2048];
                    sprintf(buff, "Wir haben einen Gewinner! %s hat das Rennen gewonnen!", (*itr)->GetName());
                    me->MonsterSay(buff, LANG_UNIVERSAL, NULL);

                    ProcessWetten(uiWinnerIdx);
                    bAnnounce3 = false;
                    bAnnounce1 = false;
                    bAnnounce0 = false;
                    bReset = false;
                }
                else if (!bStarted)
                {
                    (*itr)->SetOrientation(3.12f);
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new custom_dtrace_controlerAI(pCreature);
    }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Wette abschliessen", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        //pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "DEBUG: Reward", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);

        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();

        switch (uiAction)
        {
            case GOSSIP_ACTION_INFO_DEF+1:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Auf wen moechtest du eine Wette abschliessen?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

                pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_DOT, "Gypsi", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+11, "Wieviel Gold willst du wetten?", 0, true);
                pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_DOT, "Schnakentoeter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+12, "Wieviel Gold willst du wetten?", 0, true);
                pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_DOT, "Ornulf Flinkpaddel", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+13, "Wieviel Gold willst du wetten?", 0, true);
                pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_DOT, "Spyro", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+14, "Wieviel Gold willst du wetten?", 0, true);
                pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_DOT, "Mmmrrrggglll", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+15, "Wieviel Gold willst du wetten?", 0, true);
                pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_DOT, "Tyrael", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+16, "Wieviel Gold willst du wetten?", 0, true);

                pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+2:
                pPlayer->CLOSE_GOSSIP_MENU();
                //CAST_AI(custom_dtrace_controler::custom_dtrace_controlerAI, pCreature->AI())->RewardWette(pPlayer);
                break;
        }

        return true;
    }

    bool OnGossipSelectCode(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction, const char* code)
    {
        pPlayer->PlayerTalkClass->ClearMenus();

        if (uiSender == GOSSIP_SENDER_MAIN)
        {
            if (uiAction > GOSSIP_ACTION_INFO_DEF+10 && uiAction < GOSSIP_ACTION_INFO_DEF+17 && atoi(code) > 0)
            {
                if (pPlayer->GetMoney() >= (uint32)atol(code)*10000)
                {
                    pPlayer->ModifyMoney(-1 * (int32)atoi(code)*10000);
                    uint32 idx = uiAction - 1010;
                    CAST_AI(custom_dtrace_controler::custom_dtrace_controlerAI, pCreature->AI())->AddWette(pPlayer, (uint32)atol(code), idx);

                    char* mobname = "";
                    switch (idx) //creature_template entries
                    {
                        case 1: mobname = "Gypsi"; break;
                        case 2: mobname = "Schnakentoeter"; break;
                        case 3: mobname = "Ornulf Flinkpaddel"; break;
                        case 4: mobname = "Spyro"; break;
                        case 5: mobname = "Mmmrrrggglll"; break;
                        case 6: mobname = "Tyrael"; break;
                        default: mobname = "";
                    }
                    char buff[2048];
                    sprintf(buff, "Du hast %s Gold auf %s gewettet.", code, mobname);
                    pCreature->MonsterWhisper(buff, pPlayer->GetGUID());
                }
                else
                    pCreature->MonsterWhisper("Das kannst du dir leider nicht leisten!", pPlayer->GetGUID());
                pPlayer->CLOSE_GOSSIP_MENU();
            }
            return true;
        }

        return false;
    }
};

class custom_dtrace_participant : public CreatureScript
{
public:
    custom_dtrace_participant() : CreatureScript("custom_dtrace_participant") { }

    struct custom_dtrace_participantAI : public ScriptedAI
    {
        custom_dtrace_participantAI(Creature* pCreature) : ScriptedAI(pCreature)
        {
        }

        void JustReachedHome()
        {
            if (Creature* cControler = me->FindNearestCreature(801001, 150.0f))
                CAST_AI(custom_dtrace_controler::custom_dtrace_controlerAI, cControler->AI())->Reached(me->GetGUID(), me->GetEntry());
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new custom_dtrace_participantAI(pCreature);
    }
};

void AddSC_custom_dtrace()
{
    new custom_dtrace_controler();
    new custom_dtrace_participant();
}
