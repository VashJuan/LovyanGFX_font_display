/**
 * @file m5dial.cpp
 * @brief M5Dial Device Interface Implementation
 * @version 1.0
 * @date 2025-12-16
 *
 * @Hardwares: M5Dial
 * @Platform Version: Arduino M5Stack Board Manager v2.0.7
 * @Dependent Library:
 * M5GFX: https://github.com/m5stack/M5GFX
 * M5Unified: https://github.com/m5stack/M5Unified
 */

#include "m5dial.hpp"

M5DialDevice::M5DialDevice()
{
}

void M5DialDevice::begin()
{
    auto cfg = M5.config();
    M5Dial.begin(cfg, true, false);
}

void M5DialDevice::clearDisplay()
{
    M5Dial.Display.fillScreen(BLACK);
}

int M5DialDevice::getDisplayWidth() const
{
    return M5Dial.Display.width();
}

int M5DialDevice::getDisplayHeight() const
{
    return M5Dial.Display.height();
}

void M5DialDevice::setFont(const String& fontName)
{
    if (fontName.indexOf("FreeMono") >= 0) {
        if (fontName.indexOf("24pt") >= 0) {
            M5Dial.Display.setFont(&fonts::FreeMono24pt7b);
        } else if (fontName.indexOf("18pt") >= 0) {
            M5Dial.Display.setFont(&fonts::FreeMono18pt7b);
        } else if (fontName.indexOf("12pt") >= 0) {
            M5Dial.Display.setFont(&fonts::FreeMono12pt7b);
        } else {
            M5Dial.Display.setFont(&fonts::FreeMono9pt7b);
        }
    } else if (fontName.indexOf("FreeSans") >= 0) {
        if (fontName.indexOf("24pt") >= 0) {
            M5Dial.Display.setFont(&fonts::FreeSans24pt7b);
        } else if (fontName.indexOf("18pt") >= 0) {
            M5Dial.Display.setFont(&fonts::FreeSans18pt7b);
        } else if (fontName.indexOf("12pt") >= 0) {
            M5Dial.Display.setFont(&fonts::FreeSans12pt7b);
        } else {
            M5Dial.Display.setFont(&fonts::FreeSans9pt7b);
        }
    } else if (fontName.indexOf("FreeSerif") >= 0) {
        if (fontName.indexOf("24pt") >= 0) {
            M5Dial.Display.setFont(&fonts::FreeSerif24pt7b);
        } else if (fontName.indexOf("18pt") >= 0) {
            M5Dial.Display.setFont(&fonts::FreeSerif18pt7b);
        } else if (fontName.indexOf("12pt") >= 0) {
            M5Dial.Display.setFont(&fonts::FreeSerif12pt7b);
        } else {
            M5Dial.Display.setFont(&fonts::FreeSerif9pt7b);
        }
    } else if (fontName.indexOf("Orbitron") >= 0) {
        M5Dial.Display.setFont(&fonts::Orbitron_Light_24);
    } else if (fontName.indexOf("Roboto") >= 0) {
        M5Dial.Display.setFont(&fonts::Roboto_Thin_24);
    } else if (fontName.indexOf("DejaVu") >= 0) {
        if (fontName.indexOf("24") >= 0) {
            M5Dial.Display.setFont(&fonts::DejaVu24);
        } else if (fontName.indexOf("18") >= 0) {
            M5Dial.Display.setFont(&fonts::DejaVu18);
        } else {
            M5Dial.Display.setFont(&fonts::DejaVu12);
        }
    } else {
        // Default to built-in fonts for lgfx_fonts family
        if (fontName.indexOf("Font8") >= 0) {
            M5Dial.Display.setFont(&fonts::Font8);
        } else if (fontName.indexOf("Font7") >= 0) {
            M5Dial.Display.setFont(&fonts::Font7);
        } else if (fontName.indexOf("Font6") >= 0) {
            M5Dial.Display.setFont(&fonts::Font6);
        } else if (fontName.indexOf("Font4") >= 0) {
            M5Dial.Display.setFont(&fonts::Font4);
        } else if (fontName.indexOf("Font2") >= 0) {
            M5Dial.Display.setFont(&fonts::Font2);
        } else {
            M5Dial.Display.setFont(&fonts::Font0);
        }
    }
}

void M5DialDevice::drawWrappedText(const char* text, int centerX, int centerY)
{
    String sampleText = String(text);
    
/**  * Helper function to calculate string width in pixels
  * Source: https://codingtechroom.com/question/-calculate-string-font-width-pixels
  */
function getStringWidth(text, font) {
  const canvas = document.createElement('canvas');
  const context = canvas.getContext('2d');
  context.font = font;
  const textWidth = context.measureText(text).width;
  return textWidth;
}
    


    // if wider than the display, insert carriage returns
    int textWidth = M5Dial.Display.textWidth(sampleText);
    if (textWidth > getDisplayWidth() - 20) {
        String modifiedText;
        int lineWidth = 0;
        for (unsigned int i = 0; i < sampleText.length(); i++) {
            char c = sampleText.charAt(i);
            lineWidth += M5Dial.Display.textWidth(String(c));
            if (lineWidth > getDisplayWidth() - 20 && c == ' ') {
                modifiedText += '\n';
                lineWidth = 0;
            } else {
                modifiedText += c;
            }
        }
        sampleText = modifiedText;
    }
    
    M5Dial.Display.drawString(sampleText, centerX, centerY);
}

void M5DialDevice::displayFont(const String& familyName, const String& fontName, 
                               int fontSize, const char* sampleText)
{
    clearDisplay();
    
    const int center_x = getDisplayWidth() / 2;

    // Display family name at top - use built-in font for info display
    M5Dial.Display.setFont(&fonts::Font2);
    M5Dial.Display.setTextColor(GREEN);
    M5Dial.Display.setTextDatum(top_left);
    M5Dial.Display.setTextSize(1);

    String familyStr = "Family: " + familyName;
    M5Dial.Display.drawString(familyStr, center_x - (M5Dial.Display.textWidth(familyStr) / 2), 15);

    // Display font name
    String fontStr = "Font: " + fontName;
    M5Dial.Display.drawString(fontStr, center_x - (M5Dial.Display.textWidth(fontStr) / 2), 30);

    // Display font size
    String sizeStr = "Size: " + String(fontSize);
    M5Dial.Display.drawString(sizeStr, center_x - (M5Dial.Display.textWidth(sizeStr) / 2), 45);

    // Set the actual font for sample text display
    setFont(fontName);
    M5Dial.Display.setTextColor(WHITE);
    M5Dial.Display.setTextDatum(middle_center);
    
    // Display sample text with the current font
    int centerY = getDisplayHeight() / 2;
    drawWrappedText(sampleText, center_x, centerY);

    // Display navigation info at bottom
    M5Dial.Display.setFont(&fonts::Font2);
    M5Dial.Display.setTextColor(YELLOW);
    M5Dial.Display.setTextDatum(bottom_center);
    M5Dial.Display.drawString("Turn encoder: change font", getDisplayWidth() / 2, getDisplayHeight() - 40);
    M5Dial.Display.drawString("Press button: change text", getDisplayWidth() / 2, getDisplayHeight() - 25);
}

bool M5DialDevice::wasButtonPressed()
{
    return M5Dial.BtnA.wasPressed();
}

void M5DialDevice::update()
{
    M5Dial.update();
}

void M5DialDevice::showStartupMessage(const char* message)
{
    clearDisplay();
    M5Dial.Display.setTextColor(GREEN);
    M5Dial.Display.setTextDatum(middle_center);
    M5Dial.Display.setTextSize(1);
    M5Dial.Display.setFont(&fonts::Font2);
    M5Dial.Display.drawString(message, getDisplayWidth() / 2, getDisplayHeight() / 2 + 15);
}

// Global instance for easy access
M5DialDevice m5dialDevice;