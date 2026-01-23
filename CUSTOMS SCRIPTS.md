# Scripts Custom en OlympusCore/Darkside

Este documento detalla los scripts personalizados disponibles en la carpeta `src/server/scripts/Custom`, sus IDs recomendados y **cómo utilizarlos**.

## 1. NPCs Interactivos
Para usar estos scripts, busca su `entry` (ID) en la base de datos o crea un nuevo NPC asignándole el `ScriptName` exacto.

### `npc_promocion.cpp` (Sistema de Promoción Completo) ⭐ NUEVO
*   **ScriptName:** `"npc_promocion"`
*   **NPC ID:** `60003`
*   **Base de Datos:**
    *   `world.npc_promotion_items` - 40 configuraciones de equipamiento
    *   `characters.npc_promotion_log` - Registro de uso
*   **Requisitos:** Nivel menor a 80, 1 uso por cuenta
*   **Función:** Sistema completo de "Instant 80" con equipamiento Tier 10 (ilvl 264) automático
*   **Características:**
    *   ✅ Sube al nivel **80** instantáneamente
    *   ✅ Entrega **10,000 de oro**
    *   ✅ Equipa **Tier 10 Normal completo** + accesorios ICC 25H (ilvl 277)
    *   ✅ **4 bolsas** de 22 slots (Emblemático de Escarcha)
    *   ✅ Enseña todas las **monturas de vuelo** (75, 150, 280, 310)
    *   ✅ Actualiza **skills al máximo** para nivel 80
    *   ✅ Proficiencias de armadura (Plate/Mail según clase)
    *   ✅ **Menú dinámico** según clase (10 clases, 22 especializaciones)
    *   ✅ Control de uso: **1 vez por cuenta**
    *   ✅ Registro completo en base de datos
*   **Clases Soportadas:** Warrior (Tank/DPS), Paladin (Tank/Heal/DPS), Hunter (DPS), Rogue (DPS), Priest (Heal/DPS), Death Knight (Tank/DPS), Shaman (Caster/Melee/Heal), Mage (DPS), Warlock (DPS), Druid (Caster/Tank/Melee/Heal)
*   **Uso:** Hablar con el NPC → Seleccionar especialización → Recibir promoción completa
*   **Documentación:** Ver `NPC_PROMOCION_README.md`

### `npc_heirloom.cpp` (Vendedor de Reliquias)
*   **ScriptName:** `"npc_heirloom"`
*   **NPC ID recomendado:** `99000`
*   **Función:** Vendedor de reliquias categorizado (Armas, Placas, Malla, etc.) y abalorios PvP con detección de facción.
*   **Uso:** Hablar con el NPC y seleccionar categorías. Entrega ítems gratis.

### `npc_change_racial.cpp` (Cambio de Raciales)
*   **ScriptName:** `"npc_change_racial_traits"`
*   **NPC ID sugerido:** `3880002` (Según código fuente)
*   **Función:** Permite aprender las habilidades raciales de otra raza diferente a la tuya (ej: Orco con racial de Humano).
*   **Uso:** Hablar con el NPC y seleccionar la raza deseada.

### `npc_teleport.cpp` (Teletransportador)
*   **ScriptName:** `"npc_teleport"`
*   **NPC ID:** (Buscar en DB o crear uno nuevo).
*   **Función:** Teletransportador global a ciudades, zonas de leveo, mazmorras y zonas PvP.

### `npc_profession.cpp` (Auto-Profesiones)
*   **ScriptName:** `"npc_profession"`
*   **NPC ID:** (Buscar en DB o crear uno nuevo).
*   **Requisitos:**
    *   Nivel jugador: **80+**
    *   Costo: **1x Token de Profesión** (Item ID: `100605`).
*   **Función:** Sube instantáneamente una profesión al máximo (525) y aprende todas las recetas.

### `transmogrifier_npc.cpp` (Transfigurador)
*   **ScriptName:** `"Transmogrifier_NPC"`
*   **Función:** Sistema visual para cambiar la apariencia del equipo.
*   **Uso:** Al hablarle abre un menú especial donde colocas el objeto base y el objeto de apariencia. Requiere tener habilitado `Transmogrification.Enable` en la configuración.

### `Class_coins.cpp` (Tienda de Clase)
*   **ScriptName:** `"class_coins"`
*   **NPC ID:** (Buscar en DB).
*   **Función:** Vendedor especial que usa una moneda custom (almacenada en tabla `class_coins`) para vender "Tokens de Compra" (ID 51003).

### `bug_dual.cpp` (Fix Doble Especialización)
*   **ScriptName:** `"bug_dual"`
*   **Función:** Arregla personajes que no pueden cambiar de talentos debido a bugs.

---

## 2. Scripts de Jugador (Pasivos)

### `custom_starter_pro.cpp` (Primer Personaje Nivel 80) ⭐
*   **Tipo:** Script de Jugador (Pasivo, se ejecuta en OnLogin)
*   **Función:** Detecta el **primer personaje** creado en una cuenta y lo sube automáticamente a nivel **80**
*   **Requisitos:** 
    *   Ser nivel 1 (primer login del personaje)
    *   Ser el primer personaje de la cuenta
*   **Efecto:**
    1.  Sube a nivel **80** instantáneamente
    2.  Teletransporta a ciudad capital según facción (Stormwind/Orgrimmar)
    3.  Envía mensaje de bienvenida
*   **Nota:** Este sistema es complementario al `npc_promocion.cpp`. Sube a nivel 80 pero NO da equipamiento. Los jugadores deben usar el NPC de Promoción para obtener gear completo.

### `level_up.cpp` (Boost Instantáneo 85)
**¡ATENCIÓN!** Este script no es pasivo. Funciona al **USAR** ciertos ítems especiales.
*   **Items Activadores:** `100594`, `100595`, `100596`, `100597`, `100598`, `100599`.
*   **Efecto:**
    1.  Sube al jugador a nivel **85** instantáneamente.
    2.  Envía por **Correo** un set completo de equipo según Clase y Especialización.
    3.  Pide seleccionar talentos si eres nivel bajo.

### `custom_arena_reward.cpp` (Premio PvP)
*   **Tipo:** Script de Jugador (Pasivo).
*   **Función:** Otorga un premio al matar jugadores en Arenas.
*   **Premio:** 1x Item ID `920019` (Bloody Badge / Configurable).
*   **Límite:** Basado en el tamaño del equipo de arena (2v2 = max 2 premios, etc).

---

## 3. Comandos de Chat

### `.world <mensaje>`
*   **Script:** `world_chat.cpp`
*   **Función:** Chat global visible para todo el servidor. Muestra rangos y colores de clase.

### `.cleanchardb <FECHA>`
*   **Script:** `command_clean_character.cpp`
*   **Restricción:** Solo permitido para el Account ID **15867**.
*   **Función:** Borra personajes inactivos antes de la fecha dada.

### `.transfer <GUID> <ACC_ID>`
*   **Script:** `command_transfer.cpp`
*   **Función:** Transfiere un personaje a otra cuenta.

---

## Cómo activar estos scripts
1.  Asegúrate de que la función de carga (ej: `AddSC_npc_teleport`, `AddSC_npc_promocion`) esté llamada en `src/server/game/Scripting/ScriptLoader.cpp`.
2.  Recompila el `worldserver`.
3.  Asegúrate de tener los NPCs creados en la base de datos `world.creature_template` apuntando al `ScriptName` correcto.

## Sistema de Promoción vs Primer Personaje

### Flujo Recomendado para Nuevos Jugadores:
1.  **Crear primer personaje** → `custom_starter_pro.cpp` lo sube a **nivel 80** automáticamente
2.  **Hablar con NPC 60003** (Maestro de Promoción) → `npc_promocion.cpp` equipa **Tier 10 completo** + oro + bolsas + monturas
3.  **¡Listo para endgame!** - El jugador puede ir directamente a ICC, arenas o dungeons

### Diferencias Clave:
*   **custom_starter_pro.cpp**: Solo nivel 80, sin equipamiento
*   **npc_promocion.cpp**: Equipamiento completo + recursos, pero requiere interacción con NPC
