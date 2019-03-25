#include <stdlib.h>
#include <stdio.h>

#include <morphology.h>

void
usage(char* s)
{
  fprintf(stderr,"%s <ims-1> <ims-2> <imd>\n",s);
  exit(EXIT_FAILURE);
}

#define PARAM 3
int
main(int argc, char* argv[])
{
  if(argc != PARAM+1) usage(argv[0]);
  pnm in1 = pnm_load(argv[1]);
  pnm in2 = pnm_load(argv[2]);

  int cols = pnm_get_width(in1);
  int rows = pnm_get_height(in1);

  pnm out = pnm_new(cols ,rows , PnmRawPpm);

  unsigned short * channel_1 = pnm_get_channel(in1, NULL, 0);
  unsigned short * channel_2 = pnm_get_channel(in2, NULL, 0);
  unsigned short * channel_out = pnm_get_channel(out, NULL, 0);

  for (int i = 0; i < cols *rows; i++){
    channel_out[i] = channel_1[i] + channel_2[i];
    if (channel_out[i] > 255) channel_out[i] = 255;
  }

  pnm_set_channel(out, channel_out, 0);
  pnm_set_channel(out, channel_out, 1);
  pnm_set_channel(out, channel_out, 2);

  pnm_save(out,PnmRawPpm,argv[3]);

  pnm_free(in1);
  pnm_free(in2);
  pnm_free(out);

  free(channel_1); free(channel_2); free(channel_out);

  return EXIT_SUCCESS;
}
