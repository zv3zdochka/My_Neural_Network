#include <cmath>
#pragma once

class Activation{
public:
    static float sigmoid(float x){
        const float e = 2.7182818284;
        return  1 / (1 + pow(e, -x));
    }
    static float fast_sigmoid(float x){
        return x / (1 + abs(x));
    }
};
