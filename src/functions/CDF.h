#pragma once

#include <utility>

namespace kiv_vss::func
{
    class CDF
    {
    public:
        virtual ~CDF() = default;

        [[nodiscard]] virtual double Get_Min_Boundary() const noexcept = 0;
        [[nodiscard]] virtual double Get_Max_Boundary() const noexcept = 0;
        [[nodiscard]] virtual double Get_Mean() const noexcept = 0;
        [[nodiscard]] virtual double Get_Variance() const noexcept = 0;
        
        [[nodiscard]] virtual double operator()(double x) const = 0;
    };
}