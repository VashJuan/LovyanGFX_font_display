/**
 * @file LovyanGFX_font_display.cpp
 * @url https://github.com/vashjuan/M5Dial_font_display
 * @author John Cornelison (john@vashonSoftware.com)
 * @brief Display all LovyanGFX fonts, (on M5Dial) using an encoder to scroll through them.
  This is a demo program for M5Dial to show the various fonts available in LovyanGFX.
  Use the encoder to scroll through the fonts displayed on the screen.
 * @version 1.0
 * @date 2025-12-15
 *
 * @Hardwares: M5Dial
 * @Platform Version: Arduino M5Stack Board Manager v2.0.7
 * @Dependent Library:
 * M5GFX: https://github.com/m5stack/M5GFX
 * M5Unified: https://github.com/m5stack/M5Unified
 */

#include <Arduino.h>
#include <M5Unified.h>
#include "encoder.hpp"
#include "fontmanager.hpp"
#include "m5dial.hpp"

void setup()
{
    Serial.begin(115200);
    Serial.println("Font Display starting...");

    // Initialize M5Dial device
    m5DialDevice.begin();
    m5DialDevice.showStartupMessage("M5 Dial Font Display v 1.0");
    delay(750);

    encoder.setup();

    // Initialize font manager with device interface and sample text
    fontManager.setDevice(&m5DialDevice);
    fontManager.setSampleText("Hello World!");

    Serial.println("Setup done.");
    Serial.println("Total font families: " + String(fontManager.getTotalFamilies()));
}

void loop()
{
    m5DialDevice.update();

    // Check if encoder position changed
    if (encoder.hasPositionChanged())
    {
        long position = encoder.getPosition();
        Serial.println("Encoder position: " + String(position));

        // Update font display based on encoder position
        fontManager.update(position);

        // Print current font info to serial
        Serial.println("Family: " + fontManager.getCurrentFamilyName());
        Serial.println("Font: " + fontManager.getCurrentFontName());
        Serial.println("Size: " + String(fontManager.getCurrentFontSize()));
        Serial.println("---");
    }

    // Handle button press to change sample text
    if (M5.BtnA.wasPressed())
    {
        static int textIndex = 0;

        const char *sampleTexts[] = {
            "Hello World!",
            "Font Demo",
            "M5Dial",
            "12345",
            "ABC abc",
            // https://en.wikipedia.org/wiki/Pangram
            "Pack my box with five dozen liquor jugs",
            "The quick brown fox jumps over the lazy dog",
            "Glib jocks quiz nymph to vex dwarf.",
            "Sphinx of black quartz, judge my vow.",
            "How vexingly quick daft zebras jump!",
            "The five boxing wizards jump quickly.",
            "Jackdaws love my big sphinx of quartz."};

        textIndex = (textIndex + 1) % 12;
        fontManager.setSampleText(sampleTexts[textIndex]);
        fontManager.forceUpdate();

        Serial.println("Sample text changed to: " + String(sampleTexts[textIndex]));
    }
}