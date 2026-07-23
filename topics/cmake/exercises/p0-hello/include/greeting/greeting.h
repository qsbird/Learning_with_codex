//
// Created by Qs on 2026/7/19.
//
#ifndef GREETING_HAS_LIBRARY
#error "greeting consumers require GREETING_HAS_LIBRARY"
#endif

#ifndef CMAKE_LEARN_GREETING_H
#define CMAKE_LEARN_GREETING_H


class Greeting {
public:
    static void printGreeting();
};


#endif //CMAKE_LEARN_GREETING_H