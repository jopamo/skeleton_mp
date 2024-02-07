#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  // Validate the correct number of command-line arguments
  if(argc != 2) {
    fprintf(stderr, "Usage: %s <iterations>\n", argv[0]);
    return 1; // Exit with error if the argument count is incorrect
  }

  // Convert the command-line argument to an integer for the iteration count
  char *endptr;
  long iterations = strtol(argv[1], &endptr, 10); // Convert string to long with error checking

  // Check for conversion errors or non-positive numbers
  if (*endptr != '\0' || iterations <= 0) {
    fprintf(stderr, "Error: '%s' is not a valid positive integer.\n", argv[1]);
    return 1;
  }

  // Loop for the specified number of iterations
  for(int i = 1; i <= iterations; i++) {
    // Print the process and parent process IDs before sleeping
    printf("USER PID:%d PPID:%d Iteration:%d before sleeping\n", getpid(), getppid(), i);
    sleep(1); // Sleep for 1 second
    // Print the process and parent process IDs after sleeping
    printf("USER PID:%d PPID:%d Iteration:%d after sleeping\n", getpid(), getppid(), i);
  }

  return 0; // Successful execution
}
