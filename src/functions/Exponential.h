#pragma once

#include "cdf.h"

namespace kiv_vss::func
{
    class Exponential_CDF : public CDF
    {
    public:
        explicit Exponential_CDF(double lambda);
        ~Exponential_CDF() override = default;

        [[nodiscard]] double Get_Min_Boundary() const noexcept override;
        [[nodiscard]] double Get_Max_Boundary() const noexcept override;
        [[nodiscard]] double Get_Mean() const noexcept override;
        [[nodiscard]] double Get_Variance() const noexcept override;

        [[nodiscard]] double operator()(double x) const override;

    private:
        double m_lambda;
    };
}