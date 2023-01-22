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
Other tool you can use is SEGGER SystemView. This tool is already integrated in these projects.  
The tool is configured for continuous recording (real time recording) and for sending data using a UART, in this case the USART2 (pins PA2 and PA3) which is the UART connected to the ST-Link USB port.  
You need to set SEGGER_UART_REC to 1 in [SEGGER_SYSVIEW_Conf.h](ThirdParty/SEGGER/Config/SEGGER_SYSVIEW_Conf.h) and the USART is configured in the file [segger_uart.c](ThirdParty/SEGGER/Rec/segger_uart.c) where you need to specify the core clock frequency, peripheral addresses and the IRQ handler of the UART.  
When the continuous recording is selected, the SEGGER_SYSVIEW_Start() function does not need to be called because is already used for the [segger_uart.c](ThirdParty/SEGGER/Rec/segger_uart.c) file.  
For starting the debug, open SystemView, then select Target->Recorder Cofiguration and select UART, then select ttyACM0 and the configured speed (500000 in these projects). Finally click in the Start Recorder button.

If you use single-shot recording, the recorded debug data for the SEGGER SystemView are stored in a region of RAM memory (these buffers are configured in the [SEGGER_RTT_Conf.h](ThirdParty/SEGGER/Config/SEGGER_RTT_Conf.h)), the address of the buffer is __SEGGER_RTT.aUp[1].pBuffer. You need to export the data (RAW Binary) from this memory region to a file (with extension .SVdat) using a debugger. Now You can load this file into the SystemView.  
For single-shot recording you do not need to compile the [segger_uart.c](ThirdParty/SEGGER/Rec/segger_uart.c) file, you need to set SEGGER_UART_REC to 0 in [SEGGER_SYSVIEW_Conf.h](ThirdParty/SEGGER/Config/SEGGER_SYSVIEW_Conf.h) and call SEGGER_SYSVIEW_Start().
