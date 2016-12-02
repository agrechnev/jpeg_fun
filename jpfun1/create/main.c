/* By Oleksiy Grechnyev, 2016
   Create two simple image buffers and save them as RGB JPEG files
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "jpeglib.h"

#include "jpbuf.h"
#include "jpio.h"

int main(){
 printf("Setting up the buffer !\n");
 

 int image_width=700;
 int image_height=400;
 
 // Create a new RGB buffer
 JPEGBuffer *buffer=jpbuf_create(image_width, image_height, 3, JCS_RGB);  
 JSAMPLE *ibuffer=buffer->image_buffer; // The raw data

 // Fill the buffer
 // While it would be tempting to define a function like set_pixel()
 // I opt not to for performance reasons

 int i,j; // for loop indices

 for (i=0;i<image_height;i++) // Loop over rows
  for (j=0;j<image_width;j++) {   // Loop over columns
    int index=(i*image_width+j)*3; // Index of pixel in the buffer

    // Make some nice color pattern here
    ibuffer[index]=  256*i/image_height;  //R
    ibuffer[index+1]=  256*j/image_width; //G
    ibuffer[index+2]= 100;  //B
  }

 // Write the buffer
 printf("Writing the buffer !\n"); 

 jpio_write(buffer,"image1.jpg",255);

 // Now let us modify the buffer a bit
 // We add some random noise in a middle circle, sort of

 // Seed the random number generator
 srand((unsigned) time(NULL));
 
 for (i=0;i<image_height;i++) // Loop over rows
  for (j=0;j<image_width;j++) {   // Loop over columns
    int index=(i*image_width+j)*3; // Index of pixel in the buffer

    // Distance^2 in pixels
    int dist2=(j-image_width/2)*(j-image_width/2) + (i-image_height/2)*(i-image_height/2);
    int radius2=100*100;
    if (dist2<radius2) {
     ibuffer[index]+= rand()%40-20;  //R
     ibuffer[index+1]+= rand()%40-20; //G
     ibuffer[index+2]+= rand()%40-20;  //B
    }
  }

 // And we save it again with a new name
 jpio_write(buffer,"image2.jpg",255);

 // Free memory
 jpbuf_delete(buffer);
 buffer=NULL;
 ibuffer=NULL;

 return 0;
}

void  put_scanline_someplace(JSAMPARRAY buf, int row_stride){};