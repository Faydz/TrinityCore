/*
Note: C'è un probabile bug nel core che non considera un campo nel DB dell'npc 34206. 
E' possibile però fixarlo in game con il seguente comando:
.go creature id 34206
targhettare la creatura e lanciare il comando .mod fac 14 0
*/

-- Quest 13870 As Good as it Gets
DELETE FROM `creature` WHERE (`id`='33889');
INSERT INTO `creature` VALUES (null, 33889, 1, 1, 1, 0, 0, 2606.52, -3057.43, 155.953, 1.2293, 300, 0, 0, 84, 0, 0, 0, 0, 0);

-- Quest 13808 Mission Improbable CHAIN TIMELINE FIX 
UPDATE `quest_template` SET `NextQuestIdChain`='13815' WHERE (`Id`='13808');
UPDATE `quest_template` SET `PrevQuestId`='13808' WHERE (`Id`='13815');

-- Quest 13871 Security!
UPDATE `creature_template` SET `faction_H`='14' WHERE (`entry`='34206');
DELETE FROM `creature` WHERE (`id`='34206');
INSERT INTO `creature` VALUES (null, 34206, 1, 1, 1, 0, 0, 2446.45, -3469.26, 92.4322, 1.45438, 300, 0, 0, 84, 0, 0, 0, 0, 0);
-- this creature need ingame command .mod fac 14 0 because it doesn't keep bd value
DELETE FROM `creature_loot_template` WHERE (`entry`='34206') AND (`item`='46147');
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES ('34206', '46147', '-100');
UPDATE `creature_template` SET `lootid`='34206' WHERE (`entry`='34206');

-- Quest 13873 Gurtar's Request CHAIN TIMELINE FIX 
UPDATE `quest_template` SET `NextQuestIdChain`='13875' WHERE (`Id`='13873');
UPDATE `quest_template` SET `PrevQuestId`='13873' WHERE (`Id`='13875');

-- Quest 13806 Demon Duty
DELETE FROM `gameobject` WHERE (`id`='194612');
INSERT INTO `gameobject` VALUES (null, 194612, 1, 1, 1, 2953.34, -2817.78, 212.795, 0, 0, 0, 0, 1, 120, 255, 1);
INSERT INTO `gameobject` VALUES (null, 194612, 1, 1, 1, 2951.16, -2774.57, 219.154, 0, 0, 0, 0, 1, 120, 255, 1);
INSERT INTO `gameobject` VALUES (null, 194612, 1, 1, 1, 2948.49, -2831.21, 212.906, 0, 0, 0, 0, 1, 120, 255, 1);
INSERT INTO `gameobject` VALUES (null, 194612, 1, 1, 1, 2938.04, -2809.53, 212.669, 0, 0, 0, 0, 1, 120, 255, 1);
INSERT INTO `gameobject` VALUES (null, 194612, 1, 1, 1, 2929.13, -2842.04, 212.967, 0, 0, 0, 0, 1, 120, 255, 1);
INSERT INTO `gameobject` VALUES (null, 194612, 1, 1, 1, 2907.86, -2777.84, 213.223, 0, 0, 0, 0, 1, 120, 255, 1);
INSERT INTO `gameobject` VALUES (null, 194612, 1, 1, 1, 2896.58, -2828.26, 208.834, 0, 0, 0, 0, 1, 120, 255, 1);
INSERT INTO `gameobject` VALUES (null, 194612, 1, 1, 1, 2885.28, -2856.9, 204.177, 0, 0, 0, 0, 1, 120, 255, 1);
INSERT INTO `gameobject` VALUES (null, 194612, 1, 1, 1, 2861.07, -2888.69, 204.273, 0, 0, 0, 0, 1, 120, 255, 1);
INSERT INTO `gameobject` VALUES (null, 194612, 1, 1, 1, 2852.89, -2826.94, 200.111, 0, 0, 0, 0, 1, 120, 255, 1);
INSERT INTO `gameobject` VALUES (null, 194612, 1, 1, 1, 2815.15, -2984.61, 155.642, 0, 0, 0, 0, 1, 120, 255, 1);
INSERT INTO `gameobject` VALUES (null, 194612, 1, 1, 1, 2804.77, -3006.12, 156.995, 0, 0, 0, 0, 1, 120, 255, 1);
INSERT INTO `gameobject` VALUES (null, 194612, 1, 1, 1, 2791.69, -2948.87, 149.076, 0, 0, 0, 0, 1, 120, 255, 1);
INSERT INTO `gameobject` VALUES (null, 194612, 1, 1, 1, 2777.44, -3012.11, 153.98, 0, 0, 0, 0, 1, 120, 255, 1);
INSERT INTO `gameobject` VALUES (null, 194612, 1, 1, 1, 2771.17, -2970.23, 145.347, 0, 0, 0, 0, 1, 120, 255, 1);
INSERT INTO `gameobject` VALUES (null, 194612, 1, 1, 1, 2760.97, -2916.88, 146.449, 0, 0, 0, 0, 1, 120, 255, 1);
INSERT INTO `gameobject` VALUES (null, 194612, 1, 1, 1, 2760.45, -2948.71, 143.206, 0, 0, 0, 0, 1, 120, 255, 1);
INSERT INTO `gameobject` VALUES (null, 194612, 1, 1, 1, 2747.64, -2883.31, 157.915, 0, 0, 0, 0, 1, 120, 255, 1);
INSERT INTO `gameobject` VALUES (null, 194612, 1, 1, 1, 2743.47, -3039.16, 151.811, 0, 0, 0, 0, 1, 120, 255, 1);
INSERT INTO `gameobject` VALUES (null, 194612, 1, 1, 1, 2740.32, -3077.79, 157.417, 0, 0, 0, 0, 1, 120, 255, 1);
INSERT INTO `gameobject` VALUES (null, 194612, 1, 1, 1, 2730.52, -2979.99, 141.05, 0, 0, 0, 0, 1, 120, 255, 1);
INSERT INTO `gameobject` VALUES (null, 194612, 1, 1, 1, 2718.24, -2922.1, 140.942, 0, 0, 0, 0, 1, 120, 255, 1);
INSERT INTO `gameobject` VALUES (null, 194612, 1, 1, 1, 2702.32, -2963.67, 140.267, 0, 0, 0, 0, 1, 120, 255, 1);

-- Quest 13803 Blood of the Weak
DELETE FROM `creature` WHERE (`id`='33837');
INSERT INTO `creature` VALUES (null, 33837, 1, 1, 1, 0, 0, 2284.66, -2540.83, 98.329, 3.30019, 300, 0, 0, 46, 0, 0, 0, 0, 0);

-- Quest 13628 Got Wood? CHAIN TIMELINE FIX 
UPDATE `quest_template` SET `NextQuestIdChain`='13640' WHERE (`Id`='13628');
UPDATE `quest_template` SET `NextQuestIdChain`='13651' WHERE (`Id`='13640');
UPDATE `quest_template` SET `NextQuestIdChain`='13653' WHERE (`Id`='13651');
UPDATE `quest_template` SET `NextQuestIdChain`='13712' WHERE (`Id`='13653');
UPDATE `quest_template` SET `NextQuestIdChain`='13803' WHERE (`Id`='13712');
UPDATE `quest_template` SET `NextQuestIdChain`='13805' WHERE (`Id`='13803');
UPDATE `quest_template` SET `PrevQuestId`='13628' WHERE (`Id`='13640');
UPDATE `quest_template` SET `PrevQuestId`='13640' WHERE (`Id`='13651');
UPDATE `quest_template` SET `PrevQuestId`='13651' WHERE (`Id`='13653');
UPDATE `quest_template` SET `PrevQuestId`='13653' WHERE (`Id`='13712');
UPDATE `quest_template` SET `PrevQuestId`='13712' WHERE (`Id`='13803');
UPDATE `quest_template` SET `PrevQuestId`='13803' WHERE (`Id`='13805');

-- Quest 26447 Diabolical Plans CHAIN TIMELINE FIX 
UPDATE `quest_template` SET `NextQuestIdChain`='26449' WHERE (`Id`='26447');
UPDATE `quest_template` SET `PrevQuestId`='26447' WHERE (`Id`='26449');

-- Quest 26449 Never Again!
DELETE FROM `creature_loot_template` WHERE (`entry`='17300') AND (`item`='45477');
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES ('17300', '45477', '-93');
DELETE FROM `creature_loot_template` WHERE (`entry`='6072') AND (`item`='45476');
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES ('6072', '45476', '-99');

-- Quest 13730 Playing With Felfire CHAIN TIMELINE FIX 
UPDATE `quest_template` SET `NextQuestIdChain`='13751' WHERE (`Id`='13730');
UPDATE `quest_template` SET `NextQuestIdChain`='13797' WHERE (`Id`='13751');
UPDATE `quest_template` SET `NextQuestIdChain`='13798' WHERE (`Id`='13797');
UPDATE `quest_template` SET `PrevQuestId`='13730' WHERE (`Id`='13751');
UPDATE `quest_template` SET `PrevQuestId`='13751' WHERE (`Id`='13797');
UPDATE `quest_template` SET `PrevQuestId`='13797' WHERE (`Id`='13798');

-- Quest 25 Simmer Down Now
UPDATE `quest_template` SET `SpecialFlags`='0' WHERE (`Id`='25');

-- Quest 13888/13886 Vortex
UPDATE `quest_template` SET `RequiredRaces`='946' WHERE (`Id`='13888');
UPDATE `quest_template` SET `RequiredRaces`='2098253' WHERE (`Id`='13886');
DELETE FROM `creature` WHERE (`id`='34295');
INSERT INTO `creature` VALUES (null, 34295, 1, 1, 1, 0, 0, 3161.97, -1078.24, 485, 3.19916, 300, 0, 0, 6510, 0, 0, 0, 0, 0);
UPDATE `quest_template` SET `RequiredNpcOrGo1`='34295' WHERE (`Id`='13888');
DELETE FROM `creature` WHERE (`id`='34512');
INSERT INTO `creature` VALUES (null, 34512, 1, 1, 1, 0, 0, 2501.82, -1302.55, 135.033, 1.00807, 300, 0, 0, 1006, 0, 0, 0, 0, 0);

-- Quest 13876 Too Far Gone
UPDATE `quest_template` SET `RequiredRaces`='2098253' WHERE (`Id`='13876');

-- Quest 24463 Probing into Ashenvale CHAIN TIMELINE FIX 
UPDATE `quest_template` SET `NextQuestIdChain`='13866' WHERE (`Id`='24463');
UPDATE `quest_template` SET `PrevQuestId`='24463' WHERE (`Id`='13866');

-- Quest 13618 Find Gorat! CHAIN TIMELINE FIX 
UPDATE `quest_template` SET `NextQuestIdChain`='13619' WHERE (`Id`='13618');
UPDATE `quest_template` SET `NextQuestIdChain`='13620' WHERE (`Id`='13619');
UPDATE `quest_template` SET `PrevQuestId`='13618' WHERE (`Id`='13619');
UPDATE `quest_template` SET `PrevQuestId`='13619' WHERE (`Id`='13620');

-- Quest 13628 Got Wood? AUTOCOMPLETE
DELETE FROM `creature_questrelation` WHERE (`id`='33284') AND (`quest`='13628');
INSERT INTO `creature_questrelation` VALUES (33284, 13628);
UPDATE `quest_template` SET `RequiredNpcOrGo1`='0', `RequiredNpcOrGoCount1`='0' WHERE (`Id`='13628');

-- Quest 13640 Management Material 
DELETE FROM `gameobject_template` WHERE (`entry`='194349');
INSERT INTO `gameobject_template` VALUES (194349, 3, 289, 'Freshly Cut Wood', '', '', '', 0, 0, 1, 45069, 0, 0, 0, 0, 0, 1691, 45069, 0, 1, 0, 0, 0, 194349, 13640, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 15595);
DELETE FROM `gameobject_loot_template` WHERE (`entry`='45069') AND (`item`='45069');
INSERT INTO `gameobject_loot_template` (`entry`, `item`) VALUES ('45069', '45069');

UPDATE `creature_template` SET `AIName`='SmartAI' WHERE (`entry`='33440');
UPDATE `creature_template` SET `gossip_menu_id`='33440' WHERE (`entry`='33440');

delete from gossip_menu_option where menu_id = 33440;
insert into gossip_menu_option (menu_id,id,option_text,option_id,npc_option_npcflag) values
(33440,0,"Come now, friend. You chop and I will protect you from the elves, ok?",1,1);

DELETE FROM smart_scripts WHERE entryorguid IN (33440) AND source_type = 0;
INSERT INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, COMMENT) VALUES
(33440,0,1,2,62,0,100,1,33440,0,0,0,50,194349,6,0,0,0,0,8,0,0,0,1645.9,-2469.33,102.885,0.383669,"Summon Obj"),
(33440,0,3,2,62,0,100,1,33440,0,0,0,50,194349,6,0,0,0,0,8,0,0,0,1629.83, -2438.51, 104.921, 1.53035,"Summon Obj"),
(33440,0,4,2,62,0,100,1,33440,0,0,0,50,194349,6,0,0,0,0,8,0,0,0,1466.28, -2376, 97.2518, 0.172785,"Summon Obj"),
(33440,0,6,2,62,0,100,1,33440,0,0,0,50,194349,6,0,0,0,0,8,0,0,0,1438.83, -2398.97, 107.821, 3.87201,"Summon Obj"),
(33440,0,7,2,62,0,100,1,33440,0,0,0,50,194349,6,0,0,0,0,8,0,0,0,1404.89, -2381.07, 108.985, 3.7385,"Summon Obj"),
(33440,0,8,2,62,0,100,1,33440,0,0,0,50,194349,6,0,0,0,0,8,0,0,0,1497.78, -2325.77, 92.4337, 0.306296,"Summon Obj"),
(33440,0,9,2,62,0,100,1,33440,0,0,0,50,194349,6,0,0,0,0,8,0,0,0,1540.73, -2330.65, 99.7052, 5.55669,"Summon Obj"),
(33440,0,10,2,62,0,100,1,33440,0,0,0,50,194349,6,0,0,0,0,8,0,0,0,1668.76, -2504.82, 97.6842, 0.267034,"Summon Obj"),
(33440,0,11,2,62,0,100,1,33440,0,0,0,50,194349,6,0,0,0,0,8,0,0,0,1639.06, -2548.66, 93.8272, 0.474003,"Summon Obj"),
(33440,0,12,2,62,0,100,1,33440,0,0,0,50,194349,6,0,0,0,0,8,0,0,0,1585.85, -2525.85, 103.396, 0.246233,"Summon Obj"),
(33440,0,13,2,62,0,100,1,33440,0,0,0,50,194349,6,0,0,0,0,8,0,0,0,1504.3, -2465.68, 114.789, 6.22114,"Summon Obj"),
(33440,0,14,2,62,0,100,1,33440,0,0,0,50,194349,6,0,0,0,0,8,0,0,0,1552.78, -2435.51, 98.1095, 4.31525,"Summon Obj"),
(33440,0,15,2,62,0,100,1,33440,0,0,0,50,194349,6,0,0,0,0,8,0,0,0,1532.65, -2384.34, 97.9328, 2.30755,"Summon Obj"),
(33440,0,2,5,61,0,100,1,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0,"Chiude gossip"),
(33440,0,5,0,61,0,100,1,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Frase");

update smart_scripts set event_flags = 0 WHERE entryorguid IN (33440) AND source_type = 0;

-- Quest 13651 Needs a Little Lubrication
DELETE FROM `creature_loot_template` WHERE (`entry`='3928') AND (`item`='45071');
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES ('3928', '45071', '-32');

-- Quest 13653 Crisis at Splintertree
UPDATE `quest_template` SET `RequiredNpcOrGo1`='0', `RequiredNpcOrGoCount1`='0' WHERE (`Id`='13653');

-- Quest 13712 To the Rescue! AUTOCOMPLETE
DELETE FROM `creature_questrelation` WHERE (`id`='8582') AND (`quest`='13712');
INSERT INTO `creature_questrelation` VALUES (8582, 13712);
UPDATE `quest_template` SET `RequiredNpcOrGo1`='0', `RequiredNpcOrGoCount1`='0' WHERE (`Id`='13712');

-- Quest 824 Je'neu of the Earthen Ring 
DELETE FROM `creature` WHERE (`id`='12736');
INSERT INTO `creature` VALUES (null, 12736, 48, 1, 1, 0, 248, -157.474, 76.4155, -45.8935, 3.2508, 300, 0, 0, 562, 1, 0, 0, 0, 0);

-- Quest 26891 Amongst the Ruins 
UPDATE `gameobject_template` SET `flags`='0', `data7`='177964', `data8`='26891' WHERE (`entry`='177964');

-- Quest 13958 Condition Critical! CHAIN TIMELINE FIX 
UPDATE `quest_template` SET `NextQuestIdChain`='13962' WHERE (`Id`='13958');
UPDATE `quest_template` SET `PrevQuestId`='13958' WHERE (`Id`='13962');

-- Quest 13977 Mass Production CHAIN TIMELINE FIX 
UPDATE `quest_template` SET `NextQuestIdChain`='13980' WHERE (`Id`='13977');
UPDATE `quest_template` SET `PrevQuestId`='13977' WHERE (`Id`='13980');

-- Quest 13980 They're Out There!
UPDATE `creature_template` SET `faction_A`='14', `faction_H`='14' WHERE (`entry`='34603');
DELETE FROM `creature` WHERE (`id`='34603');
INSERT INTO `creature` VALUES (null, 34603, 1, 1, 1, 29294, 34603, 1989.53, -721.587, 100.388, 2.10502, 600, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34603, 1, 1, 1, 29294, 34603, 2038.36, -729.511, 102.086, 4.29068, 600, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34603, 1, 1, 1, 29294, 34603, 2220.75, -970.984, 90.1307, 1.37962, 600, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34603, 1, 1, 1, 29294, 34603, 2188.14, -900.467, 97.0674, 0.69913, 600, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34603, 1, 1, 1, 29296, 34603, 2048.5, -814.132, 99.9461, 4.35553, 600, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34603, 1, 1, 1, 29296, 34603, 2205.62, -934.851, 91.7555, 0.870951, 600, 0, 0, 0, 0, 0, 0, 0, 0);

-- Quest 13967 Thinning the... Herd? CHAIN TIMELINE FIX 
UPDATE `quest_template` SET `NextQuestIdChain`='6621' WHERE (`Id`='13967');
UPDATE `quest_template` SET `PrevQuestId`='13967' WHERE (`Id`='6621');

DELETE FROM `creature_loot_template` WHERE (`entry`='3750') AND (`item`='46741');
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES ('3750', '46741', '-87');
DELETE FROM `creature_loot_template` WHERE (`entry`='3743') AND (`item`='46741');
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES ('3743', '46741', '-85');
DELETE FROM `creature_loot_template` WHERE (`entry`='3745') AND (`item`='46741');
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES ('3745', '46741', '-78');

-- Quest 6621 King of the Foulweald
-- wrong spawn
DELETE FROM `creature` WHERE (`id`='12921');
DELETE FROM `gameobject` WHERE (`id`='195143');
--
DELETE FROM `gameobject` WHERE (`id`='300131');
INSERT INTO `gameobject` VALUES (null, 300131, 1, 1, 1, 2232.37, -1550.04, 93.2599, 0.752432, 0, 0, 0.367404, 0.930062, 300, 0, 1);
DELETE FROM `gameobject` WHERE (`id`='2054') AND (`position_y`='-1550');
INSERT INTO `gameobject` VALUES (null, 2054, 1, 1, 1, 2232.29, -1550, 93.2609, 6.25528, 0, 0, 0.0139527, -0.999903, 300, 0, 1);

-- Quest 26416 Well, Come to the Jungle CHAIN TIMELINE FIX 
UPDATE `quest_template` SET `NextQuestIdChain`='26417' WHERE (`Id`='26416');
UPDATE `quest_template` SET `NextQuestIdChain`='26278' WHERE (`Id`='26417');
UPDATE `quest_template` SET `NextQuestIdChain`='26278' WHERE (`Id`='28688');
UPDATE `quest_template` SET `PrevQuestId`='26416' WHERE (`Id`='26417');
UPDATE `quest_template` SET `PrevQuestId`='26417' WHERE (`Id`='26278');

-- Quest 28532 Warchief's Command: Stonetalon Mountains! CHAIN TIMELINE FIX
UPDATE `quest_template` SET `NextQuestIdChain`='25945' WHERE (`Id`='28532');
UPDATE `quest_template` SET `NextQuestIdChain`='25999' WHERE (`Id`='25945');
UPDATE `quest_template` SET `NextQuestIdChain`='26001' WHERE (`Id`='25999');
UPDATE `quest_template` SET `NextQuestIdChain`='26002' WHERE (`Id`='26001');
UPDATE `quest_template` SET `NextQuestIdChain`='26004' WHERE (`Id`='26002');
UPDATE `quest_template` SET `PrevQuestId`='28532' WHERE (`Id`='25945');
UPDATE `quest_template` SET `PrevQuestId`='25945' WHERE (`Id`='25999');
UPDATE `quest_template` SET `PrevQuestId`='25999' WHERE (`Id`='26001');
UPDATE `quest_template` SET `PrevQuestId`='26001' WHERE (`Id`='26002');
UPDATE `quest_template` SET `PrevQuestId`='26002' WHERE (`Id`='26004');

-- Quest 25945 We're Here to Do One Thing, Maybe Two... AUTOCOMPLETE - VEHICLE MISSING
UPDATE `quest_template` SET `SpecialFlags`='0' WHERE (`Id`='25945');
UPDATE `quest_template` SET `Method`='0' WHERE (`Id`='25945');

-- Quest 26010 Ashes to Ashes CHAIN TIMELINE FIX
UPDATE `quest_template` SET `NextQuestIdChain`='26020' WHERE (`Id`='26010');
UPDATE `quest_template` SET `NextQuestIdChain`='26044' WHERE (`Id`='26020');
UPDATE `quest_template` SET `NextQuestIdChain`='26045' WHERE (`Id`='26044');
UPDATE `quest_template` SET `PrevQuestId`='26010' WHERE (`Id`='26020');
UPDATE `quest_template` SET `PrevQuestId`='26044' WHERE (`Id`='26044');
UPDATE `quest_template` SET `PrevQuestId`='26044' WHERE (`Id`='26045');

-- Quest 26048 Spare Parts Up In Here! CHAIN TIMELINE FIX
UPDATE `quest_template` SET `NextQuestIdChain`='26058' WHERE (`Id`='26048');
UPDATE `quest_template` SET `PrevQuestId`='26048' WHERE (`Id`='26058');

-- Quest 13841 All Apologies CHAIN TIMELINE FIX
UPDATE `quest_template` SET `NextQuestIdChain`='13842' WHERE (`Id`='13841');
UPDATE `quest_template` SET `PrevQuestId`='13841' WHERE (`Id`='13842');

-- Quest 13936 Tweedle's Dumb CHAIN TIMELINE FIX
UPDATE `quest_template` SET `NextQuestIdChain`='13942' WHERE (`Id`='13936');
UPDATE `quest_template` SET `NextQuestIdChain`='13944' WHERE (`Id`='13942');
UPDATE `quest_template` SET `NextQuestIdChain`='13947' WHERE (`Id`='13944');
UPDATE `quest_template` SET `PrevQuestId`='13936' WHERE (`Id`='13942');
UPDATE `quest_template` SET `PrevQuestId`='13942' WHERE (`Id`='13944');
UPDATE `quest_template` SET `PrevQuestId`='13944' WHERE (`Id`='13947');

-- Quest 13936 Tweedle
DELETE FROM `spell_scripts` WHERE (`datalong`='34424');
INSERT INTO `spell_scripts` (`id`, `command`, `datalong`) VALUES ('85933', '8', '34424');
DELETE FROM `spell_linked_spell` WHERE (`spell_trigger`='65433');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`) VALUES ('65433', '85933');

-- Quest 13947 Blastranaar!
UPDATE `quest_template` SET `RequiredNpcOrGo1`='6087', `RequiredNpcOrGo2`='34132' WHERE (`Id`='13947');

-- Quest 13890 Keep the Fires Burning CHAIN TIMELINE FIX
UPDATE `quest_template` SET `NextQuestIdChain`='13920' WHERE (`Id`='13890');
UPDATE `quest_template` SET `PrevQuestId`='13890' WHERE (`Id`='13920');

-- Quest 13890 Keep the Fires Burning
DELETE FROM `spell_scripts` WHERE (`datalong`='34329');
INSERT INTO `spell_scripts` (`id`, `command`, `datalong`) VALUES ('85933', '8', '34329');
DELETE FROM `spell_linked_spell` WHERE (`spell_trigger`='65213');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`) VALUES ('65213', '85933');

-- Quest 13920 Before You Go...
DELETE FROM `creature_loot_template` WHERE (`entry`='3816') AND (`item`='46392');
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES ('3816', '46392', '-30');

-- Quest 13880 Hot Lava
UPDATE `quest_template` SET `RequiredNpcOrGo1`='43242' WHERE (`Id`='13880');
DELETE FROM `spell_scripts` WHERE (`datalong`='43242');
INSERT INTO `spell_scripts` (`id`, `command`, `datalong`) VALUES ('85933', '8', '43242');
DELETE FROM `spell_linked_spell` WHERE (`spell_trigger`='65115');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`) VALUES ('65115', '85933');
DELETE FROM `conditions` WHERE (`SourceEntry`='65115');
INSERT INTO `conditions` VALUES (17, 0, 65115, 0, 0, 30, 0, 195005, 18, 0, 0, 0, 0, '', 'Spell can be used only near a gameobject');

-- Quest 13815 Making Stumps REMOVED 
DELETE FROM `creature_questrelation` WHERE (`id`='33889') AND (`quest`='13815');

-- Quest 13798 Rain of Destruction AUTOCOMPLETE 
UPDATE `quest_template` SET `RequiredNpcOrGo1`='0', `RequiredNpcOrGo2`='0', `RequiredNpcOrGoCount1`='0', `RequiredNpcOrGoCount2`='0' WHERE (`Id`='13798');
DELETE FROM `creature_involvedrelation` WHERE (`id`='33760') AND (`quest`='13798');
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES ('33760', '13798');

-- Quest 13805 Pierce Their Heart!
DELETE FROM `item_template` WHERE (`entry`='45683');
INSERT INTO `item_template` (`entry`, `class`, `name`, `displayid`, `Quality`, `Flags`, `FlagsExtra`, `spellid_1`, `spellcooldown_1`, `bonding`, `Material`) VALUES ('45683', '12', 'Tainted Blood of the Kaldorei', '58441', '1', '64', '8192', '90863', '15000', '4', '4');
DELETE FROM `spell_scripts` WHERE (`datalong`='33847');
INSERT INTO `spell_scripts` (`id`, `command`, `datalong`) VALUES ('85933', '8', '33847');
DELETE FROM `spell_linked_spell` WHERE (`spell_trigger`='90863');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`) VALUES ('90863', '85933');
DELETE FROM `conditions` WHERE (`SourceEntry`='90863');
INSERT INTO `conditions` VALUES (17, 0, 90863, 0, 0, 30, 0, 1945630, 10, 0, 0, 0, 0, '', 'Spell can be used only near a gameobject');

-- Quest 13842 Dread Head Redemption
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE (`entry`='33760');
UPDATE `creature_template` SET `gossip_menu_id`='33760' WHERE (`entry`='33760');

delete from gossip_menu_option where menu_id = 33760;
insert into gossip_menu_option (menu_id,id,option_text,option_id,npc_option_npcflag) values
(33760,0,"This is terrible, Durak! Hellscream is conviced there's a demon behind our work here! What can we do?!",1,1);

DELETE FROM smart_scripts WHERE entryorguid IN (33760) AND source_type = 0;
INSERT INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, COMMENT) VALUES
(33760,0,1,2,62,0,100,1,33760,0,0,0,12,44414,6,60000,0,0,0,8,0,0,0,2463.4,-2465.15,109.33,2.79684,"Summon Durak"),
(33760,0,2,5,61,0,100,1,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0,"Chiude gossip"),
(33760,0,5,0,61,0,100,1,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Frase");

update smart_scripts set event_flags = 0 WHERE entryorguid IN (33760) AND source_type = 0;
UPDATE `creature_template` SET `faction_A`='14', `faction_H`='14' WHERE (`entry`='44414');
DELETE FROM `creature_loot_template` WHERE (`entry`='44414') AND (`item`='60638');
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES ('44414', '60638', '-100');
UPDATE `creature_template` SET `lootid`='44414' WHERE (`entry`='44414');

-- Alliance part

-- Quest 13886 Vortex
UPDATE `quest_template` SET `RequiredNpcOrGo1`='34295' WHERE (`Id`='13886');
DELETE FROM `creature` WHERE (`id`='34283');
INSERT INTO `creature` VALUES (null, 34283, 1, 1, 1, 0, 0, 2496.82, -1296.85, 134.08, 0.480836, 300, 0, 0, 4055, 5, 0, 0, 0, 0);
DELETE FROM `creature_template_addon` WHERE (`entry`='34283');

-- Quest 13595 Of Their Own Design
UPDATE `gameobject_template` SET `data1`='194202', `data7`='194202', `data8`='13595', `faction`='35', `flags`='0' WHERE (`entry`='194202');
DELETE FROM `gameobject_loot_template` WHERE (`entry`='194202') AND (`item`='44967');
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES ('194202', '44967', '-100');
DELETE FROM `conditions` WHERE (`SourceEntry`='62506');
INSERT INTO `conditions` VALUES (17, 0, 62506, 0, 0, 29, 0, 33183, 10, 0, 0, 0, 0, '', 'Spell can be used only near a npc');
DELETE FROM `spell_scripts` WHERE (`datalong`='33183');
INSERT INTO `spell_scripts` (`id`, `command`, `datalong`) VALUES ('85933', '8', '33183');
DELETE FROM `spell_linked_spell` WHERE (`spell_trigger`='62506');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`) VALUES ('62506', '85933');

-- Quest 26473 Bathran's Hair CHAIN TIMELINE FIX
UPDATE `quest_template` SET `NextQuestIdChain`='13623' WHERE (`Id`='26473');
UPDATE `quest_template` SET `PrevQuestId`='26473' WHERE (`Id`='13623');

-- Quest 28492 Hero's Call: Ashenvale! CHAIN TIMELINE FIX
UPDATE `quest_template` SET `NextQuestIdChain`='13594' WHERE (`Id`='28492');
UPDATE `quest_template` SET `NextQuestIdChain`='13617' WHERE (`Id`='13594');
UPDATE `quest_template` SET `NextQuestIdChain`='26465' WHERE (`Id`='13617');
UPDATE `quest_template` SET `PrevQuestId`='28492' WHERE (`Id`='13594');
UPDATE `quest_template` SET `PrevQuestId`='13594' WHERE (`Id`='13617');
UPDATE `quest_template` SET `PrevQuestId`='13617' WHERE (`Id`='26465');

-- Quest 26897 Blackfathom Deeps
DELETE FROM `creature` WHERE (`id`='33260');
INSERT INTO `creature` VALUES (null, 33260, 48, 1, 1, 0, 0, -164.144, 85.7154, -45.5824, 4.41319, 300, 0, 0, 2605, 0, 0, 0, 0, 0);

-- Quest 13985 Clear the Shrine CHAIN TIMELINE FIX
UPDATE `quest_template` SET `NextQuestIdChain`='13987' WHERE (`Id`='13985');
UPDATE `quest_template` SET `PrevQuestId`='13985' WHERE (`Id`='13987');

-- Quest 13985 Clear the Shrine
UPDATE `creature_template_addon` SET `auras`='45631' WHERE (`entry`='6731');
UPDATE `creature_template_addon` SET `auras`='45631' WHERE (`entry`='3698');
UPDATE `creature_template_addon` SET `auras`='45631' WHERE (`entry`='8308');
DELETE FROM `creature_questrelation` WHERE (`id`='3698') AND (`quest`='13985');
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES ('3698', '13985');
UPDATE `creature` SET `id`='34604' WHERE (`id`='34608');

-- Quest 13982 In a Bind
UPDATE `quest_template` SET `StartScript`='13982' WHERE (`Id`='13982');
DELETE FROM `quest_start_scripts` WHERE (`id`='13982');
INSERT INTO `quest_start_scripts` (`id`, `command`, `datalong`, `datalong2`, `x`, `y`, `z`, `o`) VALUES ('13982', '10', '34602', '120000', '2383.63', '639.579', '148.897', '2.11285');
UPDATE `creature_template` SET `faction_A`='14', `faction_H`='14', `lootid`='34602' WHERE (`entry`='34602');
DELETE FROM `creature_loot_template` WHERE (`entry`='34602') AND (`item`='46774');
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES ('34602', '46774', '-100');

-- Quest 13965 Check in on the Edunes CHAIN TIMELINE FIX
UPDATE `quest_template` SET `NextQuestIdChain`='13976' WHERE (`Id`='13965');
UPDATE `quest_template` SET `PrevQuestId`='13965' WHERE (`Id`='13976');

-- Quest 26463 Check in on the Edunes CHAIN TIMELINE FIX
UPDATE `quest_template` SET `NextQuestIdChain`='26464' WHERE (`Id`='26463');
UPDATE `quest_template` SET `NextQuestIdChain`='13645' WHERE (`Id`='26464');
UPDATE `quest_template` SET `PrevQuestId`='26463' WHERE (`Id`='26464');
UPDATE `quest_template` SET `PrevQuestId`='26464' WHERE (`Id`='13645');

DELETE FROM `creature_loot_template` WHERE (`entry`='33419') AND (`item`='5463');
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES ('33419', '5463', '-23');
DELETE FROM `creature_loot_template` WHERE (`entry`='33444') AND (`item`='5463');
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES ('33444', '5463', '-7');
UPDATE `creature_template` SET `lootid`='33419' WHERE (`entry`='33419');
UPDATE `creature_template` SET `lootid`='33444' WHERE (`entry`='33444');

-- Quest 13642 Bathed in Light CHAIN TIMELINE FIX
UPDATE `quest_template` SET `NextQuestIdChain`='26474' WHERE (`Id`='13642');
UPDATE `quest_template` SET `PrevQuestId`='13642' WHERE (`Id`='26474');

-- Quest 26453 A Helping Hand CHAIN TIMELINE FIX
UPDATE `quest_template` SET `NextQuestIdChain`='26454' WHERE (`Id`='26453');
UPDATE `quest_template` SET `PrevQuestId`='26453' WHERE (`Id`='26454');

-- Quest 13624 A Squad of Your Own CHAIN TIMELINE FIX
UPDATE `quest_template` SET `NextQuestIdChain`='13626' WHERE (`Id`='13624');
UPDATE `quest_template` SET `PrevQuestId`='13624' WHERE (`Id`='13626');

-- Quest 13626 Respect for the Fallen
DELETE FROM `npc_spellclick_spells` WHERE (`npc_entry`='33348') AND (`spell_id`='62838');
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES ('33348', '62838', '3');
UPDATE `creature_template` SET `npcflag`='16777216' WHERE (`entry`='33348');
UPDATE `creature_template_addon` SET `auras`='62817' WHERE (`entry`='33348');
UPDATE `creature_template_addon` SET `auras`='62817' WHERE (`entry`='33347');
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE (`entry`='33347');
UPDATE `creature_template` SET `npcflag`='16777216' WHERE (`entry`='33347');
DELETE FROM `npc_spellclick_spells` WHERE (`npc_entry`='33347') AND (`spell_id`='62839');
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES ('33347', '62839', '1');
DELETE FROM `smart_scripts` WHERE (`entryorguid`='33347');
INSERT INTO `smart_scripts` VALUES (33347, 0, 0, 1, 8, 0, 100, 0, 62839, 0, 0, 0, 56, 45043, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '');

-- Quest 13796 The Forest Heart
UPDATE `gameobject` SET `id`='1945630' WHERE (`id`='194549');
DELETE FROM `gameobject_template` WHERE (`entry`='1945630');
INSERT INTO `gameobject_template` VALUES (1945630, 3, 7918, 'The Forest Heart', '', 'Collecting', '', 35, 0, 2, 45573, 0, 0, 0, 0, 0, 1690, 45573, 30, 0, 0, 0, 0, 194563, 13796, 0, 0, 0, 1, 0, 19676, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 15595);
DELETE FROM `gameobject_loot_template` WHERE (`entry`='45573') AND (`item`='45573');
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES ('45573', '45573', '-100');

-- Quest 26467 Vile Satyr! Dryads in Danger! CHAIN TIMELINE FIX
UPDATE `quest_template` SET `NextQuestIdChain`='26468' WHERE (`Id`='26467');
UPDATE `quest_template` SET `PrevQuestId`='26467' WHERE (`Id`='26468');

-- Quest 26443 Diabolical Plans CHAIN TIMELINE FIX
UPDATE `quest_template` SET `NextQuestIdChain`='26445' WHERE (`Id`='26443');
UPDATE `quest_template` SET `PrevQuestId`='26443' WHERE (`Id`='26445');

-- Quest 26457 Agents of Destruction CHAIN TIMELINE FIX
UPDATE `quest_template` SET `NextQuestIdChain`='13698' WHERE (`Id`='26457');
UPDATE `quest_template` SET `PrevQuestId`='26457' WHERE (`Id`='13698');

-- Quest 13928 Recover the Fallen CHAIN TIMELINE FIX
UPDATE `quest_template` SET `NextQuestIdChain`='13935' WHERE (`Id`='13928');
UPDATE `quest_template` SET `NextQuestIdChain`='26456' WHERE (`Id`='13935');
UPDATE `quest_template` SET `PrevQuestId`='13928' WHERE (`Id`='13935');
UPDATE `quest_template` SET `PrevQuestId`='13935' WHERE (`Id`='26456');

-- Quest 13981 They Set Them Up The Bomb!
UPDATE `gameobject_template` SET `faction`='35', `flags`='32' WHERE (`entry`='195134');

-- Quest 13919 A Trip to the Moonwell CHAIN TIMELINE FIX removed first
-- UPDATE `quest_template` SET `NextQuestIdChain`='13921' WHERE (`Id`='13919');
UPDATE `quest_template` SET `NextQuestIdChain`='13922' WHERE (`Id`='13921');
UPDATE `quest_template` SET `PrevQuestId`='' WHERE (`Id`='13921');
UPDATE `quest_template` SET `PrevQuestId`='13921' WHERE (`Id`='13922');
DELETE FROM `creature_questrelation` WHERE (`id`='3894') AND (`quest`='13919');
DELETE FROM `creature_questrelation` WHERE (`id`='3894') AND (`quest`='13921');
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES ('3894', '13921');

-- Quest 13979 The Goblin Braintrust
DELETE FROM `creature_loot_template` WHERE (`entry`='34591') AND (`item`='46768');
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES ('34591', '46768', '-95');
UPDATE `creature_template` SET `lootid`='34591' WHERE (`entry`='34591');

-- Quest 25613 Do Yourself a Favor CHAIN TIMELINE FIX
UPDATE `quest_template` SET `NextQuestIdChain`='25614' WHERE (`Id`='25613');
UPDATE `quest_template` SET `NextQuestIdChain`='25615' WHERE (`Id`='25614');
UPDATE `quest_template` SET `NextQuestIdChain`='25616' WHERE (`Id`='25615');
UPDATE `quest_template` SET `PrevQuestId`='25613' WHERE (`Id`='25614');
UPDATE `quest_template` SET `PrevQuestId`='25614' WHERE (`Id`='25615');
UPDATE `quest_template` SET `PrevQuestId`='25615' WHERE (`Id`='25616');

-- Quest 13928 Recover the Fallen CHAIN TIMELINE FIX
UPDATE `quest_template` SET `NextQuestIdChain`='26470' WHERE (`Id`='13964');
UPDATE `quest_template` SET `PrevQuestId`='13964' WHERE (`Id`='26470');

-- Quest 13849 Astranaar's Burning! CHAIN TIMELINE FIX
UPDATE `quest_template` SET `NextQuestIdChain`='13853' WHERE (`Id`='13849');
UPDATE `quest_template` SET `PrevQuestId`='13849' WHERE (`Id`='13853');

-- Quest 13849 Astranaar's Burning!
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE (`entry`='34123');
DELETE FROM `smart_scripts` WHERE (`entryorguid`='34123');
INSERT INTO `smart_scripts` VALUES (34123, 0, 1, 2, 8, 0, 100, 0, 64558, 0, 0, 0, 33, 34123, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, '');
INSERT INTO `smart_scripts` VALUES (34123, 0, 2, 5, 61, 0, 100, 0, 0, 0, 0, 0, 41, 3, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, '');
-- Spawn Fire on the city - source  position like official - sniff
DELETE FROM `gameobject` WHERE (`id`='176746');
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2819.38, -317.431, 115.277, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2811.24, -275.465, 130.418, 0.84744, 0, 0, 0.411154, 0.911566, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2810.01, -275.840, 110.032, 1.97887, 0, 0, 0.835715, 0.549163, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2808.41, -313.024, 119.026, 2.39860, 0, 0, 0.931786, 0.363009, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2802.18, -325.010, 116.592, 1.29105, 0, 0, 0.601619, 0.798783, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2800.41, -264.402, 132.852, 3.24277, 0, 0, 0.998721, -0.0505664, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2799.33, -349.537, 120.350, 2.95610, 0, 0, 0.995702, 0.0926144, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2792.98, -381.928, 114.588, 3.80826, 0, 0, 0.944958, -0.327193, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2784.89, -424.233, 123.008, 4.03224, 0, 0, 0.902472, -0.430748, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2779.94, -299.078, 119.446, 4.65662, 0, 0, 0.726546, -0.687118, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2773.10, -408.986, 125.473, 0.96688, 0, 0, 0.464831, 0.885399, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2771.31, -297.304, 126.154, 1.73539, 0, 0, 0.762842, 0.646585, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2771.04, -291.716, 136.272, 5.32860, 0, 0, 0.459377, -0.888241, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2771.00, -421.207, 132.041, 4.39865, 0, 0, 0.808893, -0.587956, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2768.63, -310.858, 120.006, 6.01712, 0, 0, 0.13264, -0.991164, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2764.69, -310.333, 131.989, 4.30888, 0, 0, 0.834461, -0.551067, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2759.31, -397.641, 128.941, 5.16102, 0, 0, 0.532104, -0.846679, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2754.53, -308.010, 128.327, 1.66992, 0, 0, 0.741271, 0.671206, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2752.71, -452.756, 127.844, 4.18712, 0, 0, 0.866443, -0.499276, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2750.40, -410.627, 134.145, 2.12545, 0, 0, 0.873684, 0.486494, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2747.58, -383.599, 111.755, 2.61239, 0, 0, 0.965197, 0.261522, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2746.70, -294.354, 133.234, 5.62297, 0, 0, 0.324143, -0.946008, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2745.98, -452.087, 121.687, 5.54443, 0, 0, 0.361035, -0.932552, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2742.62, -426.497, 132.557, 5.72899, 0, 0, 0.273563, -0.961854, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2741.70, -441.704, 127.563, 5.13370, 0, 0, 0.543621, -0.839331, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2740.82, -413.218, 121.900, 1.01820, 0, 0, 0.487392, 0.873184, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2733.86, -297.445, 114.876, 5.34574, 0, 0, 0.451746, -0.892146, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2729.70, -344.726, 119.650, 1.38341, 0, 0, 0.637849, 0.770161, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2729.62, -309.025, 120.414, 6.09579, 0, 0, 0.0935588, -0.995614, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2723.58, -354.471, 121.815, 5.99762, 0, 0, 0.142298, -0.989824, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2721.94, -362.297, 135.295, 0.20923, 0, 0, 0.104427, 0.994533, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2720.46, -324.166, 119.021, 6.06438, 0, 0, 0.109184, -0.994022, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2718.26, -341.896, 129.332, 4.46609, 0, 0, 0.788611, -0.614892, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2717.86, -315.728, 124.487, 2.41620, 0, 0, 0.934944, 0.354795, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2703.43, -366.877, 121.000, 3.70818, 0, 0, 0.96014, -0.279519, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2692.70, -365.821, 113.233, 3.82599, 0, 0, 0.942019, -0.33556, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2684.30, -360.988, 123.441, 1.23417, 0, 0, 0.578658, 0.81557, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2682.71, -370.414, 120.242, 2.40834, 0, 0, 0.933541, 0.35847, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2673.78, -370.516, 126.296, 3.96341, 0, 0, 0.916757, -0.399444, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2672.17, -382.903, 120.905, 4.51712, 0, 0, 0.772669, -0.63481, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2659.50, -406.681, 120.993, 2.84815, 0, 0, 0.989256, 0.146196, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2656.26, -377.329, 121.357, 4.81557, 0, 0, 0.669701, -0.742631, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2645.60, -454.238, 126.743, 0.55871, 0, 0, 0.275738, 0.961233, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2640.94, -376.033, 107.311, 0.70083, 0, 0, 0.34328, 0.939233, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 176746, 1, 1, 1, 2639.45, -438.005, 124.045, 4.54534, 0, 0, 0.763633, -0.645651, 300, 0, 1);
-- Spawn NPC credit on the fire - source  position like official - sniff
DELETE FROM `creature` WHERE (`id`='34123');
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2819.38, -317.431, 115.277, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2811.24, -275.465, 130.418, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2810.01, -275.840, 110.032, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2808.41, -313.024, 119.026, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2802.18, -325.010, 116.592, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2800.41, -264.402, 132.852, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2799.33, -349.537, 120.350, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2792.98, -381.928, 114.588, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2784.89, -424.233, 123.008, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2779.94, -299.078, 119.446, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2773.10, -408.986, 125.473, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2771.31, -297.304, 126.154, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2771.04, -291.716, 136.272, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2771.00, -421.207, 132.041, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2768.63, -310.858, 120.006, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2764.69, -310.333, 131.989, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2759.31, -397.641, 128.941, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2754.53, -308.010, 128.327, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2752.71, -452.756, 127.844, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2750.40, -410.627, 134.145, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2747.58, -383.599, 111.755, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2746.70, -294.354, 133.234, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2745.98, -452.087, 121.687, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2742.62, -426.497, 132.557, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2741.70, -441.704, 127.563, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2740.82, -413.218, 121.900, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2733.86, -297.445, 114.876, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2729.70, -344.726, 119.650, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2729.62, -309.025, 120.414, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2723.58, -354.471, 121.815, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2721.94, -362.297, 135.295, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2720.46, -324.166, 119.021, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2718.26, -341.896, 129.332, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2717.86, -315.728, 124.487, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2703.43, -366.877, 121.000, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2692.70, -365.821, 113.233, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2684.30, -360.988, 123.441, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2682.71, -370.414, 120.242, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2673.78, -370.516, 126.296, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2672.17, -382.903, 120.905, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2659.50, -406.681, 120.993, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2656.26, -377.329, 121.357, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2645.60, -454.238, 126.743, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2640.94, -376.033, 107.311, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34123, 1, 1, 1, 0, 0, 2639.45, -438.005, 124.045, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);

-- Quest 13853 Return Fire - REMOVED - VEHICLE BUG
DELETE FROM `creature_questrelation` WHERE (`id`='4079') AND (`quest`='13853');

-- Quest 13698 Explosives Shredding - REMOVED - VEHICLE BUG
DELETE FROM `creature_questrelation` WHERE (`id`='17287') AND (`quest`='13698');

-- Quest 26446 Reclaiming Felfire Hill CHAIN TIMELINE FIX
UPDATE `quest_template` SET `NextQuestIdChain`='13766' WHERE (`Id`='26446');
UPDATE `quest_template` SET `NextQuestIdChain`='13792' WHERE (`Id`='13766');
UPDATE `quest_template` SET `PrevQuestId`='26446' WHERE (`Id`='13766');
UPDATE `quest_template` SET `PrevQuestId`='13766' WHERE (`Id`='13792');

-- Quest 13766 Closure is Only Natural
DELETE FROM `creature_template` WHERE (`entry`='341230');
INSERT INTO `creature_template` VALUES (341230, 0, 0, 0, 0, 0, 1126, 15880, 0, 0, 'Demon Gates Bunny', '', '', 0, 1, 1, 0, 0, 35, 35, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 33555200, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 1024, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 3, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, '', 15595);
DELETE FROM `creature_template_addon` WHERE (`entry`='341230');
INSERT INTO `creature_template_addon` VALUES (341230, 0, 0, 65536, 1, 0, '64573 52855');
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE (`entry`='341230');
DELETE FROM `smart_scripts` WHERE (`entryorguid`='341230');
INSERT INTO `smart_scripts` VALUES (341230, 0, 1, 2, 8, 0, 100, 0, 63578, 0, 0, 0, 33, 33767, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, '');
INSERT INTO `smart_scripts` VALUES (341230, 0, 2, 5, 61, 0, 100, 0, 0, 0, 0, 0, 41, 3, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, '');
-- Spawn NPC credit - source  position like official - sniff
DELETE FROM `creature` WHERE (`id`='341230');
INSERT INTO `creature` VALUES (null, 341230, 1, 1, 1, 0, 0, 1860.63, -3166.80, 95.3251, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 341230, 1, 1, 1, 0, 0, 1781.57, -3180.35, 91.6415, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 341230, 1, 1, 1, 0, 0, 1727.07, -3457.88, 144.293, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 341230, 1, 1, 1, 0, 0, 1710.88, -3149.39, 93.8152, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 341230, 1, 1, 1, 0, 0, 1703.57, -3027.70, 134.616, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 341230, 1, 1, 1, 0, 0, 1702.03, -3465.43, 144.692, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 341230, 1, 1, 1, 0, 0, 1692.22, -3001.30, 146.705, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 341230, 1, 1, 1, 0, 0, 1682.56, -3420.82, 145.402, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 341230, 1, 1, 1, 0, 0, 1658.45, -3083.14, 89.4618, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 341230, 1, 1, 1, 0, 0, 1658.25, -3182.58, 126.937, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 341230, 1, 1, 1, 0, 0, 1652.57, -3401.83, 143.563, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 341230, 1, 1, 1, 0, 0, 1644.87, -3127.26, 88.5480, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 341230, 1, 1, 1, 0, 0, 1643.97, -3275.80, 150.204, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 341230, 1, 1, 1, 0, 0, 1623.91, -3330.64, 144.374, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 341230, 1, 1, 1, 0, 0, 1620.87, -3025.52, 96.1755, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 341230, 1, 1, 1, 0, 0, 1611.03, -3083.82, 89.9642, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 341230, 1, 1, 1, 0, 0, 1603.38, -2986.52, 182.152, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 341230, 1, 1, 1, 0, 0, 1582.15, -2889.98, 181.976, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 341230, 1, 1, 1, 0, 0, 1574.30, -2824.32, 181.704, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 341230, 1, 1, 1, 0, 0, 1551.41, -2884.56, 133.224, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 341230, 1, 1, 1, 0, 0, 1528.89, -2868.59, 124.904, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 341230, 1, 1, 1, 0, 0, 1527.10, -2857.06, 182.661, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 341230, 1, 1, 1, 0, 0, 1499.29, -2835.97, 111.927, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 341230, 1, 1, 1, 0, 0, 1451.96, -2794.42, 145.078, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 341230, 1, 1, 1, 0, 0, 1421.22, -2796.81, 153.797, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 341230, 1, 1, 1, 0, 0, 1417.01, -2822.99, 118.144, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 341230, 1, 1, 1, 0, 0, 1404.05, -2800.93, 123.360, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 341230, 1, 1, 1, 0, 0, 1374.72, -2831.77, 108.804, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0);

-- Quest 13928 Recover the Fallen
UPDATE `creature_template` SET `modelid1`='2723', `modelid2`=NULL, `AIName`='SmartAI', `npcflag`='16777216'  WHERE (`entry`='34426');
DELETE FROM `npc_spellclick_spells` WHERE (`npc_entry`='34426') AND (`spell_id`='62839');
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES ('34426', '62839', '1');
DELETE FROM `smart_scripts` WHERE (`entryorguid`='34426');
INSERT INTO `smart_scripts` VALUES (34426, 0, 1, 2, 8, 0, 100, 0, 62839, 0, 0, 0, 56, 46543, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '');
INSERT INTO `smart_scripts` VALUES (34426, 0, 2, 5, 61, 0, 100, 0, 0, 0, 0, 0, 41, 3, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, '');

-- Quest 13935 Defend the Tree!
UPDATE `creature_template` SET `faction_A`='14' WHERE (`entry`='32850');
UPDATE `creature_template` SET `faction_A`='14' WHERE (`entry`='34390');
UPDATE `quest_template` SET `StartScript`='13935', `CompleteScript`='13935' WHERE (`Id`='13935');
DELETE FROM `quest_start_scripts` WHERE (`id`='13935');
INSERT INTO `quest_start_scripts` (`id`, `command`, `datalong`, `datalong2`) VALUES ('13935', '15', '65396', '2');
DELETE FROM `quest_end_scripts` WHERE (`id`='13935');
INSERT INTO `quest_end_scripts` (`id`, `command`, `datalong`) VALUES ('13935', '14', '65396');
DELETE FROM `creature_template` WHERE (`entry`='343770');
INSERT INTO `creature_template` VALUES (343770, 0, 0, 0, 0, 0, 29202, 0, 0, 0, 'Halannia', '', '', 0, 22, 22, 0, 0, 80, 80, 3, 1, 1, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 2, 33536, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, '', 15595);
DELETE FROM `creature` WHERE (`id`='343770');
INSERT INTO `creature` VALUES (null, 343770, 1, 1, 2, 0, 0, 2710.25, -1891.08, 207.921, 1.309, 120, 0, 0, 1, 0, 0, 0, 0, 0);
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE (`entry`='343770');
UPDATE `creature_template` SET `gossip_menu_id`='34377' WHERE (`entry`='343770');
delete from gossip_menu_option where menu_id = 34377;
insert into gossip_menu_option (menu_id,id,option_text,option_id,npc_option_npcflag) values
(34377,0,"OK, I'm ready to return",1,1);
DELETE FROM smart_scripts WHERE entryorguid IN (343770) AND source_type = 0;
INSERT INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, COMMENT) VALUES
(343770,0,1,2,62,0,100,0,34377,0,0,0,28,65396,0,0,0,0,0,7,0,0,0,0,0,0,0,"Remove aura"),
(343770,0,2,5,61,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0,"Chiude gossip"),
(343770,0,5,0,61,0,100,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Frase");
update smart_scripts set event_flags = 0 WHERE entryorguid IN (343770) AND source_type = 0;
-- Spawn NPC quest on phase 2
DELETE FROM `creature` WHERE (`id`='34390');
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2781.77, -1883.85, 189.099, 2.53018, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2801.12, -1853.47, 192.511, 2.43593, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2794.2, -1828.05, 201.77, 3.33128, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2784.76, -1817.62, 204.093, 3.46873, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2762.41, -1823.85, 200.424, 3.41375, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2739.96, -1840.5, 197.155, 2.86005, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2744.42, -1880.62, 190.265, 1.4149, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2764.87, -1906.66, 189.216, 2.0118, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2753.82, -1924.26, 187.602, 3.76717, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2716.89, -1920.46, 190.827, 5.94664, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2773.71, -1866.05, 192.581, 2.69902, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2747.84, -1791.39, 212.249, 3.28414, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2736.13, -1778.34, 212.164, 4.0499, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2717.77, -1763.15, 219.899, 3.82607, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2699.04, -1758.91, 210.098, 4.36799, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2633.77, -1764.82, 182.786, 4.75283, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2626.85, -1782.75, 184.096, 3.60222, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2643.08, -1791.04, 188.089, 5.22013, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2651.27, -1804.49, 188.153, 5.18479, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2629.97, -1830.05, 180.95, 5.55, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2606.47, -1847.86, 167.844, 0.869032, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2613.49, -1829.86, 175.412, 0.240713, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2620.53, -1857.82, 181.967, 0.0129528, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2632.52, -1879.05, 181.653, 4.67037, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2647.68, -1866.75, 187.873, 0.264284, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2656.02, -1882.18, 191.859, 1.00256, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2679.31, -1890.62, 189.921, 3.88105, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2688.71, -1900.93, 190.406, 4.10096, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2701.31, -1910.25, 188.461, 4.35621, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2776.46, -1910.53, 192.365, 5.56965, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2796.24, -1899.22, 193.092, 5.03166, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2711.93, -1823.56, 195.511, 3.81429, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2693.48, -1813.54, 193.765, 4.03813, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2686.96, -1798.18, 194.631, 4.4269, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2673.27, -1814.75, 192.589, 4.81959, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2657.37, -1850.4, 186.829, 5.82489, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2669.45, -1859.52, 187.908, 5.96626, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2683.24, -1872.45, 193.294, 3.03281, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2689.8, -1862.06, 193.299, 2.05106, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2711.03, -1846.09, 194.896, 2.40056, 300, 0, 0, 126, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34390, 1, 1, 2, 0, 0, 2731.45, -1854.91, 195.283, 0.931876, 300, 0, 0, 126, 0, 0, 0, 0, 0);
DELETE FROM `creature` WHERE (`id`='32850');
INSERT INTO `creature` VALUES (null, 32850, 1, 1, 2, 0, 0, 2683.33, -1836.39, 192.039, 4.48621, 300, 0, 0, 74, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 32850, 1, 1, 2, 0, 0, 2656.43, -1831.61, 185.753, 5.55435, 300, 0, 0, 74, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 32850, 1, 1, 2, 0, 0, 2631.2, -1849.02, 182.564, 6.0295, 300, 0, 0, 74, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 32850, 1, 1, 2, 0, 0, 2634.55, -1804.32, 186.443, 5.13928, 300, 0, 0, 74, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 32850, 1, 1, 2, 0, 0, 2663.61, -1794.51, 191.184, 4.75126, 300, 0, 0, 74, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 32850, 1, 1, 2, 0, 0, 2717.72, -1801.35, 204.48, 3.83627, 300, 0, 0, 74, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 32850, 1, 1, 2, 0, 0, 2688.67, -1779.1, 205.926, 4.37033, 300, 0, 0, 74, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 32850, 1, 1, 2, 0, 0, 2746.67, -1823.71, 201.565, 3.40037, 300, 0, 0, 74, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 32850, 1, 1, 2, 0, 0, 2735.73, -1932.25, 176.407, 1.48007, 300, 0, 0, 74, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 32850, 1, 1, 2, 0, 0, 2741.38, -1904.13, 185.872, 1.29158, 300, 0, 0, 74, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 32850, 1, 1, 2, 0, 0, 2750.6, -1859.93, 193.966, 2.36132, 300, 0, 0, 74, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 32850, 1, 1, 2, 0, 0, 2649, -1773.14, 189.23, 4.73322, 300, 0, 0, 74, 0, 0, 0, 0, 0);

-- Quest 13921 He Who Would Be Forgiven
UPDATE `creature_template_addon` SET `auras`=NULL WHERE (`entry`='34335');

-- Quest 13922 In the Hands of the Perverse
DELETE FROM `creature_loot_template` WHERE (`entry`='3758') AND (`item`='5508');
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES ('3758', '5508', '-47');
DELETE FROM `creature_loot_template` WHERE (`entry`='3759') AND (`item`='5508');
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES ('3759', '5508', '-47');
DELETE FROM `creature_loot_template` WHERE (`entry`='3762') AND (`item`='5508');
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES ('3762', '5508', '-40');
DELETE FROM `creature_loot_template` WHERE (`entry`='3763') AND (`item`='5508');
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES ('3763', '5508', '-38');

-- Quest 13924 All's Well
DELETE FROM `creature` WHERE (`id`='34358');
INSERT INTO `creature` VALUES (null, 34358, 1, 1, 1, 0, 0, 2376.1, -1700.24, 151.275, 0.945871, 300, 0, 0, 562, 0, 0, 0, 0, 0);

-- Quest 26476 Dryad Delivery CHAIN TIMELINE FIX
UPDATE `quest_template` SET `NextQuestIdChain`='26477' WHERE (`Id`='26476');
UPDATE `quest_template` SET `NextQuestIdChain`='26478' WHERE (`Id`='26477');
UPDATE `quest_template` SET `NextQuestIdChain`='26479' WHERE (`Id`='26478');
UPDATE `quest_template` SET `NextQuestIdChain`='26480' WHERE (`Id`='26479');
UPDATE `quest_template` SET `NextQuestIdChain`='13989' WHERE (`Id`='26480');
UPDATE `quest_template` SET `NextQuestIdChain`='26481' WHERE (`Id`='13989');
UPDATE `quest_template` SET `NextQuestIdChain`='26482' WHERE (`Id`='26481');
UPDATE `quest_template` SET `PrevQuestId`='26476' WHERE (`Id`='26477');
UPDATE `quest_template` SET `PrevQuestId`='26477' WHERE (`Id`='26478');
UPDATE `quest_template` SET `PrevQuestId`='26478' WHERE (`Id`='26479');
UPDATE `quest_template` SET `PrevQuestId`='26479' WHERE (`Id`='26480');
UPDATE `quest_template` SET `PrevQuestId`='26480' WHERE (`Id`='13989');
UPDATE `quest_template` SET `PrevQuestId`='13989' WHERE (`Id`='26481');
UPDATE `quest_template` SET `PrevQuestId`='26481' WHERE (`Id`='26482');

-- Quest 13868 Corrupting Influence? CHAIN TIMELINE FIX
UPDATE `quest_template` SET `NextQuestIdChain`='13872' WHERE (`Id`='13868');
UPDATE `quest_template` SET `NextQuestIdChain`='13874' WHERE (`Id`='13872');
UPDATE `quest_template` SET `NextQuestIdChain`='13877' WHERE (`Id`='13874');
UPDATE `quest_template` SET `PrevQuestId`='13868' WHERE (`Id`='13872');
UPDATE `quest_template` SET `PrevQuestId`='13872' WHERE (`Id`='13874');
UPDATE `quest_template` SET `PrevQuestId`='13874' WHERE (`Id`='13877');

-- Quest 13868 Corrupting Influence?
DELETE FROM `creature_loot_template` WHERE (`entry`='3925') AND (`item`='46128');
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES ('3925', '46128', '7');
DELETE FROM `creature_loot_template` WHERE (`entry`='3924') AND (`item`='46128');
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES ('3924', '46128', '7');
DELETE FROM `creature_loot_template` WHERE (`entry`='3926') AND (`item`='46128');
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES ('3926', '46128', '4');
DELETE FROM `creature_loot_template` WHERE (`entry`='3921') AND (`item`='46128');
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES ('3921', '46128', '0.3');
DELETE FROM `creature_loot_template` WHERE (`entry`='3922') AND (`item`='46128');
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES ('3922', '46128', '0.3');

-- Quest 25621 Field Test: Gnomecorder CHAIN TIMELINE FIX
UPDATE `quest_template` SET `NextQuestIdChain`='25622' WHERE (`Id`='25621');
UPDATE `quest_template` SET `NextQuestIdChain`='25640' WHERE (`Id`='25622');
UPDATE `quest_template` SET `NextQuestIdChain`='25642' WHERE (`Id`='25640');
UPDATE `quest_template` SET `PrevQuestId`='25621' WHERE (`Id`='25622');
UPDATE `quest_template` SET `PrevQuestId`='25622' WHERE (`Id`='25640');
UPDATE `quest_template` SET `PrevQuestId`='25640' WHERE (`Id`='25642');
UPDATE `quest_template` SET `RewardSpell`='0', `RewardSpellCast`='0' WHERE (`Id`='25621');

-- Quest 25607 Ze Gnomecorder
DELETE FROM `creature_loot_template` WHERE (`entry`='34590') AND (`item`='55144');
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES ('34590', '55144', '-55');
UPDATE `creature_template` SET `lootid`='34590' WHERE (`entry`='34590');

-- Quest 25729 Gerenzo the Traitor
UPDATE `quest_template` SET `Flags`='0' WHERE (`Id`='25729');

-- Quest 25621 Field Test: Gnomecorder
UPDATE `quest_template` SET `Flags`='0' WHERE (`Id`='25621');

-- Quest 25622 Burn, Baby, Burn!
UPDATE `creature_template` SET `unit_flags`='0' WHERE (`entry`='40957');
UPDATE `creature_template` SET `faction_A`='14' WHERE (`entry`='40957');

-- Quest 25642 Don't Look Them in the Eyes
UPDATE `gameobject_template` SET `faction`='35' WHERE (`entry`='203132');
UPDATE `gameobject_template` SET `data7`='203132', `data8`='25642' WHERE (`entry`='203132');
DELETE FROM `creature` WHERE (`id`='40995');
DELETE FROM `gameobject` WHERE (`id`='203132');
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 1003.15, -416.086, 2.51121, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 1001.99, -417.802, 2.76878, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 1000.86, -419.256, 2.99937, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 1003.19, -416.098, 2.42860, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 1002.03, -417.783, 2.68617, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 1000.90, -419.238, 2.91676, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 1001.29, -420.328, 2.05823, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 1001.83, -420.450, 1.88753, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 1002.27, -421.274, 1.68936, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 1002.53, -419.845, 1.72701, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 1002.83, -421.033, 1.54252, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 1003.14, -420.241, 1.51463, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 1002.03, -417.785, 2.68617, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 967.785, -290.036, -0.0013, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 940.273, -290.694, 18.2565, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 893.718, -265.415, 6.86104, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 921.793, -271.167, -0.5481, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 914.982, -272.469, 0.28229, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 930.254, -287.313, -0.2840, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 902.799, -279.041, 2.14672, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 932.728, -294.283, 0.00041, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 875.768, -276.663, 6.88413, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 978.868, -334.610, -1.0146, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 977.701, -330.210, -1.0673, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 962.135, -329.082, 22.2063, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 970.529, -359.477, 16.5573, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 925.328, -318.735, 18.6633, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 977.436, -336.905, -0.9475, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 928.679, -339.615, 19.9513, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 966.123, -343.870, 0.57411, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 904.672, -337.098, 19.6061, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 902.820, -333.112, 19.0656, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 883.935, -290.037, 8.91921, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 957.572, -359.061, 6.28384, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 989.443, -328.820, 0.53512, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 1011.33, -388.211, 5.99155, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 994.401, -353.363, 12.6808, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 981.432, -401.479, 9.36357, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);
INSERT INTO `gameobject` VALUES (null, 203132, 1, 1, 1, 977.494, -359.710, 16.8392, 4.97864, 0, 0, 0.606996, -0.794705, 300, 0, 1);

-- Quest 13642 Bathed in Light
DELETE FROM `creature_template` WHERE (`entry`='341231');
INSERT INTO `creature_template` VALUES (341231, 0, 0, 0, 0, 0, 1126, 15880, 0, 0, 'Bathed in Light Bunny', '', '', 0, 1, 1, 0, 0, 35, 35, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 33555200, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 1024, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 3, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, '', 15595);
DELETE FROM `creature_template_addon` WHERE (`entry`='341231');
INSERT INTO `creature_template_addon` VALUES (341231, 0, 0, 65536, 1, 0, '64573 52855');
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE (`entry`='341231');
DELETE FROM `smart_scripts` WHERE (`entryorguid`='341231');
INSERT INTO `smart_scripts` VALUES (341231, 0, 1, 2, 8, 0, 100, 0, 63578, 0, 0, 0, 56, 45066, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '');
DELETE FROM `item_template` WHERE (`entry`='45065');
INSERT INTO `item_template` (`entry`, `class`, `name`, `displayid`, `Quality`, `Flags`, `FlagsExtra`, `spellid_1`, `spellcooldown_1`, `bonding`, `Material`) VALUES ('45065', '12', 'Unbathed Concoction', '15718', '1', '8388672', '8192', '63578', '1000', '4', '1');
DELETE FROM `creature` WHERE (`id`='341231');
INSERT INTO `creature` VALUES (null, 341231, 1, 1, 1, 0, 0, 3073.09, 610.489, 5.43727, 1.80431, 300, 0, 0, 42, 0, 0, 0, 0, 0);

-- Quest 26838 Rebels Without a Clue CHAIN TIMELINE FIX
UPDATE `quest_template` SET `NextQuestIdChain`='26735' WHERE (`Id`='26838');
UPDATE `quest_template` SET `NextQuestIdChain`='26735' WHERE (`Id`='28699');
UPDATE `quest_template` SET `NextQuestIdChain`='26736' WHERE (`Id`='26735');
UPDATE `quest_template` SET `NextQuestIdChain`='26737' WHERE (`Id`='26736');
UPDATE `quest_template` SET `PrevQuestId`='26838' WHERE (`Id`='26735');
UPDATE `quest_template` SET `PrevQuestId`='26735' WHERE (`Id`='26736');
UPDATE `quest_template` SET `PrevQuestId`='26736' WHERE (`Id`='26737');

-- Quest 13913 They Took Our Gnomes
DELETE FROM `creature_questrelation` WHERE (`id`='34354') AND (`quest`='13913');

-- Quest 13987 The Last Stand
UPDATE `quest_template` SET `StartScript`='13987', `CompleteScript`='13987' WHERE (`Id`='13987');
DELETE FROM `quest_start_scripts` WHERE (`id`='13987');
INSERT INTO `quest_start_scripts` (`id`, `command`, `datalong`, `datalong2`) VALUES ('13987', '15', '65396', '2');
DELETE FROM `quest_end_scripts` WHERE (`id`='13987');
INSERT INTO `quest_end_scripts` (`id`, `command`, `datalong`) VALUES ('13987', '14', '65396');
DELETE FROM `creature_template` WHERE (`entry`='346040');
INSERT INTO `creature_template` VALUES (346040, 0, 0, 0, 0, 0, 1461, 0, 0, 0, 'Big Baobob', 'Ancient of War', '', 10541, 40, 40, 0, 0, 1934, 1934, 3, 1, 1.14286, 1, 1, 0, 0, 0, 0, 1, 2000, 2000, 1, 33024, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 266280, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 8, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, '', 15595);
DELETE FROM `creature` WHERE (`id`='346040');
INSERT INTO `creature` VALUES (null, 346040, 1, 1, 2, 0, 0, 2640.52, 418.394, 74.3014, 5.63741, 120, 0, 0, 1, 0, 0, 0, 0, 0);
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE (`entry`='346040');
UPDATE `creature_template` SET `gossip_menu_id`='34604' WHERE (`entry`='346040');
delete from gossip_menu_option where menu_id = 34604;
insert into gossip_menu_option (menu_id,id,option_text,option_id,npc_option_npcflag) values
(34604,0,"OK, I'm ready to return",1,1);
DELETE FROM smart_scripts WHERE entryorguid IN (346040) AND source_type = 0;
INSERT INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, COMMENT) VALUES
(346040,0,1,2,62,0,100,0,34604,0,0,0,28,65396,0,0,0,0,0,7,0,0,0,0,0,0,0,"Remove aura"),
(346040,0,2,5,61,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0,"Chiude gossip"),
(346040,0,5,0,61,0,100,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Frase");
update smart_scripts set event_flags = 0 WHERE entryorguid IN (346040) AND source_type = 0;
-- Spawn NPC quest on phase 2
DELETE FROM `creature` WHERE (`id`='34609');
INSERT INTO `creature` VALUES (null, 34609, 1, 1, 2, 0, 0, 2665.96, 392.407, 71.2598, 2.40933, 300, 0, 0, 272, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34609, 1, 1, 2, 0, 0, 2667.99, 348.911, 67.2598, 1.95615, 300, 0, 0, 293, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34609, 1, 1, 2, 0, 0, 2702.78, 374.462, 67.6121, 2.4641, 300, 0, 0, 293, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34609, 1, 1, 2, 0, 0, 2710.81, 414.604, 68.2686, 3.21808, 300, 0, 0, 315, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34609, 1, 1, 2, 0, 0, 2706.86, 458.714, 68.1568, 3.90138, 300, 0, 0, 315, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34609, 1, 1, 2, 0, 0, 2680.16, 442.043, 65.4598, 3.86996, 300, 0, 0, 272, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34609, 1, 1, 2, 0, 0, 2648.04, 468.295, 65.4804, 4.76531, 300, 0, 0, 272, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34609, 1, 1, 2, 0, 0, 2623.91, 479.976, 67.4294, 4.9106, 300, 0, 0, 293, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34609, 1, 1, 2, 0, 0, 2667.28, 478.334, 66.7565, 4.14877, 300, 0, 0, 272, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34609, 1, 1, 2, 0, 0, 2686.48, 466.197, 66.7615, 4.14877, 300, 0, 0, 272, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34609, 1, 1, 2, 0, 0, 2699.47, 435.114, 66.7972, 3.55579, 300, 0, 0, 293, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34609, 1, 1, 2, 0, 0, 2586.17, 423.677, 66.9574, 5.91374, 300, 0, 0, 315, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34609, 1, 1, 2, 0, 0, 2589.13, 406.631, 68.3744, 0.741889, 300, 0, 0, 315, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34609, 1, 1, 2, 0, 0, 2608.61, 388.375, 68.0022, 0.843991, 300, 0, 0, 272, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34609, 1, 1, 2, 0, 0, 2617.95, 368.853, 68.457, 0.580883, 300, 0, 0, 272, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34609, 1, 1, 2, 0, 0, 2632.84, 358.622, 68.6316, 1.46446, 300, 0, 0, 293, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34609, 1, 1, 2, 0, 0, 2651.12, 351.35, 68.2295, 1.66473, 300, 0, 0, 272, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34609, 1, 1, 2, 0, 0, 2671.48, 350.734, 67.147, 1.95926, 300, 0, 0, 315, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34609, 1, 1, 2, 0, 0, 2691.89, 359.285, 66.9666, 2.04958, 300, 0, 0, 315, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34609, 1, 1, 2, 0, 0, 2702.74, 381.19, 67.1757, 2.42657, 300, 0, 0, 293, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34609, 1, 1, 2, 0, 0, 2656.39, 445.046, 70.0883, 4.7121, 300, 0, 0, 272, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34609, 1, 1, 2, 0, 0, 2645.54, 424.05, 73.6091, 4.31841, 300, 0, 0, 293, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34609, 1, 1, 2, 0, 0, 2642.26, 439.689, 73.92, 4.41291, 300, 0, 0, 293, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34609, 1, 1, 2, 0, 0, 2617.13, 454.057, 72.5323, 4.93941, 300, 0, 0, 293, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34609, 1, 1, 2, 0, 0, 2607.98, 437.12, 72.1313, 5.82366, 300, 0, 0, 272, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34609, 1, 1, 2, 0, 0, 2610.76, 419.267, 72.2785, 0.110847, 300, 0, 0, 272, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34609, 1, 1, 2, 0, 0, 2630.75, 394.577, 71.9521, 0.735222, 300, 0, 0, 272, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34609, 1, 1, 2, 0, 0, 2645.91, 380.122, 70.9069, 1.7061, 300, 0, 0, 315, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34609, 1, 1, 2, 0, 0, 2660.69, 379.899, 69.8366, 2.11785, 300, 0, 0, 293, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34609, 1, 1, 2, 0, 0, 2679.34, 380.063, 68.1764, 2.7546, 300, 0, 0, 315, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34609, 1, 1, 2, 0, 0, 2690.18, 396.245, 66.2278, 2.58697, 300, 0, 0, 272, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34609, 1, 1, 2, 0, 0, 2694.28, 406.717, 65.6217, 3.29685, 300, 0, 0, 272, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34609, 1, 1, 2, 0, 0, 2672.78, 423.296, 71.4123, 4.29822, 300, 0, 0, 315, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (null, 34609, 1, 1, 2, 0, 0, 2679.05, 410.202, 70.9405, 3.39502, 300, 0, 0, 272, 0, 0, 0, 0, 0);














