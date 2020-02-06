#include <IL/il.h>
#include <IL/ilu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>

#define PAGESIZE 0x400
#define GFXRED 0x91
#define GFXGREEN 0x92
#define GFXYELLOW 0x93
#define GFXBLUE 0x94
#define GFXMAGENTA 0x95
#define GFXCYAN 0x96
#define GFXWHITE 0x97
#define GFXOFFSET 0xA0
#define GFXWIDTH 78
#define GFXHEIGHT 75

int main(int argc, char **argv)
{
  ILuint  ImgId;
  ILuint  ImgOutId;
  ILenum  Error;

  long x;
  long y;
  unsigned char *imdata;
  unsigned char outchar;

  // First parameter is input
  if (argc<2)
  {
    return 1;
  }

  // Check if the shared lib's version matches the executable's version.
  if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION ||
    iluGetInteger(ILU_VERSION_NUM) < ILU_VERSION)
  {
    fprintf(stderr, "DevIL version is different...exiting\n");
    return 2;
  }

  // Initialize DevIL.
  ilInit();
  iluInit();

  // Ensure loaded image format is RGB
  ilSetInteger(IL_FORMAT_MODE, IL_RGB);
  ilEnable(IL_FORMAT_SET);

  // Ensure loaded image type is in unsigned 8 bit
  ilSetInteger(IL_TYPE_MODE, IL_UNSIGNED_BYTE);
  ilEnable(IL_TYPE_SET);

  // Generate the main image name to use.
  ilGenImages(1, &ImgId);

  // Bind this image name.
  ilBindImage(ImgId);

  // Loads the image specified by File into the image named by ImgId.
  if (!ilLoadImage(argv[1]))
  {
    fprintf(stderr, "\nCould not open file... %s\n", argv[1]);
    return 4;
  }

  // Scale input image
  iluImageParameter(ILU_FILTER, ILU_SCALE_TRIANGLE);
  iluScale(GFXWIDTH, GFXHEIGHT, ilGetInteger(IL_IMAGE_DEPTH));

  // Set quantization parameters
  ilSetInteger(IL_QUANTIZATION_MODE, IL_WU_QUANT);
  ilSetInteger(IL_MAX_QUANT_INDICES, 2);

  // Convert the scaled image to 8 bit indexed
  ilConvertImage(IL_COLOUR_INDEX, IL_UNSIGNED_BYTE);

  // Convert image to page format
  imdata=ilGetData();
  for (y=0; y<(GFXHEIGHT/3); y++)
  {
    fprintf(stdout, "%c", GFXWHITE);

    for (x=0; x<(GFXWIDTH/2); x++)
    {
      // Determine character to use
      outchar=GFXOFFSET;

      if (imdata[((y*3)*GFXWIDTH)+(x*2)]!=0) outchar|=1;
      if (imdata[((y*3)*GFXWIDTH)+(x*2)+1]!=0) outchar|=2;

      if (imdata[(((y*3)+1)*GFXWIDTH)+(x*2)]!=0) outchar|=4;
      if (imdata[(((y*3)+1)*GFXWIDTH)+(x*2)+1]!=0) outchar|=8;

      if (imdata[(((y*3)+2)*GFXWIDTH)+(x*2)]!=0) outchar|=16;
      if (imdata[(((y*3)+2)*GFXWIDTH)+(x*2)+1]!=0) outchar|=64;

      fprintf(stdout, "%c", outchar);
    }
  }

  // Add filler to make it multiple of 0x100
  for (x=0; x<24; x++)
    fprintf(stdout, "%c", 0);

  return 0;
}
