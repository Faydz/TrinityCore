-- Armor Debuff (Minor)
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=91565 AND `spell_effect` = -95467;
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (91565, -95467, 1, 'Faerie Fire - Tear Armor');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=95467 AND `spell_effect` = -91565;
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (95467, -91565, 1, 'Tear Armor - Faerie Fire');

-- Physical Damage Debuff
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=58684 AND `spell_effect` IN (-30069, -30070, -81325, -81326);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (58684, -30069, 1, 'Savage Combat (rank 1) - Blood Frenzy (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (58684, -30070, 1, 'Savage Combat (rank 1) - Blood Frenzy (rank 2)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (58684, -81325, 1, 'Savage Combat (rank 1) - Brittle bones (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (58684, -81326, 1, 'Savage Combat (rank 1) - Brittle bones (rank 2)');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=58683 AND `spell_effect` IN (-30069, -30070, -81325, -81326);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (58683, -30069, 1, 'Savage Combat (rank 2) - Blood Frenzy (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (58683, -30070, 1, 'Savage Combat (rank 2) - Blood Frenzy (rank 2)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (58683, -81325, 1, 'Savage Combat (rank 2) - Brittle bones (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (58683, -81326, 1, 'Savage Combat (rank 2) - Brittle bones (rank 2)');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=30069 AND `spell_effect` IN (-58684, -58683, -81325, -81326);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (30069, -58684, 1, 'Blood Frenzy (rank 1) - Savage Combat (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (30069, -58683, 1, 'Blood Frenzy (rank 1) - Savage Combat (rank 2)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (30069, -81325, 1, 'Blood Frenzy (rank 1) - Brittle bones (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (30069, -81326, 1, 'Blood Frenzy (rank 1) - Brittle bones (rank 2)');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=30070 AND `spell_effect` IN (-58684, -58683, -81325, -81326);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (30070, -58684, 1, 'Blood Frenzy (rank 2) - Savage Combat (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (30070, -58683, 1, 'Blood Frenzy (rank 2) - Savage Combat (rank 2)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (30070, -81325, 1, 'Blood Frenzy (rank 2) - Brittle bones (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (30070, -81326, 1, 'Blood Frenzy (rank 2) - Brittle bones (rank 2)');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=81325 AND `spell_effect` IN (-30069, -30070, -58684, -58683);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (81325, -30069, 1, 'Brittle bones (rank 1) - Blood Frenzy (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (81325, -30070, 1, 'Brittle bones (rank 1) - Blood Frenzy (rank 2)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (81325, -58684, 1, 'Brittle bones (rank 1) - Savage Combat (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (81325, -58683, 1, 'Brittle bones (rank 1) - Savage Combat (rank 2)');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=81326 AND `spell_effect` IN (-30069, -30070, -58684, -58683);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (81326, -30069, 1, 'Brittle bones (rank 2) - Blood Frenzy (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (81326, -30070, 1, 'Brittle bones (rank 2) - Blood Frenzy (rank 2)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (81326, -58684, 1, 'Brittle bones (rank 2) - Savage Combat (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (81326, -58683, 1, 'Brittle bones (rank 2) - Savage Combat (rank 2)');

-- Bleed Damage Debuff
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=16511 AND `spell_effect` IN (-33876, -33878, -46857);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (16511, -33876, 1, 'Hemorrhage - Mangle (cat form)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (16511, -33878, 1, 'Hemorrhage - Mangle (bear form)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (16511, -46857, 1, 'Hemorrhage - Trauma');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=33876 AND `spell_effect` IN (-16511, -33878, -46857);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (33876, -16511, 1, 'Mangle (cat form) - Hemorrhage');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (33876, -33878, 1, 'Mangle (cat form) - Mangle (bear form)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (33876, -46857, 1, 'Mangle (cat form) - Trauma');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=33878 AND `spell_effect` IN (-16511, -33876, -46857);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (33878, -16511, 1, 'Mangle (bear form) - Hemorrhage');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (33878, -33876, 1, 'Mangle (bear form) - Mangle (cat form)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (33878, -46857, 1, 'Mangle (bear form) - Trauma');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=46857 AND `spell_effect` IN (-16511, -33876, -33878);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (46857, -16511, 1, 'Trauma - Hemorrhage');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (46857, -33876, 1, 'Trauma - Mangle (cat form)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (46857, -33878, 1, 'Trauma - Mangle (bear form)');