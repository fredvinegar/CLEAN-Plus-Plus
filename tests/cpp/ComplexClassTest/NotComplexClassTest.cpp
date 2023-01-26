// The class doesn't have constructor or destructor with cyclomatic complexity higher than 10.
// -> Has not complex class smell.
#include "NotComplexClassTest.h"

NotComplexClassTest :: NotComplexClassTest(int p1, int p2, int p3){
        for (int i=0; i < 10; i++){
            if (i<5){
                p1 --;
            }
            p1 ++;
        }
        int v = 0;
        while (true){
            v ++;
            break;
        }
        while (true){
            v ++;
            break;
        }
        while (true){
            v ++;
            break;
        }
        switch (p3) {
            case 1:
                p3 ++;
            case 2:
                p3 --;
            default:
                p3 =0;
        }


    }
void NotComplexClassTest :: func1(int p1){
        for (int i=0; i < 10; i++){
            if (i<5){
                p1 --;
            }
            p1 ++;
        }
        int v = 0;
        while (true){
            v ++;
            break;
        }
    }
NotComplexClassTest :: ~NotComplexClassTest(){
        int p1=1, p2=1, p3=1;
        for (int i=0; i < 10; i++){
            if (i<5){
                p1 --;
            }
            p1 ++;
        }
        int v = 0;
        switch (p3) {
            case 1:
                p3 ++;
            case 2:
                p3 --;
            default:
                p3 =0;
        }
        switch (p3) {
            case 1:
                p3 ++;
            case 2:
                p3 --;
            default:
                p3 =0;}
        try{
            if (p1 < 0){
                throw (0);
            }
        }catch (int i){
            p3 = i;
        }

    }
