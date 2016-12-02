/* By Oleksiy Grechnyev, 2016
  Read and write jpeg images using libjpeg 9
  loosely based on example.c from libjpeg
 */

#include <stdio.h>
#include <stdlib.h>
#include "jpeglib.h"

#include "jpbuf.h"

// Write a buffer as a jpeg file
void jpio_write(JPEGBuffer *buffer, char* file_name, int quality){
  
   // Compression params
   struct jpeg_compress_struct cinfo;
   // Error handler
   struct jpeg_error_mgr jerr;

   FILE * outfile;  // Output file
   JSAMPROW row_pointer[1];	/* pointer to JSAMPLE row[s] */
   int row_stride;		/* physical row width in image buffer */

   cinfo.err = jpeg_std_error(&jerr);
   /* Now we can initialize the JPEG compression object. */
   jpeg_create_compress(&cinfo);

   // Try to open the output file
   if ((outfile = fopen(file_name, "wb")) == NULL) {
     fprintf(stderr, "can't open %s\n", file_name);
     exit(1);
   }
   jpeg_stdio_dest(&cinfo, outfile);

   //---------------------------------------------
   // Set up the parameters
   cinfo.image_width = buffer->image_width;
   cinfo.image_height = buffer->image_height;
   
   cinfo.input_components = 3;		/* # of color components per pixel */
   cinfo.in_color_space = buffer->color_space; 	/* colorspace of input image */
   row_stride=cinfo.image_width*cinfo.input_components; // # of bytes/row

   jpeg_set_defaults(&cinfo); // Set other defaults
  
   // Set quality
   jpeg_set_quality(&cinfo, quality, TRUE /* limit to baseline-JPEG values */);
   //-------------------------------------------------------
   // Run the compressor
   jpeg_start_compress(&cinfo, TRUE);  // Start it

   // Run the scan lines
   while (cinfo.next_scanline < cinfo.image_height) {
    /* jpeg_write_scanlines expects an array of pointers to scanlines.
     * Here the array is only one element long, but you could pass
     * more than one scanline at a time if that's more convenient.
     */
    row_pointer[0] = & buffer->image_buffer[cinfo.next_scanline * row_stride];
    (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
   }
   
   // Finish compression
   jpeg_finish_compress(&cinfo);
   
   fclose(outfile); // Close the output file
 
   jpeg_destroy_compress(&cinfo); // Destroy cinfo    
}