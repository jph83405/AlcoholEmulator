#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <dos.h>
#include <math.h>
using namespace std;


int CALIBRATED;
double calibrated_matrix [2];
double coEfficient;     //typical values are in the E-6 to E-16 range
double exponent;        //typical values are between 2 and 3
const int AOUTpin0 = 0; //for alcohol sensor



void uncalibrated(){
	cout<<"Enter a raw value to calculate percentage\n";
	double raw_value;
	cin >> raw_value;
	double alcohol = coEfficient * pow(raw_value,exponent) * 100;
	cout<<"\nComputed alcohol: " << alcohol << "%\n";
}

void calibrated(){
	cout<<"Enter a raw value to calculate percentage\n";
	double raw_value;
	cin >> raw_value;
	double alcohol = exp(calibrated_matrix[0])*pow(raw_value,calibrated_matrix[1]);
	cout<<"\nComputed alcohol: " << alcohol << "%\n";
}

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
	calibrated_matrix[1] = b;
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
	calibrated_matrix[0] = a;
	return a;
}


void compute_sum_coefficients( int N_points, double px[], double py[], double coef_matrix[] ) {

  int i;
  double S00, S10, S20, S30, S40, S01, S11, S21;
  double denom, x, y, a, b, c;
  S00=S10=S20=S30=S40=S01=S11=S21=0;
 
  for (i=0; i<N_points; i++) { 
    x = px[i];
    y = py[i];
    S10 += x;
    S20 += x * x;
    S30 += x * x * x;
    S40 += x * x * x * x;
    S01 += y;
    S11 += x * y;
    S21 += x * x * y;
  }
  S00 = N_points;
 
  denom =   S00*(S20*S40 - S30*S30) - S10*(S10*S40 - S20*S30) + S20*(S10*S30 - S20*S20);

c = (S01*(S20*S40-S30*S30)-S11*(S10*S40-S20*S30)+S21*(S10*S30-S20*S20))/denom;
b = (S00*(S11*S40-S30*S21)-S10*(S01*S40-S21*S20)+S20*(S01*S30-S11*S20))/denom;
a = (  S00*(S20*S21 - S11*S30) - S10*(S10*S21 - S01*S30) + S20*(S10*S11 - S01*S20) )/denom;
           
  coef_matrix[0] = a;
  coef_matrix[1] = b;
  coef_matrix[2] = c;
 
}

void show_table(double a, double b){
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
}

void calibrate(){
	double x_axis [8];
	double y_axis [8] = {.1,.1,.25,.25,.5,.5,1,1};
	cout<< "Enter a raw value for .1%:\n";
	cin >> x_axis[0];
	cout<< "Enter a second raw value for .1%:\n";
	cin >> x_axis[1];
	cout<<"\nEnter a raw value for .25%\n";
	cin>>x_axis[2];
	cout<<"\nEnter a second raw value for .25%\n";
	cin>>x_axis[3];
	cout<<"\nEnter a raw value for .5%\n";
	cin>>x_axis[4];
	cout<<"\nEnter a second raw value for .5%\n";
	cin>>x_axis[5];
	cout<<"\nEnter a raw value for 1%\n";
	cin>>x_axis[6];
	cout<<"\nEnter a second raw value for 1%\n";
	cin>>x_axis[7];
	double b = compute_b(8,x_axis,y_axis );
	compute_a(8,b,x_axis,y_axis);
	CALIBRATED = 1;
	cout<<"\n Calibration complete\n";

}


void init(){
	coEfficient = 0.000000004326;
	exponent = 2.381;
	CALIBRATED = 0;
}

void main_loop(){
	bool exit = false;
	cout << "Welcome to alcohol detector simulator \n";
	while(!exit){
		cout << "Press: \n 1: Enter uncalibrated detection mode \n 2: Enter calibrated detection mode \n 3: Enter calibration mode \n 4: show table of values\n 5: Exit\n";
		int selection;
		cin >> selection;
		switch(selection){
			case 1:
			uncalibrated();
			break;
			case 2:
			if(CALIBRATED){
				calibrated();
			}
			else{
				cout<<"Not calibrated\n";
			}
			break;
			case 3:
			calibrate();
			break;
			case 4:
			if(CALIBRATED){
				show_table(calibrated_matrix[0],calibrated_matrix[1]);			
			}
			else{
				cout<<"Not calibrated\n";
			}
			break;
			case 5:
			cout<<"Goodbye\n";
			exit = true;
			break;
			default:
			cout << "Invalid input try again\n";
		}
	}
}



int main(void){
 init();
 main_loop();
return 1;
}