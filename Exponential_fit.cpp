#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std;


int main()
{
 

    int n,i;
    double Y[20],sumx=0,sumy=0,sumxy=0,sumx2=0;
    double a,b,A;
    cout<<"\n Enter the value of number of terms n:";
    cin>> n;
    double x [8] = {173,178,266,273,357,364,455,458};
    double y [8] = {.1,.1,.25,.25,.5,.5,1.0,1.0};
    
    for(i=0;i<=n-1;i++)
    {
        Y[i]=log(y[i]);
    }
    for(i=0;i<=n-1;i++)
    {
        sumx=sumx +x[i];
        sumx2=sumx2 +x[i]*x[i];
        sumy=sumy +Y[i];
        sumxy=sumxy +x[i]*Y[i];
 
    }
    A=((sumx2*sumy -sumx*sumxy)*1.0/(n*sumx2-sumx*sumx)*1.0);
    b=((n*sumxy-sumx*sumy)*1.0/(n*sumx2-sumx*sumx)*1.0);
    a=exp(A);
    cout<<"\n\n The curve is Y= " << a << "e^" << b <<"X\n";
    cout<< "100: " << a * exp(b*100)<<"\n";
    cout<< "150: " <<a * exp(b*150)<<"\n";
    cout<< "200: " <<a * exp(b*200)<<"\n";
    cout<< "250: " <<a * exp(b*250)<<"\n";
    cout<< "300: " <<a * exp(b*300)<<"\n";
    cout<< "350: " <<a * exp(b*350)<<"\n";
    cout<< "400: " <<a * exp(b*400)<<"\n";
    cout<< "450: " <<a * exp(b*450)<<"\n";
    cout<< "500: " <<a * exp(b*500)<<"\n";
    cout<< "550: " <<a * exp(b*550)<<"\n";
    return(0);
}