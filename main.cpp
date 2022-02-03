#include <iostream>
#include <random>
#include <cmath>
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

    // apply function to mesh
    double **Z = new double*[1000];
    for(int i=0; i < 1000; i++){
        Z[i] = new double[1000];
        for(int j=0; j < 1000; j++){
            Z[i][j] = function(x[j], y[i]);
        }
    }

    RegularGridInterpolator2D<double> f(x, y, Z, 1000, 1000);

    // test
    std::random_device seed;
    std::mt19937 generator(seed());
    std::uniform_real_distribution<> distr(-10.0, 10.0);

    double error = 0.0;
    int N = 100000;
    for(int i=0; i<N; i++){
        double xi = distr(generator);
        double yi = distr(generator);
        double interp = f(xi,yi);
        double actual = function(xi, yi);
        double error_i = 100.0*abs((actual-interp)/actual);
        error = error + error_i;
    }
    std::cout << error/N;

    return 0;
}
