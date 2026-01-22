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
