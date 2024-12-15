#include <iostream>

using namespace std;
const int INF = 1000000;
class Matrix {
public:
    int **a;     //2d array pointer to store matrix values
    int size;    //matrix size (n)

    //constructor to initialize matrix with a given size and initial value
    Matrix(int sz, int init) : size(sz) {
        //allocate memory for a 2d array
        a = new int*[size];
        for (int i = 0; i < size; i++) {
            a[i] = new int[size];
            for (int j = 0; j < size; j++) {
                a[i][j] = init; //initialize with the given value (e.g., INT_MAX)
            }
        }
    }

    //copy constructor to handle deep copy
    Matrix(const Matrix &other) : size(other.size) {
        a = new int*[size];
        for (int i = 0; i < size; i++) {
            a[i] = new int[size];
            for (int j = 0; j < size; j++) {
                a[i][j] = other.a[i][j]; //sdeep copy of the data
            }
        }
    }

    //assignment operator to handle deep copy
    Matrix& operator=(const Matrix &other) {
        if (this == &other) return *this; //handle self-assignment

        //clean up the existing memory
        for (int i = 0; i < size; i++) {
            delete[] a[i];
        }
        delete[] a;

        //allocate new memory and copy the data
        size = other.size;
        a = new int*[size];
        for (int i = 0; i < size; i++) {
            a[i] = new int[size];
            for (int j = 0; j < size; j++) {
                a[i][j] = other.a[i][j]; //deep copy of the data
            }
        }

        return *this;
    }

    ~Matrix() {
        for (int i = 0; i < size; i++) {
            delete[] a[i];
        }
        delete[] a;
    }

    //min-plus algebra
    Matrix operator* (const Matrix &ctx) const {
        Matrix product(size, INF); //initialize product matrix with large values
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                for (int k = 0; k < size; k++) {
                    if (a[i][j] != INF && ctx.a[j][k] != INF) { //if paths exist
                        product.a[i][k] = min(product.a[i][k], a[i][j] + ctx.a[j][k]);
                    }
                }
            }
        }
        return product;
    }

private:
    int min(int x, int y) const {
        return (x < y) ? x : y;
    }
};

Matrix exp_pow(Matrix dist, int k) {
    int size = dist.size;
    Matrix total(size, INF);
    for (int i = 0; i < size; i++) {
        total.a[i][i] = 0; //distance to self is zero
    }
    while (k > 0) {
        if (k % 2) {
            total = total * dist;
        }
        dist = dist * dist;
        k /= 2;
    }
    return total;
}

int main() {
    int n; //nodes
    cin >> n;

    Matrix dist(n, INF); //initialize with large values

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int weight;
            cin >> weight;
            if (weight != -1) { // -1 -no edge
                dist.a[i][j] = weight;
            }
        }
    }

    Matrix result = exp_pow(dist, n - 1);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (result.a[i][j] == INF) cout << "INF ";
            else cout << result.a[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}