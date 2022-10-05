#include <cxxopts.hpp>

#include <cmath>
#include <iostream>
#include <random>
#include <sys/time.h>
#include <typeinfo>

#define SIZE 100
#define MIN 1
#define MAX 1000000

template <typename T> void xgemm(const int N, const T *A, const T *B, T *C);
template <typename T> void matrix_print(const int N, T *A);
template <typename T>
void xgemm_run(const char *s, cxxopts::ParseResult result, std::mt19937 gen);
double wtime();

int main(int argc, char **argv) {
    cxxopts::Options options("lab2");

    options.add_options()("dgemm", "amount", cxxopts::value<unsigned int>())(
        "sgemm", "amount", cxxopts::value<unsigned int>())(
        "igemm", "amount", cxxopts::value<unsigned int>());

    const auto result = options.parse(argc, argv);

    std::random_device rd;
    std::mt19937 gen(rd());

    xgemm_run<double>("dgemm", result, gen);
    xgemm_run<float>("sgemm", result, gen);
    xgemm_run<int>("igemm", result, gen);

    return 0;
}

template <typename T>
void xgemm_run(const char *s, cxxopts::ParseResult result, std::mt19937 gen) {
    if (result.count(s) == 1) {
        const auto count = result[s].as<unsigned int>();

        if (count != 0) {
            std::uniform_real_distribution<> dist(MIN, MAX);

            T *A = new T[SIZE * SIZE];
            T *B = new T[SIZE * SIZE];
            T *C = new T[SIZE * SIZE];

            for (int i = 0; i < SIZE * SIZE; ++i) {
                A[i] = dist(gen);
                B[i] = dist(gen);
            }

            double time[count] = {0}, avg_time = 0;
            for (unsigned int i = 0; i < count; ++i) {
                time[i] = wtime();
                xgemm(SIZE, A, B, C);
                time[i] = wtime() - time[i];
                avg_time += time[i];
            }
            avg_time /= count;

            double abs_error[count] = {0};
            double rel_error[count] = {0};

            int ins_count = SIZE * SIZE * SIZE * 21;
            double task_perf[count] = {0};
            for (unsigned int i = 0; i < count; ++i) {
                abs_error[i] = fabs(avg_time - time[i]);
                rel_error[i] = (abs_error[i] / time[i]) * 100;
                task_perf[i] = ins_count / time[i];
            }

            for (unsigned int i = 0; i < count; ++i) {
                printf(
                    ";%s;%s;%d;gettimeofday;%f;%d;%f;%f;%f;%f\n",
                    s,
                    typeid(A[0]).name(),
                    ins_count,
                    time[i],
                    i + 1,
                    avg_time,
                    abs_error[i],
                    rel_error[i],
                    task_perf[i]);
            }

            // matrix_print(SIZE, A);
            // std::cout << std::endl;
            // matrix_print(SIZE, B);
            // std::cout << std::endl;
            // matrix_print(SIZE, C);

            delete[] A;
            delete[] B;
            delete[] C;
        }
    }
}

template <typename T> void xgemm(const int N, const T *A, const T *B, T *C) {
    int i, j, k;

    for (i = 0; i < N; ++i)
        for (j = 0; j < N; ++j)
            for (k = 0; k < N; ++k)
                C[i * N + j] += A[i * N + k] * B[k * N + j];
}

template <typename T> void matrix_print(const int N, T *A) {
    int i, j;

    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j)
            std::cout << A[i * N + j] << " ";
        std::cout << std::endl;
    }
}

double wtime() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}