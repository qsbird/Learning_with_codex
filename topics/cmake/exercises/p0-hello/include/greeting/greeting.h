//
// Created by Qs on 2026/7/19.
//
#ifndef GREETING_HAS_LIBRARY
#error "greeting consumers require GREETING_HAS_LIBRARY"
#endif

#ifndef CMAKE_LEARN_GREETING_H
#define CMAKE_LEARN_GREETING_H

#include <string_view>

class Greeting {
public:
    static void printGreeting(std::string_view message);
};


#endif //CMAKE_LEARN_GREETING_H