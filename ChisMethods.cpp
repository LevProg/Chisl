#include <iostream>
#include <cmath>
#include <fstream>
#include <array>
#include <tuple>
#include <vector>

using namespace std;

double random(int r) {
    srand(time(0) + r);
    return 1 + (rand() % (2*r+1) - r) * pow(10, -2);
}

double func1(double x, double per) {
    per = random(per);
    return per*pow(x, 4) + 3 * pow(x, 3) - 9 * x - 9;
}
double func2(double x, double per) {
    per = random(per);
    return (per*pow(x, 4) + 3 * pow(x, 3) - 9 * x - 9) / (x - 1);
}
double func3(double x, double per) {
    per = random(per);
    return per*0.25 * pow(x, 3) + x - 1.2502;
}

ofstream file1("result1.txt");//p 3
ofstream file2("result2.txt");//p 4 bis
ofstream file3("result3.txt");//p 4 hor
ofstream file4("result4.txt");//p 5.2 bis
ofstream file5("result5.txt");//p 5.2 hor
//f1, f2, f3
array<double, 3> result{0,0,0};
pair<array<vector<double>, 3>, array<vector<double>, 3>> results;
const array < pair<double, double>, 3 > area { pair<int, int>(1,2),pair<double, int>{1.01,2},pair<int, int>{0,2} };//a and b
const array<double (*)(double, double),3> func{ func1,func2,func3 };


double BisectionMethod(double a, double b, int nfunc, double eps, double per) {
    double (*f)(double, double)= func[nfunc];
    double res=result[nfunc];
    if (f(a, per) * f(b, per) >= 0) {
        return NAN;
    }
    double c = 0.0;
    int iter = 0;
    while ((b - a) >= eps) {
        c = (a + b) / 2;
        if (abs(f(b, per) - f(a, per)) < eps) {
            return c;
        }
        if (f(c, per) * f(a,per) < 0) {
            b = c;
        }
        else {
            a = c;
        }
        if (iter >= results.first[nfunc].size()&& per != 0) break;
        if (result[nfunc] != 0) file1 << abs(c - result[nfunc]) << endl;//p. 3
        if (per != 0) file4 << abs(c - results.first[nfunc].at(iter))/c << ' ';//p. 5.2
        else results.first[nfunc].push_back(c);
        iter++;
    }
    if (result[nfunc] != 0) file2 << abs(c - result[nfunc]) << endl;//p. 4
    cout << "Bisection: \t\tx=" << c << "\t" << "Number of iteration: " << iter << endl;
    if (per != 0) file4 << endl;
    return c;
}

double HordMethod(double a, double b, int nfunc, double epsilon, double per) {
    double (*f)(double, double) = func[nfunc];
    double res = result[nfunc];
    double x = a;
    int iter=0;
    while (abs(a - b) >= 2 * epsilon) {
        iter++;
        double fx0 = f(a, per);
        double fx1 = f(b, per);
        if (fx1 - fx0 == 0) {
            return x;
        }
        x = b - (fx1 * (b - a)) / (fx1 - fx0);
        a = b;
        b = x;
        if (iter >= results.second[nfunc].size()&& per != 0) break;
        if (result[nfunc]!=0) file1 << abs(x - result[nfunc]) << endl;//p. 3
        if (per != 0) file5 << abs(x - results.second[nfunc].at(iter))/x << ' ';//p. 5.2
        else results.second[nfunc].push_back(x);
    }
    cout << "HordMethod:\t\t x=" << x <<"\t"<< "Number of iteration: " << iter<<endl;
    if (result[nfunc] != 0) file3 << abs(x - result[nfunc]) << endl;//p. 4
    if (per != 0) file5 << endl;
    return x;
}


int main() {
    file1.precision(10);file2.precision(10);file3.precision(10);
    file4.precision(10); file5.precision(10);cout.precision(10);
    int nfunc = 2;//number of func

    for (int i = 0; i < 3; i++) result[i] = BisectionMethod(area[i].first, area[i].second, i, pow(10, -15), 0);
 
    HordMethod(area[nfunc].first, area[nfunc].second, nfunc, pow(10, -15), 0);//p. 3
    for (int i = -15; i != -1; i++) {//p. 4
        BisectionMethod(area[nfunc].first, area[nfunc].second, nfunc, pow(10, i), 0);
        HordMethod(area[nfunc].first, area[nfunc].second, nfunc, pow(10, i), 0);
    }
    for (int i = 0; i < 6; i++) {//p. 5.2
        BisectionMethod(area[nfunc].first, area[nfunc].second, nfunc, pow(10, -15), i);
        HordMethod(area[nfunc].first, area[nfunc].second, nfunc, pow(10, -15), i);
    }
    return 0;
}