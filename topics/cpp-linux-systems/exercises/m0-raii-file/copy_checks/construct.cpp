#include "file_owner.h"

int main()
{
    m0::FileOwner a(nullptr);
    m0::FileOwner b(a);
    // TODO: Use a to initialize a NEW FileOwner and trigger the deleted copy constructor.
}
