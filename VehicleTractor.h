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
#include <ConfigVehicle.h>

// software version of this library
#define TRACTOR_VERSION 0.1

class VehicleTractor{
private:
  boolean hitch;
  float wheelspeed;
  //float slip;
  
  int v_const;
  int pulse;
  
  // wheel speed flag and timer
  boolean wheelspeed_flag;
  unsigned long wheelspeed_timer;
  
  // ----------------------------------------------------------
  // private member functions implemented in VehicleTractor.cpp
  // ----------------------------------------------------------

  void updateWheelspeed();
public:
  // ---------------------------------------------------------
  // public member functions implemented in VehicleTractor.cpp
  // ---------------------------------------------------------
  
  // Constructor
  VehicleTractor();
  
  void update();

  // --------------------------------------------------------------
  // public inline member functions implemented in VehicleTractor.h
  // --------------------------------------------------------------
  inline boolean minSpeed(){
    return wheelspeed > MINSPEED;
  }
  
  // -------
  // Getters
  // -------
  inline boolean getHitch(){
    return digitalRead(HITCH_PIN);
  }
  
  inline float getSpeedKmh(){
    return wheelspeed;
  }
};
#endif