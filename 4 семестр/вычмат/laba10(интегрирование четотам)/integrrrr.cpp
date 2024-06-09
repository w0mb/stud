#include <iostream>
#include <cmath>

using namespace std;

// Функция, которую мы интегрируем
double f(double x, double y) {
    return sin(x); 
}

// Метод трапеций для двойного интеграла с указанной точностью
double integrate_trapezoidal(double a, double b, double c, double d, double epsilon) {
    int n = 1;      // Начальное количество разбиений по оси x
    int m = 1;      // Начальное количество разбиений по оси y
    double h1, h2;
    double sum = 0.0;
    double prev_sum;
    int count = 0;

    do {
        prev_sum = sum;
        sum = 0.0;
        h1 = (b - a) / n;
        h2 = (d - c) / m;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                double x = a + (i + 0.5) * h1;
                double y = c + (j + 0.5) * h2;
                sum += f(x, y);
                count++;
            }
        }
        sum *= h1 * h2;
        n *= 2;
        m *= 2;
    } while (abs(sum - prev_sum) > epsilon);

    cout << "tochost methoda trapecii: " << epsilon << endl;
    cout << "iter count trap method: " << count << endl;
    return sum;
}

// Метод Симпсона для двойного интеграла с указанной точностью
double integrate_simpson(double a, double b, double c, double d, double epsilon) {
    int n = 1;      // Начальное количество разбиений по оси x
    int m = 1;      // Начальное количество разбиений по оси y
    double h1, h2;
    double sum = 0.0;
    double prev_sum;
    int count = 0;

    do {
        prev_sum = sum;
        sum = 0.0;
        h1 = (b - a) / n;
        h2 = (d - c) / m;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                double x0 = a + i * h1;
                double x1 = a + (i + 1) * h1;
                double y0 = c + j * h2;
                double y1 = c + (j + 1) * h2;
                sum += (f(x0, y0) + 4 * f((x0 + x1) / 2, y0) + f(x1, y0) +
                        4 * f(x0, (y0 + y1) / 2) + 16 * f((x0 + x1) / 2, (y0 + y1) / 2) + 4 * f(x1, (y0 + y1) / 2) +
                        f(x0, y1) + 4 * f((x0 + x1) / 2, y1) + f(x1, y1));
                count++;
            }
        }
        sum *= (h1 * h2 / 36.0);
        n *= 2;
        m *= 2;
    } while (abs(sum - prev_sum) > epsilon);

    cout << "tochost methoda simpsona   : " << epsilon << endl;
    cout << "iter count simpson method: " << count << endl;
    return sum;
}

int main() {
    double a = 0.0; // Нижний предел интегрирования по оси x
    double b = 1.0; // Верхний предел интегрирования по оси x
    double c = 0.0; // Нижний предел интегрирования по оси y
    double d = 1.0; // Верхний предел интегрирования по оси y
    double epsilon = 1e-7; // Точность

    double result_trap = integrate_trapezoidal(a, b, c, d, epsilon);
    double result_simpson = integrate_simpson(a, b, c, d, epsilon);

    cout.precision(15);
    cout << "Trapecii res: " << result_trap << endl;
    cout.precision(15);
    cout << "Simpson res: " << result_simpson << endl;

    return 0;
}
