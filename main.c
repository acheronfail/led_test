#include "common.h"
#include "color.c"

int main() {
  Display *display;
  int screen;
  Window window;
  XEvent event;
  XClassHint *class_hint;
  unsigned long black, white;
  int window_width = 1500;
  int window_height = 10;
  int screen_width, screen_height;
  int window_x, window_y;

  // Open connection to the X server
  display = XOpenDisplay(NULL);
  if (display == NULL) {
    fprintf(stderr, "Cannot open display\n");
    exit(1);
  }

  // Get the default screen of the display
  screen = DefaultScreen(display);
  black = BlackPixel(display, screen);
  white = WhitePixel(display, screen);

  // Get screen dimensions
  screen_width = DisplayWidth(display, screen);
  screen_height = DisplayHeight(display, screen);

  // Calculate position to center the window
  window_x = (screen_width - window_width) / 2;
  window_y = 10;

  // Create a window at the calculated position
  window = XCreateSimpleWindow(display, RootWindow(display, screen), window_x, window_y, window_width, window_height, 1,
                               black, white);

  // Set the window class
  // TIP: if you use `i3` use the following settings:
  //    no_focus [class="led_test"]
  //    for_window [class="led_test"] floating enable
  class_hint = XAllocClassHint();
  class_hint->res_name = "led_test";
  class_hint->res_class = "led_test";
  XSetClassHint(display, window, class_hint);

  struct timespec start_time;
  clock_gettime(CLOCK_MONOTONIC, &start_time);

  XMapWindow(display, window);
  XSetWindowBackground(display, window, 0x000000);

  while (1) {
    // flush any window events so the window can run
    while (XPending(display)) {
      XNextEvent(display, &event);
    }

    // get time in seconds since program start
    struct timespec current_time;
    clock_gettime(CLOCK_MONOTONIC, &current_time);
    float time = (current_time.tv_sec - start_time.tv_sec) + (current_time.tv_nsec - start_time.tv_nsec) / 1e9;

    // adjust time speed as necessary here
    time *= 0.5;

    uint8_t pos = (uint8_t)floorf(fmodf(time, 4.0f) * 255.0f);

    // set window color
    XSetWindowBackground(display, window, COLOR(pos));
    XClearWindow(display, window);

    usleep(1e6 / 30);
  }

  XFree(class_hint);
  XCloseDisplay(display);
  return 0;
}
