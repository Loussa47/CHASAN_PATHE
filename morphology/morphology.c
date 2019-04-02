#include <math.h>

#include <morphology.h>
#include <se.h>

void
maximum(unsigned short *val, unsigned short *max){
  if (*val > *max){
    *max = *val;
  }
}

void
minimum(unsigned short *val, unsigned short *min){
  if(*val < *min) *min = *val;
}

void
process(int s, int hs, pnm ims, pnm imd,
        void (*pf)(unsigned short*, unsigned short*))
{
  pnm shape = se(s, hs);

  unsigned short * pixel_shape = pnm_get_channel(shape,NULL,0);

  unsigned short * channel = pnm_get_channel(ims, NULL, 0);
  unsigned short * channel_out = pnm_get_channel(ims, NULL, 0);

  int cols = pnm_get_width(ims);
  int rows = pnm_get_height(ims);

  int i_shape;
  int j_shape;
  unsigned short tmp;
  int i,j;

  for(int index = 0 ; index < cols*rows ; index++){

      i = index%cols;
      j = index/cols;

      i_shape = 0;
      tmp = channel[index];
      for(int h_i = -hs ; h_i <= hs ; h_i++){
        j_shape = 0;
        for(int h_j = -hs ; h_j <= hs ; h_j++){
          if(i + h_i >= 0 && i + h_i < cols && j + h_j>= 0 && j + h_j < rows){
              if(pixel_shape[i_shape*(2*hs+1) +j_shape] == 255){
                pf(&(channel[(h_i + i) + cols * (h_j + j)]),&tmp);
              }
          }
          j_shape++;
        }
        i_shape++;

      }
      channel_out[index] = tmp;


  }

  pnm_set_channel(imd, channel_out, 0);
  pnm_set_channel(imd, channel_out, 1);
  pnm_set_channel(imd, channel_out, 2);


  pnm_free(shape);
  free(pixel_shape);
  free(channel); free(channel_out);
  puts(">> morphology.c");
}
