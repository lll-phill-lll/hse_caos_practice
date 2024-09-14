2023-2024 год

1. [[к](01-intro)][[yt](https://youtu.be/WGxA9WTWyNQ?si=19kf_FQjDpgLqb_1)][[vk](https://vk.com/video-221776054_456239019)] - Терминал. vim. tmux. 
2. [[к](02-asm)][[yt](https://youtu.be/U6r8ubs-SAw)][[vk](https://vk.com/video-221776054_456239020)] - Язык ассемблера. Представление целых чисел. Сдвиги. GDB.
3. [[к](03-stack)][[yt](https://www.youtube.com/watch?v=TwgwQ6H4wz0)][[vk](https://vk.com/video-221776054_456239021)] - Переменные и массивы. Стек. Cdecl. Запуск asm+c и asm+c++ кода.
4. [[к](04-more-asm)][[yt](https://www.youtube.com/watch?v=vtA6kedKMD8)][[vk](https://vk.com/video-221776054_456239022)] - Lea, строки, части регистров, switch.
5. [[к](05-asm-func)][[yt](https://youtu.be/N-jkF3YofR8?si=E1ev_esI6ntMv8eA)][[vk](https://vk.com/video-221776054_456239023)] - Указатели на функции. Variadic functions.
6. [[к](06-c-basics)][[yt](https://youtu.be/6YEfGrcKMK8?si=4f4AzAKbPrftyIRw)][[vk](https://vk.com/video-221776054_456239024)] - Си. Printf/scanf, неожиданные последствия UB, буферизация, атака переполнением буфера, работа со строками используя арифметику указателей.
7. [[к](07-c-dynamic-mem)][[yt](https://youtu.be/8n6i81ZGi6U)][[vk](https://vk.com/video-221776054_456239025)] - Си. Работа с динамической памятью. malloc/calloc/realloc. Brk/Sbrk. OOM-killer.
8. [[к](08-utf-8)][[yt](https://youtu.be/ieerMEthNhE)][[vk](https://vk.com/video-221776054_456239026)] - Кодировки. Unicode, UTF-8, KOI8-R. Как работают emoji.
9. [[к](09-float)][[yt](https://youtu.be/G3_ZJeLUoRU)][[vk](https://vk.com/video-221776054_456239027)] - IEEE754, float/double, разбираемся в битах, смотрим на 0.1+0.2 != 0.3
10. [[к](10-gdb)][[yt](https://youtu.be/jf0zcz2fjFc)][[vk](https://vk.com/video-221776054_456239028)] - GDB. Break, watch. Встроенный питон. Обратный дебаг. Pretty printers.
11. [[к](11-sse)][[yt](https://youtu.be/lpDQ9suZirY)][[vk](https://vk.com/video-221776054_456239028)] - FPU, SIMD, пишем векторизацию на языке ассемблера
12. [[к](12-syscall)][[yt](https://youtu.be/1_J2gFa8Ur8)][[vk](https://vk.com/video-221776054_456239028)] - Системные вызовы. Read/Write, прерывания. 0x80
13. [[к](13-git)][[yt](https://youtu.be/O28CHd9_LME)][[vk](https://vk.com/video-221776054_456239028)] - Git. Ветки, коммиты. Делаем PR. Rebase.
14. [[к](14-yabloko-io)][[yt](https://youtu.be/4XRTW3Eug9Q)][[vk](https://vk.com/video-221776054_456239028)] - ОС YABLOKO. Port-mapped I/O, Memory-mapped I/O, делаем простую анимацию и игру.
15. [[к](15-yabloko-pit)][[yt](https://youtu.be/Wafpzzgtq_U)][[vk](https://vk.com/video-221776054_456239028)] - ОС YABLOKO. Пишем свой sleep, используя Programmable Interval Timer
16. [[к](16-fork)][[yt](https://youtu.be/dZfT3kA9_L0)][[vk](https://vk.com/video-221776054_456239028)] - Fork. Создаем процессы, дожимдаемся их выполнения. Форк-бомба.
17. [[к](17-exec)][[yt](https://youtu.be/WWS6j-TKr0w)][[vk](https://vk.com/video-221776054_456239028)] - Exec. Разбираемся, как баш запускает процессы, exec+lp/le/ve/vp/vpe. dup/dup2.
18. [[к](18-mmap)][[yt](https://youtu.be/WrSy-3RTblg)][[vk](https://vk.com/video-221776054_456239028)] - Mmap. Маппинг файла, анонимный маппинг, общая память в процессах. Как работает malloc.
19. [[к](19-files)][yt][vk] - Как работают файлы и права. inode, symlink vs hardlink. Что за странный буквы S, T в правах (drwxrwxrwt)
20. [[к](20-signals)][[yt](https://youtu.be/jja1D2VQSvs)][vk] - Сигналы. Обработчики. Sigaction. Почему не все функции можно использовать внутри обработчика.
21. ?????
22. [[к](22-pipes)][[yt](https://youtu.be/jIFUlpiBxrs)][vk] - Каналы. Pipe(2). Dup2(2). Как напрограммировать `ls -l | wc -l`. 
23. [[к](23-builds)][[yt](https://youtu.be/EzzcsUgIf6A)][vk] - Системы сборки. Make.
24. [[к](24-tests)][[yt](https://youtu.be/8v-_5VQ_hVg)][vk] - Тестирование проектов. C/Go.
25. [[к](25-sockets)][[yt](https://youtu.be/RE90c0PMBt4)][vk] - Сеть и сокеты. Getaddrinfo, connect, socket, accept. Простой клиент и сервер.
26. [[к](26-epoll)][[yt](https://youtu.be/JoMAEyHNzs0)][vk] - Мультиплексирование. Epoll. Edge-triggered vs level-triggered. Epoll + pipe. Epoll server.
27. [[к](27-fds)][yt][vk] - Все есть файловый дескриптор. eventfd, timerfd, signalfd. Соединяем все с epoll.
28. [[к](28-threads)][[yt](https://youtu.be/pPjDPe0duXc)][vk] - Pthread. Запускаем наибольшее возможное количество потоков. Передаем и принимаем параметры.
29. [[к](29-mutex)][yt][vk] - Mutex. Atomic vs mutex. Race и Deadlock. Делаем банк.
30. [к][[yt](https://youtu.be/vVI36v-_0dc)][vk] - Арендуем сервер в облаке. Запускам свой epoll сервер. nginx + systemd.

# Консультации

1. [yt](https://youtu.be/Ad-wV1it4Ls?si=ayp3mM1UauGXmy98) - секции кода, представление чисел, гдб

