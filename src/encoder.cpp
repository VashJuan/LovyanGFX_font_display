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
    // Setup encoder pins as input with pullup
    // M5Dial encoder pins: A=40, B=41
    pinMode(40, INPUT_PULLUP);
    pinMode(41, INPUT_PULLUP);
    
    // Get initial position
    oldPosition = getPosition();
}

long Encoder::getPosition() {
    // Use M5Unified's direct encoder reading for M5Dial
    // The encoder is connected to specific GPIO pins on M5Dial
    static int32_t encoder_count = 0;
    static bool last_a = false, last_b = false;
    
    // M5Dial encoder pins: A=40, B=41 (common configuration)
    bool a = digitalRead(40);
    bool b = digitalRead(41);
    
    if (last_a != a || last_b != b) {
        if (last_a && !a) {  // falling edge on A
            if (b) encoder_count++;
            else encoder_count--;
        }
        last_a = a;
        last_b = b;
    }
    
    return encoder_count;
}

bool Encoder::hasPositionChanged() {
    long currentPosition = getPosition();
    if (currentPosition != oldPosition) {
        oldPosition = currentPosition;
        return true;
    }
    return false;
}

void Encoder::resetPosition() {
    // Reset encoder position to 0 by updating our internal counter
    getPosition(); // Initialize static variables
    oldPosition = 0;
}

void Encoder::setPosition(long position) {
    // Set encoder to specific position by updating our tracking
    oldPosition = position;
}

// Global instance for easy access
Encoder encoder;
