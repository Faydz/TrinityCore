/*
 * Copyright (C) 2012 - 2013 Forgotten Lands <https://www.forgottenlands.eu>
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
#include "bastion_of_twilight.h"

enum spells 
{
    SPELL_WRACK                                   = 89421,
    SPELL_WRACK_JUMP                              = 89435,
    SPELL_FLAME_BREATH                            = 90125,
    SPELL_TWILIGHT_SLICER                         = 92851,
    SPELL_TWILIGHT_PULSE                          = 92957,
};

enum events
{
    EVENT_WRACK = 1,
    EVENT_FLAME_BREATH,
    EVENT_TWILIGHT_SLICER,
    EVENT_RESET_ORBS,
};

enum sharedDatas
{
    DATA_PRIVATE_ORB0 = 0,
};

class boss_sinestra : public CreatureScript
{
    public:
        boss_sinestra() : CreatureScript("boss_sinestra") {}

        struct boss_sinestraAI : public BossAI
        {
            boss_sinestraAI(Creature * creature) : BossAI(creature, DATA_SINESTRA)
            {
                instance = me->GetInstanceScript();
            }

            InstanceScript* instance;
            EventMap events;
            Creature* orbs[2];

            void Reset()
            {
                if (instance)
                    instance->SetData(DATA_SINESTRA_EVENT, NOT_STARTED);
                
                events.Reset();

                orbs[0] = NULL;
                orbs[1] = NULL;
            }

            void EnterCombat(Unit* /*who*/)
            {
                DoZoneInCombat(me);

                if (instance)
                    instance->SetData(DATA_SINESTRA_EVENT, IN_PROGRESS);

                events.ScheduleEvent(EVENT_WRACK, 15000);
                events.ScheduleEvent(EVENT_FLAME_BREATH, 20000);
                events.ScheduleEvent(EVENT_TWILIGHT_SLICER, 28000);
            }

            void JustDied(Unit* killer)
            {
                if (instance)
                    instance->SetData(DATA_SINESTRA_EVENT, DONE);
            }

            uint64 GetData64(uint32 type)
            {
                switch (type)
                {
                    case DATA_PRIVATE_ORB0: 
                        if (orbs[0])
                            return orbs[0]->GetGUID();
                        break;
                }

                return 0;
            }
            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);
                
                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_WRACK:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0.0f, 100.0f, true, 0))
                                DoCast(target, SPELL_WRACK, true);
                            
                            events.ScheduleEvent(EVENT_WRACK, urand(75000, 80000));
                            break;
                        case EVENT_FLAME_BREATH:
                            DoCastAOE(SPELL_FLAME_BREATH);

                            events.ScheduleEvent(EVENT_FLAME_BREATH, 20000);
                            break;
                        case EVENT_TWILIGHT_SLICER:
                            for (uint8 i = 0; i < 2; i++)
                            {
                                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0.0f, 100.0f, true, 0))
                                {
                                    Position pos;
                                    target->GetPosition(&pos);
                                    if (Creature* orb = me->SummonCreature(49863, pos, TEMPSUMMON_TIMED_DESPAWN, 15500, 0))
                                    {
                                        if (!orbs[0]) 
                                            orbs[0] = orb;
                                        else
                                            orbs[1] = orb;

                                        orb->AddThreat(target, 100000.0f);
                                        orb->Attack(target, true);

                                        // Damaging aura
                                        if (orbs[1] && orbs[0])
                                            orb->CastSpell(orbs[0], SPELL_TWILIGHT_SLICER, true);

                                        // We Love my little hacks :D
                                        orb->ClearUnitState(UNIT_STATE_CASTING);
                                        orb->GetMotionMaster()->MoveChase(target);
                                        
                                        // Twilight pulse!
                                        orb->CastSpell(orb, SPELL_TWILIGHT_PULSE, true);

                                        // Fixate
                                        // We need to research this spell..
                                    }
                                }
                            }
                            events.ScheduleEvent(EVENT_RESET_ORBS, 18000);
                            events.ScheduleEvent(EVENT_TWILIGHT_SLICER, 28000);
                            break;
                        case EVENT_RESET_ORBS:
                            orbs[0] = NULL;
                            orbs[1] = NULL;
                            break;
                        default:
                            break;
                    }                
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_sinestraAI(creature);
        }
};

class spell_sinestra_wreck : public SpellScriptLoader
{
    public:
        spell_sinestra_wreck() : SpellScriptLoader("spell_sinestra_wreck") { }

        class spell_sinestra_wreck_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_sinestra_wreck_AuraScript);
                            
            void HandleShareBuff (AuraEffect const* aurEff, AuraEffectHandleModes mode)
            {
                if (!GetTargetApplication())
                    return;

                if (!GetTargetApplication()->GetBase())
                    return;

                if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_ENEMY_SPELL)
                {
                    if (Unit* target = GetTarget())
                    {
                        CustomSpellValues values;
                        values.AddSpellMod(SPELLVALUE_MAX_TARGETS, 2);
                        values.AddSpellMod(SPELLVALUE_BASE_POINT1, GetTargetApplication()->GetBase()->GetDuration());
                        GetTarget()->CastCustomSpell(SPELL_WRACK_JUMP, values, NULL, TRIGGERED_FULL_MASK, NULL, NULL, GetCasterGUID());
                    }
                }
            }

            void Register()
            {
                AfterEffectRemove += AuraEffectRemoveFn(spell_sinestra_wreck_AuraScript::HandleShareBuff, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_sinestra_wreck_AuraScript();
        }
};


class spell_sinestra_wrack_jump : public SpellScriptLoader
{
    public:
        spell_sinestra_wrack_jump() :  SpellScriptLoader("spell_sinestra_wrack_jump") { }

        class spell_sinestra_wrack_jump_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sinestra_wrack_jump_SpellScript);

            void SelectTarget(std::list<WorldObject*>& targets)
            {
                targets.remove(GetCaster());
                targets.sort(Trinity::ObjectDistanceOrderPred(GetCaster()));

                if (targets.size() < 3)
                    return;

                targets.resize(2);
            }

            void Hit()
            {
                if (!GetHitUnit())
                    return;

                if (!GetCaster())
                    return;               

                if (!GetOriginalCaster())
                    return;

                if (Aura* debuff = GetOriginalCaster()->AddAura(89421, GetHitUnit()))
                {
                    if (!GetSpellValue())
                        return;

                    int32 duration = GetSpellValue()->EffectBasePoints[1];
                    debuff->SetDuration(duration, false);
                }
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sinestra_wrack_jump_SpellScript::SelectTarget, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sinestra_wrack_jump_SpellScript::SelectTarget, EFFECT_1, TARGET_UNIT_SRC_AREA_ENTRY);
                BeforeHit += SpellHitFn(spell_sinestra_wrack_jump_SpellScript::Hit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sinestra_wrack_jump_SpellScript();
        }
};

class OrientationCheck : public std::unary_function<Unit*, bool>
{
    public:
        explicit OrientationCheck(Unit* _orb1, Unit* _orb2) : orb1(_orb1), orb2(_orb2) { }
        bool operator()(WorldObject* object)
        {
            return !object->IsInBetween(orb1, orb2, 2.0f);
        }

    private:
        Unit* orb1;
        Unit* orb2;
};

class spell_sinestra_twilight_slicer : public SpellScriptLoader
{
    public:
        spell_sinestra_twilight_slicer() :  SpellScriptLoader("spell_sinestra_twilight_slicer") { }

        class spell_sinestra_twilight_slicer_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sinestra_twilight_slicer_SpellScript);

            void SelectTarget(std::list<WorldObject*>& targets)
            {
                // Select Other orb, and filter targets between twos
                if (Unit* orb0 =  GetCaster()->FindNearestCreature(GetCaster()->GetEntry(), 100.0f, true))
                    targets.remove_if(OrientationCheck(GetCaster(), orb0));
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sinestra_twilight_slicer_SpellScript::SelectTarget, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sinestra_twilight_slicer_SpellScript();
        }
};

void AddSC_boss_sinestra()
{
    new boss_sinestra();
    new spell_sinestra_wreck();
    new spell_sinestra_wrack_jump();
    new spell_sinestra_twilight_slicer();
}