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

#ifndef VehicleTractor_h
#define VehicleTractor_h

#include <Arduino.h>
#include <EEPROM.h>
#include "ConfigVehicleTractor.h"
#include "Language.h"

// software version of this library
#define TRACTOR_VERSION 0.1

class VehicleTractor{
private:
  float speed;
  float simspeed;
  
  byte simtime;
  
  boolean sim;
  boolean deutz;
  //float slip;
  
  int v_const;
  int wheelspeed_pulses;
  unsigned long distance;
  
  // wheel speed flag and timer
  boolean wheelspeed_puls;
  unsigned long update_age;
  
public:
  // ---------------------------------------------------------
  // public member functions implemented in VehicleTractor.cpp
  // ---------------------------------------------------------
  
  // Constructor
  VehicleTractor();
  
  void update(byte _mode);

  int calibrateSpeed(int _buttons);
  boolean readCalibrationData();
  void printCalibrationData();
  void writeCalibrationData();
  // --------------------------------------------------------------
  // public inline member functions implemented in VehicleTractor.h
  // --------------------------------------------------------------
  inline boolean resetCalibration(){
    return readCalibrationData();
  }
  
  inline void commitCalibration(){
    writeCalibrationData();
  }
  
  inline boolean minSpeed(){
    return speed > MINSPEED;
  }
  
  inline void enableSim(){
    sim = true;
  }
  
  inline void disableSim(){
    sim = false;
  }
  
  inline void enableDeutz(){
    deutz = true;
  }
  
  inline void disableDeutz(){
    deutz = false;
  }
  
  inline void setSimSpeedKmh(float _speed){
    simspeed = _speed / 36;
  }
  
  inline void setSimTime(byte _time){
    simtime = _time;
  }
  
  inline boolean simSpeed(){
    return speed >= simspeed;
  }
  
  inline void resetWheelspeedPulses(){
    wheelspeed_pulses = 0;
  }
  
  // -------
  // Getters
  // -------
  inline boolean getHitch(){
    return digitalRead(HITCH_PIN) ^ deutz; // ^ is bitwise XOR
  }
  
  inline float getSpeedMs(){
    return speed;
  }
  
  inline float getSpeedKmh(){
    return speed * 36;
  }
  
  inline boolean getSim(){
    return sim;
  }
  
  inline boolean getDeutz(){
    return deutz;
  }
  
  inline float getSimSpeedKmh(){
    return simspeed * 36;
  }
  
  inline byte getSimTime(){
    return simtime;
  }
  
  inline unsigned long getDistance(){
    return distance * 4 / v_const;
  }
};
#endif
