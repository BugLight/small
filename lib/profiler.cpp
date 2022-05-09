#include "profiler.h"

#include <chrono>
#include <fstream>

namespace small {

std::ostream& operator<<(std::ostream& os, const MemoryProfile& profile) {
    const auto size = std::min(profile.BeginTimes.size(), profile.EndTimes.size(), profile.Sizes.size());
    for (auto i = 0; i < size; ++i) {
        os << profile.BeginTimes[i] << '\t'
           << profile.EndTimes[i] << '\t'
           << profile.Sizes[i] << '\n';
    }
    return os;
}

Profiler::~Profiler() noexcept {
    std::ofstream os("profile.txt");
    for (const auto& pair : Profiles) {
        os << pair.first << '\n' << pair.second << '\n';
    }
}


MemoryProfile& Profiler::GetMemoryProfile(char* location) const {
    return Profiles[location];
}


};


void BeginAllocationProfile(const char* location, size_t size) {
    const auto& profiler = small::Profiler::Instance();
    const auto now = std::chrono::steady_clock::now();
    auto& profile = profiler.GetMemoryProfile(location);
    profile.Sizes.emplace_back(size);
    profile.BeginTimes.emplace_back(now);
}

void EndAllocationProfile(const char *location) {
    const auto& profiler = small::Profiler::Instance();
    const auto now = std::chrono::steady_clock::now();
    auto& profile = profiler.GetMemoryProfile(location);
    profile.EndTimes.emplace_back(now);
}

