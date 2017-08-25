#include "min_max.h"

min_max::min_max()
{

}

double min_max::min(double a, double b, double c)
{
    double min=256;
    if(a<min)
        min=a;
    if(b<min)
        min=b;
    if(c<min)
        min=c;
    return min;
}

double min_max::max(double a, double b, double c)
{
    double max=0;
    if(a>max)
        max=a;
    if(b>max)
        max=b;
    if(c>max)
        max=c;
    return max;
}
