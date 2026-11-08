# Arquitectura del Código Fuente (`src/` e `include/`)

Este directorio contiene la implementación modular en **C++ (Arduino / FreeRTOS)** del firmware para el microcontrolador **ESP32 (30 pines)**. El código está diseñado para separar estrictamente el procesamiento intensivo de radiofrecuencia del manejo de interfaz de usuario y comunicaciones seriales.

---

## Módulos del Firmware

| Archivo Fuente | Cabecera Asociada | Núcleo de Ejecución | Responsabilidad Técnica |
| :--- | :--- | :---: | :--- |
| **`main.cpp`** | `globals.h` | **Núcleo 0** y **Núcleo 1** | Inicializa periféricos, apaga las radios internas Wi-Fi/Bluetooth del ESP32 para ahorrar corriente, crea el semáforo `radioMutex`, lanza la tarea `jammerTask` anclada al **Núcleo 0** (`xTaskCreatePinnedToCore`) y ejecuta en el **Núcleo 1** el bucle de botones, pantalla OLED y CLI. |
| **`radio_control.cpp`** | `radio_control.h` | **Núcleo 0** | Instancia los buses hardware `VSPI` y `HSPI` a **16 MHz**, configura ambos transceptores `nRF24L01+PA+LNA` en portadora continua (`startConstCarrier`) sin auto-ACK ni retransmisiones, e implementa los algoritmos `Random()`, `Double_Sweep()` y `WiFi_Sweep()`. |
| **`display_menu.cpp`** | `display_menu.h`, `screensaver_frames.h` | **Núcleo 1** | Implementa la máquina de estados finitos (FSM) de navegación en la pantalla OLED `SSD1306` ($128 \times 64\text{ px}$ por $I^2C$ en `GPIO 27/26`) y la animación de protector de pantalla tras 30 s de inactividad. |
| **`cli_handler.cpp`** | `cli_handler.h` | **Núcleo 1** | Implementa el intérprete de comandos de un carácter por puerto serie (`UART0` a `115200 bps`) para telemetría, diagnóstico de registros SPI y operación remota del prototipo durante pruebas de laboratorio. |
| **`globals.cpp`** | `globals.h` | **Compartido** | Define las instancias `RF24`, las variables de estado marcadas con el calificador `volatile` y el manejador del semáforo mutex (`SemaphoreHandle_t radioMutex`). |
