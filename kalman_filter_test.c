/** 
    This is a test function to check the Kalman filter implementation.
    Compile with : gcc kalman_filter_test.c -o kalman_filter 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ITERATIONS 30

// Random number between -1 and 1 used to simulate noise in Kalman measurements
double frand() {
    return 2*((rand()/(double)RAND_MAX) - 0.5);
}

int main() {

    //initial values for the kalman filter
    float x_last_estimate = 0;
    float P_last = 0;
    //the noise in the system
    float Q = 0.022;
    float R = 0.617;
    
    float K;
    float P;
    float P_temp;
    float x_temp_estimate;
    float x_estimate;
    float z_measured; //the 'noisy' value we measured
    float z_real = 0.5; //the ideal value we wish to measure
    
    srand(0);
    
    //initialize with a measurement
    x_last_estimate = z_real + frand()*0.09;
    
    float sum_error_kalman = 0;
    float sum_error_measure = 0;
    
    for (int i=0;i<ITERATIONS;i++) {
        //do a prediction
        x_temp_estimate = x_last_estimate;
        P_temp = P_last + Q;

        //calculate the Kalman gain (uncertainty in the measurement)
        K = P_temp * (1.0/(P_temp + R));
        
        //measure
        z_measured = z_real + frand()*0.09; //the real measurement plus noise

        //correct
        x_estimate = x_temp_estimate + K * (z_measured - x_temp_estimate); 
        P = (1- K) * P_temp;

        //we have our new system
        printf("Ideal    position: %6.3f \n",z_real);
        printf("measured  position: %6.3f [diff:%.3f]\n",z_measured,fabs(z_real-z_measured));
        printf("Kalman   position: %6.3f [diff:%.3f]\n",x_estimate,fabs(z_real - x_estimate));
        
        // Cumulative error
        sum_error_kalman += fabs(z_real - x_estimate);
        sum_error_measure += fabs(z_real - z_measured);
        
        //update our last's estimate and factor
        P_last = P;
        x_last_estimate = x_estimate;
    }
    
    printf("Total error if using raw measured:   %f\n",sum_error_measure);
    printf("Total error if using kalman filter: %f\n",sum_error_kalman);
    printf("Reduction in error: %d%% \n",100-(int)((sum_error_kalman/sum_error_measure)*100));
    
    
    return 0;
}
