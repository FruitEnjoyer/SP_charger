################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../third_party/MCP342x.cpp 

OBJS += \
./third_party/MCP342x.o 

CPP_DEPS += \
./third_party/MCP342x.d 


# Each subdirectory must supply rules for building sources it contributes
third_party/%.o third_party/%.su third_party/%.cyclo: ../third_party/%.cpp third_party/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0plus -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L051xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-third_party

clean-third_party:
	-$(RM) ./third_party/MCP342x.cyclo ./third_party/MCP342x.d ./third_party/MCP342x.o ./third_party/MCP342x.su

.PHONY: clean-third_party

