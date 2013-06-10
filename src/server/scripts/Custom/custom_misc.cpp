#include "ScriptPCH.h"


void OnLevelChanged(Player * player, uint8 level)
{
	if (level == 20)
	{
		if (player->GetRace() == RACE_WORGEN)
		{
			player->learnSpell(68996);
		}

		player->learnSpell(33388);
		player->SendSysMessage("Dies ist eine Kontrollnachricht");
	}

	if (level == 40)
	{
		player->learnSpell(33391);
		player->SendSysMessage("Dies ist eine Kontrollnachricht");
	}

	if (level == 60)
	{
		player->learnSpell(34092);
		player->SendSysMessage("Dies ist eine Kontrollnachricht");
	}

	if (level == 70)
	{
		player->learnSpell(90267);
		player->learnSpell(34093);
		player->SendSysMessage("Dies ist eine Kontrollnachricht");
	}

	if (level == 75)
	{
		player->learnSpell(54197);
		player->SendSysMessage("Dies ist eine Kontrollnachricht");
	}

	if (level == 85)
	{
		player->learnSpell(90266);
		player->SendSysMessage("Dies ist eine Kontrollnachricht");
	}
};


void AddSC_custom_misc()
{
}