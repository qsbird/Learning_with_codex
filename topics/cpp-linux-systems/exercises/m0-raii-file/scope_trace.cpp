#include <iostream>
#include <stdexcept>

// Worked example: logs object lifetime; does not manage FileOwner's resource.
class ScopeTrace {
public:
    ScopeTrace(const char* label) : label_(label)
    {
        std::cout << "enter " << label_ << '\n';
    }
    ~ScopeTrace()
    {
        std::cout << "leave " << label_ << '\n';
    }
private:
    const char* label_;
};

void work(bool early, bool fail)
{
    ScopeTrace outer("outer");
    {
        ScopeTrace inner("inner");
        if (early) {
            return;
        }
        if (fail) {
            throw std::runtime_error("demo");
        }
        std::cout << "body\n";
    }
    std::cout << "after inner\n";
}

int main()
{
    std::cout << "=== normal ===\n";
    work(false, false);
    std::cout << "=== return ===\n";
    work(true, false);
    std::cout << "=== exception ===\n";
    try {
        work(false, true);
    } catch (const std::exception& error) {
        std::cout << "caught: " << error.what() << '\n';
    }
}
