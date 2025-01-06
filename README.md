# AvrRtos

**Atmega2560 freeRTOS demo**

### Configure by conan
```
./conan_install.sh
```

### Build by conan
```
./build.sh
```

### Clean the build
```
source ./Debug/conanbuild.sh
cmake --build ./Debug/ --target clean
source ./Debug/deactivate_conanbuild.sh
```

### Verbose build
```
. ./Debug/conanbuild.sh
cmake --build ./Debug/ -v
. ./Debug/deactivate_conanbuild.sh
```

### Prepare python venv in Ubuntu
```
apt install python3-venv
mkdir ~/myvenv1/
cd ~/myvenv1/
python3 -m venv ~/myvenv1/
source ./bin/activate
pip3 install conan
```
Download avr gcc from release tags at https://github.com/ZakKemble/avr-gcc-build
