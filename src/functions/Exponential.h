#pragma once

#include "CDF.h"

namespace kiv_vss::func
{
    class Exponential_CDF : public CDF
    {
    public:
        Exponential_CDF(double lambda);
        ~Exponential_CDF() = default;

        [[nodiscard]] double Get_Min_Boundary() const noexcept override;
        [[nodiscard]] double Get_Max_Boundary() const noexcept override;

        [[nodiscard]] double operator()(double x) const override;

    private:
        double m_lambda;
    };
}