#include "ScriptPCH.h"

enum Spells
{
	SPELL_DEEPFREEZE				= 70157,
	SPELL_TAIL						= 71077,
	SPELL_BLIZZARD					= 41482,
	SPELL_FROSTATEM					= 69649,
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

        void Reset()
        {
		t_deep = 5000;
		t_tail = 1000;
		t_blizzard = 25000;
		t_frost = 40000;
		t_enrage = 450000;
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