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
    //M5.Display.drawString("Encoder Test", M5.Display.width() / 2, M5.Display.height() / 2);
    //delay(2000);
    oldPosition = -999;
}

long Encoder::getPosition() {
    return M5.Encoder.read();
}

bool Encoder::hasPositionChanged() {
    long currentPosition = M5.Encoder.read();
    return currentPosition != oldPosition;
}

// Global instance for easy access
Encoder encoder;
