#include <stdlib.h>
#include <stdio.h>
#include <pnm.h>

int binarization(int min, int max, pnm in, pnm out){
  unsigned short *channel_in = pnm_get_channel(in, NULL, 0);
  unsigned short *channel_out = pnm_get_channel(out, NULL, 0);
  int cols = pnm_get_width(in);
  int rows = pnm_get_height(in);

  for (int i = 0; i < cols*rows; ++i){
    if (channel_in[i] >= min && channel_in[i] <= max){
      channel_out[i] = 255;
    }
    else {
      channel_out[i] = 0;
    }
  }

  for (int i = 0; i <3; ++i){
    pnm_set_channel(out, channel_out, i);
  }
  
  free(channel_in); free(channel_out);
  return EXIT_FAILURE;
}

void usage(char* s){
  fprintf(stderr, "%s <min> <max> <ims> <imd>\n", s);
  exit(EXIT_FAILURE);
}

#define PARAM 4

int main(int argc, char* argv[]){
  if (argc != PARAM+1) usage(argv[0]);
  pnm in = pnm_load(argv[3]);
  pnm out = pnm_new(pnm_get_width(in), pnm_get_height(in), PnmRawPpm);
  binarization(atoi(argv[1]), atoi(argv[2]), in, out);
  pnm_save(out, PnmRawPpm, argv[4]);
  pnm_free(in);
  pnm_free(out);
  return EXIT_SUCCESS;
}
