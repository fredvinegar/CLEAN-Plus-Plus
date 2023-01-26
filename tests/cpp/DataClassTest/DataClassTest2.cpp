// The class having num of public getters/setters and fields higher than 6,
// and cyclomatic complexity lower than the (average+std)*1.5 of the project, and the ratio between
// the methods that they are public and not setter/getter to all public methods is lower than 0.33.
// -> Has data class smell.
#include "DataClassTest2.h"

int DataClassTest2 :: get_f1(){
        for (int i=0; i<5; i++){
            if (i == 4){
                break;
            } else{
                this->f2 --;
            }
        }
        while(this->f1){
            if (this->f1 <5){
                break;
            } else{
                break;
            }
        }
        for (int i=0; i<5; i++){
            if (i == 4){
                break;
            } else{
                this->f2 --;
            }
        }
        while(this->f1){
            if (this->f1 <5){
                break;
            } else{
                break;
            }
        }
        try{
            if (this->f1 < 0){
                throw (0);
            }
        }catch (int i){
        }
        switch (this->f1) {
            case 1:
                this->f1 ++;
            case 2:
                this->f1 --;
            default:
                this->f1 =0;}
        return this->f1;
    }
int DataClassTest2 :: get_f2(){
        return this->f2;
}
void DataClassTest2 :: set_f1(int p){
        this->f1 = p;
}
void DataClassTest2 :: set_f2(int p){
        this->f2 = p;
}