#include <stdlib.h>
#include <stdio.h>

#include <morphology.h>

void
usage(char* s)
{
  fprintf(stderr,"%s <se> <hs> <ims> <imd>\n",s);
  exit(EXIT_FAILURE);
}

#define PARAM 4
int
main(int argc, char* argv[])
{
  if(argc != PARAM+1) usage(argv[0]);
  pnm in = pnm_load(argv[3]);
  pnm out = pnm_new(pnm_get_width(in),pnm_get_height(in), PnmRawPpm);
  process(atoi(argv[1]), atoi(argv[2]), in, out, maximum);
  process(atoi(argv[1]), atoi(argv[2]), out, out, minimum);


  pnm_save(out,PnmRawPpm,argv[4]);

  pnm_free(in);
  pnm_free(out);

  return EXIT_SUCCESS;
}
