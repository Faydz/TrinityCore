-- Elemental focus(shaman talent) correct proc.
DELETE FROM spell_proc_event WHERE entry = 16164;
INSERT INTO spell_proc_event (entry, SchoolMask, SpellFamilyName, SpellFamilyMask0, SpellFamilyMask1, SpellFamilyMask2, procFlags, procEx, ppmRate, CustomChance, Cooldown) VALUES (16164, 0, 11, 2416967683, 4096, 0, 0, 2, 0, 0, 0);

-- Fix Dancing Rune Weapon.
DELETE FROM `spell_proc_event` where `entry` = 49028;
INSERT INTO `spell_proc_event` (entry, procFlags) VALUES
('49028','69652');

-- Fix Lifebloom.
DELETE FROM spell_bonus_data WHERE entry = 33778;
DELETE FROM spell_bonus_data WHERE entry = 33763;
INSERT INTO spell_bonus_data (entry, direct_bonus, dot_bonus, ap_bonus, ap_dot_bonus, comments) VALUES
(33778, 0, 0, 0, 0, 'Druid - Lifebloom final heal'),
(33763, 0.516, 0.0952, 0, 0, 'Druid - Lifebloom HoT(rank 1)');

-- King of the jungle and tiger's fury 
UPDATE spell_proc_event SET procFlags = 1024 WHERE entry in (48492,48494,48495);