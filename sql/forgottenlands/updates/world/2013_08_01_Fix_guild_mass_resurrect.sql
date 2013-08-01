-- Perk Mass Resurection
DELETE FROM `spell_linked_spell` WHERE (`spell_trigger`='83968');
INSERT INTO `spell_linked_spell` VALUES (83968, 72429, 0, 'mass resurrect');