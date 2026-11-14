/*******************************************************************************
 * Size: 14 px
 * Bpp: 1
 * Opts: --bpp 1 --size 14 --no-compress --stride 1 --align 1 --font OpenSans_SemiCondensed-Bold.ttf --range 32-127 --format lvgl -o open_sans_14b.c
 ******************************************************************************/

#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif



#ifndef OPEN_SANS_14B
#define OPEN_SANS_14B 1
#endif

#if OPEN_SANS_14B

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xfc, 0x30,

    /* U+0022 "\"" */
    0xde, 0xf4,

    /* U+0023 "#" */
    0x34, 0x48, 0x97, 0xf6, 0xcd, 0xbf, 0xa4, 0x58,
    0xb0,

    /* U+0024 "$" */
    0x10, 0xf9, 0xf2, 0x87, 0x7, 0x85, 0x4a, 0xf8,
    0x20, 0x40,

    /* U+0025 "%" */
    0x73, 0x1b, 0x63, 0x68, 0x6f, 0xd, 0xfc, 0xfe,
    0xc3, 0xd8, 0x5b, 0x1b, 0x63, 0x38,

    /* U+0026 "&" */
    0x38, 0x36, 0x1b, 0xd, 0x83, 0x83, 0x9b, 0x6d,
    0x9e, 0xce, 0x3f, 0x80,

    /* U+0027 "'" */
    0xfc,

    /* U+0028 "(" */
    0x36, 0x6c, 0xcc, 0xcc, 0xc6, 0x63,

    /* U+0029 ")" */
    0xc6, 0x63, 0x33, 0x33, 0x36, 0x6c,

    /* U+002A "*" */
    0x10, 0x21, 0xf1, 0xc2, 0x8d, 0x80,

    /* U+002B "+" */
    0x30, 0xc3, 0x3f, 0x30, 0xc3, 0x0,

    /* U+002C "," */
    0x6d, 0x0,

    /* U+002D "-" */
    0xf0,

    /* U+002E "." */
    0xc0,

    /* U+002F "/" */
    0x8, 0x61, 0x84, 0x30, 0xc6, 0x18, 0x43, 0x0,

    /* U+0030 "0" */
    0x79, 0x2c, 0xf3, 0xcf, 0x3c, 0xf3, 0x49, 0xe0,

    /* U+0031 "1" */
    0x19, 0xde, 0xb1, 0x8c, 0x63, 0x18, 0xc0,

    /* U+0032 "2" */
    0x7b, 0x30, 0xc3, 0x1c, 0x63, 0x9c, 0xe3, 0xf0,

    /* U+0033 "3" */
    0xf8, 0x30, 0xc3, 0x70, 0x30, 0xc3, 0x8f, 0xe0,

    /* U+0034 "4" */
    0xc, 0x38, 0x71, 0xe6, 0xcd, 0xb3, 0x7f, 0xc,
    0x18,

    /* U+0035 "5" */
    0x7c, 0xc1, 0x83, 0x7, 0xc1, 0xc1, 0x83, 0x8f,
    0xf8,

    /* U+0036 "6" */
    0x39, 0x8c, 0x3e, 0xcf, 0x3c, 0xf3, 0x4d, 0xe0,

    /* U+0037 "7" */
    0xfc, 0x31, 0x86, 0x18, 0xc3, 0xc, 0x61, 0x80,

    /* U+0038 "8" */
    0x7b, 0x3c, 0xff, 0x71, 0xec, 0xf3, 0xcd, 0xe0,

    /* U+0039 "9" */
    0x7b, 0x2c, 0xf3, 0xcd, 0xf0, 0xc3, 0x19, 0xc0,

    /* U+003A ":" */
    0xc0, 0x3,

    /* U+003B ";" */
    0xc0, 0x3e,

    /* U+003C "<" */
    0x2, 0x1c, 0xe7, 0xf, 0x7, 0x83, 0x80,

    /* U+003D "=" */
    0xfc, 0x0, 0x3f,

    /* U+003E ">" */
    0x81, 0xc1, 0xe0, 0xf1, 0xce, 0x30, 0x0,

    /* U+003F "?" */
    0xf4, 0xc6, 0x33, 0xb9, 0x8c, 0x3, 0x0,

    /* U+0040 "@" */
    0x1f, 0x1c, 0x67, 0xff, 0xef, 0xf3, 0xfc, 0xff,
    0x3f, 0x76, 0x60, 0xf, 0xc0,

    /* U+0041 "A" */
    0x1c, 0xe, 0xf, 0x6, 0xc3, 0x63, 0x31, 0xf8,
    0xc6, 0xc3, 0x61, 0x80,

    /* U+0042 "B" */
    0xfb, 0x3c, 0xf3, 0xfb, 0x3c, 0xf3, 0xcf, 0xe0,

    /* U+0043 "C" */
    0x3e, 0xc3, 0x6, 0xc, 0x18, 0x30, 0x60, 0x62,
    0x7c,

    /* U+0044 "D" */
    0xf9, 0x9b, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xcd,
    0xf0,

    /* U+0045 "E" */
    0xfe, 0x31, 0x8f, 0xe3, 0x18, 0xc7, 0xc0,

    /* U+0046 "F" */
    0xfe, 0x31, 0x8c, 0x7f, 0x18, 0xc6, 0x0,

    /* U+0047 "G" */
    0x3e, 0xc3, 0x6, 0xc, 0xf8, 0xf1, 0xe3, 0x66,
    0x7c,

    /* U+0048 "H" */
    0xc7, 0x8f, 0x1e, 0x3f, 0xf8, 0xf1, 0xe3, 0xc7,
    0x8c,

    /* U+0049 "I" */
    0xff, 0xff, 0xf0,

    /* U+004A "J" */
    0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0xe0,

    /* U+004B "K" */
    0xc7, 0x9b, 0x76, 0xcf, 0x1f, 0x36, 0x66, 0xcd,
    0x8c,

    /* U+004C "L" */
    0xc3, 0xc, 0x30, 0xc3, 0xc, 0x30, 0xc3, 0xf0,

    /* U+004D "M" */
    0xe1, 0xf8, 0x7f, 0x3f, 0xcf, 0xd2, 0xf4, 0xbd,
    0xef, 0x7b, 0xcc, 0xf3, 0x30,

    /* U+004E "N" */
    0xe3, 0xe3, 0xf3, 0xf3, 0xdb, 0xdb, 0xcf, 0xcf,
    0xc7, 0xc7,

    /* U+004F "O" */
    0x3c, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0x66, 0x3c,

    /* U+0050 "P" */
    0xfb, 0x3c, 0xf3, 0xcf, 0xec, 0x30, 0xc3, 0x0,

    /* U+0051 "Q" */
    0x3c, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0x66, 0x3c, 0xe, 0x6, 0x3,

    /* U+0052 "R" */
    0xf9, 0x9b, 0x36, 0x6c, 0xdf, 0x36, 0x6c, 0xcd,
    0x9c,

    /* U+0053 "S" */
    0x7f, 0xc, 0x38, 0xf9, 0xf1, 0xc3, 0x8f, 0xe0,

    /* U+0054 "T" */
    0xfe, 0x60, 0xc1, 0x83, 0x6, 0xc, 0x18, 0x30,
    0x60,

    /* U+0055 "U" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc6,
    0xf8,

    /* U+0056 "V" */
    0xc3, 0xc3, 0x66, 0x66, 0x66, 0x36, 0x3c, 0x3c,
    0x1c, 0x18,

    /* U+0057 "W" */
    0xc6, 0x3c, 0x63, 0x67, 0x36, 0xf6, 0x6f, 0x66,
    0xd6, 0x69, 0x62, 0x9e, 0x39, 0xc3, 0x8c,

    /* U+0058 "X" */
    0xe6, 0x66, 0x3c, 0x3c, 0x18, 0x38, 0x3c, 0x6e,
    0x66, 0xc7,

    /* U+0059 "Y" */
    0xe7, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x18, 0x18,
    0x18, 0x18,

    /* U+005A "Z" */
    0xfc, 0x31, 0x86, 0x30, 0xc6, 0x18, 0xc3, 0xf0,

    /* U+005B "[" */
    0xfc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcf,

    /* U+005C "\\" */
    0xc1, 0x6, 0x18, 0x30, 0xc1, 0x6, 0x18, 0x20,

    /* U+005D "]" */
    0xf3, 0x33, 0x33, 0x33, 0x33, 0x3f,

    /* U+005E "^" */
    0x10, 0x30, 0xe1, 0x66, 0xcc, 0xf1, 0x80,

    /* U+005F "_" */
    0xfc,

    /* U+0060 "`" */
    0xd9, 0x80,

    /* U+0061 "a" */
    0x79, 0x30, 0xdf, 0xcf, 0x3c, 0xdf,

    /* U+0062 "b" */
    0xc3, 0xc, 0x3e, 0xcf, 0x3c, 0xf3, 0xcf, 0x3f,
    0x80,

    /* U+0063 "c" */
    0x3d, 0x8c, 0x30, 0xc3, 0xe, 0x5f,

    /* U+0064 "d" */
    0xc, 0x30, 0xdf, 0xcf, 0x3c, 0xf3, 0xcf, 0x37,
    0xc0,

    /* U+0065 "e" */
    0x78, 0x9b, 0x37, 0xfc, 0x18, 0x19, 0x1e,

    /* U+0066 "f" */
    0x33, 0x19, 0xe6, 0x31, 0x8c, 0x63, 0x18,

    /* U+0067 "g" */
    0x7f, 0x9b, 0x36, 0x67, 0x88, 0x30, 0x3e, 0xc7,
    0x8d, 0xf0,

    /* U+0068 "h" */
    0xc3, 0xc, 0x3e, 0xcf, 0x3c, 0xf3, 0xcf, 0x3c,
    0xc0,

    /* U+0069 "i" */
    0xc3, 0xff, 0xfc,

    /* U+006A "j" */
    0x30, 0x3, 0x33, 0x33, 0x33, 0x33, 0x3e,

    /* U+006B "k" */
    0xc1, 0x83, 0x6, 0x6d, 0xdb, 0x3c, 0x7c, 0xd9,
    0x9b, 0x38,

    /* U+006C "l" */
    0xff, 0xff, 0xfc,

    /* U+006D "m" */
    0xfb, 0xb3, 0x3c, 0xcf, 0x33, 0xcc, 0xf3, 0x3c,
    0xcf, 0x33,

    /* U+006E "n" */
    0xfb, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3,

    /* U+006F "o" */
    0x38, 0xdb, 0x1e, 0x3c, 0x78, 0xdb, 0x1c,

    /* U+0070 "p" */
    0xfb, 0x3c, 0xf3, 0xcf, 0x3c, 0xfe, 0xc3, 0xc,
    0x0,

    /* U+0071 "q" */
    0x7f, 0x3c, 0xf3, 0xcf, 0x3c, 0xdf, 0xc, 0x30,
    0xc0,

    /* U+0072 "r" */
    0xf7, 0x31, 0x8c, 0x63, 0x18,

    /* U+0073 "s" */
    0x7e, 0x39, 0xe7, 0x8c, 0x7e,

    /* U+0074 "t" */
    0x23, 0x3e, 0xc6, 0x31, 0x8c, 0x61, 0xc0,

    /* U+0075 "u" */
    0xcf, 0x3c, 0xf3, 0xcf, 0x3c, 0xdf,

    /* U+0076 "v" */
    0xc7, 0x8d, 0xb3, 0x66, 0xc5, 0xe, 0x1c,

    /* U+0077 "w" */
    0xce, 0x79, 0xd9, 0xab, 0x35, 0x67, 0xac, 0xf7,
    0xc, 0xe1, 0x9c,

    /* U+0078 "x" */
    0xee, 0xd8, 0xf1, 0xc3, 0x8d, 0x9b, 0x73,

    /* U+0079 "y" */
    0xcd, 0x9b, 0x33, 0x47, 0x8f, 0xc, 0x18, 0x30,
    0x43, 0x80,

    /* U+007A "z" */
    0xf8, 0xcc, 0x66, 0x33, 0x1f,

    /* U+007B "{" */
    0x19, 0x8c, 0x63, 0x60, 0xc6, 0x31, 0x8c, 0x30,

    /* U+007C "|" */
    0xff, 0xff, 0xff, 0xf0,

    /* U+007D "}" */
    0xc3, 0x18, 0xc6, 0xd, 0x8c, 0x63, 0x19, 0x80,

    /* U+007E "~" */
    0xe0, 0x70
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 49, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 61, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 102, .box_w = 5, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 6, .adv_w = 130, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 15, .adv_w = 117, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 25, .adv_w = 187, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 39, .adv_w = 149, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 51, .adv_w = 56, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 52, .adv_w = 73, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 58, .adv_w = 73, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 64, .adv_w = 111, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 70, .adv_w = 117, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 76, .adv_w = 60, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 78, .adv_w = 70, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 79, .adv_w = 60, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 80, .adv_w = 92, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 88, .adv_w = 117, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 96, .adv_w = 117, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 103, .adv_w = 117, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 111, .adv_w = 117, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 119, .adv_w = 117, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 128, .adv_w = 117, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 137, .adv_w = 117, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 145, .adv_w = 117, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 153, .adv_w = 117, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 161, .adv_w = 117, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 169, .adv_w = 61, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 171, .adv_w = 61, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 173, .adv_w = 117, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 180, .adv_w = 117, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 183, .adv_w = 117, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 190, .adv_w = 95, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 197, .adv_w = 181, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 210, .adv_w = 136, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 222, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 230, .adv_w = 125, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 239, .adv_w = 146, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 248, .adv_w = 111, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 255, .adv_w = 108, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 262, .adv_w = 145, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 271, .adv_w = 151, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 280, .adv_w = 67, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 283, .adv_w = 67, .box_w = 4, .box_h = 13, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 290, .adv_w = 132, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 299, .adv_w = 109, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 307, .adv_w = 192, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 320, .adv_w = 161, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 330, .adv_w = 156, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 340, .adv_w = 125, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 348, .adv_w = 156, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 361, .adv_w = 131, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 370, .adv_w = 111, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 378, .adv_w = 113, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 387, .adv_w = 148, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 396, .adv_w = 130, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 406, .adv_w = 195, .box_w = 12, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 421, .adv_w = 128, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 431, .adv_w = 123, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 441, .adv_w = 113, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 449, .adv_w = 71, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 455, .adv_w = 92, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 463, .adv_w = 71, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 469, .adv_w = 120, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 476, .adv_w = 99, .box_w = 6, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 477, .adv_w = 75, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 479, .adv_w = 120, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 485, .adv_w = 127, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 494, .adv_w = 102, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 500, .adv_w = 127, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 509, .adv_w = 117, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 516, .adv_w = 77, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 523, .adv_w = 115, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 533, .adv_w = 130, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 542, .adv_w = 62, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 545, .adv_w = 62, .box_w = 4, .box_h = 14, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 552, .adv_w = 123, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 562, .adv_w = 61, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 565, .adv_w = 194, .box_w = 10, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 575, .adv_w = 130, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 581, .adv_w = 124, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 588, .adv_w = 127, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 597, .adv_w = 127, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 606, .adv_w = 90, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 611, .adv_w = 98, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 616, .adv_w = 84, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 623, .adv_w = 130, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 629, .adv_w = 113, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 636, .adv_w = 173, .box_w = 11, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 647, .adv_w = 114, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 654, .adv_w = 113, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 664, .adv_w = 95, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 669, .adv_w = 85, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 677, .adv_w = 108, .box_w = 2, .box_h = 14, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 681, .adv_w = 85, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 689, .adv_w = 117, .box_w = 6, .box_h = 2, .ofs_x = 1, .ofs_y = 4}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif

};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t open_sans_14b = {
#else
lv_font_t open_sans_14b = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 15,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 0,
#endif
    .static_bitmap = 0,
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if OPEN_SANS_14B*/
