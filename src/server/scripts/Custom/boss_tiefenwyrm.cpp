#include "ScriptPCH.h"

enum Texts
{
	EMOTE_SWARMING_SHADOWS			= 5,
};

enum Spells
{
	SPELL_DEEPFREEZE				= 27808,
	SPELL_TAIL						= 71077,
	SPELL_BLIZZARD					= 41482,
	SPELL_FROSTATEM					= 69649,
	SPELL_DEATH_AND_DECAY           = 71001,
	SPELL_SWARMING_SHADOWS          = 71264,
	SPELL_ENRAGE					= 41924		//Nach 10 Minuten
};
class boss_tiefenwyrm : public CreatureScript
{
public:
    boss_tiefenwyrm() : CreatureScript("boss_tiefenwyrm") { }

    

    struct boss_tiefenwyrmAI : public ScriptedAI
    {
        boss_tiefenwyrmAI (Creature *c) : ScriptedAI(c)
        { }
		uint32 t_deep;
		uint32 t_tail;
		uint32 t_blizzard;
		uint32 t_frost;
		uint32 t_enrage;
		uint32 t_dad;
		uint32 t_shadows;

        void Reset()
        {
		t_deep = 5000;
		t_tail = 1000;
		t_blizzard = 25000;
		t_frost = 40000;
		t_enrage = 450000;
		t_dad = 30000;
		t_shadows = 60000;
		}

        void EnterCombat(Unit* /*who*/)
        {
			me->MonsterYell("Ich werde euch verschlingen!", 0, 0);
		}

        void JustDied(Unit* /*killer*/)
        {

	}
      
        void KilledUnit(Unit *)
        { 
			switch (urand(1,3))
			 {
				case 1:
					me->MonsterYell("Das war zu einfach!", 0, 0);
				break;

				case 2:
					me->MonsterYell("Ihr seid zu schwach!", 0, 0);
				break;

				case 3:
					me->MonsterYell("Schon m\303\274de?", 0, 0);
				break;
			 }
		}
        
        void UpdateAI(uint32 const diff)
        {
			if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

			 if (!UpdateVictim())
                         return;

			if (t_enrage <= diff)
			{
				DoCast(me, SPELL_ENRAGE);
				t_enrage = 450000;
			} else t_enrage -= diff;

			if (t_frost <= diff)
			{
				DoCast(me->getVictim(), SPELL_FROSTATEM);
				t_frost = 40000;
			} else t_frost -= diff;

			if (t_dad <= diff)
			{
				if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                   DoCast(target, SPELL_DEATH_AND_DECAY);
				t_dad = urand (25000, 30000);
			} else t_dad -= diff;

			if (t_shadows <= diff)
			{
				if (Player* target = SelectRandomTarget(false))
                   {
                    Talk(EMOTE_SWARMING_SHADOWS, target->GetGUID());
                    DoCast(target, SPELL_SWARMING_SHADOWS);
                   }
				t_shadows = 50000;
			} else t_shadows -= diff;

			if (t_blizzard <= diff)
			{
				DoCastAOE(SPELL_BLIZZARD, true);
				t_blizzard = 16000;
			} else t_blizzard -= diff;
			
			/*if (t_tail <= diff)
			{
				DoCast(me->getVictim(), SPELL_TAIL);
				t_tail = urand(2000, 4000);
			} else t_tail -= diff;*/

			if (t_deep <= diff)
			{
                 DoCast(me->getVictim(), SPELL_DEEPFREEZE);
                 t_deep = 45000;
            } else t_deep -= diff;

			
			DoMeleeAttackIfReady();
        }
    };
	
CreatureAI* GetAI(Creature* pCreature) const
{
     return new boss_tiefenwyrmAI (pCreature);
}

};

void AddSC_boss_tiefenwyrm()
{
    new boss_tiefenwyrm();
}