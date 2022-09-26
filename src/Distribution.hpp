// Inspiration from:
// https://www.anycodings.com/1questions/4917543/how-to-create-a-custom-random-distribution-function

#pragma once

#include <memory>
#include <vector>
#include <random>
#include <cstdint>
#include <cassert>
#include <algorithm>

#include "functions/cdf.h"

namespace kiv_vss
{
    template<typename T = double, uint32_t sample_count = 200>
    class Distribution
    {
    public:
        explicit Distribution(const std::shared_ptr<func::CDF>& cdf)
            : m_sampled_CDF(sample_count)
        {
            // Get the minimum and maximum values that can be generated.
            // This is "observed" by the "shape" of the PDF. CDF will be
            // sampled from [lo; hi].
            const double lo = cdf->Get_Min_Boundary();
            const double hi = cdf->Get_Max_Boundary();
            
            if (lo >= hi)
            {
                throw std::runtime_error("Lower boundary must be lower than upper boundary");
            }

            // Calculate the probabilities of the extreme values. These are
            // used for normalization when calculating the probability of
            // a sample of the CDF.
            const double lo_prob = cdf->operator()(lo);
            const double hi_prob = cdf->operator()(hi);

            // Step (period) used to sample the CDF function.
            double sample_step = (hi - lo) / sample_count;
            double previous_prob = 0.0;

            for (uint32_t i = 0; i < sample_count; ++i)
            {
                // Get a sample of CDF and calculate its probability (normalized).
                const double value = lo + (i * sample_step);
                const double prob  = ((cdf->operator()(value)) - lo_prob) / (hi_prob - lo_prob);

                // Make sure that CDF is monotonic.
                if (previous_prob > prob)
                {
                    throw std::runtime_error("CDF is not monotonic");
                }
                previous_prob = prob;

                // Store the pair into the array of samples.
                m_sampled_CDF[i] = { prob, value };
            }
        }

        ~Distribution() = default;

        template<typename Generator>
        T operator()(Generator& generator)
        {
            // Generate a random number [0; 1] from a uniform distribution.
            double random_01 = m_uniform_dis(generator);

            // Binary search its corresponding real value in the array of samples (inverse CBF).
            auto CDF_val_it = std::upper_bound(m_sampled_CDF.begin(), m_sampled_CDF.end(), random_01, CDF_Sample_Cmp);
            
            // Make sure we do not exceed the boundaries.
            if (CDF_val_it == m_sampled_CDF.end())
            {
                --CDF_val_it;
            }

            const auto [prob, value] = *CDF_val_it;
            const auto [prob_prev, value_prev] = *(CDF_val_it - 1);

            // Interpolation between two sampled points.
            if ((CDF_val_it - 1) >= m_sampled_CDF.begin())
            {
                const double ratio = (random_01 - prob_prev) / (prob - prob_prev);
                const double interpolated_value = (ratio * value_prev) + ((1 - ratio) * value); 
                return static_cast<T>(interpolated_value);
            }

            return static_cast<T>(value);
        }

    private:
        static bool CDF_Sample_Cmp(double prob, std::pair<double, double>& sample)
        {
            return prob < sample.first;
        }

    private:
        std::uniform_real_distribution<> m_uniform_dis;
        std::vector<std::pair<double, double>> m_sampled_CDF;
    };
}