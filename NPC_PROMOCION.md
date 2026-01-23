# NPC de Promoción - Documentación Técnica Completa

## 📋 Tabla de Contenidos
1. [Visión General](#visión-general)
2. [Arquitectura del Sistema](#arquitectura-del-sistema)
3. [Estructura de Base de Datos](#estructura-de-base-de-datos)
4. [Lógica del Script C++](#lógica-del-script-c)
5. [Flujo de Funcionamiento](#flujo-de-funcionamiento)
6. [IDs de Items Tier 10 (ICC Normal - ilvl 251)](#ids-de-items-tier-10)
7. [Implementación para TrinityCore](#implementación-para-trinitycore)
8. [Plan de Desarrollo](#plan-de-desarrollo)

---

## Visión General

### ¿Qué es el NPC de Promoción?
Es un sistema automatizado de "Instant 80" (o el nivel que se configure) que permite a los jugadores obtener un personaje completo con un solo clic, similar al sistema de "Character Boost" oficial de Blizzard pero personalizable.

### Características Principales
- **Nivel Instantáneo**: Sube el personaje al nivel configurado (80 por defecto)
- **Equipamiento Inteligente**: Entrega un set completo de equipo basado en:
  - Clase del jugador (Warrior, Paladin, Mage, etc.)
  - Especialización elegida (Tank, DPS, Healer)
  - Facción (Alianza/Horda) para items faccionarios
- **Recursos Iniciales**:
  - Oro configurable
  - Bolsas equipadas automáticamente
  - Monturas y habilidades de vuelo
  - Emblemas/Tokens para comprar items adicionales (opcional)
- **Control de Uso**:
  - Límite por cuenta (1 vez por defecto)
  - Límite por IP (opcional)
  - Registro en base de datos (log)
- **Seguridad**: Verifica que el jugador sea elegible antes de otorgar beneficios

---

## Arquitectura del Sistema

### Componentes del Módulo (AzerothCore Reference)

```
mod-npc-promotion/
├── src/
│   ├── NpcPromotion.cpp      # Lógica principal
│   ├── NpcPromotion.h        # Enums y constantes
│   └── NP_loader.cpp         # Cargador del módulo
├── data/sql/
│   ├── db-auth/              # Tabla de log de uso
│   └── db-world/             # Items y NPC
└── conf/
    └── mod-npc-promotion.conf # Configuración
```

### Clases Principales (C++)

#### 1. **NpcPromotionAnnouncer** (PlayerScript)
```cpp
class NpcPromotionAnnouncer : public PlayerScript
{
    void OnLogin(Player* player)
    {
        // Envía un mensaje al jugador cuando inicia sesión
        // anunciando la disponibilidad del NPC
    }
}
```

#### 2. **npc_promocion** (CreatureScript)
```cpp
class npc_promocion : public CreatureScript
{
    bool OnGossipHello(Player* player, Creature* creature)
    {
        // 1. Verifica si el jugador es elegible (nivel, límites)
        // 2. Detecta la clase del jugador
        // 3. Muestra opciones de especialización en el menú Gossip
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 action)
    {
        // 1. Registra el uso en la base de datos
        // 2. Llama a promotionPlayerTemplate() para nivel/oro/bolsas
        // 3. Llama a equipmentPlayer() para equipar items
        // 4. Cierra el menú
    }
}
```

#### 3. **Funciones Auxiliares**

**promotionPlayerTemplate(Player* player)**
```cpp
void promotionPlayerTemplate(Player* player)
{
    // 1. Subir nivel: player->GiveLevel(80)
    // 2. Dar oro: player->ModifyMoney(amount)
    // 3. Equipar bolsas: player->EquipNewItem(slot, bagId, true)
    // 4. Enseñar monturas y habilidades de vuelo
    // 5. Actualizar skills: player->UpdateSkillsToMaxSkillsForLevel()
}
```

**equipmentPlayer(Player* player, uint8 playerClass, uint8 playerTeam, std::string playerFunction)**
```cpp
void equipmentPlayer(Player* player, uint8 playerClass, uint8 playerTeam, std::string playerFunction)
{
    // Opción A: Dar emblemas para comprar (si EMBLEMS = true)
    if (npcPromotion.EMBLEMS)
    {
        player->AddItem(emblemId, count);
    }
    // Opción B: Equipar directamente desde DB
    else
    {
        // Consulta SQL: SELECT * FROM npc_promotion_items 
        //               WHERE class = X AND faction = Y AND function = 'tank'
        for (int slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; slot++)
        {
            if (itemId != 0)
                player->EquipNewItem(slot, itemId, true);
        }
    }
}
```

---

## Estructura de Base de Datos

### Tabla: `npc_promotion_items` (Base de Datos: `world`)

```sql
CREATE TABLE `npc_promotion_items` (
    `class` INT NOT NULL COMMENT 'ID de clase (1=Warrior, 2=Paladin, etc.)',
    `faction` INT NOT NULL COMMENT '0=Alianza, 1=Horda',
    `function` VARCHAR(50) NOT NULL COMMENT 'tank, dps, heal, caster, melee',
    `head` INT DEFAULT 0,
    `neck` INT DEFAULT 0,
    `shoulders` INT DEFAULT 0,
    `body` INT DEFAULT 0 COMMENT 'Camisa (raramente usado)',
    `chest` INT DEFAULT 0,
    `waist` INT DEFAULT 0,
    `legs` INT DEFAULT 0,
    `feet` INT DEFAULT 0,
    `wrists` INT DEFAULT 0,
    `hands` INT DEFAULT 0,
    `finger1` INT DEFAULT 0,
    `finger2` INT DEFAULT 0,
    `trinket1` INT DEFAULT 0,
    `trinket2` INT DEFAULT 0,
    `back` INT DEFAULT 0,
    `mainhand` INT DEFAULT 0,
    `offhand` INT DEFAULT 0,
    `ranged` INT DEFAULT 0,
    `tabard` INT DEFAULT 0,
    PRIMARY KEY (`class`, `faction`, `function`)
);
```

### Tabla: `npc_promotion_log` (Base de Datos: `characters`)

```sql
CREATE TABLE `npc_promotion_log` (
    `id` INT AUTO_INCREMENT PRIMARY KEY,
    `accountId` INT NOT NULL,
    `accountName` VARCHAR(255),
    `characterName` VARCHAR(255),
    `ip` VARCHAR(45),
    `date` TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    INDEX `idx_account` (`accountId`)
);
```

### Ejemplo de Datos (Warrior - Alianza - Tank)

```sql
INSERT INTO `npc_promotion_items` VALUES 
(1, 0, 'tank', 
 51227,  -- head (Sanctified Ymirjar Lord's Helmet)
 50647,  -- neck
 51229,  -- shoulders
 0,      -- body
 51225,  -- chest
 50620,  -- waist
 51226,  -- legs
 49906,  -- feet
 50659,  -- wrists
 51228,  -- hands
 50678,  -- finger1
 50642,  -- finger2
 50364,  -- trinket1
 47216,  -- trinket2
 50653,  -- back
 50415,  -- mainhand (Glorenzelg, High-Blade of the Silver Hand)
 50729,  -- offhand (Icecrown Glacial Wall)
 0,      -- ranged
 0       -- tabard
);
```

---

## Lógica del Script C++

### Flujo de `OnGossipHello`

```
┌─────────────────────────────────────────┐
│ Jugador interactúa con NPC              │
└───────────────┬─────────────────────────┘
                │
                ▼
┌─────────────────────────────────────────┐
│ ¿Nivel < 80?                            │
└───────────────┬─────────────────────────┘
                │ Sí
                ▼
┌─────────────────────────────────────────┐
│ getAccountPromotionCount(accountId)     │
│ ¿Ya usó la promoción?                   │
└───────────────┬─────────────────────────┘
                │ No
                ▼
┌─────────────────────────────────────────┐
│ switch (player->getClass())             │
│   case CLASS_WARRIOR:                   │
│     AddGossipItem("Tank")               │
│     AddGossipItem("DPS")                │
│   case CLASS_PALADIN:                   │
│     AddGossipItem("Tank")               │
│     AddGossipItem("Heal")               │
│     AddGossipItem("DPS")                │
│   ...                                   │
└───────────────┬─────────────────────────┘
                │
                ▼
┌─────────────────────────────────────────┐
│ SendGossipMenuFor(player, npc)          │
└─────────────────────────────────────────┘
```

### Flujo de `OnGossipSelect`

```
┌─────────────────────────────────────────┐
│ Jugador selecciona opción (action)     │
└───────────────┬─────────────────────────┘
                │
                ▼
┌─────────────────────────────────────────┐
│ addPromotionLog(player)                 │
│ INSERT INTO npc_promotion_log           │
└───────────────┬─────────────────────────┘
                │
                ▼
┌─────────────────────────────────────────┐
│ promotionPlayerTemplate(player)         │
│  ├─ GiveLevel(80)                       │
│  ├─ ModifyMoney(oro)                    │
│  ├─ EquipNewItem(bolsas)                │
│  └─ learnSpell(monturas, vuelo)         │
└───────────────┬─────────────────────────┘
                │
                ▼
┌─────────────────────────────────────────┐
│ player->learnSpell(PLATE_MAIL/MAIL)    │
│ (Si la clase lo requiere)               │
└───────────────┬─────────────────────────┘
                │
                ▼
┌─────────────────────────────────────────┐
│ equipmentPlayer(class, faction, spec)   │
│  └─ Query DB para obtener item IDs      │
│  └─ Loop: EquipNewItem(slot, itemId)    │
└───────────────┬─────────────────────────┘
                │
                ▼
┌─────────────────────────────────────────┐
│ CloseGossipMenuFor(player)              │
└─────────────────────────────────────────┘
```

---

## IDs de Items Tier 10 (ICC Normal - ilvl 251)

> **⚠️ NOTA IMPORTANTE:** Estos IDs son para WotLK 3.3.5a. En Cataclysm 4.3.4 los IDs pueden ser diferentes. Deberás validarlos en tu base de datos ejecutando las consultas de validación al final de esta sección.

### Consulta SQL para Validar en tu DB

```sql
-- Buscar Tier 10 por nombre en tu DB
SELECT entry, name, ItemLevel, class, subclass
FROM item_template 
WHERE name LIKE '%Sanctified%' 
  AND ItemLevel BETWEEN 251 AND 277
ORDER BY class, ItemLevel, name;

-- Buscar por sets específicos
SELECT entry, name, ItemLevel 
FROM item_template 
WHERE name LIKE '%Ymirjar%' OR name LIKE '%Lightsworn%' OR name LIKE '%Scourgelord%'
ORDER BY name;
```

### Warrior (Guerrero) - Class ID: 1

**DPS (Fury/Arms) - Ymirjar Lord's Battlegear**
- Head: 51227 (Sanctified Ymirjar Lord's Helmet)
- Shoulders: 51229 (Sanctified Ymirjar Lord's Pauldrons)
- Chest: 51225 (Sanctified Ymirjar Lord's Battleplate)
- Hands: 51228 (Sanctified Ymirjar Lord's Gauntlets)
- Legs: 51226 (Sanctified Ymirjar Lord's Legplates)

**Tank (Protection) - Ymirjar Lord's Plate**
- Head: 51221 (Sanctified Ymirjar Lord's Greathelm)
- Shoulders: 51223 (Sanctified Ymirjar Lord's Shoulderplates)
- Chest: 51219 (Sanctified Ymirjar Lord's Breastplate)
- Hands: 51222 (Sanctified Ymirjar Lord's Handguards)
- Legs: 51220 (Sanctified Ymirjar Lord's Legguards)

### Paladin - Class ID: 2

**Holy - Lightsworn Garb**
- Head: 51272 (Sanctified Lightsworn Headpiece)
- Shoulders: 51274 (Sanctified Lightsworn Spaulders)
- Chest: 51270 (Sanctified Lightsworn Tunic)
- Hands: 51273 (Sanctified Lightsworn Gloves)
- Legs: 51271 (Sanctified Lightsworn Greaves)

**Protection - Lightsworn Plate**
- Head: 51266 (Sanctified Lightsworn Faceguard)
- Shoulders: 51268 (Sanctified Lightsworn Shoulderguards)
- Chest: 51264 (Sanctified Lightsworn Chestguard)
- Hands: 51267 (Sanctified Lightsworn Handguards)
- Legs: 51265 (Sanctified Lightsworn Legguards)

**Retribution - Lightsworn Battlegear**
- Head: 51277 (Sanctified Lightsworn Helmet)
- Shoulders: 51279 (Sanctified Lightsworn Shoulderplates)
- Chest: 51275 (Sanctified Lightsworn Battleplate)
- Hands: 51278 (Sanctified Lightsworn Gauntlets)
- Legs: 51276 (Sanctified Lightsworn Legplates)

### Hunter (Cazador) - Class ID: 3

**Ahn'Kahar Blood Hunter's Battlegear**
- Head: 51286 (Sanctified Ahn'Kahar Blood Hunter's Headpiece)
- Shoulders: 51288 (Sanctified Ahn'Kahar Blood Hunter's Spaulders)
- Chest: 51284 (Sanctified Ahn'Kahar Blood Hunter's Tunic)
- Hands: 51287 (Sanctified Ahn'Kahar Blood Hunter's Handguards)
- Legs: 51285 (Sanctified Ahn'Kahar Blood Hunter's Legguards)

### Rogue (Pícaro) - Class ID: 4

**Shadowblade's Battlegear**
- Head: 51252 (Sanctified Shadowblade's Helmet)
- Shoulders: 51254 (Sanctified Shadowblade's Pauldrons)
- Chest: 51250 (Sanctified Shadowblade's Breastplate)
- Hands: 51253 (Sanctified Shadowblade's Gauntlets)
- Legs: 51251 (Sanctified Shadowblade's Legplates)

### Priest (Sacerdote) - Class ID: 5

**Holy/Discipline - Crimson Acolyte's Raiment**
- Head: 51261 (Sanctified Crimson Acolyte's Hood)
- Shoulders: 51263 (Sanctified Crimson Acolyte's Mantle)
- Chest: 51259 (Sanctified Crimson Acolyte's Robe)
- Hands: 51262 (Sanctified Crimson Acolyte's Handwraps)
- Legs: 51260 (Sanctified Crimson Acolyte's Leggings)

**Shadow - Crimson Acolyte's Regalia**
- Head: 51255 (Sanctified Crimson Acolyte's Cowl)
- Shoulders: 51257 (Sanctified Crimson Acolyte's Shoulderpads)
- Chest: 51258 (Sanctified Crimson Acolyte's Raiment)
- Hands: 51256 (Sanctified Crimson Acolyte's Gloves)
- Legs: 51254 (Sanctified Crimson Acolyte's Pants)

### Death Knight (Caballero de la Muerte) - Class ID: 6

**Tank (Blood) - Scourgelord Plate**
- Head: 51306 (Sanctified Scourgelord Faceguard)
- Shoulders: 51308 (Sanctified Scourgelord Pauldrons)
- Chest: 51304 (Sanctified Scourgelord Chestguard)
- Hands: 51307 (Sanctified Scourgelord Handguards)
- Legs: 51305 (Sanctified Scourgelord Legguards)

**DPS (Frost/Unholy) - Scourgelord Battlegear**
- Head: 51312 (Sanctified Scourgelord Helmet)
- Shoulders: 51314 (Sanctified Scourgelord Shoulderplates)
- Chest: 51310 (Sanctified Scourgelord Battleplate)
- Hands: 51313 (Sanctified Scourgelord Gauntlets)
- Legs: 51311 (Sanctified Scourgelord Legplates)

### Shaman (Chamán) - Class ID: 7

**Elemental - Frost Witch's Regalia**
- Head: 51237 (Sanctified Frost Witch's Helm)
- Shoulders: 51235 (Sanctified Frost Witch's Shoulderpads)
- Chest: 51239 (Sanctified Frost Witch's Hauberk)
- Hands: 51236 (Sanctified Frost Witch's Gloves)
- Legs: 51238 (Sanctified Frost Witch's Kilt)

**Enhancement - Frost Witch's Battlegear**
- Head: 51242 (Sanctified Frost Witch's Faceguard)
- Shoulders: 51240 (Sanctified Frost Witch's Shoulderguards)
- Chest: 51244 (Sanctified Frost Witch's Chestguard)
- Hands: 51241 (Sanctified Frost Witch's Grips)
- Legs: 51243 (Sanctified Frost Witch's War-Kilt)

**Restoration - Frost Witch's Garb**
- Head: 51247 (Sanctified Frost Witch's Headpiece)
- Shoulders: 51245 (Sanctified Frost Witch's Spaulders)
- Chest: 51249 (Sanctified Frost Witch's Tunic)
- Hands: 51246 (Sanctified Frost Witch's Handguards)
- Legs: 51248 (Sanctified Frost Witch's Legguards)

### Mage - Class ID: 8

**Bloodmage's Regalia**
- Head: 51281 (Sanctified Bloodmage's Hood)
- Shoulders: 51279 (Sanctified Bloodmage's Shoulderpads)
- Chest: 51283 (Sanctified Bloodmage's Robe)
- Hands: 51280 (Sanctified Bloodmage's Gloves)
- Legs: 51282 (Sanctified Bloodmage's Leggings)

### Warlock (Brujo) - Class ID: 9

**Dark Coven's Regalia**
- Head: 51231 (Sanctified Dark Coven's Hood)
- Shoulders: 51229 (Sanctified Dark Coven's Shoulderpads)
- Chest: 51233 (Sanctified Dark Coven's Robe)
- Hands: 51230 (Sanctified Dark Coven's Gloves)
- Legs: 51232 (Sanctified Dark Coven's Leggings)

### Druid (Druida) - Class ID: 11

**Balance - Lasherweave's Regalia**
- Head: 51290 (Sanctified Lasherweave's Cover)
- Shoulders: 51292 (Sanctified Lasherweave's Mantle)
- Chest: 51294 (Sanctified Lasherweave's Vestment)
- Hands: 51291 (Sanctified Lasherweave's Handgrips)
- Legs: 51293 (Sanctified Lasherweave's Legplates)

**Feral (Tank/DPS) - Lasherweave's Battlegear**
- Head: 51296 (Sanctified Lasherweave's Headguard)
- Shoulders: 51298 (Sanctified Lasherweave's Shoulderpads)
- Chest: 51300 (Sanctified Lasherweave's Raiment)
- Hands: 51297 (Sanctified Lasherweave's Handguards)
- Legs: 51299 (Sanctified Lasherweave's Legguards)

**Restoration - Lasherweave's Garb**
- Head: 51301 (Sanctified Lasherweave's Helmet)
- Shoulders: 51303 (Sanctified Lasherweave's Spaulders)
- Chest: 51299 (Sanctified Lasherweave's Robes)
- Hands: 51302 (Sanctified Lasherweave's Gloves)
- Legs: 51300 (Sanctified Lasherweave's Trousers)

---

## Implementación para TrinityCore

### Diferencias Clave con AzerothCore

| Aspecto | AzerothCore | TrinityCore |
|---------|-------------|-------------|
| **Headers** | `#include "ScriptMgr.h"` | `#include "ScriptPCH.h"` |
| **Database Log** | `LoginDatabase` | `CharacterDatabase` (preferible) |
| **Gossip** | `AddGossipItemFor()` | `AddGossipItemFor()` ✅ |
| **EquipItem** | `player->EquipNewItem()` | `player->EquipNewItem()` ✅ |
| **Config** | `sConfigMgr->GetOption()` | No usar, hardcodear valores |

### Constantes Importantes

```cpp
// Enums de Slots de Equipamiento
enum EquipmentSlots
{
    EQUIPMENT_SLOT_START        = 0,
    EQUIPMENT_SLOT_HEAD         = 0,
    EQUIPMENT_SLOT_NECK         = 1,
    EQUIPMENT_SLOT_SHOULDERS    = 2,
    EQUIPMENT_SLOT_BODY         = 3,
    EQUIPMENT_SLOT_CHEST        = 4,
    EQUIPMENT_SLOT_WAIST        = 5,
    EQUIPMENT_SLOT_LEGS         = 6,
    EQUIPMENT_SLOT_FEET         = 7,
    EQUIPMENT_SLOT_WRISTS       = 8,
    EQUIPMENT_SLOT_HANDS        = 9,
    EQUIPMENT_SLOT_FINGER1      = 10,
    EQUIPMENT_SLOT_FINGER2      = 11,
    EQUIPMENT_SLOT_TRINKET1     = 12,
    EQUIPMENT_SLOT_TRINKET2     = 13,
    EQUIPMENT_SLOT_BACK         = 14,
    EQUIPMENT_SLOT_MAINHAND     = 15,
    EQUIPMENT_SLOT_OFFHAND      = 16,
    EQUIPMENT_SLOT_RANGED       = 17,
    EQUIPMENT_SLOT_TABARD       = 18,
    EQUIPMENT_SLOT_END          = 19
};

// Skills de Vuelo y Armadura
#define SKILL_RIDING_75             33388
#define SKILL_RIDING_150            33391
#define SKILL_RIDING_FLYING         34090
#define SKILL_COLD_WEATHER_FLYING   54197
#define SKILL_RIDING_310            34091
#define PLATE_MAIL                  750
#define MAIL                        8737

// Configuración
#define PROMOTION_LEVEL             80
#define PROMOTION_MONEY             (1000 * GOLD)
#define BAG_ID                      41599  // Emblemático de Escarcha
```

---

## Plan de Desarrollo

### ✅ Fase 1: Documentación (COMPLETO)
- [x] Analizar módulo AzerothCore
- [x] Documentar arquitectura completa
- [x] Crear guía de implementación

### 📝 Fase 2: Base de Datos (SIGUIENTE)
- [ ] Validar IDs de Tier 10 en Cataclysm DB
- [ ] Crear tabla `npc_promotion_items` en `world`
- [ ] Crear tabla `npc_promotion_log` en `characters`
- [ ] Poblar tabla con sets de Warrior y Paladin (prueba)
- [ ] Crear NPC en `creature_template` (ID: 60003)

### 💻 Fase 3: Implementación C++
- [ ] Crear `npc_promocion.cpp` en `Custom/`
- [ ] Implementar verificación de elegibilidad
- [ ] Implementar menú Gossip por clase
- [ ] Implementar función `equipmentPlayer()`
- [ ] Implementar función `promotionPlayerTemplate()`
- [ ] Registrar en `ScriptLoader.cpp`

### 🧪 Fase 4: Testing
- [ ] Compilar y verificar errores
- [ ] Probar con Warrior Tank/DPS
- [ ] Probar con Paladin Tank/Heal/DPS
- [ ] Validar límites de cuenta
- [ ] Ajustar textos de Gossip

### 🔄 Fase 5: Expansión
- [ ] Añadir todas las clases restantes
- [ ] Poblar DB con todos los sets
- [ ] Optimizar consultas SQL
- [ ] Documentar en español los mensajes

### 🎯 Fase 6: Integración
- [ ] Decidir si reemplazar `custom_starter_pro.cpp`
- [ ] Integrar con sistema de primer personaje
- [ ] Testing final en servidor de desarrollo

---

## Notas Técnicas Adicionales

### Estructura Recomendada de Archivos

```
src/server/scripts/Custom/
├── custom_starter_pro.cpp          # Script de primer personaje
├── npc_icc_vendor.cpp              # Vendedor simple (obsoleto)
└── npc_promocion.cpp               # NUEVO: Sistema de promoción completo
```

### Orden de Slots en Query SQL

```cpp
// Orden de campos en SELECT
0:  head
1:  neck
2:  shoulders
3:  body
4:  chest
5:  waist
6:  legs
7:  feet
8:  wrists
9:  hands
10: finger1
11: finger2
12: trinket1
13: trinket2
14: back
15: mainhand
16: offhand
17: ranged
18: tabard
```

### Ejemplo de Mapeo Action → Spec

```cpp
// Warrior
#define ACTION_WARRIOR_TANK     1
#define ACTION_WARRIOR_DPS      2

// Paladin
#define ACTION_PALADIN_TANK     3
#define ACTION_PALADIN_HEAL     4
#define ACTION_PALADIN_DPS      5

// etc...
```

### Consulta para Insertar Log

```cpp
CharacterDatabase.PExecute(
    "INSERT INTO npc_promotion_log (accountId, accountName, characterName, ip) "
    "VALUES (%u, '%s', '%s', '%s')",
    accountId,
    accountName.c_str(),
    characterName.c_str(),
    ipAddress.c_str()
);
```

---

**Última Actualización:** 23 de Enero de 2026  
**Estado:** 📝 Documentación Completa - Listo para Fase 2 (Base de Datos)  
**Próximo Paso:** Validar IDs de items Tier 10 en la base de datos del servidor
