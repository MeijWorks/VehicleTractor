/*
  Config file for VehicleTractor
Copyright (C) 2011-2014 J.A. Woltjer.

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

#ifndef ConfigVehicleTractor_h
#define ConfigVehicleTractor_h

#define VOORSERIE
// Digital inputs 12V -> 5V conversion

#ifndef VOORSERIE

#define WHEEL_SPEED_PIN     A4
#define HITCH_PIN           A5

#else

#define WHEEL_SPEED_PIN     8
#define HITCH_PIN           9

#endif

#define MINSPEED            0.5f

#endif