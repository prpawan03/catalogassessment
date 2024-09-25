#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

// Function to parse the JSON-like string and extract n, k, and points
void parse_json(const char *filename, int *n, int *k, int x[], long long y[], int *count) {
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
        if (strstr(line, "\"k\":")) {
            sscanf(line, " \"k\": %d,", k);
        }
        if (sscanf(line, " \"%[^\"]\": { \"base\": \"%[^\"]\", \"value\": \"%[^\"]\" }", key, base_str, value_str) == 3) {
            int base = atoi(base_str);
            x[*count] = atoi(key);  // x is the key
            y[*count] = decode_value(value_str, base);  // y is the decoded value
            (*count)++;
        }
    }

    fclose(file);
}

// Function to find the secret (constant term c) using Lagrange interpolation
long long find_secret(const char *filename) {
    int n, k, count;
    int x[100];  // Assuming at most 100 points
    long long y[100];

    // Parse the JSON-like file to extract n, k, x[], and y[]
    parse_json(filename, &n, &k, x, y, &count);

    // We only need k points to reconstruct the secret
    // The secret is f(0)
    double secret = lagrange_interpolation(x, y, k, 0);
    return llround(secret);
}

int main() {
    // Find and print the secret for test case 1 (file: "test_case_1.json")
    long long secret1 = find_secret("test_case_1.json");
    printf("The secret (constant term c) for test case 1 is: %lld\n", secret1);

    // Find and print the secret for test case 2 (file: "test_case_2.json")
    long long secret2 = find_secret("test_case_2.json");
    printf("The secret (constant term c) for test case 2 is: %lld\n", secret2);

    return 0;
}
