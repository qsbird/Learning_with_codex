//
// Created by Qs on 2026/7/23.
//

#ifndef HELLO_TEXT_H
#define HELLO_TEXT_H


#include <string_view>
#include <iostream>
inline void printHello(std::string_view name) {
    std::cout << "Hello, " << name << '\n';
}

#endif //HELLO_TEXT_H
