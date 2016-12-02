/*
Author: Oleksiy Grechnyev, 2016
My simple operations with the buffer for jpeg image
If I cannot use objects like in Java, at least 
nobody can stop me from thinking objectively */


// The buffer for a JPEG image
// Contains size, number of bytes per pixel and the data 
typedef struct JPEGBuffer {
  
  int image_width;  // Image width in pixels
  int image_height; // Image height in pixels
  int bytes_per_pixel; // Bytes per bixel (3=RGB, 1=grayscale)  
  J_COLOR_SPACE color_space; // The color space used

  int tot_pixels; // Total number of pixels
  int tot_bytes; // Total number of bytes
  
  
  JSAMPLE * image_buffer;	// Points to a large array of RGB or BW data
} JPEGBuffer;

// Create a new buffer with given size, bytes per pixel and color space
// The buffer is initialized as black (0)
JPEGBuffer * jpbuf_create(int width, int height, int bytes, J_COLOR_SPACE cspace);

// Delete a buffer
void jpbuf_delete(JPEGBuffer *buffer);