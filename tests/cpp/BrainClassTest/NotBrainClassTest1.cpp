// The class has more than 1 brain method and cyclomatic complexity higher than the (average+std)*1.5 of all the project
// and TCC lower than 0.5 but the LOC low than the (average+std)*1.5 of all the project
// -> Has no brain class smell.
#include "NotBrainClassTest1.h"

void NotBrainClassTest1 :: N1func1(){
    int v1 = this->f1;
    int v2 = this->f2;
    int v3 = this->f3;
    int v4 = this->f4;
    int v5 = this->f5;
    this -> N1func2();
    this -> N1func3();
    this -> N1func4();
    this -> N1func5();
    this -> N1func6();
    this -> N1func7();
    this -> N1func8();
    this -> N1func9();
    this -> N1func10();
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

void NotBrainClassTest1 :: N1func2(){
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