// Author: Thainification @ DarkThunder-wow.net
// Boss 3 der DT Prison Instanz - Kla'thruun

#include "ScriptPCH.h"

enum Texts
{
    SAY_COMBAT      = 1,
    SAY_KILL        = 2,
    SAY_DEATH       = 3,
};

enum Spells
{
    SPELL_ENRAGE                    = 61632,
    SPELL_HASSERFUELLTERSTOSS       = 41926,
    SPELL_ALTEWUNDEN                = 66620,
    
    SPELL_FAEUSTEAUSSTEIN           = 62344,
    SPELL_ABSTUMPFEN                = 41410,  
};

enum Events
{
    EVENT_ENRAGE,
    EVENT_HASSERFUELLTERSTOSS,
    EVENT_ALTEWUNDEN,
    EVENT_PHASE_ZWEI,
    
    EVENT_FAEUSTEAUSSTEIN,
    EVENT_ABSTUMPFEN,
    EVENT_PHASE_EINS,
};

class boss_2_Kla_thruun : public CreatureScript
{
    public:
        boss_2_Kla_thruun() : CreatureScript("boss_2_Kla_thruun") {}
        
        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new boss_2_Kla_thruunAI(pCreature);
        }
       
        struct boss_2_Kla_thruunAI : public ScriptedAI
        {
            boss_2_Kla_thruunAI(Creature* c) : ScriptedAI(c) {}
            
            EventMap events;
            uint8 Phase;
            bool SwitchPhase;
            
            void Reset()
            {
                SwitchPhase = false;
                
                me->RemoveAllAuras();
                events.SetPhase(1);
                events.Reset();
                events.ScheduleEvent(EVENT_ENRAGE, 800000);
                events.ScheduleEvent(EVENT_HASSERFUELLTERSTOSS, urand(3000, 5000), 0, 1);
                events.ScheduleEvent(EVENT_ALTEWUNDEN, 3000, 0, 1);
                events.ScheduleEvent(EVENT_PHASE_ZWEI, 50000, 0, 1);                
            }
        
            void EnterCombat(Unit*)
            {
                me->setActive(true);
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
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {       
                        case EVENT_PHASE_ZWEI:
                        {                            
                            events.SetPhase(2);
                            events.ScheduleEvent(EVENT_FAEUSTEAUSSTEIN, 1000, 0, 2);
                            events.ScheduleEvent(EVENT_ABSTUMPFEN, 26000, 0, 2);
                            events.ScheduleEvent(EVENT_PHASE_EINS, 12500, 0, 2);
                            break;
                        }         
                        case EVENT_PHASE_EINS:
                        {                            
                            events.SetPhase(1);
                            events.ScheduleEvent(EVENT_HASSERFUELLTERSTOSS, urand(3000, 5000), 0, 1);
                            events.ScheduleEvent(EVENT_ALTEWUNDEN, 3000, 0, 1);
                            events.ScheduleEvent(EVENT_PHASE_ZWEI, 50000, 0, 1);
                            break;
                        }   
                        case EVENT_ENRAGE:
                        {
                            DoCast(me, SPELL_ENRAGE);
                            break;
                        }      
                        case EVENT_HASSERFUELLTERSTOSS:
                        {
                            if (Unit *pTarget = SelectTarget(SELECT_TARGET_TOPAGGRO,2))
                                DoCast(pTarget, SPELL_HASSERFUELLTERSTOSS);
                            events.ScheduleEvent(EVENT_HASSERFUELLTERSTOSS, urand(30000, 45000), 0, 1);
                            break;    
                        }     
                        case EVENT_ALTEWUNDEN:
                        {
                            if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                                DoCast(pTarget, SPELL_ALTEWUNDEN);
                            events.ScheduleEvent(EVENT_ALTEWUNDEN, urand(30000, 45000), 0, 1);
                            break;    
                        }   
                        case EVENT_FAEUSTEAUSSTEIN:
                        {
                            DoCast(me->getVictim(), SPELL_FAEUSTEAUSSTEIN);
                            break;    
                        }
                        case EVENT_ABSTUMPFEN:
                        {
                            DoCast(me, SPELL_ABSTUMPFEN, true);
                            events.ScheduleEvent(EVENT_ABSTUMPFEN, 26000, 0, 2);
                            break;
                        }
                    }
                }
                DoMeleeAttackIfReady();
            } 
        };
};

void AddSC_boss_2_Kla_thruun()
{
    new boss_2_Kla_thruun();
}