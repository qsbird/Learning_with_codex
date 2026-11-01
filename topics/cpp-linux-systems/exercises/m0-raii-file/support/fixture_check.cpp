#include "file_api.h"

#include <cstdio>
#include <iostream>

int main()
{
    // Only validates the fixture/toolchain; deliberately has no RAII wrapper.
    if (file_api::open(true) != nullptr) {
        return 1;
    }
    auto* file = file_api::open();
    if (file == nullptr) {
        std::cerr << "Environment cannot create a temporary file\n";
        return 2;
    }
    const bool wrote = std::fputs("M0\n", file) >= 0;
    std::rewind(file);
    const bool read = std::fgetc(file) == 'M';
    file_api::close(file);
    const auto counts = file_api::stats();
    const bool ok = wrote && read && counts.opened == 1 && counts.closed == 1
                    && counts.invalid_closes == 0 && counts.close_errors == 0
                    && counts.live == 0;
    std::cout << "fixture=" << ok << " opened=" << counts.opened
              << " closed=" << counts.closed << " live=" << counts.live
              << " invalid=" << counts.invalid_closes << '\n';
    return ok ? 0 : 1;
}
