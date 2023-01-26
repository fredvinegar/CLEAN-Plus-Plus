// The class has MLOC larger than the average+std of all methods and cc larger the average+std of all methods and NOAV larger than 6 and max nesting lower or equal to 5.
// -> Has no brain method smell.

#include "NotBrainMethodTest1.h"
void NotBrainMethodTest1 :: N1func1(){
    int v1 = this->f1;
    int v2 = this->f2;
    int v3 = this->f3;
    int v4 = this->f4;
    int v5 = this->f5;
    for (int i=0; i < 10; i++){
        if (this->f7<5){
            v1 --;
            switch (this->f6) {
                case 1:
                    v1 ++;
                case 2:
                    while (true){
                        break;
                    }
            }
        }
    }
}