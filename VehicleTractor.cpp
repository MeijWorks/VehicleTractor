/*
  VehicleTractor - a library for a tractor
 Copyright (C) 2011-2014 J.A. Woltjer.
 All rights reserved.
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "VehicleTractor.h"

//------------
// Constructor
//------------
VehicleTractor::VehicleTractor(){
  Serial.println(S_DIVIDE);
  Serial.println("Initialising tractor");
  Serial.println(S_DIVIDE);
  
  // Pin configuration
  // Inputs
  pinMode(WHEEL_SPEED_PIN, INPUT);
  pinMode(HITCH_PIN, INPUT);
  
  digitalWrite(WHEEL_SPEED_PIN, LOW);
  digitalWrite(HITCH_PIN, LOW);
  
  // Initialise members
  wheelspeed_puls = false;
  wheelspeed_pulses = 0;
  speed = 0;
  distance = 0;
  update_age = millis();
  
  
  if(!readCalibrationData()){
    v_const = 250;
    simspeed = 1.5;
    simtime = 2;
    sim = true;
    deutz = false;
  }
  
  printCalibrationData();
}

// ------------------------
// Method for updating data
// ------------------------
void VehicleTractor::update(byte _mode){
  // Update wheelspeed
  if(!sim){
    if(wheelspeed_puls != digitalRead(WHEEL_SPEED_PIN)){
      wheelspeed_pulses++;
      wheelspeed_puls = !wheelspeed_puls;
    }

    if(millis() - update_age >= 2000){
      speed = float(wheelspeed_pulses) * 2 / v_const;
      
      update_age = millis();
      
      if (_mode == 0){
        distance += wheelspeed_pulses;
      }
      
      wheelspeed_pulses = 0;
    }
  }
  else {
    speed = simspeed;
  }
}

int VehicleTractor::calibrateSpeed(int _buttons){
  if(wheelspeed_puls != digitalRead(WHEEL_SPEED_PIN)){
      wheelspeed_pulses++;
      wheelspeed_puls = !wheelspeed_puls;
  }
  
  if(_buttons == 2){
    v_const = wheelspeed_pulses / 25;
  }
  
  return wheelspeed_pulses;
}
  
boolean VehicleTractor::readCalibrationData(){
  if(EEPROM.read(200) != 255 || EEPROM.read(210) != 255 ||
    EEPROM.read(220) != 255 || EEPROM.read(230) != 255 ||
    EEPROM.read(240) != 255){
    v_const = word(EEPROM.read(200), EEPROM.read(201));
    simspeed = EEPROM.read(210) / 10.0f;
    simtime = EEPROM.read(220);
    sim = EEPROM.read(230);
    deutz = EEPROM.read(240);
    return true;
  }
  return false;
}

//---------------------------------------------------
//Method for printing calibration data to serial port
//---------------------------------------------------
void VehicleTractor::printCalibrationData(){
  // Printing calibration data to serial port
  Serial.println(S_DIVIDE);
  Serial.println("Tractor using following data:");
  Serial.println(S_DIVIDE);
  
  Serial.println("Speed calibration");
  Serial.println(v_const);
  Serial.println(S_DIVIDE);
  
  Serial.println("Simspeed");
  Serial.println(simspeed);
  Serial.println(S_DIVIDE);

  Serial.println("Sim time");
  Serial.println(simtime);
  Serial.println(S_DIVIDE);

  Serial.println("Sim mode");
  Serial.println(sim);
  Serial.println(S_DIVIDE);

  Serial.println("Deutz mode");
  Serial.println(deutz);
  Serial.println(S_DIVIDE);
}

// --------------------------------------------
// Method for writing calibrationdata to EEPROM
// --------------------------------------------
void VehicleTractor::writeCalibrationData(){
  EEPROM.write(200, highByte(v_const));
  EEPROM.write(201, lowByte(v_const));
  
  EEPROM.write(210, byte(simspeed * 10));
  EEPROM.write(220, simtime);
  EEPROM.write(230, sim);
  EEPROM.write(240, deutz);
}
