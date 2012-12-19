#include "ScriptPCH.h"

enum Spells
{
	SPELL_DEATHANDDECAY			= 61603,
	SPELL_FROSTBOLT				= 33463,
	SPELL_HELLRAIN				= 38917
};

enum Adds
{
	ADD_GHUL					= 31812
};
class boss_arkton : public CreatureScript
{
public:
    boss_arkton() : CreatureScript("boss_arkton") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_arktonAI (pCreature);
    }

    struct boss_arktonAI : public ScriptedAI
    {
        boss_arktonAI (Creature *c) : ScriptedAI(c)
        { 
		}

		uint32 t_ddc;
		uint32 t_frostbolt;
		uint32 t_hellrain;
		uint32 t_add;

        void Reset()
        {
			t_ddc = 20000;
			t_frostbolt = 3000;
			t_hellrain = 25000;
			t_add = 5000;
		}

        void EnterCombat(Unit* /*who*/)
        { 
			me->MonsterYell("Hahaha! Euer Weihnachten wird nie wieder das sein, was es einmal war!", 0, 0);
			me->MonsterYell("Ich werde euch alle toeten!", 0, 0);
		}

        void JustDied(Unit* /*killer*/)
        { 
			me->MonsterYell("Ich... habe... versagt... wartet bis... der naechste... Schnee... ko..", 0, 0);
		}
      
        void KilledUnit(Unit *)
        { 
			me->MonsterYell("Das war viel zu einfach!", 0, 0);
		}
        
        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

			if (t_ddc <= diff)
			{
				DoCast(me->getVictim(), SPELL_DEATHANDDECAY);
				me->MonsterYell("Ich bringe Verderben!", 0, 0);
				t_ddc = urand(20000,30000);
			}
			else t_ddc -= diff;

			if (t_hellrain <= diff)
			{
				DoCast(me->getVictim(), SPELL_HELLRAIN);

				switch (urand(1,3))
				{
					case 1:
						me->MonsterYell("Spuert das Hoellenfeuer!", 0, 0);
						break;
					case 2:
				me->MonsterYell("Haha! Dachtet ihr etwa ich kann nur Schnee?", 0, 0);
						break;
					case 3:
						me->MonsterYell("Jaaa! Verbreeeeennt!", 0, 0);
						break;
				}

				t_hellrain = urand(25000,35000);
			}
			else t_hellrain -= diff;
			
			if (t_frostbolt <= diff)
			{
				DoCast(me->getVictim(), SPELL_FROSTBOLT);
				t_frostbolt = urand(3000,5000);
			}
			else t_frostbolt -= diff;

			if (t_add <= diff)
			{
				me->SummonCreature (ADD_GHUL, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ());
				t_add = 7500;
			}
			else t_add -= diff;

			DoMeleeAttackIfReady(); 
        }
    };

};

void AddSC_boss_arkton()
{
    new boss_arkton();
}