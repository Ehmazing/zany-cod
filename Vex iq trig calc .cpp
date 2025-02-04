#include "robot-config.h" // Include the VEX IQ robot configuration header
#include <cmath> // Include cmath for mathematical functions like sqrt and atan2

// Define the target locations in 2D space (x, y)
struct Location {
    double x; // Forward/Backward distance in mm
    double y; // Left/Right distance in mm
};

// Define the distances to the target locations
const Location LOCATION_1 = {500.0, 300.0}; // Location 1 (x, y)
const Location LOCATION_2 = {1000.0, 600.0}; // Location 2 (x, y)

// Function to move the robot to a specified location
void moveToLocation(const Location& loc) {
    vex::motor leftMotor(vex::PORT1);
    vex::motor rightMotor(vex::PORT2);
    
    // Reset motor encoders
    leftMotor.resetRotation();
    rightMotor.resetRotation();

    // Calculate the distance to the target location
    double distance = sqrt(loc.x * loc.x + loc.y * loc.y); // Pythagorean theorem

    // Calculate the angle to turn (in degrees)
    double angle = atan2(loc.y, loc.x) * (180.0 / M_PI); // Convert radians to degrees

    // Turn the robot to face the target location
    leftMotor.setVelocity(50, vex::velocityUnits::pct);
    rightMotor.setVelocity(50, vex::velocityUnits::pct);
    
    // Turn the robot to the calculated angle
    if (angle > 0) {
        leftMotor.startRotateFor(angle, vex::rotationUnits::deg);
        rightMotor.startRotateFor(-angle, vex::rotationUnits::deg);
    } else {
        leftMotor.startRotateFor(angle, vex::rotationUnits::deg);
        rightMotor.startRotateFor(-angle, vex::rotationUnits::deg);
    }
    vex::task::sleep(1000); // Wait for the turn to finish

    // Move forward to the target location
    leftMotor.startRotateFor(distance, vex::rotationUnits::mm);
    rightMotor.startRotateFor(distance, vex::rotationUnits::mm);
    vex::task::sleep(1000); // Wait for the motors to finish moving
}

int main() {
    // Initialize the controller
    vex::controller Controller;

    while (true) {
        // Check if button 1 (Button A) is pressed
        if (Controller.ButtonA.pressing()) {
            moveToLocation(LOCATION_1);
            vex::brain::print("Moving to Location 1\n");
            vex::task::sleep(500); // Debounce delay
        }

        // Check if button 2 (Button B) is pressed
        if (Controller.ButtonB.pressing()) {
            moveToLocation(LOCATION_2);
            vex::brain::print("Moving to Location 2\n");
            vex::task::sleep(500); // Debounce delay
        }

        // Optional: Add a small delay to avoid overwhelming the controller
        vex::task::sleep(100);
    }

    return 0;
}