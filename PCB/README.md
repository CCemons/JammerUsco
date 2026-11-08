# Diseño Electrónico y Fabricación de PCB (`PCB/`)

Esta carpeta contiene todos los archivos de diseño asistido por computador (ECAD) y manufactura asistida por computador (CAM) correspondientes a las dos tarjetas de circuito impreso del prototipo **JammerUsco**:

1. **Tarjeta Principal (`Mainboard` — `JammerUsco`):** Interconecta el módulo **ESP32 (30 pines)**, los dos transceptores **nRF24L01+PA+LNA** sobre los buses dedicados `VSPI` y `HSPI`, la etapa de conversión DC-DC **LM2596 (5.0 V)**, el regulador lineal **AMS1117-3.3V** dedicado a la etapa de radiofrecuencia, y las cabeceras de conexión para la pantalla OLED $I^2C$ y la botonera.
2. **Tarjeta de Botonera (`Buttons` — `JammerUsco_Buttons`):** Placa auxiliar para los 4 pulsadores táctiles de $12\text{ mm} \times 12\text{ mm}$ (`UP`, `DOWN`, `OK`, `BACK`) con retorno común a tierra (`GND`).

---

## Estructura de Directorios

```text
PCB/
├── Kicad_Project/
│   ├── JammerUsco/                 # Proyecto KiCad nativo de la PCB principal (Mainboard)
│   │   ├── JammerUsco.kicad_pro    # Archivo de proyecto KiCad
│   │   ├── JammerUsco.kicad_sch    # Esquemático electrónico completo
│   │   └── JammerUsco.kicad_pcb    # Ruteo de la PCB (capa B.Cu + plano de masa GND)
│   ├── JammerUsco_Buttons/         # Proyecto KiCad nativo del módulo de 4 pulsadores
│   ├── Gerber/
│   │   ├── Mainboard/              # Archivos Gerber (B_Cu, Edge_Cuts, gbrjob) de la placa principal
│   │   └── Buttons/                # Archivos Gerber (B_Cu, Edge_Cuts, gbrjob) de la botonera
│   └── Drill/
│       ├── Mainboard/              # Perforaciones Excellon (.drl PTH y NPTH) de la placa principal
│       └── Buttons/                # Perforaciones Excellon (.drl PTH y NPTH) de la botonera
│
├── SYMBOLS_&_FOOTPRINTS/           # Librerías personalizadas KiCad creadas para el proyecto
│   ├── AMS1117_3.3V/               # Símbolo (.kicad_sym) y huella (.kicad_mod) del LDO AMS1117
│   ├── ESP32/                      # Símbolo y huella del DevKit ESP32 de 30 pines
│   ├── LM2596_BUCK_5V/             # Símbolo y huella del módulo convertidor Buck LM2596
│   └── NRF24L01/                   # Símbolo y huella del transceptor nRF24L01+PA+LNA
│
└── CNC/Mainboard/                  # Archivos G-Code para fresado mecánico en CNC 6040
    ├── JammerUsco-B_Cu.gbr_ncc_cnc.nc      # Trayectoria base de aislamiento de pistas (B.Cu)
    ├── JammerUsco-B_Cu_probe_only.ngc      # Rutina de sondeo superficial (G31) en malla 6×8
    ├── map.txt                             # Mapa topográfico real de cotas Z medidas en el laminado FR-4
    ├── JammerUsco-B_Cu_adjusted.ngc        # Código G final compensado en Z para ruteo de cobre
    └── JammerUsco-PTH.nc                   # Código G de taladrado de agujeros pasantes (PTH)
```

---

## Cómo Replicar las Tarjetas PCB

### Opción A: Fabricación Industrial o Química con Archivos Gerber
Si desea enviar las placas a un fabricante externo (JLCPCB, PCBWay, ALLPCB) o realizar revelado fotográfico/transferencia térmica:
1. Comprima en un archivo `.zip` el contenido de `Kicad_Project/Gerber/Mainboard/` junto con `Kicad_Project/Drill/Mainboard/` para la placa principal.
2. Comprima en otro `.zip` el contenido de `Kicad_Project/Gerber/Buttons/` junto con `Kicad_Project/Drill/Buttons/` para la botonera.
3. Especifique laminado **FR-4**, espesor **1.6 mm**, 1 capa de cobre (`Bottom Layer / B.Cu`) y peso de cobre de **1 oz (35 µm)**.

### Opción B: Fresado Mecánico en Ruteadora CNC
Si dispone de una fresadora CNC con control **Mach3 / GRBL**:
1. Sujete una placa virgen de baquelita o **FR-4 de una cara** sobre la mesa de sacrificio.
2. Ejecute el sondeo de nivelación superficial (`G31`) o utilice directamente `CNC/Mainboard/JammerUsco-B_Cu_adjusted.ngc` con una fresa tipo *V-bit* de grabado de **0.2 mm a 0.6 mm**.
3. Ejecute el taladrado de agujeros pasantes con `CNC/Mainboard/JammerUsco-PTH.nc` usando broca de carburo de tungsteno de **0.8 mm – 1.0 mm**.

### Cómo Abrir y Modificar el Proyecto en KiCad
1. Abra **KiCad 8.0 / 9.0+** y cargue `Kicad_Project/JammerUsco/JammerUsco.kicad_pro`.
2. Si desea editar componentes, vincule en *Preferencias → Configurar bibliotecas de símbolos / huellas* las 4 carpetas incluidas en `SYMBOLS_&_FOOTPRINTS/`.
