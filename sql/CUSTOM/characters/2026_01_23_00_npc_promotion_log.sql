-- =============================================================================
-- TABLA DE LOG PARA SISTEMA DE PROMOCIÓN NPC
-- Base de Datos: characters
-- =============================================================================

DROP TABLE IF EXISTS `npc_promotion_log`;
CREATE TABLE `npc_promotion_log` (
    `id` INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    `accountId` INT UNSIGNED NOT NULL COMMENT 'ID de la cuenta',
    `accountName` VARCHAR(255) DEFAULT NULL COMMENT 'Nombre de la cuenta',
    `characterName` VARCHAR(255) DEFAULT NULL COMMENT 'Nombre del personaje',
    `characterGuid` INT UNSIGNED DEFAULT 0 COMMENT 'GUID del personaje',
    `class` TINYINT UNSIGNED DEFAULT 0 COMMENT 'Clase del personaje',
    `spec` VARCHAR(50) DEFAULT NULL COMMENT 'Especialización elegida (tank/dps/heal)',
    `ip` VARCHAR(45) DEFAULT NULL COMMENT 'Dirección IP',
    `date` TIMESTAMP DEFAULT CURRENT_TIMESTAMP COMMENT 'Fecha y hora de uso',
    INDEX `idx_account` (`accountId`),
    INDEX `idx_character` (`characterGuid`),
    INDEX `idx_ip` (`ip`),
    INDEX `idx_date` (`date`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Registro de uso del sistema de promoción';

-- =============================================================================
-- NOTAS
-- =============================================================================
/*
Esta tabla registra cada vez que un jugador usa el NPC de promoción.

Campos:
- accountId: Para verificar límite de 1 uso por cuenta
- ip: Para verificar límite de 1 uso por IP (opcional)
- characterName/characterGuid: Para identificar al personaje promovido
- class/spec: Para estadísticas sobre qué clases/roles son más usados
- date: Para auditoría y análisis temporal

Consultas útiles:
-- Ver todas las promociones
SELECT * FROM npc_promotion_log ORDER BY date DESC;

-- Contar promociones por cuenta
SELECT accountId, accountName, COUNT(*) as total 
FROM npc_promotion_log 
GROUP BY accountId 
HAVING total > 1;

-- Contar promociones por clase
SELECT class, spec, COUNT(*) as total 
FROM npc_promotion_log 
GROUP BY class, spec 
ORDER BY total DESC;
*/
