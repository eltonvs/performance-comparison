#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>

#define N 20 // Number of

unsigned long long fat_r(int n);
unsigned long long fat_i(int n);

int main(int argc, char *argv[]) {
    int max_value;
    if (argc > 1)
        std::stringstream(argv[1]) >> max_value;
    else
        max_value = N;
    std::cout << ">>> Max factorial is: " << max_value << std::endl;

    std::ofstream f_out_i("graph/interactive.dat"), f_out_r("graph/recursive.dat");

    for (int i = 0; i <= max_value; i++) {
        double s1 = 0, s2 = 0;
        int precision = 100000;
        for (int j = 0; j < precision; j++) {
            // INTERACTIVE
            auto start = std::chrono::steady_clock::now();
            fat_i(i);
            auto end = std::chrono::steady_clock::now();
            //auto diff = end - start;
            auto diff = std::chrono::duration_cast<std::chrono::nanoseconds> (end - start).count();
            s1 += diff;

            // RECURSIVE
            start = std::chrono::steady_clock::now();
            fat_r(i);
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

unsigned long long fat_r(int n) {
    return (n == 0) ? 1 : n * fat_r(n-1);
}

unsigned long long fat_i(int n) {
    unsigned long long f = 1;
    while (n > 0)
        f *= n, n--;
    return f;
}
