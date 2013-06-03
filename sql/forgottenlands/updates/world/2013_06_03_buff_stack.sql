-- Attack Power Buff (Multiplier)
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=53137 AND `spell_effect` IN (-19506, -30802, -30808, -79102);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (53137, -19506, 2, 'Abomination\'s Might (rank 1) - Trueshot Aura');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (53137, -30802, 2, 'Abomination\'s Might (rank 1) - Unleashed Rage (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (53137, -30808, 2, 'Abomination\'s Might (rank 1) - Unleashed Rage (rank 2)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (53137, -79102, 2, 'Abomination\'s Might (rank 1) - Blessing of Might');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=53138 AND `spell_effect` IN (-19506, -30802, -30808, -79102);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (53138, -19506, 2, 'Abomination\'s Might (rank 2) - Trueshot Aura');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (53138, -30802, 2, 'Abomination\'s Might (rank 2) - Unleashed Rage (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (53138, -30808, 2, 'Abomination\'s Might (rank 2) - Unleashed Rage (rank 2)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (53138, -79102, 2, 'Abomination\'s Might (rank 2) - Blessing of Might');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=19506 AND `spell_effect` IN (-53137, -53138, -30802, -30808, -79102);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (19506, -53137, 2, 'Trueshot Aura - Abomination\'s Might (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (19506, -53138, 2, 'Trueshot Aura - Abomination\'s Might (rank 2)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (19506, -30802, 2, 'Trueshot Aura - Unleashed Rage (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (19506, -30808, 2, 'Trueshot Aura - Unleashed Rage (rank 2)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (19506, -79102, 2, 'Trueshot Aura - Blessing of Might');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=30802 AND `spell_effect` IN (-53137, -53138, -19506, -79102);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (30802, -53137, 2, 'Unleashed Rage (rank 1) - Abomination\'s Might (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (30802, -53138, 2, 'Unleashed Rage (rank 1) - Abomination\'s Might (rank 2)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (30802, -19506, 2, 'Unleashed Rage (rank 1) - Trueshot Aura');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (30802, -79102, 2, 'Unleashed Rage (rank 1) - Blessing of Might');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=30808 AND `spell_effect` IN (-53137, -53138, -19506, -79102);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (30808, -53137, 2, 'Unleashed Rage (rank 2) - Abomination\'s Might (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (30808, -53138, 2, 'Unleashed Rage (rank 2) - Abomination\'s Might (rank 2)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (30808, -19506, 2, 'Unleashed Rage (rank 2) - Trueshot Aura');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (30808, -79102, 2, 'Unleashed Rage (rank 2) - Blessing of Might');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=79102 AND `spell_effect` IN (-53137, -53138, -19506, -30802, -30808);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (79102, -53137, 2, 'Blessing of Might - Abomination\'s Might (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (79102, -53138, 2, 'Blessing of Might - Abomination\'s Might (rank 2)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (79102, -19506, 2, 'Blessing of Might - Trueshot Aura');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (79102, -30802, 2, 'Blessing of Might - Unleashed Rage (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (79102, -30808, 2, 'Blessing of Might - Unleashed Rage (rank 2)');

-- Agility and Strength Buff
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=6673 AND `spell_effect` = -93435;
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (6673, -93435, 2, 'Battle Shout - Roar of Courage');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=93435 AND `spell_effect` = -6673;
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (93435, -6673, 2, 'Roar of Courage - Battle Shout');

-- Armor Debuff (Minor)
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=91565 AND `spell_effect` = -95467;
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (91565, -95467, 2, 'Faerie Fire - Tear Armor');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=95467 AND `spell_effect` = -91565;
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (95467, -91565, 2, 'Tear Armor - Faerie Fire');

-- Physical Damage Debuff
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=58684 AND `spell_effect` IN (-30069, -30070, -81325, -81326);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (58684, -30069, 2, 'Savage Combat (rank 1) - Blood Frenzy (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (58684, -30070, 2, 'Savage Combat (rank 1) - Blood Frenzy (rank 2)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (58684, -81325, 2, 'Savage Combat (rank 1) - Brittle bones (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (58684, -81326, 2, 'Savage Combat (rank 1) - Brittle bones (rank 2)');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=58683 AND `spell_effect` IN (-30069, -30070, -81325, -81326);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (58683, -30069, 2, 'Savage Combat (rank 2) - Blood Frenzy (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (58683, -30070, 2, 'Savage Combat (rank 2) - Blood Frenzy (rank 2)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (58683, -81325, 2, 'Savage Combat (rank 2) - Brittle bones (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (58683, -81326, 2, 'Savage Combat (rank 2) - Brittle bones (rank 2)');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=30069 AND `spell_effect` IN (-58684, -58683, -81325, -81326);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (30069, -58684, 2, 'Blood Frenzy (rank 1) - Savage Combat (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (30069, -58683, 2, 'Blood Frenzy (rank 1) - Savage Combat (rank 2)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (30069, -81325, 2, 'Blood Frenzy (rank 1) - Brittle bones (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (30069, -81326, 2, 'Blood Frenzy (rank 1) - Brittle bones (rank 2)');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=30070 AND `spell_effect` IN (-58684, -58683, -81325, -81326);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (30070, -58684, 2, 'Blood Frenzy (rank 2) - Savage Combat (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (30070, -58683, 2, 'Blood Frenzy (rank 2) - Savage Combat (rank 2)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (30070, -81325, 2, 'Blood Frenzy (rank 2) - Brittle bones (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (30070, -81326, 2, 'Blood Frenzy (rank 2) - Brittle bones (rank 2)');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=81325 AND `spell_effect` IN (-30069, -30070, -58684, -58683);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (81325, -30069, 2, 'Brittle bones (rank 1) - Blood Frenzy (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (81325, -30070, 2, 'Brittle bones (rank 1) - Blood Frenzy (rank 2)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (81325, -58684, 2, 'Brittle bones (rank 1) - Savage Combat (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (81325, -58683, 2, 'Brittle bones (rank 1) - Savage Combat (rank 2)');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=81326 AND `spell_effect` IN (-30069, -30070, -58684, -58683);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (81326, -30069, 2, 'Brittle bones (rank 2) - Blood Frenzy (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (81326, -30070, 2, 'Brittle bones (rank 2) - Blood Frenzy (rank 2)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (81326, -58684, 2, 'Brittle bones (rank 2) - Savage Combat (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (81326, -58683, 2, 'Brittle bones (rank 2) - Savage Combat (rank 2)');

-- Bleed Damage Debuff
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=16511 AND `spell_effect` IN (-33876, -33878, -46857);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (16511, -33876, 2, 'Hemorrhage - Mangle (cat form)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (16511, -33878, 2, 'Hemorrhage - Mangle (bear form)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (16511, -46857, 2, 'Hemorrhage - Trauma');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=33876 AND `spell_effect` IN (-16511, -33878, -46857);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (33876, -16511, 2, 'Mangle (cat form) - Hemorrhage');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (33876, -33878, 2, 'Mangle (cat form) - Mangle (bear form)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (33876, -46857, 2, 'Mangle (cat form) - Trauma');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=33878 AND `spell_effect` IN (-16511, -33876, -46857);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (33878, -16511, 2, 'Mangle (bear form) - Hemorrhage');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (33878, -33876, 2, 'Mangle (bear form) - Mangle (cat form)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (33878, -46857, 2, 'Mangle (bear form) - Trauma');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=46857 AND `spell_effect` IN (-16511, -33876, -33878);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (46857, -16511, 2, 'Trauma - Hemorrhage');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (46857, -33876, 2, 'Trauma - Mangle (cat form)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (46857, -33878, 2, 'Trauma - Mangle (bear form)');

-- Critical Buff
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=24604 AND `spell_effect` IN (-24932, -51698, -51700, -51701, -29801, -51466, -51470);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (24604, -24932, 2, 'Furious Howl - Leader of the Pack');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (24604, -51698, 2, 'Furious Howl - Honor Among Thieves (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (24604, -51700, 2, 'Furious Howl - Honor Among Thieves (rank 2)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (24604, -51701, 2, 'Furious Howl - Honor Among Thieves (rank 3)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (24604, -29801, 2, 'Furious Howl - Rampage');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (24604, -51466, 2, 'Furious Howl - Elemental Oath (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (24604, -51470, 2, 'Furious Howl - Elemental Oath (rank 2)');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=24932 AND `spell_effect` IN (-24604, -51698, -51700, -51701, -29801, -51466, -51470);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (24932, -24604, 2, 'Leader of the Pack - Furious Howl');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (24932, -51698, 2, 'Leader of the Pack - Honor Among Thieves (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (24932, -51700, 2, 'Leader of the Pack - Honor Among Thieves (rank 2)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (24932, -51701, 2, 'Leader of the Pack - Honor Among Thieves (rank 3)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (24932, -29801, 2, 'Leader of the Pack - Rampage');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (24932, -51466, 2, 'Leader of the Pack - Elemental Oath (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (24932, -51470, 2, 'Leader of the Pack - Elemental Oath (rank 2)');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=51698 AND `spell_effect` IN (-24604, -24932, -29801, -51466, -51470);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (51698, -24604, 2, 'Honor Among Thieves (rank 1) - Furious Howl');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (51698, -24932, 2, 'Honor Among Thieves (rank 1) - Leader of the Pack');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (51698, -29801, 2, 'Honor Among Thieves (rank 1) - Rampage');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (51698, -51466, 2, 'Honor Among Thieves (rank 1) - Elemental Oath (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (51698, -51470, 2, 'Honor Among Thieves (rank 1) - Elemental Oath (rank 2)');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=51700 AND `spell_effect` IN (-24604, -24932, -29801, -51466, -51470);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (51700, -24604, 2, 'Honor Among Thieves (rank 2) - Furious Howl');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (51700, -24932, 2, 'Honor Among Thieves (rank 2) - Leader of the Pack');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (51700, -29801, 2, 'Honor Among Thieves (rank 2) - Rampage');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (51700, -51466, 2, 'Honor Among Thieves (rank 2) - Elemental Oath (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (51700, -51470, 2, 'Honor Among Thieves (rank 2) - Elemental Oath (rank 2)');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=51701 AND `spell_effect` IN (-24604, -24932, -29801, -51466, -51470);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (51701, -24604, 2, 'Honor Among Thieves (rank 3) - Furious Howl');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (51701, -24932, 2, 'Honor Among Thieves (rank 3) - Leader of the Pack');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (51701, -29801, 2, 'Honor Among Thieves (rank 3) - Rampage');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (51701, -51466, 2, 'Honor Among Thieves (rank 3) - Elemental Oath (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (51701, -51470, 2, 'Honor Among Thieves (rank 3) - Elemental Oath (rank 2)');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=29801 AND `spell_effect` IN (-24604, -51698, -51700, -51701, -24932, -51466, -51470);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (29801, -24604, 2, 'Rampage - Furious Howl');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (29801, -51698, 2, 'Rampage - Honor Among Thieves (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (29801, -51700, 2, 'Rampage - Honor Among Thieves (rank 2)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (29801, -51701, 2, 'Rampage - Honor Among Thieves (rank 3)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (29801, -24932, 2, 'Rampage - Leader of the Pack');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (29801, -51466, 2, 'Rampage - Elemental Oath (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (29801, -51470, 2, 'Rampage - Elemental Oath (rank 2)');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=51466 AND `spell_effect` IN (-24604, -51698, -51700, -51701, -24932, -29801);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (51466, -24604, 2, 'Elemental Oath (rank 1) - Furious Howl');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (51466, -51698, 2, 'Elemental Oath (rank 1) - Honor Among Thieves (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (51466, -51700, 2, 'Elemental Oath (rank 1) - Honor Among Thieves (rank 2)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (51466, -51701, 2, 'Elemental Oath (rank 1) - Honor Among Thieves (rank 3)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (51466, -24932, 2, 'Elemental Oath (rank 1) - Leader of the Pack');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (51466, -29801, 2, 'Elemental Oath (rank 1) - Rampage');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=51470 AND `spell_effect` IN (-24604, -51698, -51700, -51701, -24932, -29801);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (51470, -24604, 2, 'Elemental Oath (rank 2) - Furious Howl');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (51470, -51698, 2, 'Elemental Oath (rank 2) - Honor Among Thieves (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (51470, -51700, 2, 'Elemental Oath (rank 2) - Honor Among Thieves (rank 2)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (51470, -51701, 2, 'Elemental Oath (rank 2) - Honor Among Thieves (rank 3)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (51470, -24932, 2, 'Elemental Oath (rank 2) - Leader of the Pack');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (51470, -29801, 2, 'Elemental Oath (rank 2) - Rampage');

-- Water walking (ends in combat)
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=3714 AND `spell_effect` IN (-546, -1706);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (3714, -546, 2, 'Path of Frost - Water Walking');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (3714, -1706, 2, 'Path of Frost - Levitate');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=546 AND `spell_effect` IN (-3714, -1706);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (546, -3714, 2, 'Water Walking - Path of Frost');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (546, -1706, 2, 'Water Walking - Levitate');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=1706 AND `spell_effect` IN (-3714, -546);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (1706, -3714, 2, 'Levitate - Path of Frost');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (1706, -546, 2, 'Levitate - Water Walking');

-- Mana
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=54424 AND `spell_effect` IN (-79058);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (54424, -79058, 2, 'Fel Intelligence - Arcane Brilliance');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=79058 AND `spell_effect` IN (-54424);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (79058, -54424, 2, 'Arcane Brilliance - Fel Intelligence');

-- Spell Power buff
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=79058 AND `spell_effect` IN (-52109);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (79058, -52109, 2, 'Arcane Brilliance - Flametongue Totem');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=52109 AND `spell_effect` IN (-79058);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (52109, -79058, 2, 'Flametongue Totem - Arcane Brilliance');
