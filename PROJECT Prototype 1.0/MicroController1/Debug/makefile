################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
MC1.lss \

FLASH_IMAGE += \
MC1.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: MC1.elf secondary-outputs

# Tool invocations
MC1.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,MC1.map -mmcu=atmega16 -o "MC1.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

MC1.lss: MC1.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S MC1.elf  >"MC1.lss"
	@echo 'Finished building: $@'
	@echo ' '

MC1.hex: MC1.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex MC1.elf  "MC1.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: MC1.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega16 MC1.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) MC1.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
