# Modelos CAD 3D y Chasis Mecánico (`3D/`)

Esta carpeta contiene los modelos tridimensionales en estándar **STEP (ISO 10303-21, `.step`)** del chasis diseñado a medida en **Autodesk Fusion 360** y los ensambles electrónicos exportados desde **KiCad**, permitiendo tanto su inspección mecánica en cualquier programa CAD como su impresión directa en impresoras 3D de deposición de filamento fundido (**FDM**).

---

## Archivos Incluidos

| Archivo | Tipo de Modelo | Uso Principal |
| :--- | :---: | :--- |
| **`Fusion_3D_Case_Caja_Mitad_Superior_EXPORTADO.step`** | Pieza imprimible 3D | **Tapa superior del chasis:** incorpora el bisel frontal para la pantalla OLED de 0.96", los 4 alojamientos cilíndricos para los pulsadores de 12 mm y las ranuras laterales de ventilación pasiva. |
| **`Fusion_3D_Case_Caja_Mitad_Inferior_EXPORTADO.step`** | Pieza imprimible 3D | **Base inferior del chasis:** incorpora los pedestales de soporte para la PCB principal, las dos salidas traseras para los conectores SMA de las antenas de 2.4 GHz y las aberturas laterales de energía/programación. |
| **`JammerUsco.step`** | Ensamble ECAD 3D | Modelo 3D completo de la tarjeta principal (`Mainboard`) con los módulos ESP32, `nRF24L01+PA+LNA`, `LM2596` y `AMS1117-3.3V` montados sobre el sustrato FR-4. |
| **`JammerUsco_Buttons.step`** | Ensamble ECAD 3D | Modelo 3D completo de la tarjeta de botonera con los 4 pulsadores táctiles de 12 mm y sus capuchones. |
| **`Weewooday I2C OLED 0.98” 128x64.step`** | Componente CAD 3D | Modelo de referencia geométrica de la pantalla OLED `SSD1306` ($I^2C$, 4 pines) utilizado para dimensionar el vano frontal de la carcasa. |

---

## Parámetros Recomendados para Impresión 3D (FDM)

Los archivos `Fusion_3D_Case_Caja_Mitad_Superior_EXPORTADO.step` y `Fusion_3D_Case_Caja_Mitad_Inferior_EXPORTADO.step` pueden importarse directamente en laminadores modernos (**OrcaSlicer**, **PrusaSlicer**, **Bambu Studio**, **UltiMaker Cura**):

- **Material recomendado:** `PLA` o `PETG` (filamento de $1.75\text{ mm}$).
- **Altura de capa:** $0.20\text{ mm}$ (boquilla estándar de $0.4\text{ mm}$).
- **Perímetros (paredes):** $3$ a $4$ líneas de pared ($\ge 1.2\text{ mm}$) para asegurar rigidez en las torretas de atornillado.
- **Relleno (*Infill*):** $20\%\text{ – }25\%$ (patrón giroide o cúbico).
- **Orientación en cama:**
  - **Mitad Inferior:** Apoyar la cara plana exterior inferior directamente sobre la cama de impresión.
  - **Mitad Superior:** Apoyar la cara frontal plana (donde se ubica la ventana de la pantalla OLED) sobre la cama de impresión para minimizar el uso de soportes y obtener un acabado superficial limpio en el panel de control.
