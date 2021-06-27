#include<Wire.h>

#include "../config.h"

#include "./Attitude.h"


#ifdef ENABLE_DEBUG
    void printAngle(Angle *angle) {
        Serial.print(angle->pitch);
        Serial.print(",");
        Serial.print(angle->roll);
        Serial.print(",");
    }
#endif


void initAngleHistory(AngleHistory *angleHistory, Angle initial_angle) {
    for (short i = 0; i < ANGLE_HISTORY_TO_MEAN; i++) {
        angleHistory->history[i] = initial_angle;
    }
}

void addNewAngle(AngleHistory *angleHistory, Angle newAngle) {
    angleHistory->history[angleHistory->current_index] = newAngle;
    if (angleHistory->current_index == ANGLE_HISTORY_TO_MEAN-1) {
        angleHistory->current_index = 0;
    }else{
        angleHistory->current_index += 1;
    }
}

Angle getMeanAngle(AngleHistory *angleHistory) {

    double pitch_sum = 0;
    double roll_sum = 0;

    for (short i = 0; i < ANGLE_HISTORY_TO_MEAN; i++) {
        pitch_sum += angleHistory->history[i].pitch;
        roll_sum += angleHistory->history[i].roll;
    }
    pitch_sum /= ANGLE_HISTORY_TO_MEAN;
    roll_sum /= ANGLE_HISTORY_TO_MEAN;

    NEW_ANGLE(new_angle, pitch_sum, roll_sum);

    return new_angle;
}

void initAttitude (Attitude *attitude) {
    // init MPU6050
    Wire.begin(); 
	Wire.beginTransmission(MPU_ADDR); 
	Wire.write(0x6B); 
	Wire.write(0); 
	Wire.endTransmission(true); 


    // Init angles
    updateInstantAttitude(attitude);

    initAngleHistory(&(attitude->history), attitude->instant_angle);

    updateMeanAngle(attitude);
}

void updateInstantAttitude (Attitude *attitude) {

    const int minVal=265; const int maxVal=402;

    // Talking to the MPU6050
	Wire.beginTransmission(MPU_ADDR); 
  	Wire.write(0x3B); 
  	Wire.endTransmission(false);
  	Wire.requestFrom(MPU_ADDR,14,true); 
  
  	attitude->AcX=Wire.read()<<8|Wire.read(); 
  	attitude->AcY=Wire.read()<<8|Wire.read(); 
  	attitude->AcZ=Wire.read()<<8|Wire.read(); 
  
  	int xAng = map(attitude->AcX,minVal,maxVal,-90,90); 
  	int yAng = map(attitude->AcY,minVal,maxVal,-90,90); 
  	int zAng = map(attitude->AcZ,minVal,maxVal,-90,90);

  	// Calculating Angles
  	attitude->rroll = RAD_TO_DEG * (atan2(-yAng, -zAng)+PI); 
  	attitude->rpitch = RAD_TO_DEG * (atan2(-xAng, -zAng)+PI); 
    
    // Formatting angles
    attitude->rpitch += 90; // To center the value around 90°
    if (attitude->rpitch >= 360) { attitude->rpitch -= 360; }
    (attitude->instant_angle).pitch = attitude->rpitch;

    attitude->rroll += 90;
    if (attitude->rroll >= 360) { attitude->rroll -= 360; }
    (attitude->instant_angle).roll = attitude->rroll;

}

void updateMeanAngle (Attitude *attitude){
    updateInstantAttitude(attitude);
    addNewAngle(&(attitude->history), attitude->instant_angle);
    attitude->angle = getMeanAngle(&(attitude->history));
}