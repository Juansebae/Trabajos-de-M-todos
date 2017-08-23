#include<iostream>
#include<fstream>
#include<cmath>

using namespace std;

const double Beta=0.3,Gamma=0.05;

double f(double Beta,double s,double i,double t){return -Beta*s*i;}
double g(double Beta, double Gamma,double s,double i,double t){return Beta*s*i-Gamma*i;}
double p(double Gamma,double r,double i, double t){return Gamma*i;}


void UnPasoDeRungeKuta4(double Beta,double Gamma,double & s,double & i,double & r, double & t,double dt){
  
  double ds1,ds2,ds3,ds4;                       double di1 ,di2 ,di3 ,di4;
  
  ds1=dt*f(Beta,s,i,t);                         di1=dt*g(Beta,Gamma,s,i,t);
  ds2=dt*f(Beta,s+ds1/2,i+di1/2,t+dt/2);        di2=dt*g(Beta,Gamma,s+ds1/2,i+di1/2,t+dt/2);
  ds3=dt*f(Beta,s+ds2/2,i+di2/2,t+dt/2);        di3=dt*g(Beta,Gamma,s+ds2/2,i+di2/2,t+dt/2);
  ds4=dt*f(Beta,s+ds3,i+di3,t+dt);              di4=dt*g(Beta,Gamma,s+ds3,i+di3,t+dt);

  double dr1,dr2,dr3,dr4;
  
  dr1=dt*p(Gamma,r,i,t);
  dr2=dt*p(Gamma,r+dr1/2,i+di1/2,t+dt/2);
  dr3=dt*p(Gamma,r+dr2/2,i+di2/2,t+dt/2);
  dr4=dt*p(Gamma,r+dr3,i+di3,t+dt);
         
  t+=dt; s+=(ds1+2*ds2+2*ds3+ds4)/6;    i+=(di1+2*di2+2*di3+di4)/6; r+=(dr1+2*dr2+2*dr3+dr4)/6;
}


int main(void){
  double s=0.999,i=0.001,r=0,t=0;
  double dt=0.001;
  for(t=0;t<150;)
    {
      UnPasoDeRungeKuta4(Beta,Gamma,s,i,r,t,dt);
      cout<<t<<"   "<<s<<"  "<<i<<"  "<<r<<endl;
    }
   return 0;
}
