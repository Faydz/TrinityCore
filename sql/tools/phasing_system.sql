    SET FOREIGN_KEY_CHECKS=0;
     
    -- ----------------------------
    -- Table structure for `phase`
    -- ----------------------------
    DROP TABLE IF EXISTS `phase`;
    CREATE TABLE `phase` (
      `guid` INT(10) UNSIGNED NOT NULL,
      `player_name` VARCHAR(12) NOT NULL,
      `phase` INT(11) NOT NULL,
      `phase_owned` INT(11) NOT NULL,
      `get_phase` INT(10) NOT NULL,
      `has_completed` tinyint(3) NOT NULL,
      PRIMARY KEY  (`guid`)
    ) ENGINE=MyISAM DEFAULT CHARSET=latin1;
     
    -- ----------------------------
    -- Table structure for `phase_members`
    -- ----------------------------
    DROP TABLE IF EXISTS `phase_members`;
    CREATE TABLE `phase_members` (
      `guid` INT(10) UNSIGNED NOT NULL,
      `player_name` longtext NOT NULL,
      `can_build_in_phase` INT(11) NOT NULL,
      `phase` INT(11) NOT NULL
    ) ENGINE=MyISAM DEFAULT CHARSET=latin1;
