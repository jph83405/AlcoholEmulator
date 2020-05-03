#include <iostream>
using namespace std;


void check_valid_coeffs(double value, double* coef_matrix){
	double final_value = 0;
	double a = coef_matrix[0];
	double b = coef_matrix[1];
	double c = coef_matrix[2];
	final_value = a * value * value + b * value + c;
	cout << "computed value for analog reading " << value << " is " << final_value << "%\n";  
}


void compute_sum_coefficients( int N_points, double px[], double py[], double coef_matrix[] ) {

  int i;
  double S00, S10, S20, S30, S40, S01, S11, S21;
  double denom, x, y, a, b, c;
  S00=S10=S20=S30=S40=S01=S11=S21=0;
 
  for (i=0; i<N_points; i++) { 
    x = px[i];
    y = py[i];
    //S00 += 1; // x^0+y^0
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



int main(void){
double y_i [5] = {.1,.25,.5,1.0};
double x_i [5] = {243, 346, 423, 527};
double coef_matrix [3];
compute_sum_coefficients(4, x_i,y_i,coef_matrix);

check_valid_coeffs(252,coef_matrix);
check_valid_coeffs(346,coef_matrix);
check_valid_coeffs(423,coef_matrix);
check_valid_coeffs(527,coef_matrix);

return 0;
}