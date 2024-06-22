# Странички семинаров по курсу CAOS (Computer Architecture and Operating Systems) HSE

# Проекты

В качестве семинарской оценки у нас будет оценка за проект.

Страничка с проектами: [проекты](projects)

Прошлогодние проекты: [проекты](2022_216/projects)

# Темы текущего года

к - конспект

yt - ссылка на запись ютуб

vk - ссылка на запись вк

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

## Прошлые года

[2021 год. 207 группа](2021_207)

[2022 год. 216 группа](2022_216)

## Правила игры

### Форматирование ASM

1. В одном блоке кода (участок кода отделенный новой строкой сверху и снизу) между командами и аргументами должен быть отступ одного размера. Отступ должен быть сделан табом, а не пробелом. То есть все аргументы должны быть выравнены.

```
        pushl   %ebp
        movl    %esp, %ebp

        subl    $4, %esp
        and     $-16, %esp
        leal    -4(%ebp), %eax
```

### Реджекты

Сданный код проходит тестирование в тестирующей системе, а затем проверяется глазами семинариста и ассистентов.

Прошедший тесты код может быть отправлен на исправление (получен статус reject), если решение является неоптимальным, если нарушает условия, установленные в задаче или если нарушает форматирование.

### Списывание

Проверка на списывание запускается в случайное время. При обнаружении списывания обнуляется ВЕСЬ контест и составляется записка в УО.

В проверке на списывание участвуют все доступные онлайн материалы, в том числе известные репозитории с решениями и решения прошлых годов.

Если вы берете код из общедоступного источника, то нужно прикладывать ссылку на этот источник и пояснять комментариями код, чтобы было видно, что вы этот код понимаете.



## Полезные ссылки

### Материалы

* [Материалы курса 2020 года](https://github.com/blackav/hse-caos-2020)
* [Материалы физтеха](https://github.com/victor-yacovlev/fpmi-caos)
* [Вики учебник по asm](https://ru.wikibooks.org/wiki/%D0%90%D1%81%D1%81%D0%B5%D0%BC%D0%B1%D0%BB%D0%B5%D1%80_%D0%B2_Linux_%D0%B4%D0%BB%D1%8F_%D0%BF%D1%80%D0%BE%D0%B3%D1%80%D0%B0%D0%BC%D0%BC%D0%B8%D1%81%D1%82%D0%BE%D0%B2_C)

### Тулзы

* [Godbolt - compiler explorer](https://gcc.godbolt.org/)

## Файлы

* [C11 стандарт](C11_standard.pdf)
