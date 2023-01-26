//
// Created by User on 12/20/2022.
//

#include "NotBrainClassTest3.h"
void NotBrainClassTest3 :: N3func1(){
    int v1 = this->f1;
    int v2 = this->f2;
    int v3 = this->f3;
    int v4 = this->f4;
    int v5 = this->f5;
    this->N3func2();
    this->N3func3();
    this->N3func4();
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

void NotBrainClassTest3 :: N3func2(){
    int v1 = this->f1;
    int v2 = this->f2;
    int v3 = this->f3;
    int v4 = this->f4;
    int v5 = this->f5;
    this->N3func1();
    this->N3func3();
    this->N3func4();
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
void NotBrainClassTest3 :: N3func3(){
    this->N3func1();
    this->N3func2();
    this->N3func4();
}
void NotBrainClassTest3 :: N3func4(){
    this->N3func1();
    this->N3func3();
    this->N3func2();
}