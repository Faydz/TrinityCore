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
SDName: boss_Marwyn
SDComment: new script for tc implementation.
SDCategory: Halls of Reflection
EndScriptData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "halls_of_reflection.h"

enum Yells
{
    SAY_MARWYN_INTRO            = -1594506,
    SAY_MARWYN_AGGRO            = -1668060,
    SAY_MARWYN_DEATH            = -1668063,
    SAY_MARWYN_SLAY01           = -1668061,
    SAY_MARWYN_SLAY02           = -1668062,
    SAY_MARWYN_SP01             = -1668064,
    SAY_MARWYN_SP02             = -1668065,
};

enum Spells
{
    SPELL_OBLITERATE_N          = 72360,
    SPELL_OBLITERATE_H          = 72434,
    SPELL_SHARED_SUFFERING_N    = 72368,
    SPELL_SHARED_SUFFERING_H    = 72369,
    SPELL_WELL_OF_CORRUPTION    = 72362,
    SPELL_CORRUPTED_FLESH_N     = 72363,
    SPELL_CORRUPTED_FLESH_H     = 72436,
    SPELL_BERSERK               = 47008,
};

class boss_marwyn : public CreatureScript
{
public:
    boss_marwyn() : CreatureScript("boss_marwyn") { }

    struct boss_marwynAI : public ScriptedAI
    {
       boss_marwynAI(Creature *pCreature) : ScriptedAI(pCreature)
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
       uint32 SharedSufferingTimer;
       uint32 WellTimer;
       uint32 TouchTimer;
       uint32 FleshTimer;
       uint32 ObliterateTimer;
       uint32 SummonTimer;

       uint32 LocNo;
       uint64 SummonGUID[16];
       uint32 CheckSummon;

       uint8 SummonCount;
       uint8 SummonCountMarwyn;

       uint64 pSummon;

       void Reset()
       {
          BerserkTimer = 180000;
          SharedSufferingTimer = 4000;
          WellTimer = 12000;
          TouchTimer = 8000;
          FleshTimer = 21000;
          ObliterateTimer = 5000;
          SummonCount = 0;
          SummonCountMarwyn = 5;
          m_bIsCall = false;
          SummonTimer = 10000;
          me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
          me->SetVisible(false);
        }

        void Summon()
        {
             LocNo = 14;

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
                    Summon->SetReactState(REACT_PASSIVE);
                    Summon->setFaction(974);
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

        void JustDied(Unit* pKiller)
        {
          if(m_pInstance)
          {
              m_pInstance->SetData(DATA_MARWYN_EVENT, DONE);
              m_pInstance->SetData(DATA_PHASE, 3);
          }

          DoScriptText(SAY_MARWYN_DEATH, me);
        }

        void KilledUnit(Unit* pVictim)
        {
            switch(urand(0,1))
            {
                case 0: DoScriptText(SAY_MARWYN_SLAY01, me); break;
                case 1: DoScriptText(SAY_MARWYN_SLAY02, me); break;
            }
        }

        void EnterCombat(Unit* pVictim)
        {
            if (!m_pInstance) return;
          //me->RemoveFlag(MOVEFLAG_WALK, MOVEMENTFLAG_WALK_MODE);
          DoScriptText(SAY_MARWYN_AGGRO, me);
        }

        void AttackStart(Unit* who)
        {
            if (!m_pInstance) return;

               if (m_pInstance->GetData(DATA_MARWYN_EVENT) != IN_PROGRESS)
                 return;

             ScriptedAI::AttackStart(who);
        }

        void AddWave()
        {
            m_pInstance->DoUpdateWorldState(WORLD_STATE_HOR, 1);
            m_pInstance->DoUpdateWorldState(WORLD_STATE_HOR_WAVE_COUNT, SummonCountMarwyn);
        }

       void UpdateAI(const uint32 uiDiff)
        {
            if(!m_pInstance) return;

            if (m_pInstance->GetData(DATA_FALRIC_EVENT) == SPECIAL)
            {
                if(!m_bIsCall)
                {
                   m_bIsCall = true;
                   ++SummonCountMarwyn;
                   Summon();
                }
            }

            if(m_pInstance->GetData(DATA_MARWYN_EVENT) == SPECIAL)
            {
               if(SummonTimer < uiDiff)
               {
                       AddWave();
                       ++SummonCount;
                       ++SummonCountMarwyn;
                       if(SummonCount == 1)
                          DoScriptText(SAY_MARWYN_INTRO, me);

                       if(SummonCount > 4)
                       {
                            m_pInstance->SetData(DATA_MARWYN_EVENT, IN_PROGRESS);
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            me->SetInCombatWithZone();
                       }
                       else CallFallSoldier();
                       SummonTimer = 60000;
               } else SummonTimer -= uiDiff;
            }

            if(!UpdateVictim())
                return;

            if(ObliterateTimer < uiDiff)
            {
                DoCast(me->getVictim(), Regular ? SPELL_OBLITERATE_N : SPELL_OBLITERATE_H);
                ObliterateTimer = urand(8000, 12000);
            } else ObliterateTimer -= uiDiff;

            if (WellTimer < uiDiff)
            {
                DoScriptText(SAY_MARWYN_SP02, me);
                if(Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                   DoCast(pTarget, SPELL_WELL_OF_CORRUPTION);
                WellTimer= urand(25000, 30000);
            } else WellTimer -= uiDiff;

            if (SharedSufferingTimer < uiDiff)
            {
                if(Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                   DoCast(pTarget, Regular ? SPELL_SHARED_SUFFERING_N : SPELL_SHARED_SUFFERING_H);
                SharedSufferingTimer = urand(15000, 20000);
            } else SharedSufferingTimer -= uiDiff;

            if (FleshTimer < uiDiff)
            {
                DoScriptText(SAY_MARWYN_SP01, me);
                if(Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                    DoCast(pTarget, Regular ? SPELL_CORRUPTED_FLESH_N : SPELL_CORRUPTED_FLESH_H);
                FleshTimer = urand(10000, 16000);
            } else FleshTimer -= uiDiff;

            if(BerserkTimer < uiDiff)
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
        return new boss_marwynAI(pCreature);
    }

};

void AddSC_boss_marwyn()
{
    new boss_marwyn();
}