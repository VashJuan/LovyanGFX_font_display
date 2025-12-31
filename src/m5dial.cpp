/**
 * @file M5.cpp
 * @brief M5Dial Device Interface Implementation
 * @date 2025-12-16
 *
 * @Hardwares: M5Dial
 * @Platform Version: Arduino M5Stack Board Manager v2.0.7
 * @Dependent Library:
 * M5GFX: https://github.com/m5stack/M5GFX
 * M5Unified: https://github.com/m5stack/M5Unified
 */

#include "m5dial.hpp"
#include <vector>

M5DialDevice::M5DialDevice()
{
}

void M5DialDevice::begin()
{
    auto cfg = M5.config();
    M5.begin(cfg);
}

void M5DialDevice::clearDisplay()
{
    M5.Display.fillScreen(BLACK);
}

int M5DialDevice::getDisplayWidth() const
{
    return M5.Display.width();
}

int M5DialDevice::getDisplayHeight() const
{
    return M5.Display.height();
}

void M5DialDevice::drawWrappedText(const char *text, int centerX, int centerY)
{
    String sampleText = String(text);

    int textWidth = M5.Display.textWidth(sampleText);
    int maxWidth = getDisplayWidth() - 20;

    if (textWidth <= maxWidth)
    {
        // Fits on one line
        M5.Display.drawString(sampleText, centerX, centerY);
        return;
    }

    // Need to wrap - build lines that fit
    std::vector<String> lines;
    String currentLine = "";
    int currentWidth = 0;

    for (unsigned int i = 0; i < sampleText.length(); i++)
    {
        char c = sampleText.charAt(i);
        int charWidth = M5.Display.textWidth(String(c));

        // Check if adding this character would exceed width
        if (currentWidth + charWidth > maxWidth && currentLine.length() > 0)
        {
            // Try to break at last space
            int lastSpace = currentLine.lastIndexOf(' ');
            if (lastSpace > 0 && lastSpace < currentLine.length() - 1)
            {
                // Break at space
                lines.push_back(currentLine.substring(0, lastSpace));
                currentLine = currentLine.substring(lastSpace + 1) + c;
                currentWidth = M5.Display.textWidth(currentLine);
            }
            else
            {
                // No space found, force break
                lines.push_back(currentLine);
                currentLine = String(c);
                currentWidth = charWidth;
            }
        }
        else
        {
            currentLine += c;
            currentWidth += charWidth;
        }
    }

    // Add last line
    if (currentLine.length() > 0)
    {
        lines.push_back(currentLine);
    }

    // Calculate line height and draw centered
    int lineHeight = M5.Display.fontHeight();
    int totalHeight = lineHeight * lines.size();
    int startY = centerY - (totalHeight / 2);

    for (size_t i = 0; i < lines.size(); i++)
    {
        M5.Display.drawString(lines[i], centerX, startY + (i * lineHeight));
    }
}

void M5DialDevice::displayFont(const String &familyName, const String &fontName,
                               int fontSize, const lgfx::IFont *fontPtr, const char *sampleText)
{
    clearDisplay();

    const int center_x = getDisplayWidth() / 2;

    // Display family name at top - use built-in font for info display
    M5.Display.setFont(&fonts::Font2);
    M5.Display.setTextColor(GREEN);
    M5.Display.setTextDatum(top_left);
    M5.Display.setTextSize(1);

    String familyStr = "Family: " + familyName;
    M5.Display.drawString(familyStr, center_x - (M5.Display.textWidth(familyStr) / 2), 15);

    // Display font name
    String fontStr = "Font: " + fontName;
    M5.Display.drawString(fontStr, center_x - (M5.Display.textWidth(fontStr) / 2), 30);

    // Display font size
    String sizeStr = "Size: " + String(fontSize);
    M5.Display.drawString(sizeStr, center_x - (M5.Display.textWidth(sizeStr) / 2), 45);

    // Set the actual font for sample text display using font pointer
    if (fontPtr != nullptr)
    {
        M5.Display.setFont(fontPtr);
    }
    else
    {
        M5.Display.setFont(&fonts::Font2); // Fallback font
    }
    M5.Display.setTextColor(WHITE);
    M5.Display.setTextDatum(middle_center);

    // Display sample text with the current font
    int centerY = getDisplayHeight() / 2;
    drawWrappedText(sampleText, center_x, centerY);

    // Display navigation info at bottom
    M5.Display.setFont(&fonts::Font2);
    M5.Display.setTextColor(YELLOW);
    M5.Display.setTextDatum(bottom_center);
    M5.Display.drawString("Turn encoder: change font", getDisplayWidth() / 2, getDisplayHeight() - 40);
    M5.Display.drawString("Press button: change text", getDisplayWidth() / 2, getDisplayHeight() - 25);
}

bool M5DialDevice::wasButtonPressed()
{
    return M5.BtnA.wasPressed();
}

void M5DialDevice::update()
{
    M5.update();
}

void M5DialDevice::showStartupMessage(const char *message)
{
    const int centerX = getDisplayWidth() / 2;
    const int offsetY = getDisplayHeight() / 2;

    clearDisplay();

    M5.Display.setTextColor(GREEN);
    M5.Display.setTextDatum(middle_center);
    M5.Display.setTextSize(1);
    M5.Display.setFont(&fonts::Satisfy_24);
    drawWrappedText(message, centerX, offsetY - 40);
    M5.Display.drawLine(0, offsetY - 20, getDisplayWidth(), offsetY - 20, WHITE);

    M5.Display.setTextColor(WHITE);
    M5.Display.setTextDatum(middle_center);
    M5.Display.setTextSize(1);

    M5.Display.setFont(&fonts::DejaVu12);
    drawWrappedText("https://github.com/VashJuan/ LovyanGFX_font_display", centerX, offsetY + 10);
    M5.Display.setFont(&fonts::FreeMono12pt7b);
    M5.Display.setTextColor(VIOLET);
    drawWrappedText("Rotate dial to scroll thru fonts", centerX, offsetY + 70);
}

// Global instance for easy access
M5DialDevice m5DialDevice;
