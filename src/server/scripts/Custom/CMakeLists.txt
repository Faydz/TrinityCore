# Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

set(scripts_STAT_SRCS
  ${scripts_STAT_SRCS}
  Custom/custom_dtinireset.cpp
  Custom/custom_dtlostskills.cpp
  Custom/custom_dtporter.cpp
  Custom/custom_dtvipvendor.cpp
  Custom/custom_dtrace.cpp
  Custom/custom_dtplayertreff.cpp
  Custom/custom_dtevent.cpp
  Custom/custom_misc.cpp
  Custom/custom_level_npc.cpp
  Custom/Transmogrification.cpp
  Custom/Transmogrification.h
  Custom/Pro_Max.cpp
  Custom/boss_arkton.cpp
  Custom/npc_multivendor.cpp
)

SOURCE_GROUP(Custom REGULAR_EXPRESSION .*/Custom/.*)

message("  -> Prepared: Custom")
