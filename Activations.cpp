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
    static float relu(float x){
        if (x > 0){return x;}
        else{return 0;}
    }
    static float leaky_relu(float x, float a){
        if (a * x > x){return a  * x;}
        else{return x;}
    }
    static float elu(float x, float a){
        const float e = 2.7182818284;
        if (x > 0){return x;}
        else{return (a * ((pow(e,x)) -1));}
    }
    static float silu(float x){
        const float e = 2.7182818284;
        return x * (1 / (1 + pow(e, -x)));
    }
    static float tanh(float x){
        const float e = 2.7182818284;
        return (pow(e,x) - pow(e, -x))/(pow(e,x) + pow(e, -x));

    }
    static float softmax(float x){
        return x;
    }
};
