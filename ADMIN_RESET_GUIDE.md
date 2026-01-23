# Guía de Administración - Sistema de Promoción

## 🎯 Resumen Rápido

Este servidor tiene **2 sistemas de boost** independientes:

| Sistema | Script | Tabla | Límite | Descripción |
|---------|--------|-------|--------|-------------|
| **Boost Automático** | `custom_starter_pro.cpp` | `characters.first_char_boost_log` | 1 por cuenta | Nivel 80 al crear primer personaje |
| **Promoción Manual** | `npc_promocion.cpp` | `characters.npc_promotion_log` | 1 por cuenta | Tier 10 + oro + bolsas vía NPC 60003 |

---

## 🔄 Comandos de Reset

### Reset Individual (Cuenta Específica)

```sql
-- 1. Obtener Account ID de un personaje
SELECT guid, name, account, class, level
FROM characters.characters
WHERE name = 'NombreDelPersonaje';
-- Resultado: account = 123 (ejemplo)

-- 2. Resetear boost automático (permitir nuevo primer personaje)
DELETE FROM characters.first_char_boost_log WHERE accountId = 123;

-- 3. Resetear promoción manual (permitir usar NPC 60003 de nuevo)
DELETE FROM characters.npc_promotion_log WHERE accountId = 123;

-- 4. Resetear ambos sistemas
DELETE FROM characters.first_char_boost_log WHERE accountId = 123;
DELETE FROM characters.npc_promotion_log WHERE accountId = 123;
```

### Reset Masivo (Todos los Usuarios)

⚠️ **PELIGRO:** Esto borrará TODOS los registros

```sql
-- Resetear TODO el sistema de boost automático
TRUNCATE TABLE characters.first_char_boost_log;

-- Resetear TODO el sistema de promoción manual
TRUNCATE TABLE characters.npc_promotion_log;

-- Resetear AMBOS sistemas completamente
TRUNCATE TABLE characters.first_char_boost_log;
TRUNCATE TABLE characters.npc_promotion_log;
```

**Usar solo en:**
- Servidor de test/desarrollo
- Después de wipe completo
- Después de rollback de base de datos

---

## 🔍 Verificación y Auditoría

### Ver quién usó el boost automático

```sql
SELECT 
    accountId,
    characterName,
    DATE_FORMAT(date, '%Y-%m-%d %H:%i:%s') as Fecha
FROM characters.first_char_boost_log
ORDER BY date DESC
LIMIT 20;
```

### Ver quién usó la promoción manual

```sql
SELECT 
    accountId,
    accountName,
    characterName,
    CASE class 
        WHEN 1 THEN 'Warrior' WHEN 2 THEN 'Paladin' WHEN 3 THEN 'Hunter'
        WHEN 4 THEN 'Rogue' WHEN 5 THEN 'Priest' WHEN 6 THEN 'Death Knight'
        WHEN 7 THEN 'Shaman' WHEN 8 THEN 'Mage' WHEN 9 THEN 'Warlock'
        WHEN 11 THEN 'Druid'
    END as Clase,
    spec as Especializacion,
    ip,
    DATE_FORMAT(date, '%Y-%m-%d %H:%i:%s') as Fecha
FROM characters.npc_promotion_log
ORDER BY date DESC
LIMIT 20;
```

### Verificar estado de una cuenta específica

```sql
-- Ver si una cuenta usó el boost automático
SELECT 
    'Boost Automático' as Sistema,
    CASE WHEN COUNT(*) > 0 THEN 'SÍ USADO' ELSE 'DISPONIBLE' END as Estado,
    MAX(date) as FechaUso
FROM characters.first_char_boost_log
WHERE accountId = 123
UNION ALL
-- Ver si una cuenta usó la promoción manual
SELECT 
    'Promoción Manual' as Sistema,
    CASE WHEN COUNT(*) > 0 THEN 'SÍ USADO' ELSE 'DISPONIBLE' END as Estado,
    MAX(date) as FechaUso
FROM characters.npc_promotion_log
WHERE accountId = 123;
```

### Estadísticas generales

```sql
SELECT 
    'Boost Automático' as Sistema,
    COUNT(*) as TotalUsos,
    COUNT(DISTINCT accountId) as CuentasUnicas,
    MAX(date) as UltimoUso
FROM characters.first_char_boost_log
UNION ALL
SELECT 
    'Promoción Manual' as Sistema,
    COUNT(*) as TotalUsos,
    COUNT(DISTINCT accountId) as CuentasUnicas,
    MAX(date) as UltimoUso
FROM characters.npc_promotion_log;
```

### Detectar posibles abusos (múltiples cuentas misma IP)

```sql
SELECT 
    ip,
    COUNT(DISTINCT accountId) as CuentasDiferentes,
    COUNT(*) as UsosTotal,
    GROUP_CONCAT(DISTINCT accountName SEPARATOR ', ') as Cuentas
FROM characters.npc_promotion_log
GROUP BY ip
HAVING COUNT(DISTINCT accountId) > 3
ORDER BY CuentasDiferentes DESC;
```

---

## 🛠️ Casos de Uso Comunes

### Caso 1: Jugador reporta que no puede usar el NPC

```sql
-- 1. Verificar si ya lo usó
SELECT * FROM characters.npc_promotion_log 
WHERE accountName = 'nombreCuenta';

-- 2. Si quieres resetear
DELETE FROM characters.npc_promotion_log 
WHERE accountName = 'nombreCuenta';
```

### Caso 2: Jugador quiere crear otro "primer personaje"

```sql
-- 1. Verificar si ya lo usó
SELECT * FROM characters.first_char_boost_log 
WHERE accountId = 123;

-- 2. Resetear para permitir nuevo boost
DELETE FROM characters.first_char_boost_log 
WHERE accountId = 123;
```

### Caso 3: Evento especial (permitir a todos usar de nuevo)

```sql
-- Opción A: Solo promoción manual
TRUNCATE TABLE characters.npc_promotion_log;

-- Opción B: Solo boost automático
TRUNCATE TABLE characters.first_char_boost_log;

-- Opción C: Ambos sistemas
TRUNCATE TABLE characters.first_char_boost_log;
TRUNCATE TABLE characters.npc_promotion_log;
```

### Caso 4: Backup antes de cambios importantes

```sql
-- Crear backup de tablas
CREATE TABLE characters.npc_promotion_log_backup AS 
SELECT * FROM characters.npc_promotion_log;

CREATE TABLE characters.first_char_boost_log_backup AS 
SELECT * FROM characters.first_char_boost_log;

-- Restaurar si algo sale mal
TRUNCATE TABLE characters.npc_promotion_log;
INSERT INTO characters.npc_promotion_log 
SELECT * FROM characters.npc_promotion_log_backup;

TRUNCATE TABLE characters.first_char_boost_log;
INSERT INTO characters.first_char_boost_log 
SELECT * FROM characters.first_char_boost_log_backup;
```

---

## 📊 Reportes para Administración

### Reporte diario de uso

```sql
SELECT 
    DATE(date) as Fecha,
    COUNT(*) as BoostsOtorgados,
    COUNT(DISTINCT accountId) as CuentasUnicas
FROM characters.first_char_boost_log
WHERE date >= DATE_SUB(NOW(), INTERVAL 7 DAY)
GROUP BY DATE(date)
UNION ALL
SELECT 
    DATE(date) as Fecha,
    COUNT(*) as PromocionesOtorgadas,
    COUNT(DISTINCT accountId) as CuentasUnicas
FROM characters.npc_promotion_log
WHERE date >= DATE_SUB(NOW(), INTERVAL 7 DAY)
GROUP BY DATE(date)
ORDER BY Fecha DESC;
```

### Clases más populares

```sql
SELECT 
    CASE class 
        WHEN 1 THEN 'Warrior' WHEN 2 THEN 'Paladin' WHEN 3 THEN 'Hunter'
        WHEN 4 THEN 'Rogue' WHEN 5 THEN 'Priest' WHEN 6 THEN 'Death Knight'
        WHEN 7 THEN 'Shaman' WHEN 8 THEN 'Mage' WHEN 9 THEN 'Warlock'
        WHEN 11 THEN 'Druid'
    END as Clase,
    spec as Especializacion,
    COUNT(*) as Usos,
    ROUND(COUNT(*) * 100.0 / (SELECT COUNT(*) FROM characters.npc_promotion_log), 2) as Porcentaje
FROM characters.npc_promotion_log
GROUP BY class, spec
ORDER BY Usos DESC;
```

---

## 🚨 Troubleshooting

### Problema: "Ya has usado tu promoción" pero el jugador no recuerda

```sql
-- Ver detalles del uso anterior
SELECT 
    characterName as PersonajeQueLoUso,
    CASE class 
        WHEN 1 THEN 'Warrior' WHEN 2 THEN 'Paladin' WHEN 3 THEN 'Hunter'
        WHEN 4 THEN 'Rogue' WHEN 5 THEN 'Priest' WHEN 6 THEN 'Death Knight'
        WHEN 7 THEN 'Shaman' WHEN 8 THEN 'Mage' WHEN 9 THEN 'Warlock'
        WHEN 11 THEN 'Druid'
    END as Clase,
    spec as Especializacion,
    date as FechaDeUso
FROM characters.npc_promotion_log
WHERE accountId = 123;
```

### Problema: NPC no responde

```sql
-- Verificar que el NPC existe
SELECT entry, name, ScriptName, npcflag 
FROM world.creature_template 
WHERE entry = 60003;

-- Debe mostrar:
-- entry: 60003
-- name: Maestro de Promoción
-- ScriptName: npc_promocion
-- npcflag: 1
```

### Problema: Items no se equipan

```sql
-- Verificar que los datos existen
SELECT COUNT(*) as ConfiguracionesTotales 
FROM world.npc_promotion_items;
-- Debe ser 40

-- Verificar una configuración específica
SELECT * FROM world.npc_promotion_items 
WHERE class = 1 AND faction = 0 AND `function` = 'dps';
```

---

## 📋 Checklist de Mantenimiento Mensual

- [ ] Revisar logs de uso (detectar patrones inusuales)
- [ ] Verificar integridad de tablas (`CHECK TABLE`)
- [ ] Hacer backup de tablas de log
- [ ] Limpiar registros antiguos si es necesario (>6 meses)
- [ ] Revisar estadísticas de clases más usadas
- [ ] Verificar que los IDs de items siguen existiendo

---

## 📝 Notas Importantes

1. **Nunca borrar los datos de producción sin backup**
2. **Los resets NO devuelven items/oro/nivel a los personajes**
3. **El sistema usa AccountId, no CharacterGuid, para el control**
4. **Ambos sistemas son independientes** (resetear uno no afecta al otro)
5. **Los índices UNIQUE garantizan que no se pueda usar más de 1 vez**

---

## 🆘 Contacto y Soporte

Si tienes dudas sobre el sistema:
1. Lee la documentación técnica: `NPC_PROMOCION.md`
2. Lee la guía de usuario: `NPC_PROMOCION_README.md`
3. Revisa los scripts: `npc_promocion.cpp` y `custom_starter_pro.cpp`

**Fecha de última actualización:** 23/01/2026