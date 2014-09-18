################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
src/Pervasive_Displays_small_EPD/COG/V230/EPD_COG_process_v230_G2_2.obj: ../src/Pervasive_Displays_small_EPD/COG/V230/EPD_COG_process_v230_G2_2.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv5/tools/compiler/msp430_4.2.2/bin/cl430" -vmsp --abi=eabi --opt_for_speed=0 --include_path="C:/ti/ccsv5/ccs_base/msp430/include" --include_path="C:/ti/ccsv5/tools/compiler/msp430_4.2.2/include" --include_path="D:/epaper/TI LaunchPad/firmware/EPD Extension Board v1.01/EPD Extension Board v1.01/EPD_Extension_Board/src/EPD_Kit_Tool/Drivers" --include_path="D:/epaper/TI LaunchPad/firmware/EPD Extension Board v1.01/EPD Extension Board v1.01/EPD_Extension_Board/src" --include_path="D:/epaper/TI LaunchPad/firmware/EPD Extension Board v1.01/EPD Extension Board v1.01/EPD_Extension_Board/src/EPD_Kit_Tool" --include_path="D:/epaper/TI LaunchPad/firmware/EPD Extension Board v1.01/EPD Extension Board v1.01/EPD_Extension_Board/src/Pervasive_Displays_small_EPD" --define=__MSP430G2553__ --printf_support=minimal --preproc_with_compile --preproc_dependency="src/Pervasive_Displays_small_EPD/COG/V230/EPD_COG_process_v230_G2_2.pp" --obj_directory="src/Pervasive_Displays_small_EPD/COG/V230" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


