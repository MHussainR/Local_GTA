#pragma once
// #include "Health.hpp"
#include<cstring>
#include<string>

class Health;
class Money;
class Cheat_codes{
    private:
        int flag;
        std::string code;
        std::string code1;
        int code1_count;
        std::string code2;
        int code2_count;
    public:
        Cheat_codes();
        void check(char letter, Health* h, Money* m);
        void Update();
};