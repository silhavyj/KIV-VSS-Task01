#include <iostream>
#include <random>
#include <memory>
#include <limits>
#include <cmath>
#include <vector>

#include "functions/cdf.h"
#include "functions/Normal.h"
#include "functions/Uniform.h"
#include "functions/Exponential.h"

#include "Distribution.hpp"
#include "Histogram.hpp"

void Run(const std::shared_ptr<kiv_vss::func::CDF>& cdf, size_t count)
{
    try
    {
        kiv_vss::Distribution<> dis(cdf);
        std::random_device rd{};

        size_t n{};
        double mean{};
        double M2{};
        double delta;
        double variance;

        double min = std::numeric_limits<double>::max();
        double max = std::numeric_limits<double>::min();

        kiv_vss::Histogram histogram(cdf->Get_Min_Boundary(), 
                                     cdf->Get_Max_Boundary(), 30);

        for (size_t i = 0; i < count; ++i)
        {
            const auto x = dis(rd);
            histogram.Add(x);

            min = std::min(min, x);
            max = std::max(max, x);

            ++n;
            delta = x - mean;
            mean += delta / n;
            M2 += delta * (x - mean);
        }
        variance = M2 / (n - 1);

        std::cout << "E_teorie=" << cdf->Get_Mean() << '\n';
        std::cout << "D_teorie=" << cdf->Get_Variance() << '\n';
        std::cout << "E_vypocet=" << mean << '\n';
        std::cout << "D_vypocet=" << variance << '\n';

        std::cout << "\n" << histogram << '\n';
    }
    catch (std::runtime_error& e)
    {
        std::cerr << "ERROR: " << e.what() << '\n';
    }
}

int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        std::cerr << "ERROR: Invalid number of parameters\n";
        return 1;
    }

    const size_t count = std::strtoull(argv[1], nullptr, 0);
    const double input_mean = std::strtod(argv[2], nullptr);
    const double input_variance = std::strtod(argv[3], nullptr);

    auto cdf = std::make_shared<kiv_vss::func::Normal_CDF>(input_mean, input_variance);

    Run(cdf, count);
}