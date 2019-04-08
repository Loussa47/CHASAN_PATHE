#include <stdlib.h>
#include <stdio.h>

#include <bcl.h>
#include <math.h>

double
c0(){
  return 1.f;
}

double
c1(double s){
  return 1/(1+(s*s));
}

double
c2(double s){
  return exp(-(s*s));
}

double
div1(double * p1, double * p2, int i, int j, int rows, double c){

  double a,b;

  if(i-1 < 0){
    a = p1[i*rows+j] - p1[(i+1)*rows+j];
  }else{
    a = p1[i*rows+j] - p1[(i-1)*rows+j];
  }

  if(j-1 < 0){
    b = p2[i*rows+j] - p2[i*rows+j+1];
  }else{
    b = p2[i*rows+j] - p2[i*rows+j-1];
  }

  return c*a + c*b;
}

void
calculateGradient(double * u1, double * u2, double * u, int cols, int rows){

  for(int i = 0 ; i < cols ; i++){
    for(int j = 0 ; j < rows ; j++){

      if(i+1 >= cols){
        u1[i*rows+j] = u[(i-1)*rows+j] - u[i*rows+j];
      }else{
        u1[i*rows+j] = u[(i+1)*rows+j] - u[i*rows+j];
      }

      if(j+1 >= rows){
        u2[i*rows+j] = u[i*rows+j-1] - u[i*rows+j];
      }else{
        u2[i*rows+j] = u[i*rows+j-1] - u[i*rows+j];
      }

    }
  }
}

void
process(int n, int lambda, int function, char *ims, char *imd)
{
  pnm in = pnm_load(ims);
  int cols = pnm_get_width(in);
  int rows = pnm_get_height(in);

  pnm out = pnm_new(cols,rows,PnmRawPpm);

  unsigned short * channel_in = pnm_get_channel(in,NULL,0);

  double * u = (double*)malloc(rows*cols*sizeof(double));
  double * u1 = (double*)malloc(rows*cols*sizeof(double));
  double * u2 = (double*)malloc(rows*cols*sizeof(double));

  int it = 1;

  //itération 0
  for(int i = 0 ; i < cols ; i++){
    for(int j = 0 ; j < rows ; j++){
      u[i*rows+j] = channel_in[i*rows+j];
    }
  }

  double c;
  double u_norm;

  while (n != it){

    calculateGradient(u1,u2, u,cols,rows);

    for(int i = 0 ; i < cols ; i++){
      for(int j = 0 ; j < rows ; j++){

        u_norm = sqrt(u1[i*rows+j]*u1[i*rows+j] + u2[i*rows+j]*u2[i*rows+j]);

        if(function == 0){
          c = c0();
        }else if(function == 1){
          c = c1(u_norm/(double)lambda);
        }else if(function == 2){
          c = c2(u_norm/(double)lambda);
        }else exit(EXIT_FAILURE);

        u[i*rows+j] = div1(u1, u2, i, j, rows, c);

      }
    }

    it++;
  }

  for(int i = 0 ; i < cols ; i++){
    for(int j = 0 ; j < rows ; j++){
      channel_in[i*rows+j] = u[i*rows+j];
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
  free(u); free(u1); free(u2);
  free(channel_in);

}

void
usage (char *s){
  fprintf(stderr, "Usage: %s <n> <lambda> <function> <ims> <imd>\n", s);
  exit(EXIT_FAILURE);
}

#define PARAM 5
int
main(int argc, char *argv[]){
  if (argc != PARAM+1) usage(argv[0]);
  process(atoi(argv[1]),atoi(argv[2]), atoi(argv[3]), argv[4],argv[5]);
  return EXIT_SUCCESS;
}
