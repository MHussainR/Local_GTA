#include "Health.hpp"
#include "Money.hpp"
#include "cheat_codes.hpp"
#include <iostream>

Cheat_codes::Cheat_codes()
{
    flag = 0;
    code1 = "panadol";
    code2 = "ambani";
    code1_count = 0;
    code2_count = 0;
}

void Cheat_codes::check(char letter, Health *h, Money* m)
{
    code += letter;
    static int check = 0;
    std::cout << letter;

    // if (letter == code1[check] | letter == code2[check])
    // {
    //     if (letter == code1[check]){
    //         code1_count ++;
    //         // code += letter;
    //         check ++;
    //     }
    //     else if(letter == code2[check]){
    //         code2_count ++;
    //         check++;
    //     }
    // }
    // else
    // {
    //     code1_count = 0;
    //     code2_count = 0;
    //     check = 0;
    // }
    if (letter == code1[code1_count]){
        code1_count++;
    }
    else{
        code1_count = 0;
    }

    if (letter == code2[code2_count]){
        code2_count ++;
    }
    else {
        code2_count = 0;
    }

    if (code1_count == 7)
    {
        h->setHealth(100);
    }
    if (code2_count == 6){
        m->setMoney(99999999);
    }
}

void Cheat_codes::Update()
{
    static int time;
}