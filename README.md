# VolumeControl

This library provides a 2-source non-block volume control for DFPlayer mini mp3 module.

## Usage
Download ZIP; open `Sketch` menu and then `Include Library` -> `Manage Libraries` -> `Add .ZIP Library`;  
`Sketch` -> `Include Library` -> `Manage Libraries` -> `VolumeControl`  
> [Libraries guide](https://www.arduino.cc/en/Guide/Libraries)
```ino
#include <VolumeControl.h>
```
You must declare function with your own setter
```ino
void setVolume(int volume)
```
and pass it to constructor as link.  
This function will be called if volume is changed.

In main `loop()` call 
`void update(unsigned long currentMillis)` 
to check changes and update volume (each `timeInterval` mills)

See example below.

## Использование
Загрузите ZIP, после чего добавьте через меню `Скетч` -> `Подключить библиотеку` -> `Добавить ZIP библиотеку`;  
`Скетч` -> `Подключить библиотеку` -> `VolumeControl`
```ino
#include <VolumeControl.h>
```
Объявите функцию регулировки громкости
```ino
void setVolume(int volume)
```
и передайте её в конструктор по ссылке.  
При изменении громкости эта функция будет вызвана.

В цикле `loop()` вызывайте `void update(unsigned long currentMillis)` 
для проверки изменений громкости (каждые `timeInterval`) и установки громкости

## Example / Пример

```ino
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
```
