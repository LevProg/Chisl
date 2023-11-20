#include <iostream>
#include <list>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <vector>
#include <array>
#include <tuple>

using namespace std;

double func1(double x) {
    return pow(x, 4) + 3 * pow(x, 3) - 9 * x - 9;
}
double func2(double x) {
    return (pow(x, 4) + 3 * pow(x, 3) - 9 * x - 9) / (x - 1);
}
double func3(double x) {
    return 0.25 * pow(x, 3) + x - 1.2502;
}

ofstream file1("result1.txt");//p 3
ofstream file2("result2.txt");//p 4 bis
ofstream file3("result3.txt");//p 4 hor
//f1, f2, f3
array<double, 3> results{0,0,0};
const array < pair<double, double>, 3 > area { pair<int, int>(1,2),pair<double, int>{1.01,2},pair<int, int>{0,2} };//a and b
const array<double (*)(double),3> func{ func1,func2,func3 };


double BisectionMethod(double a, double b, int nfunc, double eps) {
    double (*f)(double)= func[nfunc];
    double res=results[nfunc];
    if (f(a) * f(b) >= 0) {
        return NAN;
    }
    double c = 0.0;
    int iter = 0;
    while ((b - a) >= eps) {
        iter++;
        c = (a + b) / 2;
        if (abs(f(b) - f(a)) < eps) {
            return c;
        }
        if (f(c) * f(a) < 0) {
            b = c;
        }
        else {
            a = c;
        }
        if (results[nfunc] != 0) file1 << abs(c - results[nfunc]) << endl;//p. 3
    }
    if (results[nfunc] != 0) file2 << abs(c - results[nfunc]) << endl;//p. 4
    cout << "Bisection: \t\tx=" << c << "\t" << "Number of iteration: " << iter << endl;
    return c;
}

double HordMethod(double a, double b, int nfunc, double epsilon) {
    double (*f)(double) = func[nfunc];
    double res = results[nfunc];
    double x = a;
    int iter=0;
    while (abs(a - b) >= 2 * epsilon) {
        iter++;
        double fx0 = f(a);
        double fx1 = f(b);
        if (fx1 - fx0 == 0) {
            return x;
        }
        x = b - (fx1 * (b - a)) / (fx1 - fx0);
        a = b;
        b = x;
        if (results[nfunc]!=0) file1 << abs(x - results[nfunc]) << endl;//p. 3

    }
    cout << "HordMethod:\t\t x=" << x <<"\t"<< "Number of iteration: " << iter<<endl;
    if (results[nfunc] != 0) file3 << abs(x - results[nfunc]) << endl;//p. 4
    return x;
}


int main() {
    file1.precision(10);
    file2.precision(10);
    file3.precision(10);
    cout.precision(10);

    for (int i = 0; i < 3; i++) results[i] = BisectionMethod(area[i].first, area[i].second, i, pow(10, -15));
    
    int nfunc = 1;//number of func
    //HordMethod(area[nfunc].first, area[nfunc].second, nfunc, pow(10, -15));//p. 3
    for (int i = -15; i != -1; i++) {//p. 4
        BisectionMethod(area[nfunc].first, area[nfunc].second, nfunc, pow(10, i));
        HordMethod(area[nfunc].first, area[nfunc].second, nfunc, pow(10, i));
    }
    return 0;
}


