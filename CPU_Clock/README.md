# 8-Bit CPU Clock Module (KiCad)

## Overview
The KiCad schematics and design files for a **CPU Clock Module**. Designed for 8-bit computers nd provides clock generation modes to facilitate running the clock continuously or stepping through instructions manually for debugging.

## The three 555 timer modes
* **Astable Mode (continuous):** Generates a continuous square wave clock with adjustable frequency.
* **Monostable Mode (step-by-step):** Generates a single clock pulse per button press for cycle-by-cycle debugging.
* **Bistable Mode (switching):** Uses a 555 timer to switch between the continuous and step-by-step modes.

## Circuit Architecture
The design relies on three **LM555** timers and standard **74LS series** TTL logic gates to coordinate the signals.

### 555 Timer Configurations
1.  **1 - Astable Oscillator:**
    * Configured to oscillate continuously.
    * **Control:** Speed is adjustable via potentiometer **RV1** (1MΩ).
    * **Application:** Normal program execution.
    
2.  **2 - Monostable Multivibrator:**
    * Configured to output a single pulse of fixed duration when triggered.
    * **Control:** Triggered by push button **SW1**.
    * **Application:** Manual step-by-step clock pulse for debugging.

3.  **3 - Bistable Latch:**
    * Configured as a debounced Set-Reset (SR) latch.
    * **Control:** Toggled by switch **SW2**.
    * **Application:** Selects between **continuous** (Astable) and **step-by-step** (Monostable) modes.

### Components
# Logic gates

* **74LS08 (Quad AND Gate):**
* **74LS32 (Quad OR Gate):**
* **74LS04 (Hex Inverter):**

# Other Components
| Reference | Value | Description |
| :--- | :--- | :--- |
| **U1, U2, U3** | LM555 | Timer IC |
| **U4** | 74LS04 | Hex Inverter |
| **U7** | 74LS08 | Quad 2-Input AND Gate |
| **U5** | 74LS32 | Quad 2-Input OR Gate |
| **RV1** | 1MΩ | Potentiometer (Linear) |
| **SW1** | Push Button | Momentary Switch (Step) |
| **SW2** | SPDT | Toggle Switch (Mode Select) |
| **C1, C3, C6** | 1µF / 0.1µF | Timing Capacitors |
| **D1, D2...** | LED | Status LEDs |
| **R1-R10** | 1kΩ, 220Ω, 1MΩ Resistors | 7 resistors

# Signals
* **VCC/GND:** 5V Power Supply.
* **CLK:** Main Clock Output (Active High).
* **!CLK:** Inverted Clock Output (Active Low).
* **HLT:** Halt Input (Active High - stops the clock when high).