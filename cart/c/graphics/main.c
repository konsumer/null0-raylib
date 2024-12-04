#include "cart.h"

void update(uint64_t timeMS) {
  clear(BLACK);
  draw_rectangle(50, 50, 100, 50, GREEN);
  draw_line(50, 50, 100, 100, BLUE);
  draw_line(100, 100, 150, 50, BLUE);
  draw_ellipse(320, 240, 100, 50, YELLOW);
}

int main(int argc, char *argv[]) {
  return 0;
}