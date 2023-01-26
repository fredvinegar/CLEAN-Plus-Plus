// The class has try-catch statement and the catch is empty
// -> Has empty catch smell.
#include "EmptyCatchClauseTest.h"

void EmptyCatchClauseTest :: func1(int p) {
        try {
            if (this->f >p){
                this->f ++;
            } else{
                throw (p);
            }
        }
        catch (int e){

        }
}