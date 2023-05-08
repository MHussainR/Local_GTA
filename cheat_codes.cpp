#include "cheat_codes.hpp"
#include "Health.hpp"
#include <iostream>


Cheat_codes::Cheat_codes(){
    flag = 0;
    code1 = "panadol";
    code1_count = 0;
}


void Cheat_codes::check(char letter){
    code += letter;
    static int check = 0;
    if (letter == code1[check]){
        code1_count ++;
        check++;
        std::cout << letter << " aagya ";
    }
    else {
        code1_count = 0;
        check = 0;
    }

    if (code1_count == 7){
        std::cout << "panadol";
    }
}


void Cheat_codes::Update(){
    static int time;
    // if flag 
}