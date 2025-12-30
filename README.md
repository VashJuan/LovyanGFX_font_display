# LovyanGFX Font Display

An open source, free program to display all LovyanGFX fonts on M5 Stack devices.

![Example of LovyanGFX Font Display showing the DejaVu font](./imgs/DejaVu24.jpg "LovyanGFX Font Display showing the DejaVu font")

## 📖 Description

This Arduino project displays over 100 different font variants across 12
families available in the LovyanGFX library
(<https://github.com/lovyan03/LovyanGFX>) for device display using LCD, OLED, or
EPD.

LovyanGFX apparently is similar to the Light and Versatile Graphics Library
(LVGL) at <https://lvgl.io/>, but with somewhat reduced functionality and an
easier learning curve.

Currently this application is bound to the M5Dial, but is structured to allow
display on other M5Stack devices in the future.

When powered on, users on an M5Dial can:

- Rotate the encoder to display sample text using different font families and
  the families various individual fonts that vary in size and style (italic &
  bold),
- Press the bottom M5 button to cycle through some dozen sample text strings,
  including ([seven Panagrams] (<https://en.wikipedia.org/wiki/Pangram>)),
  phrases that use all the letters of the alphabet:

      - Pack my box with five dozen liquor jugs
      - The quick brown fox jumps over the lazy dog
      - Glib jocks quiz nymph to vex dwarf
      - Sphinx of black quartz, judge my vow
      - How vexingly quick daft zebras jump!
      - The five boxing wizards jump quickly
      - Jackdaws love my big sphinx of quartz.

![Example of LovyanGFX Font Display showing the FreeMono font](./imgs/FreeMono9.jpg "LovyanGFX Font Display showing the FreeMono font")

## Source code repository

([https://github.com/VashJuan/LovyanGFX_font_display](https://github.com/VashJuan/LovyanGFX_font_display))

## ✨ Features

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

## 🔧 Hardware Requirements

- **M5Dial**: M5Stack Dial device with rotary encoder and display
- **Platform**: Arduino M5Stack Board Manager v2.0.7 or later

## 📚 Dependencies

- **M5GFX**: <https://github.com/m5stack/M5GFX>
- **M5Unified**: <https://github.com/m5stack/M5Unified>

## 🚀 Installation

### Option 1: VSCode with PlatformIO (Recommended) 🎯

The easiest way to get started is using the pre-configured VSCode workspace:

1. **Prerequisites**:
   - [Visual Studio Code](https://code.visualstudio.com/)
   - [PlatformIO IDE Extension](https://platformio.org/install/ide?install=vscode)

2. **Clone and open**:
   ```bash
   git clone https://github.com/vashjuan/m5Dial_font_display.git
   cd LovyanGFX_font_display
   code LovyanGFX_M5Dial.code-workspace
   ```

3. **Install recommended extensions** (VSCode will prompt you):
   - PlatformIO IDE
   - C/C++ Extension Pack
   - Code Spell Checker

4. **Build and upload**:
   - Press `Ctrl+Shift+P` and type "PlatformIO: Build" or use the tasks:
     - `🔨 PIO Build` - Build the project
     - `📤 PIO Upload` - Upload to device
     - `🖥️ PIO Monitor` - Monitor serial output
     - `🧹 PIO Clean` - Clean build files

### Option 2: PlatformIO CLI 🛠️

1. **Install PlatformIO**:

   - [Install PlatformIO IDE](https://platformio.org/platformio-ide) or
   - Install PlatformIO Core: `pip install platformio`

2. **Clone the repository**:

       git clone https://github.com/vashjuan/m5Dial_font_display.git
       cd LovyanGFX_font_display

3. **Build and upload**:

   ```bash
   # Using PlatformIO CLI
   pio run --target upload

   # Or using PlatformIO IDE
   # Open the project folder and click the upload button
   ```

4. **Monitor serial output**:

   ```bash
   pio device monitor
   ```

### Option 3: Arduino IDE 🔧

1. **Clone this repository**:

   ```bash
   git clone https://github.com/vashjuan/m5Dial_font_display.git
   ```

2. **Open project**: Open `LovyanGFX_font_display.ino` in Arduino IDE

3. **Install libraries**: Install required libraries through Arduino Library
   Manager:

   - 📦 M5GFX
   - 📦 M5Unified
   - 📦 M5Dial

4. **Configure**: Select the M5Dial board & appropriate serial port in Arduino
   IDE

5. **Upload**: Upload to your M5Dial device 📤

## 🏗️ VSCode Workspace Features

The included `LovyanGFX_M5Dial.code-workspace` provides:

- **🔧 Preconfigured Tasks**: Build, upload, monitor, and clean with one click
- **📝 IntelliSense**: Full C++ code completion and error detection  
- **🎯 Integrated Terminal**: Direct access to PlatformIO commands
- **📁 Smart File Organization**: Proper exclude patterns for build files
- **✏️ Code Formatting**: Automatic C++ formatting and spell checking
- **🔌 Extension Recommendations**: Auto-prompts for required extensions

### 🎮 Quick Commands in VSCode:
- **Ctrl+Shift+P** → "PlatformIO: Build" - Build the project
- **Ctrl+Shift+P** → "PlatformIO: Upload" - Upload to M5Dial  
- **Ctrl+Shift+P** → "PlatformIO: Serial Monitor" - View serial output
- **Ctrl+Shift+P** → "Tasks: Run Task" - Access custom build tasks

### 🔍 Project Structure

```
LovyanGFX_font_display/
├── 📄 platformio.ini                    # PlatformIO configuration (ESP32-S3)
├── 📋 LovyanGFX_M5Dial.code-workspace   # VSCode workspace configuration  
├── 📁 .vscode/                          # VSCode settings
│   ├── settings.json                    # Editor settings
│   ├── c_cpp_properties.json          # C++ IntelliSense config
│   ├── launch.json                     # Debug configuration
│   └── extensions.json                 # Recommended extensions
├── 📁 src/                              # Source files
│   ├── 🎯 LovyanGFX_font_display.ino    # Main Arduino sketch
│   ├── 🔧 encoder.cpp/hpp              # Encoder handling
│   ├── 🎨 fontmanager.cpp/hpp          # Font display management
│   └── 📱 m5dial.cpp/hpp               # M5Dial device interface
├── 📁 lib/                              # Custom libraries (if any)
├── 📁 include/                          # Header files
├── 📁 imgs/                             # Documentation images
└── 📖 README.md                         # This documentation
```

## 🎮 Usage

1. Power on the M5Dial
2. The device will display "M5 Dial Font Display v 1.0" on startup
3. Rotate the encoder to cycle through different fonts
4. Press the button (at bottom of dial, embossed with "M5") to cycle through the
   sample texts
5. Font information is displayed at the top of the screen
6. Serial monitor shows additional limited debug information

![Example of LovyanGFX Font Display showing the FreeSerif24 font](./imgs/FreeSerif24.jpg "LovyanGFX Font Display showing the FreeSerif24 font")

## 📁 File Structure

- 🎯 `LovyanGFX_font_display.ino` - Main Arduino sketch
- 🔧 `encoder.hpp/cpp` - Encoder handling class
- 🎨 `fontmanager.hpp/cpp` - Font display management class
- 📱 `m5dial.hpp/cpp` - M5Dial device interface
- ⚙️ `platformio.ini` - PlatformIO configuration
- 📖 `README.md` - This documentation

### 🗂️ Class Architecture

```
🎨 FontDisplayManager (fontmanager.hpp)
    ↓ uses
📱 DeviceInterface (abstract)
    ↓ implemented by
📟 M5DialDevice (m5dial.hpp)
    ↓ uses
🔧 EncoderHandler (encoder.hpp)
```

## 📝 Sample Texts

The program cycles through these sample texts when the button is pressed:

- "Hello World!"
- "Font Demo"
- "M5Dial"
- "12345"
- "ABC abc"
- and various panagrams (see
  [www.wikipedia.com/panagram](https://en.wikipedia.org/wiki/Pangram))

## 🖥️ Serial Output

The program outputs font information to the serial monitor for debugging:

- Current encoder position
- Font family name
- Font name
- Font size

## 👨‍💻 Development

### 🛠️ Building with PlatformIO

```bash
# Clean build
pio run --target clean

# Build only
pio run

# Build and upload
pio run --target upload

# Upload filesystem (if applicable)
pio run --target uploadfs

# Monitor serial output
pio device monitor

# Build with verbose output
pio run -v
```

### 🐛 Debugging

- Enable debug output by modifying `build_flags` in `platformio.ini`:

  ```ini
  build_flags =
      -DCORE_DEBUG_LEVEL=5  ; Set to 0-5 for different debug levels
  ```

- Use PlatformIO's built-in debugger (requires compatible hardware debugger)

### 🔧 Customization

- **Add new fonts**: Modify `fontmanager.cpp` to include additional LovyanGFX
  fonts
- **Change sample texts**: Edit the `sampleTexts` array in the main sketch
- **Adjust encoder sensitivity**: Modify encoder parameters in `encoder.cpp`
- **Support other devices**: Implement the `DeviceInterface` for other M5Stack
  devices

## 👨‍💻 Author

**John Cornelison** (<john@vashonSoftware.com>)

## 📋 Version

**v1.0** - Initial release (2025-12-16)

## 📜 License

This project is open source. Feel free to use, modify, and distribute.

## 🤝 Contributing

🎉 Contributions are welcome! Here's how you can help:

1. 🍴 Fork the repository
2. 🌿 Create a feature branch (`git checkout -b feature/amazing-feature`)
3. 💾 Commit your changes (`git commit -m 'Add some amazing feature'`)
4. 📤 Push to the branch (`git push origin feature/amazing-feature`)
5. 🔄 Open a Pull Request

### 💡 Ideas for contributions

- 🎨 Add support for more M5Stack devices
- 🌍 Add internationalization support
- 🎵 Add sound feedback
- 📊 Add font metrics display
- 🎭 Add font preview animations

---

<div align="center">

### 🌟 If you found this project helpful, please give it a star! ⭐

**Made with ❤️ for the M5Stack community**

📧 [Report Issues](https://github.com/vashjuan/m5Dial_font_display/issues) • 💬
[Discussions](https://github.com/vashjuan/m5Dial_font_display/discussions) • 🚀
[Latest Release](https://github.com/vashjuan/m5Dial_font_display/releases)

</div>
