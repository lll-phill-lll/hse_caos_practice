## Ассемблерные вставки

### Полезные ссылки
* [Конспект прошлогдней лекции](https://curious-sailor-21e.notion.site/10-f9dc55dfa327409fb3fbce1619114af7)
* [Документация](https://gcc.gnu.org/onlinedocs/gcc/Using-Assembly-Language-with-C.html)

### Файлы
* [Пример сложения, работа с входными и выходными параметрами](simple_addition.c)
* [Системный вызов, передача аргументов напрямую в регистры](syscall.c)
* [Ключевое слово volatile](volatile.c)
* ["memory" в списке clobbers](clobber_memory.c)

### volatile

Ключевое слово `volatile` используется чтобы указать компилятору, что у ассемблерной вставки есть побочные эффекты.
Например, компилятор не может удалить вставку, если её выходные параметры больше нигде не используются.
Также `volatile` не позволяет компилятору выносить вставку из циклов.

Пример:
```bash
# Без volatile. У ассемблерной вставки нет входных параметров, поэтому компилятор решил, что её можно выполнить один раз.
$ clang -m32 -O2 ./inline_asm/volatile.c && ./a.out
timestamps[0] = 18581236103476
timestamps[1] = 18581236103476
timestamps[2] = 18581236103476
timestamps[3] = 18581236103476
timestamps[4] = 18581236103476

# С volatile. Вставка честно выполняется на каждой итерации.
$ clang -m32 -O2 ./inline_asm/volatile.c -DVOLATILE && ./a.out
timestamps[0] = 18668519100871
timestamps[1] = 18668519100891
timestamps[2] = 18668519100911
timestamps[3] = 18668519100931
timestamps[4] = 18668519100949

# gcc не оптимизирует вставку, но полагаться на это не стоит.
$ gcc -m32 -O2 ./inline_asm/volatile.c && ./a.out
timestamps[0] = 19005083131303
timestamps[1] = 19005083131501
timestamps[2] = 19005083131531
timestamps[3] = 19005083131564
timestamps[4] = 19005083131584
```

Ассемблерная вставка с пустым списком outputs считается volatile по умолчанию.

### "memory"

Если ассемблерная вставка выполняет чтение или запись в произвольные участки памяти, в clobbers нужно указывать `"memory"`.

```bash
# Без "memory". Компилятор переупорядочил обращения к памяти, и строка "hello world" записалась в буфер уже после выполнения вставки.
$ gcc -m32 -O2 ./inline_asm/clobber_memory.c && echo "kek" | ./a.out
hell

# Добавили "memory", всё работает.
$ gcc -m32 -O2 ./inline_asm/clobber_memory.c -DCLOBBER_MEMORY && echo "kek" | ./a.out
kek

```
