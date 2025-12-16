# M5Dial Font Display

A demo program for M5Dial to display and cycle through various LovyanGFX fonts
using the rotary encoder.

## Description

This Arduino project demonstrates the access to over 100 different font variants
across 12 families available in LovyanGFX by displaying them on an M5Dial
device. Users can rotate the encoder to cycle through different font families
and fonts, with sample text displayed in each selected font.

## Features

- **Font Family Navigation**: Cycle through multiple font families including:

  - Built-in LGFX fonts (Font0, Font2, Font4, Font6, Font7, Font8)
  - Free Mono family (various sizes and styles)
  - Free Sans family (various sizes and styles)
  - Free Serif family (various sizes and styles)
  - Special fonts (Orbitron, Roboto, DejaVu)

- **Interactive Controls**:

  - Rotate encoder to change fonts
  - Press button to cycle through different sample texts

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

2. Open `font_display.ino` in Arduino IDE

3. Install required libraries through Arduino Library Manager:

   - M5GFX
   - M5Unified

4. Select the M5Dial board in Arduino IDE

5. Upload to your M5Dial device

## Usage

1. Power on the M5Dial
2. The device will display "M5 Dial Font Display v 1.0" on startup
3. Rotate the encoder to cycle through different fonts
4. Press the center button to change the sample text
5. Font information is displayed at the top of the screen
6. Serial monitor shows detailed font information for debugging

## File Structure

- `font_display.ino` - Main Arduino sketch
- `encoder.hpp/cpp` - Encoder handling class
- `fontmanager.hpp/cpp` - Font display management class
- `README.md` - This file
- `.gitignore` - Git ignore patterns

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
