/*
* Copyright (C) 2012 - 2013 Forgotten Lands <http://www.forgottenlands.eu/>
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

#include "ScriptPCH.h"
#include "blackwing_descent.h"

enum Events
{
    // Groundphase
    EVENT_SONAR_PULSE = 1,
    EVENT_MODULATION,
    EVENT_SONIC_BREATH,
    EVENT_SEARING_FLAMES,
    EVENT_REMOVE_TRACK,
};

enum Spells
{
    SPELL_SOUND_BAR_APPLY                         = 89683,
    SPELL_SOUND_BAR                               = 88824,
    SPELL_MODULATION                              = 77612,
    SPELL_SONIC_BREATH                            = 78098,
    SPELL_TRACKING                                = 78092,
    SPELL_SEARING_FLAMES                          = 77840,
};

class boss_atramedes : public CreatureScript
{
public:
    boss_atramedes() : CreatureScript("boss_atramedes") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_atramedesAI(creature);
    }

    struct boss_atramedesAI : public BossAI
    {
        boss_atramedesAI(Creature* creature) : BossAI(creature, DATA_ATRAMEDES), summons(me)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        SummonList summons;

        void Reset()
        {
            _Reset();
            summons.DespawnAll();

            if (instance)
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_SOUND_BAR);
        }

        void EnterCombat(Unit* /*who*/)
        {
            me->AddAura(SPELL_SOUND_BAR_APPLY, me);

            events.ScheduleEvent(EVENT_SONAR_PULSE, 12000);
            events.ScheduleEvent(EVENT_MODULATION,  10000);
            events.ScheduleEvent(EVENT_SONIC_BREATH, 25000);
            events.ScheduleEvent(EVENT_SEARING_FLAMES, 40000);
            _EnterCombat();
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SONAR_PULSE:
                        // Send 4 / 8 Discs to random players
                        for (int i = 0; i < RAID_MODE(4, 8); i++)
                        {
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true, 0))
                            {
                                Position pos;
                                me->GetPosition(&pos);
                                if (Creature* sonar = me->SummonCreature(49623, pos, TEMPSUMMON_TIMED_DESPAWN, 12000, 0))
                                {
                                    sonar->SetReactState(REACT_PASSIVE);
                                    sonar->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                                    float ownerOrientation = me->GetAngle(target->GetPositionX(), target->GetPositionY());
                                    sonar->GetMotionMaster()->MovePoint(0, sonar->GetPositionX() + 120 / 2 * cos(ownerOrientation), sonar->GetPositionY() + 120 / 2 * sin(ownerOrientation), sonar->GetPositionZ());
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_SONAR_PULSE, 12000);
                        break;
                    case EVENT_MODULATION:
                        DoCastAOE(SPELL_MODULATION, true);
                        events.ScheduleEvent(EVENT_MODULATION,  18000);
                        break;
                    case EVENT_SONIC_BREATH:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true, 0))
                        {
                            me->AddAura(SPELL_TRACKING, target);
                            Position pos;
                            target->GetPosition(&pos);
                            if (Creature* trackMob = me->SummonCreature(41879, pos, TEMPSUMMON_TIMED_DESPAWN, 6500, 0))
                            {
                                trackMob->Attack(target, true);
                                trackMob->AddThreat(target, 10000.0f);
                                trackMob->GetMotionMaster()->MoveFollow(target, 0.5f, 0.0f);
                                DoCastAOE(SPELL_SONIC_BREATH);
                            }
                            
                            events.ScheduleEvent(EVENT_SONIC_BREATH, 40000);
                            events.ScheduleEvent(EVENT_REMOVE_TRACK, 6500);
                        }
                        break;
                    case EVENT_REMOVE_TRACK:
                        if (instance)
                            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TRACKING);
                        break;
                    case EVENT_SEARING_FLAMES:
                        DoCastAOE(SPELL_SEARING_FLAMES);
                        events.ScheduleEvent(EVENT_SEARING_FLAMES, 40000);
                        break;
                    default:
                        break;
                }
            }		

            DoMeleeAttackIfReady();
        }

        void JustSummoned(Creature* summon)
        {
            summons.Summon(summon);

            switch (summon->GetEntry())
            {
                case 41807:
                    summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                    summon->SetReactState(REACT_PASSIVE);
                    break;
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            summons.DespawnAll();

            _JustDied();

            if (instance)
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_SOUND_BAR);
        }
    };
};

class npc_sonar_pulse : public CreatureScript
{
    public:
        npc_sonar_pulse() : CreatureScript("npc_sonar_pulse") { }
 
        struct npc_sonar_pulseAI : public ScriptedAI
        {
            npc_sonar_pulseAI(Creature* creature) : ScriptedAI(creature)
            { }

            void Reset()
            {
                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
            }
           
            void UpdateAI(uint32 diff)
            {
                // We need this shit to prevent mob do melee attacks -.-
            }

        };
 
        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_sonar_pulseAI(creature);
        }
};

class npc_tracking_flames : public CreatureScript
{
    public:
        npc_tracking_flames() : CreatureScript("npc_tracking_flames") { }
 
        struct npc_tracking_flamesAI: public ScriptedAI
        {
            npc_tracking_flamesAI(Creature* creature) : ScriptedAI(creature)
            { }

            void Reset()
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                me->SetSpeed(MOVE_WALK, 0.8f);
                me->SetSpeed(MOVE_RUN, 0.8f);
            }
           
            void UpdateAI(uint32 diff)
            {
                // We need this shit to prevent mob do melee attacks -.-
            }

        };
 
        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_tracking_flamesAI(creature);
        }
};

class npc_ancient_dwarven_shield : public CreatureScript
{
    public:
        npc_ancient_dwarven_shield() : CreatureScript("npc_ancient_dwarven_shield") { }


        bool OnGossipHello(Player* player, Creature* creature)
        {
            if (InstanceScript* instance = player->GetInstanceScript())
            {
                instance->DoSetPowerOnPlayers(POWER_ALTERNATE_POWER, -1);
                if (Creature* atramedes = ObjectAccessor::GetCreature(*creature, instance->GetData64(BOSS_ATRAMEDES)))
                    atramedes->InterruptNonMeleeSpells(false, 0, true, false);
            }

            creature->CastSpell(creature, 77611, true);
            creature->DisappearAndDie();

            return true;
        }
};



void AddSC_boss_atramedes()
{
    new boss_atramedes();
    new npc_sonar_pulse();
    new npc_tracking_flames();
    new npc_ancient_dwarven_shield();
}