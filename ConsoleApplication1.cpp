#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

int main() {
    const int N = 1000;
    int a[N], b[N], c[N];
    int x1[N], x2[N];

    // Initialize random seed
    srand(time(nullptr));

    // Set up outer parallel loop
#pragma omp parallel num_threads(8)
    {
        // Fork inner parallel loop
#pragma omp parallel for schedule(guided)
        for (int i = 0; i < N; i++) {
            // Generate random quadratic equation
            a[i] = rand() % 201 - 100;
            b[i] = rand() % 201 - 100;
            c[i] = rand() % 201 - 100;

            // Solve quadratic equation
            int d = b[i] * b[i] - 4 * a[i] * c[i];
            if (d >= 0) {
                x1[i] = (-b[i] + sqrt(d)) / (2 * a[i]);
                x2[i] = (-b[i] - sqrt(d)) / (2 * a[i]);
            }
            else {
                x1[i] = x2[i] = 0;
            }

            // Print the solutions
            std::cout << "Equation " << i << ": x1 = " << x1[i] << ", x2 = " << x2[i] << std::endl;
        }
    }

    return 0;
}
