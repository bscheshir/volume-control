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


/*
* Download ZIP; open `Sketch` menu and then `Include Library` -> `Manage Libraries` -> `Add .ZIP Library`; 
* `Sketch` -> `Include Library` -> `Manage Libraries` -> `VolumeControl`  
* #include <VolumeControl.h>
* You must declare function with your own setter
* void setVolume(int volume)
* and pass it to constructor as link.
* This function will be called if volume is changed
* In main loop() call 
* void update(unsigned long currentMillis)
* to check changes and update volume (each timeInterval mills)
* See example below.
*
* Загрузите ZIP, после чего добавьте через меню `Скетч` -> `Подключить библиотеку` -> `Добавить ZIP библиотеку`;  
* `Скетч` -> `Подключить библиотеку` -> `VolumeControl`
* #include <VolumeControl.h>
* Объявите функцию регулировки громкости
* void setVolume(int volume)
* и передайте её в конструктор по ссылке.
* При изменении громкости эта функция будет вызвана.
* В цикле loop() вызывайте 
* void update(unsigned long currentMillis)
* для проверки изменений громкости (каждые timeInterval) и установки громкости
*
* Example / Пример

#include <VolumeControl.h>

#define VOL A0

void setVolume(int volume) {
  Serial.println((String)"Volume set to " + volume);
  mp3_set_volume(volume);
}

VolumeControl vc(VOL, 500, &setVolume);

...
void setup() {
...
}

...
void loop() {
  vc.update(millis());
  ...
}
*/

#ifndef VolumeControl_h
#define VolumeControl_h
 
#include <Arduino.h>
 
#define VOLUME_CONTROL_SOFTWARE_MAX 30 // Максимальное значение громкости при установке програмным путём
#define VOLUME_CONTROL_HARDWARE_MAX 1023 // Максимальное значение громкости при установке резистором (AnalogRead)
#define VOLUME_CONTROL_COMMON_MAX 30 // Максимальное значение громкости регулируемого устройства (максимально возможное для пердачи в функцию обратного вызова)

class VolumeControl {
	public:
		typedef void (*callbackFunction)(int);
        VolumeControl(int analogPin, long timeInterval, callbackFunction f);
        void update(unsigned long currentMillis); // Проверить необходимость обновления громкости ("неблокирующая" функция), обновить, установить в случае изменений 
        void hardwareRead(); // Прочитать значение громкости из аппаратной части
        void softwareSet(int val); // Установить значение громкости как "програмное"
        int current(); // Получить текущее значение приведённой громкости
	private:
		callbackFunction func;
		int pin;//потенциометр
		int currentVolume;//текущее значение громкости после всех преобразований
		int currentVolumeHardware;// текущее значение громкости для резистора
		int currentVolumeSoftware;// текущее значение громкости для програмной регулировки
		int targetVolumeHardware;// целевое значение громкости резистора
		int targetVolumeSoftware;// целевое значение громкости програмной регулировки
		long checkTime;
		unsigned long prevMillis; // последний момент смены состояния
};
 
#endif