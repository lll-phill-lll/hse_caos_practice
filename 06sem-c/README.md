# 6 ****Семинар 07.12.2021****

## Буфферизация

```c
int main() {
    // setbuf(stdout, NULL);
    for (int i=0; i<10; ++i) fprintf(stdout,"%d",i);
    sleep(10);
    return 0;
}
```

- сначала поспим, потому выведем, потому что это всё буфферизируется и на самом деле вызов будет в конце программы
- А если раскомментировать `setbuf`, то мы сначала напишем, а потом пойдем спать

**Условия для сбрасывание буффера:**

- `\n` — перевод строки
- переполнение буффера
- можно явно сказать, куда выводить и если это `stderr`, то буффер сбросится
- `fflush():`

**Посмотрим на скорость работы с буффером и без буффера**

```c
void print(unsigned num) {
    clock_t t;
    t = clock();
    for (unsigned i = 0; i != num; ++i) {
        printf("hello, num %u", i);
    }
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC;
    fprintf(stderr, "%f seconds\n", time_taken);
}

int main() {
    unsigned iters = 10000000;
    print(iters);
    setbuf(stdout, NULL);
    print(iters);
}
```

- с буффером программы работают намного быстрее

## Каретка

```c
void print_hello() {
    printf("%s", "Hello world");
    fflush(stdout);
    sleep(1);
    printf("\r");
    fflush(stdout);
    sleep(1);
    printf("%15s lala\n %d fgdjhg \n \r 8989", "smth", 5);
}

void print_numbers() {
    for (int i = 0; i != 1 << 30; ++i) {
        printf("\r%d", i);
    }
}

int main() {
    print_hello();
    // print_numbers();
}
```

- `\r` двигает каретку в начало (то есть благодаря этому можно перезатирать вывод. То есть числа будут писаться в одной ячейке)
    - Linux — LF = \n
    - Win — CR LF = \r\n
- `\b` двигает каретку на одну назад
- Можно задавать отступ (причем как слева, так и справа)
- **Если мы выставим не все аргументы, то это УБ**

## Красивый progressbar (анимация)

```c
enum {
    PERCENT = 5,
    LEN = 100 / PERCENT,
};
void print(unsigned p) {
    int p_ = p / PERCENT;
    printf("\r[");
    for (int i = 0; i != p_; ++i) {
        printf("-");
    }
    printf(">");
    for (int i = p_; i < LEN-1; ++i) {
        printf(" ");
    }
    printf("]%4u%%", p);
    fflush(stdout);
}

void f() {
    sleep(1);
}

int main() {
    print(0);
    for (int i = 0; i <= LEN; ++i) {
        f();
        print(i*PERCENT);
    }
    printf("\n");
}
// [------>        ] 45%
// [----------->   ] 63%
```

## Работаем с файлом

**Тут мы ходим по произвольным местам в файле** 

```c
enum {
    N = 5,
};

int main(int argc, char* argv[]) {

    FILE* file = fopen(argv[1], "r");

	if (file == NULL) {
        perror("lala");
        exit(1);
    }

    long x;
    sscanf(argv[2], "%ld", &x);
    long y;
    sscanf(argv[3], "%ld", &y);

    long offset = y * (N + 1) + x;
    if (fseek(file, offset, SEEK_SET) != 0) {
        perror("fseek");
        exit(1);
    }

    char c = fgetc(file);
    if (c == '1') {
        printf("Found\n");
    } else {
        printf("Try again\n");
    }

    fclose(file);
}
```

- `r` — хотим уметь толкьо читать
- **Красивые ошибки:**
    - `perror` — более осмысленная ошибка
    - `fprintf` — кастомная ошибка
- `fseek` — выставляет filepointer в нужное место
- `fgetc` — для того, чтобы считать `char`