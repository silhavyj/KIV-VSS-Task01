#pragma once

#include <vector>
#include <cstdint>
#include <iostream>

namespace kiv_vss
{
    class Histogram
    {
    public:
        Histogram(double min, double max, uint32_t bucket_count);
        ~Histogram() = default;

        void Add(double value);

        friend std::ostream& operator<<(std::ostream& out, Histogram& histogram);

    private:
        [[nodiscard]] size_t Get_Highest_Count() const;

    private:
        double m_min;
        std::vector<size_t> m_buckets;
        double m_bucket_size;
    };
}