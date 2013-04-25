/*
 * Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
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

/*
 * Scripts for spells with SPELLFAMILY_WARRIOR and SPELLFAMILY_GENERIC spells used by warrior players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_warr_".
 */

#include "Player.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

enum WarriorSpells
{
    SPELL_WARRIOR_BLOODTHIRST                       = 23885,
    SPELL_WARRIOR_BLOODTHIRST_DAMAGE                = 23881,
    SPELL_WARRIOR_CHARGE                            = 34846,
    SPELL_WARRIOR_CHARGE_SPELLBOOK_SPELL            = 100,
    SPELL_WARRIOR_DEEP_WOUNDS_RANK_1                = 12162,
    SPELL_WARRIOR_DEEP_WOUNDS_RANK_2                = 12850,
    SPELL_WARRIOR_DEEP_WOUNDS_RANK_3                = 12868,
    SPELL_WARRIOR_DEEP_WOUNDS_RANK_PERIODIC         = 12721,
    SPELL_WARRIOR_EXECUTE                           = 20647,
    SPELL_WARRIOR_GLYPH_OF_EXECUTION                = 58367,
    SPELL_WARRIOR_GLYPH_OF_VIGILANCE                = 63326,
    SPELL_WARRIOR_IMPROVED_HAMSTRING                = 23694,
    SPELL_WARRIOR_INTERCEPT                         = 20252,
    SPELL_WARRIOR_JUGGERNAUT_CRIT_BONUS_BUFF        = 65156,
    SPELL_WARRIOR_JUGGERNAUT_CRIT_BONUS_TALENT      = 64976,
    SPELL_WARRIOR_LAST_STAND_TRIGGERED              = 12976,
    SPELL_WARRIOR_SLAM                              = 50782,
    SPELL_WARRIOR_SLAM_OFFHAND                      = 50783,
    SPELL_WARRIOR_SWEEPING_STRIKES_EXTRA_ATTACK     = 26654,
    SPELL_WARRIOR_TAUNT                             = 355,
    SPELL_WARRIOR_UNRELENTING_ASSAULT_RANK_1        = 46859,
    SPELL_WARRIOR_UNRELENTING_ASSAULT_RANK_2        = 46860,
    SPELL_WARRIOR_UNRELENTING_ASSAULT_TRIGGER_1     = 64849,
    SPELL_WARRIOR_UNRELENTING_ASSAULT_TRIGGER_2     = 64850,
    SPELL_WARRIOR_VIGILANCE_PROC                    = 50725,
    SPELL_WARRIOR_VIGILANCE_REDIRECT_THREAT         = 59665,

    SPELL_PALADIN_BLESSING_OF_SANCTUARY             = 20911,
    SPELL_PALADIN_GREATER_BLESSING_OF_SANCTUARY     = 25899,
    SPELL_PRIEST_RENEWED_HOPE                       = 63944,
    SPELL_GEN_DAMAGE_REDUCTION_AURA                 = 68066,
};

enum WarriorSpellIcons
{
    WARRIOR_ICON_ID_SUDDEN_DEATH                    = 1989,
    WARRIOR_ICON_ID_IMPROVED_HAMSTRING              = 23,
};

// 76858 Opportunity Strike
class spell_warr_opportunity_strike : public SpellScriptLoader
{
    public:
        spell_warr_opportunity_strike() : SpellScriptLoader("spell_warr_opportunity_strike") { }

        class spell_warr_opportunity_strike_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_opportunity_strike_SpellScript);
            
            void HandleEffect(SpellEffIndex /*effIndex*/)
            {
                if(Unit* caster = GetCaster())
                {
                    int32 damage = caster->CalculateDamage(BASE_ATTACK, false, true);
                    SetHitDamage(damage);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warr_opportunity_strike_SpellScript::HandleEffect, EFFECT_0, SPELL_EFFECT_NORMALIZED_WEAPON_DMG);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_opportunity_strike_SpellScript();
        }
};

// 2457, 71, 2458 Battle, Defensive, Berserker Stance
class spell_warr_stance_handler : public SpellScriptLoader
{
    public:
        spell_warr_stance_handler() : SpellScriptLoader("spell_warr_stance_handler") { }

        class spell_warr_stance_handler_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_stance_handler_SpellScript);
            
            void HandleBeforeCast()
            {
                Unit* caster = GetCaster();

                if(caster)
                {
                    int32 Rage_val = 0;
                    PlayerSpellMap const& sp_list = caster->ToPlayer()->GetSpellMap();

                    // Retrieves max rage to retain
                    for (PlayerSpellMap::const_iterator itr = sp_list.begin(); itr != sp_list.end(); ++itr)
                    {
                        if (itr->second->state == PLAYERSPELL_REMOVED || itr->second->disabled)
                            continue;

                        SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(itr->first);
                        if (spellInfo && spellInfo->SpellFamilyName == SPELLFAMILY_WARRIOR && spellInfo->SpellIconID == 139)
                        {
                            Rage_val += caster->CalculateSpellDamage(caster, spellInfo, EFFECT_0);
                        }
                    }

                    // Check and update (do not forget the * 10 on each SetPower with POWER_RAGE)
                    if (caster->GetPower(POWER_RAGE) > Rage_val * 10)
                    {
                        Rage_val *= sWorld->getRate(RATE_POWER_RAGE_INCOME);

                        caster->SetPower(POWER_RAGE, Rage_val * 10);
                    }
                }
            }

            void Register()
            {
                BeforeCast += SpellCastFn(spell_warr_stance_handler_SpellScript::HandleBeforeCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_stance_handler_SpellScript();
        }
};

// 86346 - Colossus Smash
class spell_warr_colussus_smash : public SpellScriptLoader
{
    public:
        spell_warr_colussus_smash() : SpellScriptLoader("spell_warr_colussus_smash") { }

        class spell_warr_colussus_smash_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warr_colussus_smash_AuraScript);

            void CalculateAmount(AuraEffect const* aurEff, int32& amount, bool& canBeRecalculated)
            {
                if (Unit* target = GetUnitOwner())
                {
                    if(target->GetTypeId() == TYPEID_PLAYER)
                    {
                        // 50% arpen for player
                        amount /= 2;
                    }
                }
            }

            void Register()
            {
                 DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warr_colussus_smash_AuraScript::CalculateAmount, EFFECT_1, SPELL_AURA_BYPASS_ARMOR_FOR_CASTER);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_colussus_smash_AuraScript();
        }
};

// 20252 - Intercept
class spell_warr_intercept : public SpellScriptLoader
{
    public:
        spell_warr_intercept() : SpellScriptLoader("spell_warr_intercept") { }

        class spell_warr_intercept_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_intercept_SpellScript);

            void HandleOnHit()
            {
                SpellInfo const* chargeProto = sSpellMgr->GetSpellInfo(SPELL_WARRIOR_CHARGE_SPELLBOOK_SPELL);
                Unit* caster = GetCaster();

                if (chargeProto && caster && caster->ToPlayer())
                {
                    Player* player = caster->ToPlayer();

                    // Juggernaut charge cd
                    if (caster->HasAura(SPELL_WARRIOR_JUGGERNAUT_CRIT_BONUS_TALENT) && !player->HasSpellCooldown(SPELL_WARRIOR_CHARGE_SPELLBOOK_SPELL))
                    {
                        WorldPacket data(SMSG_SPELL_COOLDOWN, 8 + 1 + 4);
                        data << uint64(player->GetGUID());
                        data << uint8(0x1);                               // flags (0x1, 0x2)
                        data << uint32(chargeProto->Id);
                        // 15 base sec - 2 from talent
                        data << uint32(13000);                              // in m.secs
                        player->GetSession()->SendPacket(&data);
                    }
                }
            }

            void Register()
            {
                
                OnHit += SpellHitFn(spell_warr_intercept_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_intercept_SpellScript();
        }
};

// 1715 - Hamstring
class spell_warr_hamstring : public SpellScriptLoader
{
    public:
        spell_warr_hamstring() : SpellScriptLoader("spell_warr_hamstring") { }

        class spell_warr_hamstring_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warr_hamstring_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARRIOR_IMPROVED_HAMSTRING))
                    return false;
                return true;
            }

            void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                Unit* caster = GetCaster();
                Unit* target = GetTarget();

                if(!caster || !caster->ToPlayer() || !target)
                    return;

                if(AuraEffect* aurEff = caster->GetAuraEffect(SPELL_AURA_PROC_TRIGGER_SPELL, SPELLFAMILY_WARRIOR, WARRIOR_ICON_ID_IMPROVED_HAMSTRING, EFFECT_0))
                {
                    if(!caster->ToPlayer()->HasSpellCooldown(SPELL_WARRIOR_IMPROVED_HAMSTRING))
                    {
                        caster->CastSpell(target, SPELL_WARRIOR_IMPROVED_HAMSTRING, true);
                        caster->ToPlayer()->AddSpellCooldown(SPELL_WARRIOR_IMPROVED_HAMSTRING, NULL, time(NULL) + aurEff->GetAmount());
                    }
                }
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_warr_hamstring_AuraScript::HandleApply, EFFECT_0, SPELL_AURA_MOD_DECREASE_SPEED, AURA_EFFECT_HANDLE_REAPPLY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_hamstring_AuraScript();
        }
};

/// Updated 4.3.4
class spell_warr_bloodthirst : public SpellScriptLoader
{
    public:
        spell_warr_bloodthirst() : SpellScriptLoader("spell_warr_bloodthirst") { }

        class spell_warr_bloodthirst_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_bloodthirst_SpellScript);

            void HandleDamage(SpellEffIndex /*effIndex*/)
            {
                int32 damage = GetEffectValue();
                ApplyPct(damage, GetCaster()->GetTotalAttackPowerValue(BASE_ATTACK));

                if (Unit* target = GetHitUnit())
                {
                    damage = GetCaster()->SpellDamageBonusDone(target, GetSpellInfo(), uint32(damage), SPELL_DIRECT_DAMAGE);
                    damage = target->SpellDamageBonusTaken(GetCaster(), GetSpellInfo(), uint32(damage), SPELL_DIRECT_DAMAGE);
                }
                SetHitDamage(damage);
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                int32 damage = GetEffectValue();
                GetCaster()->CastCustomSpell(GetCaster(), SPELL_WARRIOR_BLOODTHIRST, &damage, NULL, NULL, true, NULL);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warr_bloodthirst_SpellScript::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
                OnEffectHit += SpellEffectFn(spell_warr_bloodthirst_SpellScript::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_bloodthirst_SpellScript();
        }
};

/// Updated 4.3.4
class spell_warr_bloodthirst_heal : public SpellScriptLoader
{
    public:
        spell_warr_bloodthirst_heal() : SpellScriptLoader("spell_warr_bloodthirst_heal") { }

        class spell_warr_bloodthirst_heal_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_bloodthirst_heal_SpellScript);

            void HandleHeal(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();

                if(!caster)
                    return;

                if (SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_WARRIOR_BLOODTHIRST_DAMAGE))
                {
                    int32 calculatedHeal = CalculatePct(caster->GetMaxHealth(), float(spellInfo->Effects[EFFECT_1].CalcValue(GetCaster())) / 1000);

                    // Field Dressing check
                    if(AuraEffect* aurEff = caster->GetAuraEffect(SPELL_AURA_ADD_PCT_MODIFIER, SPELLFAMILY_WARRIOR, 2671, EFFECT_1))
                        AddPct(calculatedHeal, aurEff->GetAmount());

                    SetHitHeal(calculatedHeal);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warr_bloodthirst_heal_SpellScript::HandleHeal, EFFECT_0, SPELL_EFFECT_HEAL);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_bloodthirst_heal_SpellScript();
        }
};

/// Updated 4.3.4
class spell_warr_charge : public SpellScriptLoader
{
    public:
        spell_warr_charge() : SpellScriptLoader("spell_warr_charge") { }

        class spell_warr_charge_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_charge_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARRIOR_JUGGERNAUT_CRIT_BONUS_TALENT) || !sSpellMgr->GetSpellInfo(SPELL_WARRIOR_JUGGERNAUT_CRIT_BONUS_BUFF) || !sSpellMgr->GetSpellInfo(SPELL_WARRIOR_CHARGE))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                SpellInfo const* interceptProto = sSpellMgr->GetSpellInfo(SPELL_WARRIOR_INTERCEPT);
                int32 chargeBasePoints0 = GetEffectValue();
                Unit* caster = GetCaster();

                if(!interceptProto || !caster || !caster->ToPlayer())
                    return;

                caster->CastCustomSpell(caster, SPELL_WARRIOR_CHARGE, &chargeBasePoints0, NULL, NULL, true);

                // Juggernaut crit bonus and intercept cd
                if (caster->HasAura(SPELL_WARRIOR_JUGGERNAUT_CRIT_BONUS_TALENT))
                {
                    Player* player = caster->ToPlayer();

                    caster->CastSpell(caster, SPELL_WARRIOR_JUGGERNAUT_CRIT_BONUS_BUFF, true);

                    // Cooldown sharing
                    if(!player->HasSpellCooldown(SPELL_WARRIOR_INTERCEPT))
                    {
                        WorldPacket data(SMSG_SPELL_COOLDOWN, 8+1+4);
                        data << uint64(player->GetGUID());
                        data << uint8(0x1);                               // flags (0x1, 0x2)
                        data << uint32(interceptProto->Id);
                        // Same cooldown as charge
                        data << uint32(13000);                              // in m.secs
                        player->GetSession()->SendPacket(&data);
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warr_charge_SpellScript::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_charge_SpellScript();
        }
};

/// Updated 4.3.4
class spell_warr_concussion_blow : public SpellScriptLoader
{
    public:
        spell_warr_concussion_blow() : SpellScriptLoader("spell_warr_concussion_blow") { }

        class spell_warr_concussion_blow_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_concussion_blow_SpellScript);

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                SetHitDamage(CalculatePct(GetCaster()->GetTotalAttackPowerValue(BASE_ATTACK), GetEffectValue()));
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warr_concussion_blow_SpellScript::HandleDummy, EFFECT_2, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_concussion_blow_SpellScript();
        }
};

/// Updated 4.3.4
class spell_warr_deep_wounds : public SpellScriptLoader
{
    public:
        spell_warr_deep_wounds() : SpellScriptLoader("spell_warr_deep_wounds") { }

        class spell_warr_deep_wounds_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_deep_wounds_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARRIOR_DEEP_WOUNDS_RANK_1) || !sSpellMgr->GetSpellInfo(SPELL_WARRIOR_DEEP_WOUNDS_RANK_2) || !sSpellMgr->GetSpellInfo(SPELL_WARRIOR_DEEP_WOUNDS_RANK_3))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                int32 damage = GetEffectValue();
                Unit* caster = GetCaster();
                if (Unit* target = GetHitUnit())
                {
                    // apply percent damage mods
                    damage = caster->SpellDamageBonusDone(target, GetSpellInfo(), damage, SPELL_DIRECT_DAMAGE);

                    ApplyPct(damage, 16 * sSpellMgr->GetSpellRank(GetSpellInfo()->Id));

                    damage = target->SpellDamageBonusTaken(caster, GetSpellInfo(), damage, SPELL_DIRECT_DAMAGE);

                    SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_WARRIOR_DEEP_WOUNDS_RANK_PERIODIC);
                    uint32 ticks = spellInfo->GetDuration() / spellInfo->Effects[EFFECT_0].Amplitude;

                    // Add remaining ticks to damage done
                    if (AuraEffect const* aurEff = target->GetAuraEffect(SPELL_WARRIOR_DEEP_WOUNDS_RANK_PERIODIC, EFFECT_0, caster->GetGUID()))
                        damage += aurEff->GetAmount() * (ticks - aurEff->GetTickNumber());

                    damage /= ticks;

                    caster->CastCustomSpell(target, SPELL_WARRIOR_DEEP_WOUNDS_RANK_PERIODIC, &damage, NULL, NULL, true);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warr_deep_wounds_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_deep_wounds_SpellScript();
        }
};

/// Updated 4.3.4
class spell_warr_execute : public SpellScriptLoader
{
    public:
        spell_warr_execute() : SpellScriptLoader("spell_warr_execute") { }

        class spell_warr_execute_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_execute_SpellScript);

            void HandleOnCast()
            {
                Unit* caster = GetCaster();

                if(caster && caster->GetPower(POWER_RAGE) > 0)
                {
                    float ap = caster->GetTotalAttackPowerValue(BASE_ATTACK);

                    // Formula taken from the DBC: "${10+$AP*0.437*$m1/100}"
                    damage = int32(10 + ap * 0.437);

                    // Normalized rage (-10 because the execute base cost is not yet applied)
                    uint32 powerAfterBaseCost = caster->GetPower(POWER_RAGE) /10 -10;

                    uint32 extraRage = powerAfterBaseCost > 20 ? 20 : powerAfterBaseCost;
                    uint32 newPowerAmount = powerAfterBaseCost - extraRage;

                    // Sudden Death rage saving
                    if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_AURA_PROC_TRIGGER_SPELL, SPELLFAMILY_WARRIOR, WARRIOR_ICON_ID_SUDDEN_DEATH, EFFECT_0))
                    {
                        if(newPowerAmount < 10)
                        {
                            newPowerAmount = aurEff->GetAmount();
                        }
                    }

                    // Enter if there is extra rage to add as bonus damage
                    if(extraRage > 0)
                    {
                        // Add bonus damage
                        // Formula taken from the DBC: "${$ap*0.874*$m1/100-1} = 20 rage"
                        damage += int32 (ap * 0.874 * extraRage / 10 - 1);
                    }

                    // For remaining at the desidered rage when the warrior will use the base execute cost (10)
                    newPowerAmount += 10;

                    newPowerAmount *= sWorld->getRate(RATE_POWER_RAGE_INCOME);

                    // Sets new rage
                    caster->SetPower(POWER_RAGE, newPowerAmount * 10);
                }
            }
            
            void HandleEffect(SpellEffIndex /*effIndex*/)
            {
                SetHitDamage(damage);
            }

        private:
            int32 damage;

            void Register()
            {
                OnCast += SpellCastFn(spell_warr_execute_SpellScript::HandleOnCast);
                OnEffectHitTarget += SpellEffectFn(spell_warr_execute_SpellScript::HandleEffect, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_execute_SpellScript();
        }
};

// 59725 - Improved Spell Reflection
class spell_warr_improved_spell_reflection : public SpellScriptLoader
{
    public:
        spell_warr_improved_spell_reflection() : SpellScriptLoader("spell_warr_improved_spell_reflection") { }

        class spell_warr_improved_spell_reflection_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_improved_spell_reflection_SpellScript);

            void FilterTargets(std::list<WorldObject*>& unitList)
            {
                if (GetCaster())
                    unitList.remove(GetCaster());
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warr_improved_spell_reflection_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_CASTER_AREA_PARTY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_improved_spell_reflection_SpellScript();
        }
};

// 5246 - Intimidating Shout
class spell_warr_intimidating_shout : public SpellScriptLoader
{
    public:
        spell_warr_intimidating_shout() : SpellScriptLoader("spell_warr_intimidating_shout") { }

        class spell_warr_intimidating_shout_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_intimidating_shout_SpellScript);

            void FilterTargets(std::list<WorldObject*>& unitList)
            {
                unitList.remove(GetExplTargetWorldObject());
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warr_intimidating_shout_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENEMY);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warr_intimidating_shout_SpellScript::FilterTargets, EFFECT_2, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_intimidating_shout_SpellScript();
        }
};

/// Updated 4.3.4
class spell_warr_last_stand : public SpellScriptLoader
{
    public:
        spell_warr_last_stand() : SpellScriptLoader("spell_warr_last_stand") { }

        class spell_warr_last_stand_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_last_stand_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARRIOR_LAST_STAND_TRIGGERED))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                {
                    int32 healthModSpellBasePoints0 = int32(caster->CountPctFromMaxHealth(GetEffectValue()));
                    caster->CastCustomSpell(caster, SPELL_WARRIOR_LAST_STAND_TRIGGERED, &healthModSpellBasePoints0, NULL, NULL, true, NULL);
                }
            }

            void Register()
            {
                // add dummy effect spell handler to Last Stand
                OnEffectHit += SpellEffectFn(spell_warr_last_stand_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_last_stand_SpellScript();
        }
};

// 7384, 7887, 11584, 11585 - Overpower
class spell_warr_overpower : public SpellScriptLoader
{
    public:
        spell_warr_overpower() : SpellScriptLoader("spell_warr_overpower") { }

        class spell_warr_overpower_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_overpower_SpellScript);

            void HandleEffect(SpellEffIndex /*effIndex*/)
            {
                uint32 spellId = 0;
                if (GetCaster()->HasAura(SPELL_WARRIOR_UNRELENTING_ASSAULT_RANK_1))
                    spellId = SPELL_WARRIOR_UNRELENTING_ASSAULT_TRIGGER_1;
                else if (GetCaster()->HasAura(SPELL_WARRIOR_UNRELENTING_ASSAULT_RANK_2))
                    spellId = SPELL_WARRIOR_UNRELENTING_ASSAULT_TRIGGER_2;

                if (!spellId)
                    return;

                if (Player* target = GetHitPlayer())
                    if (target->HasUnitState(UNIT_STATE_CASTING))
                        target->CastSpell(target, spellId, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warr_overpower_SpellScript::HandleEffect, EFFECT_0, SPELL_EFFECT_ANY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_overpower_SpellScript();
        }
};

// 94009 - Rend
class spell_warr_rend : public SpellScriptLoader
{
    public:
        spell_warr_rend() : SpellScriptLoader("spell_warr_rend") { }

        class spell_warr_rend_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warr_rend_AuraScript);

            void CalculateAmount(AuraEffect const* aurEff, int32& amount, bool& canBeRecalculated)
            {
                if (Unit* caster = GetCaster())
                {
                    canBeRecalculated = false;

                    // $0.2 * (($MWB + $mwb) / 2 + $AP / 14 * $MWS) bonus per tick
                    float ap = caster->GetTotalAttackPowerValue(BASE_ATTACK);
                    int32 mws = caster->GetAttackTime(BASE_ATTACK);
                    float mwbMin = caster->GetWeaponDamageRange(BASE_ATTACK, MINDAMAGE);
                    float mwbMax = caster->GetWeaponDamageRange(BASE_ATTACK, MAXDAMAGE);
                    float mwb = ((mwbMin + mwbMax) / 2 + ap * mws / 14000) * 0.25f * 6.0f;

                    mwb /= 5.0f; // Per tick amount

                    amount += int32(caster->ApplyEffectModifiers(GetSpellInfo(), aurEff->GetEffIndex(), mwb));
                }
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warr_rend_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_rend_AuraScript();
        }
};

// 64380, 65941 - Shattering Throw
class spell_warr_shattering_throw : public SpellScriptLoader
{
    public:
        spell_warr_shattering_throw() : SpellScriptLoader("spell_warr_shattering_throw") { }

        class spell_warr_shattering_throw_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_shattering_throw_SpellScript);

            void HandleScript(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                // remove shields, will still display immune to damage part
                if (Unit* target = GetHitUnit())
                    target->RemoveAurasWithMechanic(1 << MECHANIC_IMMUNE_SHIELD, AURA_REMOVE_BY_ENEMY_SPELL);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warr_shattering_throw_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_shattering_throw_SpellScript();
        }
};

/// Updated 4.3.4
class spell_warr_slam : public SpellScriptLoader
{
    public:
        spell_warr_slam() : SpellScriptLoader("spell_warr_slam") { }

        class spell_warr_slam_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_slam_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARRIOR_SLAM))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                Unit* target = GetHitUnit();

                int32 bp0 = GetEffectValue();

                if (caster && target)
                {
                    caster->CastCustomSpell(target, SPELL_WARRIOR_SLAM, &bp0, NULL, NULL, true);
                    
                    if(Player* player = caster->ToPlayer())
                    {        
                        if(AuraEffect* aurEff = caster->GetAuraEffect(SPELL_AURA_MOD_DAMAGE_PERCENT_DONE, SPELLFAMILY_WARRIOR, 4975, EFFECT_0))
                        {
                            if(player->IsOneHandUsed(true)
                                || player->IsOneHandUsed(false))
                            {
                                caster->CastCustomSpell(target, SPELL_WARRIOR_SLAM_OFFHAND, &bp0, NULL, NULL, true);
                            }
                        }
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warr_slam_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_slam_SpellScript();
        }
};

class spell_warr_critical_block : public SpellScriptLoader
{
    public:
        spell_warr_critical_block() : SpellScriptLoader("spell_warr_critical_block") { }

        class spell_warr_critical_block_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warr_critical_block_AuraScript);

            void CalculateBonus(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)
            {
                canBeRecalculated = true;

                if (!GetCaster())
                    return;

                // critical Block (War protection mastery)
                if (Player* caster = GetCaster()->ToPlayer())
                    if (caster->HasAuraType(SPELL_AURA_MASTERY))
                        if (caster->GetPrimaryTalentTree(caster->GetActiveSpec()) == BS_WARRIOR_PROTECTION)
						{
							amount += int32(1.5f * caster->GetMasteryPoints());
						}
							
            }

            void CalculateBonusCrit(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)
            {
                canBeRecalculated = true;

                if (!GetCaster())
                    return;

                // critical Block (War protection mastery Crit Block)
                if (Player* caster = GetCaster()->ToPlayer())
                    if (caster->HasAuraType(SPELL_AURA_MASTERY))
                        if (caster->GetPrimaryTalentTree(caster->GetActiveSpec()) == BS_WARRIOR_PROTECTION)
							amount += int32(1.5f * caster->GetMasteryPoints());							
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warr_critical_block_AuraScript::CalculateBonus, EFFECT_1, SPELL_AURA_MOD_BLOCK_PERCENT);
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warr_critical_block_AuraScript::CalculateBonusCrit, EFFECT_0, SPELL_AURA_MOD_BLOCK_CRIT_CHANCE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_critical_block_AuraScript();
        }
};

// 12328, 18765, 35429 - Sweeping Strikes
class spell_warr_sweeping_strikes : public SpellScriptLoader
{
    public:
        spell_warr_sweeping_strikes() : SpellScriptLoader("spell_warr_sweeping_strikes") { }

        class spell_warr_sweeping_strikes_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warr_sweeping_strikes_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARRIOR_SWEEPING_STRIKES_EXTRA_ATTACK))
                    return false;
                return true;
            }

            bool Load()
            {
                _procTarget = NULL;
                return true;
            }

            bool CheckProc(ProcEventInfo& eventInfo)
            {
                _procTarget = eventInfo.GetActor()->SelectNearbyTarget(eventInfo.GetProcTarget());
                return _procTarget;
            }

            void HandleProc(AuraEffect const* aurEff, ProcEventInfo& /*eventInfo*/)
            {
                PreventDefaultAction();
                GetTarget()->CastSpell(_procTarget, SPELL_WARRIOR_SWEEPING_STRIKES_EXTRA_ATTACK, true, NULL, aurEff);
            }

            void Register()
            {
                DoCheckProc += AuraCheckProcFn(spell_warr_sweeping_strikes_AuraScript::CheckProc);
                OnEffectProc += AuraEffectProcFn(spell_warr_sweeping_strikes_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
            }

        private:
            Unit* _procTarget;
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_sweeping_strikes_AuraScript();
        }
};

// 50720 - Vigilance
class spell_warr_vigilance : public SpellScriptLoader
{
    public:
        spell_warr_vigilance() : SpellScriptLoader("spell_warr_vigilance") { }

        class spell_warr_vigilance_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warr_vigilance_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARRIOR_GLYPH_OF_VIGILANCE))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_WARRIOR_VIGILANCE_PROC))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_WARRIOR_VIGILANCE_REDIRECT_THREAT))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_GEN_DAMAGE_REDUCTION_AURA))
                    return false;
                return true;
            }

            bool Load()
            {
                _procTarget = NULL;
                return true;
            }

            void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                Unit* target = GetTarget();
                target->CastSpell(target, SPELL_GEN_DAMAGE_REDUCTION_AURA, true);

                if (Unit* caster = GetCaster())
                    target->CastSpell(caster, SPELL_WARRIOR_VIGILANCE_REDIRECT_THREAT, true);
            }

            void HandleAfterApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                //! WORKAROUND
                //! this glyph is a proc
                if (Unit* caster = GetCaster())
                {
                    if (AuraEffect const* glyph = caster->GetAuraEffect(SPELL_WARRIOR_GLYPH_OF_VIGILANCE, EFFECT_0))
                        GetTarget()->ModifyRedirectThreat(glyph->GetAmount());
                }
            }

            void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                Unit* target = GetTarget();
                if (target->HasAura(SPELL_GEN_DAMAGE_REDUCTION_AURA) &&
                    !(target->HasAura(SPELL_PALADIN_BLESSING_OF_SANCTUARY) ||
                    target->HasAura(SPELL_PALADIN_GREATER_BLESSING_OF_SANCTUARY) ||
                    target->HasAura(SPELL_PRIEST_RENEWED_HOPE)))
                {
                    target->RemoveAurasDueToSpell(SPELL_GEN_DAMAGE_REDUCTION_AURA);
                }

                target->ResetRedirectThreat();
            }

            bool CheckProc(ProcEventInfo& /*eventInfo*/)
            {
                _procTarget = GetCaster();
                return _procTarget;
            }

            void HandleProc(AuraEffect const* aurEff, ProcEventInfo& /*eventInfo*/)
            {
                PreventDefaultAction();
                GetTarget()->CastSpell(_procTarget, SPELL_WARRIOR_VIGILANCE_PROC, true, NULL, aurEff);
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_warr_vigilance_AuraScript::HandleApply, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
                AfterEffectApply += AuraEffectApplyFn(spell_warr_vigilance_AuraScript::HandleAfterApply, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
                OnEffectRemove += AuraEffectRemoveFn(spell_warr_vigilance_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
                DoCheckProc += AuraCheckProcFn(spell_warr_vigilance_AuraScript::CheckProc);
                OnEffectProc += AuraEffectProcFn(spell_warr_vigilance_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
            }

        private:
            Unit* _procTarget;
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_vigilance_AuraScript();
        }
};

// 50725 Vigilance
class spell_warr_vigilance_trigger : public SpellScriptLoader
{
    public:
        spell_warr_vigilance_trigger() : SpellScriptLoader("spell_warr_vigilance_trigger") { }

        class spell_warr_vigilance_trigger_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_vigilance_trigger_SpellScript);

            void HandleScript(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                // Remove Taunt cooldown
                if (Player* target = GetHitPlayer())
                    target->RemoveSpellCooldown(SPELL_WARRIOR_TAUNT, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warr_vigilance_trigger_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_vigilance_trigger_SpellScript();
        }
};
/*
class spell_warr_death_wish : public SpellScriptLoader
{
    public:
        spell_warr_death_wish() : SpellScriptLoader("spell_warr_death_wish") { }

        class spell_warr_death_wish_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warr_death_wish);
            // where function is: void function (AuraEffect* aurEff, int32& amount, bool& canBeRecalculated);
            void CalculateAmount(AuraEffect const* /*aurEff*//*, int32 &amount, bool& canBeRecalculated)
            {
                canBeRecalculated = false;
                            
                if(Unit* owner = GetCaster())
                    if (owner->ToPlayer() && owner->ToPlayer()->HasAuraType(SPELL_AURA_MASTERY))
                        if (owner->ToPlayer()->GetPrimaryTalentTree(owner->ToPlayer()->GetActiveSpec()) == BS_WARRIOR_FURY)
                            amount *= int32(1.0f + (0.056f *  (owner->ToPlayer()->GetMasteryPoints() - 6))); // fury base mastery is 2
            }
            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warr_death_wish_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE);
              //  DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warr_death_wish_AuraScript::OnEffectCalcAmount, EFFECT_1, SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_death_wish_AuraScript();
        }
};*/

class spell_warr_heroic_leap : public SpellScriptLoader
{
    public:
        spell_warr_heroic_leap() : SpellScriptLoader("spell_warr_heroic_leap") { }

        class spell_warr_heroic_leap_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_heroic_leap_SpellScript);

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->HasUnitState(UNIT_STATE_ROOT))
                    {
                        SetCustomCastResultMessage(SPELL_CUSTOM_ERROR_CANT_DO_WHILE_ROOTED);
                        return SPELL_FAILED_CUSTOM_ERROR;
                    }
                }

                return SPELL_CAST_OK;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_warr_heroic_leap_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_heroic_leap_SpellScript();
        }
};

void AddSC_warrior_spell_scripts()
{
    //new spell_warr_death_wish();
    new spell_warr_opportunity_strike();
    new spell_warr_stance_handler();
    new spell_warr_colussus_smash();
    new spell_warr_intercept();
    new spell_warr_hamstring();
    new spell_warr_bloodthirst();
    new spell_warr_bloodthirst_heal();
    new spell_warr_critical_block();
    new spell_warr_charge();
    new spell_warr_concussion_blow();
    new spell_warr_deep_wounds();
    new spell_warr_execute();
    new spell_warr_improved_spell_reflection();
    new spell_warr_intimidating_shout();
    new spell_warr_last_stand();
    new spell_warr_overpower();
    new spell_warr_rend();
    new spell_warr_shattering_throw();
    new spell_warr_slam();
    new spell_warr_sweeping_strikes();
    new spell_warr_vigilance();
    new spell_warr_vigilance_trigger();
    new spell_warr_heroic_leap();
}
