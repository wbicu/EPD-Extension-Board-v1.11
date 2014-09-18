/**
 * \file
 *
 * \brief Sample project code for demonstrating Pervasive Displays Inc. 1.44", 2" or 2.7" EPD
 *
 * \note There is quick start guide at the end of this file
 *
 * Copyright (c) 2012-2014 Pervasive Displays Inc. All rights reserved.
 *
 *  Authors: Pervasive Displays Inc.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * \brief Demonstration by EPD Extension board on EPD for showing the images
 *        alternatively or working with EPD Kit Tool
 *
 * \par Content
 * -# Include Pervasive_Displays_small_EPD.h: EPD definitions
 * -# Include if defined EPD_KIT_TOOL_FUNCTIONS, include EPD_Kit_Tool_Process.h
 *            for working with EPD Kit Tool, or include image_data.h to load image
 *            data array
 */
//#include "conf_EPD.h"
#include "Pervasive_Displays_small_EPD.h"
#if (defined EPD_KIT_TOOL_FUNCTIONS)
#include "EPD_Kit_Tool_Process.h"
#else
#include "image_data.h"
#endif

#define DCO_1MHz  0
#define DCO_8MHz  1
#define DCO_12MHz 2
#define DCO_16MHz 3

/**
 * \brief Set CPU work Frequency
 *
 * \param select_index The defined CPU frequency
 * */
void set_MCU_frequency(uint8_t select_index) {

	switch (select_index) {
	case DCO_1MHz:
		if (CALBC1_1MHZ == 0xFF || CALDCO_1MHZ == 0xFF) {
			while (1)
				; // If calibration constants erased, do not load, trap CPU.
		}
		BCSCTL1 = CALBC1_1MHZ; // Set range
		DCOCTL = CALDCO_1MHZ; // Set DCO step + modulation */
		break;
	case DCO_8MHz:
		if (CALBC1_8MHZ == 0xFF || CALDCO_8MHZ == 0xFF) {
			while (1)
				;
		}
		BCSCTL1 = CALBC1_8MHZ;
		DCOCTL = CALDCO_8MHZ;
		break;
	case DCO_12MHz:
		if (CALBC1_12MHZ == 0xFF || CALDCO_12MHZ == 0xFF) {
			while (1)
				;
		}
		BCSCTL1 = CALBC1_12MHZ;
		DCOCTL = CALDCO_12MHZ;
		break;
	case DCO_16MHz:
		if (CALBC1_16MHZ == 0xFF || CALDCO_16MHZ == 0xFF) {
			//Info is missing, guess at a good value.
			BCSCTL1 = 0x8f; //CALBC1_16MHZ at 0x10f9
			DCOCTL = 0x9C;  //CALDCO_16MHZ at 0x10f8
		} else {
			BCSCTL1 = CALBC1_16MHZ;
			DCOCTL = CALDCO_16MHZ;
		}
		break;
	}
}

/**
 * \brief LaunchPad initialization
 */
void system_init(void) {
	WDTCTL = WDTPW + WDTHOLD; // Stop Watchdog Timer
	set_MCU_frequency(DCO_16MHz); //set CPU work Frequency
	__delay_cycles(1600000);
	__delay_cycles(1600000);

}

/**
* \brief The main function will start showing two images alternatively on
* corresponding EPD depends on specified EPD size or work with EPD Kit Tool
*
* \note
* EPD size: EPD_144 = 1.44 inch, EPD_200 = 2 inch, EPD_270 = 2.7 inch
*/
int main(void) {
	/* Initialize system clock and TI LaunchPad board */
	system_init();
	/* Initialize EPD hardware */
	EPD_display_init();

	__bis_SR_register(GIE); //enable interrupts

#if (defined EPD_KIT_TOOL_FUNCTIONS) /** if working with EPD Kit Tool (default)***************/
	LED_init();
	EPD_Kit_Tool_process_init();
	for(;;) {
		EPD_Kit_tool_process_task();
	}

#else /** if showing two images alternatively ***************************************/
	for(;;) {
		/* User selects which EPD size to run demonstration by changing the
		 * USE_EPD_Type in image_data.h
		 * The Image data arrays for each EPD size are defined at image_data.c */
#if(USE_EPD_Type==USE_EPD144)
		EPD_display_from_pointer(EPD_144,(uint8_t *)&image_array_144_2,(uint8_t *)&image_array_144_1);
#elif(USE_EPD_Type==USE_EPD200)
		EPD_display_from_pointer(EPD_200,(uint8_t *)&image_array_200_2,(uint8_t *)&image_array_200_1);
#elif(USE_EPD_Type==USE_EPD270)
/* Due to if loading two image arrays for 2.7", the code size will exceed the MSP430 flash.
 * If using COG_V230_G2 without working with EPD Kit Tool, the demo will load 1st image continuously.*/
#ifdef COG_V230_G2
		EPD_display_from_pointer(EPD_270,(uint8_t *)&image_array_270_1,(uint8_t *)&image_array_270_1);
#else
		EPD_display_from_pointer(EPD_270,(uint8_t *)&image_array_270_2,(uint8_t *)&image_array_270_1);
#endif
#endif

		/* The interval of two images alternatively change is 10 seconds */
		delay_ms(10000);

#if(USE_EPD_Type==USE_EPD144)
		EPD_display_from_pointer(EPD_144,(uint8_t *)&image_array_144_1,(uint8_t *)&image_array_144_2);
#elif(USE_EPD_Type==USE_EPD200)
		EPD_display_from_pointer(EPD_200,(uint8_t *)&image_array_200_1,(uint8_t *)&image_array_200_2);
#elif(USE_EPD_Type==USE_EPD270)
		/* Due to if loading two image arrays for 2.7", the code size will exceed the MSP430 flash.
		 * If using COG_V230_G2 without working with EPD Kit Tool, the demo will load 1st image continuously.*/
#ifdef COG_V230_G2
		EPD_display_from_pointer(EPD_270,(uint8_t *)&image_array_270_1,(uint8_t *)&image_array_270_1);
#else
		EPD_display_from_pointer(EPD_270,(uint8_t *)&image_array_270_1,(uint8_t *)&image_array_270_2);
#endif
#endif

		/* The interval of two images alternatively change is 10 seconds */
		delay_ms(10000);
	}
#endif
}


/**
 * \page - Quick Start Guide
 *
 * This is the quick start guide for the EPD Extension board made by Pervasive Displays Inc.
 * with its small size EPDs on how to setup the kit to MSP430 LaunchPad(MSP-EXP430G2).
 * The code example in main.c shows two ways for EPD updates, images change
 * alternately from image array and work with PDi's EPD Kit Tool by graphic
 * user interface. It also instructs how to use the display functions.
 *
 * \note
 * - Released Date: 10 Mar, 2014.  Version: 1.11
 *   which is able to work with EPD Kit Tool v1.0
 * - CCS version = v5.5 with compiler v4.2.3
 *   If you will load project code in CCS v5.4 with compiler v4.1.8 below, please
 *   see the known issue section.
 * - PDi = Pervasive Displays Inc. http://www.pervasivedisplays.com
 * - EPD = Electronic Paper Display (Electrophoretic Display)
 * - EPD Extension Board/Kit = The driving board has direct socket to LaunchPad and
 *   also features 20 pin out bridges to your product or development kit
 * - EPD Kit Tool = The application(user graphic interface) to work with EPD
 *   Extension kit. You can download the installer and source code at here:
 *   http://www.pervasivedisplays.com/kits/ext_kit
 * - COG = Chip on Glass, the driver IC on EPD module
 * - COG G1 or G2: G is for generation. PDi offers V110 with G1 COG and V230 with G2 COG
 *   EPD to the market.(~2014)
 * - For driving PDi's small size EPDs, please read the "COG Driver Interface
 *   Timing" document(hereinafter COG Document) first. It explains the interface
 *   to the COG driver of EPD for a MCU based solution.
 * - COG G1 Document number: 4P008-00
 *   Download URL: http://www.pervasivedisplays.com/LiteratureRetrieve.aspx?ID=138408
 * - COG G2 Document number: 4P015-00
 *   Download URL: http://www.pervasivedisplays.com/LiteratureRetrieve.aspx?ID=198794
 * - This project code supports EPD size: 1.44 inch, 2 inch and 2.7 inch
 * - Supports MSP430 LaunchPad: MSP-EXP430G2
 * - The G2 EPD hasn't supported partial updated yet. The ASCII function of EPD
 *   Kit Tool when connecting V230 G2 2" or 2.7" EPD has disabled temporary (7Feb'14).
 *   When clicking [Send] button in EPD Kit Tool, there will do nothing on EPD.
 *
 * \section File_Explanation
 * - <b>image_data:</b>\n
 *   It defines the image arrays of each EPD size. User can use the array without
 *   application input.
 * - <b>conf_EPD.h:</b> The EPD configurations.\n
 *   -# EPD_KIT_TOOL_FUNCTIONS: define it if you will work with EPD Kit Tool
 *      or comment out this define if just load two images
 *   -# COG_Vxxx_Gx: define which COG driving waveform you will use
 *   -# COG_SPI_baudrate: SPI speed
 *   -# EPD_KIT_TOOL_VERSION: the firmware version of this project code
 *   -# EPD_KIT_TOOL_KIT_ID: define this kit ID, 0x0101
 * - <b>EPD_Kit_Tool</b> folder:\n
 *   If you will work with PDi's EPD Extension Kit, the commands and definitions
 *   are located in this folder.
 *     -# <b>Mem_Flash:</b>\n
 *        The functions of working with flash memory including saving image, easing
 *        images and get/set parameters.
 *     -# <b>Uart_Controller:</b>\n
 *        The functions to control and return system packets with EPD Kit Tool.
 *     -# <b>Char:</b>\n
 *        The definition of ASCII characters.
 *     -# <b>EPD_Kit_Tool_Process:</b>\n
 *        All of the functions that are provided on EPD Kit Tool.
 *     -# <b>Drivers folder:</b>\n
 *        The driver of UART and LED.
 * - <b>Pervasive_Displays_small_EPD</b> folder:\n
 *   All of the COG driving waveforms are located in this folder. Logically developer
 *   doesn't need to change the codes in this folder in order to keep correct driving
 *   the EPDs.\n\n
 *   <b><em>Software architecture:</em></b>\n
 *   [Application (ex. EPD Kit Tool)] <-- [COG Interface (<em>EPD_controller</em>)] <--
 *   [COG Process (<em>EPD_COG_process</em>)] <-- [Hardware Driver (<em>EPD_hardware_driver
 *   & EPD_hardware_gpio</em>)]\n\n
 *    -# <b>EPD_hardware_driver:</b>\n
 *       Most of the COG hardware initialization and configuration. User can implement
 *       the driver layer of EPD if some variables need to be adjusted. The provided
 *       settings and functions are Timer, SPI, PWM, temperature and EPD hardware initialization.
 *    -# <b>EPD_hardware_gpio:</b>\n
 *       GPIO pins configuration.
 *    -# <b>EPD_COG_process.h:</b>\n
 *       The common definition of COG driving process.
 *    -# <b>EPD_controller:</b>\n
 *       The interface for external function to work with EPD.
 *    -# <b>EPD_COG:</b>\n
 *       The link source of different COG and EPD switching to be used.
 *    -# <b>COG</b> folder:\n
 *       Each COG driving file presents the different waveform driving processes of COG
 *       and updating stages.
 *       The parameters of driving different EPD is defined at COG_parameters_t structure
 *       which is easy for developer adjusting initial parameters, resolution, frame time
 *       of MCU and the size of data line.
 *       - <b>EPD_COG_process_Vxxx_Gx:</b>\n
 *         The waveform driving processes and updating stages of COG v? with VXXX EPD.
 *       - <b>EPD_COG_partial_update_Vxxx:</b>\n
 *         The partial update waveform of driving processes and updating stages
 *         of COG v? with VXXX EPD.
 *
 *
 * \section Use_Case
 * -# <b>EPD_display_from_pointer</b>: Load two image data arrays from image_data.c
 *   according to predefined EPD size.
 * -# <b>EPD_display_from_flash</b>:
 *   Load image data from flash memory according to the command by EPD Kit Tool.
 *
 * \section Steps
 * -# Ensure the EPD is connected correctly on the EPD Extension board
 * -# Stack the EPD Extension board onto MSP430 LaunchPad board directly
 * -# Connect the LaunchPad board to computer's USB port via its USB cable
 * -# Find #define COG_V230_G2 in "conf_EPD.h" file. Change the COG_Vxxx_Gx to the correct COG version.
 *    - <b>Run two images only:</b>\n
 *         -# Ensure what the EPD size you are connecting. Open image_data.h file and find
 *            "#define USE_EPD_Type USE_EPD200". Change the USE_EPDXXX to the correct size.
 *         -# Find "conf_EPD.h" file. Comment out "#define EPD_KIT_TOOL_FUNCTIONS"
 *         -# Start debugging to program the driving code to MSP430 MCU. The EPD will show
 *            two images change alternately every 10 seconds (default).
 *    - <b>Work with EPD Kit Tool:</b>\n
 *         -# Find "conf_EPD.h" file. Ensure "#define EPD_KIT_TOOL_FUNCTIONS".
 *         -# Start debugging to program the driving code to MSP430 MCU.
 *         -# Install EPD Kit Tool and then execute it. On the EPD Kit Tool, click [Scan]
 *            button to search "TI_LaunchPad" kit. If found, click [Connect].
 *         -# Refer to EPD Extension Kit_User manual which can be downloaded in PDi website.
 *
 *
 * \section PDi EPD displays
 * ========================================
 * | Size | PDi Model              | FPL  |
 * |------|------------------------|------|
 * | 1.44 | EK014AS014, EK014AS015 | V110 |
 * | 2.0  | EG020AS012, EG020AS013 | V110 |
 * | 2.7  | EM027AS012, EM027AS013 | V110 |
 * | 1.44 | TBD (Q2'14)            | V230 |
 * | 2.0  | EG020BS011, EG020BS012 | V230 |
 * | 2.7  | EM027BS013, EM027BS014 | V230 |
 *
 *
 * \section known_issue Known issue
 * -# <b>Load project code in CCS v5.4 below</b>\n
 *	  - When right clicking on project name in CCS and choose "Properties", please check on
 *	    "General" item of left side tree view. In some cases, there may be Compiler version and
 *	    Effective compiler version fields. The Effective compiler version field is the version
 *	    of compiler tools being used for that build. If the project was originally created with
 *	    a version of compiler tools different than what is installed in your machine or what CCS
 *	    is set to use, then the Compiler version field will list that value. This is important
 *	    to understand in order to know exactly which version of compiler is being used to build
 *	    your project.
 *	  - Switch the Compiler version to Effective compiler version that has really installed in your
 *	    CCS. In CCS v5.4, the Compiler version should be v4.1.5, v4.1.7 or v4.1.8.
 *	  - Switch to Build/MSP430 Compiler/Include Options of left side tree view, make sure the bottom
 *	 	"Add dir to #include search path" are included six paths below. When loading CCS project
 *	 	in older IDE, the paths below are gone probably. Please add them on.
 *		- "${CCS_BASE_ROOT}/msp430/include"
 *		- "${CG_TOOL_ROOT}/include"
 *		- "${workspace_loc:/${ProjName}/src/EPD_Kit_Tool/Drivers}"
 *		- "${workspace_loc:/${ProjName}/src}"
 *		- "${workspace_loc:/${ProjName}/src/EPD_Kit_Tool}"
 *		- "${workspace_loc:/${ProjName}/src/Pervasive_Displays_small_EPD}"
 *	  - Switch to Build/MSP430 Linker/File Search Path of left side tree view, make sure the bottom
 *	 	"Add <dir> to library search path" are included three paths below. When loading CCS project
 *	 	in older IDE, the paths below are gone probably.  Please add them on.
 *		- "${CCS_BASE_ROOT}/msp430/include"
 *		- "${CG_TOOL_ROOT}/lib"
 *		- "${CG_TOOL_ROOT}/include"
 *	  - Click OK and try to Rebuild project. This CCS project code is able to run in CCS v5.4 with
 * 	 	Compiler v4.1.x
 *
 */
