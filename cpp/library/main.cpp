// main.c
#include <iostream>
#include "mylib.h"
int main()
{
        double d = 100;
        //printf("sqrt(%3.0f)=%2.0f\n",d,calcSqrt(d));
        std::cout<<"sqrt("<<d<<")="<<calcSqrt(d)<<std::endl;
        return 0;
}