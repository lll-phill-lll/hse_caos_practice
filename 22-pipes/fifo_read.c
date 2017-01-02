#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
   char buffer[1024];

   int fd = open("myfifo", O_RDONLY);

   printf("Opened fifo for read\n");

   ssize_t read_size;
   while ((read_size = read(fd, buffer, sizeof(buffer)))) {
       printf("Message received: %.*s\n", (int)read_size, buffer);
   }

   close(fd);
   printf("Closed fifo for read\n");
}
