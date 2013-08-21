-- Base script for summoning and stuff
DELETE FROM spell_script_names WHERE spell_id in(86150, 86698);
INSERT INTO `spell_script_names` VALUES (86150, 'spell_pal_guardian_of_ancient_kings');
INSERT INTO `spell_script_names` VALUES (86698, 'spell_pal_guardian_of_ancient_kings_retri');

-- Creature template scripting
DELETE FROM creature_template WHERE entry in(46499, 46490, 46506);
INSERT INTO `creature_template` VALUES (46490, 0, 0, 0, 0, 0, 35107, 0, 0, 0, 'Guardian of Ancient Kings', '', '', 0, 1, 1, 0, 0, 35, 35, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 48, 1, 0, 0, 'guard_guardian_of_ancient_kings', 15595);
INSERT INTO `creature_template` VALUES (46499, 0, 0, 0, 0, 0, 35572, 0, 0, 0, 'Guardian of Ancient Kings', '', '', 0, 1, 1, 0, 0, 35, 35, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 48, 1, 0, 0, 'guard_guardian_of_ancient_kings', 15595);
INSERT INTO `creature_template` VALUES (46506, 0, 0, 0, 0, 0, 35573, 0, 0, 0, 'Guardian of Ancient Kings', '', '', 0, 1, 1, 0, 0, 35, 35, 0, 1, 1.14286, 1, 0, 766, 1149, 0, 0, 1, 0, 0, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 48, 1, 0, 0, 'guard_guardian_of_ancient_kings', 15595);

-- Guardian's equip
DELETE FROM creature_equip_template WHERE entry in(46499, 46490, 46506);
INSERT INTO `creature_equip_template` VALUES (46499, 1, 46017, 47079, 0);
INSERT INTO `creature_equip_template` VALUES (46490, 1, 47526, 46963, 0);
INSERT INTO `creature_equip_template` VALUES (46506, 1, 47515, 0, 0);
