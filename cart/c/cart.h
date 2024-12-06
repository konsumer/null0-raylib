#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint64_t u64;
typedef float f32;
typedef double f64;

typedef u32 Image;
typedef u32 Font;
typedef u32 Sound;

// import function from host
#define HOST_FUNCTION(return_type, name, params) __attribute__((import_module("null0"), import_name(#name))) return_type name params;

// export function to host
#define CART_FUNCTION(n) __attribute__((export_name(n)))

typedef enum ImageFilter {
  FILTER_NEARESTNEIGHBOR = 0,
  FILTER_BILINEAR,
  FILTER_SMOOTH
} ImageFilter;

typedef enum Key {
  KEY_INVALID = 0,
  KEY_SPACE = 32,
  KEY_APOSTROPHE = 39,
  KEY_COMMA = 44,
  KEY_MINUS = 45,
  KEY_PERIOD = 46,
  KEY_SLASH = 47,
  KEY_0 = 48,
  KEY_1 = 49,
  KEY_2 = 50,
  KEY_3 = 51,
  KEY_4 = 52,
  KEY_5 = 53,
  KEY_6 = 54,
  KEY_7 = 55,
  KEY_8 = 56,
  KEY_9 = 57,
  KEY_SEMICOLON = 59,
  KEY_EQUAL = 61,
  KEY_A = 65,
  KEY_B = 66,
  KEY_C = 67,
  KEY_D = 68,
  KEY_E = 69,
  KEY_F = 70,
  KEY_G = 71,
  KEY_H = 72,
  KEY_I = 73,
  KEY_J = 74,
  KEY_K = 75,
  KEY_L = 76,
  KEY_M = 77,
  KEY_N = 78,
  KEY_O = 79,
  KEY_P = 80,
  KEY_Q = 81,
  KEY_R = 82,
  KEY_S = 83,
  KEY_T = 84,
  KEY_U = 85,
  KEY_V = 86,
  KEY_W = 87,
  KEY_X = 88,
  KEY_Y = 89,
  KEY_Z = 90,
  KEY_LEFT_BRACKET = 91,
  KEY_BACKSLASH = 92,
  KEY_RIGHT_BRACKET = 93,
  KEY_GRAVE_ACCENT = 96,
  KEY_WORLD_1 = 161,
  KEY_WORLD_2 = 162,
  KEY_ESCAPE = 256,
  KEY_ENTER = 257,
  KEY_TAB = 258,
  KEY_BACKSPACE = 259,
  KEY_INSERT = 260,
  KEY_DELETE = 261,
  KEY_RIGHT = 262,
  KEY_LEFT = 263,
  KEY_DOWN = 264,
  KEY_UP = 265,
  KEY_PAGE_UP = 266,
  KEY_PAGE_DOWN = 267,
  KEY_HOME = 268,
  KEY_END = 269,
  KEY_CAPS_LOCK = 280,
  KEY_SCROLL_LOCK = 281,
  KEY_NUM_LOCK = 282,
  KEY_PRINT_SCREEN = 283,
  KEY_PAUSE = 284,
  KEY_F1 = 290,
  KEY_F2 = 291,
  KEY_F3 = 292,
  KEY_F4 = 293,
  KEY_F5 = 294,
  KEY_F6 = 295,
  KEY_F7 = 296,
  KEY_F8 = 297,
  KEY_F9 = 298,
  KEY_F10 = 299,
  KEY_F11 = 300,
  KEY_F12 = 301,
  KEY_F13 = 302,
  KEY_F14 = 303,
  KEY_F15 = 304,
  KEY_F16 = 305,
  KEY_F17 = 306,
  KEY_F18 = 307,
  KEY_F19 = 308,
  KEY_F20 = 309,
  KEY_F21 = 310,
  KEY_F22 = 311,
  KEY_F23 = 312,
  KEY_F24 = 313,
  KEY_F25 = 314,
  KEY_KP_0 = 320,
  KEY_KP_1 = 321,
  KEY_KP_2 = 322,
  KEY_KP_3 = 323,
  KEY_KP_4 = 324,
  KEY_KP_5 = 325,
  KEY_KP_6 = 326,
  KEY_KP_7 = 327,
  KEY_KP_8 = 328,
  KEY_KP_9 = 329,
  KEY_KP_DECIMAL = 330,
  KEY_KP_DIVIDE = 331,
  KEY_KP_MULTIPLY = 332,
  KEY_KP_SUBTRACT = 333,
  KEY_KP_ADD = 334,
  KEY_KP_ENTER = 335,
  KEY_KP_EQUAL = 336,
  KEY_LEFT_SHIFT = 340,
  KEY_LEFT_CONTROL = 341,
  KEY_LEFT_ALT = 342,
  KEY_LEFT_SUPER = 343,
  KEY_RIGHT_SHIFT = 344,
  KEY_RIGHT_CONTROL = 345,
  KEY_RIGHT_ALT = 346,
  KEY_RIGHT_SUPER = 347,
  KEY_MENU = 348,
} Key;

typedef enum GamepadButton {
  GAMEPAD_BUTTON_UNKNOWN = 0,     // Unknown button, just for error checking
  GAMEPAD_BUTTON_UP = 1,          // Gamepad left DPAD up button
  GAMEPAD_BUTTON_RIGHT,           // Gamepad left DPAD right button
  GAMEPAD_BUTTON_DOWN,            // Gamepad left DPAD down button
  GAMEPAD_BUTTON_LEFT,            // Gamepad left DPAD left button
  GAMEPAD_BUTTON_Y,               // Gamepad right button up (i.e. PS3: Triangle, Xbox: Y)
  GAMEPAD_BUTTON_B,               // Gamepad right button right (i.e. PS3: Square, Xbox: X)
  GAMEPAD_BUTTON_A,               // Gamepad right button down (i.e. PS3: Cross, Xbox: A)
  GAMEPAD_BUTTON_X,               // Gamepad right button left (i.e. PS3: Circle, Xbox: B)
  GAMEPAD_BUTTON_LEFT_SHOULDER,   // Gamepad top/back trigger left (first), it could be a trailing button
  GAMEPAD_BUTTON_LEFT_TRIGGER,    // Gamepad top/back trigger left (second), it could be a trailing button
  GAMEPAD_BUTTON_RIGHT_SHOULDER,  // Gamepad top/back trigger right (one), it could be a trailing button
  GAMEPAD_BUTTON_RIGHT_TRIGGER,   // Gamepad top/back trigger right (second), it could be a trailing button
  GAMEPAD_BUTTON_SELECT,          // Gamepad center buttons, left one (i.e. PS3: Select)
  GAMEPAD_BUTTON_MENU,            // Gamepad center buttons, middle one (i.e. PS3: PS, Xbox: XBOX)
  GAMEPAD_BUTTON_START,           // Gamepad center buttons, right one (i.e. PS3: Start)
  GAMEPAD_BUTTON_LEFT_THUMB,      // Gamepad joystick pressed button left
  GAMEPAD_BUTTON_RIGHT_THUMB,     // Gamepad joystick pressed button right
} GamepadButton;

typedef enum MouseButton {
  MOUSE_BUTTON_UNKNOWN = 0,
  MOUSE_BUTTON_LEFT = 1,
  MOUSE_BUTTON_RIGHT = 2,
  MOUSE_BUTTON_MIDDLE = 3,
} MouseButton;

typedef enum SfxPresetType {
  SFX_COIN,
  SFX_LASER,
  SFX_EXPLOSION,
  SFX_POWERUP,
  SFX_HURT,
  SFX_JUMP,
  SFX_SELECT,
  SFX_SYNTH
} SfxPresetType;

typedef enum SfxWaveType {
  SFX_SQUARE,
  SFX_SAWTOOTH,
  SFX_SINE,
  SFX_NOISE,
  SFX_TRIANGLE,
  SFX_PINK_NOISE
} SfxWaveType;

typedef enum FileType {
  FILETYPE_REGULAR,   // a normal file 
  FILETYPE_DIRECTORY, // a directory 
  FILETYPE_SYMLINK,   // a symlink 
  FILETYPE_OTHER      // something completely different like a device 
} FileType;

typedef struct {
  u32 width;
  u32 height;
} Dimensions;

typedef struct {
  i32 x;
  i32 y;
} Vector;

typedef struct {
  i32 x;
  i32 y;
  i32 width;
  i32 height;
} Rectangle;

// Sound parameters
typedef struct SfxParams {
  SfxWaveType waveType;

  // Wave envelope parameters
  float attackTime;
  float sustainTime;
  float sustainPunch;
  float decayTime;

  // Frequency parameters
  float startFrequency;
  float minFrequency;
  float slide;
  float deltaSlide;
  float vibratoDepth;
  float vibratoSpeed;

  // Tone change parameters
  float changeAmount;
  float changeSpeed;

  // Square wave parameters
  float squareDuty;
  float dutySweep;

  // Repeat parameters
  float repeatSpeed;

  // Phaser parameters
  float phaserOffset;
  float phaserSweep;

  // Filter parameters
  float lpfCutoff;
  float lpfCutoffSweep;
  float lpfResonance;
  float hpfCutoff;
  float hpfCutoffSweep;
} SfxParams;

typedef struct {
  u8 r;
  u8 g;
  u8 b;
  u8 a;
} Color;

typedef struct FileInfo {
  i64 filesize;      // size in bytes, -1 for non-files and unknown 
  i64 modtime;       // last modification time 
  i64 createtime;    // like modtime, but for file creation time 
  i64 accesstime;    // like modtime, but for file access time 
  FileType filetype; // File? Directory? Symlink? 
  bool readonly;     // non-zero if read only, zero if writable. 
} FileInfo;

#define WIDTH 320
#define HEIGHT 240

Color LIGHTGRAY = (Color){.r = 200, .g = 200, .b = 200, .a = 255};
Color GRAY = (Color){.r = 130, .g = 130, .b = 130, .a = 255};
Color DARKGRAY = (Color){.r = 80, .g = 80, .b = 80, .a = 255};
Color YELLOW = (Color){.r = 253, .g = 249, .b = 0, .a = 255};
Color GOLD = (Color){.r = 255, .g = 203, .b = 0, .a = 255};
Color ORANGE = (Color){.r = 255, .g = 161, .b = 0, .a = 255};
Color PINK = (Color){.r = 255, .g = 109, .b = 194, .a = 255};
Color RED = (Color){.r = 230, .g = 41, .b = 55, .a = 255};
Color MAROON = (Color){.r = 190, .g = 33, .b = 55, .a = 255};
Color GREEN = (Color){.r = 0, .g = 228, .b = 48, .a = 255};
Color LIME = (Color){.r = 0, .g = 158, .b = 47, .a = 255};
Color DARKGREEN = (Color){.r = 0, .g = 117, .b = 44, .a = 255};
Color SKYBLUE = (Color){.r = 102, .g = 191, .b = 255, .a = 255};
Color BLUE = (Color){.r = 0, .g = 121, .b = 241, .a = 255};
Color DARKBLUE = (Color){.r = 0, .g = 82, .b = 172, .a = 255};
Color PURPLE = (Color){.r = 200, .g = 122, .b = 255, .a = 255};
Color VIOLET = (Color){.r = 135, .g = 60, .b = 190, .a = 255};
Color DARKPURPLE = (Color){.r = 112, .g = 31, .b = 126, .a = 255};
Color BEIGE = (Color){.r = 211, .g = 176, .b = 131, .a = 255};
Color BROWN = (Color){.r = 127, .g = 106, .b = 79, .a = 255};
Color DARKBROWN = (Color){.r = 76, .g = 63, .b = 47, .a = 255};
Color WHITE = (Color){.r = 255, .g = 255, .b = 255, .a = 255};
Color BLACK = (Color){.r = 0, .g = 0, .b = 0, .a = 255};
Color BLANK = (Color){.r = 0, .g = 0, .b = 0, .a = 0};
Color MAGENTA = (Color){.r = 255, .g = 0, .b = 255, .a = 255};
Color RAYWHITE = (Color){.r = 245, .g = 245, .b = 245, .a = 255};

// mem-management

CART_FUNCTION("malloc")
void* _wasm_host_malloc(size_t size) {
  return malloc(size);
}

CART_FUNCTION("free")
void _wasm_host_free(void* ptr) {
  free(ptr);
}

// callbacks
CART_FUNCTION("load")
void load();

CART_FUNCTION("update")
void update();

CART_FUNCTION("unload")
void unload();

CART_FUNCTION("buttonDown")
void buttonDown(GamepadButton button);

CART_FUNCTION("buttonUp")
void buttonUp(GamepadButton button);


// UTILS API

// print a string
HOST_FUNCTION(void, trace, (char* str))

// a fatal exit
HOST_FUNCTION(void, host_abort, (char*  message, char*  filename, u32 line, u32 column))

// GRAPHICS API

// Create a new blank image
HOST_FUNCTION(u32, new_image, (i32 width, i32 height, Color color))

// Copy an image to a new image
HOST_FUNCTION(u32, image_copy, (Image image))

// Create an image from a region of another image
HOST_FUNCTION(u32, image_subimage, (Image image, i32 x, i32 y, i32 width, i32 height))

// Clear the screen
HOST_FUNCTION(void, clear, (Color color))

// Draw a single pixel on the screen
HOST_FUNCTION(void, draw_point, (i32 x, i32 y, Color color))

// Draw a line on the screen
HOST_FUNCTION(void, draw_line, (i32 startPosX, i32 startPosY, i32 endPosX, i32 endPosY, Color color))

// Draw a filled rectangle on the screen
HOST_FUNCTION(void, draw_rectangle, (i32 posX, i32 posY, i32 width, i32 height, Color color))

// Draw a filled triangle on the screen
HOST_FUNCTION(void, draw_triangle, (i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, Color color))

// Draw a filled ellipse on the screen
HOST_FUNCTION(void, draw_ellipse, (i32 centerX, i32 centerY, i32 radiusX, i32 radiusY, Color color))

// Draw a filled circle on the screen
HOST_FUNCTION(void, draw_circle, (i32 centerX, i32 centerY, i32 radius, Color color))

// Draw a filled polygon on the screen
HOST_FUNCTION(void, draw_polygon, (i32 numPoints, Vector* points, Color color))

// Draw several lines on the screen
HOST_FUNCTION(void, draw_polyline, (i32 numPoints, Vector* points, Color color))

// Draw a filled arc on the screen
HOST_FUNCTION(void, draw_arc, (i32 centerX, i32 centerY, f32 radius, f32 startAngle, f32 endAngle, i32 segments, Color color))

// Draw a filled round-rectangle on the screen
HOST_FUNCTION(void, draw_rectangle_rounded, (i32 x, i32 y, i32 width, i32 height, i32 cornerRadius, Color color))

// Draw an image on the screen
HOST_FUNCTION(void, draw_image, (Image src, i32 posX, i32 posY))

// Draw a tinted image on the screen
HOST_FUNCTION(void, draw_image_tint, (Image src, i32 posX, i32 posY, Color tint))

// Draw an image, rotated, on the screen
HOST_FUNCTION(void, draw_image_rotated, (Image src, i32 posX, i32 posY, f32 degrees, f32 offsetX, f32 offsetY, ImageFilter filter))

// Draw an image, flipped, on the screen
HOST_FUNCTION(void, draw_image_flipped, (Image src, i32 posX, i32 posY, bool flipHorizontal, bool flipVertical, bool flipDiagonal))

// Draw an image, scaled, on the screen
HOST_FUNCTION(void, draw_image_scaled, (Image src, i32 posX, i32 posY, f32 scaleX, f32 scaleY, f32 offsetX, f32 offsetY, ImageFilter filter))

// Draw some text on the screen
HOST_FUNCTION(void, draw_text, (u32 fontSize, char* text, i32 posX, i32 posY, Color color))

// Save an image to persistant storage
HOST_FUNCTION(void, save_image, (Image image, char* filename))

// Load an image from a file in cart
HOST_FUNCTION(u32, load_image, (char* filename))

// Resize an image, in-place
HOST_FUNCTION(void, image_resize, (Image image, i32 newWidth, i32 newHeight, i32 offsetX, i32 offsetY, Color fill))

// Scale an image, in-place
HOST_FUNCTION(void, image_scale, (Image image, f32 scaleX, f32 scaleY, ImageFilter filter))

// Replace a color in an image, in-place
HOST_FUNCTION(void, image_color_replace, (Image image, Color color, Color replace))

// Tint a color in an image, in-place
HOST_FUNCTION(void, image_color_tint, (Image image, Color color))

// Fade a color in an image, in-place
HOST_FUNCTION(void, image_color_fade, (Image image, f32 alpha))

// Copy a font to a new font
HOST_FUNCTION(u32, font_copy, (Font font))

// Scale a font, return a new font
HOST_FUNCTION(u32, font_scale, (Font font, f32 scaleX, f32 scaleY, ImageFilter filter))

// Load a BMF font from a file in cart
HOST_FUNCTION(u32, load_font_bmf, (char* filename, char* characters))

// Load a BMF font from an image
HOST_FUNCTION(u32, load_font_bmf_from_image, (Image image, char* characters))

// Measure the size of some text
HOST_FUNCTION(u32, measure_text, (u32 fontSize, char* text))

// Meaure an image (use 0 for screen)
HOST_FUNCTION(u32, measure_image, (Image image))

// Load a TTY font from a file in cart
HOST_FUNCTION(u32, load_font_tty, (char* filename, i32 glyphWidth, i32 glyphHeight, char* characters))

// Load a TTY font from an image
HOST_FUNCTION(u32, load_font_tty_from_image, (Image image, i32 glyphWidth, i32 glyphHeight, char* characters))

// Load a TTF font from a file in cart
HOST_FUNCTION(u32, load_font_ttf, (char* filename, i32 fontSize))

// Invert the colors in an image, in-place
HOST_FUNCTION(void, image_color_invert, (Image image))

// Calculate a rectangle representing the available alpha border in an image
HOST_FUNCTION(u32, image_alpha_border, (Image image, f32 threshold))

// Crop an image, in-place
HOST_FUNCTION(void, image_crop, (Image image, i32 x, i32 y, i32 width, i32 height))

// Crop an image based on the alpha border, in-place
HOST_FUNCTION(void, image_alpha_crop, (Image image, f32 threshold))

// Adjust the brightness of an image, in-place
HOST_FUNCTION(void, image_color_brightness, (Image image, f32 factor))

// Flip an image, in-place
HOST_FUNCTION(void, image_flip, (Image image, bool horizontal, bool vertical))

// Change the contrast of an image, in-place
HOST_FUNCTION(void, image_color_contrast, (Image image, f32 contrast))

// Use an image as an alpha-mask on another image
HOST_FUNCTION(void, image_alpha_mask, (Image image, Image alphaMask, i32 posX, i32 posY))

// Create a new image, rotating another image
HOST_FUNCTION(u32, image_rotate, (Image image, f32 degrees, ImageFilter filter))

// Create a new image of a gradient
HOST_FUNCTION(u32, image_gradient, (i32 width, i32 height, Color topLeft, Color topRight, Color bottomLeft, Color bottomRight))

// Unload an image
HOST_FUNCTION(void, unload_image, (Image image))

// Unload a font
HOST_FUNCTION(void, unload_font, (Font font))

// Clear an image
HOST_FUNCTION(void, clear_on_image, (Image destination, Color color))

// Draw a single pixel on an image
HOST_FUNCTION(void, draw_point_on_image, (Image destination, i32 x, i32 y, Color color))

// Draw a line on an image
HOST_FUNCTION(void, draw_line_on_image, (Image destination, i32 startPosX, i32 startPosY, i32 endPosX, i32 endPosY, Color color))

// Draw a filled rectangle on an image
HOST_FUNCTION(void, draw_rectangle_on_image, (Image destination, i32 posX, i32 posY, i32 width, i32 height, Color color))

// Draw a filled triangle on an image
HOST_FUNCTION(void, draw_triangle_on_image, (Image destination, i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, Color color))

// Draw a filled ellipse on an image
HOST_FUNCTION(void, draw_ellipse_on_image, (Image destination, i32 centerX, i32 centerY, i32 radiusX, i32 radiusY, Color color))

// Draw a circle on an image
HOST_FUNCTION(void, draw_circle_on_image, (Image destination, i32 centerX, i32 centerY, i32 radius, Color color))

// Draw a filled polygon on an image
HOST_FUNCTION(void, draw_polygon_on_image, (Image destination, i32 numPoints, Vector* points, Color color))

// Draw several lines on an image
HOST_FUNCTION(void, draw_polyline_on_image, (Image destination, i32 numPoints, Vector* points, Color color))

// Draw a filled round-rectangle on an image
HOST_FUNCTION(void, draw_rectangle_rounded_on_image, (Image destination, i32 x, i32 y, i32 width, i32 height, i32 cornerRadius, Color color))

// Draw an image on an image
HOST_FUNCTION(void, draw_image_on_image, (Image destination, Image src, i32 posX, i32 posY))

// Draw a tinted image on an image
HOST_FUNCTION(void, draw_image_tint_on_image, (Image destination, Image src, i32 posX, i32 posY, Color tint))

// Draw an image, rotated, on an image
HOST_FUNCTION(void, draw_image_rotated_on_image, (Image destination, Image src, i32 posX, i32 posY, f32 degrees, f32 offsetX, f32 offsetY, ImageFilter filter))

// Draw an image, flipped, on an image
HOST_FUNCTION(void, draw_image_flipped_on_image, (Image destination, Image src, i32 posX, i32 posY, bool flipHorizontal, bool flipVertical, bool flipDiagonal))

// Draw an image, scaled, on an image
HOST_FUNCTION(void, draw_image_scaled_on_image, (Image destination, Image src, i32 posX, i32 posY, f32 scaleX, f32 scaleY, f32 offsetX, f32 offsetY, ImageFilter filter))

// Draw some text on an image
HOST_FUNCTION(void, draw_text_on_image, (Image destination, u32 fontSize, char* text, i32 posX, i32 posY, Color color))

// Draw a 1px outlined rectangle on the screen
HOST_FUNCTION(void, draw_rectangle_outline, (i32 posX, i32 posY, i32 width, i32 height, Color color))

// Draw a 1px outlined triangle on the screen
HOST_FUNCTION(void, draw_triangle_outline, (i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, Color color))

// Draw a 1px outlined ellipse on the screen
HOST_FUNCTION(void, draw_ellipse_outline, (i32 centerX, i32 centerY, i32 radiusX, i32 radiusY, Color color))

// Draw a 1px outlined circle on the screen
HOST_FUNCTION(void, draw_circle_outline, (i32 centerX, i32 centerY, i32 radius, Color color))

// Draw a 1px outlined polygon on the screen
HOST_FUNCTION(void, draw_polygon_outline, (i32 numPoints, Vector* points, Color color))

// Draw a 1px outlined arc on the screen
HOST_FUNCTION(void, draw_arc_outline, (i32 centerX, i32 centerY, f32 radius, f32 startAngle, f32 endAngle, i32 segments, Color color))

// Draw a 1px outlined round-rectangle on the screen
HOST_FUNCTION(void, draw_rectangle_rounded_outline, (i32 x, i32 y, i32 width, i32 height, i32 cornerRadius, Color color))

// Draw a 1px outlined rectangle on an image
HOST_FUNCTION(void, draw_rectangle_outline_on_image, (Image destination, i32 posX, i32 posY, i32 width, i32 height, Color color))

// Draw a 1px outlined triangle on an image
HOST_FUNCTION(void, draw_triangle_outline_on_image, (Image destination, i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, Color color))

// Draw a 1px outlined ellipse on an image
HOST_FUNCTION(void, draw_ellipse_outline_on_image, (Image destination, i32 centerX, i32 centerY, i32 radiusX, i32 radiusY, Color color))

// Draw a 1px outlined circle on an image
HOST_FUNCTION(void, draw_circle_outline_on_image, (Image destination, i32 centerX, i32 centerY, i32 radius, Color color))

// Draw a 1px outlined polygon on an image
HOST_FUNCTION(void, draw_polygon_outline_on_image, (Image destination, i32 numPoints, Vector* points, Color color))

// Draw a 1px outlined round-rectangle on an image
HOST_FUNCTION(void, draw_rectangle_rounded_outline_on_image, (Image destination, i32 x, i32 y, i32 width, i32 height, i32 cornerRadius, Color color))

