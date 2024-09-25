#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Set a constant value for k (the number of points needed)
#define K 3

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

// Function to parse the JSON-like string and extract n, and points
void parse_json(const char *filename, int *n, int x[], long long y[], int *count) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        exit(1);
    }

    char line[256];
    char key[10], base_str[10], value_str[256];
    *count = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "\"n\":")) {
            sscanf(line, " \"n\": %d,", n);
        }
        if (sscanf(line, " \"%[^\"]\": { \"base\": \"%[^\"]\", \"value\": \"%[^\"]\" }", key, base_str, value_str) == 3) {
            int base = atoi(base_str);
            x[*count] = atoi(key);  // x is the key
           
