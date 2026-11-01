#include "file_api.h"

#include <algorithm>
#include <vector>

namespace {
std::vector<file_api::Handle> handles;
std::size_t opened = 0;
std::size_t closed = 0;
std::size_t invalid_closes = 0;
std::size_t close_errors = 0;
}

file_api::Handle file_api::open(bool simulate_failure)
{
    if (simulate_failure) {
        return nullptr;
    }
    Handle handle = std::tmpfile();
    if (handle == nullptr) {
        return nullptr;
    }
    try {
        handles.push_back(handle);
    } catch (...) {
        std::fclose(handle);
        throw;
    }
    ++opened;
    return handle;
}

void file_api::close(Handle handle) noexcept
{
    const auto pos = std::find(handles.begin(), handles.end(), handle);
    if (handle == nullptr || pos == handles.end()) {
        ++invalid_closes;
        return;
    }
    handles.erase(pos);
    if (std::fclose(handle) != 0) {
        ++close_errors;
    }
    ++closed;
}

file_api::Stats file_api::stats() noexcept
{
    return {opened, closed, invalid_closes, close_errors, handles.size()};
}
