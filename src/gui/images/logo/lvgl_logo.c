#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_LVGL_LOGO
#define LV_ATTRIBUTE_IMG_LVGL_LOGO
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_LVGL_LOGO uint8_t lvgl_logo_map[] = {
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 0*/
  0x00, 0x00, 0xda, 0x23, 	/*Color of index 1*/
  0x00, 0x00, 0xd7, 0x4f, 	/*Color of index 2*/
  0x00, 0x00, 0xd7, 0x8d, 	/*Color of index 3*/
  0x00, 0x00, 0xd7, 0xc3, 	/*Color of index 4*/
  0x00, 0x00, 0xd8, 0xfc, 	/*Color of index 5*/
  0x20, 0x1f, 0x1d, 0x41, 	/*Color of index 6*/
  0x20, 0x1f, 0x1d, 0x66, 	/*Color of index 7*/
  0x20, 0x1e, 0x1d, 0xb8, 	/*Color of index 8*/
  0x20, 0x1f, 0x1e, 0xcc, 	/*Color of index 9*/
  0x21, 0x1f, 0x1e, 0xfe, 	/*Color of index 10*/
  0x40, 0x00, 0x00, 0x04, 	/*Color of index 11*/
  0x21, 0x1f, 0x1f, 0x0f, 	/*Color of index 12*/
  0x21, 0x1e, 0x1e, 0x2a, 	/*Color of index 13*/
  0x20, 0x1e, 0x1e, 0x94, 	/*Color of index 14*/
  0x20, 0x1e, 0x1e, 0xeb, 	/*Color of index 15*/

  0x00, 0x6e, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x7d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x0e, 0xfa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaf, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x6a, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x8a, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xa7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xfa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0x9f, 0xaa, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x0d, 0xdd, 0xdc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xdd, 0xdd, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0xdd, 0xdd, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xcd, 0x67, 0x77, 0x77, 0x6d, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xdd, 0xdd, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xfa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0x9d, 0xcd, 0x9a, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xf6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xef, 0xaa, 0x8b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb9, 0xaa, 0xa7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbc, 0x78, 0xfa, 0xaa, 0xaa, 0xaa, 0xaa, 0xfe, 0x6c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaf, 0x70, 0x00, 0xda, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xa6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xdf, 0xaa, 0xa6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6f, 0xaa, 0x9c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xef, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaf, 0xed, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xfa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xd0, 0x00, 0xca, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xf6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xa8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x0c, 0xef, 0xaa, 0xaa, 0xaa, 0xaa, 0xff, 0xaf, 0xaa, 0xaa, 0xaa, 0xaf, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xe0, 0x00, 0x7a, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xa6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xaa, 0xaf, 0xd0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0xaa, 0xaf, 0xd0, 0x00, 0x00, 0x00, 0x00, 0x6f, 0xaa, 0xaa, 0xaa, 0x9e, 0x7d, 0xdd, 0xd6, 0x6e, 0x9a, 0xaa, 0xaa, 0xa8, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xfa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 0x7e, 0xaa, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xf6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x8a, 0xaa, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x07, 0xaa, 0xaa, 0xaf, 0xed, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0d, 0xef, 0xaa, 0xaa, 0x9c, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xa6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7a, 0xaa, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd9, 0xaa, 0xfd, 0x00, 0x00, 0x00, 0x00, 0x7a, 0xaa, 0xaa, 0xec, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0xea, 0xaa, 0x9c, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xfa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xf6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xcf, 0xaa, 0xa7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7a, 0xaa, 0xeb, 0x00, 0x00, 0x00, 0x07, 0xaa, 0xaa, 0xf6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xf9, 0xd0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xfa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xa6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xaa, 0xa9, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0x9a, 0xaa, 0x60, 0x00, 0x00, 0x00, 0xdf, 0xaa, 0xaf, 0xd0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xea, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xf6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0xfa, 0xaa, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xaa, 0xa9, 0x00, 0x00, 0x00, 0x0c, 0x8a, 0xaa, 0xfd, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xc6, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe9, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xa6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc8, 0xaa, 0xa6, 0x00, 0x00, 0x00, 0x07, 0xaa, 0xaa, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0xea, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xf6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xda, 0xaa, 0xa6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xdf, 0xaa, 0x9c, 0x00, 0x00, 0x00, 0xb9, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x11, 0x12, 0x12, 0x12, 0x12, 0x12, 0x11, 0x00, 0x6a, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xa6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xae, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0xe0, 0x00, 0x00, 0x00, 0x6a, 0xaa, 0xfd, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x35, 0x55, 0x55, 0x55, 0x55, 0x55, 0x54, 0x10, 0x6a, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xf6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xfa, 0xaf, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0d, 0xaa, 0xaf, 0xc0, 0x00, 0x00, 0x00, 0x8a, 0xaa, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x20, 0x6a, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xa6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x9a, 0xaa, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x0c, 0xfa, 0xaa, 0xd0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x20, 0x6a, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xf6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7a, 0xaa, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc9, 0xaa, 0xfd, 0x00, 0x00, 0x00, 0x0d, 0xfa, 0xa9, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x20, 0x6a, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xa6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xcf, 0xaa, 0xa7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7a, 0xaa, 0x8c, 0x00, 0x00, 0x00, 0x07, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x20, 0x6a, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xf6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xaa, 0xa8, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x9a, 0xaa, 0x60, 0x00, 0x00, 0x00, 0x07, 0xaa, 0xa7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x20, 0x6a, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xa6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0d, 0xfa, 0xaa, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xaa, 0xa9, 0x00, 0x00, 0x00, 0x00, 0x0e, 0xaa, 0xa7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x20, 0x6a, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xf6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xa7, 0x00, 0x00, 0x00, 0x00, 0x0e, 0xaa, 0xa7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0d, 0xdd, 0xdc, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x20, 0x6a, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xa6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xda, 0xaa, 0xad, 0x00, 0x00, 0x00, 0x00, 0x00, 0xda, 0xaa, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x0e, 0xaa, 0xf7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0xfa, 0xf6, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x20, 0x6a, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xf6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8a, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x0e, 0xaa, 0xa7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xad, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x20, 0x6a, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xa6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xaa, 0xaf, 0xc0, 0x00, 0x00, 0x00, 0x0d, 0xfa, 0xaf, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0xaa, 0xa6, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x20, 0x6a, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xf6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x9a, 0xaa, 0xe0, 0x00, 0x00, 0x00, 0x07, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xaa, 0xa8, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xad, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x20, 0x6a, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xa6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7a, 0xaa, 0x9c, 0x00, 0x00, 0x00, 0xcf, 0xaa, 0xf6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0d, 0xfa, 0xaf, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0xaa, 0xa6, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x20, 0x6f, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xf6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc9, 0xaa, 0xa6, 0x00, 0x00, 0x00, 0x7a, 0xaa, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x9a, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xad, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x35, 0x55, 0x55, 0x55, 0x55, 0x55, 0x54, 0x10, 0xc8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xa6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0xaa, 0xa9, 0x00, 0x00, 0x0c, 0x9a, 0xaa, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0xaa, 0xa6, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x00, 0x0c, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xea, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xf6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0d, 0xfa, 0xaa, 0x60, 0x00, 0x06, 0xaa, 0xa9, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xca, 0xaa, 0xa6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xad, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc9, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xa6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x8c, 0x00, 0x08, 0xaa, 0xa7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0xaa, 0xa9, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0xaa, 0xa6, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x13, 0x33, 0x33, 0x33, 0x33, 0x33, 0x32, 0x10, 0x12, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x10, 0x08, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xf6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xdf, 0xaa, 0xfc, 0x00, 0x6a, 0xaa, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xfa, 0xaa, 0xec, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xad, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x45, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x10, 0x15, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x41, 0x08, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xa6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc8, 0xaa, 0xae, 0x0b, 0xea, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0xa7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0xaa, 0xa6, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x20, 0x25, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x51, 0x08, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xf6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xaa, 0xaf, 0xcc, 0xfa, 0xaf, 0xd0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc8, 0xaa, 0xaa, 0xec, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xad, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x20, 0x25, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x41, 0x08, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xa6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0x9a, 0xaa, 0x77, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0d, 0x9a, 0xaa, 0xae, 0xd0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc8, 0xaa, 0xa6, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x20, 0x25, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x51, 0x08, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xf6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7a, 0xaa, 0xff, 0xaa, 0xa6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd9, 0xaa, 0xaa, 0xf7, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc6, 0xfa, 0xaa, 0xad, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x20, 0x25, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x41, 0x08, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xa6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xcf, 0xaa, 0xaa, 0xaa, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0d, 0x9a, 0xaa, 0xaa, 0xfe, 0x6c, 0x00, 0x00, 0x00, 0x0c, 0xde, 0x9a, 0xaa, 0xaa, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x20, 0x25, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x51, 0x08, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xa9, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x98, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0xaa, 0xaa, 0xaa, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xce, 0xfa, 0xaa, 0xaa, 0xaf, 0x9e, 0xe7, 0xee, 0x9f, 0xaa, 0xaa, 0xaa, 0xfe, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x97, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x20, 0x25, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x41, 0x08, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x08, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0d, 0xfa, 0xaa, 0xa9, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x68, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xa8, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x20, 0x25, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x51, 0x08, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x09, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0xa7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x68, 0x9a, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0x9e, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x20, 0x25, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x41, 0x08, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd8, 0x88, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0xdd, 0xe8, 0xfa, 0xfa, 0xfa, 0x98, 0x7d, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x87, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x20, 0x25, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x51, 0x08, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xae, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xcc, 0xcd, 0xcc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x20, 0x25, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x41, 0x08, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xa7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x20, 0x25, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x51, 0x08, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x20, 0x25, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x41, 0x0e, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaf, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x24, 0x44, 0x44, 0x44, 0x44, 0x44, 0x43, 0x10, 0x13, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x21, 0x0c, 0xe8, 0x98, 0x98, 0x98, 0x98, 0x7d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const lv_img_dsc_t lvgl_logo = {
  .header.cf = LV_IMG_CF_INDEXED_4BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 190,
  .header.h = 48,
  .data_size = 4624,
  .data = lvgl_logo_map,
};
