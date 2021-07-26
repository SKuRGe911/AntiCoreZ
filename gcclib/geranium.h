#ifndef __GERANIUM_H__
#define __GERANIUM_H__

//////////////////////////////////////////////////////////////////////////
// GENERAL TYPES														//
//////////////////////////////////////////////////////////////////////////

// This type MUST be 8 bit
typedef unsigned char	BYTE __attribute__((aligned(1)));

// These types MUST be 16 bit
typedef short			SHORT __attribute__((aligned(1)));
typedef unsigned short	WORD __attribute__((aligned(1)));
typedef unsigned short	WCHAR __attribute__((aligned(1)));

// These types MUST be 16 bit or 32 bit
typedef int				INT __attribute__((aligned(1)));
typedef unsigned int	UINT __attribute__((aligned(1)));

// These types MUST be 32 bit
typedef long			LONG __attribute__((aligned(1)));
typedef unsigned long	DWORD __attribute__((aligned(1)));

typedef	float					vec2[2];
typedef	float					vec3[3];
typedef	int						ivec3[3];
typedef	float					vec4[4];
typedef	vec4					versor;
typedef	vec3					mat3[3];
typedef	vec2					mat2[2];
typedef	vec4					mat4[4];
typedef char                    col4[4];

typedef union col4s {
    col4 raw;
    struct {
        char r;
        char g;
        char b;
        char a;
    };
} col4s;

typedef union vec2s {
    vec2 raw;
    struct {
        float x;
        float y;
    };
} vec2s;

typedef union ivec2s {
    vec2 raw;
    struct {
        int x;
        int y;
    };
} ivec2s;

typedef union vec3s {
    vec3 raw;
    struct {
        float x;
        float y;
        float z;
    };
} vec3s;

typedef union ivec3s {
    ivec3 raw;
    struct {
        int x;
        int y;
        int z;
    };
} ivec3s;

typedef union vec4s {
    vec4 raw;
    struct {
        float x;
        float y;
        float z;
        float w;
    };
} vec4s;

typedef union versors {
    vec4 raw;
    struct {
        float x;
        float y;
        float z;
        float w;
    };

    struct {
        vec3s imag;
        float real;
    };
} versors;

typedef union mat2s {
    mat2  raw;
    vec2s col[2];
    struct {
        float m00, m01;
        float m10, m11;
    };
} mat2s;

typedef union mat3s {
    mat3  raw;
    vec3s col[3];
    struct {
        float m00, m01, m02;
        float m10, m11, m12;
        float m20, m21, m22;
    };
} mat3s;

typedef union mat4s {
    mat4  raw;
    vec4s col[4];
    struct {
        float m00, m01, m02, m03;
        float m10, m11, m12, m13;
        float m20, m21, m22, m23;
        float m30, m31, m32, m33;
    };
} mat4s;

//////////////////////////////////////////////////////////////////////////
// GENERAL INCLUDES														//
//////////////////////////////////////////////////////////////////////////

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <math.h>

//////////////////////////////////////////////////////////////////////////
// GENERAL STUFF														//
//////////////////////////////////////////////////////////////////////////

#define GERANIUM_OTHER_ADDRESS						0xC0000000
#define GERANIUM_IO_ADDRESS							0x80000000
#define GERANIUM_SDRAM_ADDRESS						0x40000000
#define GERANIUM_DDRAM_ADDRESS						0x00000000

//////////////////////////////////////////////////////////////////////////
// CONSOLE STUFF														//
//////////////////////////////////////////////////////////////////////////

#define CONSOLE_X_TOTAL								32
#define CONSOLE_Y_TOTAL								30
#define CONSOLE_COMMAND_BUFFER_LENGTH				1024
#define OUTPUT_CONSOLE_STRING(a)					output_console_string(a); next_line_console()

//////////////////////////////////////////////////////////////////////////
// SYSTEM MANAGEMENT STUFF												//
//////////////////////////////////////////////////////////////////////////

void flush_hi_data_cache(void);
void flush_lo_data_cache(void);
void* sdram_malloc(size_t sz);
void* sdram_memalign(size_t align, size_t sz);
bool sdram_free(void* addr);
void set_led(bool a, bool b, bool c);
void set_debug_pause(bool pause);
bool get_debug_video(void);
void set_debug_video(bool on);
void set_loading_screen_on(bool on);
bool get_loading_screen_on(void);

//////////////////////////////////////////////////////////////////////////
// CONSOLE STUFF														//
//////////////////////////////////////////////////////////////////////////

void output_console_string(char* s);
bool get_console_on(void);
void set_console_on(bool o);
void set_console_id(uint32_t id);
void output_console_formatted_string(char* str, ...);
void display_hex_dword(uint32_t dw);
void next_line_console(void);
extern char* command_buf;
#define OUTPUT_CONSOLE_STRING(a)					output_console_string(a); next_line_console()

//////////////////////////////////////////////////////////////////////////
// FILE SYSTEM STUFF													//
//////////////////////////////////////////////////////////////////////////

bool load_file_system(void);
bool open_dir(char* filedir);
void dir_to_screen(void);
bool load_file(char* filename);
uint32_t* get_file_ptr(void);
uint32_t get_file_size(void);
void free_file(void);

//////////////////////////////////////////////////////////////////////////
// VIDEO STUFF															//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
#define GERANIUM_VIDEO_DMA_LEVEL_MODE_A						0
#define GERANIUM_VIDEO_DMA_LEVEL_MODE_B_PLANE_0				1
#define GERANIUM_VIDEO_DMA_LEVEL_MODE_B_PLANE_1				2
#define GERANIUM_VIDEO_DMA_LEVEL_MODE_B_PLANE_2				3
#define GERANIUM_VIDEO_DMA_LEVEL_MODE_B_PLANE_3				4
#define GERANIUM_VIDEO_DMA_LEVEL_MODE_B_PLANE_4				5
#define GERANIUM_VIDEO_DMA_LEVEL_MODE_B_PLANE_5				6
#define GERANIUM_VIDEO_DMA_LEVEL_MODE_B_PLANE_6				7
#define GERANIUM_VIDEO_DMA_LEVEL_MODE_B_PLANE_7				8
#define GERANIUM_VIDEO_DMA_LEVEL_MODE_B_PLANE_2ND_0			9
#define GERANIUM_VIDEO_DMA_LEVEL_MODE_B_PLANE_2ND_1			10
#define GERANIUM_VIDEO_DMA_LEVEL_MODE_B_PLANE_2ND_2			11
#define GERANIUM_VIDEO_DMA_LEVEL_MODE_B_PLANE_2ND_3			12
#define GERANIUM_VIDEO_DMA_LEVEL_MODE_B_PLANE_2ND_4			13
#define GERANIUM_VIDEO_DMA_LEVEL_MODE_B_PLANE_2ND_5			14
#define GERANIUM_VIDEO_DMA_LEVEL_MODE_B_PLANE_2ND_6			15
#define GERANIUM_VIDEO_DMA_LEVEL_MODE_B_PLANE_2ND_7			16
#define GERANIUM_VIDEO_DMA_LEVEL_SPRITE_0					17
#define GERANIUM_VIDEO_DMA_LEVEL_SPRITE_1					18
#define GERANIUM_VIDEO_DMA_LEVEL_SPRITE_2					19
#define GERANIUM_VIDEO_DMA_LEVEL_SPRITE_3					20
#define GERANIUM_VIDEO_DMA_LEVEL_SPRITE_4					21
#define GERANIUM_VIDEO_DMA_LEVEL_SPRITE_5					22
#define GERANIUM_VIDEO_DMA_LEVEL_SPRITE_6					23
#define GERANIUM_VIDEO_DMA_LEVEL_SPRITE_7					24
#define GERANIUM_VIDEO_DMA_LEVEL_SPRITE_8					25
#define GERANIUM_VIDEO_DMA_LEVEL_SPRITE_9					26
#define GERANIUM_VIDEO_DMA_LEVEL_SPRITE_10					27
#define GERANIUM_VIDEO_DMA_LEVEL_SPRITE_11					28
#define GERANIUM_VIDEO_DMA_LEVEL_SPRITE_12					29
#define GERANIUM_VIDEO_DMA_LEVEL_SPRITE_13					30
#define GERANIUM_VIDEO_DMA_LEVEL_SPRITE_14					31
#define GERANIUM_VIDEO_DMA_LEVEL_SPRITE_15					32
#define GERANIUM_VIDEO_DMA_LEVEL_SPRITE_16					33
#define GERANIUM_VIDEO_DMA_LEVEL_SPRITE_17					34
#define GERANIUM_VIDEO_DMA_LEVEL_SPRITE_18					35
#define GERANIUM_VIDEO_DMA_LEVEL_SPRITE_19					36
#define GERANIUM_VIDEO_DMA_LEVEL_SPRITE_20					37
#define GERANIUM_VIDEO_DMA_LEVEL_SPRITE_21					38
#define GERANIUM_VIDEO_DMA_LEVEL_SPRITE_22					39
#define GERANIUM_VIDEO_DMA_LEVEL_SPRITE_23					40
#define GERANIUM_VIDEO_DMA_LEVEL_SPRITE_24					41
#define GERANIUM_VIDEO_DMA_LEVEL_SPRITE_25					42
//////////////////////////////////////////////////////////////////////////
#define VIDEO_DMA_LEVEL_0									0
#define VIDEO_DMA_LEVEL_1									1
#define VIDEO_DMA_LEVEL_2									2
#define VIDEO_DMA_LEVEL_3									3
#define VIDEO_DMA_LEVEL_4									4
#define VIDEO_DMA_LEVEL_5									5
#define VIDEO_DMA_LEVEL_6									6
#define VIDEO_DMA_LEVEL_7									7
#define VIDEO_DMA_LEVEL_8									8
#define VIDEO_DMA_LEVEL_9									9
#define VIDEO_DMA_LEVEL_10									10
#define VIDEO_DMA_LEVEL_11									11
#define VIDEO_DMA_LEVEL_12									12
#define VIDEO_DMA_LEVEL_13									13
#define VIDEO_DMA_LEVEL_14									14
#define VIDEO_DMA_LEVEL_15									15
#define VIDEO_DMA_LEVEL_16									16
#define VIDEO_DMA_LEVEL_17									17
#define VIDEO_DMA_LEVEL_18									18
#define VIDEO_DMA_LEVEL_19									19
#define VIDEO_DMA_LEVEL_20									20
#define VIDEO_DMA_LEVEL_21									21
#define VIDEO_DMA_LEVEL_22									22
#define VIDEO_DMA_LEVEL_23									23
#define VIDEO_DMA_LEVEL_24									24
#define VIDEO_DMA_LEVEL_25									25
#define VIDEO_DMA_LEVEL_26									26
#define VIDEO_DMA_LEVEL_27									27
#define VIDEO_DMA_LEVEL_28									28
#define VIDEO_DMA_LEVEL_29									29
#define VIDEO_DMA_LEVEL_30									30
#define VIDEO_DMA_LEVEL_31									31
#define VIDEO_DMA_LEVEL_MASK								0x01F
//////////////////////////////////////////////////////////////////////////
#define VIDEO_MODE_0										0
#define VIDEO_MODE_1										1
#define VIDEO_MODE_LOADSCREEN								4
//////////////////////////////////////////////////////////////////////////
#define VIDEO_MODE_0_WIDTH									256
#define VIDEO_MODE_0_HEIGHT									240
//////////////////////////////////////////////////////////////////////////
#define VIDEO_MODE_1_PLANAR_BUFFER_SIZE_32BIT				(((VIDEO_MODE_0_WIDTH/16)*VIDEO_MODE_0_HEIGHT)/2)
#define VIDEO_MODE_1_PLANAR_SIZE_32BIT						(((VIDEO_MODE_0_WIDTH/16)*VIDEO_MODE_0_HEIGHT)/2)
//////////////////////////////////////////////////////////////////////////
#define SPRITE_MODE_RGBA									(0x00)
#define SPRITE_MODE_GRAB									(0x01)
#define SPRITE_MODE_BARG									(0x02)
#define SPRITE_MODE_ABGR									(0x03)
//////////////////////////////////////////////////////////////////////////
bool video_caps_console(void);
bool video_caps_mode_a(void);
bool video_caps_mode_b(void);
bool video_caps_loadscreen(void);
bool video_caps_sprites(void);
bool video_caps_line_colors(void);
bool video_caps_static_colors(void);
uint32_t video_caps_sprite_total(void);
bool video_caps_sprite_alpha(void);
uint32_t video_caps_line_color_total(void);
//////////////////////////////////////////////////////////////////////////
void set_video_dma_priority_level(uint32_t id, uint32_t level);
uint32_t get_video_dma_priority_level(uint32_t id);
void set_video_mode(uint32_t mode);
uint32_t get_video_mode(void);
void set_video_buffer_auto_swap(bool on);
bool get_video_buffer_auto_swap(void);
void set_video_buffer_swap_ready(void);
bool get_video_buffer_swap_ready(void);
bool get_video_current_buffer(void);
void video_swap_buffer_now(void);
void video_set_empty_bits_hilo(bool hi);
bool video_get_empty_bits_hilo(void);
void set_default_dma_priority_for_video(void);
void set_sprite_default_dma_priority(void);
void set_secondary_planes_on(bool on);
bool get_secondary_planes_on(void);
void set_secondary_plane_mod_color(uint32_t color);
uint32_t get_secondary_plane_mod_color(void);
//////////////////////////////////////////////////////////////////////////
void set_video_mode_0_buffer_addr(uint32_t addr, bool buf);
uint32_t get_video_mode_0_buffer_addr(bool buf);
//////////////////////////////////////////////////////////////////////////
void set_mode_1_color(uint32_t color, uint32_t id, bool primary_secondary);
uint32_t get_current_plane_addr(uint32_t plane);
uint32_t get_video_mode_1_plane_count(bool primary_secondary);
void set_video_mode_1_plane_count(uint32_t planes, bool primary_secondary);
uint32_t get_video_mode_1_buffer_position(uint32_t plane, bool buf);
void set_video_mode_1_buffer_position(uint32_t pos, uint32_t plane, bool buf);
uint32_t get_video_mode_1_buffer_length(uint32_t plane, bool buf);
void set_video_mode_1_buffer_length(uint32_t len, uint32_t plane, bool buf);
uint32_t get_video_mode_1_buffer_addr(uint32_t plane, bool buf);
void set_video_mode_1_buffer_addr(void* addr, uint32_t plane, bool buf);
//////////////////////////////////////////////////////////////////////////
void set_sprite_active(uint32_t s, bool on);
bool get_sprite_active(uint32_t s);
void set_sprite_size(uint32_t s, uint32_t szx, uint32_t szy);
uint32_t get_sprite_hor_size(uint32_t s);
uint32_t get_sprite_ver_size(uint32_t s);
void set_sprite_addr(uint32_t s, uint32_t addr);
uint32_t get_sprite_addr(uint32_t s);
void set_sprite_offset(uint32_t s, uint32_t os);
uint32_t get_sprite_offset(uint32_t s);
void set_sprite_mode(uint32_t s, uint32_t mode);
uint32_t get_sprite_mode(uint32_t s);
void set_sprite_hor_pos(uint32_t s, int32_t pos);
int32_t get_sprite_hor_pos(uint32_t s);
void set_sprite_ver_pos(uint32_t s, int32_t pos);
int32_t get_sprite_ver_pos(uint32_t s);
//////////////////////////////////////////////////////////////////////////
void line_colors_on_set(bool color0, bool color1, bool color2, bool color3);		// SET LINE COLOR BANKS ON OR OFF
void line_color_set(uint32_t color);												// SET LINE COLOR FOR FOLLOWING FUNCTIONS
void line_color_line_set(uint32_t bank, uint32_t vpos);								// SET THE COLOR BANK AND VPOS FOR PREVIOUS FUNCTION COLOR
void line_set_color_out(void);														// SET THE COLOR TO MODIFYS OUTPUT COLOR
void line_set_color(void);															// SET THE COLOR TO MODIFY
void line_set_bandwidth(void);														// SET THE VARIANCE LIMIT FOR THE COLOR MODIFY
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// AUDIO STUFF															//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
bool initialize_audio_mod(char* name);
void start_audio_cpu(void);
void stop_audio_cpu(void);
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// RASTERIZER STUFF														//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
void set_rasterizer_dma_priority_level(uint32_t id, uint32_t level);
uint32_t get_rasterizer_dma_priority_level(uint32_t id);
void set_default_dma_priority_for_rasterizer(void);
void set_rasterizer_addr(uint32_t addr);
void set_rasterizer_data_length(uint32_t len);
void set_rasterizer_output_addr(uint32_t addr);
void set_rasterizer_zbuffer_addr(uint32_t addr);
void clear_rasterizer_zbuffer(void);
void start_rasterizer(void);
void stop_rasterizer(void);
bool is_rasterizer_busy(void);
//////////////////////////////////////////////////////////////////////////
uint32_t* build_raster_operations_draw_tri_texture(uint32_t* start_addr, uint32_t* size_out, vec3s* vectors, ivec2s* texture_coords, uint32_t count, bool use_z_buffer, uint32_t texture);
uint32_t* build_raster_operations_draw_tri_colors(uint32_t* start_addr, uint32_t* size_out, vec3s* vectors, col4s* colors, uint32_t count, bool use_z_buffer);
uint32_t* build_raster_operations_z_buffer_set(uint32_t* start_addr, uint32_t* size_out, uint32_t* zbuffer_addr);
uint32_t* build_raster_operations_z_buffer_set_and_clear(uint32_t* start_addr, uint32_t* size_out, uint32_t* zbuffer_addr);
uint32_t* build_raster_operations_clear(uint32_t* start_addr, uint32_t* size_out, uint32_t clear_addr, uint32_t x_size, uint32_t y_size, uint32_t x_pos, uint32_t y_pos, uint32_t x_length, uint32_t y_length, uint32_t clear_color);
uint32_t* build_raster_operations_blitt_chunky(uint32_t* start_addr, uint32_t* size_out, uint32_t src_addr, uint32_t dst_addr, uint32_t src_x_total_len, uint32_t src_y_total_len, uint32_t x_pos, uint32_t y_pos, uint32_t x_start, uint32_t y_start, uint32_t x_length, uint32_t y_length, uint32_t clear_color, uint32_t dst_length_x, uint32_t dst_length_y, uint32_t dst_start_x, uint32_t dst_start_y, bool use_clear_color);
uint32_t* build_raster_operations_load_texture(uint32_t* start_addr, uint32_t* size_out, uint32_t* addr, uint32_t sz, uint32_t xy_len, uint32_t id);
//////////////////////////////////////////////////////////////////////////
uint32_t z_buffer_malloc(size_t sz);
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// ENTRY POINT															//
//////////////////////////////////////////////////////////////////////////

int main(void);

#endif//__GERANIUM_H__