# UnoRtos

Atmega328p freeRTOS demo app

Build by ninja:
```
cmake -S ./ -B ./cbuild/ -G Ninja -D CMAKE_TOOLCHAIN_FILE=./gccavr.cmake -D CMAKE_BUILD_TYPE=Release
cmake --build ./cbuild/ --parallel
```
