#include<iostream>
#include<fstream>
#include<cmath>
#include<GL/glew.h>
#include<GL/glut.h>
#include <cuda_runtime_api.h>
#include <cuda_gl_interop.h>

using namespace std;

__global__ void SumeleUno(float * d_test){
  (*d_test)++1;
}



int main(void){
  
  //Declarar Matrices en el host.
  float h_test[1];

  //Memoria dinamica de la matriz en el device.
  float *d_test;  cudaMalloc((void**) &d_test,sizeof(float));


  //Inicializar los datos
  // Cargan en el host
  h_test[0]=10;
  // Enviarlo al device.
  // Debe de escribirse tal cual
  cudaMemcpy(d_test,h_test,sizeof(float),cudeMemcpyHostToDevice);

  //Procesar en la tarjeta Grafica.
  dim3 ThreadsPerBlock(1,1,1);
  dim3 BlocksPerGrid(1,1,1);
  SumeleUno<<<BlocksPerGrid,ThreadsPerBlock>>>(d_test);

  //Imprimir los datos
  // Devolverlo al Host
  cudaMemcpy(h_test,d_test,sizeof(float),cudaMemcpyDeviceToHost);
  //Imprimirlos
  cout_<<h_test[0]<<endl;



  return 0;
}
