#ifndef LINEAR_REGRESSION_H_
#define LINEAR_REGRESSION_H_

#include <iostream>
#include <math.h>
#include <vector>
#include <numeric>

#include "logwriter.h"

class Linear_regression
{

public:
    Linear_regression(std::vector<double> dependent_variable, std::vector<double> independent_variable);
    void formula();
    void training();
    ~Linear_regression();
    Logwriter logwrite = Logwriter("Linear_regression");

private:
    std::vector<double> dependent_variable_;
    std::vector<double> independent_variable_;
    double coefficient_;
    double intercept_;
};




#endif