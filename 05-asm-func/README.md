## Файлики с кодом:
- Указатели на функции: my_for_each: [c++](function_pointer.cpp), [asm](my_for_each.S)
- Variadic functions - считаем сумму аргументов: [c++](variadic.cpp), [asm](my_add_nums.S)
- Variadic functions - свой простой scanf (нужен simpleio): [c++](scan.cpp), [asm](my_scan.S) 

## Указатели на функции:

[Текст взят из материалов прошлых лекций](https://github.com/blackav/hse-caos-2020/tree/master/06-function-pointers)

Декларатор вида

```
int (*pfunc)(int a, int b);
```

читается следующим образом: `pfunc` &mdash; это указатель на функцию, принимающую два параметра типа `int` и возвращающую значение типа `int`.
То есть `pfunc` &mdash; это переменная <b>указатель на функцию</b>. С помощью `typedef` переменная может быть объявлена следующим образом:

```
typedef int (*func_t)(int a, int b); // func_t - тип указателя на функцию
func_t pfunc;
```

Любая переменная-указатель на функцию может принимать значение `NULL` (или 0, или nullptr в Си++).
Если переменная-указатель на функцию не равна NULL, она должна <i>указывать на</i> функцию,
совместимую по передаваемым параметрам и возвращаемому значению.

Операция взятия адреса `&`, примененная к имени функции, дает значение типа указателя на функцию
с соответствующим количеством и типом параметров и типом возвращаемого значения, например,

```
int handler(int value, int mask);

    &handler   // даст значение типа int (*)(int, int)
```

Однако, для имен функций автоматически выполняется неявное преобразование имени функции в указатель на функцию.
То есть,

```
pfunc = handler;
```

это то же самое, что

```
pfunc = &handler;
```

Поэтому, как правило, явную операцию взятия адреса перед именами функций не пишут.

## Variadic functions:

Функции с переменным числом аргументов - функции, в которые можно передать не определенное количество армументов. Пример такой функции `printf`: `int printf(const char * restrict format, ...);`

Чтобы получить доступ к переданным параметрам используются специальные макросы, которые описаны ниже.

### Документация:

- [va_start](https://en.cppreference.com/w/cpp/utility/variadic/va_start)
- [va_arg](https://en.cppreference.com/w/cpp/utility/variadic/va_arg)
- [va_end](https://en.cppreference.com/w/cpp/utility/variadic/va_end)
- [va_list](https://en.cppreference.com/w/cpp/utility/variadic/va_list)
- [документация по C](https://en.cppreference.com/w/c/variadic)
	
