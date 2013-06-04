DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=79102 AND `spell_effect` IN (-53137, -53138, -19506, -30802, -30808);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (79102, -53137, 1, 'Blessing of Might - Abomination\'s Might (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (79102, -53138, 1, 'Blessing of Might - Abomination\'s Might (rank 2)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (79102, -19506, 1, 'Blessing of Might - Trueshot Aura');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (79102, -30802, 1, 'Blessing of Might - Unleashed Rage (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (79102, -30808, 1, 'Blessing of Might - Unleashed Rage (rank 2)');

-- Agility and Strength Buff
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=6673 AND `spell_effect` = -93435;
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (6673, -93435, 1, 'Battle Shout - Roar of Courage');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=93435 AND `spell_effect` = -6673;
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (93435, -6673, 1, 'Roar of Courage - Battle Shout');

-- Critical Buff
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=24604 AND `spell_effect` IN (-24932, -51698, -51700, -51701, -29801, -51466, -51470);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (24604, -24932, 1, 'Furious Howl - Leader of the Pack');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (24604, -51698, 1, 'Furious Howl - Honor Among Thieves (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (24604, -51700, 1, 'Furious Howl - Honor Among Thieves (rank 2)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (24604, -51701, 1, 'Furious Howl - Honor Among Thieves (rank 3)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (24604, -29801, 1, 'Furious Howl - Rampage');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (24604, -51466, 1, 'Furious Howl - Elemental Oath (rank 1)');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (24604, -51470, 1, 'Furious Howl - Elemental Oath (rank 2)');

-- Water walking (ends in combat)
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=3714 AND `spell_effect` IN (-546, -1706);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (3714, -546, 1, 'Path of Frost - Water Walking');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (3714, -1706, 1, 'Path of Frost - Levitate');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=546 AND `spell_effect` IN (-3714, -1706);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (546, -3714, 1, 'Water Walking - Path of Frost');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (546, -1706, 1, 'Water Walking - Levitate');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=1706 AND `spell_effect` IN (-3714, -546);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (1706, -3714, 1, 'Levitate - Path of Frost');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (1706, -546, 1, 'Levitate - Water Walking');

-- Mana
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=54424 AND `spell_effect` IN (-79058);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (54424, -79058, 1, 'Fel Intelligence - Arcane Brilliance');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=79058 AND `spell_effect` IN (-54424);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (79058, -54424, 1, 'Arcane Brilliance - Fel Intelligence');

-- Spell Power buff
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=79058 AND `spell_effect` IN (-52109);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (79058, -52109, 1, 'Arcane Brilliance - Flametongue Totem');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=52109 AND `spell_effect` IN (-79058);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (52109, -79058, 1, 'Flametongue Totem - Arcane Brilliance');
