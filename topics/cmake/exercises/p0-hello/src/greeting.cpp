//
// Created by Qs on 2026/7/19.
//

#include <greeting/greeting.h>

#include <iostream>

#ifndef GREETING_IMPLEMENTATION
#error "This file must be compiled as part of the greeting library"
#endif

void Greeting::printGreeting() {
    std::cout << "Hello World from program input" << std::endl;
}
