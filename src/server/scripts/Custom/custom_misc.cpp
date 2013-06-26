#include "ScriptPCH.h"

class LearnSpellsOnLevelUp : public PlayerScript
{
        public:
                

LearnSpellsOnLevelUp() : PlayerScript("LearnSpellsOnLevelUp")
{}
	void OnLevelChanged(Player * player, uint8 level)
	{
		uint8 leveld = player->getLevel();
		if (leveld >= 20)
		{
			if (player->getRace() == RACE_WORGEN)
			{
				player->learnSpell(68996, false);
			}

			player->learnSpell(33388, false);
		}

		if (leveld >= 40)
		{
			player->learnSpell(33391, false);
		}

		if (leveld >= 60)
		{
			player->learnSpell(34092, false);
		}

		if (leveld >= 70)
		{
			player->learnSpell(90267, false);
			player->learnSpell(34093, false);
		}

		if (leveld >= 75)
		{
			player->learnSpell(54197, false);
		}

		if (leveld >= 85)
		{
			player->learnSpell(90266, false);
		}
	};
};


void AddSC_LearnSpellsOnLevelUp()
{
	new LearnSpellsOnLevelUp();
}