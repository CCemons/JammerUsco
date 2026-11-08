# JammerUsco — Prototipo Inhibidor de Señales en la Banda Libre de 2.4 GHz

**Universidad Surcolombiana (USCO)** — Facultad de Ingeniería — Programa de Ingeniería Electrónica  
**Autores:** Camilo Andrés Castañeda Polo ([@CCemons](https://github.com/CCemons)) · Daniel Camilo Torres Quintana ([@BlackSorix](https://github.com/BlackSorix))  
**Director:** Ing. Martín Diómedes Bravo Obando  

---

## Propósito del Repositorio (Estudio y Replicación Abierta)

Este repositorio reúne **todos los recursos de ingeniería necesarios para estudiar, analizar y replicar íntegramente** el prototipo **JammerUsco**, desarrollado como trabajo de grado para el estudio experimental de técnicas de interferencia intencional (*jamming*) y coexistencia espectral en la banda ISM de **2.4 GHz (2400–2525 MHz)**.

El repositorio está estructurado en **tres bloques fundamentales** para permitir su reproducción completa en laboratorio:

1. **[Código Fuente del Firmware (`src/`, `include/`, `platformio.ini`)](#-1-código-fuente-del-firmware-src-include)**: Firmware en C++ sobre el marco Arduino y el sistema operativo en tiempo real **FreeRTOS** para el SoC **ESP32 (30 pines)**, con ejecución paralela en ambos núcleos, control de doble bus SPI a 16 MHz (`VSPI` y `HSPI`), interfaz gráfica en pantalla OLED `SSD1306` y control remoto por puerto serie (`CLI`).
2. **[Diseño de Circuitos Impresos — PCB (`PCB/`)](#-2-diseño-electrónico-y-fabricación-de-pcb-pcb)**: Proyectos nativos en **KiCad**, librerías propias de símbolos y huellas (*footprints*), archivos estándar de manufactura **Gerber / Excellon Drill** y código G de ruteo mecánico **CNC** tanto para la tarjeta principal (*Mainboard*) como para el módulo de botonera (*Buttons*).
3. **[Modelos Mecánicos 3D (`3D/`)](#-3-modelos-3d-y-chasis-mecánico-3d)**: Archivos CAD universales en formato **STEP (`.step`)** del chasis dividido en dos mitades (listos para laminado e impresión 3D FDM) junto con los modelos tridimensionales de las placas electrónicas ensambladas.

> **Aviso de uso académico:** Este diseño y su código fuente se publican exclusivamente con fines académicos, pedagógicos y de investigación experimental en recintos controlados de laboratorio.

---

## Mapa General del Repositorio

```text
JammerUsco/
├── platformio.ini                  # Configuración de compilación y librerías en PlatformIO
├── README.md                       # Guía general de estudio y replicación del proyecto
│
├── src/                            # [1] CÓDIGO FUENTE DEL FIRMWARE (C++ / FreeRTOS)
│   ├── README.md                   # Documentación de la arquitectura de software
│   ├── main.cpp                    # Orquestación multinúcleo (Core 0: RF / Core 1: UI + CLI)
│   ├── radio_control.cpp           # Control SPI dual (VSPI/HSPI 16 MHz) y algoritmos de barrido
│   ├── display_menu.cpp            # Máquina de estados finitos (FSM) e interfaz OLED SSD1306
│   ├── cli_handler.cpp             # Intérprete de comandos remotos por UART (115200 bps)
│   └── globals.cpp                 # Variables globales volátiles y semáforo mutex (radioMutex)
│
├── include/                        # CABECERAS (.h) DEL FIRMWARE
│   ├── radio_control.h             # Prototipos de inicialización y modos de emisión RF
│   ├── display_menu.h              # Estructuras y prototipos del menú interactivo OLED
│   ├── cli_handler.h               # Declaración del parser de comandos por puerto serie
│   ├── globals.h                   # Definición de pines (GPIO), constantes y estado global
│   └── screensaver_frames.h        # Mapas de bits (PROGMEM) del protector de pantalla OLED
│
├── PCB/                            # [2] DISEÑO DE PCB, GERBERS Y RUTEO CNC
│   ├── README.md                   # Guía de apertura en KiCad y fabricación de las PCBs
│   ├── Kicad_Project/              # Proyectos nativos KiCad + salidas Gerber y Drill
│   │   ├── JammerUsco/             # Proyecto KiCad de la tarjeta principal (Mainboard)
│   │   ├── JammerUsco_Buttons/     # Proyecto KiCad de la tarjeta de pulsadores (Buttons)
│   │   ├── Gerber/                 # Archivos Gerber (.gbr) de ambas tarjetas
│   │   └── Drill/                  # Archivos de perforación Excellon (.drl) PTH y NPTH
│   ├── SYMBOLS_&_FOOTPRINTS/       # Librerías KiCad personalizadas (.kicad_sym / .kicad_mod)
│   └── CNC/Mainboard/              # Archivos G-Code (.nc/.ngc) y mapa de autoleveling (G31)
│
└── 3D/                             # [3] MODELOS CAD 3D (STEP) PARA IMPRESIÓN Y ENSAMBLE
    ├── README.md                   # Guía de impresión 3D y ensamblaje mecánico
    ├── Fusion_3D_Case_Caja_Mitad_Superior_EXPORTADO.step   # Tapa superior del chasis
    ├── Fusion_3D_Case_Caja_Mitad_Inferior_EXPORTADO.step   # Base inferior del chasis
    ├── JammerUsco.step             # Ensamble 3D completo de la PCB principal
    ├── JammerUsco_Buttons.step     # Ensamble 3D completo de la PCB de botonera
    └── Weewooday I2C OLED 0.98” 128x64.step                # Modelo CAD 3D del módulo OLED
```

---

## Guía de Replicación Paso a Paso

### Lista de Materiales (BOM)

| Componente | Cantidad | Especificación Técnica | Función en el Prototipo |
| :--- | :---: | :--- | :--- |
| **ESP32 DevKit V1 (30 pines)** | 1 | Dual-Core Xtensa LX6 a 240 MHz | Unidad central de procesamiento y control SPI/I2C |
| **nRF24L01+PA+LNA (SMA)** | 2 | Banda 2.4 GHz, PA +20 dBm, antena dipolo 2 dBi | Transceptores RF en portadora continua (`VSPI` y `HSPI`) |
| **Módulo Buck LM2596 (HW-411)** | 1 | Entrada 12 V DC → Salida ajustada a **5.0 V DC** | Regulación primaria de alta eficiencia |
| **Módulo LDO AMS1117-3.3V** | 1 | Entrada 5.0 V DC → Salida regulada **3.3 V DC** | Alimentación dedicada y filtrada para la etapa RF |
| **Pantalla OLED 0.96" I2C** | 1 | Controlador `SSD1306`, resolución 128 × 64 px | Interfaz gráfica local de usuario (GUI) |
| **Pulsadores táctiles (12 mm)** | 4 | SPST normalmente abiertos con capuchón | Navegación física (`UP`, `DOWN`, `OK`, `BACK`) |
| **Capacitores de desacoplo** | 2 | Electrolíticos de $10\text{ }\mu\text{F}$ a $100\text{ }\mu\text{F}$ | Filtrado de rizado transitorio en riel de 3.3 V |
| **Fuente de alimentación externa** | 1 | Adaptador 12 V DC / 2 A (conector plug DC) | Suministro energético principal del sistema |

---

### 1. Código Fuente del Firmware (`src/`, `include/`)

El firmware explota la arquitectura de doble núcleo del **ESP32** mediante **FreeRTOS** para garantizar que el refresco de la pantalla OLED por $I^2C$ no introduzca latencias ni tiempos muertos en la conmutación de canales de radiofrecuencia:

- **Núcleo 0 (`jammerTask`):** Ejecuta en un lazo dedicado los algoritmos de barrido espectral sobre los dos módulos `nRF24L01+PA+LNA` a través de los buses independientes `VSPI` y `HSPI` configurados a **16 MHz**. Incluye cuatro modos de operación:
  1. **Modo 1 (`Random`):** Salto pseudoaleatorio continuo sobre los 80 canales ISM ($2400\text{–}2479\text{ MHz}$).
  2. **Modo 2 (`Double Sweep`):** Barrido triangular codireccional sincronizado.
  3. **Modo 3 (`Fixed Channel`):** Portadora continua estacionaria en un canal seleccionable ($0\text{–}125$).
  4. **Modo 4 (`Wi-Fi Sweep`):** Barrido acotado a los 22 MHz de un canal Wi-Fi IEEE 802.11b/g/n seleccionable (canales 1 al 13).
- **Núcleo 1 (`loop()` Arduino):** Gestiona la lectura con antirrebote de los 4 pulsadores físicos, el renderizado de la máquina de estados en la pantalla OLED `SSD1306` y el intérprete de comandos por puerto serie (`115200 bps`).
- **Sincronización (`radioMutex`):** Un semáforo tipo *mutex* de FreeRTOS protege todas las transacciones sobre los buses SPI para evitar colisiones entre el lazo de barrido del Núcleo 0 y los cambios de configuración solicitados desde el Núcleo 1.

#### Mapa de Conexiones (Pinout ESP32 de 30 Pines)

| Subsistema | Señal | Pin ESP32 | Descripción |
| :--- | :---: | :---: | :--- |
| **Radio 1 (`VSPI`)** | `CE` / `CSN` | `GPIO 22` / `GPIO 21` | Habilitación de chip y selección de esclavo SPI 1 |
| **Radio 1 (`VSPI`)** | `SCK` / `MOSI` / `MISO` | `GPIO 18` / `GPIO 23` / `GPIO 19` | Reloj y líneas de datos del bus `VSPI` (16 MHz) |
| **Radio 2 (`HSPI`)** | `CE` / `CSN` | `GPIO 16` / `GPIO 15` | Habilitación de chip y selección de esclavo SPI 2 |
| **Radio 2 (`HSPI`)** | `SCK` / `MOSI` / `MISO` | `GPIO 14` / `GPIO 13` / `GPIO 12` | Reloj y líneas de datos del bus `HSPI` (16 MHz) |
| **Pantalla OLED (`I2C`)** | `SDA` / `SCL` | `GPIO 27` / `GPIO 26` | Bus $I^2C$ por software hacia pantalla `SSD1306` |
| **Botonera (`INPUT_PULLUP`)** | `UP` / `DOWN` / `OK` / `BACK` | `GPIO 33` / `GPIO 25` / `GPIO 32` / `GPIO 4` | Pulsadores activos en nivel bajo (`LOW`) |

#### Compilación y Carga con PlatformIO

1. Instalar [Visual Studio Code](https://code.visualstudio.com/) con la extensión **PlatformIO IDE**.
2. Clonar este repositorio y abrir la carpeta raíz en PlatformIO (`platformio.ini` descargará automáticamente las librerías `RF24 @ ^1.4.8`, `Adafruit SSD1306 @ ^2.5.7`, `Adafruit GFX @ ^1.11.9` y `ezButton @ ^1.0.4`).
3. Compilar y cargar el firmware al ESP32:
   ```bash
   pio run --target upload
   pio device monitor -b 115200
   ```

#### Comandos por Puerto Serie (`UART 115200 bps`)

| Comando | Función |
| :---: | :--- |
| `'s'` / `'p'` | Iniciar (`Start`) / Detener (`Stop`) la emisión de portadora continua RF |
| `'o'` / `'t'` / `'w'` | Seleccionar modo `Random` / `Double Sweep` / `Wi-Fi` |
| `'m'` / `'l'` / `'h'` / `'x'` | Ajustar potencia PA: `MIN (2 dBm)` / `LOW (8 dBm)` / `HIGH (14 dBm)` / `MAX (20 dBm)` |
| `'k'` / `'1'` / `'2'` | Ajustar tasa de datos RF (ensanchamiento): `250 kbps` / `1 Mbps` / `2 Mbps` |
| `'u'`/`'U'`, `'v'`/`'V'`, `'e'`, `'b'` | Emular pulsaciones cortas/largas de los botones (`UP`, `DOWN`, `OK`, `BACK`) |
| `'d'` | Imprimir diagnóstico de comunicación SPI y estado de registros `nRF24L01+` |

---

### 2. Diseño Electrónico y Fabricación de PCB (`PCB/`)

El diseño electrónico se divide en dos tarjetas independientes de una sola cara (*single-layer* en la capa `B.Cu`) optimizadas tanto para manufactura industrial como para fresado químico o mecánico CNC:

1. **Tarjeta Principal (`PCB/Kicad_Project/JammerUsco/`):** Integra el ESP32, los dos zócalos para los transceptores `nRF24L01+PA+LNA` con geometría de pistas simétrica, la cascada de regulación `LM2596` (12 V → 5 V) + `AMS1117-3.3V` (5 V → 3.3 V) y los conectores hacia la pantalla OLED y la botonera.
2. **Tarjeta de Botonera (`PCB/Kicad_Project/JammerUsco_Buttons/`):** Aloja los 4 pulsadores táctiles de 12 mm que se fijan en el panel frontal superior del chasis.

- **Para manufactura con archivos Gerber:** Utilizar los archivos listos en `PCB/Kicad_Project/Gerber/` y `PCB/Kicad_Project/Drill/`.
- **Para fabricación en fresadora CNC:** Utilizar los archivos de código G en `PCB/CNC/Mainboard/` (`JammerUsco-B_Cu_adjusted.ngc` para aislamiento de pistas y `JammerUsco-PTH.nc` para perforación).

📄 *Consulte más detalles en [`PCB/README.md`](PCB/README.md).*

---

### 3. Modelos 3D y Chasis Mecánico (`3D/`)

La carpeta `3D/` contiene todos los sólidos geométricos en estándar **ISO 10303-21 (`.step`)**, compatibles con cualquier software CAD (*Autodesk Fusion 360*, *SolidWorks*, *FreeCAD*) y laminadores de impresión 3D (*PrusaSlicer*, *UltiMaker Cura*, *Bambu Studio*, *OrcaSlicer*):

- **`Fusion_3D_Case_Caja_Mitad_Superior_EXPORTADO.step`:** Tapa superior del gabinete con vano biselado para la pantalla OLED de 0.96", cuatro guías cilíndricas para los pulsadores de 12 mm y rejillas laterales de ventilación por convección.
- **`Fusion_3D_Case_Caja_Mitad_Inferior_EXPORTADO.step`:** Base inferior con torretas de fijación para la PCB principal, aberturas traseras para los conectores coaxiales SMA de ambos radios `nRF24L01+PA+LNA` y acceso lateral para alimentación DC y puerto micro-USB.
- **`JammerUsco.step` y `JammerUsco_Buttons.step`:** Ensambles tridimensionales completos de las tarjetas electrónicas exportados desde KiCad para verificación de tolerancias mecánicas.

📄 *Consulte los parámetros recomendados de impresión 3D en [`3D/README.md`](3D/README.md).*
