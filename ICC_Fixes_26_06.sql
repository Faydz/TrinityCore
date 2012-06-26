-- Trash droppt Embleme:
Delete from `creature_loot_template` where `entry` = 100002;
INSERT INTO `creature_loot_template` VALUES (100002, 1, 100, 1, 0, -35069, 2);
-- INSERT INTO `creature_loot_template` VALUES (100002, 49426, 100, 1, 0, 1, 1);

-- Schatz Schleife
Delete from `creature_loot_template` where `entry` = 37217;
INSERT INTO `creature_loot_template` VALUES (37217, 52019, 1.0, 1, 0, 1, 1);
-- INSERT INTO `creature_loot_template` VALUES (37217, 1, 100, 1, 0, -35069, 2);

-- Schwester Svalna
INSERT INTO `creature_loot_template` VALUES (100002, 49426, 100, 1, 0, 1, 1);

-- Blutrat
Update `creature_template` set `speed_walk` = 0.6 where `entry` = 38454; -- Old 0.8
Update `creature_template` set `speed_walk` = 0.6 where `entry` = 38775; -- Old 0.8
Update `creature_template` set `speed_walk` = 0.6 where `entry` = 38776; -- Old 0.8
Update `creature_template` set `speed_walk` = 0.6 where `entry` = 38777; -- Old 0.8

-- Fraktionsübergreifendes Raiden Changes
Update `creature_template` set `faction_A` = 35, `faction_H` = 35 where `entry` = 38454; -- Old 83
Update `creature_template` set `faction_A` = 35, `faction_H` = 35 where `entry` = 37028; -- Old 83
Update `creature_template` set `faction_A` = 35, `faction_H` = 35 where `entry` = 37030; -- Old 83
Update `creature_template` set `faction_A` = 35, `faction_H` = 35 where `entry` = 37031; -- Old 83
Update `creature_template` set `faction_A` = 35, `faction_H` = 35 where `entry` = 37032; -- Old 83
Update `creature_template` set `faction_A` = 35, `faction_H` = 35 where `entry` = 37033; -- Old 83
Update `creature_template` set `faction_A` = 35, `faction_H` = 35 where `entry` = 37146; -- Old 83

Update `creature_template` set `faction_A` = 35, `faction_H` = 35 where `entry` = 37017; -- Old 84
Update `creature_template` set `faction_A` = 35, `faction_H` = 35 where `entry` = 36998; -- Old 84
Update `creature_template` set `faction_A` = 35, `faction_H` = 35 where `entry` = 37144; -- Old 84
Update `creature_template` set `faction_A` = 35, `faction_H` = 35 where `entry` = 37027; -- Old 84
Update `creature_template` set `faction_A` = 35, `faction_H` = 35 where `entry` = 37021; -- Old 84
Update `creature_template` set `faction_A` = 35, `faction_H` = 35 where `entry` = 37004; -- Old 84
Update `creature_template` set `faction_A` = 35, `faction_H` = 35 where `entry` = 37026; -- Old 84
Update `creature_template` set `faction_A` = 35, `faction_H` = 35 where `entry` = 37016; -- Old 84

Update `creature_template` set `faction_A` = 35, `faction_H` = 35 where `entry` = 37830; -- Old 1732
Update `creature_template` set `faction_A` = 35, `faction_H` = 35 where `entry` = 37200; -- Old 1732
Update `creature_template` set `faction_A` = 35, `faction_H` = 35 where `entry` = 37190; -- Old 1732
Update `creature_template` set `faction_A` = 35, `faction_H` = 35 where `entry` = 37189; -- Old 2073
Update `creature_template` set `faction_A` = 35, `faction_H` = 35 where `entry` = 37187; -- Old 1735
Update `creature_template` set `faction_A` = 35, `faction_H` = 35 where `entry` = 37967; -- Old 2050
Update `creature_template` set `faction_A` = 35, `faction_H` = 35 where `entry` = 37965; -- Old 2121
Update `creature_template` set `faction_A` = 35, `faction_H` = 35 where `entry` = 37696; -- Old 2070
Update `creature_template` set `faction_A` = 35, `faction_H` = 35 where `entry` = 37119; -- Old 2073
Update `creature_template` set `faction_A` = 35, `faction_H` = 35 where `entry` = 37928; -- Old 2131
Update `creature_template` set `faction_A` = 35, `faction_H` = 35 where `entry` = 37996; -- Old 2144
Update `creature_template` set `faction_A` = 35, `faction_H` = 35 where `entry` = 37688; -- Old 2070
Update `creature_template` set `faction_A` = 35, `faction_H` = 35 where `entry` = 37920; -- Old 1735