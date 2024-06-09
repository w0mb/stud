#include <iostream>
#include <cmath>
#include <vector>

#define e 2.7182818

using namespace std;

// Функция для вычисления y' = z
double f1(double x, double y, double z)
{
    return z;
}

// Функция для вычисления z' = (e^x + y + z) / 3
double f2(double x, double y, double z)
{
    return (pow(e, x) + y + z) / 3;
}

// Функция для метода Рунге-Кутта 4-го порядка
void rungeKutta4(double x0, double y0, double z0, double h, int iterations, vector<double> &x_arr, vector<double> &y_arr)
{
    double x = x0;
    double y = y0;
    double z = z0;

    for (int i = 0; i < iterations; ++i)
    {
        double k1_y = h * f1(x, y, z); // к - шаг умноженный на производную в начальной точке интервала
        double k1_z = h * f2(x, y, z); // 4 К ПОТОМУ ЧТО 4 ЧЛЕНА РЯДА ТЕЙЛОРА

        double k2_y = h * f1(x + h / 2, y + k1_y / 2, z + k1_z / 2); // шаг умноженный на производную в среёёдней точке интервала
        double k2_z = h * f2(x + h / 2, y + k1_y / 2, z + k1_z / 2);

        double k3_y = h * f1(x + h / 2, y + k2_y / 2, z + k2_z / 2); // тоже в средней точке интервала//производные апроксимируются в точках на отдельно рассматриваемом интервале
        double k3_z = h * f2(x + h / 2, y + k2_y / 2, z + k2_z / 2);

        double k4_y = h * f1(x + h, y + k3_y, z + k3_z); // шаг на производную в последней точке интервала//рекурентная формула (следующее через предыдущее)
        double k4_z = h * f2(x + h, y + k3_y, z + k3_z); // производная находится в каждой точке решения 4 раза(затем усредняется) - метод 4 порядка(чем больше производных тем больше точность)

        y = y + (k1_y + 2 * k2_y + 2 * k3_y + k4_y) / 6;
        z = z + (k1_z + 2 * k2_z + 2 * k3_z + k4_z) / 6;
        x = x + h;

        x_arr.push_back(x);
        y_arr.push_back(y);

        cout << "step#" << i + 1 << ": x = " << x << ", y = " << y << ", z = " << z << endl;
    }
}

// Функция для интерполяции методом Лагранжа
double lagrange(vector<double> &x_arr, vector<double> &y_arr, int n, double x)
{
    double result = 0.0;
    for (int i = 0; i <= n; ++i)
    {
        double q = 1.0;
        for (int j = 0; j <= n; ++j)
        {
            if (i != j)
            {
                q *= (x - x_arr[j]) / (x_arr[i] - x_arr[j]);
            }
        }
        result += y_arr[i] * q;
    }
    return result;
}

// Функция для метода Рунге-Кутта 2-го порядка
void rungeKutta2(double x0, double y0, double z0, double h, int iterations, vector<double> &x_arr, vector<double> &y_arr)
{
    double x = x0;
    double y = y0;
    double z = z0;

    for (int i = 0; i < iterations; ++i)
    {
        double k1_y = h * f1(x, y, z);
        double k1_z = h * f2(x, y, z);

        double k2_y = h * f1(x + h, y + k1_y, z + k1_z);
        double k2_z = h * f2(x + h, y + k1_y, z + k1_z);

        y = y + (k1_y + k2_y) / 2;
        z = z + (k1_z + k2_z) / 2;
        x = x + h;

        x_arr.push_back(x);
        y_arr.push_back(y);

        cout << "step#" << i + 1 << ": x = " << x << ", y = " << y << ", z = " << z << endl;
    }
}

int main()
{
    double x0 = 0.0, y0 = 1.0, z0 = 1.0;
    double h = 0.1;      // шаг для метода Рунге-Кутта
    int iterations = 10; // количество итераций для метода Рунге-Кутта

    vector<double> x_arr = {x0};
    vector<double> y_arr = {y0};

    cout << "========================== Runge-Kutta 4 tier ==========================" << endl;
    rungeKutta4(x0, y0, z0, h, iterations, x_arr, y_arr);

    cout << "========================== Runge-Kutta 2 tier ==========================" << endl;
    rungeKutta2(x0, y0, z0, h, iterations, x_arr, y_arr);

    // Узлы интерполяции. Их надо менять если препод выебнится - первом делом поменяйте это значение
    vector<double> interpolation_points = {0.1488};

    cout << "========================== Lagra-Interpolation ==========================" << endl;
    for (double x : interpolation_points)
    {
        double y_interpolated = lagrange(x_arr, y_arr, iterations, x);
        cout << "interpolation in x = " << x << " : y = " << y_interpolated << endl;
    }

    return 0;
}
