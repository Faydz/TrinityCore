/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

 /* ScriptData
SDName: boss_falric
SDComment: new script for tc implementation.
SDCategory: Halls of Reflection
EndScriptData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "halls_of_reflection.h"

enum Yells
{
    SAY_FALRIC_AGGRO            = -1668050,
    SAY_FALRIC_DEATH            = -1668053,
    SAY_FALRIC_SLAY01           = -1668051,
    SAY_FALRIC_SLAY02           = -1668052,
    SAY_FALRIC_SP01             = -1668054,
    SAY_FALRIC_SP02             = -1668055,
};

enum Spells
{
    SPELL_HOPELESSNESS          = 72395,
    SPELL_IMPENDING_DESPAIR     = 72426,
    SPELL_DEFILING_HORROR_N     = 72435,
    SPELL_DEFILING_HORROR_H     = 72452,
    SPELL_QUIVERING_STRIKE_N    = 72422,
    SPELL_QUIVERING_STRIKE_H    = 72453,
    SPELL_BERSERK               = 47008,
};

class boss_falric : public CreatureScript
{
public:
    boss_falric() : CreatureScript("boss_falric") { }

    struct boss_falricAI : public ScriptedAI
    {
        boss_falricAI(Creature *pCreature) : ScriptedAI(pCreature)
       {
            m_pInstance = (InstanceScript*)pCreature->GetInstanceScript();
            Regular = pCreature->GetMap()->IsRegularDifficulty();
            Reset();
       }

       InstanceScript* m_pInstance;
       bool Regular;
       bool m_bIsCall;
       //FUNCTIONS
       uint32 BerserkTimer;
       uint32 GrowlTimer;
       uint32 HorrorTimer;
       uint32 StrikeTimer;
       uint32 SummonTimer;
       uint32 LocNo;
       uint64 SummonGUID[16];
       uint32 CheckSummon;

       uint8 SummonCount;

       uint64 pSummon;

        void Reset()
        {
          BerserkTimer = 180000;
          SummonCount = 0;
          m_bIsCall = false;
          GrowlTimer = 20000;
          HorrorTimer = urand(14000,20000);
          StrikeTimer = 2000;
          SummonTimer = 10000;
          me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
          me->SetVisible(false);
        }

        void EnterCombat(Unit* pVictim)
        {
          //me->RemoveFlag(MOVEFLAG_WALK, NULL);
          DoScriptText(SAY_FALRIC_AGGRO, me);
          DoCast(me, SPELL_HOPELESSNESS);
        }

        void KilledUnit(Unit* pVictim)
        {
            switch(urand(0,1))
            {
                case 0: DoScriptText(SAY_FALRIC_SLAY01, me); break;
                case 1: DoScriptText(SAY_FALRIC_SLAY02, me); break;
            }
        }

        void JustDied(Unit* pKiller)
        {
          if(!m_pInstance) return;
             m_pInstance->SetData(DATA_MARWYN_EVENT, SPECIAL);
          DoScriptText(SAY_FALRIC_DEATH, me);
        }

        void AttackStart(Unit* who)
        {
            if(!m_pInstance) return;

               if(m_pInstance->GetData(DATA_FALRIC_EVENT) != IN_PROGRESS)
                 return;

             ScriptedAI::AttackStart(who);
        }

        void Summon()
        {
             LocNo = 0;

             for(uint8 i = 0; i < 14; i++)
             {
                switch(urand(0,3))
                {
                   case 0:
                       switch(urand(1, 3))
                       {
                         case 1: pSummon = NPC_DARK_1; break;
                         case 2: pSummon = NPC_DARK_3; break;
                         case 3: pSummon = NPC_DARK_6; break;
                       }
                       break;
                   case 1:
                       switch(urand(1, 3))
                       {
                         case 1: pSummon = NPC_DARK_2; break;
                         case 2: pSummon = NPC_DARK_3; break;
                         case 3: pSummon = NPC_DARK_4; break;
                       }
                       break;
                   case 2:
                       switch(urand(1, 3))
                       {
                         case 1: pSummon = NPC_DARK_2; break;
                         case 2: pSummon = NPC_DARK_5; break;
                         case 3: pSummon = NPC_DARK_6; break;
                       }
                       break;
                   case 3:
                       switch(urand(1, 3))
                       {
                         case 1: pSummon = NPC_DARK_1; break;
                         case 2: pSummon = NPC_DARK_5; break;
                         case 3: pSummon = NPC_DARK_4; break;
                       }
                       break;
                 }

                 CheckSummon = 0;

                 if(Creature* Summon = me->SummonCreature(pSummon, SpawnLoc[LocNo].x, SpawnLoc[LocNo].y, SpawnLoc[LocNo].z, SpawnLoc[LocNo].o, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30000))
                 {
                    SummonGUID[i] = Summon->GetGUID();
                    Summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    Summon->setFaction(974);
                    Summon->SetReactState(REACT_PASSIVE);
                 }
                 LocNo++;
             }
        }

        void CallFallSoldier()
        {
             for(uint8 i = 0; i < 4; i++)
             {
                if(Creature* Summon = m_pInstance->instance->GetCreature(SummonGUID[CheckSummon]))
                {
                   Summon->setFaction(14);
                   Summon->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                   Summon->SetReactState(REACT_AGGRESSIVE);
                   Summon->SetInCombatWithZone();
                }
                CheckSummon++;
             }
        }

        void AddWave()
        {
            m_pInstance->DoUpdateWorldState(WORLD_STATE_HOR, 1);
            m_pInstance->DoUpdateWorldState(WORLD_STATE_HOR_WAVE_COUNT, SummonCount);
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if(!m_pInstance) return;

            if (m_pInstance->GetData(DATA_FALRIC_EVENT) == SPECIAL)
            {
                if(!m_bIsCall)
                {
                   m_bIsCall = true;
                   Summon();
                }

                if (SummonTimer < uiDiff)
                {
                        ++SummonCount;
                        AddWave();
                        if(SummonCount > 4)
                        {
                            m_pInstance->SetData(DATA_FALRIC_EVENT, IN_PROGRESS);
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                            me->SetInCombatWithZone();
                        }
                        else CallFallSoldier();
                        SummonTimer = 60000;
                } else SummonTimer -= uiDiff;
            }

            if (!UpdateVictim())
                return;

            if(StrikeTimer < uiDiff)
            {
                DoCast(me->getVictim(), Regular ? SPELL_QUIVERING_STRIKE_N : SPELL_QUIVERING_STRIKE_H);
                StrikeTimer = (urand(7000, 14000));
            }
            else StrikeTimer -= uiDiff;

            if(HorrorTimer < uiDiff)
            {
                DoScriptText(SAY_FALRIC_SP01, me);
                if(Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                   DoCast(pTarget, SPELL_IMPENDING_DESPAIR);
                HorrorTimer = (urand(15000, 25000));
            }
            else HorrorTimer -= uiDiff;

            if(GrowlTimer < uiDiff)
            {
                DoScriptText(SAY_FALRIC_SP02, me);
                DoCast(me->getVictim(), Regular ? SPELL_DEFILING_HORROR_N : SPELL_DEFILING_HORROR_H);
                GrowlTimer = (urand(25000, 30000));
            }
            else GrowlTimer -= uiDiff;

            if (BerserkTimer < uiDiff)
            {
                DoCast(me, SPELL_BERSERK);
                BerserkTimer = 180000;
            } else BerserkTimer -= uiDiff;

            DoMeleeAttackIfReady();

            return;
        }
    };
    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_falricAI(pCreature);
    }
};

void AddSC_boss_falric()
{
    new boss_falric();
}