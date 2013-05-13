#include "ScriptPCH.h"
#include "Player.h"

const Position allyPositions[10]         =
{
    { 999.1775510f, 344.180481f, 370.837323f, 0.098912f },
    { 1219.899780f, 369.020172f, 376.593030f, 4.636352f },
    { 1097.829468f, 297.407440f, 338.916241f, 3.219733f },
    { 1199.673218f, 177.429062f, 355.707410f, 2.074624f },
    { 1215.193359f, 300.782928f, 361.027264f, 3.786792f },
    { 1044.470703f, 218.749252f, 343.369458f, 0.306681f },
    { 1110.909424f, 268.284393f, 338.719861f, 5.322510f },
    { 1058.053711f, 313.626953f, 337.443433f, 1.621712f },
    { 875.7924800f, 27.7601090f, 323.048169f, 1.431161f },
    { 430.6240230f, 138.813034f, 282.133130f, 2.587261f }
};

const Position hordePositions[10]         =
{
    { 104.337402f, 1035.25097f, 297.357495f, 5.554203f },
    { 169.357178f, 1096.64465f, 344.717236f, 0.914823f },
    { 56.9417230f, 1157.41992f, 368.582227f, 4.484038f },
    { -109.43637f, 957.020386f, 339.679242f, 5.199543f },
    { -28.106499f, 970.936523f, 347.605420f, 3.891850f },
    { 30.8158740f, 944.065308f, 339.694714f, 6.270818f },
    { 75.7908780f, 919.697632f, 339.477155f, 2.831559f },
    { 144.238037f, 612.312683f, 284.579053f, 2.688617f },
    { 40.9781910f, 972.875977f, 339.694653f, 5.156347f },
    { 143.599380f, 268.925079f, 289.616589f, 5.685682f }
};

class custom_dtplayertreff : public PlayerScript
{
public:
    custom_dtplayertreff() : PlayerScript("custom_dtplayertreff") {}

    void OnPVPKill(Player* killer, Player* killed) 
    {
        if (killer->GetMapId() == 37 && killed->GetMapId() == 37)
        {
            if (killed->HasAuraType(SPELL_AURA_SPIRIT_OF_REDEMPTION))
                killed->RemoveAurasByType(SPELL_AURA_MOD_SHAPESHIFT);

            killed->KillPlayer();
            killed->ResurrectPlayer(40.0f, true);

            if (Aura * aur = killed->GetAura(15007))
                aur->SetDuration(1*MINUTE*IN_MILLISECONDS); // 1 Minute Nachwirkungen

            killed->CastSpell(killed, 13874, true); // Bubble
            if (Aura * aur = killed->GetAura(13874))
                aur->SetDuration(1*MINUTE*IN_MILLISECONDS); // 1 Minute Bubble

            uint32 rnd = urand(0,9); 
            if (killed->GetTeam() == ALLIANCE)
                killed->TeleportTo(37, allyPositions[rnd].GetPositionX(), allyPositions[rnd].GetPositionY(), allyPositions[rnd].GetPositionZ(), allyPositions[rnd].GetOrientation());
            else
                killed->TeleportTo(37, hordePositions[rnd].GetPositionX(), hordePositions[rnd].GetPositionY(), hordePositions[rnd].GetPositionZ(), hordePositions[rnd].GetOrientation());
        }
    }

    void OnPlayerKilledByCreature(Creature* killer, Player* killed)
    {
        if (killed->GetMapId() == 37)
        {
            if (killed->HasAuraType(SPELL_AURA_SPIRIT_OF_REDEMPTION))
                killed->RemoveAurasByType(SPELL_AURA_MOD_SHAPESHIFT);

            killed->KillPlayer();
            killed->ResurrectPlayer(40.0f, true);

            if (Aura * aur = killed->GetAura(15007))
                aur->SetDuration(1*MINUTE*IN_MILLISECONDS); // 1 Minute Nachwirkungen

            killed->CastSpell(killed, 13874, true); // Bubble
            if (Aura * aur = killed->GetAura(13874))
                aur->SetDuration(1*MINUTE*IN_MILLISECONDS); // 1 Minute Bubble

            uint32 rnd = urand(0,9); 
            if (killed->GetTeam() == ALLIANCE)
                killed->TeleportTo(37, allyPositions[rnd].GetPositionX(), allyPositions[rnd].GetPositionY(), allyPositions[rnd].GetPositionZ(), allyPositions[rnd].GetOrientation());
            else
                killed->TeleportTo(37, hordePositions[rnd].GetPositionX(), hordePositions[rnd].GetPositionY(), hordePositions[rnd].GetPositionZ(), hordePositions[rnd].GetOrientation());
        }
    }
};

void AddSC_custom_dtpvpevent()
{
    new custom_dtplayertreff();
}