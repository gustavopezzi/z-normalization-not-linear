#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "vector.h"
#include "matrix.h"

#define NUM_POINTS 50
#define Z_OFFSET 5

vec4_t vertices[NUM_POINTS];
mat4_t projmatrix;

int main(void) {
  // Create several vertices starting from z=10, incrementing the depth by 5 units each time
  float z = 10.0;
  for (int i = 0; i < NUM_POINTS; i++) {
    vertices[i].x = 0.0f;
    vertices[i].y = 0.0f;
    vertices[i].z = z;
    vertices[i].w = 1.0f;
    z += Z_OFFSET;
  }

  // Initialize the perspective projection matrix
  int screen_width = 800;
  int screen_height = 800;
  float aspect = screen_height / screen_width;
  float fov = 3.141592 / 3.0; // 60 degrees
  float znear = 10.0f;
  float zfar = 260.0f;
  
  // Initialize the projection matrix
  // | (h/w)*1/tan(fov/2)             0              0                 0 |
  // |                  0  1/tan(fov/2)              0                 0 |
  // |                  0             0     zf/(zf-zn)  (-zf*zn)/(zf-zn) |
  // |                  0             0              1                 0 |
  projmatrix = mat4_make_perspective(fov, aspect, znear, zfar);

  // Multiply all the vertices by the projection matrix
  vec4_t projected_points[NUM_POINTS];
  for (int i = 0; i < NUM_POINTS; i++) {
    // Project the current vertex using a perspective projection matrix
    projected_points[i] = mat4_mul_vec4(&projmatrix, &vertices[i]);

    // Perform perspective divide
    if (projected_points[i].w != 0) {
        projected_points[i].x /= projected_points[i].w;
        projected_points[i].y /= projected_points[i].w;
        projected_points[i].z /= projected_points[i].w;
    }
  }

  // Output the resulting remapped depth values after the normalization
  printf("i;original-depth;normalized-depth\n");
  for (int i = 0; i < NUM_POINTS; i++) {
    printf("%f;%f\n", vertices[i].z, projected_points[i].z);
  }

  return 0;
}
