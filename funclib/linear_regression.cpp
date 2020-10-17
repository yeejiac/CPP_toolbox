#include "linear_regression.h"

Linear_regression::Linear_regression(std::vector<double> dependent_variable, std::vector<double> independent_variable)
{
    if(dependent_variable.size()==independent_variable.size())
    {
        logwrite.writeLog("debug", "(Linear_regression) Dataset OK");
        dependent_variable_ = dependent_variable;
        independent_variable_ = independent_variable;
    }
    else
    {
        logwrite.writeLog("error", "(Linear_regression) Leave");
    }
}

void Linear_regression::formula()
{
    int dataset_len = independent_variable_.size();
    double mean_independ = std::accumulate(independent_variable_.begin(),independent_variable_.end(),0)/dataset_len;
    double mean_depend = std::accumulate(dependent_variable_.begin(), dependent_variable_.end(), 0)/dataset_len;
    std::vector<double> temp;
    for(int i = 0; i<dataset_len; i++)
    {
        temp.push_back(independent_variable_[i]*dependent_variable_[i]);
    }
    double var_xy = std::accumulate(temp.begin(), temp.end(), 0) - dataset_len* mean_independ* mean_depend;
    double var_xx = std::accumulate(temp.begin(), temp.end(), 0) - dataset_len* mean_depend* mean_depend;
    coefficient_ = var_xy/var_xx;
    intercept_ = mean_depend - coefficient_ * mean_independ;
    logwrite.writeLog("debug", "(Linear_regression) Formula : Y = " + std::to_string(coefficient_) + "*X + " + std::to_string(intercept_));
}


int main()
{
    std::vector<double> x{6, 5, 11};
    std::vector<double> y{2, 3, 9};
    Linear_regression *lr = new Linear_regression(y, x);
    lr->formula();
}