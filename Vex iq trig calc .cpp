#include "vex.h"

using namespace vex;

// Create a brain object
brain Brain;

// Create a distance sensor object on Port 2
distance DistanceSensor = distance(Brain.ThreeWirePort.B); // Change to Port B for Port 2

// Create motor objects for the left and right wheels
motor LeftMotor = motor(PORT1, ratio18_1, false);
motor RightMotor = motor(PORT10, ratio18_1, true);

// Set the target distance in centimeters
const double targetDistance = 50.0; // Change this to your desired distance

// Create a controller object
controller Controller;

int main() {
    // Start the robot
    Brain.Screen.print("Press L1 to Start...");

    // Wait for the L1 button to be pressed
    while (true) {
        if (Controller.ButtonL1.pressing()) {
            Brain.Screen.clearScreen();
            Brain.Screen.print("Starting...");

            // Loop until the target distance is reached
            while (true) {
                // Get the current distance from the sensor
                double currentDistance = DistanceSensor.distance(distanceUnits::cm);

                // Print the current distance to the brain screen
                Brain.Screen.clearScreen();
                Brain.Screen.print("Current Distance: %.2f cm", currentDistance);

                // Check if the current distance is less than the target distance
                if (currentDistance < targetDistance) {
                    // If not reached, turn the motors forward
                    LeftMotor.spin(forward);
                    RightMotor.spin(forward);
                } else {
                    // If reached, stop the motors
                    LeftMotor.stop();
                    RightMotor.stop();
                    Brain.Screen.print("Target Distance Reached!");
                    break; // Exit the loop
                }

                // Wait a short time to avoid overwhelming the CPU
                task::sleep(100);
            }
        }

        // Allow a small delay to prevent overwhelming the CPU
        task::sleep(100);
    }
}
