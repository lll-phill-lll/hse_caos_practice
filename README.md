# Странички семинаров по курсу CAOS (Computer Architecture and Operating Systems) HSE

# Проекты

В качестве семинарской оценки у нас будет оценка за проект.

Страничка с проектами: TBD

Проекты прошлых годов:

[2022](2022_216/projects)
[2023](2023-226/projects)

# Темы текущего года

к - конспект

yt - ссылка на запись ютуб

vk - ссылка на запись вк

1. [[к](01-intro)][[yt](https://youtu.be/ct35VNB5j60)][[vk](https://vk.com/video-221776054_456239032)] - Терминал. vim. tmux. Устанавливаем qemu с убунтой на мак. Смотрим, как сдавать дз.
2. [[к](02-asm)][[yt](https://youtu.be/BXmhZjrzliI)][[vk](https://vk.com/video-221776054_456239033)] - x64 asm. Арифметика, условные и безусловные переходы, gdb, сдвиги.
3. [[к](03-memory)][[yt](https://youtu.be/44okapcnBM0)][[vk](https://vk.com/video-221776054_456239034)] - Первая "переменная", массивы, стек
4. [[к](04-cdecl)][[yt](https://youtu.be/RsyL8UWR42o)][[vk](https://vk.com/video-221776054_456239035)] - Стек, соглашение о вызовах, пролог, эпилог
5. [[к](05-calling-conventions-2)][[yt](https://youtu.be/Rm3lkXXVf3w)][[vk](https://vk.com/video-221776054_456239036)] - Соглашение о вызовах. Вызываем c/c++ код из асм кода и наоборот. Указатели на функции.
6. [[к](06-c-basics)][[yt](https://youtu.be/Dy27sxfRakk)][[vk](https://vk.com/video-221776054_456239039)] - Язык C. Printf/scanf. Строки/массивы. Опасности UB.
7. [[к](07-c-memory)][[yt](https://youtu.be/bLqGNXUBEFM)][[vk](https://vk.com/video-221776054_456239040)] - Динамическая память. Устройство аллокатора. malloc(0) в цикле. OOM-killer.
8. - TBA
9. [[к](09-floats)][[yt](https://youtu.be/cRToBPl9yz0)][[vk](https://vk.com/video-221776054_456239041)] - Числа с плавающей точкой. IEEE754. Всякие возникающие приколы.
10. [[к](10-simd)][[yt](https://youtu.be/SGOaM2ruocI)][[vk](https://vkvideo.ru/video-221776054_456239042)] - АКОС 10. FPU. SIMD. Векторизация. Интринсики.
11. [[к](11-syscalls)][[yt](https://youtu.be/R7MbnfvVHdg)][[vk](https://vkvideo.ru/video-221776054_456239045)] - Системные вызовы. read/write
12. [[к](12-fs)][[yt](https://youtu.be/eMnMRuf1lNc)][[vk](https://vkvideo.ru/video-221776054_456239046)] - Работа с файлами: inode, readdir, lstat, symlink, rwxrwSrwT. Пишем свой ls -l
13. [[к](13-git)][[yt](https://youtu.be/lJugblvqpKY)][[vk](https://vkvideo.ru/video-221776054_456239047)] - git + github
14. [[к](14-yabloko)][[yt](https://youtu.be/Uu-COuOY8Oc)][[vk](https://vkvideo.ru/video-221776054_456239048)] - yabloko. Устройство ОС. Делаем игру.
15. ???
16. [[к](16-fork)][[yt](https://youtu.be/pZjlb8GF_Bg)][[vk](https://vkvideo.ru/video-221776054_456239049)] - Процессы и Fork.
17. [[к](17-exec)][yt][[vk](https://vkvideo.ru/video-221776054_456239054)] - exec
18. [[к](18-pipes)][[yt](https://youtu.be/5lqdXNpKEag)][[vk](https://vkvideo.ru/video-221776054_456239050)] - Pipe + dup2. Доделываем свой игрушечный баш
19. [[к](19-signal)][[yt](https://youtu.be/VQsQKi8Dig0)][[vk](https://vkvideo.ru/video-221776054_456239051)] - Сигналы
20. [[к](20-mmap)][yt][vk] - mmap
21. [[к](21-make)][[yt](https://youtu.be/mpcQwARhfDU)][[vk](https://vkvideo.ru/video-221776054_456239053)] - система сборки make
22. [[к](22-tests)][yt][vk] - тестирование проектов
23. [[к](23-time)][yt][vk] - Время. time, localtime, strptime
24. [[к](24-cmake)][[yt](https://youtu.be/fZh1D3NUVTo)][[vk](https://vkvideo.ru/video-221776054_456239055)] - cmake

## Прошлые года

[2021 год. 207 группа](2021_207)

[2022 год. 216 группа](2022_216)

[2023 год. 226 группа](2023-226)

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
