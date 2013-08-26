
    #include "ScriptMgr.h"
    #include "ScriptedCreature.h"
    #include "ScriptedGossip.h"
    #include "Player.h"
     
     
    enum Yells
    {
		SAY_AGGRO = 0
    };
     
    enum Spells
    {
		Spell_Pick_Weapon = 75000,
		Spell_Personal_Phalanx = 74908,   //if weapon is shield
		Spell_Flaming_Shield = 90819,     //if weapon is shield and heroic
		Spell_Encumbered = 75007,         //if weapon is mace
		Spell_Dual_Blades = 74981,        //if weapon is sword
		Spell_Mighty_Stomp = 74984,
		Spell_Burning_Flames = 90764,     //if weapon is sword and heroic
		Spell_Disorienting_Roar = 74976,  //if weapon is sword
		Spell_Impaling_Slam = 75056,       //if weapon is mace
		Spell_Lava_Patch = 90754          //if weapon is Mace and heroic
    };

	enum Equips
	{
    EQUIP_SWORD = 37871,
    EQUIP_SHIELD = 35642,
    EQUIP_MACE = 43623
	};

	enum Weapons
	{
    WEAPON_SHIELD = 0,
    WEAPON_MACE = 1,
    WEAPON_SWORD = 2,
	WEAPON_NO_WEAPON = 3
	};

     
    class boss_Forgemaster_Throngus : public CreatureScript
    {
            public:
                    boss_Forgemaster_Throngus() : CreatureScript("boss_Forgemaster_Throngus") {}
     

                    struct boss_Forgemaster_ThrongusAI : public ScriptedAI
                    {
						 boss_Forgemaster_ThrongusAI(Creature* creature) : ScriptedAI(creature) {}

						 uint32 Pick_Weapon_Timer;
						 uint32 Mighty_Stomp_Timer;
						 uint32 Disorienting_Roar_Timer;
						 uint32 Impaling_Slam_Timer;
						 uint32 Burning_Flames_Timer;
						 uint32 Lava_Patch_Timer;

						 int weaponpick;


                            void Reset() OVERRIDE
                            {

								Pick_Weapon_Timer = 25000;
								Mighty_Stomp_Timer = 20000;
								Disorienting_Roar_Timer = 16000;
								Impaling_Slam_Timer = 16000;
								Burning_Flames_Timer = 6000;
								Lava_Patch_Timer = 3000;
								weaponpick = WEAPON_NO_WEAPON;
								me->RestoreFaction();
								me->RemoveAllAuras();
								SetEquipmentSlots(false, false, false, EQUIP_NO_CHANGE);
                            }
     
                            void EnterCombat(Unit* who) OVERRIDE
                            {
								 Talk(SAY_AGGRO);
                            }


							
							void ChangeWeaponAndAura(int weaponpick)
							{
								 switch(weaponpick)
									 {
									 case WEAPON_SHIELD:
										 DoCast(me, Spell_Personal_Phalanx);
										 if(IsHeroic())
											 DoCast(me, Spell_Flaming_Shield);

										 SetEquipmentSlots(false, false, EQUIP_SHIELD, EQUIP_NO_CHANGE);
										 break;
									 case WEAPON_MACE:
										 DoCast(me, Spell_Encumbered);
										 SetEquipmentSlots(false, EQUIP_MACE, false, EQUIP_NO_CHANGE);
										 break;
									 case WEAPON_SWORD:
										 DoCast(me, Spell_Dual_Blades);
										 SetEquipmentSlots(false, EQUIP_SWORD, EQUIP_SWORD, EQUIP_NO_CHANGE);
									 }
							}

     
                            void UpdateAI(uint32 uiDiff) OVERRIDE
                            {
								 if (!UpdateVictim())
									 return;

								 //Pick Weapon with all Changes
								 if(Pick_Weapon_Timer <= uiDiff)
								 {
									 me->RemoveAllAuras();
									 DoCast(me, Spell_Pick_Weapon);
									 Pick_Weapon_Timer = 45000;
									 weaponpick = rand() % 3;
									 ChangeWeaponAndAura(weaponpick);
								 }
								 else
									 Pick_Weapon_Timer -= uiDiff;

								 //Impaling_Slam

								 if(weaponpick == WEAPON_MACE)
								 {

									if(Impaling_Slam_Timer <= uiDiff)
										 {
											Unit* target = NULL;
											target = SelectTarget(SELECT_TARGET_RANDOM, 0);
											 if (target)
												 DoCast(target, Spell_Impaling_Slam);
											  Impaling_Slam_Timer = 16000;
										 }
									 else
										 Impaling_Slam_Timer -= uiDiff;

									//Lava_Patch
									if(IsHeroic())
									{
										if(Lava_Patch_Timer <=uiDiff)
										{
											DoCast(me, Spell_Lava_Patch);
											Lava_Patch_Timer = 3000;
										}
										else
											Lava_Patch_Timer -=uiDiff;

								 }

								 //Disorienting_Roar

								 if(weaponpick == WEAPON_SWORD)
								 {
									if(Disorienting_Roar_Timer <=uiDiff)
										{
											DoCast(me->GetVictim(), Spell_Disorienting_Roar);
											Disorienting_Roar_Timer = 16000;
										}
									 else
										 Disorienting_Roar_Timer -= uiDiff;
								 

								 //Burning_Flames
									 if(IsHeroic())
									 {
										 if(Burning_Flames_Timer<=uiDiff)
										 {
											 DoCast(me->GetVictim(),Spell_Burning_Flames);
											 Burning_Flames_Timer = 6000;
										 }
										 else
											 Burning_Flames_Timer -= uiDiff;
									 }
								 }


								 //Mighty_Stomp

								 if(Mighty_Stomp_Timer <= uiDiff)
									{
										Unit* target = NULL;
										target = SelectTarget(SELECT_TARGET_RANDOM, 0);
										 if (target)
											 DoCast(target, Spell_Mighty_Stomp);
										  Mighty_Stomp_Timer = 21000;
									  }
								 else
									 Mighty_Stomp_Timer -= uiDiff;


								DoMeleeAttackIfReady();
                            }
					};
		ScriptedAI* GetAI (Creature* creature) const
    {
        return new boss_Forgemaster_ThrongusAI(creature);
    }
         };
     
    void AddSC_boss_Forgemaster_Throngus()
    {
            new boss_Forgemaster_Throngus();
    }

