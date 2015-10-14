#include "DriveControl.h"
#include "XboxController.h"

#define DEFAULT_MIN_POWER .44

DriveControl::DriveControl() :
	myRobot(3, 4, 1, 2) {
	xbox = XboxController::getInstance();
	myRobot.SetExpiration(0.1);
	dsLCD = DriverStationLCD::GetInstance();
	MinPower = DEFAULT_MIN_POWER;
}

void DriveControl::initialize() {
	//xbox = XboxController::getInstance();
	myRobot.SetSafetyEnabled(true);
}
void DriveControl::initializeAutonomous() {
	myRobot.SetSafetyEnabled(false);
}

float DriveControl::scaledOffset(float originalValue, float minValue,
		float maxValue) {

	if (fabs(originalValue) <= 0.1)
		return 0.0;
	if (minValue > maxValue)
		minValue = maxValue;
	if (fabs(originalValue) > 1.0) {
		originalValue = (originalValue > 0) ? 1.0 : -1.0;
	}
	if (originalValue > 0.0) {
		return (maxValue - minValue) * originalValue + minValue;
	} else {
		return (maxValue - minValue) * originalValue - minValue;
	}
}

float DriveControl::scaledOffset(float originalValue, float minValue) {
	return scaledOffset(originalValue, minValue, 1.0);
}
float DriveControl::scaleValue(float originalValue, float offset) {
	if (offset != 1 && originalValue != 0) {
		if (originalValue > 0) {
			return (1.0 / (1.0 - offset)) * originalValue - (offset / (1.0
					- offset));
		} else {
			return (1.0 / (1.0 - offset)) * originalValue + (offset / (1.0
					- offset));
		}
	}
	return 0;
}

void DriveControl::run() {
	float lefty = 0.0;
	float righty = 0.0;
	//	lefty = xbox->getAxisLeftY();
	//	righty = xbox->getAxisRightY(); //this is for tank
	//	myRobot.TankDrive(scaledOffset(lefty, MinPower),
	//			scaledOffset(righty, MinPower)); // drive with tank style

	lefty = xbox->getAxisLeftY(); // this is for arcade
	righty = xbox->getAxisLeftX();
	myRobot.ArcadeDrive(scaledOffset(lefty, MinPower),
			scaledOffset(righty, MinPower)); // drive with tank style
//	dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "Left: %f",
//			xbox->getAxisLeftY());
//	dsLCD->PrintfLine(DriverStationLCD::kUser_Line3, "right: %f",
//			xbox->getAxisRightY());
//	dsLCD->PrintfLine(DriverStationLCD::kUser_Line4, "scaled left: %f", lefty);
//	dsLCD->PrintfLine(DriverStationLCD::kUser_Line5, "scaled rt: %f", righty);
//	dsLCD->UpdateLCD();
}

bool DriveControl::runAuto() {
	return (true);
}

