	

    #include "ScriptMgr.h"
    #include "ScriptedCreature.h"
    #include "ScriptedGossip.h"
    #include "Player.h"
     
     
    enum Yells
    {
    };
     
    enum Spells
    {
		SPELL_GEYSER			= 75722,
		SPELL_FUNGALSPORES		= 80564,
		SPELL_SHOCKBLAST		= 76008,
		SPELL_WATERSPOUT		= 75683,

		//Ehrenwache der Naz'jar
		SPELL_ARCSLASH			= 75907,
		SPELL_ENRAGE			= 75998,

		//Sturmhexe der Naz'jar
		SPELL_LIGHTNINGSURGE	= 75992,
		SPELL_CHAINLIGHTNING	= 75813
    };
     
    class lady_nazjar : public CreatureScript
    {
            public:
                    lady_nazjar() : CreatureScript("lady_nazjar") {}
     
                    struct boss_creatureAI : public ScriptedAI
                    {

							uint32 timer_geyser;
							uint32 timer_fungalspores;
							uint32 timer_shockblast;
							uint32 timer_waterspout;
							uint32 timer_phasetwo;

                            void Reset() OVERRIDE
                            {
								phasetwo = 60000;

                            }
     
                            void EnterCombat(Unit* who) OVERRIDE
                            {
                            }
     
                            void UpdateAI(uint32 uiDiff) OVERRIDE
                            {
								uint8 geyser = 0;

								if(me->HealthBelowPct(66) && geyser == 0)
								{
									if(phasetwo <= uiDiff)
									{
										me->SummonCreature(
									}
									else
									phasetwo -= uiDiff;

									geyser = 1;
								}

								if(me->HealthBelowPct(33) && geyser == 1);
								{
									if(phasetwo <= uiDiff)
									{
									}
									else
									phasetwo -= uiDiff;
									geyser = 2;
								}



                            }
     
     
     
     
                    };


    };
     
    void AddSC_lady_nazjar()
    {
            new lady_nazjar();
    }

