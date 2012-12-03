    /*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    Scripted By:    Michaeldev $$$$
    Purpose:                For AA, Donors$
    Completion:             100% $$$$$$$$$$
    $$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
     
    #include "ScriptPCH.h"
     
    enum NECC
    {
            NPC_TEXT                        = 44444,// text for npc in npc_text
            GOSSIP_ICON                     = 6,    // self explan
            DONOR_TOKEN                     = 44209,// token id
            DONOR_TOKEN_COUNT       = 75,    // how many it requires
            MAX_SKILL_LEVEL         = 450   // Max skill level for professions.
    };
     
    class Pro_Max : public CreatureScript
    {
    public: Pro_Max() : CreatureScript("Pro_Max") {}
     
            void SendMessage(Player* player)
            {
                    player->GetSession()->SendNotification("Du benoetigst mindestens 75 Embleme von DarkThunder!");
            }
     
            bool OnGossipHello(Player* player, Creature* creature)
            {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON, "Ingeneurskunst 450(75 Embleme von DarkThunder)", GOSSIP_SENDER_MAIN, 1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON, "Schmiedekunst 450(75 Embleme von DarkThunder)", GOSSIP_SENDER_MAIN, 2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON, "Alchemie 450(75 Embleme von DarkThunder)", GOSSIP_SENDER_MAIN, 3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON, "Lederverarbeitung 450(75 Embleme von DarkThunder)", GOSSIP_SENDER_MAIN, 4);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON, "Schneiderei 450(75 Embleme von DarkThunder)", GOSSIP_SENDER_MAIN, 5);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON, "Kuerschnerei 450(75 Embleme von DarkThunder)", GOSSIP_SENDER_MAIN, 6);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON, "Bergbau 450(75 Embleme von DarkThunder)", GOSSIP_SENDER_MAIN, 7);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON, "Juwelenschleifen 450(75 Embleme von DarkThunder)", GOSSIP_SENDER_MAIN, 8);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON, "Inschriftenkunde 450(75 Embleme von DarkThunder)", GOSSIP_SENDER_MAIN, 9);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON, "Kraeuterkunde 450(75 Embleme von DarkThunder)", GOSSIP_SENDER_MAIN, 10);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON, "Kochkunst 450(75 Embleme von DarkThunder)", GOSSIP_SENDER_MAIN, 11);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON, "Erste Hilfe 450(75 Embleme von DarkThunder)", GOSSIP_SENDER_MAIN, 12);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON, "Angeln 450(75 Embleme von DarkThunder)", GOSSIP_SENDER_MAIN, 13);
                    player->ADD_GOSSIP_ITEM(5, "Auf Wiedersehen!", GOSSIP_SENDER_MAIN, 1000);
                    player->SEND_GOSSIP_MENU(NPC_TEXT, creature->GetGUID());
                    return true;
            }
     
            bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
            {
                    switch(action)
                    {
                    case 1000:
                            player->CLOSE_GOSSIP_MENU();
                    break;
                    case 1:
                            if (!player->HasItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, false))
                            {
                                    SendMessage(player);
                            }
                            else
                            {      
                                    if (player->GetSkillValue(SKILL_ENGINEERING) == MAX_SKILL_LEVEL)
                                    {
                                            player->GetSession()->SendNotification("Dieser Beruf ist bereits auf der hoechsten Stufe!");
                                    }
                                    else if (player->HasSkill(SKILL_ENGINEERING) && player->HasItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, false))
                                    {
                                            player->SetSkill(SKILL_ENGINEERING, 0, MAX_SKILL_LEVEL, MAX_SKILL_LEVEL);
                                            player->DestroyItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, true);
                                    }
                                    else
                                    {
                                            player->GetSession()->SendNotification("Du musst diesen Beruf erst erlernen.");
                                    }
                            }
                            player->CLOSE_GOSSIP_MENU();
                    break;
                    case 2:
                            if (!player->HasItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, false))
                            {
                                    SendMessage(player);
                            }
                            else
                            {      
                                    if (player->GetSkillValue(SKILL_BLACKSMITHING) == MAX_SKILL_LEVEL)
                                    {
                                            player->GetSession()->SendNotification("Dieser Beruf ist bereits auf der hoechsten Stufe!");
                                    }
                                    else if (player->HasSkill(SKILL_BLACKSMITHING) && player->HasItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, false))
                                    {
                                            player->SetSkill(SKILL_BLACKSMITHING, 0, MAX_SKILL_LEVEL, MAX_SKILL_LEVEL);
                                            player->DestroyItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, true);
                                    }
                                    else
                                    {
                                            player->GetSession()->SendNotification("Du musst diesen Beruf erst erlernen.");
                                    }
                            }
                            player->CLOSE_GOSSIP_MENU();
                    break;
                    case 3:
                            if (!player->HasItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, false))
                            {
                                    SendMessage(player);
                            }
                            else
                            {      
                                    if (player->GetSkillValue(SKILL_ALCHEMY) == MAX_SKILL_LEVEL)
                                    {
                                            player->GetSession()->SendNotification("Dieser Beruf ist bereits auf der hoechsten Stufe!");
                                    }
                                    else if (player->HasSkill(SKILL_ALCHEMY) && player->HasItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, false))
                                    {
                                            player->SetSkill(SKILL_ALCHEMY, 0, MAX_SKILL_LEVEL, MAX_SKILL_LEVEL);
                                            player->DestroyItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, true);
                                    }
                                    else
                                    {
                                            player->GetSession()->SendNotification("Du musst diesen Beruf erst erlernen.");
                                    }
                            }
                            player->CLOSE_GOSSIP_MENU();
                    break;
                    case 4:
                            if (!player->HasItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, false))
                            {
                                    SendMessage(player);
                            }
                            else
                            {      
                                    if (player->GetSkillValue(SKILL_LEATHERWORKING) == MAX_SKILL_LEVEL)
                                    {
                                            player->GetSession()->SendNotification("Dieser Beruf ist bereits auf der hoechsten Stufe!");
                                    }
                                    else if (player->HasSkill(SKILL_LEATHERWORKING) && player->HasItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, false))
                                    {
                                            player->SetSkill(SKILL_LEATHERWORKING, 0, MAX_SKILL_LEVEL, MAX_SKILL_LEVEL);
                                            player->DestroyItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, true);
                                    }
                                    else
                                    {
                                            player->GetSession()->SendNotification("Du musst diesen Beruf erst erlernen.");
                                    }
                            }
                            player->CLOSE_GOSSIP_MENU();
                    break;
                    case 5:
                            if (!player->HasItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, false))
                            {
                                    SendMessage(player);
                            }
                            else
                            {      
                                    if (player->GetSkillValue(SKILL_TAILORING) == MAX_SKILL_LEVEL)
                                    {
                                            player->GetSession()->SendNotification("Dieser Beruf ist bereits auf der hoechsten Stufe!");
                                    }
                                    else if (player->HasSkill(SKILL_TAILORING) && player->HasItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, false))
                                    {
                                            player->SetSkill(SKILL_TAILORING, 0, MAX_SKILL_LEVEL, MAX_SKILL_LEVEL);
                                            player->DestroyItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, true);
                                    }
                                    else
                                    {
                                            player->GetSession()->SendNotification("Du musst diesen Beruf erst erlernen.");
                                    }
                            }
                            player->CLOSE_GOSSIP_MENU();
                    break;
                    case 6:
                            if (!player->HasItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, false))
                            {
                                    SendMessage(player);
                            }
                            else
                            {      
                                    if (player->GetSkillValue(SKILL_SKINNING) == MAX_SKILL_LEVEL)
                                    {
                                            player->GetSession()->SendNotification("Dieser Beruf ist bereits auf der hoechsten Stufe!");
                                    }
                                    else if (player->HasSkill(SKILL_SKINNING) && player->HasItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, false))
                                    {
                                            player->SetSkill(SKILL_SKINNING, 0, MAX_SKILL_LEVEL, MAX_SKILL_LEVEL);
                                            player->DestroyItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, true);
                                    }
                                    else
                                    {
                                            player->GetSession()->SendNotification("Du musst diesen Beruf erst erlernen.");
                                    }
                            }
                            player->CLOSE_GOSSIP_MENU();
                    break;
                    case 8:
                            if (!player->HasItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, false))
                            {
                                    SendMessage(player);
                            }
                            else
                            {      
                                    if (player->GetSkillValue(SKILL_MINING) == MAX_SKILL_LEVEL)
                                    {
                                            player->GetSession()->SendNotification("Dieser Beruf ist bereits auf der hoechsten Stufe!");
                                    }
                                    else if (player->HasSkill(SKILL_MINING) && player->HasItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, false))
                                    {
                                            player->SetSkill(SKILL_MINING, 0, MAX_SKILL_LEVEL, MAX_SKILL_LEVEL);
                                            player->DestroyItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, true);
                                    }
                                    else
                                    {
                                            player->GetSession()->SendNotification("Du musst diesen Beruf erst erlernen.");
                                    }
                            }
                            player->CLOSE_GOSSIP_MENU();
                    break;
                    case 7:
                            if (!player->HasItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, false))
                            {
                                    SendMessage(player);
                            }
                            else
                            {      
                                    if (player->GetSkillValue(SKILL_JEWELCRAFTING) == MAX_SKILL_LEVEL)
                                    {
                                            player->GetSession()->SendNotification("Dieser Beruf ist bereits auf der hoechsten Stufe!");
                                    }
                                    else if (player->HasSkill(SKILL_JEWELCRAFTING) && player->HasItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, false))
                                    {
                                            player->SetSkill(SKILL_JEWELCRAFTING, 0, MAX_SKILL_LEVEL, MAX_SKILL_LEVEL);
                                            player->DestroyItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, true);
                                    }
                                    else
                                    {
                                            player->GetSession()->SendNotification("Du musst diesen Beruf erst erlernen.");
                                    }
                            }
                            player->CLOSE_GOSSIP_MENU();
                    break;
                    case 9:
                            if (!player->HasItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, false))
                            {
                                    SendMessage(player);
                            }
                            else
                            {      
                                    if (player->GetSkillValue(SKILL_INSCRIPTION) == MAX_SKILL_LEVEL)
                                    {
                                            player->GetSession()->SendNotification("Dieser Beruf ist bereits auf der hoechsten Stufe!");
                                    }
                                    else if (player->HasSkill(SKILL_INSCRIPTION) && player->HasItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, false))
                                    {
                                            player->SetSkill(SKILL_INSCRIPTION, 0, MAX_SKILL_LEVEL, MAX_SKILL_LEVEL);
                                            player->DestroyItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, true);
                                    }
                                    else
                                    {
                                            player->GetSession()->SendNotification("Du musst diesen Beruf erst erlernen.");
                                    }
                            }
                            player->CLOSE_GOSSIP_MENU();
                    break;
                    case 10:
                            if (!player->HasItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, false))
                            {
                                    SendMessage(player);
                            }
                            else
                            {      
                                    if (player->GetSkillValue(SKILL_HERBALISM) == MAX_SKILL_LEVEL)
                                    {
                                            player->GetSession()->SendNotification("Dieser Beruf ist bereits auf der hoechsten Stufe!");
                                    }
                                    else if (player->HasSkill(SKILL_HERBALISM) && player->HasItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, false))
                                    {
                                            player->SetSkill(SKILL_HERBALISM, 0, MAX_SKILL_LEVEL, MAX_SKILL_LEVEL);
                                            player->DestroyItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, true);
                                    }
                                    else
                                    {
                                            player->GetSession()->SendNotification("Du musst diesen Beruf erst erlernen.");
                                    }
                            }
                            player->CLOSE_GOSSIP_MENU();
                    break;
                    case 11:
                            if (!player->HasItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, false))
                            {
                                    SendMessage(player);
                            }
                            else
                            {      
                                    if (player->GetSkillValue(SKILL_COOKING) == MAX_SKILL_LEVEL)
                                    {
                                            player->GetSession()->SendNotification("Dieser Beruf ist bereits auf der hoechsten Stufe!");
                                    }
                                    else if (player->HasSkill(SKILL_COOKING) && player->HasItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, false))
                                    {
                                            player->SetSkill(SKILL_COOKING, 0, MAX_SKILL_LEVEL, MAX_SKILL_LEVEL);
                                            player->DestroyItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, true);
                                    }
                                    else
                                    {
                                            player->GetSession()->SendNotification("Du musst diesen Beruf erst erlernen.");
                                    }
                            }
                            player->CLOSE_GOSSIP_MENU();
                    break;
                    case 12:
                            if (!player->HasItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, false))
                            {
                                    SendMessage(player);
                            }
                            else
                            {      
                                    if (player->GetSkillValue(SKILL_FIRST_AID) == MAX_SKILL_LEVEL)
                                    {
                                            player->GetSession()->SendNotification("Dieser Beruf ist bereits auf der hoechsten Stufe!");
                                    }
                                    else if (player->HasSkill(SKILL_FIRST_AID) && player->HasItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, false))
                                    {
                                            player->SetSkill(SKILL_FIRST_AID, 0, MAX_SKILL_LEVEL, MAX_SKILL_LEVEL);
                                            player->DestroyItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, true);
                                    }
                                    else
                                    {
                                            player->GetSession()->SendNotification("Du musst diesen Beruf erst erlernen.");
                                    }
                            }
                            player->CLOSE_GOSSIP_MENU();
                    break;
                    case 13:
                            if (!player->HasItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, false))
                            {
                                    SendMessage(player);
                            }
                            else
                            {      
                                    if (player->GetSkillValue(SKILL_FISHING) == MAX_SKILL_LEVEL)
                                    {
                                            player->GetSession()->SendNotification("Dieser Beruf ist bereits auf der hoechsten Stufe!");
                                    }
                                    else if (player->HasSkill(SKILL_FISHING) && player->HasItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, false))
                                    {
                                            player->SetSkill(SKILL_FISHING, 0, MAX_SKILL_LEVEL, MAX_SKILL_LEVEL);
                                            player->DestroyItemCount(DONOR_TOKEN, DONOR_TOKEN_COUNT, true);
                                    }
                                    else
                                    {
                                            player->GetSession()->SendNotification("Du musst diesen Beruf erst erlernen");
                                    }
                            }
                            player->CLOSE_GOSSIP_MENU();
                    break;
                    }
                    return true;
            }
     
    };
     
    void AddSC_Pro_Max()
    {
            new Pro_Max();
    }
