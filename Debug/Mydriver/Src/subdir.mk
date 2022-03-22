################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Mydriver/Src/EXTI.c \
../Mydriver/Src/GPIO.c \
../Mydriver/Src/I2C.c \
../Mydriver/Src/RCC.c \
../Mydriver/Src/SPI.c \
../Mydriver/Src/USART.c 

OBJS += \
./Mydriver/Src/EXTI.o \
./Mydriver/Src/GPIO.o \
./Mydriver/Src/I2C.o \
./Mydriver/Src/RCC.o \
./Mydriver/Src/SPI.o \
./Mydriver/Src/USART.o 

C_DEPS += \
./Mydriver/Src/EXTI.d \
./Mydriver/Src/GPIO.d \
./Mydriver/Src/I2C.d \
./Mydriver/Src/RCC.d \
./Mydriver/Src/SPI.d \
./Mydriver/Src/USART.d 


# Each subdirectory must supply rules for building sources it contributes
Mydriver/Src/%.o: ../Mydriver/Src/%.c Mydriver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"C:/stm32kutuphane/mydriverr/Mydriver/lnc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Mydriver-2f-Src

clean-Mydriver-2f-Src:
	-$(RM) ./Mydriver/Src/EXTI.d ./Mydriver/Src/EXTI.o ./Mydriver/Src/GPIO.d ./Mydriver/Src/GPIO.o ./Mydriver/Src/I2C.d ./Mydriver/Src/I2C.o ./Mydriver/Src/RCC.d ./Mydriver/Src/RCC.o ./Mydriver/Src/SPI.d ./Mydriver/Src/SPI.o ./Mydriver/Src/USART.d ./Mydriver/Src/USART.o

.PHONY: clean-Mydriver-2f-Src

