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
 
#include <VehicleTractor.h>

//------------
// Constructor
//------------
VehicleTractor::VehicleTractor(){
  // Pin configuration
  // Inputs
  pinMode(WHEEL_SPEED_PIN, INPUT);
  pinMode(HITCH_PIN, INPUT);
  
  // Initialise members
  wheelspeed_flag = digitalRead(WHEEL_SPEED_PIN);
  pulse = 0;
  v_const = 13500;
  wheelspeed = 2;
  wheelspeed_timer = millis();
}

// ------------------------
// Method for updating data
// ------------------------
void VehicleTractor::update(){
  //updateWheelspeed();
}

// --------------------------------
// Method for updating tractor data
// --------------------------------
void VehicleTractor::updateWheelspeed(){
  // Update wheelspeed
  if(wheelspeed_flag != digitalRead(WHEEL_SPEED_PIN)){
    wheelspeed_flag = !wheelspeed_flag;
    pulse++;
  }
  if(millis() - wheelspeed_timer >= 200){
    wheelspeed = float(pulse) / v_const;
    pulse = 0;
    wheelspeed_timer = millis();
  }
}