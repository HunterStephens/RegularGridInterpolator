//
// Created by Hunter Stephens on 2/2/22.
//

#ifndef REGULARGRIDINTERPOLATOR_REGULARGRIDINTERPOLATOR2D_H
#define REGULARGRIDINTERPOLATOR_REGULARGRIDINTERPOLATOR2D_H

#include <math.h>
#include <iostream>


template <typename T>
class RegularGridInterpolator2D {
private:
    T* x;
    T* y;
    T** Z;
    T**** Q; // Bi-Linear Q matrix
    unsigned long nx, ny;

public:
    //Destructor and Constructor
    ~RegularGridInterpolator2D();
    RegularGridInterpolator2D(T*, T*, T**, unsigned long, unsigned long);

    //methods
    T operator()(T, T);

};

template<typename T>
RegularGridInterpolator2D<T>::~RegularGridInterpolator2D() {
    delete x;
    delete y;
    delete Z;
    //delete Q;
}

template<typename T>
RegularGridInterpolator2D<T>::RegularGridInterpolator2D(T* xin, T* yin, T** Zin, unsigned long sz1, unsigned long sz2){

    // set data
    nx = sz1;
    ny = sz2;
    x = xin;
    y = yin;
    Z = Zin;
    Q = new T***[ny-1];
    for(int i=0; i < ny-1; i++){
        Q[i] = new T**[nx-1];
        for(int j=0; j < nx-1; j++){
            Q[i][j] = new T*[2];
            for(int k=0; k < 2; k++) {
                Q[i][j][k] = new T[2];
            }
        }
    }

    // fill Q matrix
    for(int i=0; i < ny-1; i++){
        for(int j=0; j < nx-1; j++){
            Q[i][j][0][0] = Z[i][j];
            Q[i][j][1][0] = Z[i+1][j] - Z[i][j];
            Q[i][j][0][1] = Z[i][j+1] - Z[i][j];
            Q[i][j][1][1] = Z[i+1][j+1]-Z[i+1][j]-Z[i][j+1]+Z[i][j];
        }
    }


}

template<typename T>
T RegularGridInterpolator2D<T>::operator()(T xin, T yin) {
    // get indices
    int j = floor((xin - x[0])/(x[1]-x[0]))-1;
    int i = floor((yin - y[0])/(y[1]-y[0]))-1;

    if (j < 0){
        j = 0;
    }
    else if (j >= nx-1){
        j = nx-2;
    }
    if (i < 0){
        i = 0;
    }
    else if (i >= ny-1){
        i = ny-2;
    }

    T** A = Q[i][j];
    return A[0][0] + A[1][0]*xin + A[0][1]*yin + A[1][1]*xin*yin;
}


#endif //REGULARGRIDINTERPOLATOR_REGULARGRIDINTERPOLATOR2D_H
