################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Lora/Radio/sx1272/sx1272.c 

OBJS += \
./Drivers/Lora/Radio/sx1272/sx1272.o 

C_DEPS += \
./Drivers/Lora/Radio/sx1272/sx1272.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Lora/Radio/sx1272/sx1272.o: ../Drivers/Lora/Radio/sx1272/sx1272.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DDEBUG -DREGION_EU868 -DUSE_BAND_868 -DUSE_MODEM_LORA -c -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/Lora/Core -I../Drivers/Lora/Crypto -I../Drivers/Lora/Mac -I../Drivers/Lora/Radio -I../Drivers/Lora/Radio/sx1272 -I../Drivers/Lora/Utilities -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/Lora/Radio/sx1272/sx1272.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

