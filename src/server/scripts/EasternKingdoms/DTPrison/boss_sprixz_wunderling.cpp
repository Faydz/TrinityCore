// Author: Weiske @ DarkThunder-wow.net
// Boss 1 der DT Prison Instanz - Sprixz Wunderling

#include "ScriptPCH.h"
 
enum Texts
{
    SAY_COMBAT  = 1,
    SAY_KILL    = 2,
    SAY_DEATH   = 3,
};
 
enum Spells
{
    // Phase 1
    SPELL_SHADOWBOLT     = 686,
    SPELL_POLYMORPH      = 65801,
    SPELL_ARCANE_BARRAGE = 67994,

    // Phase 2
    SPELL_SCORCH         = 75419,
    SPELL_FROSTFIREBOLT  = 71130,

    // Phase 3
    SPELL_MIRROR         = 55342,
    SPELL_FROSTAURA      = 28531,
    SPELL_FROSTBLITZ     = 43428,
};
 
enum Events
{
    // Phase 1
    EVENT_ADDS = 1,
    EVENT_SHADOWBOLT,
    EVENT_POLYMORPH,
    EVENT_ARCANE_BARRAGE,

    // Phase 2
    EVENT_PHASE_ZWEI,
    EVENT_SCORCH,
    EVENT_FROSTFIREBOLT,

    // Phase 3
    EVENT_MIRROR,
    EVENT_FROSTAURA,
    EVENT_FROSTBLITZ,
};

Position const AddPos[3] = 
{
    {-90.59f,  98.44f, -31.72f, 4.71f},
    {-90.65f,  44.81f, -31.72f, 1.57f},
    {-117.33f, 71.75f, -31.72f, 0.01f},
};
 
class boss_sprixz_wunderling : public CreatureScript
{
    public:
        boss_sprixz_wunderling() : CreatureScript("boss_sprixz_wunderling") { }
 
        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new boss_sprixz_wunderlingAI(pCreature);
        }
 
        struct boss_sprixz_wunderlingAI : public ScriptedAI
        {
            boss_sprixz_wunderlingAI(Creature* c) : ScriptedAI(c) {}
 
            EventMap events;
            uint8 _phase;
            bool SwitchPhase;
 
            void Reset()
            {  
                events.Reset();
                SwitchPhase = false;
                _phase = 1;      
               
                me->AddAura(45776, me);
                events.SetPhase(1);    
                events.ScheduleEvent(EVENT_ADDS, 20000, 0, 1);
                events.ScheduleEvent(EVENT_SHADOWBOLT, 2500, 0, 1);
                events.ScheduleEvent(EVENT_POLYMORPH, 20000, 0, 1);
                events.ScheduleEvent(EVENT_ARCANE_BARRAGE, 6000, 0, 1);
                events.ScheduleEvent(EVENT_PHASE_ZWEI, 65000, 0, 1);
            }
 
            void EnterCombat(Unit* /*who*/)
            {
                me->RemoveAura(45776);
                Talk(SAY_COMBAT);
            }
 
            void KilledUnit(Unit*)
            {
                Talk(SAY_KILL);
            }
           
            void JustDied(Unit* /*killer*/)
            {
                Talk(SAY_DEATH);
            }
       
            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;
                   
                if (_phase == 2 && HealthBelowPct(40))
                {
                    _phase = 3;
                    events.SetPhase(3);
                    DoCast(me, SPELL_FROSTAURA);
                    events.ScheduleEvent(EVENT_FROSTBLITZ, 150000, 0, 3);
                    events.ScheduleEvent(EVENT_MIRROR, 50000, 0, 3);
                }
 
                events.Update(diff);
 
                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_ADDS:
                        {
                            DoSummon(90015, AddPos[0], 0, TEMPSUMMON_MANUAL_DESPAWN);
                            DoSummon(90015, AddPos[1], 0, TEMPSUMMON_MANUAL_DESPAWN);
                            DoSummon(90015, AddPos[2], 0, TEMPSUMMON_MANUAL_DESPAWN);
                            events.ScheduleEvent(EVENT_ADDS, 20000, 0, 1);
                            break;
                        }
                        case EVENT_SHADOWBOLT:
                        {
                            DoCast(me->getVictim(), SPELL_SHADOWBOLT);
                            events.ScheduleEvent(EVENT_SHADOWBOLT, urand(10000, 12500), 0, 1);
                            break;
                        }
                        case EVENT_POLYMORPH:
                        {
                            if (Unit *pTarget = SelectTarget(SELECT_TARGET_TOPAGGRO, 1))
                                DoCast(pTarget, SPELL_POLYMORPH);
                            events.ScheduleEvent(EVENT_POLYMORPH, urand(15000, 20000), 0, 1);
                            break;
                        }
                        case EVENT_ARCANE_BARRAGE:
                        {
                            if (Unit *pTarget = SelectTarget(SELECT_TARGET_BOTTOMAGGRO))
                                DoCast(pTarget, SPELL_ARCANE_BARRAGE);
                            events.ScheduleEvent(EVENT_ARCANE_BARRAGE, urand(12500, 17000), 0, 1);
                            break;
                        }
                        case EVENT_PHASE_ZWEI:
                        {
                            _phase = 2;                
                            events.SetPhase(2);
                            events.ScheduleEvent(EVENT_SCORCH, 8000, 0, 2);
                            events.ScheduleEvent(EVENT_FROSTFIREBOLT, 8000, 0, 2);
                            SwitchPhase = true;
                            break;
                        }
                        case EVENT_SCORCH:
                        {
                            DoCast(me->getVictim(), SPELL_SCORCH);
                            events.ScheduleEvent(EVENT_SCORCH, urand(5000, 7000), 0, 2);
                            break;
                        }
                        case EVENT_FROSTFIREBOLT:
                        {
                            DoCast(me->getVictim(), SPELL_FROSTFIREBOLT);
                            events.ScheduleEvent(EVENT_FROSTFIREBOLT, 9500, 0, 2);
                            break;
                        }
                        case EVENT_MIRROR:
                        {
                            DoCast(me, SPELL_MIRROR);
                            events.ScheduleEvent(EVENT_MIRROR, 25000, 0, 3);
                            break;
                        }
                        case EVENT_FROSTBLITZ:
                        {
                            DoCast(me->getVictim(), SPELL_FROSTBLITZ);
                            events.ScheduleEvent(EVENT_FROSTBLITZ, urand(15000, 18000), 0, 3);
                            break;
                        }
                    }
                }
                DoMeleeAttackIfReady();
            }
        };
};
 
enum AddSpells
{
    SPELL_FROSTBOLT  = 72905,
    SPELL_FROST_NOVA = 65792,
    SPELL_DEBUFF     = 6873,
};
 
enum AddEvent
{
    EVENT_FROSTBOLT  = 1,
    EVENT_FROST_NOVA = 2,
    EVENT_DEBUFF     = 3,
};
 
class boss_sprixz_wunderling_add : public CreatureScript
{
    public:
        boss_sprixz_wunderling_add() : CreatureScript("boss_sprixz_wunderling_add") {}
 
        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new boss_sprixz_wunderling_AddAI (pCreature);
        }
 
        struct boss_sprixz_wunderling_AddAI : public ScriptedAI
        {
            boss_sprixz_wunderling_AddAI (Creature* c) : ScriptedAI(c) {}
           
            EventMap events;
 
            void Reset()
            {  
                events.Reset();
                events.ScheduleEvent(EVENT_FROSTBOLT, 1000);
                events.ScheduleEvent(EVENT_FROST_NOVA, 3000);
                events.ScheduleEvent(EVENT_DEBUFF, 6000);
            }
       
            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;    
                events.Update(diff);
 
                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_FROSTBOLT:
                        {
                            if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                                DoCast(pTarget, SPELL_FROSTBOLT);
                            events.ScheduleEvent(EVENT_FROSTBOLT, urand(4000, 6000));
                            break;
                        }
                        case EVENT_FROST_NOVA:
                        {
                            DoCast(SPELL_FROST_NOVA);
                            events.ScheduleEvent(EVENT_FROST_NOVA, 5000);
                            break;
                        }
                        case EVENT_DEBUFF:
                        {
                            DoCast(SPELL_DEBUFF);
                            events.ScheduleEvent(EVENT_DEBUFF, 120000);
                            break;
                        }
                    }
                }
            }
        };
 
};
 
void AddSC_boss_sprixz_wunderling()
{
    new boss_sprixz_wunderling();
    new boss_sprixz_wunderling_add();
}