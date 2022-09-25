#include <iostream>
#include <random>
#include <memory>
#include <fstream>

#include "functions/CDF.h"
#include "functions/Normal.h"
#include "functions/Uniform.h"
#include "functions/Exponential.h"
#include "Distribution.hpp"

int main()
{
    auto cdf = std::make_shared<kiv_vss::func::Normal_CDF>(10, 4);
    kiv_vss::Distribution<> dis(cdf);
    std::random_device rd{};

    double mean{};
    size_t n{};
    double M2{};
    double delta{};

    std::ofstream file("data.txt");
    for (int i = 0; i < 1000; ++i)
    {
        const auto x = dis(rd);
    
        ++n;
        delta = x - mean;
        mean += delta / n;
        M2 += delta * (x - mean);
        
        file << x << "\n";
    }
    double variance = M2 / (n - 1);

    std::cout << "E_teorie="  << cdf->Get_Mean() << '\n';
    std::cout << "D_teorie="  << cdf->Get_Variance() << '\n';
    std::cout << "E_vypocet=" << mean << '\n';
    std::cout << "D_vypocet"  << variance << '\n';
}