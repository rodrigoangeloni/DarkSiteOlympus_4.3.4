/*
 * Sistema de Promoción NPC - Instant 80 con Equipamiento Tier 10
 * Implementado para TrinityCore Cataclysm 4.3.4
 * 
 * Características:
 * - Nivel instantáneo a 80
 * - Equipamiento completo Tier 10 Normal (ilvl 264)
 * - Accesorios ICC 25 Heroic (ilvl 277)
 * - Bolsas, oro, monturas y skills
 * - Control de uso: 1 vez por cuenta
 * - Registro en base de datos
 * 
 * Base de datos requerida:
 * - world.npc_promotion_items
 * - characters.npc_promotion_log
 * - NPC entry: 60003 con ScriptName='npc_promocion'
 */

#include "ScriptPCH.h"
#include "AccountMgr.h"

// =============================================================================
// CONFIGURACIÓN
// =============================================================================

#define PROMOTION_LEVEL         80
#define PROMOTION_MONEY         1000 * GOLD
#define BAG_ID                  54443  // Embersilk Bag (22 slots, ilvl 83)
#define PROMOTION_LIMIT         1      // Usos permitidos por cuenta

// Skills de Vuelo
#define SKILL_RIDING_75         33388
#define SKILL_RIDING_150        33391
#define SKILL_RIDING_FLYING     34090
#define SKILL_COLD_WEATHER      54197
#define SKILL_RIDING_310        34091

// Proficiencias de Armadura
#define PLATE_MAIL              750
#define MAIL                    8737

// =============================================================================
// ENUMS
// =============================================================================

enum PromotionActions
{
    // Warrior
    ACTION_WARRIOR_TANK     = 1,
    ACTION_WARRIOR_DPS      = 2,
    
    // Paladin
    ACTION_PALADIN_TANK     = 3,
    ACTION_PALADIN_HEAL     = 4,
    ACTION_PALADIN_DPS      = 5,
    
    // Hunter
    ACTION_HUNTER_DPS       = 6,
    
    // Rogue
    ACTION_ROGUE_DPS        = 7,
    
    // Priest
    ACTION_PRIEST_HEAL      = 8,
    ACTION_PRIEST_DPS       = 9,
    
    // Death Knight
    ACTION_DK_TANK          = 10,
    ACTION_DK_DPS           = 11,
    
    // Shaman
    ACTION_SHAMAN_CASTER    = 12,
    ACTION_SHAMAN_MELEE     = 13,
    ACTION_SHAMAN_HEAL      = 14,
    
    // Mage
    ACTION_MAGE_DPS         = 15,
    
    // Warlock
    ACTION_WARLOCK_DPS      = 16,
    
    // Druid
    ACTION_DRUID_CASTER     = 17,
    ACTION_DRUID_TANK       = 18,
    ACTION_DRUID_MELEE      = 19,
    ACTION_DRUID_HEAL       = 20,
    
    // Otros
    ACTION_CLOSE            = 100,
    ACTION_TELEPORT_DALARAN = 101
};

// =============================================================================
// CLASE PRINCIPAL DEL NPC
// =============================================================================

class npc_promocion : public CreatureScript
{
public:
    npc_promocion() : CreatureScript("npc_promocion") { }

    // =========================================================================
    // FUNCIONES AUXILIARES
    // =========================================================================
    
    uint8 GetAccountPromotionCount(uint32 accountId)
    {
        QueryResult result = CharacterDatabase.PQuery(
            "SELECT COUNT(*) FROM npc_promotion_log WHERE accountId = %u", 
            accountId
        );
        
        if (result)
        {
            Field* fields = result->Fetch();
            return fields[0].GetUInt8();
        }
        return 0;
    }
    
    void AddPromotionLog(Player* player, std::string spec)
    {
        uint32 accountId = player->GetSession()->GetAccountId();
        std::string accountName;
        AccountMgr::GetName(accountId, accountName);
        std::string charName = player->GetName();
        uint32 charGuid = player->GetGUIDLow();
        uint8 playerClass = player->getClass();
        std::string ip = player->GetSession()->GetRemoteAddress();
        
        CharacterDatabase.PExecute(
            "INSERT INTO npc_promotion_log (accountId, accountName, characterName, characterGuid, class, spec, ip) "
            "VALUES (%u, '%s', '%s', %u, %u, '%s', '%s')",
            accountId, accountName.c_str(), charName.c_str(), charGuid, playerClass, spec.c_str(), ip.c_str()
        );
    }
    
    void ApplyPromotionTemplate(Player* player)
    {
        // Subir a nivel 80 solo si está por debajo
        if (player->getLevel() < PROMOTION_LEVEL)
        {
            player->GiveLevel(PROMOTION_LEVEL);
            player->InitTalentForLevel();
            player->SetUInt32Value(PLAYER_XP, 0);
        }
        
        // Dar oro
        player->ModifyMoney(PROMOTION_MONEY);
        
        // Equipar bolsas
        for (uint8 slot = INVENTORY_SLOT_BAG_START; slot < INVENTORY_SLOT_BAG_END; slot++)
        {
            if (Item* bag = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
            {
                player->DestroyItem(INVENTORY_SLOT_BAG_0, slot, true);
            }
            player->EquipNewItem(slot, BAG_ID, true);
        }
        
        // Enseñar skills de vuelo
        player->learnSpell(SKILL_RIDING_75, false);
        player->learnSpell(SKILL_RIDING_150, false);
        player->learnSpell(SKILL_RIDING_FLYING, false);
        player->learnSpell(SKILL_COLD_WEATHER, false);
        player->learnSpell(SKILL_RIDING_310, false);
        
        // Enseñar monturas según raza
        switch (player->getRace())
        {
            case RACE_HUMAN:
                player->learnSpell(23228, false); // Black Stallion
                player->learnSpell(32239, false); // Flying mount
                break;
            case RACE_DWARF:
                player->learnSpell(23239, false); // Swift Brown Ram
                player->learnSpell(32239, false);
                break;
            case RACE_NIGHTELF:
                player->learnSpell(23338, false); // Swift Stormsaber
                player->learnSpell(32239, false);
                break;
            case RACE_GNOME:
                player->learnSpell(23223, false); // Swift Mechanostrider
                player->learnSpell(32239, false);
                break;
            case RACE_DRAENEI:
                player->learnSpell(35713, false); // Swift Blue Elekk
                player->learnSpell(32239, false);
                break;
            case RACE_ORC:
                player->learnSpell(23250, false); // Swift Brown Wolf
                player->learnSpell(32243, false); // Flying mount
                break;
            case RACE_UNDEAD_PLAYER:
                player->learnSpell(66846, false); // Ochre Skeletal Warhorse
                player->learnSpell(32243, false);
                break;
            case RACE_TAUREN:
                player->learnSpell(23248, false); // Swift Brown Kodo
                player->learnSpell(32243, false);
                break;
            case RACE_TROLL:
                player->learnSpell(23242, false); // Swift Blue Raptor
                player->learnSpell(32243, false);
                break;
            case RACE_BLOODELF:
                player->learnSpell(33660, false); // Swift Pink Hawkstrider
                player->learnSpell(32243, false);
                break;
            case RACE_WORGEN:
                player->learnSpell(87840, false); // Mountain Horse
                player->learnSpell(32239, false);
                break;
            case RACE_GOBLIN:
                player->learnSpell(87841, false); // Goblin Trike
                player->learnSpell(32243, false);
                break;
        }
        
        // Actualizar todas las skills al máximo
        player->UpdateSkillsToMaxSkillsForLevel();
    }
    
    void EquipPlayerGear(Player* player, std::string functionRole)
    {
        uint8 playerClass = player->getClass();
        uint8 faction = player->GetTeamId(); // 0 = Alliance, 1 = Horde
        
        QueryResult result = WorldDatabase.PQuery(
            "SELECT head, neck, shoulders, body, chest, waist, legs, feet, wrists, hands, "
            "finger1, finger2, trinket1, trinket2, back, mainhand, offhand, ranged, tabard "
            "FROM npc_promotion_items WHERE class = %u AND faction = %u AND `function` = '%s'",
            playerClass, faction, functionRole.c_str()
        );
        
        if (!result)
        {
            ChatHandler(player->GetSession()).PSendSysMessage("Error: No se encontró equipamiento para tu clase/rol.");
            return;
        }
        
        Field* fields = result->Fetch();
        
        // Array de slots en orden
        uint8 slots[] = {
            EQUIPMENT_SLOT_HEAD,      // 0
            EQUIPMENT_SLOT_NECK,      // 1
            EQUIPMENT_SLOT_SHOULDERS, // 2
            EQUIPMENT_SLOT_BODY,      // 3
            EQUIPMENT_SLOT_CHEST,     // 4
            EQUIPMENT_SLOT_WAIST,     // 5
            EQUIPMENT_SLOT_LEGS,      // 6
            EQUIPMENT_SLOT_FEET,      // 7
            EQUIPMENT_SLOT_WRISTS,    // 8
            EQUIPMENT_SLOT_HANDS,     // 9
            EQUIPMENT_SLOT_FINGER1,   // 10
            EQUIPMENT_SLOT_FINGER2,   // 11
            EQUIPMENT_SLOT_TRINKET1,  // 12
            EQUIPMENT_SLOT_TRINKET2,  // 13
            EQUIPMENT_SLOT_BACK,      // 14
            EQUIPMENT_SLOT_MAINHAND,  // 15
            EQUIPMENT_SLOT_OFFHAND,   // 16
            EQUIPMENT_SLOT_RANGED,    // 17
            EQUIPMENT_SLOT_TABARD     // 18
        };
        
        // Equipar cada item
        for (uint8 i = 0; i < 19; i++)
        {
            uint32 itemId = fields[i].GetUInt32();
            if (itemId > 0)
            {
                player->EquipNewItem(slots[i], itemId, true);
            }
        }
        
        ChatHandler(player->GetSession()).PSendSysMessage("|cff00ff00¡Equipamiento completo aplicado con éxito!|r");
    }
    
    std::string GetFunctionFromAction(uint32 action)
    {
        switch (action)
        {
            case ACTION_WARRIOR_TANK:
            case ACTION_PALADIN_TANK:
            case ACTION_DK_TANK:
            case ACTION_DRUID_TANK:
                return "tank";
                
            case ACTION_PALADIN_HEAL:
            case ACTION_PRIEST_HEAL:
            case ACTION_SHAMAN_HEAL:
            case ACTION_DRUID_HEAL:
                return "heal";
                
            case ACTION_SHAMAN_CASTER:
            case ACTION_DRUID_CASTER:
                return "caster";
                
            case ACTION_SHAMAN_MELEE:
            case ACTION_DRUID_MELEE:
                return "melee";
                
            default:
                return "dps";
        }
    }
    
    // =========================================================================
    // GOSSIP HELLO - MENÚ PRINCIPAL
    // =========================================================================
    
    bool OnGossipHello(Player* player, Creature* creature)
    {
        uint32 accountId = player->GetSession()->GetAccountId();
        uint8 promotionCount = GetAccountPromotionCount(accountId);
        
        // Verificar si el jugador ya usó la promoción
        if (promotionCount >= PROMOTION_LIMIT)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Ya has usado tu promoción en esta cuenta.", GOSSIP_SENDER_MAIN, ACTION_CLOSE);
            player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            return true;
        }
        
        // Mostrar opciones según clase
        uint8 playerClass = player->getClass();
        
        switch (playerClass)
        {
            case CLASS_WARRIOR:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Guerrero Tanque (Protection)", GOSSIP_SENDER_MAIN, ACTION_WARRIOR_TANK);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Guerrero DPS (Fury/Arms)", GOSSIP_SENDER_MAIN, ACTION_WARRIOR_DPS);
                break;
                
            case CLASS_PALADIN:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Paladín Tanque (Protection)", GOSSIP_SENDER_MAIN, ACTION_PALADIN_TANK);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Paladín Sanador (Holy)", GOSSIP_SENDER_MAIN, ACTION_PALADIN_HEAL);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Paladín DPS (Retribution)", GOSSIP_SENDER_MAIN, ACTION_PALADIN_DPS);
                break;
                
            case CLASS_HUNTER:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Cazador DPS", GOSSIP_SENDER_MAIN, ACTION_HUNTER_DPS);
                break;
                
            case CLASS_ROGUE:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Pícaro DPS", GOSSIP_SENDER_MAIN, ACTION_ROGUE_DPS);
                break;
                
            case CLASS_PRIEST:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Sacerdote Sanador (Holy/Disc)", GOSSIP_SENDER_MAIN, ACTION_PRIEST_HEAL);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Sacerdote DPS (Shadow)", GOSSIP_SENDER_MAIN, ACTION_PRIEST_DPS);
                break;
                
            case CLASS_DEATH_KNIGHT:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Caballero de la Muerte Tanque (Blood)", GOSSIP_SENDER_MAIN, ACTION_DK_TANK);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Caballero de la Muerte DPS (Frost/Unholy)", GOSSIP_SENDER_MAIN, ACTION_DK_DPS);
                break;
                
            case CLASS_SHAMAN:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Chamán Elemental (Caster DPS)", GOSSIP_SENDER_MAIN, ACTION_SHAMAN_CASTER);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Chamán Mejora (Melee DPS)", GOSSIP_SENDER_MAIN, ACTION_SHAMAN_MELEE);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Chamán Restauración (Heal)", GOSSIP_SENDER_MAIN, ACTION_SHAMAN_HEAL);
                break;
                
            case CLASS_MAGE:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Mago DPS", GOSSIP_SENDER_MAIN, ACTION_MAGE_DPS);
                break;
                
            case CLASS_WARLOCK:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Brujo DPS", GOSSIP_SENDER_MAIN, ACTION_WARLOCK_DPS);
                break;
                
            case CLASS_DRUID:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Druida Balance (Caster DPS)", GOSSIP_SENDER_MAIN, ACTION_DRUID_CASTER);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Druida Feral Tanque (Bear)", GOSSIP_SENDER_MAIN, ACTION_DRUID_TANK);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Druida Feral DPS (Cat)", GOSSIP_SENDER_MAIN, ACTION_DRUID_MELEE);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Druida Restauración (Heal)", GOSSIP_SENDER_MAIN, ACTION_DRUID_HEAL);
                break;
                
            default:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Clase no soportada.", GOSSIP_SENDER_MAIN, ACTION_CLOSE);
                break;
        }
        
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[Cerrar]", GOSSIP_SENDER_MAIN, ACTION_CLOSE);
        
        player->SEND_GOSSIP_MENU(1, creature->GetGUID());
        return true;
    }
    
    // =========================================================================
    // GOSSIP SELECT - PROCESAR SELECCIÓN
    // =========================================================================
    
    bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        
        if (action == ACTION_CLOSE)
        {
            player->CLOSE_GOSSIP_MENU();
            return true;
        }
        
        if (action == ACTION_TELEPORT_DALARAN)
        {
            player->TeleportTo(571, 5804.14f, 624.77f, 647.76f, 1.64f);
            player->CLOSE_GOSSIP_MENU();
            return true;
        }
        
        // Obtener función/rol según la acción
        std::string functionRole = GetFunctionFromAction(action);
        
        // Registrar uso en log
        AddPromotionLog(player, functionRole);
        
        // Aplicar template (nivel, oro, bolsas, monturas)
        ApplyPromotionTemplate(player);
        
        // Enseñar proficiencias de armadura
        uint8 playerClass = player->getClass();
        switch (playerClass)
        {
            case CLASS_WARRIOR:
            case CLASS_PALADIN:
            case CLASS_DEATH_KNIGHT:
                player->learnSpell(PLATE_MAIL, false);
                break;
                
            case CLASS_HUNTER:
            case CLASS_SHAMAN:
                player->learnSpell(MAIL, false);
                break;
        }
        
        // Equipar items desde base de datos
        EquipPlayerGear(player, functionRole);
        
        // Mensaje de confirmación
        ChatHandler(player->GetSession()).PSendSysMessage(
            "|cff00ff00===========================================|r"
        );
        ChatHandler(player->GetSession()).PSendSysMessage(
            "|cff00ff00¡PROMOCIÓN COMPLETADA!|r"
        );
        ChatHandler(player->GetSession()).PSendSysMessage(
            "|cffff9900- Nivel: 80|r"
        );
        ChatHandler(player->GetSession()).PSendSysMessage(
            "|cffff9900- Oro: 10,000g|r"
        );
        ChatHandler(player->GetSession()).PSendSysMessage(
            "|cffff9900- Equipamiento: Tier 10 Normal (ilvl 264)|r"
        );
        ChatHandler(player->GetSession()).PSendSysMessage(
            "|cffff9900- Bolsas: 4x [Emblemático de Escarcha]|r"
        );
        ChatHandler(player->GetSession()).PSendSysMessage(
            "|cffff9900- Monturas de vuelo: Aprendidas|r"
        );
        ChatHandler(player->GetSession()).PSendSysMessage(
            "|cff00ff00===========================================|r"
        );
        ChatHandler(player->GetSession()).PSendSysMessage(
            "|cff00ff00¡Que tengas suerte en tus aventuras!|r"
        );
        
        player->CLOSE_GOSSIP_MENU();
        return true;
    }
};

// =============================================================================
// REGISTRO DEL SCRIPT
// =============================================================================

void AddSC_npc_promocion()
{
    new npc_promocion();
}
