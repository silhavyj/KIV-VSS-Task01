#pragma once

#include "CDF.h"

namespace kiv_vss::func
{
    class Normal_CDF : public CDF
    {
    public:
        Normal_CDF(double mean, double sd);
        ~Normal_CDF() = default;

        [[nodiscard]] double Get_Min_Boundary() const noexcept override;
        [[nodiscard]] double Get_Max_Boundary() const noexcept override;

        [[nodiscard]] double operator()(double x) const override;

    private:
        double m_mean;
        double m_sd;
    };
}