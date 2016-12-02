/*
Author: Oleksiy Grechnyev, 2016
My simple operations with the buffer for jpeg image
If I cannot use objects like in Java, at least 
nobody can stop me from thinking objectively */

#include <stdio.h>
#include <stdlib.h>
#include "jpeglib.h"

#include "jpbuf.h"

// Create a new buffer with given size, bytes per pixel and color space
// The buffer is initialized as black (0)
JPEGBuffer * jpbuf_create(int width, int height, int bytes, J_COLOR_SPACE cspace){
  // Allocate mem
  JPEGBuffer *result=(JPEGBuffer *)malloc(sizeof(JPEGBuffer));

  // Set fields
  result->image_width=width;
  result->image_height=height;
  result->bytes_per_pixel=bytes;
  result->color_space=cspace;
  
  result->tot_pixels=width*height;
  result->tot_bytes=width*height*bytes;

  // Allocate the buffer, initializing with 0
  result->image_buffer=(JSAMPLE *)calloc(result->tot_bytes,sizeof(JSAMPLE));
}

// Delete a buffer
void jpbuf_delete(JPEGBuffer *buffer){
  free(buffer->image_buffer);
  free(buffer);
}