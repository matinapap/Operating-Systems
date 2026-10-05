#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void print_process_info(const char* name) {
    printf("%s: PID=%d, PPID=%d\n", name, getpid(), getppid());
}

int main() {
    pid_t pid1, pid2, pid3, pid4, pid5, pid6, pid7, pid8, pid9;

    // Create P1
    pid1 = fork();
    if (pid1 == 0) {
        // This is P1
        print_process_info("P1");

        // Create P4
        pid4 = fork();
        if (pid4 == 0) {
            // This is P4
            print_process_info("P4");
            exit(0);
        }
        wait(NULL); // P1 waits for P4
        exit(0);
    }

    // Create P2
    pid2 = fork();
    if (pid2 == 0) {
        // This is P2

        // Create P5
        pid5 = fork();
        if (pid5 == 0) {
            // This is P5
            print_process_info("P5");
            exit(0);
        }

        // Create P6
        pid6 = fork();
        if (pid6 == 0) {
            // This is P6
            print_process_info("P6");
            exit(0);
        }

        waitpid(pid6, NULL, 0); // P2 waits for P6
        print_process_info("P2");
        wait(NULL); // P2 waits for P5
        exit(0);
    }

    // Create P3
    pid3 = fork();
    if (pid3 == 0) {
        // This is P3

        // Create P7
        pid7 = fork();
        if (pid7 == 0) {
            // This is P7
            print_process_info("P7");
            exit(0);
        }

        // Create P8
        pid8 = fork();
        if (pid8 == 0) {
            // This is P8
            print_process_info("P8");
            exit(0);
        }

        // Create P9
        pid9 = fork();
        if (pid9 == 0) {
            // This is P9
            print_process_info("P9");
            exit(0);
        }

        waitpid(pid9, NULL, 0); // P3 waits for P9
        waitpid(pid7, NULL, 0); // P3 waits for P7 or P8
        print_process_info("P3");
        wait(NULL); // Wait for the remaining child
        exit(0);
    }

    waitpid(pid1, NULL, 0); // P0 waits for P1
    print_process_info("P0");

    // Replace P0 with the `cat` command to print the source code
    execlp("cat", "cat", __FILE__, NULL);

    return 0;
}