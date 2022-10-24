#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <random>

#include "Histogram.h"

// total number of generated numbers
static constexpr uint32_t N = 100000;

using Sample_t = std::pair<uint32_t, double>;

int main(int argc, char* argv[])
{
    // Make sure that user provided a filename as the first parameter.
    if (argc != 2)
    {
        std::cerr << "ERROR: Invalid number of parameters (input file expected)\n";
        return 1;
    }

    // Try to open the file.
    std::fstream file(argv[1], std::ios::in);
    if (!file)
    {
        std::cerr << "ERROR: Failed to open the input file\n";
        return 2;
    }

    std::vector<Sample_t> samples; // contents of the file (number; probability)
    uint32_t number;               // number read from the file
    double probability;            // probability of the number

    double mean_theory{};          // theoretical mean = sum(pi * xi)
    double var_theory{};           // theoretical variance = sum(pi * xi^2) - theoretical mean

    // Read the contents of the file (line by line).
    while (file >> number && file >> probability)
    {
        samples.emplace_back(number, probability);

        mean_theory += number * probability;
        var_theory += number * number * probability;
    }
    var_theory -= (mean_theory * mean_theory);

    // Sort the samples (contents of the file) by the value (NOT the probability),
    // so we have an ascending sequence of number e.g. 1, 6, 8, 10, 15
    std::sort(samples.begin(), samples.end(), [](const auto& x, const auto& y) {
        return x.first < y.first;
    });

    std::vector<uint32_t> values; // array of just the numbers (passed into the histogram)
    
    // Add up all probabilities (calculate the CDF function).
    for (auto it = samples.begin() + 1; it != samples.end(); ++it)
    {
        it->second += (it - 1)->second;
        values.emplace_back((it - 1)->first);
    }
    // Do not forget to add the very last number as well.
    values.emplace_back(samples.rbegin()->first);

    // Sum of all probabilities must be 1.
    constexpr double epsilon = 0.00001;
    if (std::abs(samples.rbegin()->second - 1.0) > epsilon)
    {
        std::cerr << "ERROR: Sum of all probabilities must be 1\n";
        return 3;
    }

    kiv_vss::Histogram histogram(values);            // histogram
    std::random_device rd{};                         // random device used when generating random numbers
    std::uniform_real_distribution<> uniform_dist{}; // uniform distribution (0, 1)

    // Define some values used when calculating actual mean and variance.
    double n{};
    double mean{};
    double M2{};
    double delta;

    // Generate N random numbers from the given discrete distribution.
    for (uint32_t i = 0; i < N; ++i)
    {
        // Generate a random number from (0, 1).
        const double random_01 = uniform_dist(rd);

        // Binary search the number whose added up probability is closest to the generated number (0, 1).
        auto it = std::upper_bound(samples.begin(), samples.end(), random_01, [&](double prob, Sample_t& sample) {
            return prob < sample.second;
        });
        
        // Get the number and add it to the histogram.
        const uint32_t x = it->first;
        histogram.Add(x);

        // Keep calculating the mean and variance.
        ++n;
        delta = x - mean;
        mean += delta / n;
        M2 += delta * (x - mean);
    }
    double var = M2 / (n - 1);

    // Compare theoretical and actual values.
    std::cout << "E_teorie=" << mean_theory << '\n';
    std::cout << "D_teorie=" << var_theory << '\n';
    std::cout << "E_vypocet=" << mean << '\n';
    std::cout << "D_vypocet=" << var << '\n';

    // Print out the histogram.
    std::cout << '\n' << histogram << '\n';
}