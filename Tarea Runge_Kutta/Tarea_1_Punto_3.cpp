#include<iostream>
#include<fstream>
#include<cmath>

using namespace std;

double f(double Ro, double Sinf){
  const double So=0.999;
  return Sinf- So*exp(Ro*(Sinf-1));
 };

void ZerosPorBis(double Ro,double a, double b,double & zero){
  const double Err=1e-5;
  double m;
  
  if (f(Ro,a)*f(Ro,b)<0){
    do{
      m=(a+b)/2;	
      if(f(Ro,a)*f(Ro,m)<0){b=m;}
      else{a=m;}
    }while(abs(f(Ro,m))>Err);
    zero=m;
  }
  else if(f(Ro,a)*f(Ro,b)==0){
    if(f(Ro,a)==0){zero=f(Ro,a);}
    else{zero=f(Ro,b);}
	
  }
  else{cout<<"No hay un cero en el intervalo"<<endl;}
}

void  CerosFinder(double Ro, double & zero){
  double x,k=0.001,y;
  int ceros=0;
  for(x=0;ceros<1;x+=k){
    y=x+k;
    if (f(Ro,x)*f(Ro,y)<=0){
      ZerosPorBis(Ro,x,y,zero);
	ceros+=1;
      }
      else{
	ceros=ceros;
      }
    
  }
}


int main(void){
  double Ro=1;
  double zero=0;
   for (Ro=0;Ro<6;Ro+=0.01){
  
    CerosFinder(Ro,zero);
    cout<<Ro<<"  "<<zero<<endl;
     }

   return 0;
}
