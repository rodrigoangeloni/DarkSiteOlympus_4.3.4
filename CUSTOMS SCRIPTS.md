# Scripts Custom en OlympusCore/Darkside

Este documento detalla los scripts personalizados disponibles en la carpeta `src/server/scripts/Custom`, sus IDs recomendados y **cómo utilizarlos**.

## 1. NPCs Interactivos
Para usar estos scripts, busca su `entry` (ID) en la base de datos o crea un nuevo NPC asignándole el `ScriptName` exacto.

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

## 2. Items Especiales & Level Up

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
1.  Asegúrate de que la función de carga (ej: `AddSC_npc_teleport`) esté llamada en `src/server/game/Scripting/ScriptLoader.cpp`.
2.  Recompila el `worldserver`.
3.  Asegúrate de tener los NPCs creados en la base de datos `world.creature_template` apuntando al `ScriptName` correcto.
