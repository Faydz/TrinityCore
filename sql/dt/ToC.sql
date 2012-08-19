-- update immunity
UPDATE creature_template SET mechanic_immune_mask = 617299803 WHERE entry IN (35144, 35511, 35512, 35513); -- Acidmaw
UPDATE creature_template SET mechanic_immune_mask = 617299803 WHERE entry IN (34799, 35514, 35515, 35516); -- Dreadscale
UPDATE creature_template SET mechanic_immune_mask = 617299803 WHERE entry IN (34797, 35447, 35448, 35449); -- Icehowl
UPDATE creature_template SET mechanic_immune_mask = 617299803 WHERE entry IN (34796, 35438, 35439, 35440); -- Gormok the Impaler
UPDATE creature_template SET mechanic_immune_mask = 617299803 WHERE entry IN (34780, 35216, 35268, 35269); -- Lord Jaraxxus
UPDATE creature_template SET mechanic_immune_mask = 617299803 WHERE entry IN (34496, 35347, 35348, 35349); -- Eydis Darkbane
UPDATE creature_template SET mechanic_immune_mask = 617299803 WHERE entry IN (34497, 35350, 35351, 35352); -- Fjola Lightbane
UPDATE creature_template SET mechanic_immune_mask = 617299803 WHERE entry IN (34564, 34566, 35615, 35616); -- Anub'arak

-- firebomb scriptname and modelid (ToC Gormok encounter)
UPDATE creature_template SET ScriptName = "npc_firebomb" WHERE entry = 34854;
UPDATE creature_template SET modelid1 = 11686, modelid2 = 0 WHERE entry = 34854;

-- frost sphere corrections
UPDATE creature_template SET modelid1 = 11686, minlevel = 80, InhabitType = 4, RegenHealth = 0 WHERE entry IN (34606, 34649);

-- twin waypoints
DELETE FROM waypoint_data WHERE id IN (34496, 34497);
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, move_flag) VALUES
(34496, 1, 553.5, 180.5, 395.14, 1),
(34496, 2, 545.5, 170, 395.14, 1),
(34496, 3, 546, 169, 395.14, 1),
(34497, 1, 573.5, 180.5, 395.14, 1),
(34497, 2, 585.5, 170, 395.14, 1),
(34497, 3, 585, 169, 395.14, 1);

-- Dark / Light essence removing
DELETE FROM spell_linked_spell WHERE spell_trigger IN (-67222, -67223, -67224, -65686, -67176, -67177, -67178, -65684);
INSERT INTO spell_linked_spell (spell_trigger, spell_effect, type, comment) VALUES
(-67222, -67511, 0, 'Light Essence 25M'),
(-67223, -67512, 0, 'Light Essence 10M H'),
(-67224, -67513, 0, 'Light Essence 25M H'),
(-65686, -65811, 0, 'Light Essence 10M'),
(-67176, -67179, 0, 'Dark Essence 25M'),
(-67177, -67180, 0, 'Dark Essence 10M H'),
(-67178, -67181, 0, 'Dark Essence 25M H'),
(-65684, -65827, 0, 'Dark Essence 10M');

-- Dark / Light Vortex scriptname
DELETE FROM spell_script_names WHERE spell_id IN (66059, 67155, 67156, 67157, 66048, 67203, 67204, 67205);
INSERT INTO spell_script_names VALUES
(66059, 'spell_twin_vortex'),
(67155, 'spell_twin_vortex'),
(67156, 'spell_twin_vortex'),
(67157, 'spell_twin_vortex'),
(66048, 'spell_twin_vortex'),
(67203, 'spell_twin_vortex'),
(67204, 'spell_twin_vortex'),
(67205, 'spell_twin_vortex');

-- removing infernal model of nerubian burrower
UPDATE creature_template SET modelid1 = 0 WHERE entry = 34862;

-- removing infernal model of submerged anub'arak
UPDATE creature_template SET modelid2 = 0 WHERE entry = 34660;

-- correcting hitbox of Anub'Arak
UPDATE creature_model_info SET bounding_radius = 1.085, combat_reach = 10.5 WHERE modelid = 29268;

-- correcting hitbox of Acidmaw
UPDATE creature_model_info SET bounding_radius = 1.24, combat_reach = 12 WHERE modelid = 29815;

-- spawn the Anub'arak gate in all versions of the instance
UPDATE gameobject SET spawnMask = 15 WHERE guid = 151192;

-- hand of sacrifice scriptname
DELETE FROM spell_script_names WHERE spell_id = 6940;
INSERT INTO spell_script_names (spell_id, ScriptName) VALUES
(6940, 'spell_pal_hand_of_sacrifice');

-- divine sacrifice scriptname
DELETE FROM spell_script_names WHERE spell_id = 64205;
INSERT INTO spell_script_names (spell_id, ScriptName) VALUES
(64205, 'spell_pal_divine_sacrifice');

-- righteous defense scriptname
DELETE FROM spell_script_names WHERE spell_id = 31789;
INSERT INTO spell_script_names (spell_id, ScriptName) VALUES
(31789, 'spell_pal_righteous_defense');

-- making the Four Horsemen chest lootable
UPDATE gameobject_template SET flags = flags & ~16 WHERE entry = 193426;