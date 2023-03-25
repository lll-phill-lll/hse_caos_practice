#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int main() {
    int fds[2];         // массив из файловых дискрипторов
                        // fds[0] - отвечает за чтение, fds[1] - отвечает за запись
    if (pipe(fds)) {    // превращаем файловые дискрипторы в канал и ловим ошибку
        perror("pipe");
        exit(1);
    }
/*-------------------------п-р-и-м-е-р--1-----------------------------------------------------------------------------*/
    // write/read
    //  {
    //      char wbuf[] = "hello";
    //      char rbuf[6];

    //      write(fds[1], wbuf, sizeof(wbuf));        // запись, поэтому fds[1]

    //      ssize_t read_size = read(fds[0], rbuf, sizeof(rbuf));   // чтение, поэтому fds[0]
    //      printf("read bytes: %lu\n", read_size);                 // смотрим сколько прочитали
    //      int string_len = read_size;
    //      printf("read from pipe: %.*s\n", string_len, rbuf);     // смотрим что прочитали
    //  }

///*-------------------------п-р-и-м-е-р--2---------------------------------------------------------------------------*/
//    // зависнет
//     {
//         char wbuf[] = "hello";
//         char rbuf[6];
//
//         ssize_t read_size = read(fds[0], rbuf, sizeof(rbuf));    // вот тут он ждет пока кто-то что-то не напишет
//         write(fds[1], wbuf, sizeof(wbuf));
//         printf("read bytes: %lu\n", read_size);
//         printf("read from pipe: %s\n", rbuf);
//     }

///*-------------------------п-р-и-м-е-р--3---------------------------------------------------------------------------*/
//
//      {
//          char wbuf[] = "hello";
//          char rbuf[6];
//
//          close(fds[1]);
//          ssize_t read_size = read(fds[0], rbuf, sizeof(rbuf));
//          if (read_size < 0) {
//              perror("read");
//          }
//          ssize_t write_size = write(fds[1], wbuf, sizeof(wbuf));
//          if (write_size < 0) {
//              perror("write");
//          }
//      }

///*-------------------------п-р-и-м-е-р--4---------------------------------------------------------------------------*/
//     {
//          // signal(SIGPIPE, SIG_IGN);
//          char wbuf[] = "hello";
//          close(fds[0]);
//          int res = write(fds[1], wbuf, sizeof(wbuf));
//          if (res < 0) {
//              perror("write");
//          } else {
//              printf("success\n");
//          }
//     }

///*-------------------------п-р-и-м-е-р--5---------------------------------------------------------------------------*/
//
//    // если считанные данные больше, чем буфер, куда мы записываем,
//    // то выведется кол-во элементов, равное размеру буфера выода
//
//    {
//        char wbuf[] = "hello";
//        write(fds[1], wbuf, sizeof(wbuf));
//        char rbuf[2];
//        ssize_t read_size = read(fds[0], rbuf, sizeof(rbuf));
//        printf("read bytes: %lu\n", read_size);
//        int string_len = read_size;
//        printf("read from pipe: %.*s\n", string_len, rbuf);       //%.* - ограничивает размер вывода
//    }
}
