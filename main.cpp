#include <iostream>
#include <math.h>
#include "RegularGridInterpolator2D.h"

double function(double x, double y){
    return 2.0*x*x + 3.0*y*y - 4.2;
}
int main() {
    // create mesh
    double *x = new double[1000];
    double *y = new double[1000];
    for(int i=0; i < 1000; i++){
        x[i] = -10.0 + (20.0/1000.0)*i;
        y[i] = -10.0 + (20.0/1000.0)*i;
    }


    double **Z = new double*[1000];
    for(int i=0; i < 1000; i++){
        Z[i] = new double[1000];
        for(int j=0; j < 1000; j++){
            Z[i][j] = function(x[j], y[i]);
        }
    }

    RegularGridInterpolator2D<double> f(x, y, Z, 1000, 1000);



    return 0;
}
