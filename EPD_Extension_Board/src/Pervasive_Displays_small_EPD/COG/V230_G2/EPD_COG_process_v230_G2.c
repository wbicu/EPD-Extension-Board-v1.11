/**
* \file
*
* \brief The waveform driving processes and updating stages of G2 COG with V230 EPD
*
* Copyright (c) 2012-2014 Pervasive Displays Inc. All rights reserved.
*
* \asf_license_start
*
* \page License
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice,
*    this list of conditions and the following disclaimer.
*
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
*
* 3. The name of Atmel may not be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
* 4. This software may only be redistributed and used in connection with an
*    Atmel microcontroller product.
*
* THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
* EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
* OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
* \asf_license_stop
**/

#include "EPD_COG_Process.h"
#ifdef COG_V230_G2

#define ADDRESS_NULL		0xffffffff
//EPD Panel parameters
const struct COG_parameters_t COG_parameters[COUNT_OF_EPD_TYPE]  = {
	{
		// FOR 1.44"
		{0x00,0x00,0x00,0x00,0x00,0x0F,0xFF,0x00},
		0x03,
		(128/8),
		96,
		((((128+96)*2)/8)+1),
		0,
		480
	},
	{
		// For 2.0"
		{0x00,0x00,0x00,0x00,0x01,0xFF,0xE0,0x00},
		0x03,
		(200/8),
		96,
		((((200+96)*2)/8)+1),
		0,
		480
	},
	{
		// For 2.7"
		{0x00,0x00,0x00,0x7F,0xFF,0xFE,0x00,0x00},
		0x00,
		(264/8),
		176,
		((((264+176)*2)/8)+1),
		0,
		630
	}
};

/* \brief EPD Waveform parameters
 * \note the parameters of waveform table below is different from the G2 COG document due to
 *       use block size is easier to achieve than accurate block time for different MCU.
 *       The approach is also working.
 * */
 const struct EPD_WaveformTable_Struct E_Waveform[COUNT_OF_EPD_TYPE][3]  = {
		{// FOR 1.44"
			{//50 』 T 「 40
				4,				//stage1_frame1
				16,				//stage1_block1
				2,				//stage1_step1				
				155,			//stage2_t1
				155,			//stage2_t2
				4,				//stage2_cycle
				4,				//stage3_frame3
				16,				//stage3_block3
				2				//stage3_step3
			}
			,{//40 』 T 「 10
				4,				//stage1_frame1
				16,				//stage1_block1
				2,				//stage1_step1				
				155,			//stage2_t1
				155,			//stage2_t2
				4,				//stage2_cycle
				4,				//stage3_frame3
				16,				//stage3_block3
				2				//stage3_step3
			},
			{//10 』 T 「 0
				2,				//stage1_frame1
				42,				//stage1_block1
				6,				//stage1_step1
				392,			//stage2_t1
				392,			//stage2_t2
				4,				//stage2_cycle
				2,				//stage3_frame3
				42,				//stage3_block3
				6				//stage3_step3
			}
			
		},
		{// For 2.0"
			{//50 』 T 「 40
				4,				//stage1_frame1
				36,				//stage1_block1
				2,				//stage1_step1				
				196,			//stage2_t1
				196,			//stage2_t2
				4,				//stage2_cycle
				4,				//stage3_frame3
				36,				//stage3_block3
				2				//stage3_step3
			},
			{//40 』 T 「 10
				2,				//stage1_frame1
				36,				//stage1_block1
				2,				//stage1_step1
				196,			//stage2_t1
				196,			//stage2_t2
				4,				//stage2_cycle
				2,				//stage3_frame3
				36,				//stage3_block3
				2				//stage3_step3
			},
			{//10 』 T 「 0
				2,				//stage1_frame1
				36,				//stage1_block1
				2,				//stage1_step1
				392,			//stage2_t1
				392,			//stage2_t2
				4,				//stage2_cycle
				2,				//stage3_frame3
				36,				//stage3_block3
				2				//stage3_step3
			}
		},
		{// For 2.7"
			{//50 』 T 「 40
				4,				//stage1_frame1
				28,				//stage1_block1
				4,				//stage1_step1
				196,			//stage2_t1
				196,			//stage2_t2
				4,				//stage2_cycle
				4,				//stage3_frame3
				28,				//stage3_block3
				4				//stage3_step3
			},
			{//40 』 T 「 10
				2,				//stage1_frame1
				28,				//stage1_block1
				4,				//stage1_step1
				196,			//stage2_t1
				196,			//stage2_t2
				4,				//stage2_cycle
				2,				//stage3_frame3
				28,				//stage3_block3
				4				//stage3_step3
			},
			{//10 』 T 「 0
				2,				//stage1_frame1
				28,				//stage1_block1
				4,				//stage1_step1
				392,			//stage2_t1
				392,			//stage2_t2
				4,				//stage2_cycle
				2,				//stage3_frame3
				28,				//stage3_block3
				4				//stage3_step3
			}
		},
	 
 };

const uint8_t   SCAN_TABLE[4] = {0xC0,0x30,0x0C,0x03};
	
static struct EPD_WaveformTable_Struct *action__Waveform_param;
static COG_line_data_packet_type COG_Line;
static EPD_read_flash_handler _On_EPD_read_flash;
static uint8_t  *data_line_even;
static uint8_t  *data_line_odd;
static uint8_t  *data_line_scan;
static uint8_t  *data_line_border_byte;

/**
* \brief According to EPD size and temperature to get stage_time
* \note Refer to COG document Section 5.3 for more details
*
* \param EPD_type_index The defined EPD size
*/
static void set_temperature_factor(uint8_t EPD_type_index) {
	int8_t temperature;
	temperature = get_temperature();	
        if (50 >= temperature  && temperature > 40){
			action__Waveform_param=(struct EPD_WaveformTable_Struct *)&E_Waveform[EPD_type_index][0];
		}else if (40 >= temperature  && temperature > 10){
			action__Waveform_param=(struct EPD_WaveformTable_Struct *)&E_Waveform[EPD_type_index][1];
		}else if (10 >= temperature  && temperature > 0){
			action__Waveform_param=(struct EPD_WaveformTable_Struct *)&E_Waveform[EPD_type_index][2];
		}else action__Waveform_param=(struct EPD_WaveformTable_Struct *)&E_Waveform[EPD_type_index][1]; //Default
}

/**
* \brief Initialize the EPD hardware setting
*/
void EPD_init(void) {
	EPD_display_hardware_init();
	EPD_cs_low();
	EPD_rst_low();
	EPD_discharge_low();
	EPD_border_low();
}

/**
* \brief Select the EPD size to get line data array for driving COG
*
* \param EPD_type_index The defined EPD size
*/
void COG_driver_EPDtype_select(uint8_t EPD_type_index) {
	switch(EPD_type_index) {
		case EPD_144:
		data_line_even = &COG_Line.line_data_by_size.line_data_for_144.even[0];
		data_line_odd  = &COG_Line.line_data_by_size.line_data_for_144.odd[0];
		data_line_scan = &COG_Line.line_data_by_size.line_data_for_144.scan[0];
		data_line_border_byte = &COG_Line.line_data_by_size.line_data_for_144.border_byte;
		break;
		case EPD_200:
		data_line_even = &COG_Line.line_data_by_size.line_data_for_200.even[0];
		data_line_odd  = &COG_Line.line_data_by_size.line_data_for_200.odd[0];
		data_line_scan = &COG_Line.line_data_by_size.line_data_for_200.scan[0];
		data_line_border_byte = &COG_Line.line_data_by_size.line_data_for_200.border_byte;
		break;
		case EPD_270:
		data_line_even = &COG_Line.line_data_by_size.line_data_for_270.even[0];
		data_line_odd  = &COG_Line.line_data_by_size.line_data_for_270.odd[0];
		data_line_scan = &COG_Line.line_data_by_size.line_data_for_270.scan[0];
		data_line_border_byte = &COG_Line.line_data_by_size.line_data_for_270.border_byte;
		break;
	}
}

/**
* \brief Power on COG Driver
* \note For detailed flow and description, please refer to the COG G2 document Section 3.
*/
void EPD_power_on (void) {	
	/* Initial state */
	EPD_Vcc_turn_on(); //Vcc and Vdd >= 2.7V	
	EPD_cs_high();
	EPD_border_high();
	EPD_rst_high();
	delay_ms(5);	
	EPD_rst_low();
	delay_ms(5);
	EPD_rst_high();
	delay_ms(5);
}


/**
* \brief Initialize COG Driver
* \note For detailed flow and description, please refer to the COG G2 document Section 4.
*
* \param EPD_type_index The defined EPD size
*/
uint8_t EPD_initialize_driver (uint8_t EPD_type_index) {
	
	uint16_t i;
	// Empty the Line buffer
	for (i = 0; i <= LINE_BUFFER_DATA_SIZE; i ++) {
		COG_Line.uint8[i] = 0x00;
	}
	// Determine the EPD size for driving COG
	COG_driver_EPDtype_select(EPD_type_index);

	// Sense temperature to determine Temperature Factor
	set_temperature_factor(EPD_type_index);
	i = 0;
	
	while (EPD_IsBusy()) {
		if((i++) >= 0x0FFF) return ERROR_BUSY;
	}
	
	//Check COG ID
	if((SPI_R(0x72,0x00) & 0x0f) !=0x02) return ERROR_COG_ID;

	//Disable OE
	epd_spi_send_byte(0x02,0x40);	

	//Check Breakage
	if((SPI_R(0x0F,0x00) & 0x80) != 0x80) return ERROR_BREAKAGE;
	
	//Power Saving Mode
 	epd_spi_send_byte(0x0B, 0x02);

	//Channel Select
	epd_spi_send (0x01, (uint8_t *)&COG_parameters[EPD_type_index].channel_select, 8);

	//High Power Mode Osc Setting
	epd_spi_send_byte(0x07,0xD1);

	//Power Setting
	epd_spi_send_byte(0x08,0x02);

	//Set Vcom level
	epd_spi_send_byte(0x09,0xC2);

	//Power Setting
	epd_spi_send_byte(0x04,0x03);

	//Driver latch on
	epd_spi_send_byte(0x03,0x01);

	//Driver latch off
	epd_spi_send_byte(0x03,0x00);

	delay_ms(5);

	//Chargepump Start
	i=0;
	do {
		//Start chargepump positive V
		//VGH & VDH on
		epd_spi_send_byte(0x05,0x01);

		delay_ms(240);

		//Start chargepump neg voltage
		//VGL & VDL on
		epd_spi_send_byte(0x05,0x03);

		delay_ms(40);

		//Set chargepump
		//Vcom_Driver to ON
		//Vcom_Driver on
		epd_spi_send_byte(0x05,0x0F);

		delay_ms(40);

		//Check DC/DC
		if((SPI_R(0x0F,0x00) & 0x40) != 0x00) break;	
		
	}while((i++) != 4);
	
	if(i>=4) 
	{
		//Output enable to disable
		epd_spi_send_byte(0x02,0x40);
		return ERROR_CHARGEPUMP;
	}
	else  return RES_OK;
}

/**
* \brief Initialize the parameters of Block type stage 
*
* \param EPD_type_index The defined EPD size
* \param EPD_V230_G2_Struct The Block type waveform structure
* \param block_size The width of Block size
* \param step_size The width of Step size
* \param frame_cycle The width of Step size
*/
void stage_init(uint8_t EPD_type_index,struct EPD_V230_G2_Struct *S_epd_v230,
				uint8_t block_size,uint8_t step_size,
				uint8_t frame_cycle)
{
	S_epd_v230->frame_y0 = 0;
	S_epd_v230->frame_y1 = 176;
	S_epd_v230->block_y0 = 0;
	S_epd_v230->block_y1 = 0;
	S_epd_v230->step_y0 = 0;
	S_epd_v230->step_y1 = 0;
	S_epd_v230->block_size = action__Waveform_param->stage1_block1;
	S_epd_v230->step_size =action__Waveform_param->stage1_step1;
	S_epd_v230->frame_cycle = action__Waveform_param->stage1_frame1;
	S_epd_v230->number_of_steps = (COG_parameters[EPD_type_index].vertical_size / S_epd_v230->step_size) + (action__Waveform_param->stage1_block1 / action__Waveform_param->stage1_step1) -1;
	
}

/**
* \brief For Frame type waveform to update all black/white pattern
*
* \param EPD_type_index The defined EPD size
* \param bwdata Black or White color to whole screen
* \param work_time The working time
*/
static inline void same_data_frame (uint8_t EPD_type_index, uint8_t bwdata, uint32_t work_time) {
	uint16_t i;
	for (i = 0; i <  COG_parameters[EPD_type_index].horizontal_size; i++) {
		data_line_even[i]=bwdata;
		data_line_odd[i]=bwdata;
	}
	start_EPD_timer();
	do 
	{	
		for (i = 0; i < COG_parameters[EPD_type_index].vertical_size; i++) {
			
			/* Scan byte shift per data line */
			data_line_scan[(i>>2)]=SCAN_TABLE[(i%4)];
			
			/* Sending data */
			epd_spi_send (0x0A, (uint8_t *)&COG_Line.uint8, COG_parameters[EPD_type_index].data_line_size);
		 
			/* Turn on Output Enable */
			epd_spi_send_byte (0x02, 0x07);
		
			data_line_scan[(i>>2)]=0;
			
		}
	} while (get_current_time_tick()<(work_time));
		/* Stop system timer */
		stop_EPD_timer();
}

/**
* \brief Write nothing Line to COG
* \note A line whose all Scan Bytes are 0x00
*
* \param EPD_type_index The defined EPD size
*/
void nothing_line(uint8_t EPD_type_index) {
	uint16_t i;
	for (i = 0; i <  COG_parameters[EPD_type_index].horizontal_size; i++) {
		data_line_even[i]	=	NOTHING;
		data_line_odd[i]	=	NOTHING;
	}
}


/**
* \brief Get line data of Stage 1 and 3
*
* \note
* - One dot/pixel is comprised of 2 bits which are White(10), Black(11) or Nothing(01).
*   The image data bytes must be divided into Odd and Even bytes.
* - The COG driver uses a buffer to write one line of data (FIFO) - interlaced
*   It's different order from COG_G1
*   Odd byte {D(199,y),D(197,y), D(195,y), D(193,y)}, ... ,{D(7,y),D(5,y),D(3,y), D(1,y)}
*   Scan byte {S(96), S(95)...}
*   Odd byte  {D(2,y),D(4,y), D(6,y), D(8,y)}, ... ,{D(194,y),D(196,y),D(198,y), D(200,y)}
* - For more details on the driving stages, please refer to the COG G2 document Section 5.
*
* \param EPD_type_index The defined EPD size
* \param image_ptr The pointer of memory that stores image that will send to COG
* \param stage_no The assigned stage number that will proceed
*/

void read_line_data_handle(uint8_t EPD_type_index,uint8_t *image_prt,uint8_t stage_no)
{
	int16_t x,k;
	uint8_t	temp_byte; // Temporary storage for image data check
	k=COG_parameters[EPD_type_index].horizontal_size-1;	
	for (x =0 ; x < COG_parameters[EPD_type_index].horizontal_size ; x++) {
				temp_byte = *image_prt++;
				switch(stage_no) {
					case Stage1: // Inverse image
					/* Example at stage 1 to get Even and Odd data. It's different order from G1.
					* +---------+----+----+----+----+----+----+----+----+
					* |         |bit7|bit6|bit5|bit4|bit3|bit2|bit1|bit0|
					* |temp_byte+----+----+----+----+----+----+----+----+
					* |         |  1 |  0 |  1 |  1 |  0 |  1 |  0 |  0 |
					* +---------+----+----+----+----+----+----+----+----+ */
					data_line_odd[x]       = ((temp_byte & 0x40) ? BLACK3  : WHITE3); // WHITE3 = 0x80 = 1000 0000
					data_line_odd[x]      |= ((temp_byte & 0x10) ? BLACK2  : WHITE2); // BLACK2 = 0x30 = 0011 0000
					data_line_odd[x]      |= ((temp_byte & 0x04) ? BLACK1  : WHITE1); // BLACK1 = 0x0C = 0000 1100
					data_line_odd[x]	  |= ((temp_byte & 0x01) ? BLACK0  : WHITE0); // WHITE0 = 0x02 = 0000 0010
					/* data_line_odd[x] = 1000 0000 | 0011 0000 | 0000 1100 | 0000 0010 = 1011 1110 ==> 1011 1110
					* See Even data row at the table below*/
					
					data_line_even[k]    = ((temp_byte & 0x80) ? BLACK0  : WHITE0); // BLACK0 = 0x03 = 0000 0011
					data_line_even[k]   |= ((temp_byte & 0x20) ? BLACK1  : WHITE1); // BLACK1 = 0x0C = 0000 1100
					data_line_even[k]   |= ((temp_byte & 0x08) ? BLACK2  : WHITE2); // WHITE2 = 0x20 = 0010 0000
					data_line_even[k--] |= ((temp_byte & 0x02) ? BLACK3  : WHITE3); // WHITE3 = 0x80 = 1000 0000
					/* data_line_even[k] = 0000 0011 | 0000 1100 | 0010 0000 | 1000 0000 = 1010 1111 ==> 1111 1010
					* See Odd data row at the table below
					* +---------+----+----+----+----+----+----+----+----+
					* |         |bit7|bit6|bit5|bit4|bit3|bit2|bit1|bit0|
					* |temp_byte+----+----+----+----+----+----+----+----+
					* |         |  1 |  0 |  1 |  1 |  0 |  1 |  0 |  0 |
					* +---------+----+----+----+----+----+----+----+----+
					* | Color   |  W |  B |  W |  W |  B |  W |  B |  B | W=White, B=Black, N=Nothing
					* +---------+----+----+----+----+----+----+----+----+
					* | Stage 1 |  B |  W |  B |  B |  W |  B |  W |  W | Inverse
					* +---------+----+----+----+----+----+----+----+----+
					* | Input   | 11 | 10 | 11 | 11 | 10 | 11 | 10 | 10 | W=10, B=11, N=01
					* +---------+----+----+----+----+----+----+----+----+
					* |Even data| 11 |    | 11 |    | 10 |    | 10 |    | = 1111 1010
					* +---------+----+----+----+----+----+----+----+----+
					* |Odd data |    | 10 |    | 11 |    | 11 |    | 10 | = 1011 1110
					* +---------+----+----+----+----+----+----+----+----+ */
					break;				
					case Stage3: // New image
						data_line_odd[x]		 = ((temp_byte & 0x40) ? WHITE3  : BLACK3 );
						data_line_odd[x]		|= ((temp_byte & 0x10) ? WHITE2  : BLACK2 );
						data_line_odd[x]		|= ((temp_byte & 0x04) ? WHITE1  : BLACK1 );
						data_line_odd[x]		|= ((temp_byte & 0x01) ? WHITE0  : BLACK0 );

						data_line_even[k]		 = ((temp_byte & 0x80) ? WHITE0  : BLACK0 );
						data_line_even[k]		|= ((temp_byte & 0x20) ? WHITE1  : BLACK1 );
						data_line_even[k]		|= ((temp_byte & 0x08) ? WHITE2  : BLACK2 );
						data_line_even[k--]		|= ((temp_byte & 0x02) ? WHITE3  : BLACK3 );
					break;
				}
		}	
}


/**
* \brief The base function to handle the driving stages for Frame and Block type
*
* \note
* - There are 3 stages to complete an image update on COG_V230_G2 type EPD.
* - For more details on the driving stages, please refer to the COG G2 document Section 5.4
*
* \param EPD_type_index The defined EPD size
* \param image_ptr The pointer of image array that stores image that will send to COG
* \param image_data_address The address of memory that stores image
* \param stage_no The assigned stage number that will proceed
* \param lineoffset Line data offset
*/
void stage_handle_Base(uint8_t EPD_type_index,uint8_t *image_prt,long image_data_address,
						uint8_t stage_no,uint8_t lineoffset)
{	
	struct EPD_V230_G2_Struct S_epd_v230;
	int16_t cycle,m,i; //m=number of steps
	//uint8_t isLastframe = 0;	//If it is the last frame to send Nothing at the fist scan line
	uint8_t isLastBlock=0;		//If the beginning line of block is in active range of EPD
	int16_t scanline_no=0;
	uint8_t *action_block_prt;
	long action_block_address;
	uint8_t byte_array[LINE_BUFFER_DATA_SIZE];
	/** Stage 2: BLACK/WHITE image, Frame type */
	if(stage_no==Stage2)
	{
		for(i=0;i<action__Waveform_param->stage2_cycle;i++)
		{
			same_data_frame (EPD_type_index,ALL_BLACK,action__Waveform_param->stage2_t1);
			same_data_frame (EPD_type_index,ALL_WHITE,action__Waveform_param->stage2_t2);
		}
		return;
	}
	/** Stage 1 & 3, Block type */
	// The frame/block/step of Stage1 and Stage3 are default the same.
	stage_init(EPD_type_index,
				&S_epd_v230,
				action__Waveform_param->stage1_block1,
				action__Waveform_param->stage1_step1,
				action__Waveform_param->stage1_frame1);
	 
	 /* Repeat number of frames */
   	 for (cycle = 0; cycle < (S_epd_v230.frame_cycle ); cycle++)
   	 {
		
	    // if (cycle == (S_epd_v230.frame_cycle - 1)) isLastframe = 1;
		 
		 isLastBlock = 0;
		 S_epd_v230.step_y0 = 0;
		 S_epd_v230.step_y1 = S_epd_v230.step_size ;
		 S_epd_v230.block_y0 = 0;
		 S_epd_v230.block_y1 = 0;
		 /* Move number of steps */
	   	 for (m = 0; m < S_epd_v230.number_of_steps; m++)	 
	   	 {		   	
			 S_epd_v230.block_y1 += S_epd_v230.step_size;
			 S_epd_v230.block_y0 = S_epd_v230.block_y1 - S_epd_v230.block_size;
			/* reset block_y0=frame_y0 if block is not in active range of EPD */
		   	 if (S_epd_v230.block_y0 < S_epd_v230.frame_y0) S_epd_v230.block_y0 = S_epd_v230.frame_y0;
			
			/* if the beginning line of block is in active range of EPD */
			 if (S_epd_v230.block_y1 == S_epd_v230.block_size) isLastBlock = 1;
			 	
			 if(image_prt!=NULL)
			 {
				 action_block_prt=(image_prt+(int)(S_epd_v230.block_y0*lineoffset));	
			 }
			 else if(_On_EPD_read_flash!=NULL)	//Read line data in range of block, read first
			 {
				action_block_address=image_data_address+(long)(S_epd_v230.block_y0*lineoffset);
				_On_EPD_read_flash(action_block_address,(uint8_t *)&byte_array,
									COG_parameters[EPD_type_index].horizontal_size);
				action_block_prt=(uint8_t *)&byte_array;
			 }	
			/* Update line data */
		   	 for (i = S_epd_v230.block_y0; i < S_epd_v230.block_y1; i++)
		   	 {		
				
			     if (i >= COG_parameters[EPD_type_index].vertical_size) break;
				 //if (isLastframe && 
				 if ( 
				  isLastBlock &&(i < (S_epd_v230.step_size + S_epd_v230.block_y0)))
				  {
					  nothing_line(EPD_type_index);					
				  }
				  else	 
				  {			  					 
					  read_line_data_handle(EPD_type_index,action_block_prt,stage_no);					
				  }
			   		
				if(_On_EPD_read_flash!=NULL)	//Read line data in range of block
				{
					action_block_address +=lineoffset;
					_On_EPD_read_flash(action_block_address,(uint8_t *)&byte_array,
					COG_parameters[EPD_type_index].horizontal_size);
					action_block_prt=(uint8_t *)&byte_array;
				}
				else action_block_prt+=lineoffset;
					
				scanline_no= (COG_parameters[EPD_type_index].vertical_size-1)-i;
					
				/* Scan byte shift per data line */
				data_line_scan[(scanline_no>>2)] = SCAN_TABLE[(scanline_no%4)];
				   
				/*  the border uses the internal signal control byte. */
				*data_line_border_byte=0x00;
					   
				/* Sending data */
				epd_spi_send (0x0A, (uint8_t *)&COG_Line.uint8,
				COG_parameters[EPD_type_index].data_line_size);
				
					 
				/* Turn on Output Enable */
				epd_spi_send_byte (0x02, 0x07);
					   
				data_line_scan[(scanline_no>>2)]=0;		
										
		   	 }												
	   	 }
			
    }	
}

/**
* \brief The driving stages from image array (image_data.h) to COG
*
* \param EPD_type_index The defined EPD size
* \param image_ptr The pointer of image array that stores image that will send to COG
* \param stage_no The assigned stage number that will proceed
* \param lineoffset Line data offset
*/
void stage_handle(uint8_t EPD_type_index,uint8_t *image_prt,uint8_t stage_no,uint8_t lineoffset)
{
	stage_handle_Base(EPD_type_index,image_prt,ADDRESS_NULL,stage_no,lineoffset);	
}

/**
* \brief The driving stages from memory to COG
*
* \note
* - This function is additional added here for developer if the image data
*   is stored in Flash memory.
*
* \param EPD_type_index The defined EPD size
* \param image_data_address The address of flash memory that stores image
* \param stage_no The assigned stage number that will proceed
* \param lineoffset Line data offset
*/
static void stage_handle_ex(uint8_t EPD_type_index,long image_data_address,uint8_t stage_no,uint8_t lineoffset) {
	stage_handle_Base(EPD_type_index,NULL,image_data_address,stage_no,lineoffset);
}

/**
* \brief Write image data from memory array (image_data.h) to the EPD
*
* \param EPD_type_index The defined EPD size
* \param previous_image_ptr The pointer of memory that stores previous image
* \param new_image_ptr The pointer of memory that stores new image
*/
void EPD_display_from_array_prt (uint8_t EPD_type_index, uint8_t *previous_image_ptr,
		uint8_t *new_image_ptr) {	
	_On_EPD_read_flash=0;
	stage_handle(EPD_type_index,new_image_ptr,Stage1,COG_parameters[EPD_type_index].horizontal_size);	
	stage_handle(EPD_type_index,new_image_ptr,Stage2,COG_parameters[EPD_type_index].horizontal_size);	
	stage_handle(EPD_type_index,new_image_ptr,Stage3,COG_parameters[EPD_type_index].horizontal_size);	
}

/**
* \brief Write image data from Flash memory to the EPD
* \note This function is additional added here for developer if the image data
* is stored in Flash.
*
* \param EPD_type_index The defined EPD size
* \param previous_image_flash_address The start address of memory that stores previous image
* \param new_image_flash_address The start address of memory that stores new image
* \param On_EPD_read_flash Developer needs to create an external function to read flash
*/
void EPD_display_from_flash_prt (uint8_t EPD_type_index, long previous_image_flash_address,
    long new_image_flash_address,EPD_read_flash_handler On_EPD_read_flash) {
		
	uint8_t line_len;
	line_len=LINE_SIZE;
	if(line_len==0) line_len=COG_parameters[EPD_type_index].horizontal_size;
		
	_On_EPD_read_flash=On_EPD_read_flash;	
	stage_handle_ex(EPD_type_index,new_image_flash_address,Stage1,line_len);
	stage_handle_ex(EPD_type_index,new_image_flash_address,Stage2,line_len);
	stage_handle_ex(EPD_type_index,new_image_flash_address,Stage3,line_len);	
}


/**
* \brief Write Dummy Line to COG
* \note A line whose all Scan Bytes are 0x00
*
* \param EPD_type_index The defined EPD size
*/
static inline void dummy_line(uint8_t EPD_type_index) {
	uint8_t	i;
	for (i = 0; i < (COG_parameters[EPD_type_index].vertical_size/8); i++) {
		switch(EPD_type_index) {
			case EPD_144:
			COG_Line.line_data_by_size.line_data_for_144.scan[i]=0x00;
			break;
			case EPD_200:
			COG_Line.line_data_by_size.line_data_for_200.scan[i]=0x00;
			break;
			case EPD_270:
			COG_Line.line_data_by_size.line_data_for_270.scan[i]=0x00;
			break;
		}
	}
	/* Set charge pump voltage level reduce voltage shift */
	epd_spi_send_byte (0x04, COG_parameters[EPD_type_index].voltage_level);
	
	/* Sending data */
	epd_spi_send (0x0A, (uint8_t *)&COG_Line.uint8, COG_parameters[EPD_type_index].data_line_size);

	/* Turn on Output Enable */
	epd_spi_send_byte (0x02, 0x07);
}


/**
* \brief Write Border(Input) Dummy Line
* \note Set Border byte 0xFF to write Black and set 0xAA to write White
*
* \param EPD_type_index The defined EPD size
*/
static void border_dummy_line(uint8_t EPD_type_index)
{
	uint16_t	i;
	for (i = 0; i < COG_parameters[EPD_type_index].data_line_size; i++)
	{
		COG_Line.uint8[i] = 0x00;
	}
	
	*data_line_border_byte=BORDER_BYTE_B;
	//Write a Border(B) Dummy Line
	epd_spi_send (0x0a, (uint8_t *)&COG_Line.uint8, COG_parameters[EPD_type_index].data_line_size);
	//Turn on OE
	epd_spi_send_byte (0x02, 0x07);
	
	sys_delay_ms(40);
	
	*data_line_border_byte=BORDER_BYTE_W;
	//Write a Borde(B) Dummy Line
	epd_spi_send (0x0a, (uint8_t *)&COG_Line.uint8, COG_parameters[EPD_type_index].data_line_size);
	//Turn on OE
	epd_spi_send_byte (0x02, 0x07);

	sys_delay_ms(200);
	
	
}


/**
* \brief Power Off COG Driver
* \note For detailed flow and description, please refer to the COG G2 document Section 6.
*
* \param EPD_type_index The defined EPD size
*/
uint8_t EPD_power_off(uint8_t EPD_type_index) {
	uint8_t y;		

	if(EPD_type_index==EPD_144 || EPD_type_index==EPD_200) 	{
		border_dummy_line(EPD_type_index);
		dummy_line(EPD_type_index);
	}

	delay_ms (25);
	if(EPD_type_index==EPD_270)	{
		EPD_border_low();
		delay_ms (200);
		EPD_border_high();
	}

	//Check DC/DC
	if((SPI_R(0x0F,0x00) & 0x40) == 0x00) return ERROR_DC;
	
	//Turn on Latch Reset
	epd_spi_send_byte (0x03, 0x01);
	//Turn off OE
	epd_spi_send_byte (0x02, 0x05);
	//Power off charge pump Vcom
	epd_spi_send_byte (0x05, 0x0E);
	//Power off charge pump neg voltage
	epd_spi_send_byte (0x05, 0x02);
	//Turn off all charge pump 
	epd_spi_send_byte (0x05, 0x00);
	//Turn off OSC
	epd_spi_send_byte (0x07, 0x0D);
	
	epd_spi_send_byte (0x04, 0x83);
	delay_ms(120);
	epd_spi_send_byte (0x04, 0x00);
	
	epd_spi_detach ();
	EPD_cs_low();
	EPD_rst_low();
	EPD_Vcc_turn_off ();
	EPD_border_low();
	delay_ms (10);
		
	for(y=0;y<10;y++)
	{
		EPD_discharge_high ();		
		delay_ms (10);		
		EPD_discharge_low ();	
		delay_ms (10);	
	}
	return RES_OK;
}

#endif

