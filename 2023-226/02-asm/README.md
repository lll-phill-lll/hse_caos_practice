# [АК]ОС 2. Язык ассемблера. Представление целых чисел. Сдвиги. GDB.

## Видео

[[youtube](https://youtu.be/U6r8ubs-SAw)][[vk](https://vk.com/video-221776054_456239020)]

## Файлики с кодом

1. [Считываем 2 числа, выводим сумму](add_two.S)
2. [Считываем, пока считывается, выводим сумму считанного](infinite_read.S)
3. [Считываем число и печатаем его же](simple_read_write.S)
4. [Сдвиги - можно подебажить и посмотреть, что происходит](shifts.S)
5. [Выводим все числа меньше считанного](loop.S)

## Компиляция и запуск:

### Компиляция:

`gcc -m32 <file_name> -o <binname>`

`gcc -m32 prog1.S simpleio_i686.S -o prog1`

### Запуск:

`./prog1`

### Сгенерировать asm код из c:

`gcc -S -m32 -O0 file.c`

Появится файлик file.s
## simpleio_i686.S

readi32 - считать 32 битное число (сложится в eax)

readi64 - считать 64 битное число (сложится в edx:eax)

writei32 - напечатать 32 битное число (печатается из eax)

writei64 - напечатать 64 битное число (печатается из edx:eax)

Если ввод закончен, что флаг CF выставится в 1. Проверить по jc.

Чтобы закончить ввод нужно нажать CTRL+D или произвести ввод из файла `cat file.txt | ./a.out` или через `echo "1 2 3" | ./a.out`


## Регистры:

%eax, %ebx, %ecx, %edx, %esi, %edi, %ebp, %esp

## Инструкции:

        add    SRC, DST        /* DST += SRC */
        sub    SRC, DST        /* DST -= SRC */
        inc    DST             /* ++DST */
        dec    DST             /* --DST */
        neg    DST             /* DST = -DST */
        mov    SRC, DST        /* DST = SRC */
        imul   SRC             /* (%eax,%edx) = %eax * SRC - знаковое */
        mul    SRC             /* (%eax,%edx) = %eax * SRC - беззнаковое */
        and    SRC, DST        /* DST &= SRC */
        or     SRC, DST        /* DST |= SRC */
        xor    SRC, DST        /* DST ^= SRC */
        not    DST             /* DST = ~DST */
        cmp    SRC, DST        /* DST - SRC, результат не сохраняется, */
        test   SRC, DST        /* DST & SRC, результат не сохраняется  */
        adc    SRC, DST        /* DST += SRC + CF */
        sbb    SRC, DST        /* DST -= SRC - CF */
        sdq                    /* расширяет старший бит регистра %eax на %edx */

## Флаги:

Большинство арифметических инструкций в результате вычисления результата инструкции устанавливают арифметические флаги слова состояния процесса.

Флаг *ZF* устанавливается, если в результате операции был получен нуль.

Флаг *SF* устанавливается, если в результате операции было получено отрицательное число.

Флаг *CF* устанавливается, если в результате выполнения операции произошел перенос из старшего бита результата. Например, для сложения CF устанавливается если результат сложения двух беззнаковых чисел не может быть представлен 32-битным беззнаковым числом.

Флаг *OF* устанавливается, если в результате выполняния операции произошло переполнение знакового результата. Например, при сложении OF устанавливается, если результат сложения двух знаковых чисел не может быть представлен 32-битным знаковым числом.

Обратите внимание, что и сложение addl, и вычитание subl устанавливают одновременно и флаг CF, и флаг OF. Сложение и вычитание знаковых и беззнаковых чисел выполняется совершенно одинаково, и поэтому используется одна инструкция и для знаковой, и для беззнаковой операции.

## Переходы:

        jz      label   /* переход, если равно (нуль), ZF == 1 */
        jnz     label   /* переход, если не равно (не нуль), ZF == 0 */
        jc      label   /* переход, если CF == 1 */
        jnc     label   /* переход, если CF == 0 */
        jo      label   /* переход, если OF == 1 */
        jno     label   /* переход, если OF == 0 */
        jg      label   /* переход, если больше для знаковых чисел */
        jge     label   /* переход, если >= для знаковых чисел */
        jl      label   /* переход, если < для знаковых чисел */
        jle     label   /* переход, если <= для знаковых чисел */
        ja      label   /* переход, если > для беззнаковых чисел */
        jae     label   /* переход, если >= (беззнаковый) */
        jb      label   /* переход, если < (беззнаковый) */
        jbe     label   /* переход, если <= (беззнаковый) */

## GDB:

### Компиляция:

Нужно компилировать с отладочными символами, добавив `-g`

`gcc -m32 -g prog1.S simpleio_i686.S -o prog1`

### Запуск:

`gdb ./prog1`

### Команды:

    list (l)- показать код.  l 3 показать код с третей строки
    break (b)- установить брейкпоинт. Нужно указать имя функции или строку. b main. Выполнение дойдет до этого места и остановится.
    run (r) - запустить программу
    info break (i b) - посмотреть брейкпоинты
    del <breakpoint num> - удалить брейкпоинт с номером breakpoint_num
    layout regs (la reg) - включить просмотр регистров
    step (s) - сделать шаг исполнения (с заходом в функции)
    next (n) - сделать шаг исполнения (без захода в функции)
    continue (c) - продолжить выполнение до следующего брейкпоинта
    refresh - обновить отображение (если все съехало или перекособочилось)
    finish - выйти из функции
    help <command> - справка по команде

    p/t $eax - напечатать регистр eax бинарно
    p/z $eax - напечатать регистр eax 16-рично
    set $eax=5 - установить значение $eax равное 5
    jump main - продолжить выполнение с другого места (не обязательно main, можно указать любое другое место или номер строки)
    p/t $eax^3 - напечатать в бинарном виде рузультат выполнения команды $eax XOR 3 (другие логические операции тоже можно использовать)
    ctrl+x o - переключиться между панелями


## Сдвиги:

Указаны быстрые пояснения к сдвигам, котоорые взяты с [вики учебник по asm](https://ru.wikibooks.org/wiki/%D0%90%D1%81%D1%81%D0%B5%D0%BC%D0%B1%D0%BB%D0%B5%D1%80_%D0%B2_Linux_%D0%B4%D0%BB%D1%8F_%D0%BF%D1%80%D0%BE%D0%B3%D1%80%D0%B0%D0%BC%D0%BC%D0%B8%D1%81%D1%82%D0%BE%D0%B2_C) полное описание смотрите в источнике.

### shl - логические сдвиг влево

```
                              До сдвига:
          +---+     +----------------------------------+
          | ? |     | 10001000100010001000100010001011 |
          +---+     +----------------------------------+
         Флаг CF    Операнд

                       Сдвиг влево на 1 бит:
          +---+     +----------------------------------+
          | 1 | <-- | 00010001000100010001000100010110 | <-- 0
          +---+     +----------------------------------+
         Флаг CF    Операнд

                      Сдвиг влево на 3 бита:
 +----+   +---+     +----------------------------------+
 | 10 |   | 0 | <-- | 01000100010001000100010001011000 | <-- 000
 +----+   +---+     +----------------------------------+
Улетели  Флаг CF    Операнд
в никуда

```

### shr - логический сдвиг вправо

```
                  До сдвига:
        +----------------------------------+     +---+
        | 10001000100010001000100010001011 |     | ? |
        +----------------------------------+     +---+
        Операнд                                  Флаг CF

          Логический сдвиг вправо на 1 бит:
        +----------------------------------+     +---+
  0 --> | 01000100010001000100010001000101 | --> | 1 |
        +----------------------------------+     +---+
        Операнд                                 Флаг CF

          Логический сдвиг вправо на 3 бита:
        +----------------------------------+     +---+  +----+
000 --> | 00010001000100010001000100010001 | --> | 0 |  | 11 |
        +----------------------------------+     +---+  +----+
        Операнд                                 Флаг CF Улетели
                                                        в никуда
```

### sal - арифметический сдвиг влево

Не отличается от shl

### sar - арифметический сдвиг вправо

```
                  До сдвига:
        +----------------------------------+     +---+
        | 10001000100010001000100010001011 |     | ? |
        +----------------------------------+     +---+
        Операнд                                  Флаг CF
        старший бит равен 1 ==>
          ==> значение отрицательное ==>
          ==> "вдвинуть" бит 1 ---+
                                  |
  +-------------------------------+
  |
  V       Арифметический сдвиг вправо на 1 бит:
        +----------------------------------+     +---+
  1 --> | 11000100010001000100010001000101 | --> | 1 |
        +----------------------------------+     +---+
        Операнд                                 Флаг CF

          Арифметический сдвиг вправо на 3 бита:
        +----------------------------------+     +---+  +----+
111 --> | 11110001000100010001000100010001 | --> | 0 |  | 11 |
        +----------------------------------+     +---+  +----+
        Операнд                                 Флаг CF Улетели
                                                        в никуда
```

### rol - циклический сдвиг(вращение) влево

```
                              До сдвига:
      +---+         +----------------------------------+
      | ? |         | 10001000100010001000100010001011 |
      +---+         +----------------------------------+
     Флаг CF        Операнд

                      Циклический сдвиг влево на 1 бит:
      +---+  1    1 +----------------------------------+
      | 1 | <--+--- | 00010001000100010001000100010111 | ---+
      +---+    |    +----------------------------------+    |
     Флаг CF   V    Операнд                                 ^
               |                                            |
               +------------------->--->--->----------------+
                1

                      Циклический сдвиг влево на 3 бита:
      +---+  0  100 +----------------------------------+
      | 0 | <--+--- | 01000100010001000100010001011100 | ---+
      +---+    |    +----------------------------------+    |
     Флаг CF   V    Операнд                                 ^
               |                                            |
               +------------------->--->--->----------------+
                100

```

### ror - циклический сдвиг(вращение) вправо

```
                  До сдвига:
        +----------------------------------+         +---+
        | 10001000100010001000100010001011 |         | ? |
        +----------------------------------+         +---+
        Операнд                                     Флаг CF

          Циклический сдвиг вправо на 1 бит:
        +----------------------------------+ 1    1  +---+
   +--- | 11000100010001000100010001000101 | ---+--> | 1 |
   |    +----------------------------------+    |    +---+
   ^    Операнд                                 V   Флаг CF
   |                                            |
   +-------------------<---<---<----------------+
                                               1

          Циклический сдвиг вправо на 3 бита:
        +----------------------------------+ 011  0  +---+
   +--- | 01110001000100010001000100010001 | ---+--> | 0 |
   |    +----------------------------------+    |    +---+
   ^    Операнд                                 V   Флаг CF
   |                                            |
   +-------------------<---<---<----------------+
                                             011

```