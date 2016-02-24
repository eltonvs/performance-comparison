#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>

#define N 20 // Number of

unsigned long long fib_r(int n);
unsigned long long fib_i(int n);

int main(int argc, char *argv[]) {
    int max_value;
    if (argc > 1)
        std::stringstream(argv[1]) >> max_value;
    else
        max_value = N;
    std::cout << ">>> Max fibonacci is: " << max_value << std::endl;

    std::ofstream f_out_i("graph/interactive.dat"), f_out_r("graph/recursive.dat");

    for (int i = 0; i <= max_value; i++) {
        double s1 = 0, s2 = 0;
        int precision = 1;
        for (int j = 0; j < precision; j++) {
            // INTERACTIVE
            auto start = std::chrono::steady_clock::now();
            fib_i(i);
            auto end = std::chrono::steady_clock::now();
            //auto diff = end - start;
            auto diff = std::chrono::duration_cast<std::chrono::nanoseconds> (end - start).count();
            s1 += diff;

            // RECURSIVE
            start = std::chrono::steady_clock::now();
            fib_r(i);
            end = std::chrono::steady_clock::now();
            diff = std::chrono::duration_cast<std::chrono::nanoseconds> (end - start).count();
            s2 += diff;
        }

        s1 /= precision, s2 /= precision;
        f_out_i << i << " " << s1 << "\n";
        f_out_r << i << " " << s2 << "\n";
        std::cout << "Elapsed Time = " << s1 << " ns | " << s2 << " ns" << std::endl;
    }

    f_out_i.close();
    f_out_r.close();

    // Generate Graph
    std::system("gnuplot -p 'graph/plot.gp'");

    return EXIT_SUCCESS;

}

unsigned long long fib_r(int n) {
    return (n == 0 || n == 1) ? n : fib_r(n-1) + fib_r(n-2);
}

unsigned long long fib_i(int n) {
    unsigned long long f = n, f0 = 0, f1 = 1;
    for (int i = 2; i <= n; i++)
        f = f0 + f1, f0 = f1, f1 = f;
    return f;
}
