DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=80964 AND `spell_effect`=93983;
INSERT INTO `spell_linked_spell` (`spell_trigger`,`spell_effect`,`comment`) VALUES (80964,93983,'Skull Bash (bear form) - Charge');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=80964 AND `spell_effect`=93985;
INSERT INTO `spell_linked_spell` (`spell_trigger`,`spell_effect`,`type`,`comment`) VALUES (80964,93985,1,'Skull bash (bear form) - Interrupt');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=80965 AND `spell_effect`=93983;
INSERT INTO `spell_linked_spell` (`spell_trigger`,`spell_effect`,`comment`) VALUES (80965, 93983, 'Skull bash (cat form) - Charge');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=80965 AND `spell_effect`=93985;
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (80965, 93985, 1, 'Skull bash (cat form) - Interrupt');