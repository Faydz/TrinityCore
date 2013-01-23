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
 * Scripts for spells with SPELLFAMILY_WARLOCK and SPELLFAMILY_GENERIC spells used by warlock players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_warl_".
 */

#include "Player.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

enum WarlockSpells
{
    SPELL_WARLOCK_CORRUPTION                      = 172,
    SPELL_WARLOCK_BANE_OF_DOOM_EFFECT               = 18662,
    SPELL_WARLOCK_DEMONIC_CIRCLE_SUMMON             = 48018,
    SPELL_WARLOCK_DEMONIC_CIRCLE_TELEPORT           = 48020,
    SPELL_WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST         = 62388,
    SPELL_WARLOCK_DEMONIC_EMPOWERMENT_SUCCUBUS      = 54435,
    SPELL_WARLOCK_DEMONIC_EMPOWERMENT_IMP         = 54444,
    SPELL_WARLOCK_DEMONIC_EMPOWERMENT_VOIDWALKER    = 54443,
    SPELL_WARLOCK_DEMONIC_EMPOWERMENT_FELGUARD      = 54508,
    SPELL_WARLOCK_DEMONIC_EMPOWERMENT_FELHUNTER     = 54509,
    SPELL_WARLOCK_DRAIN_LIFE_HEALTH_ENERGIZE      = 89653,
    SPELL_WARLOCK_IMMOLATE                        = 348,
    SPELL_WARLOCK_HAUNT                             = 48181,
    SPELL_WARLOCK_HAUNT_HEAL                        = 48210,
    SPELL_WARLOCK_LIFE_TAP_ENERGIZE                 = 31818,
    SPELL_WARLOCK_LIFE_TAP_ENERGIZE_2               = 32553,
    SPELL_WARLOCK_SOULSHATTER                       = 32835,
    SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_BUFF_R1  = 60955,
    SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_BUFF_R2  = 60956,
	SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_R1       = 18703,
    SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_R2       = 18704,
    SPELL_WARLOCK_IMPROVED_HEALTHSTONE_R1         = 18692,
	SPELL_WARLOCK_IMPROVED_HEALTHSTONE_R2         = 18693,
    SPELL_WARLOCK_IMPROVED_LIFE_TAP_ICON_ID       = 208,
    SPELL_WARLOCK_JINX_R1                         = 85541,
    SPELL_WARLOCK_JINX_R2                         = 86105,
    SPELL_WARLOCK_MANA_FEED_ICON_ID               = 1982,
    SPELL_WARLOCK_NETHER_WARD                     = 91711,
    SPELL_WARLOCK_NETHER_WARD_TALENT              = 91713,
    SPELL_WARLOCK_SHADOW_WARD                     = 6229,
    SPELL_WARLOCK_SOUL_SHARD_ENERGIZE             = 87388,
    SPELL_WARLOCK_SOUL_SWAP_COOLDOWN              = 94229,
    SPELL_WARLOCK_SOUL_SWAP_GLYPH                 = 56226,
    SPELL_WARLOCK_SOUL_SWAP_GRAPHIC_EFFECT        = 92795,
    SPELL_WARLOCK_SOUL_SWAP_SAVE_DOTS             = 86211,
    SPELL_WARLOCK_SOULBURN                        = 74434,
    SPELL_WARLOCK_UNSTABLE_AFFLICTION             = 30108,
    SPELL_WARLOCK_UNSTABLE_AFFLICTION_DISPEL      = 31117,
};

bool _SeedOfCorruptionFlag = false;

// 71521 spell_warl_Hand_of_Guldan
class spell_warl_hand_of_guldan: public SpellScriptLoader 
{
public:
    spell_warl_hand_of_guldan() : SpellScriptLoader("spell_warl_hand_of_guldan")  { }

    class spell_warl_hand_of_guldan_SpellScript: public SpellScript
    {
        PrepareSpellScript(spell_warl_hand_of_guldan_SpellScript);

        void BeforeEffect(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();

            if (!target)
                return;

            if (!caster)
                return;

            // Cast the debuff on the target (it applies the aura)
            caster->CastSpell(target, 86000, true);

            // Graphical effect
            target->CastSpell(target, 85526, true);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_warl_hand_of_guldan_SpellScript::BeforeEffect, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const 
    {
        return new spell_warl_hand_of_guldan_SpellScript();
    }
};

// 687/28176 - spell_warl_armor_nether_ward_ignore
class spell_warl_armor_nether_ward_ignore: public SpellScriptLoader 
{
public:
    spell_warl_armor_nether_ward_ignore() : SpellScriptLoader("spell_warl_armor_nether_ward_ignore") { }

    class spell_warl_armor_nether_ward_ignore_AuraScript: public AuraScript
    {
        PrepareAuraScript(spell_warl_armor_nether_ward_ignore_AuraScript);

        void OnEffectCalcAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
        {
            if(GetCaster())
            {
                if(GetCaster()->HasAura(SPELL_WARLOCK_NETHER_WARD_TALENT))
                    amount = SPELL_WARLOCK_NETHER_WARD;
                else
                    amount = SPELL_WARLOCK_SHADOW_WARD;
            }
        }

        void Register()
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_armor_nether_ward_ignore_AuraScript::OnEffectCalcAmount, EFFECT_2, SPELL_AURA_OVERRIDE_ACTIONBAR_SPELLS);
        }
    };

    AuraScript* GetAuraScript() const 
    {
        return new spell_warl_armor_nether_ward_ignore_AuraScript();
    }
};

// 77799 - spell_warl_fel_flame
class spell_warl_fel_flame: public SpellScriptLoader 
{
public:
    spell_warl_fel_flame() : SpellScriptLoader("spell_warl_fel_flame") { }

    class spell_warl_fel_flame_SpellScript: public SpellScript
    {
        PrepareSpellScript(spell_warl_fel_flame_SpellScript);

        void HandleScriptEffect(SpellEffIndex /*effIndex*/) 
        {
            Unit* target = GetHitUnit();
            Unit* caster = GetCaster();

            if (!target)
                return;

            if (!caster)
                return;
            
            // Immolate
            if (target->HasAura(SPELL_WARLOCK_IMMOLATE, caster->GetGUID()))
            {
                int32 newDuration = target->GetAura(SPELL_WARLOCK_IMMOLATE, caster->GetGUID())->GetDuration();
                if (newDuration >= GetEffectValue()*1000)
                    newDuration = target->GetAura(SPELL_WARLOCK_IMMOLATE, caster->GetGUID())->GetMaxDuration();
                else
                    newDuration += (GetEffectValue()*1000);

                target->GetAura(SPELL_WARLOCK_IMMOLATE, caster->GetGUID())->SetDuration(newDuration, true);
            } 
            // Unstable Affliction
            else if (target->HasAura(SPELL_WARLOCK_UNSTABLE_AFFLICTION, caster->GetGUID()))
            {
                int32 newDuration = target->GetAura(SPELL_WARLOCK_UNSTABLE_AFFLICTION, caster->GetGUID())->GetDuration();
                if (newDuration >= GetEffectValue()*1000)
                    newDuration = target->GetAura(SPELL_WARLOCK_UNSTABLE_AFFLICTION, caster->GetGUID())->GetMaxDuration();
                else
                    newDuration += (GetEffectValue()*1000);

                target->GetAura(SPELL_WARLOCK_UNSTABLE_AFFLICTION, caster->GetGUID())->SetDuration(newDuration, true);
            }            
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_warl_fel_flame_SpellScript::HandleScriptEffect, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const 
    {
        return new spell_warl_fel_flame_SpellScript();
    }
};

// 29722 - Incinerate
class spell_warl_incinerate : public SpellScriptLoader
{
public:
    spell_warl_incinerate() : SpellScriptLoader("spell_warl_incinerate") { }

    class spell_warl_incinerate_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_incinerate_SpellScript);

        void RecalculateDamage()
        {
            if(!GetCaster() || !GetHitUnit())
                return;

            // Bonus damage if the immolate dot is on the target
            if(GetHitUnit()->HasAura(SPELL_WARLOCK_IMMOLATE, GetCaster()->GetGUID()))
            {
                int32 newDamage = GetHitDamage() + int32(GetHitDamage() / 6);
                SetHitDamage(newDamage); 
            }
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_warl_incinerate_SpellScript::RecalculateDamage);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warl_incinerate_SpellScript();
    }
};

// 1490 - Curse of the Elements
class spell_warl_curse_of_the_elements: public SpellScriptLoader {
public:
    spell_warl_curse_of_the_elements() : SpellScriptLoader("spell_warl_curse_of_the_elements") { }

    class spell_warl_curse_of_the_elements_AuraScript: public AuraScript
    {
        PrepareAuraScript(spell_warl_curse_of_the_elements_AuraScript);

        void HandlePeriodic(AuraEffect const* /*aurEff*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetTarget();
                
            if (!target || !caster)
                return;
            
            if(caster->GetDummyAuraEffect(SPELLFAMILY_WARLOCK, 5002, EFFECT_0))
            {
                // Check if warlock has the either the first or the second rank of jinx
                if (caster->HasAura(18179))
                    caster->CastSpell(target, SPELL_WARLOCK_JINX_R1, true);
                else if(caster->HasAura(85479))
                    caster->CastSpell(target, SPELL_WARLOCK_JINX_R2, true);
            }
        }

        void Register() 
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_curse_of_the_elements_AuraScript::HandlePeriodic, EFFECT_2, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_warl_curse_of_the_elements_AuraScript();
    }
};

// 86121 - Soul Swap action bar spell
class spell_warl_soul_swap: public SpellScriptLoader {
public:
    spell_warl_soul_swap() : SpellScriptLoader("spell_warl_soul_swap") { }

    class spell_warl_soul_swap_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_soul_swap_SpellScript);

        SpellCastResult CheckRequirement()
        {
            Unit* caster = GetCaster();
            Unit* target = GetExplTargetUnit();

            if (!target || !caster)
                return SPELL_FAILED_BAD_TARGETS;

            // Check if there are any dots on the target
            if(target->GetSoulSwapDotsCount(caster) == 0)
                return SPELL_FAILED_BAD_TARGETS;

            return SPELL_CAST_OK;
        }
            
        // Graphic effect for the first cast
        void HandleEffectLaunchTarget(SpellEffIndex /*effIndex*/) 
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();

            if (!target || !caster)
                return;

            target->CastSpell(caster, SPELL_WARLOCK_SOUL_SWAP_GRAPHIC_EFFECT, true, 0, 0, caster->GetGUID());
        }
            
        // Handles the first cast of soul swap
        void HandleEffectHit(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();
                
            if (!target || !caster)
                return;

            target->RemoveAndSaveSoulSwapDots(caster);
            caster->CastSpell(caster, SPELL_WARLOCK_SOUL_SWAP_SAVE_DOTS, true);
        }

        void Register()
        {
            OnCheckCast += SpellCheckCastFn(spell_warl_soul_swap_SpellScript::CheckRequirement);
            OnEffectLaunchTarget += SpellEffectFn(spell_warl_soul_swap_SpellScript::HandleEffectLaunchTarget, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            OnEffectHitTarget += SpellEffectFn(spell_warl_soul_swap_SpellScript::HandleEffectHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript *GetSpellScript() const
    {
        return new spell_warl_soul_swap_SpellScript();
    }
};

// 86211 - Handles Soul Swap saved dots buff onRemove
class spell_warl_soul_swap_buff : public SpellScriptLoader
{
public:
    spell_warl_soul_swap_buff() : SpellScriptLoader("spell_warl_soul_swap_buff") { }

    class spell_warl_soul_swap_buff_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warl_soul_swap_buff_AuraScript);

        void HandleEffectRemove(AuraEffect const * /*aurEff*/, AuraEffectHandleModes mode)
        {
            Unit * caster = GetCaster();

            if (!caster)
                return;

            caster->ResetSoulSwapDots();
        }

        // function registering
        void Register()
        {
            OnEffectRemove += AuraEffectRemoveFn(spell_warl_soul_swap_buff_AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_OVERRIDE_ACTIONBAR_SPELLS, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript *GetAuraScript() const
    {
        return new spell_warl_soul_swap_buff_AuraScript();
    }
};

//86213 - Soul Swap paste
class spell_warl_soul_swap_exhale : public SpellScriptLoader
{
public:
    spell_warl_soul_swap_exhale() : SpellScriptLoader("spell_warl_soul_swap_exhale") { }

    class spell_warl_soul_swap_exhale_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_soul_swap_exhale_SpellScript);

        SpellCastResult CheckRequirementInternal(SpellCustomErrors& extendedError)
        {
            return SPELL_CAST_OK;
        }

        SpellCastResult CheckRequirement()
        {
            if (!GetExplTargetUnit())
                return SPELL_FAILED_BAD_TARGETS;

            if (GetExplTargetUnit()->GetGUID() == GetCaster()->GetSourceOfSoulSwapDots())
                return SPELL_FAILED_BAD_TARGETS;

            SpellCustomErrors extension = SPELL_CUSTOM_ERROR_NONE;
            SpellCastResult result = CheckRequirementInternal(extension);

            if (result != SPELL_CAST_OK)
            {
                Spell::SendCastResult(GetExplTargetUnit()->ToPlayer(), GetSpellInfo(), 0, result, extension);
                return result;
            }

            return SPELL_CAST_OK;
        }
        
        // The OnCast handler is used to prevent double soul swap when spamming the action bar bind
        void HandleOnCast()
        {
            Unit * caster = GetCaster();

            if (!caster)
                return;

            // Glyph of Soul Swap cooldown
            if (caster->HasAura(SPELL_WARLOCK_SOUL_SWAP_GLYPH))
                caster->CastSpell(caster, SPELL_WARLOCK_SOUL_SWAP_COOLDOWN, false);
        }

        void HandleEffectHit(SpellEffIndex /*effIndex*/)
        {
            Unit * target = GetHitUnit();
            Unit * caster = GetCaster();

            if (!caster || !target)
                return;
            
            if (caster->CastSavedSoulSwapDots(target))
                caster->RemoveAura(SPELL_WARLOCK_SOUL_SWAP_SAVE_DOTS);
        }

        void Register()
        {
            OnCheckCast += SpellCheckCastFn(spell_warl_soul_swap_exhale_SpellScript::CheckRequirement);
            OnCast += SpellCastFn(spell_warl_soul_swap_exhale_SpellScript::HandleOnCast);
            OnEffectHitTarget += SpellEffectFn(spell_warl_soul_swap_exhale_SpellScript::HandleEffectHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript *GetSpellScript() const
    {
        return new spell_warl_soul_swap_exhale_SpellScript();
    }
};

// 689/89420 - Drain Life
class spell_warl_drain_life: public SpellScriptLoader
{
public:
    spell_warl_drain_life() : SpellScriptLoader("spell_warl_drain_life") { }

    class spell_warl_drain_life_AuraScript: public AuraScript
    {
        PrepareAuraScript(spell_warl_drain_life_AuraScript);

        void HandlePeriodic(AuraEffect const* /*aurEff*/)
        {
            if(Unit* caster = GetCaster())
            {
                // Base percent
                int32 bp = 2; 
                
                // Checks for Death's Embrace talent and %
                if (AuraEffect const* aurEff = caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_WARLOCK, 3223, EFFECT_0))
                {
                    if (caster->HealthBelowPct(25))
                    {
                        bp += int32(aurEff->GetAmount());
                    }
                }

                caster->CastCustomSpell(caster, SPELL_WARLOCK_DRAIN_LIFE_HEALTH_ENERGIZE, &bp, NULL, NULL, true);
            }
        }

        void Register() 
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_drain_life_AuraScript::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_warl_drain_life_AuraScript();
    }
};

// 1120 - Offylike Drain Soul. cit. "drain soul has always checked if the target is in execute range on initial spell cast rather than on each tic."
class spell_warl_drain_soul: public SpellScriptLoader
{
public:
    spell_warl_drain_soul() : SpellScriptLoader("spell_warl_drain_soul"){ }

    class spell_warl_drain_soul_AuraScript: public AuraScript
    {
        PrepareAuraScript(spell_warl_drain_soul_AuraScript);

        void BeforeEffect(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if(Unit* caster = GetCaster())
            {
                // Need to get effect1 and use GetSpellInfo() because effect0 doesn't have an aura state.
                _pandemic = caster->GetAuraEffect(SPELL_AURA_ADD_FLAT_MODIFIER, SPELLFAMILY_WARLOCK, 4554, EFFECT_1);
            }
        }

        void OnPeriodic(AuraEffect const* aurEff)
        {
			if(!GetTarget())
				return;

			Aura* unstableAff = GetTarget()->GetAura(SPELL_WARLOCK_UNSTABLE_AFFLICTION);

            // Check if target is under 25% when casting Drain Soul
            if (aurEff->GetBase())
            {
                // Pandemic talent
                if (unstableAff && _pandemic && aurEff->GetBase()->WasUnder25PercentOnApp() 
                    && roll_chance_i(_pandemic->GetSpellInfo()->Effects[0].BasePoints))
                {
                    unstableAff->RefreshDuration();
                }
            }    
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_warl_drain_soul_AuraScript::BeforeEffect, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_drain_soul_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
        }

        // Pandemic is checked at the beginning to avoid a check for each periodic tick. So I need a script scope var.
        AuraEffect* _pandemic;
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_warl_drain_soul_AuraScript();
    }
};

// 710 - Banish
/// Updated 4.3.4
class spell_warl_banish : public SpellScriptLoader
{
    public:
        spell_warl_banish() : SpellScriptLoader("spell_warl_banish") { }

        class spell_warl_banish_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_banish_SpellScript);

            bool Load()
            {
                _removed = false;
                return true;
            }

            void HandleBanish()
            {
                /// Casting Banish on a banished target will cancel the effect
                /// Check if the target already has Banish, if so, do nothing.
                if (Unit* target = GetHitUnit())
                {
                    if (target->GetAuraEffect(SPELL_AURA_SCHOOL_IMMUNITY, SPELLFAMILY_WARLOCK, 0, 0x08000000, 0))
                    {
                        // No need to remove old aura since its removed due to not stack by current Banish aura
                        PreventHitDefaultEffect(EFFECT_0);
                        PreventHitDefaultEffect(EFFECT_1);
                        PreventHitDefaultEffect(EFFECT_2);
                        _removed = true;
                    }
                }
            }

            void RemoveAura()
            {
                if (_removed)
                    PreventHitAura();
            }

            void Register()
            {
                BeforeHit += SpellHitFn(spell_warl_banish_SpellScript::HandleBanish);
                AfterHit += SpellHitFn(spell_warl_banish_SpellScript::RemoveAura);
            }

            bool _removed;
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_banish_SpellScript();
        }
};

// 6201 - Create Healthstone
class spell_warl_create_healthstone : public SpellScriptLoader
{
    public:
        spell_warl_create_healthstone() : SpellScriptLoader("spell_warl_create_healthstone") { }

        class spell_warl_create_healthstone_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_create_healthstone_SpellScript);

            static uint32 const iTypes[8][3];

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARLOCK_IMPROVED_HEALTHSTONE_R1) || !sSpellMgr->GetSpellInfo(SPELL_WARLOCK_IMPROVED_HEALTHSTONE_R2))
                    return false;
                return true;
            }

            SpellCastResult CheckCast()
            {
                if (Player* caster = GetCaster()->ToPlayer())
                {
                    uint8 spellRank = sSpellMgr->GetSpellRank(GetSpellInfo()->Id);
                    ItemPosCountVec dest;
                    InventoryResult msg = caster->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, iTypes[spellRank - 1][0], 1, NULL);
                    if (msg != EQUIP_ERR_OK)
                        return SPELL_FAILED_TOO_MANY_OF_ITEM;
                }
                return SPELL_CAST_OK;
            }

            void HandleScriptEffect(SpellEffIndex effIndex)
            {
                if (Unit* unitTarget = GetHitUnit())
                {
                    uint32 rank = 0;
                    // Improved Healthstone
                    if (AuraEffect const* aurEff = unitTarget->GetDummyAuraEffect(SPELLFAMILY_WARLOCK, 284, 0))
                    {
                        switch (aurEff->GetId())
                        {
                            case SPELL_WARLOCK_IMPROVED_HEALTHSTONE_R1:
                                rank = 1;
                                break;
                            case SPELL_WARLOCK_IMPROVED_HEALTHSTONE_R2:
                                rank = 2;
                                break;
                            default:
                                sLog->outError(LOG_FILTER_SPELLS_AURAS, "Unknown rank of Improved Healthstone id: %d", aurEff->GetId());
                                break;
                        }
                    }
                    uint8 spellRank = sSpellMgr->GetSpellRank(GetSpellInfo()->Id);
                    if (spellRank > 0 && spellRank <= 8)
                        CreateItem(effIndex, iTypes[spellRank - 1][rank]);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warl_create_healthstone_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
                OnCheckCast += SpellCheckCastFn(spell_warl_create_healthstone_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_create_healthstone_SpellScript();
        }
};

uint32 const spell_warl_create_healthstone::spell_warl_create_healthstone_SpellScript::iTypes[8][3] =
{
    { 5512, 19004, 19005},              // Minor Healthstone
    { 5511, 19006, 19007},              // Lesser Healthstone
    { 5509, 19008, 19009},              // Healthstone
    { 5510, 19010, 19011},              // Greater Healthstone
    { 9421, 19012, 19013},              // Major Healthstone
    {22103, 22104, 22105},              // Master Healthstone
    {36889, 36890, 36891},              // Demonic Healthstone
    {36892, 36893, 36894}               // Fel Healthstone
};



// 27243 Seed of Corruption dot
class spell_warl_seed_of_corruption_dot : public SpellScriptLoader
{
    public:
        spell_warl_seed_of_corruption_dot() : SpellScriptLoader("spell_warl_seed_of_corruption_dot") { }

        class spell_warl_seed_of_corruption_dot_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_seed_of_corruption_dot_SpellScript);

            void HandleHit(SpellEffIndex /*effIndex*/)
            {
                if(Unit* caster = GetCaster())
                {
                    //Checks for soulburn buff and soulburn: Seed of Corruption talent
                    if(caster->HasAura(SPELL_WARLOCK_SOULBURN) && caster->GetDummyAuraEffect(SPELLFAMILY_WARLOCK, 1932, 0))
                    {
                        _SeedOfCorruptionFlag = true;
                        caster->RemoveAurasDueToSpell(SPELL_WARLOCK_SOULBURN);
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warl_seed_of_corruption_dot_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_seed_of_corruption_dot_SpellScript();
        }
};

// 603 Bane of Doom
/// Updated 4.3.4
class spell_warl_bane_of_doom : public SpellScriptLoader
{
    public:
        spell_warl_bane_of_doom() : SpellScriptLoader("spell_warl_bane_of_doom") { }
 
        class spell_warl_curse_of_doom_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_curse_of_doom_AuraScript);
 
            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARLOCK_BANE_OF_DOOM_EFFECT))
                    return false;
                return true;
            }
 
            bool Load()
            {
                return GetCaster() && GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }
 
            void HandlePeriodic(AuraEffect const* /*aurEff*/)
            {
                if (!GetCaster() || !GetTarget())
                    return;
 
                //Base chance
                int chance = 20;

                if(AuraEffect* aurEff = GetCaster()->GetAuraEffect(SPELL_AURA_ADD_FLAT_MODIFIER, SPELLFAMILY_WARLOCK, 195, EFFECT_0))
                    chance += int(aurEff->GetAmount());

                if(roll_chance_i(chance))
                    GetCaster()->CastSpell(GetTarget(), SPELL_WARLOCK_BANE_OF_DOOM_EFFECT, true);
            }
 
            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_curse_of_doom_AuraScript::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
            }
        };
 
        AuraScript* GetAuraScript() const
        {
            return new spell_warl_curse_of_doom_AuraScript();
        }
};

// 48018 - Demonic Circle: Summon
/// Updated 4.3.4
class spell_warl_demonic_circle_summon : public SpellScriptLoader
{
    public:
        spell_warl_demonic_circle_summon() : SpellScriptLoader("spell_warl_demonic_circle_summon") { }

        class spell_warl_demonic_circle_summon_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_demonic_circle_summon_AuraScript);

            void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes mode)
            {
                // If effect is removed by expire remove the summoned demonic circle too.
                if (!(mode & AURA_EFFECT_HANDLE_REAPPLY))
                    GetTarget()->RemoveGameObject(GetId(), true);

                GetTarget()->RemoveAura(SPELL_WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST);
            }

            void HandleDummyTick(AuraEffect const* /*aurEff*/)
            {
                if (GameObject* circle = GetTarget()->GetGameObject(GetId()))
                {
                    // Here we check if player is in demonic circle teleport range, if so add
                    // WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST; allowing him to cast the WARLOCK_DEMONIC_CIRCLE_TELEPORT.
                    // If not in range remove the WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST.

                    SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DEMONIC_CIRCLE_TELEPORT);

                    if (GetTarget()->IsWithinDist(circle, spellInfo->GetMaxRange(true)))
                    {
                        if (!GetTarget()->HasAura(SPELL_WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST))
                            GetTarget()->CastSpell(GetTarget(), SPELL_WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST, true);
                    }
                    else
                        GetTarget()->RemoveAura(SPELL_WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST);
                }
            }

            void Register()
            {
                OnEffectRemove += AuraEffectApplyFn(spell_warl_demonic_circle_summon_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_demonic_circle_summon_AuraScript::HandleDummyTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_demonic_circle_summon_AuraScript();
        }
};

// 48020 - Demonic Circle: Teleport
/// Updated 4.3.4
class spell_warl_demonic_circle_teleport : public SpellScriptLoader
{
    public:
        spell_warl_demonic_circle_teleport() : SpellScriptLoader("spell_warl_demonic_circle_teleport") { }
 
        class spell_warl_demonic_circle_teleport_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_demonic_circle_teleport_AuraScript);
 
            void HandleTeleport(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* player = GetTarget()->ToPlayer())
                {
                    if (GameObject* circle = player->GetGameObject(SPELL_WARLOCK_DEMONIC_CIRCLE_SUMMON))
                    {
                        player->NearTeleportTo(circle->GetPositionX(), circle->GetPositionY(), circle->GetPositionZ(), circle->GetOrientation());
                        player->RemoveMovementImpairingAuras();
                    }
                }
            }
 
            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_warl_demonic_circle_teleport_AuraScript::HandleTeleport, EFFECT_0, SPELL_AURA_MECHANIC_IMMUNITY, AURA_EFFECT_HANDLE_REAL);
            }
        };
 
        AuraScript* GetAuraScript() const
        {
            return new spell_warl_demonic_circle_teleport_AuraScript();
        }
};


// 47193 - Demonic Empowerment
/// Updated 4.3.4
class spell_warl_demonic_empowerment : public SpellScriptLoader
{
    public:
        spell_warl_demonic_empowerment() : SpellScriptLoader("spell_warl_demonic_empowerment") { }

        class spell_warl_demonic_empowerment_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_demonic_empowerment_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DEMONIC_EMPOWERMENT_SUCCUBUS) 
                    || !sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DEMONIC_EMPOWERMENT_VOIDWALKER) 
                    || !sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DEMONIC_EMPOWERMENT_FELGUARD) 
                    || !sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DEMONIC_EMPOWERMENT_FELHUNTER) 
                    || !sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DEMONIC_EMPOWERMENT_IMP))
                    return false;
                return true;
            }

            void HandleScriptEffect(SpellEffIndex /*effIndex*/)
            {
                if (Creature* targetCreature = GetHitCreature())
                {
                    if (targetCreature->isPet())
                    {
                        CreatureTemplate const* ci = sObjectMgr->GetCreatureTemplate(targetCreature->GetEntry());
                        switch (ci->family)
                        {
                            case CREATURE_FAMILY_SUCCUBUS:
                                targetCreature->CastSpell(targetCreature, SPELL_WARLOCK_DEMONIC_EMPOWERMENT_SUCCUBUS, true);
                                break;
                            case CREATURE_FAMILY_VOIDWALKER:
                            {
                                SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DEMONIC_EMPOWERMENT_VOIDWALKER);
                                int32 hp = int32(targetCreature->CountPctFromMaxHealth(GetCaster()->CalculateSpellDamage(targetCreature, spellInfo, 0)));
                                targetCreature->CastCustomSpell(targetCreature, SPELL_WARLOCK_DEMONIC_EMPOWERMENT_VOIDWALKER, &hp, NULL, NULL, true);
                                break;
                            }
                            case CREATURE_FAMILY_FELGUARD:
                                targetCreature->CastSpell(targetCreature, SPELL_WARLOCK_DEMONIC_EMPOWERMENT_FELGUARD, true);
                                break;
                            case CREATURE_FAMILY_FELHUNTER:
                                targetCreature->CastSpell(targetCreature, SPELL_WARLOCK_DEMONIC_EMPOWERMENT_FELHUNTER, true);
                                break;
                            case CREATURE_FAMILY_IMP:
                                targetCreature->CastSpell(targetCreature, SPELL_WARLOCK_DEMONIC_EMPOWERMENT_IMP, true);
                                break;
                        }
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warl_demonic_empowerment_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_demonic_empowerment_SpellScript();
        }
};

// 47422 - Everlasting Affliction
/// Updated 4.3.4
class spell_warl_everlasting_affliction : public SpellScriptLoader
{
    public:
        spell_warl_everlasting_affliction() : SpellScriptLoader("spell_warl_everlasting_affliction") { }

        class spell_warl_everlasting_affliction_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_everlasting_affliction_SpellScript);

            void HandleScriptEffect(SpellEffIndex /*effIndex*/)
            {
                if (Unit* unitTarget = GetHitUnit())
                    // Refresh corruption on target
                    if (AuraEffect* aur = unitTarget->GetAuraEffect(SPELL_AURA_PERIODIC_DAMAGE, SPELLFAMILY_WARLOCK, 0x2, 0, 0, GetCaster()->GetGUID()))
                        aur->GetBase()->RefreshDuration();
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warl_everlasting_affliction_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_everlasting_affliction_SpellScript();
        }
};

// 48181 - Haunt
/// Updated 4.3.4
class spell_warl_haunt : public SpellScriptLoader
{
    public:
        spell_warl_haunt() : SpellScriptLoader("spell_warl_haunt") { }

        class spell_warl_haunt_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_haunt_SpellScript);

            void HandleOnHit()
            {
                if (Aura* aura = GetHitAura())
                    if (AuraEffect* aurEff = aura->GetEffect(EFFECT_1))
                        aurEff->SetAmount(GetHitDamage());
            }

            void Register()
            {
                AfterHit += SpellHitFn(spell_warl_haunt_SpellScript::HandleOnHit);
            }
        };

        class spell_warl_haunt_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_haunt_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARLOCK_HAUNT_HEAL))
                    return false;
                return true;
            }

            void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                {
                    int32 amount = aurEff->GetAmount();
                    GetTarget()->CastCustomSpell(caster, SPELL_WARLOCK_HAUNT_HEAL, &amount, NULL, NULL, true, NULL, aurEff, GetCasterGUID());
                }
            }
            
            void Register()
            {
                OnEffectRemove += AuraEffectApplyFn(spell_warl_haunt_AuraScript::HandleRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_haunt_SpellScript();
        }

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_haunt_AuraScript();
        }
};

// 755 Health Funnel
/// Updated 4.3.4
class spell_warl_health_funnel : public SpellScriptLoader
{
public:
    spell_warl_health_funnel() : SpellScriptLoader("spell_warl_health_funnel") { }
 
    class spell_warl_health_funnel_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warl_health_funnel_AuraScript);
 
        void ApplyEffect(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetTarget();

            if (!caster || !target)
                return;
 
            if (caster->HasAura(SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_R2))
            {
                target->AddAura(SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_BUFF_R2, target);
            }
            else if (caster->HasAura(SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_R1))
            {
                target->AddAura(SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_BUFF_R1, target);
            }
        }
 
        void RemoveEffect(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* target = GetTarget();
            
            if(!target)
                return;

            target->RemoveAurasDueToSpell(SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_BUFF_R1);
            target->RemoveAurasDueToSpell(SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_BUFF_R2);
        }
 
        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_warl_health_funnel_AuraScript::ApplyEffect, EFFECT_0, SPELL_AURA_OBS_MOD_HEALTH, AURA_EFFECT_HANDLE_REAL);
            OnEffectRemove += AuraEffectRemoveFn(spell_warl_health_funnel_AuraScript::RemoveEffect, EFFECT_0, SPELL_AURA_OBS_MOD_HEALTH, AURA_EFFECT_HANDLE_REAL);
        }
    };
 
    AuraScript* GetAuraScript() const
    {
        return new spell_warl_health_funnel_AuraScript();
    }
};

// 1454 - Life Tap
/// Updated 4.3.4
class spell_warl_life_tap : public SpellScriptLoader
{
    public:
        spell_warl_life_tap() : SpellScriptLoader("spell_warl_life_tap") { }

        class spell_warl_life_tap_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_life_tap_SpellScript);

            bool Load()
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARLOCK_LIFE_TAP_ENERGIZE) || !sSpellMgr->GetSpellInfo(SPELL_WARLOCK_LIFE_TAP_ENERGIZE_2))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Player* caster = GetCaster()->ToPlayer();
                if (Unit* target = GetHitUnit())
                {
                    int32 damage = caster->CountPctFromMaxHealth(GetSpellInfo()->Effects[EFFECT_2].CalcValue());
                    int32 mana = CalculatePct(damage, GetSpellInfo()->Effects[EFFECT_1].CalcValue());

                    // Shouldn't Appear in Combat Log
                    target->ModifyHealth(-damage);

                    // Improved Life Tap mod
					if (AuraEffect const* aurEff = caster->GetDummyAuraEffect(SPELLFAMILY_WARLOCK, SPELL_WARLOCK_IMPROVED_LIFE_TAP_ICON_ID, 0))
                        AddPct(mana, aurEff->GetAmount());

                    caster->CastCustomSpell(target, SPELL_WARLOCK_LIFE_TAP_ENERGIZE, &mana, NULL, NULL, false);

                    // Mana Feed
                    if (AuraEffect const* aurEff = caster->GetAuraEffect(SPELL_AURA_ADD_FLAT_MODIFIER, SPELLFAMILY_WARLOCK, SPELL_WARLOCK_MANA_FEED_ICON_ID, 0))
                    {
                        int32 manaFeedVal = aurEff->GetAmount();
                        ApplyPct(manaFeedVal, mana);
                        caster->CastCustomSpell(caster, SPELL_WARLOCK_LIFE_TAP_ENERGIZE_2, &manaFeedVal, NULL, NULL, true, NULL);
                    }
                }
            }

            SpellCastResult CheckCast()
            {
                if (int32(GetCaster()->GetHealth()) > int32(GetCaster()->CountPctFromMaxHealth(GetSpellInfo()->Effects[EFFECT_2].CalcValue())))
                    return SPELL_CAST_OK;
                return SPELL_FAILED_FIZZLE;
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warl_life_tap_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
                OnCheckCast += SpellCheckCastFn(spell_warl_life_tap_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_life_tap_SpellScript();
        }
};

// 27285 - Seed of Corruption
/// Updated 4.3.4
class spell_warl_seed_of_corruption : public SpellScriptLoader
{
    public:
        spell_warl_seed_of_corruption() : SpellScriptLoader("spell_warl_seed_of_corruption") { }

        class spell_warl_seed_of_corruption_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_seed_of_corruption_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                if (GetExplTargetUnit())
                    targets.remove(GetExplTargetUnit());
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warl_seed_of_corruption_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_seed_of_corruption_SpellScript();
        }
};

// 29858 - Soulshatter
/// Updated 4.3.4
class spell_warl_soulshatter : public SpellScriptLoader
{
    public:
        spell_warl_soulshatter() : SpellScriptLoader("spell_warl_soulshatter") { }

        class spell_warl_soulshatter_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_soulshatter_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARLOCK_SOULSHATTER))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                if (Unit* target = GetHitUnit())
                    if (target->CanHaveThreatList() && target->getThreatManager().getThreat(caster) > 0.0f)
                        caster->CastSpell(target, SPELL_WARLOCK_SOULSHATTER, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warl_soulshatter_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_soulshatter_SpellScript();
        }
};

// 30108, 34438, 34439, 35183 - Unstable Affliction
/// Updated 4.3.4
class spell_warl_unstable_affliction : public SpellScriptLoader
{
    public:
        spell_warl_unstable_affliction() : SpellScriptLoader("spell_warl_unstable_affliction") { }

        class spell_warl_unstable_affliction_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_unstable_affliction_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARLOCK_UNSTABLE_AFFLICTION_DISPEL))
                    return false;
                return true;
            }

            void HandleDispel(DispelInfo* dispelInfo)
            {
                if (Unit* caster = GetCaster())
                    if (AuraEffect const* aurEff = GetEffect(EFFECT_0))
                    {
                        int32 damage = aurEff->GetAmount() * 9;
                        // backfire damage and silence
                        caster->CastCustomSpell(dispelInfo->GetDispeller(), SPELL_WARLOCK_UNSTABLE_AFFLICTION_DISPEL, &damage, NULL, NULL, true, NULL, aurEff);
                    }
            }

            void Register()
            {
                AfterDispel += AuraDispelFn(spell_warl_unstable_affliction_AuraScript::HandleDispel);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_unstable_affliction_AuraScript();
        }
};

void AddSC_warlock_spell_scripts()
{
	new spell_warl_hand_of_guldan();
    new spell_warl_armor_nether_ward_ignore();
    new spell_warl_fel_flame();
    new spell_warl_incinerate();
    new spell_warl_curse_of_the_elements();
    new spell_warl_soul_swap();
    new spell_warl_soul_swap_buff();
    new spell_warl_soul_swap_exhale();
    new spell_warl_drain_life();
    new spell_warl_drain_soul();
    new spell_warl_banish();
    new spell_warl_demonic_empowerment();
    new spell_warl_create_healthstone();
    new spell_warl_everlasting_affliction();
    new spell_warl_seed_of_corruption_dot();
    new spell_warl_seed_of_corruption();
    new spell_warl_soulshatter();
    new spell_warl_life_tap();
    new spell_warl_demonic_circle_summon();
    new spell_warl_demonic_circle_teleport();
    new spell_warl_haunt();
    new spell_warl_unstable_affliction();
    new spell_warl_bane_of_doom();
    new spell_warl_health_funnel();
}
