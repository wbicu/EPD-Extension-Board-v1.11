################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
src/EPD_Kit_Tool/Drivers/EPD_LED.obj: ../src/EPD_Kit_Tool/Drivers/EPD_LED.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv5/tools/compiler/msp430_4.2.3/bin/cl430" -vmsp --abi=eabi --opt_for_speed=1 --include_path="C:/ti/ccsv5/ccs_base/msp430/include" --include_path="C:/ti/ccsv5/tools/compiler/msp430_4.2.3/include" --include_path="D:/Partnering for Success/Ref.Designs/Extension board/1.44 - 2.7/Code/Firmware/LaunchPad/EPD Extension Board v1.11/EPD_Extension_Board/src/EPD_Kit_Tool/Drivers" --include_path="D:/Partnering for Success/Ref.Designs/Extension board/1.44 - 2.7/Code/Firmware/LaunchPad/EPD Extension Board v1.11/EPD_Extension_Board/src" --include_path="D:/Partnering for Success/Ref.Designs/Extension board/1.44 - 2.7/Code/Firmware/LaunchPad/EPD Extension Board v1.11/EPD_Extension_Board/src/EPD_Kit_Tool" --include_path="D:/Partnering for Success/Ref.Designs/Extension board/1.44 - 2.7/Code/Firmware/LaunchPad/EPD Extension Board v1.11/EPD_Extension_Board/src/Pervasive_Displays_small_EPD" --define=__MSP430G2553__ --printf_support=minimal --preproc_with_compile --preproc_dependency="src/EPD_Kit_Tool/Drivers/EPD_LED.pp" --obj_directory="src/EPD_Kit_Tool/Drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/EPD_Kit_Tool/Drivers/Uart_Driver.obj: ../src/EPD_Kit_Tool/Drivers/Uart_Driver.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv5/tools/compiler/msp430_4.2.3/bin/cl430" -vmsp --abi=eabi --opt_for_speed=1 --include_path="C:/ti/ccsv5/ccs_base/msp430/include" --include_path="C:/ti/ccsv5/tools/compiler/msp430_4.2.3/include" --include_path="D:/Partnering for Success/Ref.Designs/Extension board/1.44 - 2.7/Code/Firmware/LaunchPad/EPD Extension Board v1.11/EPD_Extension_Board/src/EPD_Kit_Tool/Drivers" --include_path="D:/Partnering for Success/Ref.Designs/Extension board/1.44 - 2.7/Code/Firmware/LaunchPad/EPD Extension Board v1.11/EPD_Extension_Board/src" --include_path="D:/Partnering for Success/Ref.Designs/Extension board/1.44 - 2.7/Code/Firmware/LaunchPad/EPD Extension Board v1.11/EPD_Extension_Board/src/EPD_Kit_Tool" --include_path="D:/Partnering for Success/Ref.Designs/Extension board/1.44 - 2.7/Code/Firmware/LaunchPad/EPD Extension Board v1.11/EPD_Extension_Board/src/Pervasive_Displays_small_EPD" --define=__MSP430G2553__ --printf_support=minimal --preproc_with_compile --preproc_dependency="src/EPD_Kit_Tool/Drivers/Uart_Driver.pp" --obj_directory="src/EPD_Kit_Tool/Drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


