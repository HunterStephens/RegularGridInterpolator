//
// Created by Hunter Stephens on 2/2/22.
//

#ifndef REGULARGRIDINTERPOLATOR_REGULARGRIDINTERPOLATOR1D_H
#define REGULARGRIDINTERPOLATOR_REGULARGRIDINTERPOLATOR1D_H

#include <math.h>
#include <iostream>

template <typename T>
class RegularGridInterpolator1D {
private:
    T* gridPoints;
    T* gridValues;
    T* interpolant_m;
    T* interpolant_b;
    unsigned long size;

public:
    //Destructor and Constructor
    ~RegularGridInterpolator1D();
    RegularGridInterpolator1D(T*, T*, unsigned long n);

    //methods
    T operator()(T);

};

template<typename T>
RegularGridInterpolator1D<T>::~RegularGridInterpolator1D() {
    delete gridPoints;
    delete gridValues;
    delete interpolant_m;
    delete interpolant_b;
}
template<typename T>
RegularGridInterpolator1D<T>::RegularGridInterpolator1D(T* gPs, T* gVs, unsigned long sz){
    // init interpolant
    size = sz;
    interpolant_m = new T[size-1];
    interpolant_b = new T[size-1];
    gridPoints = gPs;
    gridValues = gVs;

    for(int i=0; i<size-1; i++){
        interpolant_m[i] = (gridValues[i+1]-gridValues[i])/(gridPoints[i+1]-gridPoints[i]);
        interpolant_b[i] = gridValues[i] - gridPoints[i]*interpolant_m[i];
    }

}

template<typename T>
T RegularGridInterpolator1D<T>::operator()(T x) {
    // get index
    int index = floor((x - gridPoints[0])/(gridPoints[1]-gridPoints[0]))-1;
    if (index < 0){
        return gridValues[0];
    }
    else if (index >= size-1){
        return gridValues[size-1];
    }
    else{
        return interpolant_m[index]*x + interpolant_b[index];
    }
}

#endif //REGULARGRIDINTERPOLATOR_REGULARGRIDINTERPOLATOR1D_H
