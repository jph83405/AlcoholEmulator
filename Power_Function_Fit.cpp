#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std;

double compute_b(int n, double x[8], double y[8]){
	double product_logs = 0;
	double sum_x_logs = 0;
	double sum_y_logs = 0;
	double sum_square_x_logs = 0;
	for(int i = 0; i<n; i++){
		product_logs+=log(x[i])*log(y[i]);
		sum_x_logs+=log(x[i]);
		sum_y_logs+=log(y[i]);
		sum_square_x_logs+=log(x[i])*log(x[i]);
	}
	double b = ((double)n*product_logs - (sum_y_logs*sum_x_logs))/((double)n*sum_square_x_logs-sum_x_logs*sum_x_logs);
	return b;
}

double compute_a (int n, double b, double x[8], double y[8]){
	double sum_y_logs = 0;
	double sum_x_logs = 0;
	for(int i = 0;i<n;i++){
		sum_x_logs+=log(x[i]);
		sum_y_logs+=log(y[i]);
	}
	double a = (sum_y_logs - b * sum_x_logs)/(double)n;
	return a;
}

int main(void){
	int n = 8;
	double x_axis [8] = {173,178,266,273,357,364,455,458};
	double y_axis [8] = {.1,.1,.25,.25,.5,.5,1.0,1.0};
	double b = compute_b(n, x_axis,y_axis);
	double a = compute_a(n,b,x_axis,y_axis);
	cout<< "100: " <<exp(a)*pow(100,b)<<"\n";
    cout<< "150: " <<exp(a)*pow(150,b)<<"\n";
    cout<< "200: " <<exp(a)*pow(200,b)<<"\n";
    cout<< "250: " <<exp(a)*pow(250,b)<<"\n";
    cout<< "300: " <<exp(a)*pow(300,b)<<"\n";
    cout<< "350: " <<exp(a)*pow(350,b)<<"\n";
    cout<< "400: " <<exp(a)*pow(400,b)<<"\n";
    cout<< "450: " <<exp(a)*pow(450,b)<<"\n";
    cout<< "500: " <<exp(a)*pow(500,b)<<"\n";
    cout<< "550: " <<exp(a)*pow(550,b)<<"\n";
return 1;
}
