DELETE FROM `spell_proc_event` WHERE `entry`=84617;
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES 
(84617, 1, 8, 4063232, 8, 0, 8736, 0, 0, 101, 0);
DELETE FROM `spell_script_names` WHERE `spell_id` = 1943;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (1943, 'spell_rog_rupture');