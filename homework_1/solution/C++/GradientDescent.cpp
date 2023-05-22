#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>

// 定义目标函数
double f(const std::vector<double>& x) {
    int N = x.size();
    double result = 0.0;

    for (int i = 0; i < N / 2; i++) {
        double term1 = 100 * (x[2 * i] * x[2 * i] - x[2 * i + 1]) * (x[2 * i] * x[2 * i] - x[2 * i + 1]);
        double term2 = (x[2 * i] - 1) * (x[2 * i] - 1);
        result += term1 + term2;
    }

    return result;
}

// 计算目标函数的梯度
std::vector<double> gradient(const std::vector<double>& x) {
    int N = x.size();
    std::vector<double> grad(N, 0.0);

    for (int i = 0; i < N / 2; i++) {
        double term1 = 400 * x[2 * i] * (x[2 * i] * x[2 * i] - x[2 * i + 1]);
        double term2 = 2 * (x[2 * i] - 1);

        grad[2 * i] += term1 + term2;
        grad[2 * i + 1] -= 200 * (x[2 * i] * x[2 * i] - x[2 * i + 1]);
    }

    return grad;
}

// 最速梯度下降法求解最优值
std::vector<double> steepestDescent(const std::vector<double>& initialPoint, int maxIterations, double alpha) {
    std::vector<double> x = initialPoint;

    for (int k = 0; k < maxIterations; k++) {
        std::vector<double> grad = gradient(x);

        // 计算步长
        double stepSize = 1.0;
        double c = 0.5; // Armijo准则中的常数


        auto x_new = [](std::vector<double> x, std::vector<double> grad, double stepSize) {
            std::vector<double> res;
            for (size_t i = 0; i < x.size(); ++i) {
                res.push_back(x[i] - stepSize * grad[i]);
            }

            return res;
        };


        while (f(x_new(x, grad, stepSize)) > f(x) - c * stepSize * inner_product(grad.begin(), grad.end(), grad.begin(), 0.0)) {
            stepSize *= alpha;
        }

        // 更新参数
        x = x_new(x, grad, stepSize);
    }

    return x;
}

int main() {
    int N = 1000; // 参数个数，假设为偶数
    int maxIterations = 2000; // 最大迭代次数
    double alpha = 0.5; // 步长缩放因子

    std::vector<double> initialPoint(N, 0.0); // 初始点

    std::vector<double> optimalPoint = steepestDescent(initialPoint, maxIterations, alpha);

    std::cout << "Optimal Point: ";
    for (int i = 0; i < N; i++) {
        std::cout << optimalPoint[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Optimal Value: " << f(optimalPoint) << std::endl;

    return 0;
}
