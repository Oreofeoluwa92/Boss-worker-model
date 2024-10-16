#include <iostream>
#include <sys/types.h>  // For pid_t
#include <sys/wait.h>   // For wait()
#include <unistd.h>     // For fork(), execl()
#include <cstdlib>      // For atoi()
using namespace std;

int main(int argc, char *argv[]) {
    // Check if correct number of command-line arguments is provided
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
        int start = i * range_size + 1; // Start of the range for this worker
        int end = (i == num_workers - 1) ? upper_bound : (i + 1) * range_size; // End of range

        // Fork a new process
        pid_t pid = fork();
        
        if (pid == 0) {
            // Child process: Run the worker program using execl()
            char start_str[10], end_str[10]; // Buffers to hold the start and end numbers as strings
            sprintf(start_str, "%d", start); // Convert start to string
            sprintf(end_str, "%d", end);     // Convert end to string

            execl("./worker", "./worker", start_str, end_str, (char*)NULL); // Execute the worker program
            cerr << "Error: execl() failed!" << endl; // This line is reached only if execl() fails
            exit(1); // Exit the child process if execl fails
        } 
        else if (pid > 0) {
            // Parent process: Wait for the child to finish
            wait(NULL); // Wait for the worker process to complete
            //cout << "searching " << start << " to " << end << endl;
        } 
        else {
            // Fork failed
            cerr << "Error: fork() failed!" << endl;
            return 1;
        }
    }

    return 0; // End of the program
}
