#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

const int MAX_N = 10000;
const int MAX_M = 100;
const int MAX_T = 30;
double p[MAX_N][3];
double q[MAX_M];
int c[MAX_M];

int cr() {
    int N, M, S, T;
    double d;
    double a[MAX_M][MAX_T], xi[MAX_M];

    srand(time(NULL));

    // read input from file
    ifstream fin("galaxies.txt");
    fin >> N;
    for (int i = 0; i < N; i++) {
        fin >> p[i][0] >> p[i][1] >> p[i][2];
    }
    fin >> M;
    for (int i = 0; i < M; i++) {
        fin >> q[i];
        c[i] = 0;
    }
    fin.close();

    // set sampling parameters
    S = 100;
    T = 30;

    // sample objects and count pairs in each distance range
    for (int t = 0; t < T; t++) {
        for (int i = 0; i < M; i++) {
            a[i][t] = 0.0;
        }
        for (int s = 0; s < S; s++) {
            int u1 = rand() % N;
            int u2 = rand() % N;
            while (u2 == u1) {
                u2 = rand() % N;
            }
            d = sqrt(pow(p[u1][0] - p[u2][0], 2) +
                     pow(p[u1][1] - p[u2][1], 2) +
                     pow(p[u1][2] - p[u2][2], 2));
            for (int i = 0; i < M; i++) {
                if (d <= q[i]) {
                    c[i]++;
                    a[i][t] += 1.0;
                    break;
                }
            }
        }
    }

    // compute correlation function
    for (int i = 0; i < M; i++) {
        xi[i] = 0.0;
        for (int t = 0; t < T; t++) {
            xi[i] += a[i][t];
        }
        xi[i] /= T * S;
    }

    // save correlation function in file
    ofstream fout("correlation.txt");
    //fout<<"distance range\tCF"<<endl;
    for (int i = 0; i < M; i++) {
        fout << q[i] << " " << xi[i] << endl;
    }
    fout.close();
    cout << "Correlation function saved to file." << endl;

    return 0;
}
