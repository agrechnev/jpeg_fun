/* By Oleksiy Grechnyev, 2016
  Read and write jpeg images using libjpeg 9
  loosely based on example.c from libjpeg
 */


// Write a buffer as a jpeg file
void jpio_write(JPEGBuffer *buffer, char* file_name, int quality);