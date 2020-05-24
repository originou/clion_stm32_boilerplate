# clion_stm32_boilerplate
Boilerplate for stm32 project with clion IDE

## Clone project
>       git clone https://github.com/originou/clion_stm32_boilerplate.git --recurse-submodules
## Purposes
- Use advantage of Clion IDE.
- Manage differents family for stm32 (f1, f4 [..])
- Manage several projects
- Use openlibcm3 and FreeRTOS

## Dependencies
-   libopencm3  (current master :  90753950bbe10e87b8caabfb0bd6e1d195bb24b8)
>     git submodule add https://github.com/libopencm3/libopencm3.git
-   FreeRTOS (V10.3.1)
>       git submodule add https://github.com/FreeRTOS/FreeRTOS.git rtos
>       cd ./rtos
>       git checkout V10.3.1
>       git submodule update --init --recursive
>       cd -

## Build project
example
>       cmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain.cmake -DTOOLCHAIN_DIR=/opt/gcc-arm/bin -DCMAKE_BUILD_TYPE=stm32f4_black
>       make


## Build types
-   stm32f103_bluepill
-   stm32f4_black