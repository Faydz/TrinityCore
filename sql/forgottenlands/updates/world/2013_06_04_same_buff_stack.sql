-- Attack Power Buff (Multiplier)
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=53137 AND `spell_effect` IN (-53137);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (53137, -53137, 2, 'Abomination\'s Might (rank 1) - Abomination\'s Might (rank 1)');
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=53138 AND `spell_effect` IN (-53138);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (53138, -53138, 2, 'Abomination\'s Might (rank 2) - Abomination\'s Might (rank 2)');
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=19506 AND `spell_effect` IN (-19506);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (19506, -19506, 2, 'Trueshot Aura - Trueshot Aura');
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=30802 AND `spell_effect` IN (-30802);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (30802, -30802, 2, 'Unleashed Rage (rank 1) - Unleashed Rage (rank 1)');
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=30808 AND `spell_effect` IN (-30808);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (30808, -30808, 2, 'Unleashed Rage (rank 2) - Unleashed Rage (rank 2)');
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=79102 AND `spell_effect` IN (-79102);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (79102, -79102, 2, 'Blessing of Might - Blessing of Might');

-- Agility and Strength Buff
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=6673 AND `spell_effect` = -6673;
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (6673, -6673, 2, 'Battle Shout - Battle Shout');
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=93435 AND `spell_effect` = -93435;
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (93435, -93435, 2, 'Roar of Courage - Roar of Courage');

-- Critical Buff
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=24604 AND `spell_effect` IN (-24604);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (24604, -24604, 2, 'Furious Howl - Furious Howl');
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=24932 AND `spell_effect` IN (-24932);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (24932, -24932, 2, 'Leader of the Pack - Leader of the Pack');
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=51698 AND `spell_effect` IN (-51698);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (51698, -51698, 2, 'Honor Among Thieves (rank 1) - Honor Among Thieves (rank 1)');
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=51700 AND `spell_effect` IN (-51700);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (51700, -51700, 2, 'Honor Among Thieves (rank 2) - Honor Among Thieves (rank 2)');
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=51701 AND `spell_effect` IN (-51701);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (51701, -51701, 2, 'Honor Among Thieves (rank 3) - Honor Among Thieves (rank 3)');
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=29801 AND `spell_effect` IN (-29801);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (29801, -29801, 2, 'Rampage - Rampage');
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=51466 AND `spell_effect` IN (-51466);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (51466, -51466, 2, 'Elemental Oath (rank 1) - Elemental Oath (rank 1)');
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=51470 AND `spell_effect` IN (-51470);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (51470, -51470, 2, 'Elemental Oath (rank 2) - Elemental Oath (rank 2)');

-- Water walking (ends in combat)
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=3714 AND `spell_effect` IN (-3714);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (3714, -3714, 2, 'Path of Frost - Path of Frost');
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=546 AND `spell_effect` IN (-546);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (546, -546, 2, 'Water Walking - Water Walking');
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=1706 AND `spell_effect` IN (-1706);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (1706, -1706, 2, 'Levitate - Levitate');

-- Mana
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=54424 AND `spell_effect` IN (-54424);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (54424, -54424, 2, 'Fel Intelligence - Fel Intelligence');
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=79058 AND `spell_effect` IN (-79058);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (79058, -79058, 2, 'Arcane Brilliance - Arcane Brilliance');

-- Spell Power buff
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=79058 AND `spell_effect` IN (-79058);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (79058, -79058, 2, 'Arcane Brilliance - Arcane Brilliance');
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=52109 AND `spell_effect` IN (-52109);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (52109, -52109, 2, 'Flametongue Totem - Flametongue Totem');