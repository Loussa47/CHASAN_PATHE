#include <stdlib.h>
#include <stdio.h>

#include <bcl.h>


double
laplacien(double * channel, int i,int j, int cols, int rows){
  double u = channel[i*rows+j];
  double u1,u2,u3,u4;

  if(i+1 >= cols){
    u1 = channel[(i-1)*rows+j];
  }else{
    u1 = channel[(i+1)*rows+j];
  }

  if(i-1 < 0){
    u2 = channel[(i+1)*rows+j];
  }else{
    u2 = channel[(i-1)*rows+j];
  }

  if(j+1 >= rows){
    u3 = channel[i*rows+(j-1)];
  }else{
    u3 = channel[i*rows+(j+1)];
  }

  if(j-1 < 0){
    u4 = channel[i*rows+(j+1)];
  }else{
    u4 = channel[i*rows+(j-1)];
  }

  return u1 + u2 + u3 + u4 - 4 * u;
}

void
process(int n, char *ims, char *imd)
{
  pnm in = pnm_load(ims);
  int cols = pnm_get_width(in);
  int rows = pnm_get_height(in);

  pnm out = pnm_new(cols,rows,PnmRawPpm);

  unsigned short * channel_in = pnm_get_channel(in,NULL,0);

  double * channel_prev = (double*)malloc(rows*cols*sizeof(double));
  double * channel_next = (double*)malloc(rows*cols*sizeof(double));
  double * tmp;

  double lap;
  int it = 1;

  //itération 0
  for(int i = 0 ; i < cols ; i++){
    for(int j = 0 ; j < rows ; j++){
      channel_prev[i*rows+j] = (double) channel_in[i*rows+j];
    }
  }


  while (n != it){

    for(int i = 0 ; i < cols ; i++){
      for(int j = 0 ; j < rows ; j++){
        lap = laplacien(channel_prev,i,j,cols,rows);
        channel_next[i*rows+j] = (0.25 * lap) + channel_prev[i*rows+j];
      }
    }
    it++;

    /* Switch prev/next for next iteration */
    tmp = channel_prev;
    channel_prev = channel_next;
    channel_next = tmp;

  }

  for(int i = 0 ; i < cols ; i++){
    for(int j = 0 ; j < rows ; j++){
      channel_in[i*rows+j] = channel_prev[i*rows+j];
      //Normalisation
      if(channel_in[i*rows+j] > 255) channel_in[i*rows+j] = 255;

    }
  }

  pnm_set_channel(out, channel_in,0);
  pnm_set_channel(out, channel_in,1);
  pnm_set_channel(out, channel_in,2);

  /* SAVE & FREE*/

  pnm_save(out, PnmRawPpm, imd);

  pnm_free(in); pnm_free(out);
  free(channel_prev); free(channel_next);
  free(channel_in);

}

void
usage (char *s){
  fprintf(stderr, "Usage: %s <n> <ims> <imd>\n", s);
  exit(EXIT_FAILURE);
}

#define PARAM 3
int
main(int argc, char *argv[]){
  if (argc != PARAM+1) usage(argv[0]);
  process(atoi(argv[1]), argv[2], argv[3]);
  return EXIT_SUCCESS;
}
