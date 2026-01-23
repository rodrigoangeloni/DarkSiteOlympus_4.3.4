## Lista de Reparaciones

### ==== 05/01/2024 ====
Fix crash StoneCore
Fix Spell Arcane Missiles
Spawn npc lost isle
Update World Boss Julak Doom
Fix Guardian of Ancient Kings
Fix Locales
Fix Quest Point

### ==== 07/01/2024 ====
Add Worguen Transform at 12:00 to 3:00 am

### ==== 08/01/2024 ====
Fix Quest A Rejuvenating Touch
Fix Quest Save Krennan Aranas
Fix Sacrifices
Fix Battle for Gilneas City
Fix Objetos Start Wargen
Fix Spawn Npcs Gilneas
Fix Gossip Lord Hewell
Fix Spell Warr Charge
Fix Spell Warr Intercept

### ==== 12/01/2024 ====
Fix Quest Unholy Cow
Fix Quest He\'s Holding Out on Us
Fix Quest Twilight Shores
Fix SAI Flintlocke\'s Seaplane
Fix SAI Anduin
Fix SAI - condition  Samuelson
Fix Cadena de misiones Se busca un heroe en tierras altas crepusculares

### ==== 13/01/2024 - 22/01/2024 Zone Vashjir ====
Quest fix Sea Legs
Quest fix Pay It Forward
Quest fix Remnants of Battle
Quest fix Buy Us Some Time
Quest fix Nerve Tonic
Quest fix The Abyssal Ride
Quest fix The Horde's Hoard
Quest fix Raw Materials
Quest fix A Case of Crabs
Quest fix A Taste For Tail
Quest fix A Girl's Best Friend
Quest fix Rest For the Weary
Quest fix Change of Plans
Quest fix Lady La-La's Medallion
Quest fix Pressure is Mounting
Quest fix A Test of Wills
Quest fix Ophidophobia
Quest fix Kliklak's Craw
Quest fix Once More, With Eeling [DEPRICATED]
Quest fix Better Late Than Dead
Quest fix Back in the Saddle
Quest fix Shark Bait
Quest fix Blackfin's Booty
Quest fix To Arms!
Quest fix Traveling on Our Stomachs
Quest fix On Our Own Terms
Quest fix All or Nothing
Quest fix Stormwind Elite Aquatic and Land Forces
Quest fix Gimme Shelter!
Quest fix Ain't Too Proud to Beg
Quest fix Can't Start a Fire Without a Spark
Quest fix Piercing the Ruins
Quest fix Caught Off-Guard
Quest fix Swift Approach
Quest fix An Occupation of Time
Quest fix A Better Vantage
Quest fix Upon the Scene of Battle
Quest fix Starve a Fever, Feed a Cold
Quest fix A Desperate Plea
Quest fix Oh, the Insanity!
Quest fix Dah, Nunt... Dah, Nunt...
Quest fix Getting Your Hands Dirty
Quest fix DUN-dun-DUN-dun-DUN-dun
Quest fix A Bone to Pick
Quest fix Tenuous Negotiations
Quest fix Shallow End of the Gene Pool
Quest fix What? This Old Thing?
Quest fix Decisions, Decisions
Quest fix Undersea Sanctuary
Quest fix Spelunking
Quest fix Debriefing
Quest fix How Disarming
Quest fix Come Hell or High Water
Quest fix What? What? In My Gut...?
Quest fix Wake of Destruction
Quest fix Decompression
Quest fix Sea Legs
Quest fix Pay It Forward
Quest fix Rest For the Weary
Quest fix Buy Us Some Time
Quest fix Traveling on Our Stomachs
Quest fix Girding Our Loins
Quest fix Helm's Deep
Quest fix Finders, Keepers
Quest fix Bring It On!
Quest fix Blood and Thunder!
Quest fix Spelunking
Quest fix Debriefing
Quest fix Decompression
Quest fix What? What? In My Gut...?
Quest fix Shark Weak
Quest fix The Warden's Time
Quest fix Once More, With Eeling

### ==== 28/01/2024 Zone Vashjir ====
Fix item  Levantatormentas, Tramo de la Tempestad
Quest fix Backed Into a Corner
Quest fix Totem Modification
Quest fix The Looming Threat
Quest fix Across the Great Divide
Quest fix Shelled Salvation
Quest fix Making Contact
Quest fix Looking Forward
Quest fix Swift Action
Quest fix Fallen But Not Forgotten
Quest fix Gauging Success
Quest fix Decompression
Quest fix What? What? In My Gut...?
Quest fix Orders Are For the Living

### ==== 28/01/2024  - 06/03/2024 ====
Fix undead start
Fix text echo of Jaina
Add autovalance
Fix text Panicked Citizen
Fix text Frightened Citizen
Update npc Panicked Citizen
Fix npc eyes of archerus
Fix npc Aronus
Add npc Skip dk zone
Quest fix quest endgame
Quest fix quest The maelstrom
Quest fix quest Patriarch's Blessing
Quest fix Gunship Down
Quest fix On Second Thought, Take One Prisoner
Quest fix Some Spraining to Do
Quest fix Deathwing's Fall

### ==== 22/01/2026 ====
Fix OpenSSL 3.x support (Fix 'Connected' freeze)
Enable Legacy Provider for newer OpenSSL versions in AuthServer & WorldServer
Add Custom NPC Heirloom Vendor (Vendedor de Reliquias)
    * Instructions to enable NPC:
        1. Recompile worldserver (Clean & Build) to include the new script `src/server/scripts/Custom/npc_heirloom.cpp` and `ScriptLoader.cpp` changes.
        2. Execute the SQL file in 'world' database: `sql/CUSTOM/world/2026_01_22_00_npc_heirloom.sql`.
        3. Spawn in game: `.npc add 99000`.

### ==== 23/01/2026 ====
Add Complete Promotion System (Sistema de Promoción NPC)
    * New script: `src/server/scripts/Custom/npc_promocion.cpp` (685 lines)
    * New NPC: ID 60003 "Maestro de Promoción" with ScriptName='npc_promocion'
    * Database tables created:
        - `world.npc_promotion_items` (40 gear configurations for all classes)
        - `characters.npc_promotion_log` (usage tracking)
    * Features:
        - Instant level 80 boost
        - Complete Tier 10 Normal (ilvl 264) gear auto-equipped
        - ICC 25H accessories (ilvl 277)
        - 10,000 gold
        - 4x 22-slot bags (Embersilk Bag)
        - All flying mounts learned (75, 150, 280, 310)
        - Skills maxed for level 80
        - Armor proficiencies (Plate/Mail)
        - Dynamic gossip menu per class (10 classes, 22 specs)
        - 1 use per account limit
        - Full database logging
    * Supported classes: Warrior, Paladin, Hunter, Rogue, Priest, Death Knight, Shaman, Mage, Warlock, Druid
    * SQL files:
        - `sql/CUSTOM/world/2026_01_23_00_npc_promotion_structure.sql`
        - `sql/CUSTOM/world/2026_01_23_01_npc_promotion_validation.sql`
        - `sql/CUSTOM/world/2026_01_23_03_npc_promotion_data_full.sql`
        - `sql/CUSTOM/characters/2026_01_23_00_npc_promotion_log.sql`
    * Documentation: `NPC_PROMOCION.md` (technical) & `NPC_PROMOCION_README.md` (user guide)
    * Instructions:
        1. Execute SQL files in 'world' and 'characters' databases
        2. Recompile worldserver to include new script
        3. Spawn in game: `.npc add 60003`
        4. Recommended location: Dalaran (Krasus' Landing) coords 5804.14, 624.77, 647.76
Fix critical bug in First Character Level 80 system (custom_starter_pro.cpp)
    * Issue: Logic allowed multiple characters per account to receive level 80 boost
    * Solution: Implemented proper tracking system with `characters.first_char_boost_log` table
    * New behavior: Only ONE character per account receives automatic level 80 boost on first login
    * SQL file: `sql/CUSTOM/characters/2026_01_23_01_first_char_boost_log.sql`
    * Prevention: UNIQUE constraint on accountId ensures 1 boost per account at database level
Remove obsolete script: `npc_icc_vendor.cpp` (replaced by npc_promocion.cpp)
Update documentation:
    * `CUSTOMS SCRIPTS.md` - Added npc_promocion.cpp documentation
    * `CUSTOMS SCRIPTS.md` - Added custom_starter_pro.cpp documentation (first character level 80 system)
    * `NPC_PROMOCION_README.md` - Complete user guide with reset instructions
    * `ADMIN_RESET_GUIDE.md` - NEW: Administrator guide with all reset commands and troubleshooting
    * Added workflow: First char → Level 80 (auto) → Use NPC 60003 → Full Tier 10 gear → Ready for endgame
    * Added SQL queries for auditing, statistics, and mass resets