#include "Uniform.h"

namespace kiv_vss::func
{
    Uniform_CDF::Uniform_CDF(double a, double b)
        : m_a(a),
          m_b(b)
    {

    }

    [[nodiscard]] double Uniform_CDF::Get_Min_Boundary() const noexcept
    {
        return m_a;
    }

    [[nodiscard]] double Uniform_CDF::Get_Max_Boundary() const noexcept
    {
        return m_b;
    }

    [[nodiscard]] double Uniform_CDF::operator()(double x) const
    {
        if (x < m_a)
        {
            return 0;
        }
        else if (x > m_b)
        {
            return 1;
        }
        return (x - m_a) / (m_b - m_a);
    }
}