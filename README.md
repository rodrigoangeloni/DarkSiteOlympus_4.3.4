# Olympus Source 
<p align="center">
  <img src="https://i.imgur.com/p2G31xH.png" alt="OlympusCore" width="200"/>
</p>

<p align="center">
  <em>Un emulador MMORPG para la versión 4.3.4, basado en Olympus Core.</em>
</p>

---

## 🌟 Características

* **Estabilidad y Rendimiento:** Optimizado para ofrecer una experiencia de juego fluida y estable.
* **Compatibilidad Actualizada:** Soporte para las últimas versiones de Visual Studio, MySQL y otras dependencias clave.
* **Funcionalidades Completas:** Implementación de las principales características del juego, incluyendo JcJ, JcE, misiones y eventos.
* **Comunidad Activa:** Un proyecto impulsado por la comunidad, con espacio para contribuciones y mejoras constantes.

---

## 📋 Requisitos

Para compilar y ejecutar **Olympus Source**, necesitarás el siguiente software:

* **Visual Studio 2022:** [Descargar](https://visualstudio.microsoft.com/es/vs/)
* **MySQL 8.0:** [Descargar](https://dev.mysql.com/downloads/mysql/)
* **OpenSSL 3.1.8:** [Descargar](https://slproweb.com/products/Win32OpenSSL.html)
* **CMake 3.24.3:** [Descargar](https://cmake.org/download/)
* **Boost 1.78.0:** [Descargar](https://www.boost.org/users/history/version_1_78_0.html)

---

## 🚀 Guía de Compilación

1. **Clona el Repositorio:**
   ```bash
   git clone https://github.com/tu_usuario/tu_repositorio.git
   ```

2. **Configura con CMake:**
   - Abre la GUI de CMake.
   - Selecciona la carpeta del código fuente y una carpeta para la compilación (ej. `build`).
   - Haz clic en `Configure` y selecciona "Visual Studio 17 2022" como generador.
   - Asegúrate de que todas las dependencias (Boost, OpenSSL, MySQL) sean detectadas correctamente.
   - Haz clic en `Generate`.

3. **Compila en Visual Studio:**
   - Abre el archivo `.sln` generado en la carpeta `build`.
   - Selecciona la configuración `RelWithDebInfo`.
   - Compila la solución.

---

## 🙌 Contribuciones

¡Tu ayuda es bienvenida! Si quieres contribuir a **Olympus Source**, por favor, sigue estos pasos:

1. Haz un `fork` del repositorio.
2. Crea una nueva rama para tus cambios (`git checkout -b feature/nueva-funcionalidad`).
3. Realiza tus cambios y haz `commit` (`git commit -am 'Añade nueva funcionalidad'`).
4. Haz `push` a tu rama (`git push origin feature/nueva-funcionalidad`).
5. Abre un `Pull Request`.

---

## 📄 Licencia

Este proyecto está bajo la Licencia Pública General de GNU. Consulta el archivo `LICENSE` para más detalles.
