#pragma once

#include "CDF.h"

namespace kiv_vss::func
{
    class Uniform_CDF : public CDF
    {
    public:
        Uniform_CDF(double a, double b);
        ~Uniform_CDF() = default;

        [[nodiscard]] double Get_Min_Boundary() const noexcept override;
        [[nodiscard]] double Get_Max_Boundary() const noexcept override;

        [[nodiscard]] double operator()(double x) const override;

    private:
        double m_a;
        double m_b;
    };
}