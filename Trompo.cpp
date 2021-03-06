// Programa para estudiar el cabeceo de un trompo pesado

#include <iostream>
#include <cmath>
using namespace std;

const double deltat=0.0001;
const double g=1;
const double l=1;
const double m=1;

  
//---------Clase CuerpoRigido-------//

class CuerpoRigido{
private:
  double I1,I2,I3,q0,q1,q2,q3,wx,wy,wz,Nx,Ny,Nz;
public:
  void Inicie(double Ix,double Iy,double Iz,double theta0,double phi0, double psi0,
	      double wx0,double wy0,double wz0);

  void Rote(double dt);
  void CalculeTorque(void);
  void CalcularXYZ(double &x,double &y, double &z);
  double getWX(void){return wx;};
  double getWY(void){return wy;};
  double getWZ(void){return wz;};
  double getTheta(void){return acos((q0*q0-q1*q1-q2*q2+q3*q3)/(q0*q0+q1*q1+q2*q2+q3*q3));};

};


void CuerpoRigido:: Inicie(double Ix,double Iy,double Iz,double theta0,double phi0, double psi0,
			   double wx0,double wy0,double wz0){

  // Momento de Inercia.

  I1=Ix; I2=Iy; I3=Iz;

  // Velcidad Angular Inicial.

  wx=wx0;wy=wy0;wz=wz0;

  //Posici�n inicial ( en cuaterniones)

  q0=cos(0.5*theta0)*cos(0.5*(phi0+psi0));
  q1=sin(0.5*theta0)*cos(0.5*(phi0-psi0));
  q2=sin(0.5*theta0)*sin(0.5*(phi0-psi0));
  q3=cos(0.5*theta0)*sin(0.5*(phi0+psi0));
}




void CuerpoRigido::CaluleTorque(void){

  // Torques en el sistema rotante pegado al cuerpo. En este caso, s�lo el debido a mg

  Ny=-2*(q1*q3-q0*q2)*m*g*l;
  Nx=2*(q2*q3+q0*q1)*m*g*l;
  Nz=0;
}

void CuerpoRigido::Rote(double dt){
  double q0old=q0, q1old=q1, q2old=q2, q3old=q3;
  double wxold=wx, wyold=wy, wzold=wz;
  
  // Actualiza cuaterniones a partir de omega

  q0+=dt*0.5*(-q1old*wx-q2old*wy-q3old*wz);
  q1+=dt*0.5*( q0old*wx-q3old*wy+q2old*wz);
  q2+=dt*0.5*( q3old*wx+q0old*wy-q1old*wz);
  q3+=dt*0.5*(-q2old*wx+q1old*wy-q0old*wz);

  // Actualiza omega a partir del torque (ecuaciones de Euler)
  wx+=dt*((Nx/I1)+wyold*wzold*(I2-I3)/I1);
  wy+=dt*((Ny/I2)+wxold*wzold*(I3-I1)/I2);
  wz+=dt*((Nz/I3)+wxold*wyold*(I1-I2)/I3);

  
}
