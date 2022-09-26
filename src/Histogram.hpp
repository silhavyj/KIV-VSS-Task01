#pragma once

#include <vector>
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <iomanip>

namespace kiv_vss
{
    template<typename T = double>
    class Histogram
    {
    public:
        Histogram(T min, T max, uint32_t bucket_count)
            : m_min(min),
              m_buckets(bucket_count + 1),
              m_bucket_size((max - min) / bucket_count)
        {

        }

        ~Histogram() = default;

        void Add(T value)
        {
            const auto bucket_id = static_cast<size_t>((value - m_min) / m_bucket_size);
            ++m_buckets[bucket_id];
        }

        template<typename E = double>
        friend std::ostream& operator<<(std::ostream& out, Histogram<E>& histogram)
        {
            static constexpr int BUCKET_WIDTH = 50;
            static constexpr int PADDING = 10;

            const size_t highest_count = histogram.Get_Highest_Count();

            for (size_t i = 0; i < histogram.m_buckets.size(); ++i)
            {
                const size_t width = (histogram.m_buckets[i] * BUCKET_WIDTH) / highest_count;
                out << std::setw(PADDING) << (histogram.m_min + (i * histogram.m_bucket_size)) << ": ";
                for (size_t j = 0; j < width; ++j)
                {
                    out << '*';
                }
                out << '\n';
            }
            return out;
        }

    private:
        [[nodiscard]] size_t Get_Highest_Count() const
        {
            return *std::max_element(m_buckets.begin(), m_buckets.end());
        }

    private:
        T m_min;
        std::vector<size_t> m_buckets;
        T m_bucket_size;
    };
}