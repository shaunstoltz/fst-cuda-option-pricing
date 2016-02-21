#include "parameters.h"

#include <assert.h>
#include <cmath>

#include "utils.h"

Parameters::Parameters()
: startPrice(100.0)
, strikePrice(100.0)
, riskFreeRate(0.05)
, dividendRate(0.02)
, expiryTime(10.0)
, volatility(0.15)
, driftRate(-1.08)
, normalStdev(0.4)
, logBoundary(7.5)
, resolution(2048)
, timesteps(1)
, optionPayoffType(Put)
, optionExerciseType(European)
{
    assert(isPowerOfTwo(resolution));

    timeIncrement = expiryTime / resolution;

    // No jumps.
    jumpMean = 0.0;
    kappa = 0.0;
}

void Parameters::enableJumps()
{
    // When jumps were not enabled, the mean should be zero.
    assert(jumpMean == 0.0);
    jumpMean = 0.1;

    // Calculation of kappa, see p.13 of paper
    kappa = exp(driftRate + normalStdev * normalStdev / 2.0) - 1.0;
}
