-- update immunity
UPDATE `creature_template` set `mechanic_immune_mask` = 617299803 where entry IN ('36612', '37957', '37958', '37959'); -- Lod Mark'gar
UPDATE `creature_template` set `mechanic_immune_mask` = 617299803 where entry IN ('36855', '38106', '38296', '38297'); -- Lady Deathwhisper
UPDATE `creature_template` set `mechanic_immune_mask` = 617299803 where entry IN ('37813', '38402', '38582', '38583'); -- Deathbringer Saurfang
UPDATE `creature_template` set `mechanic_immune_mask` = 617299803 where entry IN ('36627', '38390', '38549', '38550'); -- Rotface
UPDATE `creature_template` set `mechanic_immune_mask` = 617299803 where entry IN ('36626', '37504', '37505', '37506'); -- Festergut
UPDATE `creature_template` set `mechanic_immune_mask` = 617299803 where entry IN ('36678', '38431', '38585', '38586'); -- Professor Putricide
UPDATE `creature_template` set `mechanic_immune_mask` = 617299803 where entry IN ('37562', '38602', '38760', '38761'); -- Gas Cloud
UPDATE `creature_template` set `mechanic_immune_mask` = 617299803 where entry IN ('37697', '38604', '38758', '38759'); -- Volatile Ooze
UPDATE `creature_template` SET `mechanic_immune_mask` = 617299803 where entry IN ('36980', '38320', '38321', '38322'); -- Ice Tombs / Sindragosa

-- Rotface:
-- remove conditions (target selection changed from TARGET_UNIT_NEARBY_ENTRY to TARGET_UNIT_TARGET_ANY so doesn't need it anymore)
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry`=69508;
/* backup data
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(13, 0, 69508, 0, 0, 18, 0, 1, 37986, 0, 0, 0, '', 'Rotface - Slime Spray');
*/

-- Add script
DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_rotface_slime_spray';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(69507, 'spell_rotface_slime_spray'),
(71213, 'spell_rotface_slime_spray'),
(73189, 'spell_rotface_slime_spray'),
(73190, 'spell_rotface_slime_spray');

-- Sindragosa:
-- Fix spell 69762 Unchained Magic 
-- Add internal cooldown with 1 seconds, so multi-spell spells will only apply one stack of triggered spell 69766 (i.e. Chain Heal)
DELETE FROM `spell_proc_event` WHERE `entry` = 69762;
INSERT INTO `spell_proc_event` (entry, SchoolMask, SpellFamilyName, SpellFamilyMask0, SpellFamilyMask1, SpellFamilyMask2, procFlags, procEx, ppmRate, CustomChance, Cooldown) VALUES
(69762, 0, 0, 0, 0, 0, 81920, 0, 0, 0, 1);