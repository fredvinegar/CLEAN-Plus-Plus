// The class has MLOC larger than the average+std of all methods and cc larger the average+std of all methods and max nesting bigger than 5 but NOAV lower or equal to 6.
// -> Has no brain method smell.
#include "NotBrainMethodTest2.h"
void NotBrainMethodTest2 :: N2func1(){
    int v1 = this->f1;
    int v2 = this->f2;
    int v3 = this->f3;
    for (int i=0; i < 10; i++){
        if (this->f7<5){
            v1 --;
            switch (this->f6) {
                case 1:
                    v1 ++;
                case 2:
                    while (true){
                        try {
                            if (true) {
                                break;
                            }
                        }catch (...){
                            if (true){
                                v1--;
                            }
                        }

                    }
            }
        }
    }
}