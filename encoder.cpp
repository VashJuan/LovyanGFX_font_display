#include "encoder.hpp"

// Constructor
Encoder::Encoder() : oldPosition(-999) {
    // Initialize with default position
}

// Destructor
Encoder::~Encoder() {
    // Cleanup if needed
}

void Encoder::setup() {
    //M5Dial.Display.drawString("Encoder Test", M5Dial.Display.width() / 2, M5Dial.Display.height() / 2);
    //delay(2000);
    oldPosition = -999;
}

void Encoder::update() {
    long newPosition = M5Dial.Encoder.read();

    if (newPosition != oldPosition) {
        //M5Dial.Speaker.tone(8000, 20);
        //M5Dial.Display.clear();
        oldPosition = newPosition;
        //Serial.println(newPosition);
        //M5Dial.Display.drawString(String(newPosition), M5Dial.Display.width() / 2, M5Dial.Display.height() / 2);
    }

    if (M5Dial.BtnA.wasPressed()) {
        //M5Dial.Speaker.tone(8000, 20);
        //M5Dial.Display.clear();
        //M5Dial.Display.drawString("Pressing", M5Dial.Display.width() / 2, M5Dial.Display.height() / 2);
        // M5Dial.Encoder.readAndReset(); // reboot!                          
    }
    
    if (M5Dial.BtnA.wasReleased()) {
        //M5Dial.Speaker.tone(8000, 20);
        //M5Dial.Display.clear();
        //M5Dial.Display.drawString("Released!!!", M5Dial.Display.width() / 2,M5Dial.Display.height() / 2);
    }

    // UI: If button pressed for 5 seconds, reset encoder position to 100
    if (M5Dial.BtnA.pressedFor(5000)) {
        M5Dial.Encoder.write(100);
    }
}

long Encoder::getPosition() {
    return M5Dial.Encoder.read();
}

void Encoder::setPosition(long position) {
    //M5Dial.Encoder.write(position);
    oldPosition = position;
}

void Encoder::resetPosition(int position) {
    //M5Dial.Encoder.write(position);
    oldPosition = position;
}

bool Encoder::hasPositionChanged() {
    long currentPosition = M5Dial.Encoder.read();
    return currentPosition != oldPosition;
}

long Encoder::getOldPosition() const {
    return oldPosition;
}

// Global instance for easy access
Encoder encoder;