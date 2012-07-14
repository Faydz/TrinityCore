/////////////////////////////////////////////////////////////////////
//	DT_Ini Boss
//
//	Boss Nr 01 Viertel 02
//	Der Schwarze Doktor	
//
//	made by gizmo.ms
/////////////////////////////////////////////////////////////////////

#include "ScriptPCH.h"

enum DoktorSpells
{
    SPELL_ENRAGE			= 47008,
    SPELL_ANTIAGGRO			= 29232,
    SPELL_BENOMMEN		    = 38767,
    SPELL_SAURESALVE		= 70273,
    SPELL_GIFTPFUETZE		= 70274
};

enum Adds
{
	ADD_WURM				= 200016
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
        boss_der_schwarzedoktorAI (Creature *c) : ScriptedAI(c)
        { }
		
		uint32 t_antiaggro;
		uint32 t_benommen;
		uint32 t_sauresalve;
		uint32 t_giftpfuetze;
		uint32 t_enrage;

		uint32 t_add;

		uint32 Phase;
		
        void Reset()
        {
			t_antiaggro = 3000;
	        t_benommen = 15000;
			t_sauresalve = 10000;
			t_giftpfuetze = 0;
			t_enrage = 240000;
			t_add = 30000;

			Phase = 1;
        }

        void EnterCombat(Unit* /*who*/)
        {
           me->MonsterYell("tttteeeessssttttt", 0, 0);
           me->MonsterYell("So spuert meinen Zorn", 0, 0);
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
                        me->MonsterYell("testest", 0, 0);
                   break;
                   case 2:
                       me->MonsterYell("Ihr seid zu schwach!", 0, 0);
                   break;
                   case 3:
                       me->MonsterYell("Schon muede?", 0, 0);
                  break;
             }
        }
        
        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

			if (((me->GetHealth()*100 / me->GetMaxHealth()) < 55) && (Phase == 1))
			{
				Phase = 2;
			}

			if (Phase ==1)
			{
				if (t_antiaggro <= diff)
				{
					DoCast(me->getVictim(), SPELL_ANTIAGGRO);
				} else t_antiaggro -= diff;
			  
				if (t_benommen <= diff)
				{
					if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, true))
					DoCast(pTarget, SPELL_BENOMMEN);
					t_benommen = 30000;
				} else t_benommen -= diff;
			           						         
				if (t_sauresalve <= diff)
				{
					if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, true))
					DoCast(pTarget, SPELL_SAURESALVE);
					t_sauresalve = 20000;
				} else t_sauresalve -= diff;

				if (t_enrage <= diff)
				{
					DoCast(me->getVictim(), SPELL_ENRAGE);
				} else t_enrage -= diff;

				if (t_add <= diff)
				{
					if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, true))
					me->SummonCreature (ADD_WURM, pTarget->GetPositionX(), pTarget->GetPositionY(), pTarget->GetPositionZ());
					if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, true))
					me->SummonCreature (ADD_WURM, pTarget->GetPositionX(), pTarget->GetPositionY(), pTarget->GetPositionZ());
					if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, true))
					me->SummonCreature (ADD_WURM, pTarget->GetPositionX(), pTarget->GetPositionY(), pTarget->GetPositionZ());
					t_add = 25000;
				} else t_add -= diff;
					
				
				DoMeleeAttackIfReady();
			}

			if (Phase == 2)
			{
				if (t_giftpfuetze <= diff)			
				{
					DoCast(me->getVictim(), SPELL_GIFTPFUETZE);
					t_giftpfuetze = 7000;
				} else t_giftpfuetze -= diff;

				if (t_enrage <= diff)
				{
					DoCast(me->getVictim(), SPELL_ENRAGE);
				} else t_enrage -= diff;

				if (t_benommen <= diff)
				{
					if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, true))
					DoCast(pTarget, SPELL_BENOMMEN);
					t_benommen = 15000;
				} else t_benommen -= diff;
			           						         
				if (t_sauresalve <= diff)
				{
					if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, true))
					DoCast(pTarget, SPELL_SAURESALVE);
					t_sauresalve = 10000;
				} else t_sauresalve -= diff;

				DoMeleeAttackIfReady();
			}
        }
    };

};

void AddSC_boss_der_schwarzedoktor()
{
    new boss_der_schwarzedoktor();
}