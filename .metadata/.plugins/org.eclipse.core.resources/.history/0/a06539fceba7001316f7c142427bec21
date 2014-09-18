################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv5/tools/compiler/msp430_4.2.3

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./src/EPD_Kit_Tool/Drivers/Uart_Driver.obj" \
"./src/EPD_Kit_Tool/Drivers/EPD_LED.obj" \
"./src/EPD_Kit_Tool/Uart_Controller.obj" \
"./src/EPD_Kit_Tool/Mem_Flash.obj" \
"./src/EPD_Kit_Tool/EPD_Kit_Tool_Process.obj" \
"./src/EPD_Kit_Tool/Char.obj" \
"./src/Pervasive_Displays_small_EPD/EPD_hardware_gpio.obj" \
"./src/Pervasive_Displays_small_EPD/EPD_hardware_driver.obj" \
"./src/Pervasive_Displays_small_EPD/EPD_controller.obj" \
"./src/Pervasive_Displays_small_EPD/EPD_COG.obj" \
"./src/main.obj" \
"./src/image_data.obj" \
"../lnk_msp430g2553.cmd" \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include src/subdir_vars.mk
-include src/Pervasive_Displays_small_EPD/subdir_vars.mk
-include src/EPD_Kit_Tool/subdir_vars.mk
-include src/EPD_Kit_Tool/Drivers/subdir_vars.mk
-include subdir_rules.mk
-include src/subdir_rules.mk
-include src/Pervasive_Displays_small_EPD/subdir_rules.mk
-include src/EPD_Kit_Tool/subdir_rules.mk
-include src/EPD_Kit_Tool/Drivers/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: EPD_Extension_Board.out

# Tool invocations
EPD_Extension_Board.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: MSP430 Linker'
	"C:/ti/ccsv5/tools/compiler/msp430_4.2.3/bin/cl430" -vmsp --abi=eabi --opt_for_speed=1 --define=__MSP430G2553__ --printf_support=minimal -z --heap_size=80 --stack_size=80 -i"C:/ti/ccsv5/ccs_base/msp430/include" -i"C:/ti/ccsv5/tools/compiler/msp430_4.2.3/lib" -i"C:/ti/ccsv5/tools/compiler/msp430_4.2.3/include" --reread_libs --warn_sections --xml_link_info="EPD_Extension_Board_linkInfo.xml" --rom_model -o "EPD_Extension_Board.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(MSP430_EXECUTABLE_OUTPUTS__QUOTED) "EPD_Extension_Board.out"
	-$(RM) "src\image_data.pp" "src\main.pp" "src\Pervasive_Displays_small_EPD\EPD_COG.pp" "src\Pervasive_Displays_small_EPD\EPD_controller.pp" "src\Pervasive_Displays_small_EPD\EPD_hardware_driver.pp" "src\Pervasive_Displays_small_EPD\EPD_hardware_gpio.pp" "src\EPD_Kit_Tool\Char.pp" "src\EPD_Kit_Tool\EPD_Kit_Tool_Process.pp" "src\EPD_Kit_Tool\Mem_Flash.pp" "src\EPD_Kit_Tool\Uart_Controller.pp" "src\EPD_Kit_Tool\Drivers\EPD_LED.pp" "src\EPD_Kit_Tool\Drivers\Uart_Driver.pp" 
	-$(RM) "src\image_data.obj" "src\main.obj" "src\Pervasive_Displays_small_EPD\EPD_COG.obj" "src\Pervasive_Displays_small_EPD\EPD_controller.obj" "src\Pervasive_Displays_small_EPD\EPD_hardware_driver.obj" "src\Pervasive_Displays_small_EPD\EPD_hardware_gpio.obj" "src\EPD_Kit_Tool\Char.obj" "src\EPD_Kit_Tool\EPD_Kit_Tool_Process.obj" "src\EPD_Kit_Tool\Mem_Flash.obj" "src\EPD_Kit_Tool\Uart_Controller.obj" "src\EPD_Kit_Tool\Drivers\EPD_LED.obj" "src\EPD_Kit_Tool\Drivers\Uart_Driver.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

