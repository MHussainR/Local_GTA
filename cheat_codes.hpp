#pragma once
#include "Health.hpp"
#include<cstring>
#include<string>


class Cheat_codes{
    private:
        int flag;
        char* code;
        const char* code1;
        int code1_count;
    public:
        Cheat_codes();
        void check(char letter);
        void Update();
};