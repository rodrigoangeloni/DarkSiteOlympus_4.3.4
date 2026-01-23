-- =============================================================================
-- CONSULTAS DE VALIDACIÓN PARA TIER 10 ICC (CATACLYSM 4.3.4)
-- =============================================================================
-- IMPORTANTE: Ejecuta estas consultas ANTES de poblar npc_promotion_items
-- para verificar que los IDs de items existen en tu base de datos
-- =============================================================================

-- 1. BUSCAR TODOS LOS ITEMS TIER 10 "SANCTIFIED" (ilvl 264)
SELECT entry, name, ItemLevel, class, subclass, Quality
FROM item_template 
WHERE name LIKE '%Sanctified%' 
  AND ItemLevel = 264
ORDER BY class, name;

-- 2. BUSCAR SETS ESPECÍFICOS POR NOMBRE
-- Warrior: Ymirjar Lord
SELECT entry, name, ItemLevel, InventoryType 
FROM item_template 
WHERE name LIKE '%Ymirjar Lord%' 
  AND ItemLevel = 264
ORDER BY InventoryType;

-- Paladin: Lightsworn
SELECT entry, name, ItemLevel, InventoryType 
FROM item_template 
WHERE name LIKE '%Lightsworn%' 
  AND ItemLevel = 264
ORDER BY InventoryType;

-- Death Knight: Scourgelord
SELECT entry, name, ItemLevel, InventoryType 
FROM item_template 
WHERE name LIKE '%Scourgelord%' 
  AND ItemLevel = 264
ORDER BY InventoryType;

-- Hunter: Ahn'Kahar
SELECT entry, name, ItemLevel, InventoryType 
FROM item_template 
WHERE name LIKE '%Ahn\'Kahar%' 
  AND ItemLevel = 264
ORDER BY InventoryType;

-- Rogue: Shadowblade
SELECT entry, name, ItemLevel, InventoryType 
FROM item_template 
WHERE name LIKE '%Shadowblade%' 
  AND ItemLevel = 264
ORDER BY InventoryType;

-- Priest: Crimson Acolyte
SELECT entry, name, ItemLevel, InventoryType 
FROM item_template 
WHERE name LIKE '%Crimson Acolyte%' 
  AND ItemLevel = 264
ORDER BY InventoryType;

-- Shaman: Frost Witch
SELECT entry, name, ItemLevel, InventoryType 
FROM item_template 
WHERE name LIKE '%Frost Witch%' 
  AND ItemLevel = 264
ORDER BY InventoryType;

-- Mage: Bloodmage
SELECT entry, name, ItemLevel, InventoryType 
FROM item_template 
WHERE name LIKE '%Bloodmage%' 
  AND ItemLevel = 264
ORDER BY InventoryType;

-- Warlock: Dark Coven
SELECT entry, name, ItemLevel, InventoryType 
FROM item_template 
WHERE name LIKE '%Dark Coven%' 
  AND ItemLevel = 264
ORDER BY InventoryType;

-- Druid: Lasherweave
SELECT entry, name, ItemLevel, InventoryType 
FROM item_template 
WHERE name LIKE '%Lasherweave%' 
  AND ItemLevel = 264
ORDER BY InventoryType;

-- 3. BUSCAR ACCESORIOS ICC (Nivel 264-277)
-- Collares
SELECT entry, name, ItemLevel 
FROM item_template 
WHERE InventoryType = 2  -- Neck
  AND ItemLevel BETWEEN 264 AND 277
  AND Quality = 4  -- Epic
ORDER BY ItemLevel DESC, name
LIMIT 10;

-- Anillos
SELECT entry, name, ItemLevel 
FROM item_template 
WHERE InventoryType = 11  -- Finger
  AND ItemLevel BETWEEN 264 AND 277
  AND Quality = 4
ORDER BY ItemLevel DESC, name
LIMIT 10;

-- Trinkets
SELECT entry, name, ItemLevel, class
FROM item_template 
WHERE InventoryType = 12  -- Trinket
  AND ItemLevel BETWEEN 264 AND 277
  AND Quality = 4
ORDER BY class, ItemLevel DESC, name
LIMIT 20;

-- Capas
SELECT entry, name, ItemLevel 
FROM item_template 
WHERE InventoryType = 16  -- Back/Cloak
  AND ItemLevel BETWEEN 264 AND 277
  AND Quality = 4
ORDER BY ItemLevel DESC, name
LIMIT 10;

-- 4. BUSCAR ARMAS ICC (Nivel 264-277)
-- Espadas de una mano
SELECT entry, name, ItemLevel, subclass 
FROM item_template 
WHERE class = 2  -- Weapon
  AND subclass = 7  -- One-Handed Swords
  AND ItemLevel BETWEEN 264 AND 277
  AND Quality = 4
ORDER BY ItemLevel DESC, name
LIMIT 10;

-- Espadas de dos manos
SELECT entry, name, ItemLevel, subclass 
FROM item_template 
WHERE class = 2 
  AND subclass = 8  -- Two-Handed Swords
  AND ItemLevel BETWEEN 264 AND 277
  AND Quality = 4
ORDER BY ItemLevel DESC, name
LIMIT 10;

-- Escudos
SELECT entry, name, ItemLevel 
FROM item_template 
WHERE class = 4  -- Armor
  AND subclass = 6  -- Shields
  AND ItemLevel BETWEEN 264 AND 277
  AND Quality = 4
ORDER BY ItemLevel DESC, name
LIMIT 10;

-- 5. VERIFICAR SI EXISTEN LOS IDS ESPECÍFICOS DOCUMENTADOS
-- (Estos son los IDs de WotLK 3.3.5a, pueden ser diferentes en Cataclysm)
SELECT entry, name, ItemLevel 
FROM item_template 
WHERE entry IN (
    -- Warrior DPS (Ymirjar Lord's Battlegear)
    51227, 51229, 51225, 51228, 51226,
    -- Warrior Tank (Ymirjar Lord's Plate)
    51221, 51223, 51219, 51222, 51220,
    -- Paladin Holy
    51272, 51274, 51270, 51273, 51271,
    -- Paladin Protection
    51266, 51268, 51264, 51267, 51265,
    -- Paladin Retribution
    51277, 51279, 51275, 51278, 51276
)
ORDER BY entry;

-- =============================================================================
-- NOTAS DE USO
-- =============================================================================
/*
1. Ejecuta estas consultas en tu base de datos 'world'
2. Anota los IDs reales que existen en tu servidor
3. Si los IDs de WotLK (51XXX) no existen, busca por nombre
4. Actualiza el archivo de datos (2026_01_23_02_npc_promotion_data.sql) con los IDs correctos
5. En Cataclysm, los items pueden tener IDs completamente diferentes

MAPEO DE INVENTORYTYPE:
1  = Head
2  = Neck
3  = Shoulder
4  = Shirt (Body)
5  = Chest
6  = Waist
7  = Legs
8  = Feet
9  = Wrist
10 = Hands
11 = Finger
12 = Trinket
13 = One-Hand (Weapon)
14 = Shield (Off-hand)
15 = Ranged
16 = Back (Cloak)
17 = Two-Hand (Weapon)
20 = Chest (Robe)
21 = Main Hand
22 = Off Hand
23 = Held In Off-hand
26 = Ranged (thrown)

CLASES:
1  = Warrior
2  = Paladin
3  = Hunter
4  = Rogue
5  = Priest
6  = Death Knight
7  = Shaman
8  = Mage
9  = Warlock
11 = Druid
*/
