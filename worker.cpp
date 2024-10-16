#include <iostream>
#include <cstdlib>  // For atoi
#include <cmath>    // For sqrt
#include <fstream>
using namespace std;

bool Prime(int num) {
    if (num <= 1) return false;
    if (num == 2) return true;  // 2 is prime
    if (num % 2 == 0) return false;  // even numbers > 2 are not prime

    for (int i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <start> <end>" << endl;
        return 1;
    }

    int lower = atoi(argv[1]);
    int upper = atoi(argv[2]);


    string filename = "primes_" + to_string(lower) + "_to_" + to_string(upper) + ".txt";
    ofstream file(filename);

    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return 1;
    }


    for (int i = lower; i <= upper; ++i) {
        if (Prime(i)) {
            cout << i << " ";
            file << i << " ";
        }
    }

    file << endl;
    file.close();

    return 0;
}


