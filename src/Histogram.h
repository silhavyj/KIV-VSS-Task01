#pragma once

#include <vector>
#include <cstdint>
#include <iostream>
#include <vector>

namespace kiv_vss
{
    class Histogram
    {
    public:
        explicit Histogram(const std::vector<uint32_t>& numbers);
        ~Histogram() = default;

        void Add(uint32_t value);

        friend std::ostream& operator<<(std::ostream& out, Histogram& histogram);

    private:
        std::vector<uint32_t> m_numbers;
        std::vector<size_t> m_buckets;
        size_t m_highest_count;
    };
}