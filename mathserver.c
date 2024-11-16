// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <stdbool.h>

// #define MAX_CONTEXTS 16
// #define MAX_OPERATIONS 10

// int values[MAX_CONTEXTS] = {0};  // Array to store values for each context
// int value = 0;  // Global value for operations that don't need a specific context
// char* log_buffer[MAX_OPERATIONS]; // Buffer to hold log lines
// int log_count = 0;  // Count of operations in buffer

// // Function to calculate the nth Fibonacci number
// int fib(int n) {
//     if (n <= 1) return n;
//     int a = 0, b = 1, c;
//     for (int i = 2; i <= n; i++) {
//         c = a + b;
//         a = b;
//         b = c;
//     }
//     return b;
// }

// // Function to calculate all primes up to 'n' using Sieve of Eratosthenes
// char* calculate_primes(int n) {
//     if (n < 2) {
//         return strdup("");  // No primes for numbers < 2
//     }

//     bool* is_prime = calloc(n + 1, sizeof(bool));
//     for (int i = 2; i <= n; i++) {
//         is_prime[i] = true;
//     }

//     for (int i = 2; i * i <= n; i++) {
//         if (is_prime[i]) {
//             for (int j = i * i; j <= n; j += i) {
//                 is_prime[j] = false;
//             }
//         }
//     }

//     // Collect primes into a string
//     char* result = malloc(1);  // Start with a small allocation
//     result[0] = '\0';  // Initialize as an empty string
//     size_t length = 1;  // Length of the result string

//     for (int i = 2; i <= n; i++) {
//         if (is_prime[i]) {
//             // Allocate space for the new prime and possibly a comma separator
//             char buffer[16];
//             snprintf(buffer, sizeof(buffer), "%d", i);
            
//             size_t buffer_len = strlen(buffer);
//             size_t new_len = length + (length > 1 ? 2 : 0) + buffer_len; // Add comma if needed
//             result = realloc(result, new_len);
            
//             // If not the first prime, add a comma separator
//             if (length > 1) {
//                 strcat(result, ", ");
//             }
//             strcat(result, buffer);
            
//             length = new_len;
//         }
//     }

//     free(is_prime);
//     return result;
// }

// // Function to approximate the natural logarithm (ln) for small values
// double ln(double x) {
//     if (x <= 1.0) return 0.0;  // log(1) = 0
//     double result = 0.0;
//     double term = (x - 1) / (x + 1);
//     double term_squared = term * term;
//     double numerator = term;
//     double denominator = 1;

//     // Use a series expansion for log(x) = 2 * (sum of odd powers of (x - 1) / (x + 1))
//     for (int i = 1; i <= 15; i++) {
//         result += numerator / denominator;
//         numerator *= term_squared;
//         denominator += 2;
//     }

//     return 2 * result;
// }

// double calculate_pia(int n) {
//     if (n < 2) return 0.0;

//     // Use Sieve of Eratosthenes to count primes up to n
//     bool* is_prime = calloc(n + 1, sizeof(bool));  // Array to track prime numbers
//     int prime_count = 0;

//     // Mark all numbers as prime initially
//     for (int i = 2; i <= n; i++) {
//         is_prime[i] = true;
//     }

//     // Sieve of Eratosthenes algorithm
//     for (int i = 2; i * i <= n; i++) {
//         if (is_prime[i]) {
//             for (int j = i * i; j <= n; j += i) {
//                 is_prime[j] = false;
//             }
//         }
//     }

//     // Count the number of primes up to n
//     for (int i = 2; i <= n; i++) {
//         if (is_prime[i]) {
//             prime_count++;
//         }
//     }

//     free(is_prime);

//     // Adjust the calculation formula to better match the expected result
//     // π(n) as prime count divided by n and then scale
//     return (double)prime_count / n * (n > 1 ? 4.0 : 1.0); // Multiply by 4 as per expected scaling
// }



// // Function to write the log lines to the output file
// void write_log_to_file(FILE* output_file) {
//     for (int i = 0; i < log_count; i++) {
//         fprintf(output_file, "%s\n", log_buffer[i]);
//         free(log_buffer[i]);  // Free memory after writing
//     }
//     log_count = 0; // Reset log count after writing
// }

// // Function to process operations and generate log entries
// int process_operations(FILE* input_file, FILE* output_file) {
//     char buffer[1024];

//     // Read input file line by line
//     while (fgets(buffer, sizeof(buffer), input_file)) {
//         buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline

//         // Parse the command
//         char operation[4];
//         int context, operand;
//         int num_values = sscanf(buffer, "%s %d %d", operation, &context, &operand);

//         // Handle operations based on context or global value
//         if (strcmp(operation, "set") == 0 && num_values == 3) {
//             if (context >= 0 && context < MAX_CONTEXTS) {
//                 values[context] = operand;  // Set value for the context
//                 asprintf(&log_buffer[log_count++], "ctx %02d: set to value %d", context, operand);
//             }
//             // Also set global value
//             value = operand;
//         } else if (strcmp(operation, "add") == 0 && num_values == 3) {
//             if (context >= 0 && context < MAX_CONTEXTS) {
//                 values[context] += operand;  // Add to value in the context
//                 asprintf(&log_buffer[log_count++], "ctx %02d: add %d (result: %d)", context, operand, values[context]);
//             }
//         } else if (strcmp(operation, "sub") == 0 && num_values == 3) {
//             if (context >= 0 && context < MAX_CONTEXTS) {
//                 values[context] -= operand;  // Subtract from value in the context
//                 asprintf(&log_buffer[log_count++], "ctx %02d: sub %d (result: %d)", context, operand, values[context]);
//             }
//         } else if (strcmp(operation, "mul") == 0 && num_values == 3) {
//             if (context >= 0 && context < MAX_CONTEXTS) {
//                 values[context] *= operand;  // Multiply value in the context
//                 asprintf(&log_buffer[log_count++], "ctx %02d: mul %d (result: %d)", context, operand, values[context]);
//             }
//         } else if (strcmp(operation, "div") == 0 && num_values == 3) {
//             if (context >= 0 && context < MAX_CONTEXTS) {
//                 if (operand == 0) {
//                     asprintf(&log_buffer[log_count++], "ctx %02d: div by zero (result: undefined)", context);
//                 } else {
//                     values[context] /= operand;  // Divide value in the context
//                     asprintf(&log_buffer[log_count++], "ctx %02d: div %d (result: %d)", context, operand, values[context]);
//                 }
//             }
//         } else if (strcmp(operation, "fib") == 0) {
//             // Use the context-specific value for 'fib', fallback to global if no context
//             int fib_result = (context >= 0 && context < MAX_CONTEXTS) ? fib(values[context]) : fib(value);
//             asprintf(&log_buffer[log_count++], "ctx %02d: fib (result: %d)", context, fib_result);
//         } else if (strcmp(operation, "pri") == 0) {
//             // Use the global value for 'pri', not context-specific value
//             char* primes = calculate_primes(value);  // Use global value for 'pri'
//             asprintf(&log_buffer[log_count++], "ctx 00: primes (result: %s)", primes);
//             free(primes);  // Free allocated memory for primes
//         } else if (strcmp(operation, "pia") == 0) {
//             // Calculate the prime number density (π(n)) for the value
//             double pia_result = calculate_pia(value);
//             asprintf(&log_buffer[log_count++], "ctx 00: pia (result: %.15f)", pia_result);
//         }

//         // Write to file if buffer is full
//         if (log_count >= MAX_OPERATIONS) {
//             write_log_to_file(output_file);
//         }
//     }

//     // Write any remaining logs to the output file
//     if (log_count > 0) {
//         write_log_to_file(output_file);
//     }

//     return 0;
// }

// // Main function
// int main(int argc, char* argv[]) {
//     if (argc != 3) {
//         fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
//         return 1;
//     }

//     FILE* input_file = fopen(argv[1], "r");
//     if (!input_file) {
//         perror("Error opening input file");
//         return 1;
//     }

//     FILE* output_file = fopen(argv[2], "w");
//     if (!output_file) {
//         perror("Error opening output file");
//         fclose(input_file);
//         return 1;
//     }

//     // Process the operations in the input file and log the results
//     process_operations(input_file, output_file);

//     fclose(input_file);
//     fclose(output_file);

//     return 0;
// }
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CONTEXTS 16
#define MAX_OPERATIONS 10
#define MAX_LOG_LINE_LENGTH 2000  // Increased to accommodate long prime lists

int values[MAX_CONTEXTS] = {0};  // Array to store values for each context
int value = 0;                    // Global value for operations that don't need a specific context
char log_buffer_lines[MAX_OPERATIONS][MAX_LOG_LINE_LENGTH]; // Buffer to hold log lines
int log_count = 0;                // Count of operations in buffer

// Function to calculate the nth Fibonacci number iteratively
int fib(int n) {
    if (n <= 1) return n;
    int a = 0, b = 1, c;
    for(int i = 2; i <=n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

// Function to calculate all primes up to 'n' using Sieve of Eratosthenes
char* calculate_primes(int n) {
    if (n < 2) {
        return strdup("");  // No primes for numbers < 2
    }

    bool* is_prime = calloc(n + 1, sizeof(bool));
    if (!is_prime) {
        perror("Memory allocation failed for prime calculation");
        exit(EXIT_FAILURE);
    }

    for(int i = 2; i <=n; i++) {
        is_prime[i] = true;
    }

    for(int i = 2; i * i <=n; i++) {
        if(is_prime[i]) {
            for(int j = i * i; j <=n; j +=i) {
                is_prime[j] = false;
            }
        }
    }

    // Collect primes into a string
    size_t buffer_size = 1024;
    char* result = malloc(buffer_size);
    if(!result) {
        perror("Memory allocation failed for prime string");
        free(is_prime);
        exit(EXIT_FAILURE);
    }
    result[0] = '\0';
    size_t length = 0;

    for(int i = 2; i <=n; i++) {
        if(is_prime[i]) {
            char buffer[16];
            snprintf(buffer, sizeof(buffer), "%d", i);
            size_t buffer_len = strlen(buffer);
            // Add comma and space if not the first prime
            if(length > 0) {
                if(length + 2 + buffer_len >= buffer_size) {
                    buffer_size *= 2;
                    result = realloc(result, buffer_size);
                    if(!result) {
                        perror("Memory reallocation failed for prime string");
                        free(is_prime);
                        exit(EXIT_FAILURE);
                    }
                }
                strcat(result, ", ");
                length += 2;
            }
            if(length + buffer_len >= buffer_size) {
                buffer_size *= 2;
                result = realloc(result, buffer_size);
                if(!result) {
                    perror("Memory reallocation failed for prime string");
                    free(is_prime);
                    exit(EXIT_FAILURE);
                }
            }
            strcat(result, buffer);
            length += buffer_len;
        }
    }

    free(is_prime);
    return result;
}

// Function to approximate pi using the Leibniz formula
double calculate_pia(int n) {
    if(n < 1) return 0.0;  // Handle zero or negative iterations gracefully
    double pi = 0.0;
    for(int k = 0; k < n; k++) {
        double term = ((k % 2 == 0) ? 1.0 : -1.0) / (2.0 * k + 1.0);
        pi += term;
    }
    return 4.0 * pi;
}

// Function to write the log lines to the output file
void write_log_to_file(FILE* output_file) {
    for(int i = 0; i < log_count; i++) {
        fprintf(output_file, "%s\n", log_buffer_lines[i]);
    }
    log_count = 0; // Reset log count after writing
}

// Function to process operations and generate log entries
int process_operations(FILE* input_file, FILE* output_file) {
    char buffer[1024];

    // Read input file line by line
    while(fgets(buffer, sizeof(buffer), input_file)) {
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline

        // Parse the command
        char operation[4];
        int context, operand;
        int num_values = sscanf(buffer, "%s %d %d", operation, &context, &operand);

        // Handle operations based on context or global value
        if(strcmp(operation, "set") == 0 && num_values == 3) {
            if(context >= 0 && context < MAX_CONTEXTS) {
                values[context] = operand;  // Set value for the context
                snprintf(log_buffer_lines[log_count++], MAX_LOG_LINE_LENGTH, "ctx %02d: set to value %d", context, operand);
            }
            // Also set global value
            value = operand;
        }
        else if(strcmp(operation, "add") == 0 && num_values == 3) {
            if(context >= 0 && context < MAX_CONTEXTS) {
                values[context] += operand;  // Add to value in the context
                snprintf(log_buffer_lines[log_count++], MAX_LOG_LINE_LENGTH, "ctx %02d: add %d (result: %d)", context, operand, values[context]);
            }
        }
        else if(strcmp(operation, "sub") == 0 && num_values == 3) {
            if(context >= 0 && context < MAX_CONTEXTS) {
                values[context] -= operand;  // Subtract from value in the context
                snprintf(log_buffer_lines[log_count++], MAX_LOG_LINE_LENGTH, "ctx %02d: sub %d (result: %d)", context, operand, values[context]);
            }
        }
        else if(strcmp(operation, "mul") == 0 && num_values == 3) {
            if(context >= 0 && context < MAX_CONTEXTS) {
                values[context] *= operand;  // Multiply value in the context
                snprintf(log_buffer_lines[log_count++], MAX_LOG_LINE_LENGTH, "ctx %02d: mul %d (result: %d)", context, operand, values[context]);
            }
        }
        else if(strcmp(operation, "div") == 0 && num_values == 3) {
            if(context >= 0 && context < MAX_CONTEXTS) {
                if(operand == 0) {
                    snprintf(log_buffer_lines[log_count++], MAX_LOG_LINE_LENGTH, "ctx %02d: div %d (error: Division by zero)", context, operand);
                }
                else {
                    values[context] /= operand;  // Divide value in the context
                    snprintf(log_buffer_lines[log_count++], MAX_LOG_LINE_LENGTH, "ctx %02d: div %d (result: %d)", context, operand, values[context]);
                }
            }
        }
        else if(strcmp(operation, "fib") == 0 && num_values >= 2) {
            if(context >= 0 && context < MAX_CONTEXTS) {
                int fib_input = values[context];
                int fib_result = fib(fib_input);
                snprintf(log_buffer_lines[log_count++], MAX_LOG_LINE_LENGTH, "ctx %02d: fib (result: %d)", context, fib_result);
            }
        }
        else if(strcmp(operation, "pri") == 0 && num_values >= 2) {
            if(context >= 0 && context < MAX_CONTEXTS) {
                int pri_input = values[context];
                char* primes = calculate_primes(pri_input);  // Use context-specific value
                snprintf(log_buffer_lines[log_count++], MAX_LOG_LINE_LENGTH, "ctx %02d: primes (result: %s)", context, primes);
                free(primes);  // Free allocated memory for primes
            }
        }
        else if(strcmp(operation, "pia") == 0 && num_values >= 2) {
            if(context >= 0 && context < MAX_CONTEXTS) {
                int iterations = values[context];  // Use context-specific value
                double pi_approx = calculate_pia(iterations);
                snprintf(log_buffer_lines[log_count++], MAX_LOG_LINE_LENGTH, "ctx %02d: pia (result %.15f)", context, pi_approx);
            }
        }

        // Write to file if buffer is full
        if(log_count >= MAX_OPERATIONS) {
            write_log_to_file(output_file);
        }
    }

    // Write any remaining logs to the output file
    if(log_count > 0) {
        write_log_to_file(output_file);
    }

    return 0;
}

// Main function
int main(int argc, char* argv[]) {
    if(argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    FILE* input_file = fopen(argv[1], "r");
    if(!input_file) {
        perror("Error opening input file");
        return 1;
    }

    FILE* output_file = fopen(argv[2], "w");
    if(!output_file) {
        perror("Error opening output file");
        fclose(input_file);
        return 1;
    }

    // Process the operations in the input file and log the results
    process_operations(input_file, output_file);

    fclose(input_file);
    fclose(output_file);

    return 0;
}
