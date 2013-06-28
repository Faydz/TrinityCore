#include "Player.h"

#include "ScriptMgr.h"

#include "SpellScript.h"

#include "SpellAuraEffects.h"

#include "Group.h"

enum PaladinSpells

{

    SPELL_PALADIN_DIVINE_PLEA				    = 54428,

    SPELL_PALADIN_BLESSING_OF_SANCTUARY_BUFF	 = 67480,

    SPELL_PALADIN_BLESSING_OF_SANCTUARY_ENERGIZE = 57319,

    SPELL_PALADIN_HOLY_SHOCK_R1				  = 20473,

    SPELL_PALADIN_HOLY_SHOCK_R1_DAMAGE		   = 25912,

    SPELL_PALADIN_HOLY_SHOCK_R1_HEALING		  = 25914,

    SPELL_PALADIN_BLESSING_OF_LOWER_CITY_DRUID   = 37878,

    SPELL_PALADIN_BLESSING_OF_LOWER_CITY_PALADIN = 37879,

    SPELL_PALADIN_BLESSING_OF_LOWER_CITY_PRIEST  = 37880,

    SPELL_PALADIN_BLESSING_OF_LOWER_CITY_SHAMAN  = 37881,

    SPELL_PALADIN_DIVINE_STORM				   = 53385,

    SPELL_PALADIN_DIVINE_STORM_DUMMY			 = 54171,

    SPELL_PALADIN_DIVINE_STORM_HEAL			  = 54172,

    SPELL_PALADIN_EYE_FOR_AN_EYE_RANK_1          = 9799,
    SPELL_PALADIN_EYE_FOR_AN_EYE_DAMAGE		  = 25997,

    SPELL_PALADIN_FORBEARANCE				    = 25771,

    SPELL_PALADIN_AVENGING_WRATH_MARKER		  = 61987,

    SPELL_PALADIN_IMMUNE_SHIELD_MARKER		   = 61988,

    SPELL_PALADIN_HAND_OF_SACRIFICE			  = 6940,

    SPELL_PALADIN_DIVINE_SACRIFICE			   = 64205,

    SPELL_PALADIN_DIVINE_PURPOSE_PROC		    = 90174,

    SPELL_PALADIN_GLYPH_OF_SALVATION			 = 63225,

    SPELL_PALADIN_RIGHTEOUS_DEFENSE_TAUNT	    = 31790,

    SPELL_PALADIN_SEAL_OF_RIGHTEOUSNESS		  = 25742,

   

    SPELL_PALADIN_WORD_OF_GLORY				  = 85673,

    SPELL_GENERIC_ARENA_DAMPENING			    = 74410,

    SPELL_GENERIC_BATTLEGROUND_DAMPENING		 = 74411

};



// 37877 - Blessing of Faith

class spell_pal_blessing_of_faith : public SpellScriptLoader

{

    public:

	    spell_pal_blessing_of_faith() : SpellScriptLoader("spell_pal_blessing_of_faith") { }

	    class spell_pal_blessing_of_faith_SpellScript : public SpellScript

	    {

		    PrepareSpellScript(spell_pal_blessing_of_faith_SpellScript);

		    bool Validate(SpellInfo const* /*spellInfo*/)

		    {

			    if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_BLESSING_OF_LOWER_CITY_DRUID) || !sSpellMgr->GetSpellInfo(SPELL_PALADIN_BLESSING_OF_LOWER_CITY_PALADIN) || !sSpellMgr->GetSpellInfo(SPELL_PALADIN_BLESSING_OF_LOWER_CITY_PRIEST) || !sSpellMgr->GetSpellInfo(SPELL_PALADIN_BLESSING_OF_LOWER_CITY_SHAMAN))

				    return false;

			    return true;

		    }

		    void HandleDummy(SpellEffIndex /*effIndex*/)

		    {

			    if (Unit* unitTarget = GetHitUnit())

			    {

				    uint32 spell_id = 0;

				    switch (unitTarget->getClass())

				    {

					    case CLASS_DRUID:

						    spell_id = SPELL_PALADIN_BLESSING_OF_LOWER_CITY_DRUID;

						    break;

					    case CLASS_PALADIN:

						    spell_id = SPELL_PALADIN_BLESSING_OF_LOWER_CITY_PALADIN;

						    break;

					    case CLASS_PRIEST:

						    spell_id = SPELL_PALADIN_BLESSING_OF_LOWER_CITY_PRIEST;

						    break;

					    case CLASS_SHAMAN:

						    spell_id = SPELL_PALADIN_BLESSING_OF_LOWER_CITY_SHAMAN;

						    break;

					    default:

						    return; // ignore for non-healing classes

				    }

				    Unit* caster = GetCaster();

				    caster->CastSpell(caster, spell_id, true);

			    }

		    }

		    void Register()

		    {

			    OnEffectHitTarget += SpellEffectFn(spell_pal_blessing_of_faith_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);

		    }

	    };

	    SpellScript* GetSpellScript() const

	    {

		    return new spell_pal_blessing_of_faith_SpellScript();

	    }

};

// 20911 - Blessing of Sanctuary

// 25899 - Greater Blessing of Sanctuary

class spell_pal_blessing_of_sanctuary : public SpellScriptLoader

{

    public:

	    spell_pal_blessing_of_sanctuary() : SpellScriptLoader("spell_pal_blessing_of_sanctuary") { }

	    class spell_pal_blessing_of_sanctuary_AuraScript : public AuraScript

	    {

		    PrepareAuraScript(spell_pal_blessing_of_sanctuary_AuraScript);

		    bool Validate(SpellInfo const* /*spellInfo*/)

		    {

			    if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_BLESSING_OF_SANCTUARY_BUFF))

				    return false;

			    if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_BLESSING_OF_SANCTUARY_ENERGIZE))

				    return false;

			    return true;

		    }

		    void HandleEffectApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)

		    {

			    Unit* target = GetTarget();

			    if (Unit* caster = GetCaster())

				    caster->CastSpell(target, SPELL_PALADIN_BLESSING_OF_SANCTUARY_BUFF, true);

		    }

		    void HandleEffectRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)

		    {

			    Unit* target = GetTarget();

			    target->RemoveAura(SPELL_PALADIN_BLESSING_OF_SANCTUARY_BUFF, GetCasterGUID());

		    }

		    bool CheckProc(ProcEventInfo& /*eventInfo*/)

		    {

			    return GetTarget()->getPowerType() == POWER_MANA;

		    }

		    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& /*eventInfo*/)

		    {

			    PreventDefaultAction();

			    GetTarget()->CastSpell(GetTarget(), SPELL_PALADIN_BLESSING_OF_SANCTUARY_ENERGIZE, true, NULL, aurEff);

		    }

		    void Register()

		    {

			    AfterEffectApply += AuraEffectApplyFn(spell_pal_blessing_of_sanctuary_AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);

			    AfterEffectRemove += AuraEffectRemoveFn(spell_pal_blessing_of_sanctuary_AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);

			    DoCheckProc += AuraCheckProcFn(spell_pal_blessing_of_sanctuary_AuraScript::CheckProc);

			    OnEffectProc += AuraEffectProcFn(spell_pal_blessing_of_sanctuary_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);

		    }

	    };

	    AuraScript* GetAuraScript() const

	    {

		    return new spell_pal_blessing_of_sanctuary_AuraScript();

	    }

};

// 64205 - Divine Sacrifice

class spell_pal_divine_sacrifice : public SpellScriptLoader

{

    public:

	    spell_pal_divine_sacrifice() : SpellScriptLoader("spell_pal_divine_sacrifice") { }

	    class spell_pal_divine_sacrifice_AuraScript : public AuraScript

	    {

		    PrepareAuraScript(spell_pal_divine_sacrifice_AuraScript);

		    uint32 groupSize, minHpPct;

		    int32 remainingAmount;

		    bool Load()

		    {

			    if (Unit* caster = GetCaster())

			    {

				    if (caster->GetTypeId() == TYPEID_PLAYER)

				    {

					    if (caster->ToPlayer()->GetGroup())

						    groupSize = caster->ToPlayer()->GetGroup()->GetMembersCount();

					    else

						    groupSize = 1;

				    }

				    else

					    return false;

				    remainingAmount = (caster->CountPctFromMaxHealth(GetSpellInfo()->Effects[EFFECT_2].CalcValue(caster)) * groupSize);

				    minHpPct = GetSpellInfo()->Effects[EFFECT_1].CalcValue(caster);

				    return true;

			    }

			    return false;

		    }

		    void Split(AuraEffect* /*aurEff*/, DamageInfo & /*dmgInfo*/, uint32 & splitAmount)

		    {

			    remainingAmount -= splitAmount;

			    // break when absorbed everything it could, or if the casters hp drops below 20%

			    if (Unit* caster = GetCaster())

				    if (remainingAmount <= 0 || (caster->GetHealthPct() < minHpPct))

					    caster->RemoveAura(SPELL_PALADIN_DIVINE_SACRIFICE);

		    }

		    void Register()

		    {

			    OnEffectSplit += AuraEffectSplitFn(spell_pal_divine_sacrifice_AuraScript::Split, EFFECT_0);

		    }

	    };

	    AuraScript* GetAuraScript() const

	    {

		    return new spell_pal_divine_sacrifice_AuraScript();

	    }

};

// 53385 - Divine Storm

class spell_pal_divine_storm : public SpellScriptLoader

{

    public:

	    spell_pal_divine_storm() : SpellScriptLoader("spell_pal_divine_storm") { }

	    class spell_pal_divine_storm_SpellScript : public SpellScript

	    {

		    PrepareSpellScript(spell_pal_divine_storm_SpellScript);

		    uint32 healPct;

		    bool Validate(SpellInfo const* /*spellInfo*/)

		    {

			    if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_DIVINE_STORM_DUMMY))

				    return false;

			    return true;

		    }

		    bool Load()

		    {

			    healPct = GetSpellInfo()->Effects[EFFECT_1].CalcValue(GetCaster());

			    return true;

		    }

		    void TriggerHeal()

		    {

			    Unit* caster = GetCaster();

			    caster->CastCustomSpell(SPELL_PALADIN_DIVINE_STORM_DUMMY, SPELLVALUE_BASE_POINT0, (GetHitDamage() * healPct) / 100, caster, true);

		    }

		    void Register()

		    {

			    AfterHit += SpellHitFn(spell_pal_divine_storm_SpellScript::TriggerHeal);

		    }

	    };

	    SpellScript* GetSpellScript() const

	    {

		    return new spell_pal_divine_storm_SpellScript();

	    }

};

// 54171 - Divine Storm (Dummy)

class spell_pal_divine_storm_dummy : public SpellScriptLoader

{

    public:

	    spell_pal_divine_storm_dummy() : SpellScriptLoader("spell_pal_divine_storm_dummy") { }

	    class spell_pal_divine_storm_dummy_SpellScript : public SpellScript

	    {

		    PrepareSpellScript(spell_pal_divine_storm_dummy_SpellScript);

		    bool Validate(SpellInfo const* /*spellInfo*/)

		    {

			    if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_DIVINE_STORM_HEAL))

				    return false;

			    return true;

		    }

		    void CountTargets(std::list<WorldObject*>& targetList)

		    {

			    _targetCount = targetList.size();

		    }

		    void HandleDummy(SpellEffIndex /*effIndex*/)

		    {

			    if (!_targetCount || ! GetHitUnit())

				    return;

			    int32 heal = GetEffectValue() / _targetCount;

			    GetCaster()->CastCustomSpell(GetHitUnit(), SPELL_PALADIN_DIVINE_STORM_HEAL, &heal, NULL, NULL, true);

		    }

	    private:

		    uint32 _targetCount;

		    void Register()

		    {

			    OnEffectHitTarget += SpellEffectFn(spell_pal_divine_storm_dummy_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);

			    OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pal_divine_storm_dummy_SpellScript::CountTargets, EFFECT_0, TARGET_UNIT_CASTER_AREA_RAID);

		    }

	    };

	    SpellScript* GetSpellScript() const

	    {

		    return new spell_pal_divine_storm_dummy_SpellScript();
            void HandleEffectProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
                int32 damage = CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), aurEff->GetAmount());

                OnEffectProc += AuraEffectProcFn(spell_pal_eye_for_an_eye_AuraScript::HandleEffectProc, EFFECT_0, m_scriptSpellId == SPELL_PALADIN_EYE_FOR_AN_EYE_RANK_1 ? SPELL_AURA_DUMMY : SPELL_AURA_PROC_TRIGGER_SPELL);
	    }

};

// 63521 - Guarded by The Light

class spell_pal_guarded_by_the_light : public SpellScriptLoader

{

    public:

	    spell_pal_guarded_by_the_light() : SpellScriptLoader("spell_pal_guarded_by_the_light") { }

	    class spell_pal_guarded_by_the_light_SpellScript : public SpellScript

	    {

		    PrepareSpellScript(spell_pal_guarded_by_the_light_SpellScript);

		    bool Validate(SpellInfo const* /*spellInfo*/)

		    {

			    if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_DIVINE_PLEA))

				    return false;

			    return true;

		    }

		    void HandleScriptEffect(SpellEffIndex /*effIndex*/)

		    {

			    // Divine Plea

			    if (Aura* aura = GetCaster()->GetAura(SPELL_PALADIN_DIVINE_PLEA))

				    aura->RefreshDuration();

		    }

		    void Register()

		    {

			    OnEffectHitTarget += SpellEffectFn(spell_pal_guarded_by_the_light_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);

		    }

	    };

	    SpellScript* GetSpellScript() const

	    {

		    return new spell_pal_guarded_by_the_light_SpellScript();

	    }

};

// 6940 - Hand of Sacrifice

class spell_pal_hand_of_sacrifice : public SpellScriptLoader

{

    public:

	    spell_pal_hand_of_sacrifice() : SpellScriptLoader("spell_pal_hand_of_sacrifice") { }

	    class spell_pal_hand_of_sacrifice_AuraScript : public AuraScript

	    {

		    PrepareAuraScript(spell_pal_hand_of_sacrifice_AuraScript);

		    int32 remainingAmount;

		    bool Load()

		    {

			    if (Unit* caster = GetCaster())

			    {

				    remainingAmount = caster->GetMaxHealth();

				    return true;

			    }

			    return false;

		    }

		    void Split(AuraEffect* /*aurEff*/, DamageInfo & /*dmgInfo*/, uint32 & splitAmount)

		    {

			    remainingAmount -= splitAmount;

			    if (remainingAmount <= 0)

			    {

				    GetTarget()->RemoveAura(SPELL_PALADIN_HAND_OF_SACRIFICE);

			    }

		    }

		    void Register()

		    {

			    OnEffectSplit += AuraEffectSplitFn(spell_pal_hand_of_sacrifice_AuraScript::Split, EFFECT_0);

		    }

	    };

	    AuraScript* GetAuraScript() const

	    {

		    return new spell_pal_hand_of_sacrifice_AuraScript();

	    }

};

// 1038 - Hand of Salvation

class spell_pal_hand_of_salvation : public SpellScriptLoader

{

    public:

	    spell_pal_hand_of_salvation() : SpellScriptLoader("spell_pal_hand_of_salvation") { }

	    class spell_pal_hand_of_salvation_AuraScript : public AuraScript

	    {

		    PrepareAuraScript(spell_pal_hand_of_salvation_AuraScript);

		    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)

		    {

			    if (Unit* caster = GetCaster())

			    {

				    // Glyph of Salvation

				    if (caster->GetGUID() == GetUnitOwner()->GetGUID())

					    if (AuraEffect const* aurEff = caster->GetAuraEffect(SPELL_PALADIN_GLYPH_OF_SALVATION, EFFECT_0))

						    amount -= aurEff->GetAmount();

			    }

		    }

		    void Register()

		    {

			    DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pal_hand_of_salvation_AuraScript::CalculateAmount, EFFECT_1, SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN);

		    }

	    };

	    AuraScript* GetAuraScript() const

	    {

		    return new spell_pal_hand_of_salvation_AuraScript();

	    }

};

// -20473 - Holy Shock

class spell_pal_holy_shock : public SpellScriptLoader

{

    public:

	    spell_pal_holy_shock() : SpellScriptLoader("spell_pal_holy_shock") { }

	    class spell_pal_holy_shock_SpellScript : public SpellScript

	    {

		    PrepareSpellScript(spell_pal_holy_shock_SpellScript);

		    bool Validate(SpellInfo const* spell)

		    {

			    if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_HOLY_SHOCK_R1))

				    return false;

			    // can't use other spell than holy shock due to spell_ranks dependency

			    if (sSpellMgr->GetFirstSpellInChain(SPELL_PALADIN_HOLY_SHOCK_R1) != sSpellMgr->GetFirstSpellInChain(spell->Id))

				    return false;

			    uint8 rank = sSpellMgr->GetSpellRank(spell->Id);

			    if (!sSpellMgr->GetSpellWithRank(SPELL_PALADIN_HOLY_SHOCK_R1_DAMAGE, rank, true) || !sSpellMgr->GetSpellWithRank(SPELL_PALADIN_HOLY_SHOCK_R1_HEALING, rank, true))

				    return false;

			    return true;

		    }

		    void HandleDummy(SpellEffIndex /*effIndex*/)

		    {

			    Unit* caster = GetCaster();

			    if (Unit* unitTarget = GetHitUnit())

			    {

				    uint8 rank = sSpellMgr->GetSpellRank(GetSpellInfo()->Id);

				    if (caster->IsFriendlyTo(unitTarget))

					    caster->CastSpell(unitTarget, sSpellMgr->GetSpellWithRank(SPELL_PALADIN_HOLY_SHOCK_R1_HEALING, rank), true, 0);

				    else

					    caster->CastSpell(unitTarget, sSpellMgr->GetSpellWithRank(SPELL_PALADIN_HOLY_SHOCK_R1_DAMAGE, rank), true, 0);

			    }

		    }

		    SpellCastResult CheckCast()

		    {

			    Unit* caster = GetCaster();

			    if (Unit* target = GetExplTargetUnit())

			    {

				    if (!caster->IsFriendlyTo(target))

				    {

					    if (!caster->IsValidAttackTarget(target))

						    return SPELL_FAILED_BAD_TARGETS;

					    if (!caster->isInFront(target))

						    return SPELL_FAILED_UNIT_NOT_INFRONT;

				    }

			    }

			    else

				    return SPELL_FAILED_BAD_TARGETS;

			    return SPELL_CAST_OK;

		    }

		   

		    void CalculateDamage (SpellEffIndex /*effIndex*/)

		    {

			    Unit* caster = GetCaster();

			   

			    if (Unit* target = GetExplTargetUnit())

			    {

				    if (!caster->IsFriendlyTo(target))

				    {

					    int32 damage = GetHitDamage();

					    if (!damage)

						    damage = 13 * caster->getLevel();

					   

					    damage += caster->ToPlayer()->GetBaseSpellPowerBonus() * 0.16;

					    SetHitDamage(damage);

				    }

			    }

		    }

		    void Register()

		    {

			    OnCheckCast += SpellCheckCastFn(spell_pal_holy_shock_SpellScript::CheckCast);

			    OnEffectHitTarget += SpellEffectFn(spell_pal_holy_shock_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);

			    OnEffectHitTarget += SpellEffectFn(spell_pal_holy_shock_SpellScript::CalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);

		    }

	    };

	    SpellScript* GetSpellScript() const

	    {

		    return new spell_pal_holy_shock_SpellScript();

	    }

};

// -633 - Lay on Hands

class spell_pal_lay_on_hands : public SpellScriptLoader

{

    public:

	    spell_pal_lay_on_hands() : SpellScriptLoader("spell_pal_lay_on_hands") { }

	    class spell_pal_lay_on_hands_SpellScript : public SpellScript

	    {

		    PrepareSpellScript(spell_pal_lay_on_hands_SpellScript);

		    bool Validate(SpellInfo const* /*spell*/)

		    {

			    if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_FORBEARANCE))

				    return false;

			    if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_AVENGING_WRATH_MARKER))

				    return false;

			    if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_IMMUNE_SHIELD_MARKER))

				    return false;

			    return true;

		    }

		    SpellCastResult CheckCast()

		    {

			    Unit* caster = GetCaster();

			    if (Unit* target = GetExplTargetUnit())

				    if (caster == target)

					    if (target->HasAura(SPELL_PALADIN_FORBEARANCE) || target->HasAura(SPELL_PALADIN_AVENGING_WRATH_MARKER) || target->HasAura(SPELL_PALADIN_IMMUNE_SHIELD_MARKER))

						    return SPELL_FAILED_TARGET_AURASTATE;

			    return SPELL_CAST_OK;

		    }

		    void HandleScript()

		    {

			    Unit* caster = GetCaster();

			    if (caster == GetHitUnit())

			    {

				    caster->CastSpell(caster, SPELL_PALADIN_FORBEARANCE, true);

				    caster->CastSpell(caster, SPELL_PALADIN_AVENGING_WRATH_MARKER, true);

				    caster->CastSpell(caster, SPELL_PALADIN_IMMUNE_SHIELD_MARKER, true);

			    }

		    }

		    void Register()

		    {

			    OnCheckCast += SpellCheckCastFn(spell_pal_lay_on_hands_SpellScript::CheckCast);

			    AfterHit += SpellHitFn(spell_pal_lay_on_hands_SpellScript::HandleScript);

		    }

	    };

	    SpellScript* GetSpellScript() const

	    {

		    return new spell_pal_lay_on_hands_SpellScript();

	    }

};

// 31789 - Righteous Defense

class spell_pal_righteous_defense : public SpellScriptLoader

{

    public:

	    spell_pal_righteous_defense() : SpellScriptLoader("spell_pal_righteous_defense") { }

	    class spell_pal_righteous_defense_SpellScript : public SpellScript

	    {

		    PrepareSpellScript(spell_pal_righteous_defense_SpellScript);

		    bool Validate(SpellInfo const* /*spellInfo*/)

		    {

			    if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_RIGHTEOUS_DEFENSE_TAUNT))

				    return false;

			    return true;

		    }

		    SpellCastResult CheckCast()

		    {

			    Unit* caster = GetCaster();

			    if (caster->GetTypeId() != TYPEID_PLAYER)

				    return SPELL_FAILED_DONT_REPORT;

			    if (Unit* target = GetExplTargetUnit())

			    {

				    if (!target->IsFriendlyTo(caster) || target->getAttackers().empty())

					    return SPELL_FAILED_BAD_TARGETS;

			    }

			    else

				    return SPELL_FAILED_BAD_TARGETS;

			    return SPELL_CAST_OK;

		    }

		    void HandleTriggerSpellLaunch(SpellEffIndex effIndex)

		    {

			    PreventHitDefaultEffect(effIndex);

		    }

		    void HandleTriggerSpellHit(SpellEffIndex effIndex)

		    {

			    PreventHitDefaultEffect(effIndex);

			    if (Unit* target = GetHitUnit())

				    GetCaster()->CastSpell(target, SPELL_PALADIN_RIGHTEOUS_DEFENSE_TAUNT, true);

		    }

		    void Register()

		    {

			    OnCheckCast += SpellCheckCastFn(spell_pal_righteous_defense_SpellScript::CheckCast);

			    //! WORKAROUND

			    //! target select will be executed in hitphase of effect 0

			    //! so we must handle trigger spell also in hit phase (default execution in launch phase)

			    //! see issue #3718

			    OnEffectLaunchTarget += SpellEffectFn(spell_pal_righteous_defense_SpellScript::HandleTriggerSpellLaunch, EFFECT_1, SPELL_EFFECT_TRIGGER_SPELL);

			    OnEffectHitTarget += SpellEffectFn(spell_pal_righteous_defense_SpellScript::HandleTriggerSpellHit, EFFECT_1, SPELL_EFFECT_TRIGGER_SPELL);

		    }

	    };

	    SpellScript* GetSpellScript() const

	    {

		    return new spell_pal_righteous_defense_SpellScript();

	    }

};

class spell_pal_judgements_of_the_bold : public SpellScriptLoader

{

    public:

	    spell_pal_judgements_of_the_bold() : SpellScriptLoader("spell_pal_judgements_of_the_bold") { }

	    class spell_pal_judgements_of_the_bold_AuraScript : public AuraScript

	    {

		    PrepareAuraScript(spell_pal_judgements_of_the_bold_AuraScript);

		    bool Load()

		    {

			    if (GetCaster()->GetTypeId() != TYPEID_PLAYER)

				    return false;

			    return true;

		    }

		    void CalculateMana(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)

		    {

			    if (Unit* caster = GetCaster())

			    {

				    canBeRecalculated = true;

				    int32 basemana = caster->ToPlayer()->GetCreateMana();

				    amount = (3 * basemana) / 100; // 3% of base mana

			    }

		    }

		    void Register()

		    {

			    DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pal_judgements_of_the_bold_AuraScript::CalculateMana, EFFECT_0, SPELL_AURA_PERIODIC_ENERGIZE);

		    }

	    };

	    AuraScript* GetAuraScript() const

	    {

		    return new spell_pal_judgements_of_the_bold_AuraScript();

	    }

};

// Shield of Righteous

// Spell Id: 53600

class spell_pal_shield_of_righteous : public SpellScriptLoader

{

public:

    spell_pal_shield_of_righteous() : SpellScriptLoader("spell_pal_shield_of_righteous") { }

    class spell_pal_shield_of_righteous_SpellScript : public SpellScript

    {

	    PrepareSpellScript(spell_pal_shield_of_righteous_SpellScript)

	    bool Load()

	    {

		    if (GetCaster()->GetTypeId() != TYPEID_PLAYER)

			    return false;

		    return true;

	    }

	    void CalculateDamage(SpellEffIndex /*effIndex*/)

	    {

		    if (Unit* caster = GetCaster())

		    {

			    int32 damage = GetHitDamage();

			    int32 power = caster->GetPower(POWER_HOLY_POWER);

			    switch (power)

			    {

				    case 0:

					    damage = int32(damage * - 1.0f);

					    break;

				    case 1:

					    damage = int32((damage * 3.0f) - 3);

					    break;

				    case 2:

					    damage = int32((damage * 6.0f) - 6);

					    break;

			    }

			    SetHitDamage(damage);

			    caster->SetPower(POWER_HOLY_POWER, int32(-power));

		    }

	    }

	    void Register()

	    {

		    OnEffectHitTarget += SpellEffectFn(spell_pal_shield_of_righteous_SpellScript::CalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);

	    }

    };

    SpellScript* GetSpellScript() const

    {

	    return new spell_pal_shield_of_righteous_SpellScript();

    }

};

class spell_pal_word_of_glory : public SpellScriptLoader

{

public:

    spell_pal_word_of_glory() : SpellScriptLoader("spell_pal_word_of_glory") { }

    class spell_pal_word_of_glory_heal_SpellScript : public SpellScript

    {

	    PrepareSpellScript(spell_pal_word_of_glory_heal_SpellScript)

		   

		    int32 totalheal;

	   

	    bool Validate (SpellInfo const* /*spellEntry*/)

	    {

		    if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_WORD_OF_GLORY))

			    return false;

		    return true;

	    }

	   

	    bool Load()

	    {

		    if (GetCaster()->GetTypeId() != TYPEID_PLAYER)

			    return false;

		   

		    if (GetCaster()->ToPlayer()->getClass() != CLASS_PALADIN)

			    return false;

		   

		    return true;

	    }

	    void ChangeHeal(SpellEffIndex /*effIndex*/)

	    {

		    totalheal = GetHitHeal();

		    Unit* caster = GetCaster();

		    Unit* target = GetHitUnit();

		   

		    if (!target)

			    return;

    if (GetCaster()->HasAura(SPELL_PALADIN_DIVINE_PURPOSE_PROC))

    {

	    totalheal *= 3;

	   

	    // Selfless Healer

	    if (AuraEffect const* auraEff = caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_PALADIN, 3924, EFFECT_0))

		    if (target != caster)

			    totalheal += (totalheal * auraEff->GetAmount()) / 100;

	   

	    SetHitHeal(totalheal);

	    const_cast<SpellValue*>(GetSpellValue())->EffectBasePoints[1] = totalheal;

	    return;

    }

    switch (caster->GetPower(POWER_HOLY_POWER))

    {

    case 0: // 1 Holy Power

	    {

		    totalheal = totalheal;

		    break;

	    }

    case 1: // 2 Holy Power

	    {

		    totalheal *= 2;

		    break;

	    }

    case 2: // 3 Holy Power

	    {

		    totalheal *= 3;

		    break;

	    }

    }

    // Selfless Healer

    if (AuraEffect const* auraEff = caster->GetDummyAuraEffect(SPELLFAMILY_PALADIN, 3924, EFFECT_0))

	    if (target != caster)

		    totalheal += (totalheal * auraEff->GetAmount()) / 100;

    SetHitHeal(totalheal);

    const_cast<SpellValue*>(GetSpellValue())->EffectBasePoints[1] = totalheal;

	    }

	   

	    void PreventEffect(SpellEffIndex effIndex)

	    {

		    // Glyph of Long Word

		    if (!GetCaster()->HasAura(93466))

			    PreventHitDefaultEffect(effIndex);

	    }

    void HandlePeriodic()

    {

	    // Glyph of Long Word

	    if (!GetCaster()->HasAura(93466))

		    PreventHitAura();

    }

    void Register()

    {

	    OnEffectHitTarget += SpellEffectFn(spell_pal_word_of_glory_heal_SpellScript::ChangeHeal, EFFECT_0, SPELL_EFFECT_HEAL);

	    OnEffectHitTarget += SpellEffectFn(spell_pal_word_of_glory_heal_SpellScript::PreventEffect, EFFECT_1, SPELL_EFFECT_APPLY_AURA);

	    AfterHit += SpellHitFn(spell_pal_word_of_glory_heal_SpellScript::HandlePeriodic);

    }

    };

   

    class spell_pal_word_of_glory_heal_AuraScript : public AuraScript

    {

	    PrepareAuraScript(spell_pal_word_of_glory_heal_AuraScript)

		   

		    bool Validate (SpellInfo const* /*spellEntry*/)

	    {

		    if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_WORD_OF_GLORY)->Effects[1].Effect)

			    return false;

		    return true;

	    }

	    bool Load()

	    {

		    if (GetCaster()->GetTypeId() != TYPEID_PLAYER)

			    return false;

		   

		    if (GetCaster()->ToPlayer()->getClass() != CLASS_PALADIN)

			    return false;

		    return true;

	    }

	   

	    void CalculateOvertime(AuraEffect const* aurEff, int32& amount, bool& canBeRecalculated)

	    {

		    // Had to do ALLLLLL the scaling manually because (afaik) there is no way to hook the GetHitHeal from the spell's effIndex 0

		    Unit* caster = GetCaster();

		    int32 bonus = (caster->ToPlayer()->GetTotalAttackPowerValue(BASE_ATTACK) * 0.198) + (caster->ToPlayer()->GetBaseSpellPowerBonus() * 0.209);

		    int32 divinebonus = (caster->ToPlayer()->GetTotalAttackPowerValue(BASE_ATTACK) * 0.594) + (caster->ToPlayer()->GetBaseSpellPowerBonus() * 0.627);

		    int32 multiplier;

		   

		    if (AuraEffect const* longWord = GetCaster()->GetDummyAuraEffect(SPELLFAMILY_PALADIN, 4127, 1))

		    {

			    canBeRecalculated = true;

			    switch (caster->GetPower(POWER_HOLY_POWER))

			    {

			    case 0:

				    {

					    bonus = bonus;

					    multiplier = 1;

					    break;

				    }

			    case 1:

				    {

					    bonus = (caster->ToPlayer()->GetTotalAttackPowerValue(BASE_ATTACK) * 0.396) + (caster->ToPlayer()->GetBaseSpellPowerBonus() * 0.418);

					    multiplier = 2;

					    break;

				    }

			    case 2:

				    {

					    bonus = (caster->ToPlayer()->GetTotalAttackPowerValue(BASE_ATTACK) * 0.594) + (caster->ToPlayer()->GetBaseSpellPowerBonus() * 0.627);

					    multiplier = 3;

					    break;

				    }

			    }

			    if (caster->HasAura(SPELL_PALADIN_DIVINE_PURPOSE_PROC))

			    {

				    amount = ((((GetSpellInfo()->Effects[0].CalcValue(caster) * 3)  + divinebonus) * longWord->GetAmount()) / 100)  / 3;

			    }

			    else

				    amount = ((((GetSpellInfo()->Effects[0].CalcValue(caster) * multiplier)  + bonus) * longWord->GetAmount()) / 100)  / 3;

		    }

	    }

	   

	    void Register()

	    {

		    DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pal_word_of_glory_heal_AuraScript::CalculateOvertime, EFFECT_1, SPELL_AURA_PERIODIC_HEAL);

	    }

    };

   

    AuraScript* GetAuraScript() const

    {

	    return new spell_pal_word_of_glory_heal_AuraScript();

    }

    SpellScript* GetSpellScript() const

    {

	    return new spell_pal_word_of_glory_heal_SpellScript();

    }

};

// 85285 - Sacred Shield

class spell_pal_sacred_shield : public SpellScriptLoader

{

    public:

	    spell_pal_sacred_shield() : SpellScriptLoader("spell_pal_sacred_shield") { }

	    class spell_pal_sacred_shield_SpellScript : public SpellScript

	    {

		    PrepareSpellScript(spell_pal_sacred_shield_SpellScript);

		    SpellCastResult CheckCast()

		    {

			    Unit* caster = GetCaster();

			    if (caster->GetTypeId() != TYPEID_PLAYER)

				    return SPELL_FAILED_DONT_REPORT;

			    if (!caster->HealthBelowPct(30))

				    return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;

			    return SPELL_CAST_OK;

		    }

		    void Register()

		    {

			    OnCheckCast += SpellCheckCastFn(spell_pal_sacred_shield_SpellScript::CheckCast);

		    }

	    };

	    SpellScript* GetSpellScript() const

	    {

		    return new spell_pal_sacred_shield_SpellScript();

	    }

};

// Templar's Verdict

// Spell Id: 85256

class spell_pal_templar_verdict : public SpellScriptLoader

{

public:

    spell_pal_templar_verdict() : SpellScriptLoader("spell_pal_templar_verdict") { }

   

    class spell_pal_templar_verdict_SpellScript : public SpellScript

    {

	    PrepareSpellScript(spell_pal_templar_verdict_SpellScript)

		   

		    bool Validate (SpellInfo const* /*spellEntry*/)

		    {

			    if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_DIVINE_PURPOSE_PROC))

				    return false;

			    return true;

		    }

		    bool Load()

		    {

			    if (GetCaster()->GetTypeId() != TYPEID_PLAYER)

				    return false;

			    if (GetCaster()->ToPlayer()->getClass() != CLASS_PALADIN)

				    return false;

			    return true;

		    }

		    void ChangeDamage(SpellEffIndex /*effIndex*/)

		    {

			    Unit* caster = GetCaster();

			    int32 damage = GetHitDamage();

			    if (caster->HasAura(SPELL_PALADIN_DIVINE_PURPOSE_PROC))

				    damage *= 7.5;  // 7.5*30% = 225%

			    else

			    {

				    switch (caster->GetPower(POWER_HOLY_POWER))

				    {

					    case 0: // 1 Holy Power

						    damage = damage;

						    break;

					    case 1: // 2 Holy Power

						    damage *= 3;    // 3*30 = 90%

						    break;

					    case 2: // 3 Holy Power

						    damage *= 7.5;  // 7.5*30% = 225%

						    break;

				    }

			    }

			    SetHitDamage(damage);

		    }

		    void Register()

		    {

			    OnEffectHitTarget += SpellEffectFn(spell_pal_templar_verdict_SpellScript::ChangeDamage, EFFECT_0, SPELL_EFFECT_WEAPON_PERCENT_DAMAGE);

		    }

	    };

	    SpellScript* GetSpellScript() const

	    {

		    return new spell_pal_templar_verdict_SpellScript();

	    }

};

class spell_pal_exorcism_and_holy_wrath_damage : public SpellScriptLoader

{

    public:

	    spell_pal_exorcism_and_holy_wrath_damage() : SpellScriptLoader("spell_pal_exorcism_and_holy_wrath_damage") { }

	    class spell_pal_exorcism_and_holy_wrath_damage_AuraScript : public AuraScript

	    {

		    PrepareAuraScript(spell_pal_exorcism_and_holy_wrath_damage_AuraScript);

		    void HandleEffectCalcSpellMod(AuraEffect const* aurEff, SpellModifier*& spellMod)

		    {

			    if (!spellMod)

			    {

				    spellMod = new SpellModifier(aurEff->GetBase());

				    spellMod->op = SPELLMOD_DAMAGE;

				    spellMod->type = SPELLMOD_FLAT;

				    spellMod->spellId = GetId();

				    spellMod->mask[1] = 0x200002;

			    }

			    spellMod->value = aurEff->GetAmount();

		    }

		    void Register()

		    {

			    DoEffectCalcSpellMod += AuraEffectCalcSpellModFn(spell_pal_exorcism_and_holy_wrath_damage_AuraScript::HandleEffectCalcSpellMod, EFFECT_0, SPELL_AURA_DUMMY);

		    }

	    };

	    AuraScript* GetAuraScript() const

	    {

		    return new spell_pal_exorcism_and_holy_wrath_damage_AuraScript();

	    }

};

// Selfes healer

class spell_pal_selfless_healer : public SpellScriptLoader

{

public:

    spell_pal_selfless_healer() : SpellScriptLoader("spell_pal_selfless_healer") { }

    class spell_pal_selfless_healer_SpellScript : public SpellScript

    {

	    PrepareSpellScript(spell_pal_selfless_healer_SpellScript)

  uint8 holyStack;

	    bool Load()

	    {

		    if (GetCaster()->GetTypeId() != TYPEID_PLAYER)

			    return false;

   holyStack = 0;

		    return GetCaster()->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_PALADIN, 3924, 0);

	    }

	    void HandleBeforeCast()

	    {

   if (Unit* caster = GetCaster())

    holyStack = caster->GetPower(POWER_HOLY_POWER);

	    }

	    void HandleAfterHit()

	    {

		    if (Unit* caster = GetCaster())

		    {

    int32 baseAmount = 0;

    int32 amount = 0;

    if (AuraEffect const* pAurEff = caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_PALADIN, 3924, 1))

	 baseAmount = pAurEff->GetAmount();

			    if (caster->HasAura(SPELL_PALADIN_DIVINE_PURPOSE_PROC))

				    amount = baseAmount * 3;

    else

	 amount = baseAmount * holyStack;

    if (amount != 0)

	 caster->CastCustomSpell(caster, 90811, &amount, NULL, NULL, true);

		    }

	    }

	    void Register()

	    {

   BeforeCast += SpellCastFn(spell_pal_selfless_healer_SpellScript::HandleBeforeCast);

   AfterHit += SpellHitFn(spell_pal_selfless_healer_SpellScript::HandleAfterHit);

	    }

    };

    SpellScript* GetSpellScript() const

    {

	    return new spell_pal_selfless_healer_SpellScript();

    }

};

// Divine purpose proc

class spell_pal_divine_purpose : public SpellScriptLoader

{

public:

    spell_pal_divine_purpose() : SpellScriptLoader("spell_pal_divine_purpose") { }

    class spell_pal_divine_purpose_SpellScript : public SpellScript

    {

	    PrepareSpellScript(spell_pal_divine_purpose_SpellScript)

  uint8 holyStack;

	    bool Load()

	    {

		    if (GetCaster()->GetTypeId() != TYPEID_PLAYER)

			    return false;

		    return GetCaster()->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_PALADIN, 2170, 0);

	    }

	    void HandleAfterHit()

	    {

		    if (Unit* caster = GetCaster())

    if (AuraEffect const* pAurEff = caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_PALADIN, 2170, 0))

	 if (roll_chance_i(pAurEff->GetAmount()))

	  caster->CastSpell(caster, 90174, true);

	    }

	    void Register()

	    {

   AfterHit += SpellHitFn(spell_pal_divine_purpose_SpellScript::HandleAfterHit);

	    }

    };

    SpellScript* GetSpellScript() const

    {

	    return new spell_pal_divine_purpose_SpellScript();

    }

};

void AddSC_paladin_spell_scripts()

{

    new spell_pal_blessing_of_faith();

    new spell_pal_blessing_of_sanctuary();

    new spell_pal_divine_sacrifice();

    new spell_pal_divine_storm();

    new spell_pal_divine_storm_dummy();

    new spell_pal_guarded_by_the_light();

    new spell_pal_hand_of_sacrifice();

    new spell_pal_hand_of_salvation();

    new spell_pal_holy_shock();

    new spell_pal_lay_on_hands();

    new spell_pal_judgements_of_the_bold();

    new spell_pal_shield_of_righteous();

    new spell_pal_word_of_glory();

    new spell_pal_templar_verdict();

    new spell_pal_exorcism_and_holy_wrath_damage();

new spell_pal_selfless_healer();

new spell_pal_divine_purpose();

    new spell_pal_sacred_shield();

}