
    #include "ScriptMgr.h"
    #include "ScriptedCreature.h"
    #include "ScriptedGossip.h"
    #include "Player.h"
     
     
    enum Yells
    {
    };
     
    enum Spells
    {
		Spell_Blitz				= 74670,
		Spell_Bleeding_Wound	= 74846,
		Spell_Ground_Siege		= 74634,
		Spell_Frenzy			= 74853
    };
     
    class Generall_Umbriss : public CreatureScript
    {
            public:
                    Generall_Umbriss() : CreatureScript("Generall_Umbriss") {}
     

                    struct Generall_UmbrissAI : public ScriptedAI
                    {
						 Generall_UmbrissAI(Creature* creature) : ScriptedAI(creature) {}

						 uint32 Blitz_Timer;
						 uint32 Bleeding_Wound_Timer;
						 uint32 Ground_Siege_Timer;

                            void Reset() OVERRIDE
                            {

								Blitz_Timer = 20000;
								Bleeding_Wound_Timer = 5000;
								Ground_Siege_Timer = 16000;
								me->RestoreFaction();
                            }
     
                            void EnterCombat(Unit* who) OVERRIDE
                            {
                            }
     
                            void UpdateAI(uint32 uiDiff) OVERRIDE
                            {
								 if (!UpdateVictim())
									 return;

								 //Frenzy
								 if(me->HealthBelowPct(30))
								 {
									 DoCast(me, Spell_Frenzy);
								 }

								 //Blitz

								 if(Blitz_Timer <= uiDiff)
									  {
										Unit* target = NULL;
										target = SelectTarget(SELECT_TARGET_RANDOM, 0);
										 if (target)
											 DoCast(target, Spell_Blitz);
										  Blitz_Timer = 20000;
									  }
								 else
									 Blitz_Timer -= uiDiff;

								 //Bleeding_Wound

								 if(Bleeding_Wound_Timer <=uiDiff)
									{
										DoCast(me->GetVictim(), Spell_Bleeding_Wound);
										Bleeding_Wound_Timer = 5000;
									}
								 else
									 Bleeding_Wound_Timer -= uiDiff;

								 //Ground_Siege

								 if(Ground_Siege_Timer <= uiDiff)
									{
										Unit* target = NULL;
										target = SelectTarget(SELECT_TARGET_RANDOM, 0);
										 if (target)
											 DoCast(target, Spell_Ground_Siege);
										  Ground_Siege_Timer = 16000;
									  }
								 else
									 Ground_Siege_Timer -= uiDiff;




								DoMeleeAttackIfReady();
                            }
					};
		ScriptedAI* GetAI (Creature* creature) const
    {
        return new Generall_UmbrissAI(creature);
    }
         };
     
    void AddSC_Generall_Umbriss()
    {
            new Generall_Umbriss();
    }

