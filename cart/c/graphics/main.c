#include "cart.h"

void update(uint64_t timeMS) {
  clear(BLACK);
  
  // shirt
  draw_rectangle(270, 320, 100, 100, GREEN);
  draw_line(320, 340, 320, 420, RED);

  // pants
  draw_rectangle(270, 420, 100, 100, BLUE);
  draw_line(320, 440, 320, 480, BLACK);
    
  // head
  draw_circle(320, 240, 100, YELLOW);

  // eyes
  draw_circle(280, 200, 10, BLACK);
  draw_circle(360, 200, 10, BLACK);

  // bill
  draw_ellipse(320, 260, 50, 10, ORANGE);
  draw_line(280, 260, 360, 260, RED);
}

int main(int argc, char *argv[]) {
  return 0;
}