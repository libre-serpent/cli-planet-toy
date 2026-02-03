#include "array_sum.h"

int array_sum(std::vector<int>& array, int upto){
    int sum = 0;
    for (int x = 0; x < upto; ++x){
        sum += array[x];
    }
    return sum;
}
