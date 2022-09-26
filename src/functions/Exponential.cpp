#include <cmath>
#include <stdexcept>

#include "Exponential.h"

namespace kiv_vss::func
{
    Exponential_CDF::Exponential_CDF(double lambda)
        : m_lambda(lambda)
    {
        if (m_lambda <= 0)
        {
            throw std::runtime_error("Lambda must be > 0");
        }
    }

    [[nodiscard]] double Exponential_CDF::Get_Min_Boundary() const noexcept
    {
        return 0;
    }
 
    [[nodiscard]] double Exponential_CDF:: Get_Max_Boundary() const noexcept
    {
        static constexpr double LOWEST_PROB = 0.05;
        return -std::log(LOWEST_PROB / m_lambda) * (1 / m_lambda);
    }

    [[nodiscard]] double Exponential_CDF::Get_Mean() const noexcept
    {
        return 1 / m_lambda;
    }

    [[nodiscard]] double Exponential_CDF::Get_Variance() const noexcept
    {
        return 1 / (m_lambda * m_lambda);
    }

    [[nodiscard]] double Exponential_CDF::operator()(double x) const
    {
        return 1 - std::exp(-m_lambda * x); 
    }
}