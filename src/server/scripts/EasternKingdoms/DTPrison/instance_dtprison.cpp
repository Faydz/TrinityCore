/* ScriptData
SDName: Instance_DTPrison
SD%Complete: ?
SDComment:
SDCategory: DT Prison (MapID = 35)
EndScriptData */

#include "ScriptPCH.h"
#include "dtprison.h"

enum Blah
{
    DATA_BLAH                                   = 3000
};

class instance_dtprison : public InstanceMapScript
{
    public:
        instance_dtprison()
            : InstanceMapScript("instance_dtprison", 35)
        {
        }

        struct instance_dtprison_InstanceMapScript : public InstanceScript
        {
            instance_dtprison_InstanceMapScript(Map* map) : InstanceScript(map) {}

            uint64 uiBossDoorGUID;

            uint32 State;

            uint64 uiChakalakaGUID;

            void Initialize()
            {
                uiBossDoorGUID = 0;
                uiChakalakaGUID = 0;
                State = 1;
            }

            void OnGameObjectCreate(GameObject* go)
            {
                switch (go->GetEntry())
                {
                    case GO_BOSSTUER:   uiBossDoorGUID = go->GetGUID(); break;
                }
            }

            void OnCreatureCreate(Creature* c)
            {
                switch (c->GetEntry())
                {
                    case BOSS_CHAKALAKA:    uiChakalakaGUID = c->GetGUID(); break;
                }
            }

            void SetData(uint32 type, uint32 data)
            {
                switch (type)
                {
                    case EVENT_STATE:
                        //mach iwas
                        break;
                    case EVENT_BLAH:
                        if (data == DONE) //Wenn EVENT_BLAH abgeschlossen, Tür öffnen
                            if (GameObject* go = instance->GetGameObject(uiBossDoorGUID))
                                go->SetGoState(GO_STATE_ACTIVE);
                        break;
                }

                if (data == DONE)
                    SaveToDB();
            }

            uint32 GetData(uint32 type)
            {
                switch (type)
                {
                    case EVENT_STATE:
                        return State;
                }

                return 0;
            }

            uint64 GetData64(uint32 data)
            {
                switch (data)
                {
                    case DATA_CHAKALAKA:
                        return uiChakalakaGUID;
                }

                return 0;
            }
        };

        InstanceScript* GetInstanceScript(InstanceMap* map) const
        {
            return new instance_dtprison_InstanceMapScript(map);
        }
};

void AddSC_instance_dtprison()
{
    new instance_dtprison();
}
