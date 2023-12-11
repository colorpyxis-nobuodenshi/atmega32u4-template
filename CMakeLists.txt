cmake_minimum_required(VERSION 3.15)

set(CMAKE_TOOLCHAIN_FILE "avr-gcc.toolchain.cmake")

project(myproject C CXX ASM)

include_directories(
    include/
    lib/FreeRTOS-Kernel/include/
    portable/
    lib/LUFA/Driver/
    lib/LUFA/Drivers/USB/
    lib/LUFA/Driver/Core/
    lib/LUFA/Driver/Core/AVR8/
    lib/LUFA/Driver/Class/
    lib/LUFA/Driver/Class/Common/
    lib/LUFA/Driver/Class/Device/
)

add_definitions(-DF_CPU=16000000)
add_definitions(-DF_USB=16000000)
add_avr_executable(${PROJECT_NAME} "atmega32u4"
    src/main.c
    src/Descriptors.c

    lib/FreeRTOS-Kernel/list.c
    lib/FreeRTOS-Kernel/queue.c
    lib/FreeRTOS-Kernel/tasks.c
    lib/FreeRTOS-Kernel/timers.c
    lib/FreeRTOS-Kernel/portable/MemMang/heap_3.c
    portable/port.c
    lib/LUFA/Drivers/USB/Core/AVR8/USBController_AVR8.c
    lib/LUFA/Drivers/USB/Core/AVR8/USBInterrupt_AVR8.c
    lib/LUFA/Drivers/USB/Core/ConfigDescriptors.c
    lib/LUFA/Drivers/USB/Core/Events.c
    lib/LUFA/Drivers/USB/Core/USBTask.c
    lib/LUFA/Drivers/USB/Core/AVR8/Device_AVR8.c
    lib/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c
    lib/LUFA/Drivers/USB/Core/AVR8/EndpointStream_AVR8.c
    lib/LUFA/Drivers/USB/Core/DeviceStandardReq.c
    # lib/LUFA/Drivers/USB/Class/Device/AudioClassDevice.c
    # lib/LUFA/Drivers/USB/Class/Device/CCIDClassDevice.c
    lib/LUFA/Drivers/USB/Class/Device/CDCClassDevice.c
    # lib/LUFA/Drivers/USB/Class/Device/HIDClassDevice.c
    # lib/LUFA/Drivers/USB/Class/Device/MassStorageClassDevice.c
    # lib/LUFA/Drivers/USB/Class/Device/MIDIClassDevice.c
    # lib/LUFA/Drivers/USB/Class/Device/PrinterClassDevice.c
    # lib/LUFA/Drivers/USB/Class/Device/RNDISClassDevice.c
)

