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
};

enum Spells
{
    SPELL_SOUND_BAR_APPLY                         = 89683,
    SPELL_SOUND_BAR                               = 88824,
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
                    default:
                        break;
                }
            }		

            DoMeleeAttackIfReady();
        }

        void JustSummoned(Creature* summon)
        {
            summons.Summon(summon);
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

void AddSC_boss_atramedes()
{
    new boss_atramedes();
}