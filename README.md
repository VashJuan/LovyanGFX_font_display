# LovyanGFX Font Display

A demo program for M5 Stack devices to display the various LovyanGFX fonts.

## Description

This Arduino project displays over 100 different font variants across 12
families available in the LovyanGFX library
(https://github.com/lovyan03/LovyanGFX) for device display using LCD, OLED, or
EPD.

LovyanGFX apparently is similar to the Light and Versatile Graphics Library
(LVGL) at https://lvgl.io/, but with somewhat reduced functionality and an
easier learning curve.

Currently this application is bound to the M5Dial, but is structured to allow
display on other M5Stack devices in the future.

When powered on, users on an M5Dial can:

- Rotate the encoder to display sample text using different font families and
  the families various individual fonts that vary in size and style (italic &
  bold),
- Press the bottom M5 button to cycle through some dozen sample text strings,
  including ([seven Panagrams] (https://en.wikipedia.org/wiki/Pangram)), phrases
  that use all the letters of the alphabet:

      - Pack my box with five dozen liquor jugs
      - The quick brown fox jumps over the lazy dog
      - Glib jocks quiz nymph to vex dwarf
      - Sphinx of black quartz, judge my vow
      - How vexingly quick daft zebras jump!
      - The five boxing wizards jump quickly
      - Jackdaws love my big sphinx of quartz.

## Features

- **Font Family Navigation**: Cycle through multiple font families including:

  - Built-in LGFX fonts
  - Free Mono family
  - Free Sans family
  - Free Serif family
  - Decorative fonts (Orbitron, Roboto, Satisfy, Yellowtail)
  - DejaVu family
  - Japanese Mincho family (commented out to save memory space)
  - Japanese Gothic family (commented out to save memory space)
  - eFontCN family (Chinese) (commented out to save memory space)
  - eFontJA family (Japanese) (commented out to save memory space)

- **Interactive Controls**:

  - Rotate encoder to cycle through all the fonts
  - Press button to cycle through different sample strings of text

- **Real-time Display**: Shows font family name, font name, size, and sample
  text

## Hardware Requirements

- **M5Dial**: M5Stack Dial device with rotary encoder and display
- **Platform**: Arduino M5Stack Board Manager v2.0.7 or later

## Dependencies

- **M5GFX**: https://github.com/m5stack/M5GFX
- **M5Unified**: https://github.com/m5stack/M5Unified

## Installation

1. Clone this repository:

   ```bash
   git clone https://github.com/vashjuan/m5Dial_font_display.git
   ```

2. Open `LovyanGFX_font_display.ino` in Arduino IDE

3. Install required libraries through Arduino Library Manager:

   - M5GFX
   - M5Unified

4. Select the M5Dial board & appropriate serial port in Arduino IDE

5. Upload to your (M5Dial) device

## Usage

1. Power on the M5Dial
2. The device will display "M5 Dial Font Display v 1.0" on startup
3. Rotate the encoder to cycle through different fonts
4. Press the button (at bottom of dial, embossed with "M5") to cycle through the
   sample texts
5. Font information is displayed at the top of the screen
6. Serial monitor shows additional limited debug information

## File Structure

- `LovyanGFX_font_display.ino` - Main Arduino sketch
- `encoder.hpp/cpp` - Encoder handling class
- `fontmanager.hpp/cpp` - Font display management class
- `README.md` - This file

## Sample Texts

The program cycles through these sample texts when the button is pressed:

- "Hello World!"
- "Font Demo"
- "M5Dial"
- "12345"
- "ABC abc"
- and various panagrams (see
  [www.wikipedia.com/panagram](https://en.wikipedia.org/wiki/Pangram))

## Serial Output

The program outputs font information to the serial monitor for debugging:

- Current encoder position
- Font family name
- Font name
- Font size

## Author

**John Cornelison** (john@vashonSoftware.com)

## Version

**v1.0** - Initial release (2025-12-16)

## License

This project is open source. Feel free to use, modify, and distribute.

## Contributing

Contributions are welcome! Please feel free to submit pull requests or open
issues for bugs and feature requests.
