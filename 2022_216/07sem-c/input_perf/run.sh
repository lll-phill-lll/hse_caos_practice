#!/bin/bash

set -e

echo "Test 1M data"
dd if=/dev/urandom of=data bs=1M count=1 2>/dev/null
for IO in READ FSCANF; do
    gcc -Wall -Werror -std=gnu11 -O2 -DIO_${IO} ./main.c
    echo -e "==========\n$IO"
    time ./a.out < data
done

echo -e "\n\nTest 10M data"
dd if=/dev/urandom of=data bs=10M count=1 2>/dev/null
for IO in FSCANF FGETC; do
    gcc -Wall -Werror -std=gnu11 -O2 -DIO_${IO} ./main.c
    echo -e "==========\n$IO"
    time ./a.out < data
done

echo -e "\n\nTest 100M data"
dd if=/dev/urandom of=data bs=100M count=1 2>/dev/null
for IO in FGETC GETC GETC_UNLOCKED; do
    gcc -Wall -Werror -std=gnu11 -O2 -DIO_${IO} ./main.c
    echo -e "==========\n$IO"
    time ./a.out < data
done

rm data a.out
