#include "ScriptPCH.h"

class FirstCharLevel80 : public PlayerScript
{
public:
    FirstCharLevel80() : PlayerScript("FirstCharLevel80") { }

    void OnLogin(Player* player) override
    {
        // Solo verificar si el jugador es nivel 1 para evitar consultas innecesarias
        if (player->getLevel() > 1)
            return;

        uint32 accountId = player->GetSession()->GetAccountId();

        // Verificar si esta cuenta YA recibió el boost alguna vez
        QueryResult checkLog = CharacterDatabase.PQuery(
            "SELECT COUNT(*) FROM first_char_boost_log WHERE accountId = %u", 
            accountId
        );

        if (checkLog)
        {
            Field* fields = checkLog->Fetch();
            uint32 boostCount = fields[0].GetUInt32();

            // Si ya recibió el boost anteriormente, no hacer nada
            if (boostCount > 0)
                return;
        }

        // Registrar que esta cuenta está recibiendo el boost
        uint32 charGuid = player->GetGUIDLow();
        std::string charName = player->GetName();
        
        CharacterDatabase.PExecute(
            "INSERT INTO first_char_boost_log (accountId, characterGuid, characterName) "
            "VALUES (%u, %u, '%s')",
            accountId, charGuid, charName.c_str()
        );

        // Subir a nivel 80
        player->GiveLevel(80);

        // Teletransporte según facción
        if (player->GetTeam() == ALLIANCE)
        {
            // Ventormenta (Stormwind) - Trade District (coordenadas .gps verificadas)
            player->TeleportTo(0, -8487.21f, 602.69f, 96.88f, 5.65f);
        }
        else
        {
            // Orgrimmar - Valle de la Fuerza (coordenadas .gps verificadas)
            player->TeleportTo(1, 1583.12f, -4160.82f, 21.12f, 0.0f);
        }

        ChatHandler(player->GetSession()).PSendSysMessage("¡Bienvenido! Al ser tu primer personaje, has sido subido al nivel 80.");
    }
};

void AddSC_FirstCharLevel80()
{
    new FirstCharLevel80();
}
