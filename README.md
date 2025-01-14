# UnoRtos

**Atmega328p freeRTOS demo**

### Configure project
```
cmake -S ./ -B ./cbuild/ -D CMAKE_TOOLCHAIN_FILE=./gccavr.cmake --graphviz=cbuild/graph.dot -G Ninja
dot -Tsvg ./cbuild/graph.dot -o ./cbuild/graph.svg
```

### Build source code
```
cmake --build ./cbuild/ --parallel
```

### Flash software
```
cmake --build ./cbuild/ --target flash
```
or invoke avrdude directly:
```
avrdude -p atmega328p -c usbtiny -U flash:w:./cbuild/uno_rtos.elf:e
```
