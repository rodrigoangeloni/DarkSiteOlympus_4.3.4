# Sistema de Promoción NPC - IMPLEMENTACIÓN COMPLETADA ✅

## 📋 Estado del Proyecto

### ✅ Fase 1: Documentación - COMPLETADA
- [x] Análisis completo del sistema AzerothCore
- [x] Arquitectura documentada en [NPC_PROMOCION.md](NPC_PROMOCION.md)
- [x] IDs de items Tier 10 validados en base de datos Cataclysm

### ✅ Fase 2: Base de Datos - COMPLETADA
- [x] Tabla `world.npc_promotion_items` creada
- [x] Tabla `characters.npc_promotion_log` creada
- [x] NPC 60003 "Maestro de Promoción" creado
- [x] **40 configuraciones** de equipamiento insertadas
- [x] **10 clases completas**: Warrior, Paladin, Hunter, Rogue, Priest, Death Knight, Shaman, Mage, Warlock, Druid
- [x] **Todos los roles**: Tank, DPS, Melee, Caster, Heal

### ✅ Fase 3: Script C++ - COMPLETADA
- [x] Archivo [npc_promocion.cpp](src/server/scripts/Custom/npc_promocion.cpp) creado
- [x] Menú Gossip dinámico por clase
- [x] Sistema de equipamiento desde base de datos
- [x] Promoción completa (nivel, oro, bolsas, monturas)
- [x] Control de uso: 1 vez por cuenta
- [x] Registro automático en base de datos
- [x] Mensajes personalizados en español

---

## 🚀 Guía de Instalación

### 1. Ejecutar Scripts SQL

```sql
-- En base de datos 'world'
SOURCE sql/CUSTOM/world/2026_01_23_00_npc_promotion_structure.sql;
SOURCE sql/CUSTOM/world/2026_01_23_03_npc_promotion_data_full.sql;

-- En base de datos 'characters'
SOURCE sql/CUSTOM/characters/2026_01_23_00_npc_promotion_log.sql;
```

### 2. Compilar el Core

```bash
cd build
cmake --build . --config RelWithDebInfo
```

El archivo `npc_promocion.cpp` se incluirá automáticamente gracias al `GLOB_RECURSE` en CMakeLists.txt.

### 3. Spawnear el NPC

Opción A - Comando en juego:
```
.npc add 60003
```

Opción B - SQL directo:
```sql
INSERT INTO creature (id, map, position_x, position_y, position_z, orientation)
VALUES (60003, 571, 5804.14, 624.77, 647.76, 1.64);
-- Coordenadas: Dalaran (Krasus' Landing)
```

---

## 📊 Estadísticas del Sistema

### Configuraciones por Clase

| Clase | Roles | Configs | Detalles |
|-------|-------|---------|----------|
| Warrior | 2 | 4 | Tank, DPS |
| Paladin | 3 | 6 | Tank, Holy, Retribution |
| Hunter | 1 | 2 | DPS |
| Rogue | 1 | 2 | DPS |
| Priest | 2 | 4 | Holy/Disc, Shadow |
| Death Knight | 2 | 4 | Blood, Frost/Unholy |
| Shaman | 3 | 6 | Elemental, Enhancement, Restoration |
| Mage | 1 | 2 | DPS |
| Warlock | 1 | 2 | DPS |
| Druid | 4 | 8 | Balance, Feral Tank, Feral DPS, Restoration |
| **TOTAL** | **22** | **40** | **20 por facción** |

### Equipamiento Otorgado

- **Tier 10 Normal** (ilvl 264): Sets completos
- **Accesorios ICC 25H** (ilvl 277): Collares, anillos, capas
- **Trinkets Cataclysm** (ilvl 277): Twilight Scales
- **Armas BiS ICC**: Glorenzelg, Trauma, Calamity's Grasp, etc.

---

## 🎮 Cómo Usar el Sistema

### Paso 1: Encontrar el NPC
Busca al **"Maestro de Promoción"** en:
- Dalaran (Krasus' Landing): coords `5804.14, 624.77, 647.76`
- O donde lo hayas spawneado

### Paso 2: Interactuar
Al hacer clic, verás un menú con las especializaciones disponibles para tu clase:

**Ejemplo - Paladin:**
- Paladín Tanque (Protection)
- Paladín Sanador (Holy)
- Paladín DPS (Retribution)

### Paso 3: Seleccionar Rol
Al elegir tu especialización, recibirás INMEDIATAMENTE:

✅ **Nivel 80** (con XP en 0 para nuevo nivel)  
✅ **10,000 de oro**  
✅ **Tier 10 completo** (Head, Shoulders, Chest, Hands, Legs)  
✅ **Accesorios ICC** (Neck, Rings, Trinkets, Back, Waist, Feet, Wrists)  
✅ **Armas y Off-hand apropiados** para tu rol  
✅ **4 bolsas de 22 slots** (Emblemático de Escarcha)  
✅ **Monturas de vuelo aprendidas** (75, 150, 280, 310)  
✅ **Skills al máximo** para nivel 80  
✅ **Proficiencias de armadura** (Plate/Mail según clase)  

### Paso 4: ¡Listo!
Puedes ir directamente a raids, arenas o dungeons.

---

## ⚙️ Configuración Avanzada

### Modificar Nivel de Promoción

Editar en `npc_promocion.cpp`:

```cpp
#define PROMOTION_LEVEL         85  // Cambiar a 85 para Cataclysm endgame
```

### Modificar Oro Otorgado

```cpp
#define PROMOTION_MONEY         5000 * GOLD  // 50,000 de oro
```

### Permitir Múltiples Usos

```cpp
#define PROMOTION_LIMIT         3  // Permite 3 promociones por cuenta
```

### Cambiar Bolsas

```cpp
#define BAG_ID                  41599  // Item ID de la bolsa
```

### Modificar Equipamiento

Editar directamente en la base de datos:

```sql
UPDATE npc_promotion_items 
SET mainhand = 50070, offhand = 50616
WHERE class = 2 AND function = 'heal';
```

---

## 📁 Archivos del Sistema

```
DarkSiteOlympus_4.3.4/
├── sql/CUSTOM/
│   ├── world/
│   │   ├── 2026_01_23_00_npc_promotion_structure.sql  # Tablas + NPC
│   │   ├── 2026_01_23_01_npc_promotion_validation.sql # Consultas de validación
│   │   └── 2026_01_23_03_npc_promotion_data_full.sql  # 40 configuraciones
│   └── characters/
│       └── 2026_01_23_00_npc_promotion_log.sql        # Tabla de log
│
├── src/server/scripts/Custom/
│   └── npc_promocion.cpp                              # Script C++ (685 líneas)
│
└── NPC_PROMOCION.md                                    # Documentación técnica completa
    NPC_PROMOCION_README.md                             # Esta guía
```

---

## 🔍 Consultas SQL Útiles

### Ver todas las promociones realizadas

```sql
SELECT 
    accountName, 
    characterName, 
    CASE class 
        WHEN 1 THEN 'Warrior' WHEN 2 THEN 'Paladin' WHEN 3 THEN 'Hunter'
        WHEN 4 THEN 'Rogue' WHEN 5 THEN 'Priest' WHEN 6 THEN 'Death Knight'
        WHEN 7 THEN 'Shaman' WHEN 8 THEN 'Mage' WHEN 9 THEN 'Warlock'
        WHEN 11 THEN 'Druid'
    END as Clase,
    spec,
    ip,
    date 
FROM characters.npc_promotion_log 
ORDER BY date DESC;
```

### Ver todos los boost automáticos de primer personaje

```sql
SELECT 
    accountId,
    characterName,
    date
FROM characters.first_char_boost_log
ORDER BY date DESC;
```

### Estadísticas de uso por clase

```sql
SELECT 
    CASE class 
        WHEN 1 THEN 'Warrior' WHEN 2 THEN 'Paladin' WHEN 3 THEN 'Hunter'
        WHEN 4 THEN 'Rogue' WHEN 5 THEN 'Priest' WHEN 6 THEN 'Death Knight'
        WHEN 7 THEN 'Shaman' WHEN 8 THEN 'Mage' WHEN 9 THEN 'Warlock'
        WHEN 11 THEN 'Druid'
    END as Clase,
    spec,
    COUNT(*) as Total
FROM characters.npc_promotion_log 
GROUP BY class, spec
ORDER BY Total DESC;
```

### Ver equipamiento de una clase/rol específico

```sql
SELECT * FROM world.npc_promotion_items 
WHERE class = 1 AND faction = 0 AND `function` = 'tank';
```

---

## 🔧 Administración y Mantenimiento

### 🔄 Resetear Sistema de Promoción (NPC 60003)

Si necesitas permitir que una cuenta use nuevamente el NPC de promoción:

```sql
-- Resetear promoción de una cuenta específica
DELETE FROM characters.npc_promotion_log 
WHERE accountId = 123;  -- Cambiar por el ID de cuenta real
```

**Verificar antes de resetear:**
```sql
SELECT * FROM characters.npc_promotion_log WHERE accountId = 123;
```

### 🔄 Resetear Boost de Primer Personaje (custom_starter_pro)

Si necesitas permitir que una cuenta reciba nuevamente el boost automático al crear un personaje:

```sql
-- Resetear boost automático de una cuenta específica
DELETE FROM characters.first_char_boost_log 
WHERE accountId = 123;  -- Cambiar por el ID de cuenta real
```

**Verificar antes de resetear:**
```sql
SELECT * FROM characters.first_char_boost_log WHERE accountId = 123;
```

### 🔄 Resetear AMBOS Sistemas (Completo)

```sql
-- Resetear ambos sistemas para una cuenta
DELETE FROM characters.npc_promotion_log WHERE accountId = 123;
DELETE FROM characters.first_char_boost_log WHERE accountId = 123;
```

### 📊 Obtener Account ID de un Personaje

Si solo tienes el nombre del personaje:

```sql
SELECT guid, name, account, class, race, level
FROM characters.characters
WHERE name = 'NombreDelPersonaje';
```

### 🧹 Limpieza Masiva (Usar con precaución)

```sql
-- Resetear TODAS las promociones (permitir que todos usen el sistema de nuevo)
TRUNCATE TABLE characters.npc_promotion_log;
TRUNCATE TABLE characters.first_char_boost_log;
```

⚠️ **ADVERTENCIA:** Esto borrará TODOS los registros. Solo usar para:
- Testing en servidor de desarrollo
- Reset completo del servidor
- Después de un rollback de personajes

### 📈 Estadísticas Generales

```sql
-- Total de cuentas que usaron el sistema
SELECT 
    'Promociones NPC' as Sistema,
    COUNT(DISTINCT accountId) as CuentasUnicas,
    COUNT(*) as UsosTotal
FROM characters.npc_promotion_log
UNION ALL
SELECT 
    'Boost Automático' as Sistema,
    COUNT(DISTINCT accountId) as CuentasUnicas,
    COUNT(*) as UsosTotal
FROM characters.first_char_boost_log;
```

### 🔍 Auditoría: Ver qué cuenta usó qué sistema

```sql
SELECT 
    p.accountId,
    p.accountName,
    'NPC Promoción' as TipoBoost,
    p.characterName,
    p.spec as Detalle,
    p.date
FROM characters.npc_promotion_log p
UNION ALL
SELECT 
    f.accountId,
    'N/A' as accountName,
    'Boost Automático' as TipoBoost,
    f.characterName,
    'Nivel 80 Auto' as Detalle,
    f.date
FROM characters.first_char_boost_log f
ORDER BY date DESC;
```

---

## 🐛 Troubleshooting

### El NPC no aparece en el juego
**Solución:**
1. Verificar que el SQL se ejecutó correctamente
2. Ejecutar `.npc add 60003` en el juego
3. Verificar en DB: `SELECT * FROM creature WHERE id = 60003`

### El NPC no responde al hacer clic
**Solución:**
1. Verificar que `npcflag = 1` en `creature_template`
2. Verificar que `ScriptName = 'npc_promocion'` (exactamente)
3. Recompilar y reiniciar worldserver

### Items no se equipan
**Solución:**
1. Ejecutar consultas de validación: `2026_01_23_01_npc_promotion_validation.sql`
2. Verificar que los IDs existen en `item_template`:
   ```sql
   SELECT entry, name FROM item_template WHERE entry IN (51218, 51210, 51219, 51216, 51217);
   ```
3. Si faltan items, reemplazarlos en `npc_promotion_items`

### "Ya has usado tu promoción"
**Causa:** El sistema detectó un registro en `npc_promotion_log` para tu cuenta.

**Solución:**
```sql
-- Ver tus registros
SELECT * FROM characters.npc_promotion_log WHERE accountId = TU_ACCOUNT_ID;

-- Eliminar para permitir otra promoción
DELETE FROM characters.npc_promotion_log WHERE accountId = TU_ACCOUNT_ID;
```

### El boost automático no funciona en mi primer personaje
**Causa:** La cuenta ya recibió el boost anteriormente con otro personaje.

**Solución:**
```sql
-- Verificar si ya se usó
SELECT * FROM characters.first_char_boost_log WHERE accountId = TU_ACCOUNT_ID;

-- Si quieres resetear
DELETE FROM characters.first_char_boost_log WHERE accountId = TU_ACCOUNT_ID;
```

### Un personaje quedó a nivel 80 sin equipamiento
**Causa:** Recibió el boost automático de `custom_starter_pro` pero no usó el NPC de promoción.

**Solución:** Simplemente habla con el NPC 60003 "Maestro de Promoción" para obtener el equipamiento completo.

### Error de compilación: "ScriptPCH.h not found"
**Solución:**
Reemplazar en `npc_promocion.cpp`:
```cpp
// Cambiar esto:
#include "ScriptPCH.h"

// Por esto:
#include "ScriptMgr.h"
#include "Player.h"
#include "AccountMgr.h"
#include "Chat.h"
```

### El jugador recibe nivel pero no equipamiento
**Causa:** Probablemente un error en la consulta SQL.

**Solución:**
1. Verificar logs del worldserver
2. Verificar que la tabla tiene datos:
   ```sql
   SELECT COUNT(*) FROM world.npc_promotion_items;
   -- Debe retornar 40
   ```
3. Ejecutar manualmente la query para debug:
   ```sql
   SELECT * FROM npc_promotion_items 
   WHERE class = 1 AND faction = 0 AND `function` = 'dps';
   ```

---

## 📝 Notas Técnicas

### Sistema Dual de Boost

El servidor implementa **DOS sistemas complementarios**:

#### 1️⃣ **Boost Automático** (`custom_starter_pro.cpp`)
- **Trigger:** OnLogin de personaje nivel 1
- **Condición:** Primera vez que la cuenta crea un personaje
- **Efecto:** 
  - Nivel 80 instantáneo
  - Teletransporte a ciudad capital
  - Mensaje de bienvenida
- **Sin equipamiento** (solo nivel)
- **Control:** `characters.first_char_boost_log` (1 uso por cuenta)

#### 2️⃣ **Promoción Manual** (`npc_promocion.cpp`)
- **Trigger:** Interacción con NPC 60003
- **Condición:** Nivel < 80, no haber usado la promoción antes
- **Efecto:**
  - Nivel 80
  - Equipamiento completo Tier 10
  - 10,000 oro
  - Bolsas, monturas, skills
- **Control:** `characters.npc_promotion_log` (1 uso por cuenta)

#### 🔀 Flujo Recomendado:
```
1. Crear personaje → custom_starter_pro → Nivel 80 (auto)
2. Hablar con NPC 60003 → npc_promocion → Equipamiento completo
3. ¡Listo para endgame!
```

### Slots de Equipamiento
```cpp
EQUIPMENT_SLOT_HEAD      = 0   // Cabeza
EQUIPMENT_SLOT_NECK      = 1   // Cuello
EQUIPMENT_SLOT_SHOULDERS = 2   // Hombros
EQUIPMENT_SLOT_BODY      = 3   // Camisa
EQUIPMENT_SLOT_CHEST     = 4   // Pecho
EQUIPMENT_SLOT_WAIST     = 5   // Cintura
EQUIPMENT_SLOT_LEGS      = 6   // Piernas
EQUIPMENT_SLOT_FEET      = 7   // Pies
EQUIPMENT_SLOT_WRISTS    = 8   // Muñecas
EQUIPMENT_SLOT_HANDS     = 9   // Manos
EQUIPMENT_SLOT_FINGER1   = 10  // Anillo 1
EQUIPMENT_SLOT_FINGER2   = 11  // Anillo 2
EQUIPMENT_SLOT_TRINKET1  = 12  // Trinket 1
EQUIPMENT_SLOT_TRINKET2  = 13  // Trinket 2
EQUIPMENT_SLOT_BACK      = 14  // Espalda
EQUIPMENT_SLOT_MAINHAND  = 15  // Mano principal
EQUIPMENT_SLOT_OFFHAND   = 16  // Mano secundaria
EQUIPMENT_SLOT_RANGED    = 17  // A distancia
EQUIPMENT_SLOT_TABARD    = 18  // Tabardo
```

### IDs de Monturas por Raza
Ver código completo en `npc_promocion.cpp` líneas 170-225.

### Base de Datos
- **world.npc_promotion_items**: 19 columnas (slots) + 3 PK (class, faction, function)
- **characters.npc_promotion_log**: 9 columnas con índices en accountId, characterGuid, ip, date
- **characters.first_char_boost_log**: 5 columnas con UNIQUE en accountId (garantiza 1 boost por cuenta)

---

## 🎯 Roadmap Futuro (Opcional)

- [ ] Añadir Tier 10 Heroic (ilvl 277) como opción premium
- [ ] Sistema de re-equipamiento para personajes ya 80
- [ ] Integrar con sistema de donaciones
- [ ] Añadir glyphs y gems automáticamente
- [ ] Menú de teletransporte post-promoción
- [ ] Estadísticas web de uso

---

## 📄 Licencia y Créditos

- **Sistema Original**: [mod-npc-promotion](https://github.com/pangolp/mod-npc-promotion) (AzerothCore)
- **Adaptación**: TrinityCore Cataclysm 4.3.4
- **Base de Datos**: DarkSiteOlympus 4.3.4
- **Implementación**: 23 de Enero de 2026
- **Licencia**: GNU AGPL v3

---

## ✅ Checklist Final

- [x] SQL ejecutado correctamente
- [x] Core compilado sin errores
- [x] NPC spawneado en el juego
- [x] Probado con al menos 1 clase
- [x] Verificado que el log se registra correctamente
- [x] Equipamiento aplicado correctamente
- [x] Monturas aprendidas
- [x] Skills actualizadas

**¡El sistema está listo para producción!** 🎉
