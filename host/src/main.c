// basic stuff that gets used all over
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <raylib.h>

#ifdef _WINDOWS
#include <windows.h>
#else
#include <unistd.h>
#define sleep(x) usleep((x)*1000)
#endif

#define CVECTOR_LOGARITHMIC_GROWTH
#include "cvector.h"

// filesystem utils (used by host)
#include "fs.h"

// set this to false to stop
bool keepRunning = true;

// host implementations for emscripten/wamr
#include "host.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <CART_FILE>\n", argv[0]);
    return 1;
  }

  if (!fs_init(argv[1])) {
    fprintf(stderr, "Could not initialize filesystem with %s\n", argv[1]);
    return 1;
  }

  DetectFileType d = fs_detect_type_real(argv[1]);

  if (d == FILE_TYPE_UNKNOWN) {
    fprintf(stderr, "Invalid cart %s\n", argv[1]);
    return 1;
  }

  char* cartFilename = d == FILE_TYPE_WASM ? basename(argv[1]) : "main.wasm";
  if (!wasm_host_load(cartFilename)) {
    fprintf(stderr, "Could not start cart-host with %s\n", argv[1]);
    return 1;
  }

  SetTraceLogLevel(LOG_ERROR);

  InitWindow(640, 480, "null0");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    wasm_host_update();
    EndDrawing();
  }

  CloseWindow();

  wasm_host_unload();
  return 0;
}
