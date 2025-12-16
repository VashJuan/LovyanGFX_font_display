/**
 * @file LovyanGFX_font_display.ino
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

#include "M5Dial.h"
#include "encoder.hpp"
#include "fontmanager.hpp"

void setup()
{
    auto cfg = M5.config();
    M5Dial.begin(cfg, true, false);
    Serial.begin(115200);

    Serial.println("Font Display starting...");

    M5Dial.Display.fillScreen(BLACK);
    M5Dial.Display.setTextColor(GREEN);
    M5Dial.Display.setTextDatum(middle_center);
    M5Dial.Display.setTextSize(1);

    M5Dial.Display.drawString("M5 Dial Font Display v 1.0", M5Dial.Display.width() / 2, M5Dial.Display.height() / 2);
    delay(750);

    encoder.setup();

    // Initialize font manager with sample text
    fontManager.setSampleText("Hello World!");

    Serial.println("Setup done.");
    Serial.println("Total font families: " + String(fontManager.getTotalFamilies()));
}

void loop()
{
    M5Dial.update();

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
    if (M5Dial.BtnA.wasPressed())
    {
        static int textIndex = 0;
        const char *sampleTexts[] = {
            "Hello World!",
            "Font Demo",
            "M5Dial",
            "12345",
            "ABC abc"};

        textIndex = (textIndex + 1) % 5;
        fontManager.setSampleText(sampleTexts[textIndex]);
        fontManager.forceUpdate();

        // TODO: Cycle through pangrams
        /*
            static int pangramIndex = 0;
            fontManager.setSampleText(fontManager.pangrams[pangramIndex]);
            pangramIndex = (pangramIndex + 1) % 7;
            fontManager.forceUpdate();
            */

        Serial.println("Sample text changed to: " + String(sampleTexts[textIndex]));
    }
}