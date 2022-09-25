#include <cmath>

#include "Exponential.h"

namespace kiv_vss::func
{
    Exponential_CDF::Exponential_CDF(double lambda)
        : m_lambda(lambda)
    {

    }

    [[nodiscard]] double Exponential_CDF::Get_Min_Boundary() const noexcept
    {
        return 0;
    }
 
    [[nodiscard]] double Exponential_CDF:: Get_Max_Boundary() const noexcept
    {
        // TODO
        return 100;
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
        return 1 - std::exp(-m_lambda / x); 
    }
}