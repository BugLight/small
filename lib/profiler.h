#ifndef PROFILER_H
#define PROFILER_H

#ifdef __cplusplus

#include <chrono>
#include <ostream>
#include <unordered_map>
#include <vector>

namespace small {

    struct MemoryProfile {
        using TimePoint = std::chrono::microseconds;

        std::vector<TimePoint> BeginTimes;
        std::vector<TimePoint> EndTimes;
        std::vector<size_t> Sizes;
    };

    std::ostream& operator<<(std::ostream& os, const MemoryProfile& profile);

    class Profiler {
    public:
        static Profiler& Instance() {
            static Profiler instance;
            return instance;
        }

        ~Profiler() noexcept;

        Profiler(const Profiler&) = delete;
        Profiler(Profiler&&) = delete;
        Profiler& operator=(const Profiler&) = delete;
        Profiler& operator=(Profiler&&) = delete;

        MemoryProfile& GetMemoryProfile(const char* location);
    private:
        Profiler() = default;

        std::unordered_map<const char*, MemoryProfile> Profiles;
    };

};  // namespace small

extern "C" {
#endif  // __cplusplus

void BeginAllocationProfile(const char* location, size_t size);

void EndAllocationProfile(const char* location);

#ifdef __cplusplus
}
#endif  // __cplusplus
#endif  // PROFILER_H

