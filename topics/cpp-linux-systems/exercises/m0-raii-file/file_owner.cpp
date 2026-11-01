#include "file_owner.h"

m0::FileOwner::FileOwner(file_api::Handle handle)
{
    // TODO: Retain the acquired handle so this object owns its release.
    handle_ = handle;
    return;
}

m0::FileOwner::~FileOwner()
{
    // TODO: Release an owned file exactly once; an empty owner does nothing.
    if (handle_ != nullptr) {
        file_api::close(handle_);
    }
    return;
}
