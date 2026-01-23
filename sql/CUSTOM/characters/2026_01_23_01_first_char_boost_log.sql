-- =============================================================================
-- Tabla de Log para Boost de Primer Personaje
-- Base de Datos: characters
-- Fecha: 23/01/2026
-- =============================================================================

-- Crear tabla para trackear el boost automático de nivel 80
CREATE TABLE IF NOT EXISTS `first_char_boost_log` (
    `id` INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    `accountId` INT UNSIGNED NOT NULL COMMENT 'ID de la cuenta que recibió el boost',
    `characterGuid` INT UNSIGNED NOT NULL COMMENT 'GUID del personaje que recibió el boost',
    `characterName` VARCHAR(255) DEFAULT NULL COMMENT 'Nombre del personaje',
    `date` TIMESTAMP DEFAULT CURRENT_TIMESTAMP COMMENT 'Fecha en que se otorgó el boost',
    
    UNIQUE KEY `idx_account` (`accountId`) COMMENT 'Solo un boost por cuenta',
    INDEX `idx_character` (`characterGuid`),
    INDEX `idx_date` (`date`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COMMENT='Registro de boost automático a nivel 80 para primer personaje';

-- =============================================================================
-- Consultas Útiles
-- =============================================================================

-- Ver todos los boost otorgados
-- SELECT accountId, characterName, date FROM first_char_boost_log ORDER BY date DESC;

-- Ver si una cuenta específica ya recibió el boost
-- SELECT * FROM first_char_boost_log WHERE accountId = 123;

-- Resetear boost de una cuenta (permitir nuevo boost)
-- DELETE FROM first_char_boost_log WHERE accountId = 123;

-- Estadísticas de uso
-- SELECT COUNT(*) as total_boosts, 
--        DATE(date) as fecha,
--        COUNT(*) as boosts_dia
-- FROM first_char_boost_log 
-- GROUP BY DATE(date) 
-- ORDER BY fecha DESC;
