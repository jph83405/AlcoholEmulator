#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <dos.h>
#include <math.h>
using namespace std;


int CALIBRATED;
double calibrated_matrix [3];
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
	double alcohol = calibrated_matrix[0] * raw_value * raw_value + calibrated_matrix[1] * raw_value + calibrated_matrix[2];
	cout<<"\nComputed alcohol: " << alcohol << "%\n";
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

void calibrate(){
	double x_axis [4];
	double y_axis [4] = {.1,.25,.5,1};
	cout<< "Enter a raw value for .1%:\n";
	cin >> x_axis[0];
	cout<<"\nEnter a raw value for .25%\n";
	cin>>x_axis[1];
	cout<<"\nEnter a raw value for .5%\n";
	cin>>x_axis[2];
	cout<<"\nEnter a raw value for 1%\n";
	cin>>x_axis[3];
	compute_sum_coefficients(4,x_axis,y_axis,calibrated_matrix);
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
		cout << "Press: \n 1: Enter uncalibrated detection mode \n 2: Enter calibrated detection mode \n 3: Enter calibration mode \n 4: exit\n";
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
			cout << "Goodbye";
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