/////////////////////////////////////////////////////////////////////
//	DT_Ini Boss
//
//	Boss Nr 01 Viertel 02
//	Der Schwarze Doktor	
//
//	made by gizmo.ms
/////////////////////////////////////////////////////////////////////

#include "ScriptPCH.h"

enum Texts
{
	SAY_INTRO				= 0,
	SAY_ADDS				= 1,
	SAY_KILL				= 2,
	SAY_ENRAGE				= 3,
	SAY_DEATH				= 4,
	SAY_PHASE2				= 5
};

enum Spells
{
    SPELL_ENRAGE			= 47008,
	SPELL_ANTIAGGRO			= 29232,
	SPELL_BENOMMEN			= 38767,
	SPELL_SAURESALVE		= 70273,
	SPELL_GIFTPFUETZE		= 70274	
};

enum Adds
{
	ADD_WURM				= 200016
};

enum Events
{
	EVENT_SAURESALVE,
	EVENT_BENOMMEN,
	EVENT_ANTIAGGRO,
	EVENT_ADDS,
	
	EVENT_GIFTPFUETZE,
	
	EVENT_ENRAGE	
};

class boss_der_schwarzedoktor : public CreatureScript
{
    public:
        boss_der_schwarzedoktor() : CreatureScript("boss_der_schwarzedoktor") { }

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new boss_der_schwarzedoktorAI (pCreature);
        }

        struct boss_der_schwarzedoktorAI : public ScriptedAI
        {
            boss_der_schwarzedoktorAI (Creature *c) : ScriptedAI(c) { }
            
            EventMap events;
            uint8 _phase;
                        
            void Reset()
            {
                events.Reset();
                me->RemoveAllAuras();
                _phase = 1;
                events.SetPhase(1);			
                events.ScheduleEvent(EVENT_ENRAGE, 800000);
                events.ScheduleEvent(EVENT_ANTIAGGRO, 3000,0,1);
                events.ScheduleEvent(EVENT_BENOMMEN, 30000,0,1);
                events.ScheduleEvent(EVENT_SAURESALVE, 15000,0,1);
                events.ScheduleEvent(EVENT_ADDS, 30000,0,1);				
            }

            void EnterCombat(Unit* /*who*/)
            {
                me->setActive(true);
                Talk(SAY_INTRO);
            }

            void JustDied(Unit* /*killer*/)
            {
                Talk(SAY_DEATH);
            }
          
            void KilledUnit(Unit *)
            {
                Talk(SAY_KILL);
            }
            
            void UpdateAI(const uint32 diff)
            {
                if (_phase == 1 && HealthBelowPct(55))
                {
                    _phase = 2; 
                    events.SetPhase(2); 
                    Talk(SAY_PHASE2);
                    events.ScheduleEvent(EVENT_BENOMMEN, 10000,0,2);
                    events.ScheduleEvent(EVENT_SAURESALVE, 5000,0,2);
                    events.ScheduleEvent(EVENT_GIFTPFUETZE, 7000,0,2);
                }
                if (!UpdateVictim())
                        return;  
                    events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_ANTIAGGRO:
                        {
                            DoCast(me->getVictim(), SPELL_ANTIAGGRO);
                            break;    
                        } 
                        case EVENT_SAURESALVE:
                        {
                            if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                                DoCast(pTarget, SPELL_SAURESALVE);
                            events.ScheduleEvent(EVENT_SAURESALVE,10000, 0, 1);
                            events.ScheduleEvent(EVENT_SAURESALVE,5000, 0, 2);
                            break;
                        }
                        case EVENT_BENOMMEN:
                        {
                            if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                                DoCast(pTarget, SPELL_BENOMMEN);
                            events.ScheduleEvent(EVENT_BENOMMEN, 15000, 0, 1);
                            events.ScheduleEvent(EVENT_BENOMMEN, 10000, 0, 2);
                            break;
                        }
                        case EVENT_ADDS:
                        {
                            if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                                me->SummonCreature (ADD_WURM, pTarget->GetPositionX(), pTarget->GetPositionY(), pTarget->GetPositionZ());
                            if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                                me->SummonCreature (ADD_WURM, pTarget->GetPositionX(), pTarget->GetPositionY(), pTarget->GetPositionZ());
                            if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                                me->SummonCreature (ADD_WURM, pTarget->GetPositionX(), pTarget->GetPositionY(), pTarget->GetPositionZ());
                            events.ScheduleEvent(EVENT_ADDS, 25000, 0, 1);
                            break;
                        }
                        case EVENT_GIFTPFUETZE:
                        {
                            DoCast(me->getVictim(), SPELL_GIFTPFUETZE);
                            events.ScheduleEvent(EVENT_GIFTPFUETZE, urand(5000, 7000), 0, 2);
                            break;    
                        } 
                        case EVENT_ENRAGE:
                        {
                            DoCast(me, SPELL_ENRAGE);
                            break;
                        }
                    }
                }
                DoMeleeAttackIfReady();
            }
        };
};

void AddSC_boss_der_schwarzedoktor()
{
    new boss_der_schwarzedoktor();
}