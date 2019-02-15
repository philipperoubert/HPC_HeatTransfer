#include <stdio.h>
#include <math.h>

double calculate_temperature(int i, int j, double temperatureArray[][500]){
    float deltaXY = 0.0002;
    float alphasquare = 0.01;
    double spacial_derivativeX = (temperatureArray[i+1][j] - 2 * temperatureArray[i][j] + temperatureArray[i-1][j]) / ( powf(deltaXY,2));
    double spacial_derivativeY = (temperatureArray[i][j+1] - 2 * temperatureArray[i][j] + temperatureArray[i][j-1]) / ( powf(deltaXY,2));
    double temperature = alphasquare * (spacial_derivativeX + spacial_derivativeY);
    return temperature;
}


int main(void) {

  double temperatures[500][500];
  for (int i=0; i<500; i++){
    for (int j=0; j<500; j++){
      if((i>=149 && i<=349) && (j>=149 && j<=349)){
        temperatures[i][j] = 50.0;
      }else{
        temperatures[i][j] = 20.0;
      }
    }
  }

  int timestep = 0;
  double timestepValue = 0.0000009;
  
  while(timestep < 100){
    printf("Hello");
    timestep++;
    for (int i=0; i<500; i++){
      for (int j=0; j<500; j++){
        temperatures[i][j] += (calculate_temperature(i, j, temperatures) * timestepValue );
      }
    }
  }
  printf("Hello World\n");
  printf("%f", calculate_temperature(149, 149, temperatures));

  printf("Writing out results\n");
  FILE *outfile;
  outfile=fopen("hte.dat","w");

  for (int i=0; i<500; i++){
    for (int j=0; j<500; j++){
      float xIndex = (float)i * 0.0002;
      float yIndex = (float)j * 0.0002;
      fprintf(outfile,"%f %f %f \n",xIndex, yIndex, temperatures[i][j]);
    }
  }
  fclose(outfile);
  return 0;
}