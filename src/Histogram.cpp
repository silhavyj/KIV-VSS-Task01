#include <algorithm>
#include <iomanip>
#include <cmath>

#include "Histogram.h"

namespace kiv_vss
{
    Histogram::Histogram(const std::vector<uint32_t>& numbers)
            : m_numbers(numbers),
              m_buckets(numbers.size()),
              m_highest_count{}
    {

    }

    void Histogram::Add(uint32_t value)
    {
        const auto it = std::lower_bound(m_numbers.begin(), m_numbers.end(), value);
        const auto index = it - m_numbers.begin();
        ++m_buckets[index];
        m_highest_count = std::max(m_highest_count, m_buckets[index]);
    }

    std::ostream& operator<<(std::ostream& out, Histogram& histogram)
    {
        static constexpr int BUCKET_WIDTH = 50;
        static constexpr int PRECISION = 4;

        for (size_t i = 0; i < histogram.m_buckets.size(); ++i)
        {
            const size_t width = (histogram.m_buckets[i] * BUCKET_WIDTH) / histogram.m_highest_count;
            out << std::fixed << std::setprecision(PRECISION) << histogram.m_numbers[i] << ':';
            for (size_t j = 0; j < width; ++j)
            {
                out << '*';
            }
            out << '\n';
        }
        return out;
    }
}