# Library Dependencies

This directory can be used for project-specific libraries.

PlatformIO will automatically install the dependencies specified in
`platformio.ini`:

- **M5GFX**: Graphics library for M5Stack devices
- **M5Unified**: Unified M5Stack hardware interface
- **M5Dial**: M5Stack Dial device-specific library

## Adding Custom Libraries

If you need to add custom libraries that aren't available in the PlatformIO
registry:

1. Clone or download the library to this `lib/` directory
2. Ensure the library follows PlatformIO's structure requirements
3. The library will be automatically included in builds

## Library Structure

```
lib/
├── CustomLibrary/
│   ├── library.json    # Library metadata (optional)
│   ├── src/           # Source files
│   └── examples/      # Example code (optional)
└── README.md          # This file
```

For more information, visit:
[PlatformIO Library Manager Documentation](https://docs.platformio.org/en/latest/librarymanager/)
