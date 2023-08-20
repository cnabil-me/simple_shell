# How shell works

A shell is a command-line interface (CLI) program that provides a user-friendly way to interact with an operating system's kernel and execute various commands. It acts as an intermediary between the user and the operating system, allowing users to enter commands and receive output from the system. Here's an overview of how a shell works:

## Command Prompt and Input :

The user interacts with the shell by entering commands through a command prompt. The prompt typically indicates the current working directory, the user's name, the hostname of the machine, or other relevant information. When the user enters a command and presses Enter, the shell processes the input.

## Input Parsing :

The shell parses the input command to understand the command itself and any additional arguments or options. It separates the command and its parameters based on spaces or other defined delimiters.

## Command Execution:

After parsing the input, the shell identifies the command to be executed. There are a few possibilities for how the shell handles the execution :

- **Built-in Commands  : **
	Some commands are implemented as part of the shell itself. These are often basic operations like changing directories (`cd`), displaying information (`echo`), or setting environment variables. The shell recognizes these commands and executes them directly without creating new processes.

- **External Commands :**
	- Most commands are external programs or utilities installed on the system. The shell uses the `fork()` system call to create a child process and then uses the `exec()` family of functions to replace the child process's code with the code of the desired command. This new process executes the requested command and communicates the results back to the shell.

## Process Management :

When the shell forks a child process to execute an external command, it may need to manage the execution of multiple processes simultaneously. The shell can use system calls like `wait()` to wait for child processes to complete before continuing.

## I/O Redirection and Pipes :

Shells allow users to redirect input and output streams of commands. For example, you can redirect the output of a command to a file or use the output of one command as the input to another using pipes (`|`). The shell manages these operations by modifying the file descriptors of the processes it creates.

## Variable Substitution and Expansion :

Shells often provide features like variable substitution, where variables (e.g., `$HOME`) are replaced with their corresponding values, and command substitution, where the output of a command is used as part of another command.

## Control Structures:

Shells support control structures like loops and conditional statements. These enable users to create scripts or automate tasks by repeating commands or executing different commands based on conditions.

## Script Execution:

Shells allow users to write scripts, which are sequences of shell commands stored in files. The shell can read and execute these scripts, allowing for more complex and automated operations.

## User Interaction and Output :

The shell provides a way for the user to interact with the system and receive output from executed commands. Output from commands is displayed on the screen, and the shell may also provide error messages and other informative responses.

In summary, a shell provides an interface for users to interact with an operating system by interpreting and executing commands, managing processes, and handling input and output operations. Different shells (e.g., Bash, Zsh, PowerShell) offer various features and capabilities, but they all follow a similar general process flow.

# PID and PPID

PID and PPID are crucial concepts in process management within an operating system. PID uniquely identifies each process, while PPID indicates the process that created the current process. These identifiers play a significant role in various aspects of process scheduling, communication, and control.

## PID - Process ID :

A Process ID (PID) is a unique numerical identifier assigned to each running process in an operating system. The PID is used by the operating system to track and manage processes. It allows the system to distinguish one process from another and is crucial for process management, scheduling, and communication.

The PID is usually a non-negative integer. The first process (known as the "init" process or "systemd" on modern systems) is typically assigned PID 1, and subsequent processes are assigned higher PIDs in sequential order. When a process terminates, its PID becomes available for reuse by other processes.

in C and C++ on POSIX-compliant systems (like Linux and Unix), you can use the `getpid()` function from the `unistd.h` header to retrieve the PID.

```c
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = getpid();
    printf("PID: %d\n", pid);
    return 0;
}
```

## PPID - Parent Process ID :

The Parent Process ID (PPID) is the PID of the process that spawned or created the current process. In other words, the PPID is the PID of the parent process in relation to the current process. `Every process, except the initial process (often with PID 1), has a parent process from which it was created`

The PPID is used for process management and tracking the hierarchical relationship between processes. When a process is created using mechanisms like the `fork()` system call, the newly created process inherits its parent's PID and gets the PPID set to the parent's PID. This establishes a tree-like structure of processes, with parent-child relationships.

To obtain the Parent Process ID (PPID) of the currently running process in C on POSIX-compliant systems (such as Linux and Unix), you can use the `getppid()` function provided by the `unistd.h` header. Here's how you can use it :

```c
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t ppid = getppid();
    printf("PPID: %d\n", ppid);
    return 0;
}
```

## Zombie process

In the context of operating systems and programming, a "zombie process" refers to a state of a child process that has completed its execution but still has an entry in the process table. Zombie processes occur when a parent process doesn't explicitly wait for its child process to exit using the `wait` or `waitpid` system calls. Let's break down the concept:

1.  **Process Lifecycle:** When a child process is created using the `fork` system call, it becomes an independent process with its own process ID (PID). The child process executes its task and eventually exits. At this point, its exit status and other information are still stored in the process table.

2.  **Zombie Process:** A zombie process is a child process that has completed its execution but hasn't yet been completely removed from the process table. The process has exited, but its exit status and other information are still kept in memory. Zombie processes can linger in this state until the parent process calls a system call like `wait` or `waitpid` to collect the exit status of the child.

3.  **Cleaning Up Zombie Processes:** To remove a zombie process from the process table and release the resources associated with it, the parent process must explicitly call a waiting function like `wait` or `waitpid`. This allows the operating system to clean up the process entry and free the resources, thus preventing the accumulation of zombie processes.


Here's a simple example of how a zombie process might occur:

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid = fork();

    if (child_pid == 0) {
        // Child process
        printf("Child process executing\n");
        exit(0);
    } else if (child_pid > 0) {
        // Parent process
        printf("Parent process created child process (PID: %d)\n", child_pid);
        sleep(5); // Simulating parent delay
    } else {
        perror("Fork failed");
        return 1;
    }

    // Parent process doesn't explicitly wait for the child

    return 0;
}

```

In this example, the parent process doesn't call `wait` or `waitpid` to wait for the child to exit. As a result, the child process becomes a zombie process after it finishes its execution. After about 5 seconds, the zombie process will be reaped by the operating system.

In real-world applications, it's important for the parent process to properly handle the cleanup of its child processes to avoid the accumulation of zombie processes. This can be achieved by using the `wait` or `waitpid` system calls appropriately.



# Manipulate the environment

In C, you can manipulate the environment of the current process using the functions and variables provided by the standard library. The environment consists of a set of key-value pairs, where each pair represents an environment variable. Here's how you can manipulate the environment in C:

## Accessing Environment Variables :
Environment variables are stored as strings in the `environ` array, which is a global variable. You can access environment variables using this array.

```c
    #include <stdio.h>
    #include <stdlib.h>

    extern char **environ;

    int main() {
        char *value = getenv("PATH");

        // Get the value of the PATH variable
        if (value != NULL) {
            printf("PATH: %s\n", value);
        } else {
            printf("PATH variable not found\n");
        }

        return 0;
    }
```

## Setting Environment Variables :

You can set or modify environment variables using the `setenv()` function. If the variable doesn't exist, it will be created. If it already exists, its value will be updated.

```c
    #include <stdio.h>
    #include <stdlib.h>

    int main() {
        if (setenv("MY_VARIABLE", "my_value", 1) == 0) {
            printf("MY_VARIABLE set successfully.\n");
        } else {
            printf("Failed to set MY_VARIABLE.\n");
        }

        return 0;
    }
```

## Removing Environment Variables:

You can remove an environment variable using the `unsetenv()` function.

 ```c
	#include <stdio.h>
    #include <stdlib.h>

    int main() {
        if (unsetenv("MY_VARIABLE") == 0) {
            printf("MY_VARIABLE unset successfully.\n");
        } else {
            printf("Failed to unset MY_VARIABLE.\n");
        }
        return 0;
    }
```

> Remember that manipulating the environment `affects only the current process and its child processes`. Environment changes made by the current process do not affect the parent process or unrelated processes.

> Please note that while these examples demonstrate basic environment manipulation, you should handle errors and return values properly in actual applications for robustness.

# Function vs system call

Both functions and system calls are mechanisms used in programming to accomplish tasks or perform operations, but they have distinct differences in terms of their nature and functionality.

## Function :

-   A function is a self-contained block of code that performs a specific task or operation within a program.
-   Functions are used for modular programming, allowing code to be organized into reusable and manageable pieces.
-   Functions are typically called within the same process's memory space and execute as part of the program's execution flow.
-   Function calls involve pushing parameters onto the call stack and jumping to the function's code location. When the function returns, control is transferred back to the calling code.

## System Call :

-   A system call is an interface provided by the operating system to allow user-level processes to request services from the kernel.
-   System calls provide a way for user-level programs to interact with the lower-level resources of the operating system, such as file I/O, networking, memory allocation, etc.
-   System calls involve a transition from user mode to kernel mode, where the user-level code interacts with the kernel's services.
-   System calls are more involved than function calls, as they require a context switch between user mode and kernel mode, which can have performance implications.

## Key Differences:

**Location of Execution :**
    -   Functions execute within the same process's memory space, and control is transferred using the program's call stack.
    -   System calls involve a transition from user mode to kernel mode, where the operating system's code executes in a separate memory space.

**Scope and Purpose :**
    -   Functions are part of a program's codebase and serve specific tasks within the program's logic.
    -   System calls provide access to operating system services and resources that are outside the scope of the program.

**Privileges and Security : **
    -   Function calls are subject to the program's user-level privileges and security mechanisms.
    -   System calls often require proper permissions and authentication to access kernel-level resources, enhancing security.

**Performance and Overhead :**
    -   Function calls typically involve less overhead, as they don't require the same level of context switching and privilege elevation as system calls.
    -   System calls can be slower due to the context switch between user mode and kernel mode and the associated overhead.

## Summary

functions are integral parts of program logic that execute within the program's memory space, while system calls are interfaces provided by the operating system to access kernel-level services and resources. The distinction between the two is crucial for understanding how user-level code interacts with the operating system and how different layers of software interact with each other.

## Create processes `fork()`

In C, you can create processes using the `fork()` system call. The `fork()` function creates a new process by duplicating the existing process. The newly created process is known as the child process, and the original process is the parent process. Here's how you can use `fork()` to create processes:

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t child_pid;

    // Create a new process
    child_pid = fork();

    if (child_pid < 0) {
        // Forking failed
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (child_pid == 0) {
        // This code is executed by the child process
        printf("Child process (PID: %d)\n", getpid());
    } else {
        // This code is executed by the parent process
        printf("Parent process (PID: %d)\n", getpid());
        printf("Child process created (PID: %d)\n", child_pid);
    }

    return 0;
}

```

In this example:

1.  The `fork()` function is called, and its return value is stored in `child_pid`. If `fork()` returns a negative value, it means the creation of the child process failed.
2.  If `child_pid` is zero, it means the code is being executed by the child process. If `child_pid` is greater than zero, it means the code is being executed by the parent process, and `child_pid` contains the PID of the child process.
3.  The parent and child processes then print their respective PIDs using `getpid()`.

When you run this program, you will see output indicating both the parent and child processes. The child process inherits the code, data, and open file descriptors from the parent process, but they each have their own separate memory space.

Keep in mind that `fork()` creates a copy of the existing process, which can lead to complexities in managing resources like open file descriptors and memory. Modern programming practices often use higher-level constructs or libraries for process management and concurrency.

# The 3 prototypes of main function

## int main(void)

This prototype for `main` doesn't accept any parameters. The use of `void` in the parentheses indicates that the function doesn't expect any arguments. While some compilers might allow this syntax, it's not recommended and may not be portable. It's better to use the standard `int main(int argc, char *argv[])` prototype to access command-line arguments.

```c
#include <stdio.h>

int main(void) {
    printf("Hello from main(void)!\n");
    return 0;
}
```

## int main(int ac, char **av)

This prototype includes two parameters: `ac` and `av`. These names are arbitrary and can be anything, but the types should match. `ac` stands for "argument count," and `av` stands for "argument vector." This prototype is similar to the standard one, with different parameter names.

```c
#include <stdio.h>

int main(int ac, char **av) {
    printf("Hello from main(int ac, char **av)!\n");
    printf("Number of arguments: %d\n", ac);
    for (int i = 0; i < ac; i++) {
        printf("Argument %d: %s\n", i, av[i]);
    }
    return 0;
}

```

## int main(int ac, char **av, char **env)

This prototype includes three parameters : `ac`, `av`, and `env`. `env` stands for "environment," and it's meant to represent the environment variables passed to the program. Environment variables are not typically passed directly to the `main` function in this way. Instead, they are often accessed using the `extern char **environ` global variable. This prototype is not standard and might not work as expected on all systems.

In summary, while you might come across variations of the `main` function prototype, it's crucial to stick to the standard `int main(int argc, char *argv[])` prototype when writing portable and maintainable C code that deals with command-line arguments.

# How shell find a program?

The shell uses the `PATH` environment variable to locate executable programs when you enter a command without specifying its full path. The `PATH` variable is a colon-separated list of directories that the shell searches through when looking for the executable corresponding to a command. When you enter a command in the shell, the shell follows these steps to find the program using the `PATH`:

1.  **Command Input:** When you type a command in the shell, the shell first interprets the command.

2.  **Path Resolution:** If the command does not include an absolute or relative path (e.g., `/usr/bin/ls` or `./myprogram`), the shell uses the `PATH` variable to search for the executable.

3.  **Searching the Directories:** The shell splits the `PATH` variable into individual directories using the colon (`:`) as a delimiter. It then sequentially searches each of these directories in the order they appear in the `PATH`.

4.  **Executable Check:** In each directory, the shell checks if the desired command (program) exists as an executable file. It looks for files with the same name as the command.

5.  **Command Execution:** If the shell finds an executable file with the same name as the command in one of the `PATH` directories, it executes that program using the provided arguments.

For example, consider a `PATH` variable like this:

```bash
code/usr/local/bin:/usr/bin:/bin
```

If you enter the command `ls`, the shell would search for the `ls` executable in each of the specified directories (`/usr/local/bin`, `/usr/bin`, and `/bin`) in that order. If it finds the `ls` executable in `/usr/bin`, it will execute that program.

Keep in mind the following points:

-   The shell stops searching as soon as it finds the first matching executable in one of the `PATH` directories.
-   If the executable you want to run is not in any of the `PATH` directories, you need to provide the full or relative path to the executable file.
-   Changing the order of directories in the `PATH` variable can affect which executable is found first.
-   Security implications: Having `.` (the current directory) in your `PATH` is considered a security risk, as it can potentially allow execution of malicious scripts or binaries with the same name as common commands.

# Execute a program`execve`

The `execve()` system call is used to replace the current process's memory space with a new program. It's commonly used to execute another program from within a C program. The `execve()` function is powerful because it allows you to specify the exact program to execute along with its command-line arguments and environment variables.

Here's the basic syntax of the `execve()` function:

```c
#include <unistd.h>

int execve(const char *pathname, char *const argv[], char *const envp[]);

```

-   `pathname`: The path to the executable program you want to run.
-   `argv`: An array of strings containing the command-line arguments for the new program.
-   `envp`: An array of strings containing the environment variables for the new program.

Here's an example demonstrating how to use `execve()` to execute another program:

```c
#include <stdio.h>
#include <unistd.h>

int main() {
    char *const arguments[] = {"ls", "-l", NULL};
    char *const environment[] = {"PATH=/usr/bin", NULL};

    // Replace the current process with "ls -l"
    execve("/usr/bin/ls", arguments, environment);

    // The following lines will only execute if execve fails
    perror("execve"); // Print an error message
    return 1;         // Return an error code
}
```

In this example:

-   We specify the program we want to execute as "/usr/bin/ls".
-   We provide the command-line arguments in the `arguments` array, which is `{"ls", "-l", NULL}`.
-   We set the environment variable in the `environment` array, which is `{"PATH=/usr/bin", NULL}`.

> Keep in mind these important points when using `execve()`:
> -   The code after `execve()` will only execute if `execve()` fails. If `execve()` succeeds, the current process is replaced by the new program, and the code is never reached.
> -   If `execve()` fails, you can use `perror()` to print an error message indicating the reason for the failure.
> -   The program specified in `pathname` must be an executable binary, and its path should be an absolute path or a path relative to the current directory.
> -   When using `execve()`, you're responsible for handling memory allocation and management for the `argv` and `envp` arrays.

# Suspend  a process

In Unix-like operating systems, you can use the `wait()` system call to suspend the execution of a parent process until one of its child processes terminates.

## wait()

The `wait()` function allows the parent process to wait for the completion of a specific child or any child process. Here's how you can use the `wait()` system call :

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t child_pid;

    // Create a child process
    child_pid = fork();

    if (child_pid < 0) {
        // Forking failed
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (child_pid == 0) {
        // This code is executed by the child process
        printf("Child process (PID: %d) executing\n", getpid());
        sleep(3); // Simulating some work in the child
        printf("Child process (PID: %d) exiting\n", getpid());
        exit(0);
    } else {
        // This code is executed by the parent process
        printf("Parent process (PID: %d) waiting for child\n", getpid());
        int status;
        pid_t terminated_child_pid = wait(&status);

        if (WIFEXITED(status)) {
            printf("Child process (PID: %d) terminated with exit status: %d\n", terminated_child_pid, WEXITSTATUS(status));
        } else {
            printf("Child process (PID: %d) terminated abnormally\n", terminated_child_pid);
        }
    }

    return 0;
}

```

In this example:

-   The parent process creates a child process using `fork()`.
-   The parent process waits for the child to terminate using the `wait()` function.
-   The `wait()` function suspends the execution of the parent until the child terminates.
-   The parent can also retrieve information about the child's termination status using the `status` parameter.

> Please note that `wait()` only waits for a single child process. If you have multiple child processes and want to wait for any of them to terminate, you might need to use more advanced mechanisms like `waitpid()` with options or signals.

## waitpid()

The `waitpid()` function is similar to `wait()`, but it provides more flexibility by allowing you to specify which child process you want to wait for and additional options. Here's an example of how to use `waitpid()`:

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t child_pid1, child_pid2;
    int status;

    // Create two child processes
    child_pid1 = fork();

    if (child_pid1 < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (child_pid1 == 0) {
        // Child process 1
        printf("Child process 1 (PID: %d) executing\n", getpid());
        sleep(3);
        printf("Child process 1 (PID: %d) exiting\n", getpid());
        exit(0);
    }

    child_pid2 = fork();

    if (child_pid2 < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (child_pid2 == 0) {
        // Child process 2
        printf("Child process 2 (PID: %d) executing\n", getpid());
        sleep(5);
        printf("Child process 2 (PID: %d) exiting\n", getpid());
        exit(0);
    }

    // Parent process
    printf("Parent process (PID: %d) waiting for children\n", getpid());

    // Wait for child_pid1 to terminate and retrieve its exit status
    waitpid(child_pid1, &status, 0);
    if (WIFEXITED(status)) {
        printf("Child process 1 (PID: %d) terminated with exit status: %d\n", child_pid1, WEXITSTATUS(status));
    }

    // Wait for any child process to terminate and retrieve its exit status
    waitpid(-1, &status, 0);
    if (WIFEXITED(status)) {
        printf("A child process terminated with exit status: %d\n", WEXITSTATUS(status));
    }

    return 0;
}

```

In this example:

-   Two child processes are created using `fork()`.
-   The parent process waits for each child process to terminate using `waitpid()` with different arguments and options.
-   The first `waitpid()` waits specifically for `child_pid1` to terminate and retrieves its exit status.
-   The second `waitpid()` with `-1` as the first argument waits for any child process to terminate and retrieves its exit status.

`waitpid()` is useful when you need to wait for specific child processes or when you want to handle child processes in a particular order. The `-1` argument allows you to wait for any child process. Be sure to handle the exit status and error conditions appropriately in your actual programs.

# EOF “end-of-file”

`EOF` stands for "end-of-file." In C and many other programming languages, EOF is a special value that indicates the end of a file or input stream. It's used to signal that there is no more data to be read from a file or input source. When reading from a file or input stream, encountering EOF indicates that you have reached the end of the data.

In C, EOF is represented by the macro `EOF`, which is a negative integer value. It's usually defined as `-1`. When you perform input operations, such as reading characters from a file using functions like `getc()` or `fgetc()`, you'll often check for EOF to determine if you've reached the end of the file.

Here's a common way to use EOF when reading characters from a file:

```c
#include <stdio.h>

int main() {
    FILE *file = fopen("myfile.txt", "r");
    int character;

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    while ((character = fgetc(file)) != EOF) {
        putchar(character);
    }

    fclose(file);
    return 0;
}
```

In this example, the program opens a file named "myfile.txt" for reading. It reads characters from the file using `fgetc()` in a loop until EOF is encountered. Once EOF is reached, the loop stops, indicating that the end of the file has been reached.

It's important to handle EOF properly when reading from files to avoid processing data after the end of the file or encountering errors due to unexpected behavior.

# The `stat` function

The `stat` function in C is used to retrieve information about a file or file system object, such as a regular file, directory, symbolic link, etc. It fills a `struct stat` with various pieces of information about the file. This information includes details like file size, permissions, timestamps, owner, and more.

Here's a breakdown of how the `stat` function works and its important components:

##  Function Signature:

```c
int stat(const char *path, struct stat *buf);
```
-The `stat` function takes two parameters:
-`path`: A pointer to the path of the file or object you want to retrieve information about.
-`buf`: A pointer to a `struct stat` that will hold the information retrieved by the function.

## Struct stat :

The `struct stat` is a structure defined in the `<sys/stat.h>` header that holds various attributes of a file or object. It typically includes members like:
    -`st_mode`: File mode (permissions and file type).
    -`st_size`: Size of the file in bytes.
    -`st_mtime`: Last modification timestamp.
    -`st_uid` and `st_gid`: User and group IDs of the owner.
    -   ...and more.

## Return Value :

The `stat` function returns an integer value. If the function call is successful, it returns `0`. If an error occurs, it returns `-1`, and you can use the global variable `errno` to identify the specific error that occurred.

## Example Usage :

Here's a simple example of using the `stat` function to retrieve information about a file:
```c
    #include <stdio.h>
    #include <sys/stat.h>

    int main() {
        const char *filename = "example.txt";
        struct stat file_info;

        if (stat(filename, &file_info) == 0) {
            printf("File size: %ld bytes\n", file_info.st_size);
            printf("File mode: %o\n", file_info.st_mode);
            // More information can be extracted from 'file_info'
        } else {
            perror("stat");
        }

        return 0;
    }
```

In this example, the program retrieves the size and mode of the file named "example.txt" using the `stat` fu

Remember that the `stat` function operates on the file path, not a file descriptor, so it's suitable for getting information about files that you might not currently have open. If you need information about an open file descriptor, you would typically use the `fstat` function.

# Credit :

- CHERRADI NABIL Mouhssine <Hi@cnabil.me>
- Chidubem Uchendu <dubemxe@gmail.com>
