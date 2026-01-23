-- =============================================================================
-- ESTRUCTURA DE TABLAS PARA SISTEMA DE PROMOCIÓN NPC
-- Base de Datos: world
-- =============================================================================

-- Tabla para almacenar los items de equipamiento por clase/facción/rol
DROP TABLE IF EXISTS `npc_promotion_items`;
CREATE TABLE `npc_promotion_items` (
    `class` INT NOT NULL COMMENT 'ID de clase (1=Warrior, 2=Paladin, 3=Hunter, etc.)',
    `faction` INT NOT NULL COMMENT '0=Alianza, 1=Horda',
    `function` VARCHAR(50) NOT NULL COMMENT 'tank, dps, heal, caster, melee',
    `head` INT UNSIGNED DEFAULT 0,
    `neck` INT UNSIGNED DEFAULT 0,
    `shoulders` INT UNSIGNED DEFAULT 0,
    `body` INT UNSIGNED DEFAULT 0 COMMENT 'Camisa (raramente usado)',
    `chest` INT UNSIGNED DEFAULT 0,
    `waist` INT UNSIGNED DEFAULT 0,
    `legs` INT UNSIGNED DEFAULT 0,
    `feet` INT UNSIGNED DEFAULT 0,
    `wrists` INT UNSIGNED DEFAULT 0,
    `hands` INT UNSIGNED DEFAULT 0,
    `finger1` INT UNSIGNED DEFAULT 0,
    `finger2` INT UNSIGNED DEFAULT 0,
    `trinket1` INT UNSIGNED DEFAULT 0,
    `trinket2` INT UNSIGNED DEFAULT 0,
    `back` INT UNSIGNED DEFAULT 0,
    `mainhand` INT UNSIGNED DEFAULT 0,
    `offhand` INT UNSIGNED DEFAULT 0,
    `ranged` INT UNSIGNED DEFAULT 0,
    `tabard` INT UNSIGNED DEFAULT 0,
    PRIMARY KEY (`class`, `faction`, `function`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Items de promoción por clase/facción/rol';

-- =============================================================================
-- NPC DE PROMOCIÓN EN CREATURE_TEMPLATE
-- =============================================================================

SET @NPC_ENTRY := 60003;

DELETE FROM `creature_template` WHERE `entry` = @NPC_ENTRY;
INSERT INTO `creature_template` (
    `entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, 
    `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, 
    `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, 
    `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, 
    `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, 
    `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, 
    `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, 
    `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, 
    `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, 
    `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, 
    `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, 
    `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, 
    `HealthModifier`, `ManaModifier`, `ArmorModifier`, `DamageModifier`, 
    `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, 
    `MechanicImmuneMask`, `flags_extra`, `ScriptName`, `VerifiedBuild`
) VALUES (
    @NPC_ENTRY, 0, 0, 0, 
    0, 0, 25593, 0, 0, 0,  -- modelid1: Humano noble masculino
    'Maestro de Promoción', 'Equipamiento Inicial', '', 0, 80, 80, 
    2, 35, 1, 1, 1.14286, 1.2,  -- npcflag 1 = Gossip
    0, 0, 2000, 2000, 1, 
    1, 1, 0, 0, 0, 
    0, 0, 0, 0, 0, 
    7, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 
    '', 0, 3, 1, 
    1, 1, 1, 1, 
    1, 0, 0, 1, 
    0, 0, 'npc_promocion', 0
);

-- =============================================================================
-- NOTAS DE IMPLEMENTACIÓN
-- =============================================================================
/*
1. La tabla npc_promotion_items almacena configuraciones de equipo para cada combinación de:
   - Clase (1-11, excepto 10)
   - Facción (0=Alianza, 1=Horda)
   - Función/Rol (tank, dps, heal, caster, melee)

2. El NPC (entry 60003) está configurado con:
   - npcflag = 1 (solo Gossip, no vendor)
   - ScriptName = 'npc_promocion' (debe coincidir con el nombre en el .cpp)
   - faction = 35 (neutral amistoso)
   - ModelID 25593 (humano noble, se puede cambiar)

3. Para spawnear el NPC en el juego, usa:
   .npc add 60003

4. La tabla npc_promotion_log se crea en la base de datos 'characters' (ver archivo separado)

5. Los datos de ejemplo (Warrior/Paladin) están en archivo separado para pruebas
*/
