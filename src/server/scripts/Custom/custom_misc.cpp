#include "ScriptPCH.h"


void OnLevelChanged(Player * player, uint8 level)
{
	if (level == 20)
	{
		player->learnSpell(33388, true);
	}

	if (level == 40)
	{
		player->learnSpell(33391, true);
	}

	if (level == 60)
	{
		player->learnSpell(34092, true);
	}

	if (level == 70)
	{
		player->learnSpell(90267, true);
		player->learnSpell(34093, true);
	}

	if (level == 75)
	{
		player->learnSpell(54197, true);
	}

	if (level == 85)
	{
		player->learnSpell(90266, true);
	}
};


void AddSC_custom_misc()
{
}