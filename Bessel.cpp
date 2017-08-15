#include<iostream>
#include<fstream>
#include<cmath>

using namespace std;
double f(double alpha,double x,double t){
  return cos(alpha*t-x*sin(t));
}

double IntegralPorSimpson(double alpha,double x,double a,double b,int N){
  double h=(b-a)/N,suma,t;
  int i;
 
  for (suma=0,i=0;i<=N;i++){
     t=a+i*h;
    if(i==0 || i==N)
      {
	suma+=f(alpha,x,t);
      }
      else if(i%2==0)
	{
	  suma+=2*f(alpha,x,t);
	}
      else
	{
	  suma+=4*f(alpha,x,t);
	} 
      

  }

  return (suma)*h/3;

}

double Bessel(double alpha,double x){
  return  IntegralPorSimpson(alpha,x,0,M_PI,50)/M_PI;

}


double CerosPorBis(double a, double b,double alpha){
  double m;
 const double Err=1e-5;
  if (Bessel(alpha,a)*Bessel(alpha,b)<0){
    
    do{
      m=(b+a)/2;
      if (Bessel(alpha,a)*Bessel(alpha,m)<0){
	b=m;
      }
      else{
	a=m;
      }       
    }while(abs(Bessel(alpha,m))>Err);

   
    cout<<"El cero esta en:  "<<endl;
    return m;
  }
  else if (Bessel(alpha,a)*Bessel(alpha,b)==0){
    if (Bessel(alpha,a)==0){
      m=a;
    }
    else{
      m=b;  
    }

    return m;
  }
  else{
    cout<<"No existe un cero en el intervalo "<<endl;
  }

}

double  CerosFinder(double alpha){
  double x,k,y;
  int ceros;
  ceros=0;
  k=1;
  for(x=0;ceros<3;x+=k){
    y=x+k;
      if (Bessel(alpha,x)*Bessel(alpha,y)<0){
	cout<<CerosPorBis(x,y,alpha)<<endl;
	ceros+=1;
      }
      else{
	ceros=ceros;
      }
    
  }
   return 0;
}


int main(void){
  double x,alpha=0;
  double m;
  
  // for(x=0;x<20;x+=0.1){
  //   Bessel(alpha,x);
  //   cout<<x<<" "<<Bessel(alpha,x)<<endl;
  // }
  cout<<CerosFinder(alpha)<<endl;
   return 0;
}
