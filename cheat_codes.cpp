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

void Cheat_codes::check(char letter, Health *h, Money *m)
{
    // Concatenate the entered letter to the code string
    code += letter;
    static int check = 0;
    std::cout << letter;

    // Check for matches with cheat codes
    if (letter == code1[code1_count])
    {
        code1_count++;
    }
    else
    {
        code1_count = 0;
    }

    if (letter == code2[code2_count])
    {
        code2_count++;
    }
    else
    {
        code2_count = 0;
    }

    // Check if a cheat code has been entered completely
    if (code1_count == 7)
    {
        // Activate cheat code 1: Reset health to 100
        h->setHealth(100);
    }
    if (code2_count == 6)
    {
        // Activate cheat code 2: Set money to a large amount
        m->setMoney(99999999);
    }
}

void Cheat_codes::Update()
{
    // Perform any necessary updates
    static int time;
}
