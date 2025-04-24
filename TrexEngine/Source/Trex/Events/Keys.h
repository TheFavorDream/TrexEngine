#pragma once

/*

	written by: Pouya Alizadeh (Voltage)
	E-mail: poyavoltage148@gmail.com


	Purpose:
	This file contains all key values as macro defines.
*/



//Key States 
enum KeyState { KEY_NONE = -1, KEY_RELEASE, KEY_PRESS, KEY_HOLD };

enum ButtonState { MS_RELEASE, MS_PRESS};
#define KEY_INVALID			   -1

//AlphaBet
#define TX_KEY_A                  65
#define TX_KEY_B                  66
#define TX_KEY_C                  67
#define TX_KEY_D                  68
#define TX_KEY_E                  69
#define TX_KEY_F                  70
#define TX_KEY_G                  71
#define TX_KEY_H                  72
#define TX_KEY_I                  73
#define TX_KEY_J                  74
#define TX_KEY_K                  75
#define TX_KEY_L                  76
#define TX_KEY_M                  77
#define TX_KEY_N                  78
#define TX_KEY_O                  79
#define TX_KEY_P                  80
#define TX_KEY_Q                  81
#define TX_KEY_R                  82
#define TX_KEY_S                  83
#define TX_KEY_T                  84
#define TX_KEY_U                  85
#define TX_KEY_V                  86
#define TX_KEY_W                  87
#define TX_KEY_X                  88
#define TX_KEY_Y                  89
#define TX_KEY_Z                  90

//Number keys
#define TX_KEY_0                  48
#define TX_KEY_1                  49
#define TX_KEY_2                  50
#define TX_KEY_3                  51
#define TX_KEY_4                  52
#define TX_KEY_5                  53
#define TX_KEY_6                  54
#define TX_KEY_7                  55
#define TX_KEY_8                  56
#define TX_KEY_9                  57

#define TX_KEY_MINUS              45  /* - */
#define TX_KEY_EQUAL              61  /* = */

#define TX_KEY_SPACE              32
#define TX_KEY_APOSTROPHE         39  /* ' */
#define TX_KEY_COMMA              44  /* , */
#define TX_KEY_PERIOD             46  /* . */
#define TX_KEY_SLASH              47  /* / */
#define TX_KEY_SEMICOLON          59  /* ; */
#define TX_KEY_LEFT_BRACKET       91  /* [ */
#define TX_KEY_BACKSLASH          92  /* \ */
#define TX_KEY_RIGHT_BRACKET      93  /* ] */
#define TX_KEY_GRAVE_ACCENT       96  /* ` */


/* Function keys */
#define TX_KEY_ESCAPE             256
#define TX_KEY_ENTER              257
#define TX_KEY_TAB                258
#define TX_KEY_BACKSPACE          259
#define TX_KEY_INSERT             260
#define TX_KEY_DELETE             261
#define TX_KEY_RIGHT              262
#define TX_KEY_LEFT               263
#define TX_KEY_DOWN               264
#define TX_KEY_UP                 265
#define TX_KEY_PAGE_UP            266
#define TX_KEY_PAGE_DOWN          267
#define TX_KEY_HOME               268
#define TX_KEY_END                269
#define TX_KEY_CAPS_LOCK          280
#define TX_KEY_SCROLL_LOCK        281
#define TX_KEY_NUM_LOCK           282
#define TX_KEY_PRINT_SCREEN       283
#define TX_KEY_PAUSE              284

//F Keys
#define TX_KEY_F1                 290
#define TX_KEY_F2                 291
#define TX_KEY_F3                 292
#define TX_KEY_F4                 293
#define TX_KEY_F5                 294
#define TX_KEY_F6                 295
#define TX_KEY_F7                 296
#define TX_KEY_F8                 297
#define TX_KEY_F9                 298
#define TX_KEY_F10                299
#define TX_KEY_F11                300
#define TX_KEY_F12                301
#define TX_KEY_F13                302
#define TX_KEY_F14                303
#define TX_KEY_F15                304
#define TX_KEY_F16                305
#define TX_KEY_F17                306
#define TX_KEY_F18                307
#define TX_KEY_F19                308
#define TX_KEY_F20                309
#define TX_KEY_F21                310
#define TX_KEY_F22                311
#define TX_KEY_F23                312
#define TX_KEY_F24                313
#define TX_KEY_F25                314

//Num pad keys
#define TX_KEY_KP_0               320
#define TX_KEY_KP_1               321
#define TX_KEY_KP_2               322
#define TX_KEY_KP_3               323
#define TX_KEY_KP_4               324
#define TX_KEY_KP_5               325
#define TX_KEY_KP_6               326
#define TX_KEY_KP_7               327
#define TX_KEY_KP_8               328
#define TX_KEY_KP_9               329
#define TX_KEY_KP_DECIMAL         330
#define TX_KEY_KP_DIVIDE          331
#define TX_KEY_KP_MULTIPLY        332
#define TX_KEY_KP_SUBTRACT        333
#define TX_KEY_KP_ADD             334
#define TX_KEY_KP_ENTER           335
#define TX_KEY_KP_EQUAL           336

//Function keys
#define TX_KEY_LEFT_SHIFT         340
#define TX_KEY_LEFT_CONTROL       341
#define TX_KEY_LEFT_ALT           342
#define TX_KEY_LEFT_SUPER         343
#define TX_KEY_RIGHT_SHIFT        344
#define TX_KEY_RIGHT_CONTROL      345
#define TX_KEY_RIGHT_ALT          346
#define TX_KEY_RIGHT_SUPER        347
#define TX_KEY_MENU			   348


//Mouse Button
#define TX_MOUSE_BUTTON_1         0
#define TX_MOUSE_BUTTON_2         1
#define TX_MOUSE_BUTTON_3         2
#define TX_MOUSE_BUTTON_4         3
#define TX_MOUSE_BUTTON_5         4
#define TX_MOUSE_BUTTON_6         5
#define TX_MOUSE_BUTTON_7         6
#define TX_MOUSE_BUTTON_8         7
#define TX_MOUSE_BUTTON_LAST      TX_MOUSE_BUTTON_8
#define TX_MOUSE_BUTTON_LEFT      TX_MOUSE_BUTTON_1
#define TX_MOUSE_BUTTON_RIGHT     TX_MOUSE_BUTTON_2
#define TX_MOUSE_BUTTON_MIDDLE    TX_MOUSE_BUTTON_3