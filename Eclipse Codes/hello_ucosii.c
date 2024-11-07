#include <io.h>
#include "system.h"
#include "altera_avalon_timer_regs.h"
#include "altera_avalon_timer.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_irq.h"
#include "sys/alt_stdio.h"
#include "alt_types.h"
#include <stdio.h>
#include "includes.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Altera_UP_SD_Card_Avalon_Interface.h"
#include "altera_up_avalon_video_dma_controller.h"
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "sys/alt_stdio.h"

#define MAX_SUBDIRECTORIES 20

void displayVGA(char fn[]);
void VGA_box (int,int,int,int,int);


void delay(int ms){

	int i;
	for (i=ms;i>0;i--)
	{}

}

void draw_ECE_178(alt_up_pixel_buffer_dma_dev *pixel_buffer_dev )
{	delay(500000);
	int background_color = 0x001F;  // Blue in a 16-bit color format
	 alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev, 0, 0, 639, 479, background_color, 0);

	alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev, 10, 10, 20, 88, 0xffff, 0x001F);
	    alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev, 10, 10, 60, 20, 0xffff, 0x001F);
	    alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev, 10, 50, 50, 60, 0xffff, 0x001F);
	    alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev, 10, 80, 60, 88, 0xffff, 0x001F);

	    // Draw "C"
	    alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev, 70, 10, 80, 88, 0xffff, 0x001F);
    alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev, 80, 10, 100, 20, 0xffff, 0x001F);
	    alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev, 80, 80, 100, 88, 0xffff, 0x001F);

	    // Draw "E"
	   alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev, 110, 10, 120, 88, 0xffff, 0x001F);
	    alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev, 110, 10, 160, 20, 0xffff, 0x001F);
	    alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev, 110, 50, 150, 60, 0xffff, 0x001F);
	    alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev, 110, 80, 160, 88, 0xffff, 0x001F);

	    // Draw "178"
	    alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev, 170, 110, 180, 188, 0xffff, 0x001F);  // 1



	    alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev, 210, 110, 220, 188, 0xffff, 0x001F);  // 7
	    alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev, 190, 110, 220, 120, 0xffff, 0x001F);

	    alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev, 230, 110, 270, 120, 0xffff, 0x001F);  // 8
	    alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev, 230, 110, 240, 188, 0xffff, 0x001F);
	    alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev, 260, 110, 270, 188, 0xffff, 0x001F);
	    alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev, 230, 145, 270, 155, 0xffff, 0x001F);
	    alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev, 230, 180, 270, 188, 0xffff, 0x001F);


}

void VGA_box (int x1, int y1, int x2, int y2, int pixel_color){
int offset, row, column;
volatile short * pixel_buffer = (short *) SRAM_BASE;//VGA pixel buffer address
for (row = y1-1; row <= y2-1; row++)
{
column = x1;
while (column <= x2)
{
offset = (row << 9) + column;
//Computer halfword address, set pixel
*(pixel_buffer + offset) = pixel_color;
++column;
}// END of WHILE-LOOP
}// END of FOR-LOOP
}// END of VGA_box



void displayVGA(char fn[]){
int i,j;
int offset, row, column;
	short int handler;
short att3 = 0, att2 = 0, att1 = 0;
int pixel;
short int *pixel_buffer = (short int *)SRAM_BASE; // VGA pixel buffer address

if (strcmp(fn,"blank")==0){
//Clear 640X480 screen
	printf("Screen cleared \n");
VGA_box (0,0,639,479,0xFFFF);
} else {
//Read Image from SD-Card
handler = alt_up_sd_card_fopen(fn, false);
//Skip Header
for (j = 0; j < 54; j++){
att1 = alt_up_sd_card_read(handler);
}
for (i = 240; i >= 0; i = i-1){
for (j = 0; j < 320; j++){
//Read each byte
att1 = (unsigned char)alt_up_sd_card_read(handler);
att2 = (unsigned char)alt_up_sd_card_read(handler);
att3 = (unsigned char)alt_up_sd_card_read(handler);
//24bit to 16-bit conversion
pixel = ((att3>>3)<<11) | ((att2>>2)<< 5) | (att1>>3);
for (row = i-1; row <= i-1; row++)
{
column = j;
while (column <= j)
{
offset = (row << 9) + column;
//Computer halfword address, set pixel
*(pixel_buffer + offset) = pixel;
++column;
}// END of WHILE-LOOP
}// END of FOR-LOOP
//pixel_buffer[i * 320 + j] = pixel;
//VGA_box (j, i, j, i, pixel);
}
}
alt_up_sd_card_fclose(handler);
}
}//END of displayVGA()

int main(void)
{int delaytime;
char ch;

alt_up_pixel_buffer_dma_dev *pixel_buffer_dev;
//	alt_up_video_dma_dev *char_dma_dev;


	pixel_buffer_dev = alt_up_pixel_buffer_dma_open_dev ("/dev/VGA_Subsystem_VGA_Pixel_DMA");
if ( pixel_buffer_dev == NULL)
	alt_printf ("Error: could not open VGA pixel buffer device\n");
else
	alt_printf ("BufferOpen \n");

/* clear the graphics screen */
alt_up_pixel_buffer_dma_clear_screen(pixel_buffer_dev, 0);

delay(3000000);
	draw_ECE_178 (pixel_buffer_dev);
delay(900000);

alt_up_sd_card_dev * sd_card;
				sd_card = alt_up_sd_card_open_dev("/dev/SD_Card");
	//Local Variables
	int connected = 0;
	//Enable SD-Card Interface
	//If SD-Card Interface is enabled successfully
	if (sd_card != NULL){
	//If SD-Card is present on the DE2-115 Board
	if ((connected == 0) && (alt_up_sd_card_is_Present())){
	printf("Card Connected! \n ");
	//Check FAT16 File System
	if (alt_up_sd_card_is_FAT16()){
	printf("FAT16 File System Detected \n ");
	// Initialize the Start Menu
		displayVGA("\SMILE.BMP");
		delay(1000);
		displayVGA("\LOADING.BMP");
		delay(1000);
		displayVGA("\GAMEOVER.BMP");
		delay(1000);
		displayVGA("\SCORE.BMP");
		delay(1000000);
		displayVGA("blank");

	}}}

  return 0;
}
