################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MC1.c \
../adc.c \
../external_eeprom.c \
../i2c.c \
../keypad.c \
../lcd.c \
../timer.c \
../uart.c 

OBJS += \
./MC1.o \
./adc.o \
./external_eeprom.o \
./i2c.o \
./keypad.o \
./lcd.o \
./timer.o \
./uart.o 

C_DEPS += \
./MC1.d \
./adc.d \
./external_eeprom.d \
./i2c.d \
./keypad.d \
./lcd.d \
./timer.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


