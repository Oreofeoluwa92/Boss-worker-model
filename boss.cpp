#include <iostream>
#include <sys/types.h>  // For pid_t
#include <sys/wait.h>   // For wait()
#include <unistd.h>     // For fork(), execl()
#include <cstdlib>      // For atoi()
using namespace std;

int main(int argc, char* argv[]) {
    // Check if the correct number of command-line arguments is provided
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <num_workers> <upper_bound>" << endl;
        return 1;
    }

    // Convert command-line arguments to integers
    int num_workers = atoi(argv[1]);
    int upper_bound = atoi(argv[2]);

    // Calculate the size of the range for each worker
    int range_size = upper_bound / num_workers;

    // Loop to create worker processes
    for (int i = 0; i < num_workers; ++i) {
        // Calculate the start and end of the range for this worker
        int start = i * range_size + 1; // Start of the range for this worker
        int end = (i == num_workers - 1) ? upper_bound : (i + 1) * range_size; // End of range

        // Fork a new process
        pid_t pid = fork();

        if (pid == 0) {
            // Child process
            char start_str[10], end_str[10]; // Buffers to hold the start and end numbers as strings
            sprintf(start_str, "%d", start); // Convert start to string
            sprintf(end_str, "%d", end);     // Convert end to string

            // Execute worker program with the range as arguments
            execl("./worker", "./worker", start_str, end_str, (char*)NULL);
            cerr << "Error: execl() failed!" << endl;
            exit(1);
        }
        else if (pid > 0) {
            // Parent process: Output the range this worker will search
            cout << "Worker " << i + 1 << " searching from " << start << " to " << end << endl;
        }
        else {
            // Fork failed
            cerr << "Error: fork() failed!" << endl;
            return 1;
        }
    }

    // Parent process waits for all worker processes to finish
    for (int i = 0; i < num_workers; ++i) {
        wait(NULL); // Wait for all children to complete
    }

    cout << "All workers completed." << endl;

    return 0; // End of the program
}
