/*#include <iostream>
#include <cstdint>
#include <random>
#include <vector>
#include <algorithm>
#include <functional>
#include <fstream>
#include <cassert>
#include <memory>

namespace kiv_vss::functions
{
    class CCDF
    {
    public:
        virtual ~CCDF() = default;

        virtual double Get_Min_Boundary() const noexcept = 0;
        virtual double Get_Max_Boundary() const noexcept = 0;
        
        virtual double operator()(double x) const = 0;
    };

    class CNormal_CDF : public CCDF
    {
    public:
        CNormal_CDF(double mean, double sd)
            : m_mean(mean),
              m_sd(sd)
        {

        }

        double Get_Min_Boundary() const noexcept override
        {
            return m_mean - 4 * m_sd;
        }

        double Get_Max_Boundary() const noexcept override
        {
            return m_mean + 4 * m_sd;
        }

        double operator()(double x) const override
        {
            return 0.5 * (1 + std::erf((x - m_mean) / (m_sd * M_SQRT2)));
        }

    private:
        double m_mean;
        double m_sd;
    };

    class CUniform_CDF : public CCDF
    {
    public:
        CUniform_CDF(double a, double b)
            : m_a(a),
              m_b(b)
        {
            
        }

        double Get_Min_Boundary() const noexcept override
        {
            return m_a;
        }

        double Get_Max_Boundary() const noexcept override
        {
            return m_b;
        }

        double operator()(double x) const override
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

    private:
        double m_a;
        double m_b;
    };
}

namespace kiv_vss
{
    template<typename T = double, uint32_t sample_count = 200>
    class CDistribution
    {
    public:
        CDistribution(std::shared_ptr<kiv_vss::functions::CCDF> cdf)
            : m_uniform_distribution(0.0, 1.0),
              m_sampled_CDF(sample_count)
        {
            const double high = cdf->Get_Max_Boundary();
            const double low = cdf->Get_Min_Boundary(); 

            const double cdf_low = (*cdf)(low);
            const double cdf_high = (*cdf)(high);

            for (uint32_t i = 0; i < sample_count; ++i)
            {
                const double value = (i / static_cast<double>(sample_count)) * (high - low) + low;
                const double probability = ((*cdf)(value) - cdf_low) / (cdf_high - cdf_low);

                m_sampled_CDF[i] = { probability, value };
            }
        }

        template<typename Generator>
        T operator()(Generator& generator)
        {
            double random_value_01 = m_uniform_distribution(generator);
            auto CDF_value_it = std::upper_bound(m_sampled_CDF.begin(), m_sampled_CDF.end(), random_value_01);
            if (CDF_value_it == m_sampled_CDF.end())
            {
                return static_cast<T>(m_sampled_CDF.rbegin()->value);
            }
            return static_cast<T>(CDF_value_it->value);
        }

    private:
        struct TSample
        {
            double probability;
            double value;

            friend bool operator<(double probability, const TSample& sample)
            { 
                return probability < sample.probability;
            }
        };

    private:
        std::uniform_real_distribution<> m_uniform_distribution;
        std::vector<TSample> m_sampled_CDF;
    };
}

int main()
{
    std::random_device r;
    
    kiv_vss::CDistribution<> distribution(std::make_shared<kiv_vss::functions::CNormal_CDF>(10, 2));

    std::ofstream file("data.txt");
    
    for (int i = 0; i < 1000; ++i)
    {
        const auto value = distribution(r);
        file << value << "\n";

        std::cout << value << "\n";
    }


    return 0;
}*/

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
    auto cdf = std::make_shared<kiv_vss::func::Exponential_CDF>(2);
    kiv_vss::Distribution<> dis(cdf);
    std::random_device rd{};

    std::ofstream file("data.txt");
    for (int i = 0; i < 1000; ++i)
    {
        const auto value = dis(rd);
        file << value << "\n";

        // std::cout << value << "\n";
    }
}