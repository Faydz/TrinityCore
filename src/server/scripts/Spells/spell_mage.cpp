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
 * Scripts for spells with SPELLFAMILY_MAGE and SPELLFAMILY_GENERIC spells used by mage players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_mage_".
 */

#include "Player.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuras.h"
#include "SpellAuraEffects.h"
#include "Pet.h"

enum MageSpells
{
    SPELL_MAGE_FLAMESTRIKE                       = 2120,

    SPELL_MAGE_CHILLED_R1                        = 12484,
    SPELL_MAGE_CHILLED_R2                        = 12485,

    SPELL_MAGE_COLD_SNAP                         = 11958,

    SPELL_MAGE_CONE_OF_COLD_AURA_R1              = 11190,
    SPELL_MAGE_CONE_OF_COLD_AURA_R2              = 12489,
    SPELL_MAGE_CONE_OF_COLD_TRIGGER_R1           = 83301,
    SPELL_MAGE_CONE_OF_COLD_TRIGGER_R2           = 83302,

    SPELL_MAGE_FROST_WARDING_R1                  = 28332,
    SPELL_MAGE_FROST_WARDING_TRIGGERED           = 57776,

    SPELL_MAGE_SHATTERED_BARRIER_R1              = 44745,
    SPELL_MAGE_SHATTERED_BARRIER_R2              = 54787,
    SPELL_MAGE_SHATTERED_BARRIER_FREEZE_R1       = 55080,
    SPELL_MAGE_SHATTERED_BARRIER_FREEZE_R2       = 83073,

    SPELL_MAGE_INCANTER_S_ABSORPTION_TRIGGERED   = 44413,
    SPELL_MAGE_INCANTER_S_ABSORPTION_KNOCKBACK   = 86261,

    SPELL_MAGE_SQUIRREL_FORM                     = 32813,
    SPELL_MAGE_GIRAFFE_FORM                      = 32816,
    SPELL_MAGE_SERPENT_FORM                      = 32817,
    SPELL_MAGE_DRAGONHAWK_FORM                   = 32818,
    SPELL_MAGE_WORGEN_FORM                       = 32819,
    SPELL_MAGE_SHEEP_FORM                        = 32820,

    SPELL_MAGE_IMPROVED_MANA_GEM_TRIGGERED       = 83098,

    SPELL_MAGE_GLYPH_OF_ETERNAL_WATER            = 70937,
    SPELL_MAGE_SUMMON_WATER_ELEMENTAL_PERMANENT  = 70908,
    SPELL_MAGE_SUMMON_WATER_ELEMENTAL_TEMPORARY  = 70907,
    SPELL_MAGE_RING_OF_FROST_SUMMON              = 82676,
    SPELL_MAGE_RING_OF_FROST_FREEZE              = 82691,
    SPELL_MAGE_RING_OF_FROST_DUMMY               = 91264,

    SPELL_MAGE_FINGERS_OF_FROST                  = 44544,
    MAGE_SPELL_CAUTERIZE_HEAL                    = 87023,

    SPELL_MAGE_RING_OF_FROST_OBJ_ENTRY           = 44199,

    SPELL_MAGE_FROSTFIRE_BOLT                    = 44614,
};

enum MageIcons
{
    ICON_MAGE_SHATTER                            = 976,
    ICON_MAGE_IMPROVED_FLAMESTRIKE               = 37,
    ICON_MAGE_IMPROVED_FREEZE                    = 94,
    ICON_MAGE_INCANTER_S_ABSORPTION              = 2941,
    ICON_MAGE_IMPROVED_MANA_GEM                  = 1036,
    SPELL_MAGE_PIERCING_CHILL                    = 4625,
};

enum ArcaneBlastSpells
{
    SPELL_ARCANE_BLAST                      = 30451,    
    SPELL_SLOW                              = 31589,
};

// 44544 - Fingers of Frost
class spell_fingers_of_frost : public SpellScriptLoader
{
    public:
        spell_fingers_of_frost() : SpellScriptLoader("spell_fingers_of_frost") { }

        class spell_fingers_of_frost_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_fingers_of_frost_SpellScript);
            
            void HandleBeforeHit()
            {
                Unit* caster = GetCaster();
                Unit* target = GetExplTargetUnit();
                
                if(caster && target && caster->HasAura(SPELL_MAGE_FINGERS_OF_FROST))
                {
                    if(GetSpellInfo()->Id == SPELL_MAGE_FROSTFIRE_BOLT && GetSpell()->GetCastTime() != 0)
                        return;

                    target->ModifyAuraState(AURA_STATE_FROZEN, true);
                }
            }

            void HandleAfterHit()
            {
                Unit* caster = GetCaster();
                Unit* target = GetExplTargetUnit();

                if(caster && target && caster->HasAura(SPELL_MAGE_FINGERS_OF_FROST))
                {
                    if(GetSpellInfo()->Id == SPELL_MAGE_FROSTFIRE_BOLT && GetSpell()->GetCastTime() != 0)
                        return;

                    target->ModifyAuraState(AURA_STATE_FROZEN, false);
                }
            }

            void Register()
            {
                BeforeCast += SpellCastFn(spell_fingers_of_frost_SpellScript::HandleBeforeHit);
                AfterHit += SpellHitFn(spell_fingers_of_frost_SpellScript::HandleAfterHit);
            }
        };

        class spell_fingers_of_frost_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_fingers_of_frost_AuraScript);
            
            void HandleProc(AuraEffect const* aurEff, ProcEventInfo& /*eventInfo*/)
            {
                PreventDefaultAction();

                aurEff->GetBase()->ModStackAmount(-1);
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_fingers_of_frost_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_ABILITY_IGNORE_AURASTATE);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_fingers_of_frost_SpellScript();
        }

        AuraScript* GetAuraScript() const
        {
            return new spell_fingers_of_frost_AuraScript();
        }
};

// 44614 - Frostfire Bolt
class spell_mage_frostfire_bolt : public SpellScriptLoader
{
    public:
        spell_mage_frostfire_bolt() : SpellScriptLoader("spell_mage_frostfire_bolt") { }
        
        class spell_mage_frostfire_bolt_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_mage_frostfire_bolt_AuraScript);

            void CalculateAmount(AuraEffect const* aurEff, int32& amount, bool& /*canBeRecalculated*/)
            {
                if(Unit* caster = GetCaster())
                {
                    if(caster->HasAura(61205))
                    {
                        amount = 0;
                    }
                }
            }
            
            void UpdateAmount(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                if(Unit* caster = GetCaster())
                {
                    if(!caster->HasAura(61205))
                    {
                        aurEff->GetBase()->SetStackAmount(1);
                    }
                }
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_mage_frostfire_bolt_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_MOD_DECREASE_SPEED);
                AfterEffectApply += AuraEffectApplyFn(spell_mage_frostfire_bolt_AuraScript::UpdateAmount, EFFECT_0, SPELL_AURA_MOD_DECREASE_SPEED, AURA_EFFECT_HANDLE_CHANGE_AMOUNT_MASK);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_mage_frostfire_bolt_AuraScript();
        }
};

// 83154 - Piercing Chill
class spell_mage_piercing_chill : public SpellScriptLoader
{
    public:
        spell_mage_piercing_chill() : SpellScriptLoader("spell_mage_piercing_chill") { }

        class spell_mage_piercing_chill_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_piercing_chill_SpellScript);

            void HandleTargetSelectEff0(std::list<WorldObject*>& targets)
            {
                if(Unit* caster = GetCaster())
                {
                    targets.remove(GetExplTargetUnit());

                   if(AuraEffect* aurEff = caster->GetDummyAuraEffect(SPELLFAMILY_MAGE, SPELL_MAGE_PIERCING_CHILL, EFFECT_0))
                   {
                       Trinity::Containers::RandomResizeList(targets, aurEff->GetAmount());
                       choosenTargets = targets;
                   }
                }
            }

            void RemoveTargetEffect(WorldObject*& target)
            {
                target = NULL;
            }

            void HandleTargetSelectEff2(std::list<WorldObject*>& targets)
            {
                targets.clear();

                if(!choosenTargets.empty())
                {
                    targets = choosenTargets;
                }
            }

        private:
            std::list<WorldObject*> choosenTargets;

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_mage_piercing_chill_SpellScript::HandleTargetSelectEff0, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
                OnObjectTargetSelect += SpellObjectTargetSelectFn(spell_mage_piercing_chill_SpellScript::RemoveTargetEffect, EFFECT_2, TARGET_UNIT_TARGET_ENEMY);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_mage_piercing_chill_SpellScript::HandleTargetSelectEff2, EFFECT_2, TARGET_UNIT_DEST_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_piercing_chill_SpellScript();
        }
};

// 82676 - Ring of Frost
class spell_mage_ring_of_frost : public SpellScriptLoader
{
    public:
        spell_mage_ring_of_frost() : SpellScriptLoader("spell_mage_ring_of_frost") { }

        class spell_mage_ring_of_frost_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_ring_of_frost_SpellScript);

            void HandleBeforeCast()
            {
                if (Unit* caster = GetCaster())
                {
                    std::list<Creature*> unitList;
                    caster->GetCreatureListWithEntryInGrid(unitList, SPELL_MAGE_RING_OF_FROST_OBJ_ENTRY, 100.0f);

                    for (std::list<Creature*>::const_iterator itr = unitList.begin(); itr != unitList.end(); ++itr)
                    {
                        if (TempSummon* tSummon = (*itr)->ToTempSummon())
                        {
                            if (tSummon->GetSummonerGUID() == caster->GetGUID())
                                tSummon->UnSummon();
                        }
                    }
                }
            }

            void Register()
            {
                BeforeCast += SpellCastFn(spell_mage_ring_of_frost_SpellScript::HandleBeforeCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_ring_of_frost_SpellScript();
        }
};

class spell_mage_arcane_blast : public SpellScriptLoader
{
public:
    spell_mage_arcane_blast() : SpellScriptLoader("spell_mage_arcane_blast") { }

    class spell_mage_arcane_blast_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_mage_arcane_blast_SpellScript);

        void HandleBlastScript(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            if (!caster  || caster->GetTypeId() !=TYPEID_PLAYER)
                return;

            if (Unit* unitTarget = GetHitUnit())
            {
                if (AuraEffect* aurEff = caster->GetDummyAuraEffect(SPELLFAMILY_MAGE, 2294, 0)) //Nether vortex
                { 
                    if (aurEff->GetId() == 86181 && !roll_chance_i(50)) //Nether vortex rank 1
                            return;

                    bool castSlow = true;
                    Unit::AuraList& scAuras = caster->GetSingleCastAuras();
                    for (Unit::AuraList::iterator iter = scAuras.begin(); iter != scAuras.end();) //Check other applications of slow
                    {
                        Aura* aura = *iter;
                        if (aura)
                        {
                            if (aura->GetId() == SPELL_SLOW)
                            {
                                castSlow = false;
                                break;
                            }
                        }
                        ++iter;
                    }
                    if (castSlow)
                        caster->AddAura(SPELL_SLOW, unitTarget);
                }
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_mage_arcane_blast_SpellScript::HandleBlastScript, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_mage_arcane_blast_SpellScript();
    }
};

class spell_mage_blast_wave : public SpellScriptLoader
{
    public:
        spell_mage_blast_wave() : SpellScriptLoader("spell_mage_blast_wave") { }

        class spell_mage_blast_wave_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_blast_wave_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_FLAMESTRIKE))
                    return false;
                return true;
            }

            void CountTargets(std::list<WorldObject*>& targetList)
            {
                _targetCount = targetList.size();
            }

            void HandleImprovedFlamestrike()
            {
                if (_targetCount >= 2)
                    if (AuraEffect* aurEff = GetCaster()->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_MAGE, ICON_MAGE_IMPROVED_FLAMESTRIKE, EFFECT_0))
                        if (roll_chance_i(aurEff->GetAmount()))
                        {
                            float x, y, z;
                            WorldLocation const* loc = GetExplTargetDest();
                            if (!loc)
                                return;

                            loc->GetPosition(x, y, z);
                            GetCaster()->CastSpell(x, y, z, SPELL_MAGE_FLAMESTRIKE, true);
                        }
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_mage_blast_wave_SpellScript::CountTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
                AfterCast += SpellCastFn(spell_mage_blast_wave_SpellScript::HandleImprovedFlamestrike);
            }

        private:
            uint32 _targetCount;
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_blast_wave_SpellScript();
        }
};

class spell_pyromaniac : public SpellScriptLoader
{
    public:
        spell_pyromaniac() : SpellScriptLoader("spell_pyromaniac") { }

        class spell_pyromaniac_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pyromaniac_SpellScript);

            /*bool Validate(SpellInfo const* /*spellEntry* /)
            {
                if (!sSpellMgr->GetSpellInfo(11355) && !sSpellMgr->GetSpellInfo(2120))
                    return false;
                return true;
            } */

            void CountTargets(std::list<WorldObject*>& targetList)
            {
                _targetCount = targetList.size();
                if (_targetCount >= 3 && GetCaster() && GetCaster()->ToPlayer()){
                    if (AuraEffect* aurEff = GetCaster()->GetDummyAuraEffect(SPELLFAMILY_MAGE, 2128, 0))
                    {
                        Player* player = GetCaster()->ToPlayer();
                        int32 bh=10;
                        if (aurEff->GetId() == 34293)
                            bh=5;
                        player->CastCustomSpell(player, 83582, &bh, NULL, NULL, true);
                        if(player->GetAura(83582)){
                            player->GetAura(83582)->SetDuration(10000);
                        }
                    }
                }
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pyromaniac_SpellScript::CountTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
            }

        private:
            uint32 _targetCount;
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_pyromaniac_SpellScript();
        }
};

// 42208 Blizzard
/// Updated 4.3.4
class spell_mage_blizzard : public SpellScriptLoader
{
   public:
       spell_mage_blizzard() : SpellScriptLoader("spell_mage_blizzard") { }
 
       class spell_mage_blizzard_SpellScript : public SpellScript
       {
           PrepareSpellScript(spell_mage_blizzard_SpellScript);
 
           bool Validate(SpellInfo const* /*spellEntry*/)
           {
               if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_CHILLED_R1))
                   return false;
               if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_CHILLED_R2))
                   return false;
               return true;
           }
 
           void AddChillEffect(SpellEffIndex /*effIndex*/)
           {
               Unit* caster = GetCaster();
               if (Unit* unitTarget = GetHitUnit())
               {
                   if (caster->IsScriptOverriden(GetSpellInfo(), 836))
                       caster->CastSpell(unitTarget, SPELL_MAGE_CHILLED_R1, true);
                   else if (caster->IsScriptOverriden(GetSpellInfo(), 988))
                       caster->CastSpell(unitTarget, SPELL_MAGE_CHILLED_R2, true);
               }
           }
 
           void Register()
           {
               OnEffectHitTarget += SpellEffectFn(spell_mage_blizzard_SpellScript::AddChillEffect, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
           }
       };
 
       SpellScript *GetSpellScript() const
       {
           return new spell_mage_blizzard_SpellScript();
       }
};

// 11958 - Cold Snap
class spell_mage_cold_snap : public SpellScriptLoader
{
    public:
        spell_mage_cold_snap() : SpellScriptLoader("spell_mage_cold_snap") { }

        class spell_mage_cold_snap_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_cold_snap_SpellScript);

            bool Load()
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Player* caster = GetCaster()->ToPlayer();
                // immediately finishes the cooldown on Frost spells
                const SpellCooldowns& cm = caster->GetSpellCooldownMap();
                for (SpellCooldowns::const_iterator itr = cm.begin(); itr != cm.end();)
                {
                    SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(itr->first);

                    if (spellInfo->SpellFamilyName == SPELLFAMILY_MAGE &&
                        (spellInfo->GetSchoolMask() & SPELL_SCHOOL_MASK_FROST) &&
                        spellInfo->Id != SPELL_MAGE_COLD_SNAP && spellInfo->GetRecoveryTime() > 0)
                    {
                        caster->RemoveSpellCooldown((itr++)->first, true);
                    }
                    else
                        ++itr;
                }
            }

            void Register()
            {
                OnEffectHit += SpellEffectFn(spell_mage_cold_snap_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_cold_snap_SpellScript();
        }
};

// 120 - Cone of Cold
/// Updated 4.3.4
class spell_mage_cone_of_cold : public SpellScriptLoader
{
    public:
        spell_mage_cone_of_cold() : SpellScriptLoader("spell_mage_cone_of_cold") { }

        class spell_mage_cone_of_cold_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_cone_of_cold_SpellScript);

            void HandleConeOfColdScript(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                if (Unit* unitTarget = GetHitUnit())
                {
                    if (caster->HasAura(SPELL_MAGE_CONE_OF_COLD_AURA_R1)) // Improved Cone of Cold Rank 1
                        unitTarget->CastSpell(unitTarget, SPELL_MAGE_CONE_OF_COLD_TRIGGER_R1, true);
                    else if (caster->HasAura(SPELL_MAGE_CONE_OF_COLD_AURA_R2)) // Improved Cone of Cold Rank 2
                        unitTarget->CastSpell(unitTarget, SPELL_MAGE_CONE_OF_COLD_TRIGGER_R2, true);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_mage_cone_of_cold_SpellScript::HandleConeOfColdScript, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_cone_of_cold_SpellScript();
        }
};

// 42955 Conjure Refreshment
/// Updated 4.3.4
struct ConjureRefreshmentData
{
    uint32 minLevel;
    uint32 maxLevel;
    uint32 spellId;
};

uint8 const MAX_CONJURE_REFRESHMENT_SPELLS = 7;
ConjureRefreshmentData const _conjureData[MAX_CONJURE_REFRESHMENT_SPELLS] =
{
    { 33, 43, 92739 },
    { 44, 53, 92799 },
    { 54, 63, 92802 },
    { 64, 73, 92805 },
    { 74, 79, 74625 },
    { 80, 84, 92822 },
    { 85, 85, 92727 }
};

// 42955 - Conjure Refreshment
class spell_mage_conjure_refreshment : public SpellScriptLoader
{
    public:
        spell_mage_conjure_refreshment() : SpellScriptLoader("spell_mage_conjure_refreshment") { }

        class spell_mage_conjure_refreshment_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_conjure_refreshment_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                for (uint8 i = 0; i < MAX_CONJURE_REFRESHMENT_SPELLS; ++i)
                    if (!sSpellMgr->GetSpellInfo(_conjureData[i].spellId))
                        return false;
                return true;
            }

            bool Load()
            {
                if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                uint8 level = GetHitUnit()->getLevel();
                for (uint8 i = 0; i < MAX_CONJURE_REFRESHMENT_SPELLS; ++i)
                {
                    ConjureRefreshmentData const& spellData = _conjureData[i];
                    if (level < spellData.minLevel || level > spellData.maxLevel)
                        continue;
                    GetHitUnit()->CastSpell(GetHitUnit(), spellData.spellId);
                    break;
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_mage_conjure_refreshment_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_conjure_refreshment_SpellScript();
        }
};

// -6143, -543 - Frost Warding
class spell_mage_frost_warding_trigger : public SpellScriptLoader
{
    public:
        spell_mage_frost_warding_trigger() : SpellScriptLoader("spell_mage_frost_warding_trigger") { }

        class spell_mage_frost_warding_trigger_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_mage_frost_warding_trigger_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_FROST_WARDING_TRIGGERED) || !sSpellMgr->GetSpellInfo(SPELL_MAGE_FROST_WARDING_R1))
                    return false;
                return true;
            }

            void Absorb(AuraEffect* aurEff, DamageInfo & dmgInfo, uint32 & absorbAmount)
            {
                Unit* target = GetTarget();
                if (AuraEffect* talentAurEff = target->GetAuraEffectOfRankedSpell(SPELL_MAGE_FROST_WARDING_R1, EFFECT_0))
                {
                    int32 chance = talentAurEff->GetSpellInfo()->Effects[EFFECT_1].CalcValue();

                    if (roll_chance_i(chance))
                    {
                        int32 bp = dmgInfo.GetDamage();
                        dmgInfo.AbsorbDamage(bp);
                        target->CastCustomSpell(target, SPELL_MAGE_FROST_WARDING_TRIGGERED, &bp, NULL, NULL, true, NULL, aurEff);
                        absorbAmount = 0;
                        PreventDefaultAction();
                    }
                }
            }

            void Register()
            {
                 OnEffectAbsorb += AuraEffectAbsorbFn(spell_mage_frost_warding_trigger_AuraScript::Absorb, EFFECT_0);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_mage_frost_warding_trigger_AuraScript();
        }
};

// 116 - Frostbolt
/// Updated 4.3.4
class spell_mage_frostbolt : public SpellScriptLoader
{
   public:
       spell_mage_frostbolt() : SpellScriptLoader("spell_mage_frostbolt") { }

       class spell_mage_frostbolt_SpellScript : public SpellScript
       {
           PrepareSpellScript(spell_mage_frostbolt_SpellScript);

           void RecalculateDamage(SpellEffIndex /*effIndex*/)
           {
               if (GetHitUnit() && GetHitUnit()->HasAuraState(AURA_STATE_FROZEN, GetSpellInfo(), GetCaster()))
               {
                   if (AuraEffect* aurEff = GetCaster()->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_MAGE, ICON_MAGE_SHATTER, EFFECT_1))
                   {
                       int32 damage = GetHitDamage();
                       AddPct(damage, aurEff->GetAmount());
                       SetHitDamage(damage);
                   }
               }
           }

           void Register()
           {
               OnEffectHitTarget += SpellEffectFn(spell_mage_frostbolt_SpellScript::RecalculateDamage, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
           }
       };

       SpellScript* GetSpellScript() const
       {
           return new spell_mage_frostbolt_SpellScript();
       }
};

// -44457 - Living Bomb
class spell_mage_living_bomb : public SpellScriptLoader
{
    public:
        spell_mage_living_bomb() : SpellScriptLoader("spell_mage_living_bomb") { }

        class spell_mage_living_bomb_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_mage_living_bomb_AuraScript);

            bool Validate(SpellInfo const* spellInfo)
            {
                if (!sSpellMgr->GetSpellInfo(uint32(spellInfo->Effects[EFFECT_1].CalcValue())))
                    return false;
                return true;
            }

            void AfterRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                AuraRemoveMode removeMode = GetTargetApplication()->GetRemoveMode();
                if (removeMode != AURA_REMOVE_BY_ENEMY_SPELL && removeMode != AURA_REMOVE_BY_EXPIRE)
                    return;

                if (Unit* caster = GetCaster())
                    caster->CastSpell(GetTarget(), uint32(aurEff->GetAmount()), true, NULL, aurEff);
            }

            void Register()
            {
                AfterEffectRemove += AuraEffectRemoveFn(spell_mage_living_bomb_AuraScript::AfterRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_mage_living_bomb_AuraScript();
        }
};

// 11426 - Ice Barrier
/// Updated 4.3.4
class spell_mage_ice_barrier : public SpellScriptLoader
{
   public:
       spell_mage_ice_barrier() : SpellScriptLoader("spell_mage_ice_barrier") { }

       class spell_mage_ice_barrier_AuraScript : public AuraScript
       {
           PrepareAuraScript(spell_mage_ice_barrier_AuraScript);

           void AfterRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
           {
               if (GetTargetApplication()->GetRemoveMode() != AURA_REMOVE_BY_ENEMY_SPELL)
                   return;

               if (GetTarget()->HasAura(SPELL_MAGE_SHATTERED_BARRIER_R1))
                   GetTarget()->CastSpell(GetTarget(), SPELL_MAGE_SHATTERED_BARRIER_FREEZE_R1, true);
               else if (GetTarget()->HasAura(SPELL_MAGE_SHATTERED_BARRIER_R2))
                   GetTarget()->CastSpell(GetTarget(), SPELL_MAGE_SHATTERED_BARRIER_FREEZE_R2, true);
           }

           void CalculateAmount(AuraEffect const* aurEff, int32& amount, bool& canBeRecalculated)
            {
                canBeRecalculated = false;
                if (Unit* caster = GetCaster())
                {
                    // +80.68% from sp bonus
                    float bonus = 0.8068f;
                    bonus *= caster->SpellBaseDamageBonusDone(GetSpellInfo()->GetSchoolMask());
                    amount += int32(bonus);
                    //Glyph of ice barrier
                    if (caster->HasAura(63095)) amount *= 1.3f;
                }
            }

           void Register()
           {
               DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_mage_ice_barrier_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB); 
               AfterEffectRemove += AuraEffectRemoveFn(spell_mage_ice_barrier_AuraScript::AfterRemove, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB, AURA_EFFECT_HANDLE_REAL);
           }
       };

       AuraScript* GetAuraScript() const
       {
           return new spell_mage_ice_barrier_AuraScript();
       }
};

// 1463 - Mana Shield
/// Updated 4.3.4
class spell_mage_mana_shield : public SpellScriptLoader
{
    public:
       spell_mage_mana_shield() : SpellScriptLoader("spell_mage_mana_shield") { }

       class spell_mage_mana_shield_AuraScript : public AuraScript
       {
           PrepareAuraScript(spell_mage_mana_shield_AuraScript);

           void HandleAbsorb(AuraEffect* /*aurEff*/, DamageInfo & /*dmgInfo*/, uint32 & absorbAmount)
           {
               if (AuraEffect* aurEff = GetTarget()->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_GENERIC, ICON_MAGE_INCANTER_S_ABSORPTION, EFFECT_0))
               {
                   int32 bp = CalculatePct(absorbAmount, aurEff->GetAmount());
                   GetTarget()->CastCustomSpell(GetTarget(), SPELL_MAGE_INCANTER_S_ABSORPTION_TRIGGERED, &bp, NULL, NULL, true);
               }
           }

           void AfterRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
           {
               if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_ENEMY_SPELL)
                   GetTarget()->CastSpell(GetTarget(), SPELL_MAGE_INCANTER_S_ABSORPTION_KNOCKBACK, true);
           }

           void Register()
           {
                AfterEffectManaShield += AuraEffectManaShieldFn(spell_mage_mana_shield_AuraScript::HandleAbsorb, EFFECT_0);
                AfterEffectRemove += AuraEffectRemoveFn(spell_mage_mana_shield_AuraScript::AfterRemove, EFFECT_0, SPELL_AURA_MANA_SHIELD, AURA_EFFECT_HANDLE_REAL);
           }
       };

       AuraScript* GetAuraScript() const
       {
           return new spell_mage_mana_shield_AuraScript();
       }
};

// 543 - Mage Ward
/// Updated 4.3.4
class spell_mage_mage_ward : public SpellScriptLoader
{
    public:
        spell_mage_mage_ward() : SpellScriptLoader("spell_mage_mage_ward") { }

        class spell_mage_mage_ward_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_mage_mage_ward_AuraScript);

            void HandleAbsorb(AuraEffect* /*aurEff*/, DamageInfo & /*dmgInfo*/, uint32 & absorbAmount)
            {
                if (AuraEffect* aurEff = GetTarget()->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_GENERIC, ICON_MAGE_INCANTER_S_ABSORPTION, EFFECT_0))
                {
                    int32 bp = CalculatePct(absorbAmount, aurEff->GetAmount());
                    GetTarget()->CastCustomSpell(GetTarget(), SPELL_MAGE_INCANTER_S_ABSORPTION_TRIGGERED, &bp, NULL, NULL, true);
                }
            }
             
            void CalculateAmount(AuraEffect const* aurEff, int32& amount, bool& canBeRecalculated)
            {
                canBeRecalculated = false;
                if (Unit* caster = GetCaster())
                {
                    // +80.68% from sp bonus
                    float bonus = 0.8068f;
                    bonus *= caster->SpellBaseDamageBonusDone(GetSpellInfo()->GetSchoolMask());
                    amount += int32(bonus);
                }
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_mage_mage_ward_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB); 
                AfterEffectAbsorb += AuraEffectAbsorbFn(spell_mage_mage_ward_AuraScript::HandleAbsorb, EFFECT_0);
            }
       };

       AuraScript* GetAuraScript() const
       {
           return new spell_mage_mage_ward_AuraScript();
       }
};

enum SilvermoonPolymorph
{
    NPC_AUROSALIA       = 18744
};

/// @todo move out of here and rename - not a mage spell
// 32826 - Polymorph (Visual)
class spell_mage_polymorph_cast_visual : public SpellScriptLoader
{
    public:
        spell_mage_polymorph_cast_visual() : SpellScriptLoader("spell_mage_polymorph_visual") { }

        class spell_mage_polymorph_cast_visual_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_polymorph_cast_visual_SpellScript);

            static const uint32 PolymorhForms[6];

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                // check if spell ids exist in dbc
                for (uint32 i = 0; i < 6; i++)
                    if (!sSpellMgr->GetSpellInfo(PolymorhForms[i]))
                        return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Unit* target = GetCaster()->FindNearestCreature(NPC_AUROSALIA, 30.0f))
                    if (target->GetTypeId() == TYPEID_UNIT)
                        target->CastSpell(target, PolymorhForms[urand(0, 5)], true);
            }

            void Register()
            {
                // add dummy effect spell handler to Polymorph visual
                OnEffectHitTarget += SpellEffectFn(spell_mage_polymorph_cast_visual_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_polymorph_cast_visual_SpellScript();
        }
};

uint32 const spell_mage_polymorph_cast_visual::spell_mage_polymorph_cast_visual_SpellScript::PolymorhForms[6] =
{
    SPELL_MAGE_SQUIRREL_FORM,
    SPELL_MAGE_GIRAFFE_FORM,
    SPELL_MAGE_SERPENT_FORM,
    SPELL_MAGE_DRAGONHAWK_FORM,
    SPELL_MAGE_WORGEN_FORM,
    SPELL_MAGE_SHEEP_FORM
};

// 5405  - Replenish Mana (Mana Gem)
/// Updated 4.3.4
class spell_mage_replenish_mana : public SpellScriptLoader
{
   public:
       spell_mage_replenish_mana() : SpellScriptLoader("spell_mage_replenish_mana") { }

       class spell_mage_replenish_mana_SpellScript : public SpellScript
       {
           PrepareSpellScript(spell_mage_replenish_mana_SpellScript);

           bool Validate(SpellInfo const* /*spellInfo*/)
           {
               if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_IMPROVED_MANA_GEM_TRIGGERED))
                   return false;
               return true;
           }

           void HandleImprovedManaGem()
           {
               if (AuraEffect* aurEff = GetCaster()->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_MAGE, ICON_MAGE_IMPROVED_MANA_GEM, EFFECT_0))
               {
                   int32 bp = CalculatePct(GetCaster()->GetMaxPower(POWER_MANA), aurEff->GetAmount());
                   GetCaster()->CastCustomSpell(GetCaster(), SPELL_MAGE_IMPROVED_MANA_GEM_TRIGGERED, &bp, &bp, NULL, true);
               }
           }

           void Register()
           {
               AfterCast += SpellCastFn(spell_mage_replenish_mana_SpellScript::HandleImprovedManaGem);
           }
       };

       SpellScript* GetSpellScript() const
       {
           return new spell_mage_replenish_mana_SpellScript();
       }
};

// 82691 - Ring of Frost (freeze efect)
/// Updated 4.3.4
class spell_mage_ring_of_frost_freeze : public SpellScriptLoader
{
    public:
        spell_mage_ring_of_frost_freeze() : SpellScriptLoader("spell_mage_ring_of_frost_freeze") { }

        class spell_mage_ring_of_frost_freeze_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_ring_of_frost_freeze_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_RING_OF_FROST_SUMMON))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_RING_OF_FROST_FREEZE))
                    return false;
                return true;
            }

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                float outRadius = sSpellMgr->GetSpellInfo(SPELL_MAGE_RING_OF_FROST_SUMMON)->Effects[EFFECT_0].CalcRadius();
                float inRadius  = 4.7f;

                for (std::list<WorldObject*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
                    if (Unit* unit = (*itr)->ToUnit())
                        if (unit->HasAura(SPELL_MAGE_RING_OF_FROST_DUMMY) || unit->HasAura(SPELL_MAGE_RING_OF_FROST_FREEZE) || unit->GetExactDist(GetExplTargetDest()) > outRadius || unit->GetExactDist(GetExplTargetDest()) < inRadius)
                            targets.erase(itr--);
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_mage_ring_of_frost_freeze_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_ring_of_frost_freeze_SpellScript();
        }

        class spell_mage_ring_of_frost_freeze_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_mage_ring_of_frost_freeze_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_RING_OF_FROST_DUMMY))
                    return false;
                return true;
            }

            void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                if (GetTargetApplication()->GetRemoveMode() != AURA_REMOVE_BY_EXPIRE)
                    if (GetCaster())
                        GetCaster()->CastSpell(GetTarget(), SPELL_MAGE_RING_OF_FROST_DUMMY, true);
            }

            void Register()
            {
                AfterEffectRemove += AuraEffectRemoveFn(spell_mage_ring_of_frost_freeze_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_MOD_STUN, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_mage_ring_of_frost_freeze_AuraScript();
        }
};

// 31687 - Summon Water Elemental
class spell_mage_summon_water_elemental : public SpellScriptLoader
{
    public:
        spell_mage_summon_water_elemental() : SpellScriptLoader("spell_mage_summon_water_elemental") { }

        class spell_mage_summon_water_elemental_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_summon_water_elemental_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_GLYPH_OF_ETERNAL_WATER) || !sSpellMgr->GetSpellInfo(SPELL_MAGE_SUMMON_WATER_ELEMENTAL_TEMPORARY) || !sSpellMgr->GetSpellInfo(SPELL_MAGE_SUMMON_WATER_ELEMENTAL_PERMANENT))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();

                if (Player* player = caster->ToPlayer())
                    if (Guardian* elemental = player->GetGuardianPet())
                        // Check if the pet we are going to unsummon is the mage's water elemental
                        if (elemental->GetEntry() == uint32(sSpellMgr->GetSpellInfo(SPELL_MAGE_SUMMON_WATER_ELEMENTAL_TEMPORARY)->Effects[EFFECT_0].MiscValue) ||
                            elemental->GetEntry() == uint32(sSpellMgr->GetSpellInfo(SPELL_MAGE_SUMMON_WATER_ELEMENTAL_PERMANENT)->Effects[EFFECT_0].MiscValue))
                            elemental->UnSummon();

                // Glyph of Eternal Water
                if (caster->HasAura(SPELL_MAGE_GLYPH_OF_ETERNAL_WATER))
                    caster->CastSpell(caster, SPELL_MAGE_SUMMON_WATER_ELEMENTAL_PERMANENT, true);
                else
                    caster->CastSpell(caster, SPELL_MAGE_SUMMON_WATER_ELEMENTAL_TEMPORARY, true);
            }

            void Register()
            {
                // add dummy effect spell handler to Summon Water Elemental
                OnEffectHit += SpellEffectFn(spell_mage_summon_water_elemental_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_summon_water_elemental_SpellScript();
        }
};

// 33395 Water Elemental's Freeze
/// Updated 4.3.4
class spell_mage_water_elemental_freeze : public SpellScriptLoader
{
   public:
       spell_mage_water_elemental_freeze() : SpellScriptLoader("spell_mage_water_elemental_freeze") { }

       class spell_mage_water_elemental_freeze_SpellScript : public SpellScript
       {
           PrepareSpellScript(spell_mage_water_elemental_freeze_SpellScript);

           bool Validate(SpellInfo const* /*spellInfo*/)
           {
               if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_FINGERS_OF_FROST))
                   return false;
               return true;
           }

           void CountTargets(std::list<WorldObject*>& targetList)
           {
               _didHit = !targetList.empty();
           }

           void HandleImprovedFreeze()
           {
               if (!_didHit)
                   return;

               Unit* owner = GetCaster()->GetOwner();
               if (!owner)
                   return;

               if (AuraEffect* aurEff = owner->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_MAGE, ICON_MAGE_IMPROVED_FREEZE, EFFECT_0))
               {
                   if (roll_chance_i(aurEff->GetAmount()))
                       owner->CastCustomSpell(SPELL_MAGE_FINGERS_OF_FROST, SPELLVALUE_AURA_STACK, 2, owner, true);
               }
           }

           void Register()
           {
               OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_mage_water_elemental_freeze_SpellScript::CountTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
               AfterCast += SpellCastFn(spell_mage_water_elemental_freeze_SpellScript::HandleImprovedFreeze);
           }

       private:
           bool _didHit;
       };

       SpellScript* GetSpellScript() const
       {
           return new spell_mage_water_elemental_freeze_SpellScript();
       }
};

// cauterize
class spell_mage_cauterize : public SpellScriptLoader 
{
public:
    spell_mage_cauterize() : SpellScriptLoader("spell_mage_cauterize") { }

    class spell_mage_cauterize_AuraScript: public AuraScript 
    {
        PrepareAuraScript(spell_mage_cauterize_AuraScript);

        uint32 healPct;

        bool Validate(SpellInfo const* /*spellEntry*/) 
        {
            if (!sSpellMgr->GetSpellInfo(MAGE_SPELL_CAUTERIZE_HEAL))
                return false;
            return true;
        }

        void CalculateAmount(AuraEffect const * /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/) 
        {
            // Set absorbtion amount to unlimited
            amount = -1;
        }

        void Absorb(AuraEffect * aurEff, DamageInfo & dmgInfo, uint32 & absorbAmount)
        {
            Unit * target = GetTarget();
            if (dmgInfo.GetDamage() < target->GetHealth())
                return;

            if (target->ToPlayer() && target->ToPlayer()->HasSpellCooldown(MAGE_SPELL_CAUTERIZE_HEAL))
                return;

            bool isRank1 = true;
            if (target->HasAura(86949))
                isRank1 = false;

            if ((isRank1 && urand(0, 1) == 1) || !isRank1)
            {
                int32 healAmount = int32(target->CountPctFromMaxHealth(40.0f));

                target->CastCustomSpell(target, MAGE_SPELL_CAUTERIZE_HEAL, NULL, &healAmount, NULL, true);
                absorbAmount = dmgInfo.GetDamage();

                if (target->ToPlayer())
                    target->ToPlayer()->AddSpellCooldown(MAGE_SPELL_CAUTERIZE_HEAL, 0, time(NULL) + 60);
            }
        }

        void Register()
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_mage_cauterize_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
            OnEffectAbsorb += AuraEffectAbsorbFn(spell_mage_cauterize_AuraScript::Absorb, EFFECT_0);
        }
    };

    AuraScript *GetAuraScript() const 
    {
        return new spell_mage_cauterize_AuraScript();
    }
};

void AddSC_mage_spell_scripts()
{
    new spell_fingers_of_frost();
    new spell_mage_frostfire_bolt();
    new spell_mage_piercing_chill();
    new spell_mage_ring_of_frost();
    new spell_mage_arcane_blast();
    new spell_mage_blast_wave();
    new spell_pyromaniac();
    new spell_mage_cold_snap();
    new spell_mage_cone_of_cold();
    new spell_mage_conjure_refreshment();
    new spell_mage_frost_warding_trigger();
    new spell_mage_blizzard();
    new spell_mage_frostbolt();
    new spell_mage_living_bomb();
    new spell_mage_ice_barrier();
    new spell_mage_mana_shield();
    new spell_mage_mage_ward();
    new spell_mage_polymorph_cast_visual();
    new spell_mage_replenish_mana();
    new spell_mage_ring_of_frost_freeze();
    new spell_mage_summon_water_elemental();
    new spell_mage_water_elemental_freeze();
    new spell_mage_cauterize();
}
