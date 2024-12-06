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
        int semicolonIndex = data.indexOf(';'); // returns first index of semi-colon within serial input string
        index = 0;  // Reset index to start storing new coordinates

        // Receive and print all coordinates back to serial
        while (semicolonIndex >= 0 && index < 10) {
            String coordPair = data.substring(startIndex, semicolonIndex);
            int commaIndex = coordPair.indexOf(','); // comma index in order to split x and y coordinates

            if (commaIndex >= 0) {
                // Separate x and y values and convert to floats
                x_coords[index] = coordPair.substring(0, commaIndex).toFloat();
                y_coords[index] = coordPair.substring(commaIndex + 1).toFloat();
                index++; // append the index after previous x, y values inserted into respective arrays above

                // send the received coordinates back to the serial monitor
                Serial.print("Received x: ");
                Serial.print(x_coords[index - 1]);
                Serial.print(", y: ");
                Serial.println(y_coords[index - 1]);
            }

            // Move to the next pair
            startIndex = semicolonIndex + 1;
            semicolonIndex = data.indexOf(';', startIndex);
        }

        // After receiving all coordinates, start moving the motors
        for (int i = 0; i < index; i++) {
            int targetXSteps = x_coords[i] * xMaxSteps;  // Convert x percentage to steps
            int targetYSteps = y_coords[i] * yMaxSteps;  // Convert y percentage to steps
            
            // Calculate the difference from the current position
            int xStepDifference = targetXSteps - currentXPos;
            int yStepDifference = targetYSteps - currentYPos;

            int xStepCount = 0;
            int yStepCount = 0;

            // Move motors simultaneously
            while (xStepCount != abs(xStepDifference) || yStepCount != abs(yStepDifference)) { // go till both motors reach destination
                if (xStepCount < abs(xStepDifference)) {
                    myStepper.step(xStepDifference > 0 ? 1 : -1); // calculate if motor needs to move in the positive or negative direcation
                    xStepCount++;
                }
                if (yStepCount < abs(yStepDifference)) {
                    myStepper2.step(yStepDifference > 0 ? -1 : 1); //inverted y axis as origin is on the top left
                    yStepCount++;
                }
            }

            // Update current positions
            currentXPos = targetXSteps;
            currentYPos = targetYSteps;

            delay(500); // Brief delay between movements
        }

        Serial.println("Movements completed.");
    }
}
