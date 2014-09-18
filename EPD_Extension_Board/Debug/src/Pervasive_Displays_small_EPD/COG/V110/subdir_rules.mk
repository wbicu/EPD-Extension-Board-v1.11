################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
src/Pervasive_Displays_small_EPD/COG/V110/EPD_COG_process_V110.obj: ../src/Pervasive_Displays_small_EPD/COG/V110/EPD_COG_process_V110.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv5/tools/compiler/msp430_4.1.8/bin/cl430" -vmsp --abi=eabi -g --include_path="C:/ti/ccsv5/ccs_base/msp430/include" --include_path="C:/ti/ccsv5/tools/compiler/msp430_4.1.8/include" --include_path="D:/epaper/TI LaunchPad/firmware/EPD_Extension_Board_v1.00_for_TI_LaunchPad/EPD Extension Board v1.01/EPD Extension Board v1.02/EPD Extension Board/src/EPD_Kit_Tool/Drivers" --include_path="D:/epaper/TI LaunchPad/firmware/EPD_Extension_Board_v1.00_for_TI_LaunchPad/EPD Extension Board v1.01/EPD Extension Board v1.02/EPD Extension Board/src" --include_path="D:/epaper/TI LaunchPad/firmware/EPD_Extension_Board_v1.00_for_TI_LaunchPad/EPD Extension Board v1.01/EPD Extension Board v1.02/EPD Extension Board/src/EPD_Kit_Tool" --include_path="D:/epaper/TI LaunchPad/firmware/EPD_Extension_Board_v1.00_for_TI_LaunchPad/EPD Extension Board v1.01/EPD Extension Board v1.02/EPD Extension Board/src/Pervasive_Displays_small_EPD" --advice:power="all" --define=__MSP430G2553__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="src/Pervasive_Displays_small_EPD/COG/V110/EPD_COG_process_V110.pp" --obj_directory="src/Pervasive_Displays_small_EPD/COG/V110" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


