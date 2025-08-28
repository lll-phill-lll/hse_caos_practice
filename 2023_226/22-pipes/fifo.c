
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

#define FIFO_PATH "myfifo"

void writer_process() {
   int fd;
   char message[] = "Hello, named pipe!";

   // Open the named pipe for writing
   fd = open(FIFO_PATH, O_WRONLY);
   if (fd == -1) {
      perror("open");
      exit(EXIT_FAILURE);
   }

   // Write the message to the named pipe
   write(fd, message, strlen(message) + 1);
   printf("Message sent: %s", message);

   // Close the named pipe
   close(fd);
}

void reader_process() {
   int fd;
   char buffer[100];

   // Open the named pipe for reading
   fd = open(FIFO_PATH, O_RDONLY);
   if (fd == -1) {
      perror("open");
      exit(EXIT_FAILURE);
   }

   // Read the message from the named pipe
   read(fd, buffer, sizeof(buffer));
   printf("Message received: %s", buffer);

   // Close the named pipe
   close(fd);
}

int main() {
   pid_t pid;

   // Fork a child process
   pid = fork();

   if (pid == -1) {
      perror("fork");
      exit(EXIT_FAILURE);
   } else if (pid == 0) {
      // Child process (writer)
      writer_process();
   } else {
      // Parent process (reader)
      reader_process();

      // Wait for the child process to finish
      wait(NULL);

   }
   return 0;
}
