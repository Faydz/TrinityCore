#include "ScriptPCH.h"

class LearnSpellsOnLevelUp : public PlayerScript
{
        public:
                std::vector<uint32> ignoreSpells;

void OnLevelChanged(Player * player, uint8 level)
{
	uint8 leveld = player->getLevel();
	if (leveld >= 20)
	{
		if (player->getRace() == RACE_WORGEN)
		{
			player->learnSpell(spellInfo->68996, false);
		}

		player->learnSpell(spellInfo->33388, false);
		player->SetMoney(80000);
	}

	if (leveld >= 40)
	{
		player->learnSpell(spellInfo->33391, false);
		player->SetMoney(80000);
	}

	if (leveld >= 60)
	{
		player->learnSpell(spellInfo->34092, false);
		player->SetMoney(80000);
	}

	if (leveld >= 70)
	{
		player->learnSpell(spellInfo->90267, false);
		player->learnSpell(spellInfo->34093, false);
		player->SetMoney(80000);
	}

	if (leveld >= 75)
	{
		player->learnSpell(spellInfo->54197, false);
		player->SetMoney(80000);
	}

	if (leveld >= 85)
	{
		player->learnSpell(spellInfo->90266, false);
		player->SetMoney(80000);
	}
}
};


void AddSC_custom_misc()
{
}