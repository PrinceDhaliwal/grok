#ifndef TEST_STATS_H
#define TEST_STATS_H

#include <iostream>
#include <string>

#include "common/colors.h"

namespace grok {
namespace test {

class TestStats {
public:
    TestStats() :
        failed_{ 0 }, passed_{ 0 }
    { }

    void AddFailed()
    {
        failed_++;
    }

    void AddPassed()
    {
        passed_++;
    }

    auto GetPassed() const
    {
        return passed_;
    }

    auto GetFailed() const
    {
        return failed_;
    }

    auto GetTotal() const
    {
        return passed_ + failed_;
    }

    friend std::ostream &operator<<(std::ostream &os, const TestStats &stats)
    {
        os << "Test Stats: " << std::endl;
        if (stats.GetFailed()) {
            os << "Failed: " <<  Color::Color(Color::Colors::fred);
            os << stats.GetFailed() << Color::Reset() << std::endl;
        }
        if (stats.GetPassed()) {
            os << "Passed: " <<  Color::Color(Color::Colors::fgreen);
            os << stats.GetPassed() << Color::Reset() << std::endl;
        }
        return os;
    }
private:
    size_t failed_;
    size_t passed_;    
};

}
}

#endif