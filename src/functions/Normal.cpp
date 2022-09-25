#include <cmath>

#include "Normal.h"

namespace kiv_vss::func
{
    Normal_CDF::Normal_CDF(double mean, double sd)
        : m_mean(mean),
          m_sd(sd)
    {

    }

    [[nodiscard]] double Normal_CDF::Get_Min_Boundary() const noexcept
    {
        return m_mean - 4 * m_sd;
    }

    [[nodiscard]] double Normal_CDF::Get_Max_Boundary() const noexcept
    {
        return m_mean + 4 * m_sd;
    }
    
    [[nodiscard]] double Normal_CDF::operator()(double x) const
    {
        return 0.5 * (1 + std::erf((x - m_mean) / (m_sd * M_SQRT2)));
    }
}