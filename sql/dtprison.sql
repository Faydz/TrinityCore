/* Add DTPrison Instance template entry & access requirements */
INSERT INTO access_requirement (`mapId`, `difficulty`, `level_min`, `level_max`, `item`, `item2`, `quest_done_A`, `quest_done_H`, `completed_achievement`, `quest_failed_text`, `comment`) VALUES
(35, 0, 80, 80, 0, 0, 0, 0, 0, NULL, 'DT-Ini: Das Verlies von Sturmwind'),
(35, 2, 80, 80, 0, 0, 0, 0, 0, NULL, 'DT-Ini: Das Verlies von Sturmwind');

INSERT INTO instance_template (`map`, `parent`, `script`, `allowMount`) VALUES
(35, 0, 'instance_dtprison', 0);
