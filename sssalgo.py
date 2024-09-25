import json
import numpy as np

def decode_value(value, base):
    return int(value, int(base))

def lagrange_interpolation(x, y, x_target):
    n = len(x)
    result = 0
    for i in range(n):
        term = y[i]
        for j in range(n):
            if i != j:
                term *= (x_target - x[j]) / (x[i] - x[j])
        result += term
    return result

def find_secret(data):
    keys = data['keys']
    n, k = keys['n'], keys['k']
    
    x = []
    y = []
    
    for i in range(1, n+1):
        if str(i) in data:
            point = data[str(i)]
            x.append(i)
            y.append(decode_value(point['value'], point['base']))
    
    # We only need k points to reconstruct the secret
    x = x[:k]
    y = y[:k]
    
    # The secret is f(0)
    secret = round(lagrange_interpolation(x, y, 0))
    return secret

# JSON input as a string
json_input = '''
{
    "keys": {
        "n": 4,
        "k": 3
    },
    "1": {
        "base": "10",
        "value": "4"
    },
    "2": {
        "base": "2",
        "value": "111"
    },
    "3": {
        "base": "10",
        "value": "12"
    },
    "6": {
        "base": "4",
        "value": "213"
    }
}
'''

# Parse JSON data
data = json.loads(json_input)

# Find and print the secret
secret = find_secret(data)
print(f"The secret (constant term c) is: {secret}")

# Second test case
json_input_2 = '''
{
    "keys": {
        "n": 9,
        "k": 6
    },
    "1": {
        "base": "10",
        "value": "28735619723837"
    },
    "2": {
        "base": "16",
        "value": "1A228867F0CA"
    },
    "3": {
        "base": "12",
        "value": "32811A4AA0B7B"
    },
    "4": {
        "base": "11",
        "value": "917978721331A"
    },
    "5": {
        "base": "16",
        "value": "1A22886782E1"
    },
    "6": {
        "base": "10",
        "value": "28735619654702"
    },
    "7": {
        "base": "14",
        "value": "71AB5070CC4B"
    },
    "8": {
        "base": "9",
        "value": "122662581541670"
    },
    "9": {
        "base": "8",
        "value": "642121030037605"
    }
}
'''

# Parse second JSON data
data_2 = json.loads(json_input_2)

# Find and print the secret for the second test case
secret_2 = find_secret(data_2)
print(f"The secret (constant term c) for the second test case is: {secret_2}")
