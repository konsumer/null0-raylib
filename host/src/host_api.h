// Host interface exposed to WAMR and Emscripten

#pragma once

#include "hexdump.h"

static cvector_vector_type(Image) images = NULL;
static cvector_vector_type(Texture2D) textures = NULL;

// Used to test passing structs over wasm-barrier
typedef struct {
  u32 x;
  u32 y;
} TestPoint;

// UTILS API

// print a string
HOST_FUNCTION(void, trace, (u32 strPtr), {
  char* str = copy_from_cart_string(strPtr);
  printf("%s\n", str);
  free(str);
})

// a fatal exit
HOST_FUNCTION(void, abort, (u32 messagePtr, u32 filenamePtr, u32 line, u32 column), {
  char* message = copy_from_cart_string(messagePtr);
  char* filename = copy_from_cart_string(filenamePtr);
  fprintf(stderr, "%s: %s:%u:%u\n", message, filename, line, column);
  free(message);
  free(filename);
})

// TEST API

// send a string to host
HOST_FUNCTION(void, test_string_in, (u32 strPtr), {
  char* str = copy_from_cart_string(strPtr);
  printf("host test_string_in: got string from cart: %s\n", str);
  free(str);
})

// return a string from host
HOST_FUNCTION(u32, test_string_out, (), {
  char* s = "hello from host";
  return copy_to_cart_string(s);
})

// send some bytes to host
HOST_FUNCTION(void, test_bytes_in, (u32 bytesPtr, u32 bytesLen), {
  u8* bytes = copy_from_cart(bytesPtr, bytesLen);
  printf("host test_bytes_in:\n");
  hexdump(bytes, bytesLen);
  free(bytes);
})

// return some bytes from host
HOST_FUNCTION(u32, test_bytes_out, (u32 outLenPtr), {
  u32 outLen = 4;
  u8 returnVal[4] = {1,2,3,4};
  copy_to_cart_with_pointer(outLenPtr, &outLen, sizeof(outLen));
  return copy_to_cart(returnVal, outLen);
})

// send struct to host
HOST_FUNCTION(void, test_struct_in, (u32 pointPtr), {
  TestPoint* point = copy_from_cart(pointPtr, sizeof(TestPoint));
  printf("host test_struct_in: (%u, %u)\n", point->x, point->y);
  free(point);
})

// return struct from host
HOST_FUNCTION(u32, test_struct_out, (), {
  TestPoint result = { .x=1111, .y=2222 };
  return copy_to_cart(&result, sizeof(result));
})

// GRAPHICS API

// Given an image, save it to images and return index
u32 null0_save_image(Image image) {
  u32 imageId = cvector_size(images);
  cvector_push_back(images, image);
  cvector_push_back(textures, LoadTextureFromImage(image));
  return imageId;
}

// Given an image-id, return the images
Image null0_get_image(u32 imageId) {
  return images[imageId];
} 

// Create a new blank image
HOST_FUNCTION(u32, new_image, (i32 width, i32 height, u32 colorPtr), {
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  u32 ret = null0_save_image(GenImageColor(width, height, *color));
  free(color);
  return ret;
})

// Copy an image to a new image
HOST_FUNCTION(u32, image_copy, (u32 imagePtr), {
  return null0_save_image(ImageCopy(null0_get_image(imagePtr)));
})

// Create an image from a region of another image
HOST_FUNCTION(u32, image_subimage, (u32 imagePtr, i32 x, i32 y, i32 width, i32 height), {
  return null0_save_image(ImageFromImage(null0_get_image(imagePtr), (Rectangle){.x=x, .y=y, .width=width, .height=height}));
})

// Clear the screen
HOST_FUNCTION(void, clear, (u32 colorPtr), {
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  ClearBackground(*color);
  free(color);
})

// Draw a single pixel on the screen
HOST_FUNCTION(void, draw_point, (i32 x, i32 y, u32 colorPtr), {
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  DrawPixel(x, y, *color);
  free(color);
})

// Draw a line on the screen
HOST_FUNCTION(void, draw_line, (i32 startPosX, i32 startPosY, i32 endPosX, i32 endPosY, u32 colorPtr), {
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  DrawLine(startPosX, startPosY, endPosX, endPosY, *color);
  free(color);
})

// Draw a filled rectangle on the screen
HOST_FUNCTION(void, draw_rectangle, (i32 posX, i32 posY, i32 width, i32 height, u32 colorPtr), {
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  DrawRectangle(posX, posY, width, height, *color);
  free(color);
})

// Draw a filled triangle on the screen
HOST_FUNCTION(void, draw_triangle, (i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, u32 colorPtr), {
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  Vector2 v1 = (Vector2){.x=x1, .y=y1};
  Vector2 v2 = (Vector2){.x=x2, .y=y2};
  Vector2 v3 = (Vector2){.x=x3, .y=y3};
  DrawTriangle(v1, v2, v3, *color);
  free(color);
})

// Draw a filled ellipse on the screen
HOST_FUNCTION(void, draw_ellipse, (i32 centerX, i32 centerY, i32 radiusX, i32 radiusY, u32 colorPtr), {
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  DrawEllipse(centerX, centerY, radiusX, radiusY, *color);
  free(color);
})

// Draw a filled circle on the screen
HOST_FUNCTION(void, draw_circle, (i32 centerX, i32 centerY, i32 radius, u32 colorPtr), {
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  DrawCircle(centerX, centerY, (float) radius, *color); 
  free(color);
})

// Draw a filled polygon on the screen
HOST_FUNCTION(void, draw_polygon, (i32 numPoints, u32 pointsPtr, u32 pointsLen, u32 colorPtr), {
  u8* points = copy_from_cart(pointsPtr, pointsLen);
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  // TODO
  free(points);
  free(color);
})

// Draw several lines on the screen
HOST_FUNCTION(void, draw_polyline, (i32 numPoints, u32 pointsPtr, u32 pointsLen, u32 colorPtr), {
  u8* points = copy_from_cart(pointsPtr, pointsLen);
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  // TODO
  free(points);
  free(color);
})

// Draw a filled arc on the screen
HOST_FUNCTION(void, draw_arc, (i32 centerX, i32 centerY, f32 radius, f32 startAngle, f32 endAngle, i32 segments, u32 colorPtr), {
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  // TODO
  free(color);
})

// Draw a filled round-rectangle on the screen
HOST_FUNCTION(void, draw_rectangle_rounded, (i32 x, i32 y, i32 width, i32 height, i32 cornerRadius, u32 colorPtr), {
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  // TODO
  free(color);
})

// Draw an image on the screen
HOST_FUNCTION(void, draw_image, (u32 srcPtr, i32 posX, i32 posY), {
  // TODO
})

// Draw a tinted image on the screen
HOST_FUNCTION(void, draw_image_tint, (u32 srcPtr, i32 posX, i32 posY, u32 tintPtr), {
  Color* tint = copy_from_cart(tintPtr, sizeof(Color));
  // TODO
  free(tint);
})

// Draw an image, rotated, on the screen
HOST_FUNCTION(void, draw_image_rotated, (u32 srcPtr, i32 posX, i32 posY, f32 degrees, f32 offsetX, f32 offsetY, u32 filter), {
  // TODO
})

// Draw an image, flipped, on the screen
HOST_FUNCTION(void, draw_image_flipped, (u32 srcPtr, i32 posX, i32 posY, bool flipHorizontal, bool flipVertical, bool flipDiagonal), {
  // TODO
})

// Draw an image, scaled, on the screen
HOST_FUNCTION(void, draw_image_scaled, (u32 srcPtr, i32 posX, i32 posY, f32 scaleX, f32 scaleY, f32 offsetX, f32 offsetY, u32 filter), {
  // TODO
})

// Draw some text on the screen
HOST_FUNCTION(void, draw_text, (u32 fontPtr, u32 textPtr, i32 posX, i32 posY, u32 colorPtr), {
  char* text = copy_from_cart_string(textPtr);
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  // TODO
  free(text);
  free(color);
})

// Save an image to persistant storage
HOST_FUNCTION(void, save_image, (u32 imagePtr, u32 filenamePtr), {
  char* filename = copy_from_cart_string(filenamePtr);
  // TODO
  free(filename);
})

// Load an image from a file in cart
HOST_FUNCTION(u32, load_image, (u32 filenamePtr), {
  char* filename = copy_from_cart_string(filenamePtr);
  // TODO
  Image result = {};
  free(filename);
  return copy_to_cart(&result, sizeof(result));
})

// Resize an image, in-place
HOST_FUNCTION(void, image_resize, (u32 imagePtr, i32 newWidth, i32 newHeight, i32 offsetX, i32 offsetY, u32 fillPtr), {
  Color* fill = copy_from_cart(fillPtr, sizeof(Color));
  // TODO
  free(fill);
})

// Scale an image, in-place
HOST_FUNCTION(void, image_scale, (u32 imagePtr, f32 scaleX, f32 scaleY, u32 filter), {
  // TODO
})

// Replace a color in an image, in-place
HOST_FUNCTION(void, image_color_replace, (u32 imagePtr, u32 colorPtr, u32 replacePtr), {
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  Color* replace = copy_from_cart(replacePtr, sizeof(Color));
  // TODO
  free(color);
  free(replace);
})

// Tint a color in an image, in-place
HOST_FUNCTION(void, image_color_tint, (u32 imagePtr, u32 colorPtr), {
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  // TODO
  free(color);
})

// Fade a color in an image, in-place
HOST_FUNCTION(void, image_color_fade, (u32 imagePtr, f32 alpha), {
  // TODO
})

// Copy a font to a new font
HOST_FUNCTION(u32, font_copy, (u32 fontPtr), {
  // TODO
  return 0;
})

// Scale a font, return a new font
HOST_FUNCTION(u32, font_scale, (u32 fontPtr, f32 scaleX, f32 scaleY, u32 filter), {
  // TODO
  return 0;
})

// Load a BMF font from a file in cart
HOST_FUNCTION(u32, load_font_bmf, (u32 filenamePtr, u32 charactersPtr), {
  char* filename = copy_from_cart_string(filenamePtr);
  // TODO
  free(filename);
  return 0;
})

// Load a BMF font from an image
HOST_FUNCTION(u32, load_font_bmf_from_image, (u32 imagePtr, u32 charactersPtr), {
  char* characters = copy_from_cart_string(charactersPtr);
  // TODO
  free(characters);
  return 0;
})

// Measure the size of some text
HOST_FUNCTION(u32, measure_text, (u32 fontPtr, u32 textPtr), {
  char* text = copy_from_cart_string(textPtr);
  // TODO
  free(text);
  return 0;
})

// Meaure an image (use 0 for screen)
HOST_FUNCTION(u32, measure_image, (u32 imagePtr), {
  // TODO
  return 0;
})

// Load a TTY font from a file in cart
HOST_FUNCTION(u32, load_font_tty, (u32 filenamePtr, i32 glyphWidth, i32 glyphHeight, u32 charactersPtr), {
  char* filename = copy_from_cart_string(filenamePtr);
  char* characters = copy_from_cart_string(charactersPtr);
  // TODO
  free(filename);
  free(characters);
  return 0;
})

// Load a TTY font from an image
HOST_FUNCTION(u32, load_font_tty_from_image, (u32 imagePtr, i32 glyphWidth, i32 glyphHeight, u32 charactersPtr), {
  char* characters = copy_from_cart_string(charactersPtr);
  // TODO
  free(characters);
  return 0;
})

// Load a TTF font from a file in cart
HOST_FUNCTION(u32, load_font_ttf, (u32 filenamePtr, i32 fontSize), {
  char* filename = copy_from_cart_string(filenamePtr);
  // TODO
  free(filename);
  return 0;
})

// Invert the colors in an image, in-place
HOST_FUNCTION(void, image_color_invert, (u32 imagePtr), {
  // TODO
})

// Calculate a rectangle representing the available alpha border in an image
HOST_FUNCTION(u32, image_alpha_border, (u32 imagePtr, f32 threshold), {
  // TODO
  return 0;
})

// Crop an image, in-place
HOST_FUNCTION(void, image_crop, (u32 imagePtr, i32 x, i32 y, i32 width, i32 height), {
  // TODO
})

// Crop an image based on the alpha border, in-place
HOST_FUNCTION(void, image_alpha_crop, (u32 imagePtr, f32 threshold), {
  // TODO
})

// Adjust the brightness of an image, in-place
HOST_FUNCTION(void, image_color_brightness, (u32 imagePtr, f32 factor), {
  // TODO
})

// Flip an image, in-place
HOST_FUNCTION(void, image_flip, (u32 imagePtr, bool horizontal, bool vertical), {
  // TODO
})

// Change the contrast of an image, in-place
HOST_FUNCTION(void, image_color_contrast, (u32 imagePtr, f32 contrast), {
  // TODO
})

// Use an image as an alpha-mask on another image
HOST_FUNCTION(void, image_alpha_mask, (u32 imagePtr, u32 alphaMaskPtr, i32 posX, i32 posY), {
  // TODO
})

// Create a new image, rotating another image
HOST_FUNCTION(u32, image_rotate, (u32 imagePtr, f32 degrees, u32 filter), {
  // TODO
  return 0;
})

// Create a new image of a gradient
HOST_FUNCTION(u32, image_gradient, (i32 width, i32 height, u32 topLeftPtr, u32 topRightPtr, u32 bottomLeftPtr, u32 bottomRightPtr), {
  Color* topLeft = copy_from_cart(topLeftPtr, sizeof(Color));
  Color* topRight = copy_from_cart(topRightPtr, sizeof(Color));
  Color* bottomLeft = copy_from_cart(bottomLeftPtr, sizeof(Color));
  Color* bottomRight = copy_from_cart(bottomRightPtr, sizeof(Color));
  // TODO
  free(topLeft);
  free(topRight);
  free(bottomLeft);
  free(bottomRight);
  return 0;
})

// Unload an image
HOST_FUNCTION(void, unload_image, (u32 imagePtr), {
  // TODO
})

// Unload a font
HOST_FUNCTION(void, unload_font, (u32 fontPtr), {
 // TODO
})

// Clear an image
HOST_FUNCTION(void, clear_on_image, (u32 destinationPtr, u32 colorPtr), {
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  // TODO
  free(color);
})

// Draw a single pixel on an image
HOST_FUNCTION(void, draw_point_on_image, (u32 destinationPtr, i32 x, i32 y, u32 colorPtr), {
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  // TODO
  free(color);
})

// Draw a line on an image
HOST_FUNCTION(void, draw_line_on_image, (u32 destinationPtr, i32 startPosX, i32 startPosY, i32 endPosX, i32 endPosY, u32 colorPtr), {
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  // TODO
  free(color);
})

// Draw a filled rectangle on an image
HOST_FUNCTION(void, draw_rectangle_on_image, (u32 destinationPtr, i32 posX, i32 posY, i32 width, i32 height, u32 colorPtr), {
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  // TODO
  free(color);
})

// Draw a filled triangle on an image
HOST_FUNCTION(void, draw_triangle_on_image, (u32 destinationPtr, i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, u32 colorPtr), {
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  // TODO
  free(color);
})

// Draw a filled ellipse on an image
HOST_FUNCTION(void, draw_ellipse_on_image, (u32 destinationPtr, i32 centerX, i32 centerY, i32 radiusX, i32 radiusY, u32 colorPtr), {
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  // TODO
  free(color);
})

// Draw a circle on an image
HOST_FUNCTION(void, draw_circle_on_image, (u32 destinationPtr, i32 centerX, i32 centerY, i32 radius, u32 colorPtr), {
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  // TODO
  free(color);
})

// Draw a filled polygon on an image
HOST_FUNCTION(void, draw_polygon_on_image, (u32 destinationPtr, i32 numPoints, u32 pointsPtr, u32 pointsLen, u32 colorPtr), {
  u8* points = copy_from_cart(pointsPtr, pointsLen);
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  // TODO
  free(points);
  free(color);
})

// Draw several lines on an image
HOST_FUNCTION(void, draw_polyline_on_image, (u32 destinationPtr, i32 numPoints, u32 pointsPtr, u32 pointsLen, u32 colorPtr), {
  u8* points = copy_from_cart(pointsPtr, pointsLen);
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  // TODO
  free(points);
  free(color);
})

// Draw a filled round-rectangle on an image
HOST_FUNCTION(void, draw_rectangle_rounded_on_image, (u32 destinationPtr, i32 x, i32 y, i32 width, i32 height, i32 cornerRadius, u32 colorPtr), {
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  // TODO
  free(color);
})

// Draw an image on an image
HOST_FUNCTION(void, draw_image_on_image, (u32 destinationPtr, u32 srcPtr, i32 posX, i32 posY), {
  // TODO
})

// Draw a tinted image on an image
HOST_FUNCTION(void, draw_image_tint_on_image, (u32 destinationPtr, u32 srcPtr, i32 posX, i32 posY, u32 tintPtr), {
  Color* tint = copy_from_cart(tintPtr, sizeof(Color));
  // TODO
  free(tint);
})

// Draw an image, rotated, on an image
HOST_FUNCTION(void, draw_image_rotated_on_image, (u32 destinationPtr, u32 srcPtr, i32 posX, i32 posY, f32 degrees, f32 offsetX, f32 offsetY, u32 filter), {
  // TODO
})

// Draw an image, flipped, on an image
HOST_FUNCTION(void, draw_image_flipped_on_image, (u32 destinationPtr, u32 srcPtr, i32 posX, i32 posY, bool flipHorizontal, bool flipVertical, bool flipDiagonal), {
  // TODO
})

// Draw an image, scaled, on an image
HOST_FUNCTION(void, draw_image_scaled_on_image, (u32 destinationPtr, u32 srcPtr, i32 posX, i32 posY, f32 scaleX, f32 scaleY, f32 offsetX, f32 offsetY, u32 filter), {
  // TODO
})

// Draw some text on an image
HOST_FUNCTION(void, draw_text_on_image, (u32 destinationPtr, u32 fontPtr, u32 textPtr, i32 posX, i32 posY, u32 colorPtr), {
  char* text = copy_from_cart_string(textPtr);
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  // TODO
  free(text);
  free(color);
})

// Draw a 1px outlined rectangle on the screen
HOST_FUNCTION(void, draw_rectangle_outline, (i32 posX, i32 posY, i32 width, i32 height, u32 colorPtr), {
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  // TODO
  free(color);
})

// Draw a 1px outlined triangle on the screen
HOST_FUNCTION(void, draw_triangle_outline, (i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, u32 colorPtr), {
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  // TODO
  free(color);
})

// Draw a 1px outlined ellipse on the screen
HOST_FUNCTION(void, draw_ellipse_outline, (i32 centerX, i32 centerY, i32 radiusX, i32 radiusY, u32 colorPtr), {
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  // TODO
  free(color);
})

// Draw a 1px outlined circle on the screen
HOST_FUNCTION(void, draw_circle_outline, (i32 centerX, i32 centerY, i32 radius, u32 colorPtr), {
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  // TODO
  free(color);
})

// Draw a 1px outlined polygon on the screen
HOST_FUNCTION(void, draw_polygon_outline, (i32 numPoints, u32 pointsPtr, u32 pointsLen, u32 colorPtr), {
  u8* points = copy_from_cart(pointsPtr, pointsLen);
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  // TODO
  free(points);
  free(color);
})

// Draw a 1px outlined arc on the screen
HOST_FUNCTION(void, draw_arc_outline, (i32 centerX, i32 centerY, f32 radius, f32 startAngle, f32 endAngle, i32 segments, u32 colorPtr), {
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  // TODO
  free(color);
})

// Draw a 1px outlined round-rectangle on the screen
HOST_FUNCTION(void, draw_rectangle_rounded_outline, (i32 x, i32 y, i32 width, i32 height, i32 cornerRadius, u32 colorPtr), {
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  // TODO
  free(color);
})

// Draw a 1px outlined rectangle on an image
HOST_FUNCTION(void, draw_rectangle_outline_on_image, (u32 destinationPtr, i32 posX, i32 posY, i32 width, i32 height, u32 colorPtr), {
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  // TODO
  free(color);
})

// Draw a 1px outlined triangle on an image
HOST_FUNCTION(void, draw_triangle_outline_on_image, (u32 destinationPtr, i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, u32 colorPtr), {
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  // TODO
  free(color);
})

// Draw a 1px outlined ellipse on an image
HOST_FUNCTION(void, draw_ellipse_outline_on_image, (u32 destinationPtr, i32 centerX, i32 centerY, i32 radiusX, i32 radiusY, u32 colorPtr), {
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  // TODO
  free(color);
})

// Draw a 1px outlined circle on an image
HOST_FUNCTION(void, draw_circle_outline_on_image, (u32 destinationPtr, i32 centerX, i32 centerY, i32 radius, u32 colorPtr), {
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  // TODO
  free(color);
})

// Draw a 1px outlined polygon on an image
HOST_FUNCTION(void, draw_polygon_outline_on_image, (u32 destinationPtr, i32 numPoints, u32 pointsPtr, u32 pointsLen, u32 colorPtr), {
  u8* points = copy_from_cart(pointsPtr, pointsLen);
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  // TODO
  free(points);
  free(color);
})

// Draw a 1px outlined round-rectangle on an image
HOST_FUNCTION(void, draw_rectangle_rounded_outline_on_image, (u32 destinationPtr, i32 x, i32 y, i32 width, i32 height, i32 cornerRadius, u32 colorPtr), {
  Color* color = copy_from_cart(colorPtr, sizeof(Color));
  // TODO
  free(color);
})
