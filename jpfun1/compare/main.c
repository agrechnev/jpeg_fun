#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "jpeglib.h"

#include "jpbuf.h"
#include "jpio.h"

int main(int argc, char *argv[]){

 int imin(int x, int y){ 
  return x<y ? x:y;
 }

 // Check if 2 file names are supplied
 if (argc<3) {
  printf("Compare 2 jpeg files\n");
  printf("Usage: \n");
  printf("jpcompare <file1> <file2>\n");
  exit(0);
 }
 
 // Read the 2 files
 printf("Reading the input files!\n");

 JPEGBuffer *buffer1 = jpio_read(argv[1]);  
 JPEGBuffer *buffer2 = jpio_read(argv[2]);

 
 printf("\n%s :\n\n",argv[1]);
 printf("width=%d\n",buffer1->image_width);
 printf("height=%d\n",buffer1->image_height);

 
 printf("\n%s :\n\n",argv[2]);
 printf("width=%d\n",buffer2->image_width);
 printf("height=%d\n",buffer2->image_height);

 if ( buffer1->image_width != buffer2->image_width ||
      buffer1->image_height != buffer2->image_height ) {
   printf("\n Warning ! \n\n");
   printf("\n Image size differ ! \n\n");
   printf("\n Using minimal values for comparison. \n\n");
 }

 // Get the minimum size
 int  image_width = imin(buffer1->image_width, buffer2->image_width);
 int image_height = imin(buffer1->image_height, buffer2->image_height);
 
 // Create a new grayscale bufffer for output
 JPEGBuffer *buffer_out = jpbuf_create(image_width, image_height, 3, JCS_RGB); 
 
 // Raw data
 JSAMPLE *ibuf1=buffer1->image_buffer;
 JSAMPLE *ibuf2=buffer2->image_buffer;
 JSAMPLE *ibuf_o=buffer_out->image_buffer;

 int i,j; // for loop indices


 // As usual I don't use many per-pixel functions calls to maximize efficiency
 for (i=0;i<image_height;i++) // Loop over rows
  for (j=0;j<image_width;j++) {   // Loop over columns
    int ind1=(i*buffer1->image_width+j)*3; // Index of pixel in the input buffers
    int ind2=(i*buffer2->image_width+j)*3; 
    int indo=(i*image_width+j)*3; // Index of pixel in the output buffer

    // Make the comparison
    int r1= (int) ibuf1[ind1];
    int r2= (int) ibuf2[ind2];
    int g1= (int) ibuf1[ind1+1];
    int g2= (int) ibuf2[ind2+1];
    int b1= (int) ibuf1[ind1+2];
    int b2= (int) ibuf2[ind2+2];

    // Calculate the distance
    // Comparison algorithms can vary, this is the simplest one
    JSAMPLE dist= (JSAMPLE)( (abs(r1-r2) + abs(g1-g2) + abs(b1-b2))/3);

    // Write the  data to the output buffer
    ibuf_o[indo]=dist;
    ibuf_o[indo+1]=dist;
    ibuf_o[indo+2]=dist;
  }

 // Write the buffer
 printf("Writing the buffer !\n"); 

 jpio_write(buffer_out,"result.jpg",255);
 
 // Free memory
 jpbuf_delete(buffer1);
 jpbuf_delete(buffer2);
 jpbuf_delete(buffer_out);

 return 0;
}

void  put_scanline_someplace(JSAMPARRAY buf, int row_stride){};