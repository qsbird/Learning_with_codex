//
// Created by Qs on 2026/7/19.
//

#include <greeting/greeting.h>

#include <iostream>
#include "greeting_config.h"

#if HAVE_UNISTD_H
#include <unistd.h>
#endif

#include "greeting_banner.h"

#ifndef GREETING_IMPLEMENTATION
#error "This file must be compiled as part of the greeting library"
#endif

void Greeting::printGreeting(std::string_view message) {
#if HAVE_GETPID
    std::cout << "PID: " << getpid() << '\n';
#endif

    std::cout << GREETING_BUILD_BANNER << '\n';
    std::cout << message << std::endl;
}
