// The class has LOC higher than the (average+std)*1.5 of all the project
// and cyclomatic complexity higher than the (average+std)*1.5 of all the project
// and TCC lower than 0.5, but it has no brain method.
// -> Has brain class smell.

#include "NotBrainClassTest2.h"
void NotBrainClassTest2 :: N2func1(){
    int v1 = this->f1;
    for (int i=0; i < 10; i++){
        if (this->f1<5){
            v1 --;
            switch (this->f1) {
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
    for (int i=0; i < 10; i++){
        if (this->f1<5){
            v1 --;
            switch (this->f1) {
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
