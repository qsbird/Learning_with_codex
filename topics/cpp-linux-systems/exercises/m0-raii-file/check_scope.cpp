#include "file_owner.h"

#include <iostream>
#include <stdexcept>
#include <string_view>
#include <type_traits>

static_assert(!std::is_copy_constructible_v<m0::FileOwner>);
static_assert(!std::is_copy_assignable_v<m0::FileOwner>);

void use_file(file_api::Handle handle, std::string_view path,
              std::size_t expected_live, bool& alive_while_owned)
{
    m0::FileOwner owner(handle);
    alive_while_owned = file_api::stats().live == expected_live;
    if (path == "return") {
        return;
    }
    if (path == "exception") {
        throw std::runtime_error("expected scope exit");
    }
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        return 2;
    }
    const std::string_view path = argv[1];
    if (path != "normal" && path != "return" && path != "exception" && path != "empty") {
        return 2;
    }
    const auto before = file_api::stats();
    const bool empty = path == "empty";
    auto* handle = file_api::open(empty);
    if (!empty && handle == nullptr) {
        std::cerr << "Environment cannot create a temporary file\n";
        return 2;
    }
    bool alive_while_owned = false;
    bool caught = false;
    try {
        use_file(handle, path, before.live + (empty ? 0 : 1), alive_while_owned);
    } catch (const std::runtime_error& error) {
        caught = std::string_view(error.what()) == "expected scope exit";
    }
    const auto after = file_api::stats();
    const std::size_t acquired = empty ? 0 : 1;
    const bool ok = alive_while_owned
                    && after.opened == before.opened + acquired
                    && after.closed == before.closed + acquired
                    && after.invalid_closes == before.invalid_closes
                    && after.close_errors == before.close_errors
                    && after.live == before.live
                    && caught == (path == "exception");
    std::cout << "case=" << path << " ok=" << ok
              << " opened=" << after.opened << " closed=" << after.closed
              << " live=" << after.live << " invalid=" << after.invalid_closes
              << " close_errors=" << after.close_errors
              << " alive_while_owned=" << alive_while_owned
              << " caught=" << caught << '\n';
    return ok ? 0 : 1;
}
