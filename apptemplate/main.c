//////////////////////////////////////////////////////////////////////////
#pragma GCC push_options
#pragma GCC optimize ("align-functions=16")
//////////////////////////////////////////////////////////////////////////
#include "../geranium.h"
//////////////////////////////////////////////////////////////////////////
void put_pixel_mode_0(uint32_t addrstart, uint32_t x, uint32_t y, uint16_t color) {
	*(((uint16_t*)(addrstart))+((y* VIDEO_MODE_0_WIDTH*1)+(x*1)))=color;
}
//////////////////////////////////////////////////////////////////////////
void draw_line_mode_0(uint32_t addrstart, int32_t x, int32_t y, int32_t x2, int32_t y2, uint16_t color) {
	int32_t longest, shortest, numerator, i;
	int32_t dx1 = (x < x2) ? 1 : -1;
	int32_t dy1 = (y < y2) ? 1 : -1;
	int32_t dx2, dy2;

	longest = abs(x2 - x);
	shortest = abs(y2 - y);
	if (longest < shortest) {
		longest = abs(y2 - y);
		shortest = abs(x2 - x);
		dx2 = 0;
		dy2 = dy1;
	}
	else {
		dx2 = dx1;
		dy2 = 0;
	}

	numerator = longest / 2;
	for (i = 0; i <= longest; i++) {
		put_pixel_mode_0(addrstart, x, y, color);
		if (numerator >= longest - shortest) {
			numerator += shortest;
			numerator -= longest;
			x += dx1;
			y += dy1;
		}
		else {
			numerator += shortest;
			x += dx2;
			y += dy2;
		}
	}
}
//////////////////////////////////////////////////////////////////////////
int main(void)
{
	OUTPUT_CONSOLE_STRING("APP TEMPLATE");
	set_led(true, true, true);
	set_console_on(false);
	set_default_dma_priority_for_video();
	set_sprite_default_dma_priority();
	set_default_dma_priority_for_rasterizer();
	set_debug_video(false);
	set_loading_screen_on(true);

	if(load_file_system()==false){

	}

	set_loading_screen_on(false);
	set_video_mode(VIDEO_MODE_0);

	//////////////////////////////////////////////////////////////////////////
	uint32_t* screen_buf_a = (uint32_t*)sdram_malloc(VIDEO_MODE_0_WIDTH * VIDEO_MODE_0_HEIGHT * sizeof(uint16_t));
	if (screen_buf_a == 0) {
		return 0;
	}
	memset(screen_buf_a, 0, VIDEO_MODE_0_WIDTH * VIDEO_MODE_0_HEIGHT * sizeof(uint16_t));
	//////////////////////////////////////////////////////////////////////////
	uint32_t* screen_buf_b = (uint32_t*)sdram_malloc(VIDEO_MODE_0_WIDTH * VIDEO_MODE_0_HEIGHT * sizeof(uint16_t));
	if (screen_buf_b == 0) {
		return 0;
	}
	memset(screen_buf_b, 0, VIDEO_MODE_0_WIDTH * VIDEO_MODE_0_HEIGHT * sizeof(uint16_t));
	//////////////////////////////////////////////////////////////////////////
	set_video_mode_0_buffer_addr((uint32_t)screen_buf_a, false);
	set_video_mode_0_buffer_addr((uint32_t)screen_buf_b, true);
	//////////////////////////////////////////////////////////////////////////
	set_video_buffer_auto_swap(true);
	//////////////////////////////////////////////////////////////////////////
	uint32_t ax=0, ay=0, bx=255, by=239;
	while (1)
	{
		ax = ax + 1;
		if(ax==255){
			ax = 0;
		}
		ay = ay + 1;
		if (ay == 239) {
			ay = 0;
		}
		bx = bx - 1;
		if (bx == 0) {
			bx = 255;
		}
		by = by + 1;
		if (by == 0) {
			by = 239;
		}
		draw_line_mode_0((uint32_t)(get_video_current_buffer() == true ? screen_buf_a : screen_buf_b), ax, ay, bx, by, rand());

		set_video_buffer_swap_ready();

		while (get_video_buffer_swap_ready() == true) { 
		
		}
	}
	//////////////////////////////////////////////////////////////////////////
	return 0;
	//////////////////////////////////////////////////////////////////////////

}
//////////////////////////////////////////////////////////////////////////
#pragma GCC pop_options


