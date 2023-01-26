// The class has at least one method that has cyclomatic complexity bigger or equal to 8.
// -> Has complex methodTest smell.
#include "ComplexMethodTest.h"
void ComplexMethodTest :: fun1 (int p1, int p2, int p3){
        /*if
         * else
         * while
         * case
         * for*/
        int v = 0;
        while (true){
            v ++;
            break;
        }
        while (true){
            v ++;
            break;
        }
        //  for (int i=0; i < 10; i++)
        for (int i=0; i < 10; i++){
            if (i<5){
                p1 --;
            }
            p1 ++;
        }


        switch (p3) {
            case 1:
                p3 ++;
            case 2:
                p3 --;
            default:
                p3 =0;
        }

        try{
            if (p1 < 0){
                throw (0);
            }
        }catch (int i){
            p3 = i;
        }

}


