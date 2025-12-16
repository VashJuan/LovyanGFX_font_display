/**
 * @file fontmanager.cpp
 * @brief Font Display Manager Implementation
 * @version 1.0
 * @date 2025-12-16
 *
 * @Hardwares: M5Dial
 * @Platform Version: Arduino M5Stack Board Manager v2.0.7
 * @Dependent Library:
 * M5GFX: https://github.com/m5stack/M5GFX
 * M5Unified: https://github.com/m5stack/M5Unified
 */

#include "fontmanager.hpp"
#include "M5Dial.h"  // For font definitions

// Define font families with font pointers for easy iteration
const FontInfo fontFamilies[][20] = {
    // Built-in LGFX fonts
    {
        {"lgfx_fonts", "Font0", 0, &fonts::Font0},
        {"lgfx_fonts", "Font2", 2, &fonts::Font2},
        {"lgfx_fonts", "Font4", 4, &fonts::Font4},
        {"lgfx_fonts", "Font6", 6, &fonts::Font6},
        {"lgfx_fonts", "Font7", 7, &fonts::Font7},
        {"lgfx_fonts", "Font8", 8, &fonts::Font8},
        {nullptr, nullptr, 0, nullptr} // End marker
    },
    // Free Mono family
    {
        {"Free Mono", "FreeMono9pt7b", 9, &fonts::FreeMono9pt7b},
        {"Free Mono", "FreeMono12pt7b", 12, &fonts::FreeMono12pt7b},
        {"Free Mono", "FreeMono18pt7b", 18, &fonts::FreeMono18pt7b},
        {"Free Mono", "FreeMono24pt7b", 24, &fonts::FreeMono24pt7b},
        {"Free Mono", "FreeMonoBold9pt7b", 9, &fonts::FreeMonoBold9pt7b},
        {"Free Mono", "FreeMonoBold12pt7b", 12, &fonts::FreeMonoBold12pt7b},
        {"Free Mono", "FreeMonoBold18pt7b", 18, &fonts::FreeMonoBold18pt7b},
        {"Free Mono", "FreeMonoBold24pt7b", 24, &fonts::FreeMonoBold24pt7b},
        {nullptr, nullptr, 0, nullptr} // End marker
    },
    // Free Sans family
    {
        {"Free Sans", "FreeSans9pt7b", 9, &fonts::FreeSans9pt7b},
        {"Free Sans", "FreeSans12pt7b", 12, &fonts::FreeSans12pt7b},
        {"Free Sans", "FreeSans18pt7b", 18, &fonts::FreeSans18pt7b},
        {"Free Sans", "FreeSans24pt7b", 24, &fonts::FreeSans24pt7b},
        {"Free Sans", "FreeSansBold9pt7b", 9, &fonts::FreeSansBold9pt7b},
        {"Free Sans", "FreeSansBold12pt7b", 12, &fonts::FreeSansBold12pt7b},
        {"Free Sans", "FreeSansBold18pt7b", 18, &fonts::FreeSansBold18pt7b},
        {"Free Sans", "FreeSansBold24pt7b", 24, &fonts::FreeSansBold24pt7b},
        {nullptr, nullptr, 0, nullptr} // End marker
    },
    // Free Serif family
    {
        {"Free Serif", "FreeSerif9pt7b", 9, &fonts::FreeSerif9pt7b},
        {"Free Serif", "FreeSerif12pt7b", 12, &fonts::FreeSerif12pt7b},
        {"Free Serif", "FreeSerif18pt7b", 18, &fonts::FreeSerif18pt7b},
        {"Free Serif", "FreeSerif24pt7b", 24, &fonts::FreeSerif24pt7b},
        {"Free Serif", "FreeSerifBold9pt7b", 9, &fonts::FreeSerifBold9pt7b},
        {"Free Serif", "FreeSerifBold12pt7b", 12, &fonts::FreeSerifBold12pt7b},
        {"Free Serif", "FreeSerifBold18pt7b", 18, &fonts::FreeSerifBold18pt7b},
        {"Free Serif", "FreeSerifBold24pt7b", 24, &fonts::FreeSerifBold24pt7b},
        {nullptr, nullptr, 0, nullptr} // End marker
    },
    // Special fonts
    {
        {"Orbitron", "Orbitron_Light_24", 24, &fonts::Orbitron_Light_24},
        {"Orbitron", "Orbitron_Medium_24", 24, &fonts::Orbitron_Medium_20},
        {"Roboto", "Roboto_Thin_24", 24, &fonts::Roboto_Thin_24},
        {"DejaVu", "DejaVu12", 12, &fonts::DejaVu12},
        {"DejaVu", "DejaVu18", 18, &fonts::DejaVu18},
        {"DejaVu", "DejaVu24", 24, &fonts::DejaVu24},
        {nullptr, nullptr, 0, nullptr} // End marker
    }
};

const int NUM_FONT_FAMILIES = 5;

// Constructor implementation
FontDisplayManager::FontDisplayManager(DeviceInterface* deviceInterface) : 
    currentFamilyIndex(0), 
    currentFontIndex(0), 
    lastEncoderPosition(-999), 
    sampleText("Sample Text 123"),
    displayChanged(true),
    device(deviceInterface)
{
}

void FontDisplayManager::setDevice(DeviceInterface* deviceInterface)
{
    device = deviceInterface;
    displayChanged = true;
}

// Private method implementations
int FontDisplayManager::getFontsInFamily(int familyIndex) const
{
    if (familyIndex < 0 || familyIndex >= NUM_FONT_FAMILIES) {
        return 0;
    }
    
    int count = 0;
    while (fontFamilies[familyIndex][count].family != nullptr) {
        count++;
    }
    return count;
}

String FontDisplayManager::getFamilyName(int familyIndex) const
{
    if (familyIndex < 0 || familyIndex >= NUM_FONT_FAMILIES) {
        return "Unknown";
    }

    if (fontFamilies[familyIndex][0].family != nullptr) {
        return String(fontFamilies[familyIndex][0].family);
    }
    return "Empty Family";
}

String FontDisplayManager::getFontName(int familyIndex, int fontIndex) const
{
    if (familyIndex < 0 || familyIndex >= NUM_FONT_FAMILIES) {
        return "Invalid Family";
    }
    
    int fontsInFamily = getFontsInFamily(familyIndex);
    if (fontIndex < 0 || fontIndex >= fontsInFamily) {
        return "Invalid Font";
    }

    return String(fontFamilies[familyIndex][fontIndex].name);
}

void FontDisplayManager::mapEncoderToFont(long encoderPosition)
{
    // Calculate total number of fonts across all families
    int totalFonts = 0;
    for (int i = 0; i < NUM_FONT_FAMILIES; i++) {
        totalFonts += getFontsInFamily(i);
    }

    if (totalFonts == 0) {
        currentFamilyIndex = 0;
        currentFontIndex = 0;
        return;
    }

    // Ensure position is positive and wrap around
    long positivePosition = ((encoderPosition % totalFonts) + totalFonts) % totalFonts;
    
    // Find which family and font index this position corresponds to
    int currentPos = 0;
    for (int familyIdx = 0; familyIdx < NUM_FONT_FAMILIES; familyIdx++) {
        int fontsInThisFamily = getFontsInFamily(familyIdx);
        if (positivePosition < currentPos + fontsInThisFamily) {
            currentFamilyIndex = familyIdx;
            currentFontIndex = positivePosition - currentPos;
            return;
        }
        currentPos += fontsInThisFamily;
    }

    // Fallback
    currentFamilyIndex = 0;
    currentFontIndex = 0;
}

// Public method implementations
void FontDisplayManager::setSampleText(const char* text)
{
    sampleText = text;
    displayChanged = true;
}

void FontDisplayManager::update(long encoderPosition)
{
    // Check if encoder position has changed
    if (encoderPosition != lastEncoderPosition) {
        mapEncoderToFont(encoderPosition);
        lastEncoderPosition = encoderPosition;
        displayChanged = true;
    }

    // Update display if needed
    if (displayChanged) {
        displayCurrentFont();
        displayChanged = false;
    }
}

void FontDisplayManager::displayCurrentFont()
{
    if (device == nullptr) {
        return; // Cannot display without a device
    }
    
    String familyName = getFamilyName(currentFamilyIndex);
    String fontName = getFontName(currentFamilyIndex, currentFontIndex);
    int fontSize = getCurrentFontSize();
    const lgfx::IFont* fontPtr = getCurrentFontPtr();
    
    device->displayFont(familyName, fontName, fontSize, fontPtr, sampleText);
}

void FontDisplayManager::displaySampleText()
{
    // This method is now handled by the device interface
    // The actual font rendering and text display is delegated to the device
    displayCurrentFont();
}

String FontDisplayManager::getCurrentFamilyName() const
{
    return getFamilyName(currentFamilyIndex);
}

String FontDisplayManager::getCurrentFontName() const
{
    return getFontName(currentFamilyIndex, currentFontIndex);
}

int FontDisplayManager::getTotalFamilies() const
{
    return NUM_FONT_FAMILIES;
}

int FontDisplayManager::getFontsInCurrentFamily() const
{
    return getFontsInFamily(currentFamilyIndex);
}

int FontDisplayManager::getCurrentFamilyIndex() const
{
    return currentFamilyIndex;
}

int FontDisplayManager::getCurrentFontIndex() const
{
    return currentFontIndex;
}

void FontDisplayManager::forceUpdate()
{
    displayChanged = true;
}

int FontDisplayManager::getCurrentFontSize() const
{
    if (currentFamilyIndex >= 0 && currentFamilyIndex < NUM_FONT_FAMILIES &&
        currentFontIndex >= 0 && currentFontIndex < getFontsInFamily(currentFamilyIndex)) {
        return fontFamilies[currentFamilyIndex][currentFontIndex].size;
    }
    return 0;
}

const lgfx::IFont* FontDisplayManager::getCurrentFontPtr() const
{
    if (currentFamilyIndex >= 0 && currentFamilyIndex < NUM_FONT_FAMILIES &&
        currentFontIndex >= 0 && currentFontIndex < getFontsInFamily(currentFamilyIndex)) {
        return fontFamilies[currentFamilyIndex][currentFontIndex].fontPtr;
    }
    return nullptr;
}

int FontDisplayManager::getTotalFonts() const
{
    int totalFonts = 0;
    for (int i = 0; i < NUM_FONT_FAMILIES; i++) {
        totalFonts += getFontsInFamily(i);
    }
    return totalFonts;
}

const FontInfo* FontDisplayManager::getFontByAbsoluteIndex(int absoluteIndex) const
{
    if (absoluteIndex < 0) {
        return nullptr;
    }
    
    int currentPos = 0;
    for (int familyIdx = 0; familyIdx < NUM_FONT_FAMILIES; familyIdx++) {
        int fontsInThisFamily = getFontsInFamily(familyIdx);
        if (absoluteIndex < currentPos + fontsInThisFamily) {
            int fontIdx = absoluteIndex - currentPos;
            return &fontFamilies[familyIdx][fontIdx];
        }
        currentPos += fontsInThisFamily;
    }
    
    return nullptr;
}

// Global instance for easy access
FontDisplayManager fontManager;