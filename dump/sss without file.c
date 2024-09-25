#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Function to decode value from different bases
long long decode_value(const char* value, int base) {
    return strtoll(value, NULL, base);
}

// Function for Lagrange interpolation to find f(0)
double lagrange_interpolation(int x[], long long y[], int n, int x_target) {
    double result = 0;

    for (int i = 0; i < n; i++) {
        double term = y[i];
        for (int j = 0; j < n; j++) {
            if (i != j) {
                term *= (double)(x_target - x[j]) / (x[i] - x[j]);
            }
        }
        result += term;
    }

    return result;
}

// Function to find the secret (constant term c) using Lagrange interpolation
long long find_secret(int x[], char* values[], int bases[], int n, int k) {
    long long y[k];
    
    // Decode the y values from different bases
    for (int i = 0; i < k; i++) {
        y[i] = decode_value(values[i], bases[i]);
    }

    // Use Lagrange interpolation to find f(0) (the constant term c)
    double secret = lagrange_interpolation(x, y, k, 0);
    
    return llround(secret);
}

int main() {
    // Test case 1
    int n = 4, k = 3;
    int x1[] = {1, 2, 3, 6};
    char* values1[] = {"4", "111", "12", "213"};
    int bases1[] = {10, 2, 10, 4};

    long long secret1 = find_secret(x1, values1, bases1, n, k);
    printf("The secret (constant term c) is: %lld\n", secret1);

    // Test case 2
    n = 9, k = 6;
    int x2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    char* values2[] = {
        "28735619723837", "1A228867F0CA", "32811A4AA0B7B", 
        "917978721331A", "1A22886782E1", "28735619654702", 
        "71AB5070CC4B", "122662581541670", "642121030037605"
    };
    int bases2[] = {10, 16, 12, 11, 16, 10, 14, 9, 8};

    long long secret2 = find_secret(x2, values2, bases2, n, k);
    printf("The secret (constant term c) for the second test case is: %lld\n", secret2);

    return 0;
}
