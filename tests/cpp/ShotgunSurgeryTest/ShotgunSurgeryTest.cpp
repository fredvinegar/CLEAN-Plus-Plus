// The class has at least one method that has cyclomatic complexity bigger or equal to 6, and 8 or more other functions call it.
// -> Has shotgun surgery smell.
#include "ShotgunSurgeryTest.h"

void ShotgunSurgeryTest :: fun1 (int p1, int p2, int p3) {
    for (int i = 0; i < 10; i++) {
        if (i < 5) {
            p1--;
        }
        p1++;
    }
    int v = 0;
    while (true) {
        v++;
        break;
    }
    switch (p3) {
        case 1:
            p3++;
        case 2:
            p3--;
        default:
            p3 = 0;
    }
    try {
        if (p1 < 0) {
            throw (0);
        }
    } catch (int i) {
        p3 = i;
    }

}
void ShotgunSurgeryTest :: fun2(int p1, int p2, int p3) {
    this->fun1(p1, p2, p3);
}
void ShotgunSurgeryTest :: fun3(int p1, int p2, int p3) {
    this->fun1(p1, p2, p3);
}
void ShotgunSurgeryTest :: fun4(int p1, int p2, int p3) {
    this->fun1(p1, p2, p3);
}
void ShotgunSurgeryTest :: fun5(int p1, int p2, int p3) {
    this->fun1(p1, p2, p3);
}
void ShotgunSurgeryTest :: fun6(int p1, int p2, int p3) {
    this->fun1(p1, p2, p3);
}
void ShotgunSurgeryTest :: fun7(int p1, int p2, int p3) {
    this->fun1(p1, p2, p3);
}
void ShotgunSurgeryTest :: fun8(int p1, int p2, int p3) {
    this->fun1(p1, p2, p3);
}
void ShotgunSurgeryTest :: fun9(int p1, int p2, int p3) {
    this->fun1(p1, p2, p3);
}
void ShotgunSurgeryTest :: fun10(int p1, int p2, int p3) {
    this->fun1(p1, p2, p3);
}
