	

    #include "ScriptMgr.h"
    #include "ScriptedCreature.h"
    #include "ScriptedGossip.h"
    #include "Player.h"
     
     
    enum Yells
    {
    };
     
    enum Spells
    {
		SPELL_PARALYSIS			=	84030,
		SPELL_ROAR				=	86169,
		SPELL_FRENZIED			=	83693,
		SPELL_MALOVOLENT		=	83908,
		SPELL_FRENZY			=	82396
    };
     
    class boss_halfus : public CreatureScript
    {
            public:
                    boss_halfus() : CreatureScript("boss_halfus") {}
     
                    struct boss_creatureAI : public ScriptedAI
                    {
								uint32 t_para;
								uint32 t_frenzy;
								uint32 t_roar;
								uint32 t_frenzied;
								uint32 t_malovolent;

							

                            void Reset() OVERRIDE
                            {
								t_para = 10000;
								t_frenzy = 360000;
								t_roar = 15000;
								t_frenzied = 30000;
								t_malovolent = 12000;

                            }
     
                            void EnterCombat(Unit* who) OVERRIDE
                            {

                            }
     
                            void UpdateAI(uint32 uiDiff) OVERRIDE
                            {

								if(t_frenzy <= uiDiff)
								{
									DoCast(me, SPELL_FRENZY);
									t_frenzy = 180000;
								}
								else
								{
									t_frenzy -= uiDiff;
								}

								if(t_malovolent <= uiDiff)
								{
									DoCast(me->GetVictim(), SPELL_MALOVOLENT);
									t_malovolent = urand(10000, 18000);
								}
								else
								{
									t_malovolent -= uiDiff;
								}

								if(t_frenzied <= uiDiff)
								{
									DoCast(me, SPELL_FRENZIED);
									t_frenzied = 500000;
								}
								else
								{
									t_frenzied -= uiDiff;
								}

								DoMeleeAttackIfReady();


                            }
     
     
     
     
                    };


    };
     
    void AddSC_boss_halfus()
    {
            new boss_halfus();
    }

