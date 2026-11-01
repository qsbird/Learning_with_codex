#pragma once

#include <cstddef>
#include <cstdio>

// Coach-provided test support. Single-threaded use only.
// Use open/close together so lifecycle checks can observe every release.
namespace file_api {
using Handle = std::FILE*;

struct Stats {
    std::size_t opened;
    std::size_t closed;
    std::size_t invalid_closes;
    std::size_t close_errors;
    std::size_t live;
};

// A real temporary file; nullptr if acquisition fails.
// simulate_failure=true returns nullptr without opening any file.
Handle open(bool simulate_failure = false);

// Records invalid/null/double close attempts without calling fclose on them.
// Valid handles are actually closed. Inspect Stats for errors.
void close(Handle handle) noexcept;
Stats stats() noexcept;
} // namespace file_api
