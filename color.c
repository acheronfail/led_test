#include "common.h"

// NOTE: set COLOR to whichever function you'd like to use to set the color
#define COLOR color_wheel

inline static float taylor_series(float zero_to_tau) {
  float x = (-0.5 * zero_to_tau) + 2.4;
  float x3 = x * x * x;
  float x5 = x3 * x * x;
  float r = fabs(x - (x3 / 6.0) + (x5 / 120.0));
  return fminf(r, 1.0f);
}

static uint32_t color_wheel3(uint8_t pos) {
  float norm = (float)pos / 255.0;
  float r = taylor_series((norm + 0.0 / 3.0) * TAU);
  float b = taylor_series((norm + 1.0 / 3.0) * TAU);
  float g = taylor_series((norm + 2.0 / 3.0) * TAU);
  return ((uint8_t)(r * 255) << 16) | ((uint8_t)(g * 255) << 8) | (uint8_t)(b * 255);
}

static uint32_t color_wheel2(uint8_t pos) {
  float norm = (float)pos / 255.0;
  float r = sqrtf(sinf((norm + 0.0 / 3.0) * TAU) * 0.5 + 0.5);
  float b = sqrtf(sinf((norm + 1.0 / 3.0) * TAU) * 0.5 + 0.5);
  float g = sqrtf(sinf((norm + 2.0 / 3.0) * TAU) * 0.5 + 0.5);
  printf("r = %.4f\n", r);
  return ((uint8_t)(r * 255) << 16) | ((uint8_t)(g * 255) << 8) | (uint8_t)(b * 255);
}

static uint32_t color_wheel(uint8_t pos) {
  pos = 255 - pos;
  if (pos < 85) {
    return ((uint32_t)(255 - pos * 3) << 16) | ((uint32_t)0 << 8) | (pos * 3);
  } else if (pos < 170) {
    pos -= 85;
    return ((uint32_t)0 << 16) | ((uint32_t)(pos * 3) << 8) | (255 - pos * 3);
  } else {
    pos -= 170;
    return ((uint32_t)(pos * 3) << 16) | ((uint32_t)(255 - pos * 3) << 8) | 0;
  }
}