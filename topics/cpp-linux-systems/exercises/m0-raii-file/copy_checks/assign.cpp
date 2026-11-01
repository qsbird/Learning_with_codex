#include "file_owner.h"

int main()
{
    m0::FileOwner a(nullptr);
    m0::FileOwner c(nullptr);
    a= c;
    // TODO: Assign a to the ALREADY EXISTING c and trigger deleted copy assignment.
}
