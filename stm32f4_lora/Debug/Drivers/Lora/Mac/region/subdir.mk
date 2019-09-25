################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Lora/Mac/region/Region.c \
../Drivers/Lora/Mac/region/RegionAS923.c \
../Drivers/Lora/Mac/region/RegionAU915.c \
../Drivers/Lora/Mac/region/RegionCN470.c \
../Drivers/Lora/Mac/region/RegionCN779.c \
../Drivers/Lora/Mac/region/RegionCommon.c \
../Drivers/Lora/Mac/region/RegionEU433.c \
../Drivers/Lora/Mac/region/RegionEU868.c \
../Drivers/Lora/Mac/region/RegionIN865.c \
../Drivers/Lora/Mac/region/RegionKR920.c \
../Drivers/Lora/Mac/region/RegionUS915-Hybrid.c \
../Drivers/Lora/Mac/region/RegionUS915.c 

OBJS += \
./Drivers/Lora/Mac/region/Region.o \
./Drivers/Lora/Mac/region/RegionAS923.o \
./Drivers/Lora/Mac/region/RegionAU915.o \
./Drivers/Lora/Mac/region/RegionCN470.o \
./Drivers/Lora/Mac/region/RegionCN779.o \
./Drivers/Lora/Mac/region/RegionCommon.o \
./Drivers/Lora/Mac/region/RegionEU433.o \
./Drivers/Lora/Mac/region/RegionEU868.o \
./Drivers/Lora/Mac/region/RegionIN865.o \
./Drivers/Lora/Mac/region/RegionKR920.o \
./Drivers/Lora/Mac/region/RegionUS915-Hybrid.o \
./Drivers/Lora/Mac/region/RegionUS915.o 

C_DEPS += \
./Drivers/Lora/Mac/region/Region.d \
./Drivers/Lora/Mac/region/RegionAS923.d \
./Drivers/Lora/Mac/region/RegionAU915.d \
./Drivers/Lora/Mac/region/RegionCN470.d \
./Drivers/Lora/Mac/region/RegionCN779.d \
./Drivers/Lora/Mac/region/RegionCommon.d \
./Drivers/Lora/Mac/region/RegionEU433.d \
./Drivers/Lora/Mac/region/RegionEU868.d \
./Drivers/Lora/Mac/region/RegionIN865.d \
./Drivers/Lora/Mac/region/RegionKR920.d \
./Drivers/Lora/Mac/region/RegionUS915-Hybrid.d \
./Drivers/Lora/Mac/region/RegionUS915.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Lora/Mac/region/Region.o: ../Drivers/Lora/Mac/region/Region.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DDEBUG -DREGION_EU868 -DUSE_BAND_868 -DUSE_MODEM_LORA -c -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/Lora/Core -I../Drivers/Lora/Crypto -I../Drivers/Lora/Mac -I../Drivers/Lora/Radio -I../Drivers/Lora/Radio/sx1272 -I../Drivers/Lora/Utilities -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/Lora/Mac/region/Region.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/Lora/Mac/region/RegionAS923.o: ../Drivers/Lora/Mac/region/RegionAS923.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DDEBUG -DREGION_EU868 -DUSE_BAND_868 -DUSE_MODEM_LORA -c -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/Lora/Core -I../Drivers/Lora/Crypto -I../Drivers/Lora/Mac -I../Drivers/Lora/Radio -I../Drivers/Lora/Radio/sx1272 -I../Drivers/Lora/Utilities -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/Lora/Mac/region/RegionAS923.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/Lora/Mac/region/RegionAU915.o: ../Drivers/Lora/Mac/region/RegionAU915.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DDEBUG -DREGION_EU868 -DUSE_BAND_868 -DUSE_MODEM_LORA -c -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/Lora/Core -I../Drivers/Lora/Crypto -I../Drivers/Lora/Mac -I../Drivers/Lora/Radio -I../Drivers/Lora/Radio/sx1272 -I../Drivers/Lora/Utilities -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/Lora/Mac/region/RegionAU915.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/Lora/Mac/region/RegionCN470.o: ../Drivers/Lora/Mac/region/RegionCN470.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DDEBUG -DREGION_EU868 -DUSE_BAND_868 -DUSE_MODEM_LORA -c -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/Lora/Core -I../Drivers/Lora/Crypto -I../Drivers/Lora/Mac -I../Drivers/Lora/Radio -I../Drivers/Lora/Radio/sx1272 -I../Drivers/Lora/Utilities -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/Lora/Mac/region/RegionCN470.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/Lora/Mac/region/RegionCN779.o: ../Drivers/Lora/Mac/region/RegionCN779.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DDEBUG -DREGION_EU868 -DUSE_BAND_868 -DUSE_MODEM_LORA -c -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/Lora/Core -I../Drivers/Lora/Crypto -I../Drivers/Lora/Mac -I../Drivers/Lora/Radio -I../Drivers/Lora/Radio/sx1272 -I../Drivers/Lora/Utilities -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/Lora/Mac/region/RegionCN779.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/Lora/Mac/region/RegionCommon.o: ../Drivers/Lora/Mac/region/RegionCommon.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DDEBUG -DREGION_EU868 -DUSE_BAND_868 -DUSE_MODEM_LORA -c -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/Lora/Core -I../Drivers/Lora/Crypto -I../Drivers/Lora/Mac -I../Drivers/Lora/Radio -I../Drivers/Lora/Radio/sx1272 -I../Drivers/Lora/Utilities -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/Lora/Mac/region/RegionCommon.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/Lora/Mac/region/RegionEU433.o: ../Drivers/Lora/Mac/region/RegionEU433.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DDEBUG -DREGION_EU868 -DUSE_BAND_868 -DUSE_MODEM_LORA -c -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/Lora/Core -I../Drivers/Lora/Crypto -I../Drivers/Lora/Mac -I../Drivers/Lora/Radio -I../Drivers/Lora/Radio/sx1272 -I../Drivers/Lora/Utilities -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/Lora/Mac/region/RegionEU433.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/Lora/Mac/region/RegionEU868.o: ../Drivers/Lora/Mac/region/RegionEU868.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DDEBUG -DREGION_EU868 -DUSE_BAND_868 -DUSE_MODEM_LORA -c -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/Lora/Core -I../Drivers/Lora/Crypto -I../Drivers/Lora/Mac -I../Drivers/Lora/Radio -I../Drivers/Lora/Radio/sx1272 -I../Drivers/Lora/Utilities -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/Lora/Mac/region/RegionEU868.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/Lora/Mac/region/RegionIN865.o: ../Drivers/Lora/Mac/region/RegionIN865.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DDEBUG -DREGION_EU868 -DUSE_BAND_868 -DUSE_MODEM_LORA -c -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/Lora/Core -I../Drivers/Lora/Crypto -I../Drivers/Lora/Mac -I../Drivers/Lora/Radio -I../Drivers/Lora/Radio/sx1272 -I../Drivers/Lora/Utilities -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/Lora/Mac/region/RegionIN865.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/Lora/Mac/region/RegionKR920.o: ../Drivers/Lora/Mac/region/RegionKR920.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DDEBUG -DREGION_EU868 -DUSE_BAND_868 -DUSE_MODEM_LORA -c -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/Lora/Core -I../Drivers/Lora/Crypto -I../Drivers/Lora/Mac -I../Drivers/Lora/Radio -I../Drivers/Lora/Radio/sx1272 -I../Drivers/Lora/Utilities -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/Lora/Mac/region/RegionKR920.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/Lora/Mac/region/RegionUS915-Hybrid.o: ../Drivers/Lora/Mac/region/RegionUS915-Hybrid.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DDEBUG -DREGION_EU868 -DUSE_BAND_868 -DUSE_MODEM_LORA -c -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/Lora/Core -I../Drivers/Lora/Crypto -I../Drivers/Lora/Mac -I../Drivers/Lora/Radio -I../Drivers/Lora/Radio/sx1272 -I../Drivers/Lora/Utilities -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/Lora/Mac/region/RegionUS915-Hybrid.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/Lora/Mac/region/RegionUS915.o: ../Drivers/Lora/Mac/region/RegionUS915.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DDEBUG -DREGION_EU868 -DUSE_BAND_868 -DUSE_MODEM_LORA -c -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/Lora/Core -I../Drivers/Lora/Crypto -I../Drivers/Lora/Mac -I../Drivers/Lora/Radio -I../Drivers/Lora/Radio/sx1272 -I../Drivers/Lora/Utilities -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/Lora/Mac/region/RegionUS915.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

