#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>
#include "vector.h"

typedef struct {
    float m[4][4];
} mat4_t;

static inline vec4_t mat4_mul_vec4(mat4_t* m, vec4_t* v) {
  vec4_t result;
  result.x = m->m[0][0] * v->x + m->m[0][1] * v->y + m->m[0][2] * v->z + m->m[0][3] * v->w;
  result.y = m->m[1][0] * v->x + m->m[1][1] * v->y + m->m[1][2] * v->z + m->m[1][3] * v->w;
  result.z = m->m[2][0] * v->x + m->m[2][1] * v->y + m->m[2][2] * v->z + m->m[2][3] * v->w;
  result.w = m->m[3][0] * v->x + m->m[3][1] * v->y + m->m[3][2] * v->z + m->m[3][3] * v->w;
  return result;
}

static inline mat4_t mat4_mul_mat4(mat4_t* a, mat4_t* b) {
  mat4_t m;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      m.m[i][j] = a->m[i][0] * b->m[0][j] + a->m[i][1] * b->m[1][j] + a->m[i][2] * b->m[2][j] + a->m[i][3] * b->m[3][j];
    }
  }
  return m;
}

static inline mat4_t mat4_make_perspective(float fov, float aspect, float znear, float zfar) {
  // | (h/w)*1/tan(fov/2)             0              0                 0 |
  // |                  0  1/tan(fov/2)              0                 0 |
  // |                  0             0     zf/(zf-zn)  (-zf*zn)/(zf-zn) |
  // |                  0             0              1                 0 |
  mat4_t m = {{{ 0 }}};
  m.m[0][0] = aspect * (1 / tan(fov / 2));
  m.m[1][1] = 1 / tan(fov / 2);
  m.m[2][2] = zfar / (zfar - znear);
  m.m[2][3] = (-zfar * znear) / (zfar - znear);
  m.m[3][2] = 1.0;
  return m;
}

#endif