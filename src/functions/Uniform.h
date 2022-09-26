#pragma once

#include "cdf.h"

namespace kiv_vss::func
{
    class Uniform_CDF : public CDF
    {
    public:
        explicit Uniform_CDF(double a, double b);
        ~Uniform_CDF() override = default;

        [[nodiscard]] double Get_Min_Boundary() const noexcept override;
        [[nodiscard]] double Get_Max_Boundary() const noexcept override;
        [[nodiscard]] double Get_Mean() const noexcept override;
        [[nodiscard]] double Get_Variance() const noexcept override;

        [[nodiscard]] double operator()(double x) const override;

    private:
        double m_a;
        double m_b;
    };
}