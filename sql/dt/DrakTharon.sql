-- correct some flags, factions
UPDATE `creature_template` SET `faction_A`=1814,`faction_H`=1814,`unit_flags`=`unit_flags`&~33554432&~2,`dynamicflags`=`dynamicflags`&~32,`type_flags`=`type_flags`&~128,`flags_extra`=`flags_extra`&~2 WHERE `entry` IN (26620,31339);

UPDATE `creature_template` SET `unit_flags`=`unit_flags`|0x2, `flags_extra`=`flags_extra`|0x2 WHERE `entry`=27490;

UPDATE `creature_template` SET `unit_flags`=`unit_flags`&~33554432&~2 WHERE `entry` IN (26638,31351);
UPDATE `creature_template` SET `dynamicflags`=`dynamicflags`&~32 WHERE `entry` IN (26638,31351);
UPDATE `creature` SET `unit_flags`=0,`dynamicflags`=`dynamicflags`&~32 WHERE `id` IN (26638,31351);

UPDATE `creature_template` SET `faction_A`=1814,`faction_H`=1814 WHERE `entry` IN (26639,31345,26830,31352,27431,31338);