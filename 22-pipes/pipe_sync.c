#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>




int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "not enough args\n");
        exit(1);
    }
    int child_num = strtol(argv[1], NULL, 10);
    int pfd[2];

    printf("Parent started\n");

    pipe(pfd);

    for (int j = 0; j < child_num; j++) {
        switch (fork()) {
        case -1:
            perror("fork");
            exit(1);

        case 0: /* Child */
            close(pfd[0]);

            sleep(2);
            /// important
            printf("Child [PID=%d] closing pipe\n", getpid());
            close(pfd[1]);


            _exit(0);

        default:
            break;
        }
    }

    close(pfd[1]);


    printf("Parent wait\n");

    int j, dummy;
    if (read(pfd[0], &dummy, 1) != 0) {
        printf("parent didn't get EOF");

    }
    printf("Parent ready to go\n");
}
