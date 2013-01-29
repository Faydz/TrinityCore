#include "ScriptPCH.h"

enum Spells
{
	SPELL_DEEPFREEZE				= 60511,
	SPELL_TAIL						= 58957,
	SPELL_BLIZZARD					= 41482,
	SPELL_FROSTATEM					= 72641,
	SPELL_ENRAGE					= 41924		//Nach 10 Minuten
};
class boss_tiefenwyrm : public CreatureScript
{
public:
    boss_tiefenwyrm() : CreatureScript("boss_tiefenwyrm") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_tiefenwyrmAI (pCreature);
    }

    struct boss_tiefenwyrmAI : public ScriptedAI
    {
        boss_tiefenwyrmAI (Creature *c) : ScriptedAI(c)
        { }

		uint32 t_deep = 20000;
		uint32 t_tail = 8000;
		uint32 t_blizzard = 25000;
		uint32 t_Frost = 40000;
		uint32 t_enrage = 600000;
        void Reset()
        {
		
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
        
        void UpdateAI(const uint32 diff)
        {
			 if (!UpdateVictim())
                return;

			if (t_enrage <= diff)
			{
				DoCast(me, SPELL_ENRAGE);
				t_enrage = 300000;
			} else t_enrage -= diff;

			if (t_deep <= diff)
			{
                DoCast(me->getVictim(), SPELL_DEEPFREEZE);
                t_deep = 20000;
            } else t_deep -= diff;

			if (t_tail <= diff)
			{
				DoCast(me->getVictim(), SPELL_TAIL);
				t_tail = 4000;
			} else t_tail -= diff;

			if (t_blizzard <= diff)
			{
				DoCast(me->getVictim(), SPELL_BLZZARD);
				t_blizzard = 16000;
			} else t_blizzard -= diff;

			if (t_frost <= diff)
			{
				DoCast(me->getVictim(), SPELL_FROST);
				t_frost = 40000;
			} else t_frost -= diff;
        }
    };

};

void AddSC_boss_tiefenwyrm()
{
    new boss_tiefenwyrm();
}