#include <math.h>

#include <morphology.h>
#include <se.h>

void
maximum(unsigned short *val, unsigned short *max){
  if (val > max) max = val;
}

void
minimum(unsigned short *val, unsigned short *min){
  if(val < min) min = val;
}

void
process(int s, int hs, pnm ims, pnm imd,
        void (*pf)(unsigned short*, unsigned short*))
{
  int cols = pnm_get_width(ims);
  int rows = pnm_get_height(imd);
  pnm img1 = se(s, hs);



  pnm_free(img1); pnm_free(img2); pnm_free(img3);
  puts(">> morphology.c");
}
