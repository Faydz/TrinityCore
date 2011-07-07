#include "ScriptMgr.h"
#include "Chat.h"

class anticheat_commandscript : public CommandScript
{
public:
    anticheat_commandscript() : CommandScript("anticheat_commandscript") { }

    ChatCommand* GetCommands() const
    {
        static ChatCommand anticheatCommandTable[] =
        {
            { "on",            SEC_ADMINISTRATOR,  false,  &HandleAnticheatOnCommand,      "", NULL },
            { "off",           SEC_ADMINISTRATOR,  false,  &HandleAnticheatOffCommand,     "", NULL },
            { NULL,            0,                  false,  NULL,                           "", NULL }
        };
        static ChatCommand commandTable[] =
        {
            { "anticheat",     SEC_ADMINISTRATOR,  false,  NULL,          "", anticheatCommandTable },
            { NULL,            0,                  false,  NULL,          "", NULL }
        };
        return commandTable;
    }

    static bool HandleAnticheatOnCommand(ChatHandler* handler, const char *args)
    {
        handler->PSendSysMessage(LANG_COMMAND_ACON);
        handler->GetSession()->GetPlayer()->SetAntiGMMsg(true);
        return true;
    }

    static bool HandleAnticheatOffCommand(ChatHandler* handler, const char *args)
    {
        handler->PSendSysMessage(LANG_COMMAND_ACOFF);
        handler->GetSession()->GetPlayer()->SetAntiGMMsg(false);
        return true;
    }
};

void AddSC_anticheat_commandscript()
{
    new anticheat_commandscript();
}
