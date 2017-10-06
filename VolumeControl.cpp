/*******************************************************************************
 * Copyright (C) 2017 BSCheshir                                                *
 *                                                                             *
 * VolumeControl, This library provides a 2-source non-block volume control    *
 * for DFPlayer mini mp3 module.                                               *
 * www.github.com/bscheshir/VolumeControl (github as default source provider)  *
 *                                                                             *
 * This file is part of the VolumeControl library.                             *
 *                                                                             *
 * VolumeControl is free software: you can redistribute it and/or              *
 * modify it under the terms of the GNU Lesser General Public License as       *
 * published by the Free Software Foundation, either version 3 of              *
 * the License, or any later version.                                          *
 *                                                                             *
 * VolumeControl is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *
 * GNU Lesser General Public License for more details.                         *
 *                                                                             *
 * You should have received a copy of the GNU Lesser General Public            *
 * License along with VolumeControl. If not, see                               *
 * <http://www.gnu.org/licenses/>.                                             *
 *                                                                             *
 ******************************************************************************/

 /*
 *	name:			VolumeControl
 *	version:		1.0
 *	Author:			BSCheshir <bscheshir@gmail.com>
 *	Date:			2017-10-05
 *	Description:	2-source non-block volume control library for DFPlayer mini board
 */


#include "VolumeControl.h" //include the declaration for this class

VolumeControl::VolumeControl(int analogPin, long timeInterval, callbackFunction f) {
	pin = analogPin;
	checkTime = timeInterval;
	func = f;
	hardwareRead();
	currentVolumeHardware = targetVolumeHardware;
	currentVolumeSoftware = targetVolumeHardware;
	targetVolumeSoftware = targetVolumeHardware;
	currentVolume = targetVolumeHardware;
	prevMillis = 0;
}

void VolumeControl::update(unsigned long currentMillis) {
  if ((currentMillis - prevMillis >= checkTime))
  {
	prevMillis = currentMillis; // запоминаем момент времени

	bool changed = false;
	hardwareRead();
	if (targetVolumeHardware != currentVolumeHardware) {
	  currentVolumeHardware = targetVolumeHardware;
	  currentVolume = currentVolumeHardware;
	  changed = true;
	}
	else if (targetVolumeSoftware != currentVolumeSoftware) {
	  currentVolumeSoftware = targetVolumeSoftware;
	  currentVolume = currentVolumeSoftware;
	  changed = true;
	}
	if (changed) {
	  // вызов внешней функции
	  func(currentVolume);
	}
  }
}


void VolumeControl::hardwareRead() {
  // http://arduino.ru/Reference/Map
  int val = analogRead(pin);
  targetVolumeHardware = constrain(map(val, 0, VOLUME_CONTROL_HARDWARE_MAX, 0, VOLUME_CONTROL_COMMON_MAX), 0, VOLUME_CONTROL_COMMON_MAX);
}

void VolumeControl::softwareSet(int val) {
  targetVolumeSoftware = constrain(map(val, 0, VOLUME_CONTROL_SOFTWARE_MAX, 0, VOLUME_CONTROL_COMMON_MAX), 0, VOLUME_CONTROL_COMMON_MAX);
}

int VolumeControl::current() {
  return currentVolume;
}

