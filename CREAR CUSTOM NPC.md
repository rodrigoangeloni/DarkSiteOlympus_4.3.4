# Guía para crear NPCs Custom (C++) en OlympusCore

1. **Crear el Script C++**:
   - Crear un archivo `.cpp` en `src/server/scripts/Custom/` (ej: `npc_mi_npc.cpp`).
   - Definir la clase heredando de `CreatureScript`.
   - Asignar un nombre de script único en el constructor (ej: `"npc_mi_npc"`).
   - Implementar la lógica (OnGossipHello, OnGossipSelect, etc).
   - Al final del archivo, crear la función de carga: `void AddSC_npc_mi_npc() { new npc_mi_npc(); }`.

2. **Registrar en ScriptLoader**:
   - Abrir `src/server/game/Scripting/ScriptLoader.cpp`.
   - Declarar la función al inicio (zona de Custom): `void AddSC_npc_mi_npc();`.
   - Llamar a la función dentro de `void AddCustomScripts()` al final del archivo.

3. **Crear el NPC en la Base de Datos**:
   - Insertar una fila en `creature_template` usando un ID disponible (ej: 99001).
   - Asignar el nombre exacto del script en la columna `ScriptName` (ej: `'npc_mi_npc'`).
   - Usar un `modelid` válido (ej: 19 para humano).

4. **Compilar y Ejecutar**:
   - Recompilar la solución (Build worldserver).
   - Ejecutar el SQL en la DB `world`.
   - Reiniciar servidor o recargar caché (`.reload creature_template [ID]`) si el SQL se puso con el server on.
   - Spawnearlo: `.npc add [ID]`.

---

## Ejemplo Completo: Sistema de Promoción (npc_promocion.cpp)

El script `npc_promocion.cpp` es un ejemplo avanzado de NPC custom que implementa:

### Características:
*   **Menú Gossip dinámico** según la clase del jugador (10 clases, 22 especializaciones)
*   **Equipamiento desde base de datos** (`world.npc_promotion_items`)
*   **Control de uso** (1 vez por cuenta)
*   **Registro de actividad** (`characters.npc_promotion_log`)
*   **Promoción completa**: Nivel 80 + Tier 10 + oro + bolsas + monturas

### Código Clave:

```cpp
class npc_promocion : public CreatureScript
{
public:
    npc_promocion() : CreatureScript("npc_promocion") { }

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        // Verificar elegibilidad
        uint32 accountId = player->GetSession()->GetAccountId();
        uint8 promotionCount = GetAccountPromotionCount(accountId);
        
        if (promotionCount >= 1) {
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Ya usaste tu promoción", 0, 100);
            SendGossipMenuFor(player, 1, creature->GetGUID());
            return true;
        }
        
        // Menú dinámico según clase
        switch (player->getClass()) {
            case CLASS_WARRIOR:
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Guerrero Tanque", 0, 1);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Guerrero DPS", 0, 2);
                break;
            // ... más clases
        }
        
        SendGossipMenuFor(player, 1, creature->GetGUID());
        return true;
    }
    
    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
    {
        // Aplicar promoción
        player->GiveLevel(80);
        player->ModifyMoney(10000 * GOLD);
        EquipPlayerGear(player, GetRoleFromAction(action));
        AddPromotionLog(player, GetRoleFromAction(action));
        
        CloseGossipMenuFor(player);
        return true;
    }
};

void AddSC_npc_promocion() { new npc_promocion(); }
```

### Base de Datos:

```sql
-- NPC en creature_template
INSERT INTO creature_template (entry, modelid1, name, subname, ScriptName, npcflag, faction_A, faction_H)
VALUES (60003, 25593, 'Maestro de Promoción', 'Equipamiento Inicial', 'npc_promocion', 1, 35, 35);

-- Tabla de items
CREATE TABLE npc_promotion_items (
    class INT NOT NULL,
    faction INT NOT NULL,
    `function` VARCHAR(50) NOT NULL,
    head INT, neck INT, shoulders INT, chest INT, /* ... más slots ... */
    PRIMARY KEY (class, faction, `function`)
);

-- Tabla de log
CREATE TABLE npc_promotion_log (
    id INT AUTO_INCREMENT PRIMARY KEY,
    accountId INT NOT NULL,
    characterName VARCHAR(255),
    class TINYINT,
    spec VARCHAR(50),
    date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
```

### Ventajas de este Diseño:
*   ✅ **Escalable**: Añadir nuevas clases solo requiere editar la DB
*   ✅ **Auditable**: Todo uso queda registrado
*   ✅ **Reutilizable**: El patrón se puede aplicar a otros NPCs
*   ✅ **Mantenible**: Cambiar equipamiento no requiere recompilar

### Documentación Completa:
Ver `NPC_PROMOCION_README.md` y `NPC_PROMOCION.md` para detalles técnicos completos.

## Estructura de Base de Datos (OlympusCore / Cataclysm)

Al crear el SQL para `creature_template`, ten en cuenta que tu base de datos tiene algunas columnas con nombres diferentes al estándar de Trinity/AzerothCore.

**Columnas Importantes:**

*   **entry**: ID único del NPC (ej: 99000).
*   **modelid1**: ID del modelo visual (ej: 19 = Humano).
*   **name**: Nombre del NPC.
*   **subname**: Título o subtítulo (ej: "Vendedor Custom").
*   **minlevel / maxlevel**: Nivel del NPC.
*   **faction_A / faction_H**: Facción para Alianza y Horda (Usar 35 para amistoso con ambos). **Nota:** Algunos cores usan solo `faction` o `faction_A/H`. En tu caso son dos columnas separadas.
*   **npcflag**: Flags de interacción (1 = Gossip/Hablar, 128 = Vendedor, etc). Para menú custom usa 1 (Gossip).
*   **ScriptName**: **CRUCIAL**. Debe coincidir exactamente con el nombre en el `.cpp` (`"npc_mi_npc"`).

**Diferencias específicas de tu DB:**

*   Usa `Health_mod`, `Mana_mod`, `Armor_mod` (en lugar de `HealthModifier`, etc).
*   Usa `faction_A` y `faction_H` (en lugar de una sola `faction`).
*   Incluye columnas extra como `exp_unk`, `currencyId`, `questItem1`...`questItem6`, `WDBVerified`.

**Plantilla SQL Básica:**

```sql
INSERT INTO `creature_template` 
(`entry`, `modelid1`, `name`, `subname`, `minlevel`, `maxlevel`, `faction_A`, `faction_H`, `npcflag`, `ScriptName`, `Health_mod`, `Mana_mod`, `Armor_mod`, `rank`, `unit_class`, `unit_flags`, `type`) 
VALUES 
(99001, 19, 'Mi NPC Custom', 'Titulo', 80, 80, 35, 35, 1, 'npc_mi_npc', 1, 1, 1, 0, 1, 0, 7);
```
*(Asegúrate de rellenar el resto de columnas obligatorias con 0 si usas un INSERT completo)*
