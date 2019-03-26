#include <stdlib.h>
#include <math.h>

#include <bcl.h>
#include <se.h>

enum {SQUARE, DIAMOND, DISK, LINE_V, DIAG_R, LINE_H, DIAG_L, CROSS, PLUS};


void
makeSquare(int cols, int rows, unsigned short* pix) {
  for (int i = 0; i < cols*rows; i++){
    pix[i] = 255;
  }
}

void
makeDiamond(int cols, int rows, int hs, unsigned short* pix) {
  for (int i = 0; i < cols; i++){
    for (int j = 0; j < rows; j++){
      if (abs(i-hs)+abs(hs-j)<= hs)
        pix[i*rows+j] = 255;
    }
  }
}

void
makeDisk(int cols, int rows, int hs, unsigned short* pix) {
  for (int i = 0; i < cols; i++){
    for (int j = 0; j < rows; j++){
      if (sqrt((i-hs)*(i-hs)+(hs-j)*(hs-j))<= hs)
        pix[i*rows+j] = 255;
    }
  }
}

void
makeLineV(int cols, int rows, int hs, unsigned short* pix) {
  for (int i = 0; i < rows; i++)
    pix[i*cols+hs] = 255;
}

void
makeDiagR(int cols, unsigned short* pix) {
  for (int i = cols-1; i >= 0; i--)
    pix[i*cols-i] = 255;
}

void
makeLineH(int rows, int hs, unsigned short* pix) {
  for (int i = 0; i < rows; i++)
    pix[hs*rows+i] = 255;
}

void
makeDiagL(int cols, unsigned short* pix) {
  for (int i = 0; i < cols; i++)
    pix[i*cols+i] = 255;
}


pnm
se(int s, int hs){
  int cols = 2*hs +1;
  int rows = 2*hs +1;
  pnm ims = pnm_new(cols, rows, PnmRawPpm);
  unsigned short *pix = pnm_get_channel(ims, NULL, 0);

  if (s == SQUARE){
    makeSquare(cols, rows, pix);
  }
  else if (s == DIAMOND){
    makeDiamond(cols, rows, hs, pix);
  }
  else if (s == DISK){
    makeDisk(cols, rows, hs, pix);
  }
  else if (s == LINE_V) {
    makeLineV(cols, rows, hs, pix);
  }
  else if (s == DIAG_R) {
    makeDiagR(cols, pix);
  }
  else if (s == LINE_H) {
    makeLineH(rows, hs, pix);
  }
  else if (s == DIAG_L) {
    makeDiagL(cols, pix);
  }
  else if (s == CROSS) {
    makeDiagL(cols, pix);
    makeDiagR(cols, pix);
  }
  else if (s == PLUS) {
    makeLineH(rows, hs, pix);
    makeLineV(cols, rows, hs, pix);
  }

  pnm_set_channel(ims,pix,0);
  pnm_set_channel(ims,pix,1);
  pnm_set_channel(ims,pix,2);

  free(pix);
  return ims;
}
