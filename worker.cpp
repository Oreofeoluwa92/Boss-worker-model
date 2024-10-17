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

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <start> <end>" << endl;
        return 1;
    }

    int lower = atoi(argv[1]);
    int upper = atoi(argv[2]);

    // Generate file name based on input range
    string filename = "primes_" + to_string(lower) + "_to_" + to_string(upper) + ".txt";
    ofstream file(filename);

    // Check if file opened successfully
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return 1;
    }

    // Iterate through the range and check for primes
   // cout << "Primes found : " << endl;
    for (int i = lower; i <= upper; ++i) {
        if (Prime(i)) {
            file << i << " ";
            cout << i << " ";  // Output prime to console
             // Write prime to file
        }
    }
    std::cout << std::endl;
    file << endl;  // Write a newline at the end of the file
    file.close();  // Close the file

    return 0;
}
