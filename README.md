# nucleo-f446re-freertos
This is a collection of projects with a FreeRTOS introduced in the [stm32f446re](https://www.st.com/en/microcontrollers-microprocessors/stm32f446re.html) microcontroller from scratch. The board used for testing is the [nucleo-f446re](https://www.st.com/en/evaluation-tools/nucleo-f446re.html).  
The repository has a [ThirdParty](ThirdParty) folder, where is placed the code of the FreeRTOS and the [SEGGER SystemView](https://www.segger.com/products/development-tools/systemview/) (a tool used to debug the FreeRTOS).  
On the other hand, each example is coded in a separate folder:
- [001Tasks](001Tasks): two tasks executed with nothing to do, only some debug information. You can change the time needed for completing a task using a delay function.

## Compiling
The build enviroment used is [CMake](https://cmake.org/), you will find a CMakeLists.txt file and a separate arm_toolchain.cmake file where the cross copilation toolchain is defined. For compiling the project you can do:
```console
mkdir build
cd build
cmake ..
make
```

## Testing
You can use OpenOCD (Open On-Chip Debugger) for programming or debugging this project. You can starting OpenOCD typing:
```console
openocd -f board/st_nucleo_f4.cfg
```
You can use a telnet connection for connecting to the OpenOCD server:
```console
telnet 127.0.0.1 4444
```
You can program the microcontroller using:
```console
reset init
flash write_image erase your_app.elf
reset
```

## Debugging
You can use gdb for debug, if your executable file is named foo.elf, you can do:
- Open a terminal and execute OpenOCD
- Open other terminal and execute gdb, in the gdb session execute:
```console
target remote localhost:3333
monitor reset init
file foo.elf
tui enable
```
