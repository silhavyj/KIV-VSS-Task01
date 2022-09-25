#pragma once

#include <memory>
#include <vector>
#include <random>
#include <cstdint>
#include <algorithm>

#include "functions/CDF.h"

namespace kiv_vss
{
    template<typename T = double, uint32_t sample_count = 200>
    class Distribution
    {
    public:
        Distribution(std::shared_ptr<func::CDF> cdf)
            : m_sampled_CDF(sample_count)
        {
            // Get the minimum and maximum values that can be generated.
            // This is "observed" by the "shape" of the PDF. CDF will be
            // sampled from [lo; hi].
            const double lo = cdf->Get_Min_Boundary();
            const double hi = cdf->Get_Max_Boundary();

            // Calculate the probabilities of the extreme values. These are
            // used for normalization when calculating the probability of
            // a sample of the CDF.
            const double lo_prob = cdf->operator()(lo);
            const double hi_prob = cdf->operator()(hi);

            // Step (period) used to sample the CDF function.
            double sample_step = (hi - lo) / sample_count;

            for (uint32_t i = 0; i < sample_count; ++i)
            {
                // Get a sample of CDF and calculate its probability (normalized).
                const double value = lo + (i * sample_step);
                const double prob  = ((cdf->operator()(value)) - lo_prob) / (hi_prob - lo_prob);

                // Store the pair into the array of samples.
                m_sampled_CDF[i] = { prob, value };
            }
        }

        ~Distribution() = default;

        template<typename Generator>
        T operator()(Generator& generator)
        {
            // Generate a random number [0; 1] from a uniform distribution.
            double random_01 = m_unform_dis(generator);

            // Binary search its corresponding real value in the array of samples (inverse CBF).
            auto CDF_val_it = std::upper_bound(m_sampled_CDF.begin(), m_sampled_CDF.end(), random_01, CDF_Sample_Cmp);
            
            // Make sure we do not exceed the boundaries.
            if (CDF_val_it == m_sampled_CDF.end())
            {
                --CDF_val_it;
            }

            // Return the value.
            const auto [prob, value] = *CDF_val_it;
            return static_cast<T>(value);
        }

    private:
        static bool CDF_Sample_Cmp(double prob, std::pair<double, double>& sample)
        {
            return prob < sample.first;
        }

    private:
        std::uniform_real_distribution<> m_unform_dis;
        std::vector<std::pair<double, double>> m_sampled_CDF;
    };
}