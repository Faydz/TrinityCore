DELETE FROM `command` WHERE `name` = 'anticheat';
INSERT INTO `command` (`name`,`security`,`help`) VALUES 
('anticheat','2','Syntax: .anticheat on|off');

DELETE FROM `trinity_string` WHERE `entry` IN (11997,11998,11999);
INSERT INTO `trinity_string` (`entry`,`content_default`) VALUES 
(11997,"Akzeptiere AntiCheat Nachrichten: %s"),
(11998,"Akzeptiere AntiCheat Nachrichten: AN (ON)"),
(11999,"Akzeptiere AntiCheat Nachrichten: AUS (OFF)");