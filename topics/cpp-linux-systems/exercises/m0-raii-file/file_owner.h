#pragma once

#include "file_api.h"

namespace m0 {
// M0.1: one owner, used without copying or moving.
class FileOwner {
public:
    explicit FileOwner(file_api::Handle handle);
    ~FileOwner();

    FileOwner(const FileOwner&) = delete;
    FileOwner& operator=(const FileOwner&) = delete;

private:
    file_api::Handle handle_ = nullptr;
};
} // namespace m0
