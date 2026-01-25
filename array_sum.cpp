#include "array_sum.h"

int array_sum(std::vector<int>& array, int array_length){
    int sum = 0;
    for (int x = 0; x < array_length; ++x){
        sum += array[x];
    }
    return sum;
}
