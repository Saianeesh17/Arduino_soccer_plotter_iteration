#include <Stepper.h>

int motorSpeed = 10;
Stepper myStepper(2048, 8, 10, 9, 11);  // X-axis motor (Steps per Revoluton, IN1, IN3, IN2, IN4)
Stepper myStepper2(2048, 2, 4, 3, 5);   // Y-axis motor (Steps per Revoluton, IN1, IN3, IN2, IN4)
const int xMaxSteps = 2048;  // Max steps for x-axis
const int yMaxSteps = 2048;  // Max steps for y-axis

// Variables to store current absolute position of each motor
int currentXPos = 0;
int currentYPos = 0;

// Arrays to store x and y coordinates
float x_coords[10];
float y_coords[10];
int index = 0;

void setup() {
    Serial.begin(9600);
    while (!Serial) {;}  // Wait for serial connection to initialize

    // initialize motors with appropriate speed
    myStepper.setSpeed(motorSpeed);
    myStepper2.setSpeed(motorSpeed);

    Serial.println("Ready to receive coordinates...");
}

void loop() {
    if (Serial.available() > 0) {
        String data = Serial.readStringUntil('\n');  // Read the whole line of data

        // Parse data and store coordinates
        int startIndex = 0;
        int semicolonIndex = data.indexOf(';');
        index = 0;

        // Receive and store all coordinates
        while (semicolonIndex >= 0 && index < 10) {
            String coordPair = data.substring(startIndex, semicolonIndex);
            int commaIndex = coordPair.indexOf(',');

            if (commaIndex >= 0) {
                x_coords[index] = coordPair.substring(0, commaIndex).toFloat() / 100.0;  // Convert percentage to ratio
                y_coords[index] = coordPair.substring(commaIndex + 1).toFloat() / 100.0; // Convert percentage to ratio
                Serial.print("Received x: ");
                Serial.print(x_coords[index] * 100);  // Print percentage for clarity
                Serial.print(", y: ");
                Serial.println(y_coords[index] * 100);
                index++;
            }

            startIndex = semicolonIndex + 1;
            semicolonIndex = data.indexOf(';', startIndex);
        }

        // After receiving all coordinates, move the motors
        for (int i = 0; i < index; i++) {
            int targetXSteps = round(x_coords[i] * xMaxSteps);  // Convert x ratio to steps
            int targetYSteps = round(y_coords[i] * yMaxSteps);  // Convert y ratio to steps
            
            // Calculate the difference from the current position
            int xStepDifference = targetXSteps - currentXPos;
            int yStepDifference = targetYSteps - currentYPos;

            // Determine the direction of movement
            int xDirection = (xStepDifference > 0) ? 1 : -1;
            int yDirection = (yStepDifference > 0) ? 1 : -1;

            // Move the motors simultaneously
            while (xStepDifference != 0 || yStepDifference != 0) {
                if (xStepDifference != 0) {
                    myStepper.step(xDirection);
                    xStepDifference -= xDirection;
                }
                if (yStepDifference != 0) {
                    myStepper2.step(-yDirection);  // Inverted y-axis movement
                    yStepDifference -= yDirection;
                }
            }

            // Update current positions
            currentXPos = targetXSteps;
            currentYPos = targetYSteps;

            delay(500);

            // Print updated position for debugging
            Serial.print("Moved to x: ");
            Serial.print(currentXPos);
            Serial.print(", y: ");
            Serial.println(currentYPos);
        }

        Serial.println("Movements completed.");
    }
}

