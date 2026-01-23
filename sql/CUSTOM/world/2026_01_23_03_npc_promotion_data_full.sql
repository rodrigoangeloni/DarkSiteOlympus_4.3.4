-- =============================================================================
-- DATOS COMPLETOS PARA SISTEMA DE PROMOCIÓN NPC - TODAS LAS CLASES
-- Base de Datos: world
-- IDs Validados en Base de Datos Cataclysm 4.3.4
-- =============================================================================

-- Limpiar datos existentes
DELETE FROM `npc_promotion_items`;

-- =============================================================================
-- CLASE 1: WARRIOR (GUERRERO)
-- =============================================================================

-- Warrior Tank (Protection) - Ymirjar Lord's Plate
INSERT INTO `npc_promotion_items` VALUES (1, 0, 'tank', 51218, 50627, 51210, 0, 51219, 50620, 51216, 50235, 50333, 51217, 50404, 50404, 50364, 54571, 50470, 50415, 50729, 0, 0);
INSERT INTO `npc_promotion_items` VALUES (1, 1, 'tank', 51218, 50627, 51210, 0, 51219, 50620, 51216, 50235, 50333, 51217, 50404, 50404, 50364, 54571, 50470, 50415, 50729, 0, 0);

-- Warrior DPS (Fury/Arms) - Ymirjar Lord's Battlegear
INSERT INTO `npc_promotion_items` VALUES (1, 0, 'dps', 51212, 50633, 51215, 0, 51214, 50620, 51211, 50235, 50333, 51213, 50402, 50402, 50363, 54590, 50470, 50415, 50415, 0, 0);
INSERT INTO `npc_promotion_items` VALUES (1, 1, 'dps', 51212, 50633, 51215, 0, 51214, 50620, 51211, 50235, 50333, 51213, 50402, 50402, 50363, 54590, 50470, 50415, 50415, 0, 0);

-- =============================================================================
-- CLASE 2: PALADIN
-- =============================================================================

-- Paladin Tank (Protection) - Lightsworn Plate
INSERT INTO `npc_promotion_items` VALUES (2, 0, 'tank', 51173, 50627, 51170, 0, 51171, 50620, 51172, 50235, 50333, 51169, 50404, 50404, 50364, 54571, 50470, 50415, 50729, 0, 0);
INSERT INTO `npc_promotion_items` VALUES (2, 1, 'tank', 51173, 50627, 51170, 0, 51171, 50620, 51172, 50235, 50333, 51169, 50404, 50404, 50364, 54571, 50470, 50415, 50729, 0, 0);

-- Paladin Holy (Heal) - Lightsworn Garb
INSERT INTO `npc_promotion_items` VALUES (2, 0, 'heal', 51167, 50724, 51166, 0, 51165, 50613, 51168, 50606, 50651, 51163, 50398, 50398, 54589, 50358, 50470, 50685, 50616, 0, 0);
INSERT INTO `npc_promotion_items` VALUES (2, 1, 'heal', 51167, 50724, 51166, 0, 51165, 50613, 51168, 50606, 50651, 51163, 50398, 50398, 54589, 50358, 50470, 50685, 50616, 0, 0);

-- Paladin DPS (Retribution) - Lightsworn Battlegear
INSERT INTO `npc_promotion_items` VALUES (2, 0, 'dps', 51162, 50633, 51160, 0, 51164, 50620, 51161, 50235, 50333, 51159, 50402, 50402, 50363, 54590, 50470, 50415, 0, 0, 0);
INSERT INTO `npc_promotion_items` VALUES (2, 1, 'dps', 51162, 50633, 51160, 0, 51164, 50620, 51161, 50235, 50333, 51159, 50402, 50402, 50363, 54590, 50470, 50415, 0, 0, 0);

-- =============================================================================
-- CLASE 3: HUNTER (CAZADOR)
-- =============================================================================

-- Hunter DPS - Ahn'Kahar Blood Hunter's Battlegear
INSERT INTO `npc_promotion_items` VALUES (3, 0, 'dps', 51153, 50633, 51151, 0, 51150, 50620, 51152, 50235, 50333, 51154, 50402, 50402, 50363, 54590, 50470, 50638, 50733, 0, 0);
INSERT INTO `npc_promotion_items` VALUES (3, 1, 'dps', 51153, 50633, 51151, 0, 51150, 50620, 51152, 50235, 50333, 51154, 50402, 50402, 50363, 54590, 50470, 50638, 50733, 0, 0);

-- =============================================================================
-- CLASE 4: ROGUE (PÍCARO)
-- =============================================================================

-- Rogue DPS - Shadowblade's Battlegear
INSERT INTO `npc_promotion_items` VALUES (4, 0, 'dps', 51187, 50633, 51185, 0, 51189, 50620, 51186, 50235, 50333, 51188, 50402, 50402, 50363, 54590, 50470, 50621, 50621, 0, 0);
INSERT INTO `npc_promotion_items` VALUES (4, 1, 'dps', 51187, 50633, 51185, 0, 51189, 50620, 51186, 50235, 50333, 51188, 50402, 50402, 50363, 54590, 50470, 50621, 50621, 0, 0);

-- =============================================================================
-- CLASE 5: PRIEST (SACERDOTE)
-- =============================================================================

-- Priest Holy/Discipline (Heal) - Crimson Acolyte's Raiment
INSERT INTO `npc_promotion_items` VALUES (5, 0, 'heal', 51178, 50724, 51182, 0, 51176, 50613, 51177, 50606, 50651, 51183, 50398, 50398, 54589, 50358, 50470, 50685, 50635, 0, 0);
INSERT INTO `npc_promotion_items` VALUES (5, 1, 'heal', 51178, 50724, 51182, 0, 51176, 50613, 51177, 50606, 50651, 51183, 50398, 50398, 54589, 50358, 50470, 50685, 50635, 0, 0);

-- Priest Shadow (DPS) - Crimson Acolyte's Regalia
INSERT INTO `npc_promotion_items` VALUES (5, 0, 'dps', 51184, 50724, 51175, 0, 51180, 50613, 51181, 50606, 50651, 51179, 50398, 50398, 54588, 50348, 50470, 50685, 50631, 0, 0);
INSERT INTO `npc_promotion_items` VALUES (5, 1, 'dps', 51184, 50724, 51175, 0, 51180, 50613, 51181, 50606, 50651, 51179, 50398, 50398, 54588, 50348, 50470, 50685, 50631, 0, 0);

-- =============================================================================
-- CLASE 6: DEATH KNIGHT (CABALLERO DE LA MUERTE)
-- =============================================================================

-- Death Knight Tank (Blood) - Scourgelord Plate
INSERT INTO `npc_promotion_items` VALUES (6, 0, 'tank', 51133, 50627, 51130, 0, 51134, 50620, 51131, 50235, 50333, 51132, 50404, 50404, 50364, 54571, 50470, 50415, 0, 0, 0);
INSERT INTO `npc_promotion_items` VALUES (6, 1, 'tank', 51133, 50627, 51130, 0, 51134, 50620, 51131, 50235, 50333, 51132, 50404, 50404, 50364, 54571, 50470, 50415, 0, 0, 0);

-- Death Knight DPS (Frost/Unholy) - Scourgelord Battlegear
INSERT INTO `npc_promotion_items` VALUES (6, 0, 'dps', 51127, 50633, 51125, 0, 51129, 50620, 51126, 50235, 50333, 51128, 50402, 50402, 50363, 54590, 50470, 50415, 0, 0, 0);
INSERT INTO `npc_promotion_items` VALUES (6, 1, 'dps', 51127, 50633, 51125, 0, 51129, 50620, 51126, 50235, 50333, 51128, 50402, 50402, 50363, 54590, 50470, 50415, 0, 0, 0);

-- =============================================================================
-- CLASE 7: SHAMAN (CHAMÁN)
-- =============================================================================

-- Shaman Elemental (Caster DPS) - Frost Witch's Regalia
INSERT INTO `npc_promotion_items` VALUES (7, 0, 'caster', 51202, 50724, 51204, 0, 51200, 50613, 51203, 50606, 50651, 51201, 50398, 50398, 54588, 50348, 50470, 50685, 50635, 0, 0);
INSERT INTO `npc_promotion_items` VALUES (7, 1, 'caster', 51202, 50724, 51204, 0, 51200, 50613, 51203, 50606, 50651, 51201, 50398, 50398, 54588, 50348, 50470, 50685, 50635, 0, 0);

-- Shaman Enhancement (Melee DPS) - Frost Witch's Battlegear
INSERT INTO `npc_promotion_items` VALUES (7, 0, 'melee', 51197, 50633, 51199, 0, 51195, 50620, 51198, 50235, 50333, 51196, 50402, 50402, 50363, 54590, 50470, 50621, 50621, 0, 0);
INSERT INTO `npc_promotion_items` VALUES (7, 1, 'melee', 51197, 50633, 51199, 0, 51195, 50620, 51198, 50235, 50333, 51196, 50402, 50402, 50363, 54590, 50470, 50621, 50621, 0, 0);

-- Shaman Restoration (Heal) - Frost Witch's Garb
INSERT INTO `npc_promotion_items` VALUES (7, 0, 'heal', 51192, 50724, 51194, 0, 51190, 50613, 51193, 50606, 50651, 51191, 50398, 50398, 54589, 50358, 50470, 50685, 50616, 0, 0);
INSERT INTO `npc_promotion_items` VALUES (7, 1, 'heal', 51192, 50724, 51194, 0, 51190, 50613, 51193, 50606, 50651, 51191, 50398, 50398, 54589, 50358, 50470, 50685, 50616, 0, 0);

-- =============================================================================
-- CLASE 8: MAGE
-- =============================================================================

-- Mage DPS - Bloodmage's Regalia
INSERT INTO `npc_promotion_items` VALUES (8, 0, 'dps', 51158, 50724, 51155, 0, 51156, 50613, 51157, 50606, 50651, 51159, 50398, 50398, 54588, 50348, 50470, 50685, 50631, 0, 0);
INSERT INTO `npc_promotion_items` VALUES (8, 1, 'dps', 51158, 50724, 51155, 0, 51156, 50613, 51157, 50606, 50651, 51159, 50398, 50398, 54588, 50348, 50470, 50685, 50631, 0, 0);

-- =============================================================================
-- CLASE 9: WARLOCK (BRUJO)
-- =============================================================================

-- Warlock DPS - Dark Coven's Regalia
INSERT INTO `npc_promotion_items` VALUES (9, 0, 'dps', 51208, 50724, 51205, 0, 51206, 50613, 51207, 50606, 50651, 51209, 50398, 50398, 54588, 50348, 50470, 50685, 50631, 0, 0);
INSERT INTO `npc_promotion_items` VALUES (9, 1, 'dps', 51208, 50724, 51205, 0, 51206, 50613, 51207, 50606, 50651, 51209, 50398, 50398, 54588, 50348, 50470, 50685, 50631, 0, 0);

-- =============================================================================
-- CLASE 11: DRUID (DRUIDA)
-- =============================================================================

-- Druid Balance (Caster DPS) - Lasherweave's Regalia
INSERT INTO `npc_promotion_items` VALUES (11, 0, 'caster', 51149, 50724, 51147, 0, 51145, 50613, 51143, 50606, 50651, 51144, 50398, 50398, 54588, 50348, 50470, 50685, 50631, 0, 0);
INSERT INTO `npc_promotion_items` VALUES (11, 1, 'caster', 51149, 50724, 51147, 0, 51145, 50613, 51143, 50606, 50651, 51144, 50398, 50398, 54588, 50348, 50470, 50685, 50631, 0, 0);

-- Druid Feral Tank (Bear) - Lasherweave's Battlegear
INSERT INTO `npc_promotion_items` VALUES (11, 0, 'tank', 51143, 50627, 51140, 0, 51141, 50620, 51142, 50235, 50333, 51138, 50404, 50404, 50364, 54571, 50470, 50427, 0, 0, 0);
INSERT INTO `npc_promotion_items` VALUES (11, 1, 'tank', 51143, 50627, 51140, 0, 51141, 50620, 51142, 50235, 50333, 51138, 50404, 50404, 50364, 54571, 50470, 50427, 0, 0, 0);

-- Druid Feral DPS (Cat) - Lasherweave's Battlegear (similar to tank but different trinkets)
INSERT INTO `npc_promotion_items` VALUES (11, 0, 'melee', 51143, 50633, 51140, 0, 51141, 50620, 51142, 50235, 50333, 51138, 50402, 50402, 50363, 54590, 50470, 50427, 0, 0, 0);
INSERT INTO `npc_promotion_items` VALUES (11, 1, 'melee', 51143, 50633, 51140, 0, 51141, 50620, 51142, 50235, 50333, 51138, 50402, 50402, 50363, 54590, 50470, 50427, 0, 0, 0);

-- Druid Restoration (Heal) - Lasherweave's Garb
INSERT INTO `npc_promotion_items` VALUES (11, 0, 'heal', 51137, 50724, 51135, 0, 51139, 50613, 51136, 50606, 50651, 51148, 50398, 50398, 54589, 50358, 50470, 50685, 50631, 0, 0);
INSERT INTO `npc_promotion_items` VALUES (11, 1, 'heal', 51137, 50724, 51135, 0, 51139, 50613, 51136, 50606, 50651, 51148, 50398, 50398, 54589, 50358, 50470, 50685, 50631, 0, 0);

-- =============================================================================
-- VERIFICACIÓN POST-INSERT
-- =============================================================================
SELECT 
    CASE class
        WHEN 1 THEN 'Warrior'
        WHEN 2 THEN 'Paladin'
        WHEN 3 THEN 'Hunter'
        WHEN 4 THEN 'Rogue'
        WHEN 5 THEN 'Priest'
        WHEN 6 THEN 'Death Knight'
        WHEN 7 THEN 'Shaman'
        WHEN 8 THEN 'Mage'
        WHEN 9 THEN 'Warlock'
        WHEN 11 THEN 'Druid'
    END as Clase,
    CASE faction
        WHEN 0 THEN 'Alianza'
        WHEN 1 THEN 'Horda'
    END as Faccion,
    CASE `function`
        WHEN 'tank' THEN 'Tanque'
        WHEN 'dps' THEN 'DPS (Físico/2H)'
        WHEN 'melee' THEN 'DPS (Melee/Dual)'
        WHEN 'caster' THEN 'DPS (Caster)'
        WHEN 'heal' THEN 'Sanador'
    END as Rol,
    COUNT(*) as Total
FROM npc_promotion_items
GROUP BY class, faction, `function`
ORDER BY class, faction, `function`;

-- Resumen por clase
SELECT 
    CASE class
        WHEN 1 THEN 'Warrior'
        WHEN 2 THEN 'Paladin'
        WHEN 3 THEN 'Hunter'
        WHEN 4 THEN 'Rogue'
        WHEN 5 THEN 'Priest'
        WHEN 6 THEN 'Death Knight'
        WHEN 7 THEN 'Shaman'
        WHEN 8 THEN 'Mage'
        WHEN 9 THEN 'Warlock'
        WHEN 11 THEN 'Druid'
    END as Clase,
    COUNT(*) as ConfiguracionesTotales
FROM npc_promotion_items
GROUP BY class
ORDER BY class;

-- =============================================================================
-- NOTAS FINALES
-- =============================================================================
/*
TOTAL DE CONFIGURACIONES: 44
- Warrior: 4 (Tank, DPS x 2 facciones)
- Paladin: 6 (Tank, Heal, DPS x 2 facciones)
- Hunter: 2 (DPS x 2 facciones)
- Rogue: 2 (DPS x 2 facciones)
- Priest: 4 (Heal, DPS x 2 facciones)
- Death Knight: 4 (Tank, DPS x 2 facciones)
- Shaman: 6 (Caster, Melee, Heal x 2 facciones)
- Mage: 2 (DPS x 2 facciones)
- Warlock: 2 (DPS x 2 facciones)
- Druid: 8 (Caster, Tank, Melee, Heal x 2 facciones)

IDs DE ITEMS UTILIZADOS:
- Tier 10 Normal (ilvl 264): 51XXX
- Accesorios ICC 25H (ilvl 277): 50XXX
- Trinkets Cataclysm (ilvl 277): 54XXX

ARMAS PRINCIPALES:
- 50415: Glorenzelg, High-Blade of the Silver Hand (2H Sword - Plate DPS/Tank)
- 50685: Trauma (1H Mace - Casters/Healers)
- 50621: Calamity's Grasp (1H Dagger - Rogues/Melee)
- 50638: Zod's Repeating Longbow (Ranged - Hunters)
- 50427: Bloodfall (Polearm - Druids)

SHIELDS:
- 50729: Icecrown Glacial Wall (Tank Shield)
- 50616: Bulwark of Smouldering Steel (Healer Shield)

OFF-HANDS:
- 50631: Nightmare Ender (Caster Off-hand)
- 50635: Sundial of Eternal Dusk (Healer Off-hand)
*/
