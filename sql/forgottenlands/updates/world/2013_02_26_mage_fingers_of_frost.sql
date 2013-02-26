DELETE FROM spell_proc_event WHERE entry in(44545, 44543, 83074, 44544);
DELETE FROM spell_script_names WHERE spell_id in(44544, 30455, 44614);

INSERT INTO `spell_proc_event` VALUES (44543, 0, 3, 1049120, 4096, 0, 65536, 0, 0, 7, 0);
INSERT INTO `spell_proc_event` VALUES (44545, 0, 3, 1049120, 4096, 0, 65536, 0, 0, 15, 0);
INSERT INTO `spell_proc_event` VALUES (83074, 0, 3, 1049120, 4096, 0, 65536, 0, 0, 20, 0);
INSERT INTO `spell_proc_event` VALUES (44544, 0, 3, 131072, 1048576, 0, 65536, 0, 0, 100, 0);
INSERT INTO `spell_script_names` VALUES (44544, 'spell_fingers_of_frost');
INSERT INTO `spell_script_names` VALUES (30455, 'spell_fingers_of_frost');
INSERT INTO `spell_script_names` VALUES (44614, 'spell_fingers_of_frost');
