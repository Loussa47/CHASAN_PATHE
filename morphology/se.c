#include <stdlib.h>
#include <math.h>

#include <bcl.h>
#include <se.h>

enum {SQUARE, DIAMOND, DISK, LINE_V, DIAG_R, LINE_H, DIAG_L, CROSS, PLUS};


pnm
se(int s, int hs){
  int cols = 2*hs +1;
  int rows = 2*hs +1;
  pnm ims = pnm_new(cols, rows, PnmRawPpm);
  unsigned short *pix = pnm_get_channel(ims, NULL, 0);
  if (s == SQUARE){
    for (int i = 0; i < cols*rows; i++){
      pix[i] = 255;
    }
  }
  else if (s == DIAMOND){
    for (int i = 0; i < cols; i++){
      for (int j = 0; j < rows; j++){
        if (abs(i-hs)+abs(hs-j)<= hs){
          pix[i*rows+j] = 255;
        }
      }
    }
  }
  else if (s == DISK){
    for (int i = 0; i < cols; i++){
      for (int j = 0; j < rows; j++){
        if (sqrt((i-hs)*(i-hs)+(hs-j)*(hs-j))<= hs){
          pix[i*rows+j] = 255;
        }
      }
    }
  }
  else if (s == LINE_V) {
    for (int i = 0; i < rows; i++){
      pix[i*cols+hs] = 255;
    }
  } else if (s == DIAG_R) {
    for (int i = cols-1; i >= 0; i--){
      pix[i*cols-i] = 255;
    }
  } else if (s == LINE_H) {
    for (int i = 0; i < rows; i++){
      pix[hs*rows+i] = 255;
    }
  } else if (s == DIAG_L) {
    for (int i = 0; i < cols; i++){
      pix[i*cols+i] = 255;
    }
  } else if (s == CROSS) {
    for (int i = cols-1; i >= 0; i--){
      pix[i*cols-i] = 255;
    }
    for (int i = 0; i < cols; i++){
      pix[i*cols+i] = 255;
    }
  } else if (s == PLUS) {
for (int i = 0; i < rows; i++){
      pix[i*cols+hs] = 255;
      pix[hs*rows+i] = 255;
    }
  }

  pnm_set_channel(ims,pix,0);
  pnm_set_channel(ims,pix,1);
  pnm_set_channel(ims,pix,2);

  free(pix);
  return ims;
}
