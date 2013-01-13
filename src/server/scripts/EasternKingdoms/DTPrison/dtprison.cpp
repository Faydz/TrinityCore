/////////////////////////////////////////////////////////////////////
//	DT_Ini Trash
//
//	Trash Nr 01 Viertel 02
//	verseuchter Krieger	
//
//	made by gizmo.ms
/////////////////////////////////////////////////////////////////////

#include "ScriptPCH.h"

enum KriegerSpells
{
    SPELL_SAUREWUNDE		= 40481,
    SPELL_TEUFELSSAUREATEM	= 40508,
    SPELL_BENOMMEN			= 38767
};


class trash_verseuchterkrieger : public CreatureScript
{
public:
    trash_verseuchterkrieger() : CreatureScript("trash_verseuchterkrieger") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new trash_verseuchterkriegerAI (pCreature);
    }

    struct trash_verseuchterkriegerAI : public ScriptedAI
    {
        trash_verseuchterkriegerAI (Creature *c) : ScriptedAI(c)
        { }
		
		uint32 t_saurewunde;
		uint32 t_benommen;
		uint32 t_teufelssaureatem;
		
        void Reset()
        {
            t_saurewunde 		= 3000;
            t_benommen 			= 5000;
            t_teufelssaureatem	= 0;
        }

        void EnterCombat(Unit* /*who*/)
        {
           me->MonsterYell("So sp\303\274rt meinen Zorn", 0, 0);
        }

        void JustDied(Unit* /*killer*/)
        {
          me->MonsterSay("Ich habe versagt...",0,0);
        }
      
        void KilledUnit(Unit *)
        {
             switch (urand(1,3))
             {
               case 1:
                    me->MonsterYell("Haha, das war einfach!", 0, 0);
               break;
               case 2:
                   me->MonsterYell("Ihr seid zu schwach!", 0, 0);
               break;
               case 3:
                   me->MonsterYell("Schon m\303\274ede?", 0, 0);
              break;
             }
        }
        
        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

			if (((me->GetHealth()*100 / me->GetMaxHealth()) < 50))
			{
				if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, true))
				DoCast(pTarget, SPELL_TEUFELSSAUREATEM);
				t_teufelssaureatem = 20000;
			}

			if (t_benommen <= diff)
			{
				if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, true))
				DoCast(pTarget, SPELL_BENOMMEN);
				t_benommen = 10000;
			} else t_benommen -= diff;
			
			if (t_saurewunde <= diff)
			{
				DoCast(me->getVictim(), SPELL_SAUREWUNDE);
				t_saurewunde = 10000;
			} else t_saurewunde -= diff;
			           						         
			DoMeleeAttackIfReady();
		}
    };
};

void AddSC_dtprison()
{
    new trash_verseuchterkrieger();
}