#include "classes.h"


int NumOps::intConv(std::string& num) {
    char* p;
    int convNum = strtol(num.c_str(), &p, 10);
    if (*p == 0)
        return convNum;
    throw std::invalid_argument("Invalid integer string");
}

unsigned NumOps::incomeCounter(unsigned* defaultRev, unsigned* minutes)
{
    unsigned modMinutes = *minutes % 60;
    if (modMinutes != 0)
        modMinutes = 1;
    return *defaultRev * ((*minutes / 60) + modMinutes);
}

bool NumOps::posCheck(int num) {
    return num > 0;
}