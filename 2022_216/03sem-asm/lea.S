// ** Условие **
// Сравнить результат работы lea и mov

   .global main
    // метки main и arr на самом деле это адреса следующей за ними инструкции
main:
    mov     $1, %edx
    // lea сохраняет адрес, положим его в %eax, чтобы напечатать
    // lea - load effective address
    lea     arr(, %edx, 4), %eax    // arr + edx * 4 -> eax
    call    writei32
    // mov сохранит значение по адресу, положим его в %eax, чтобы напечатать
    mov     arr(, %edx, 4), %eax    // value(arr + edx * 4) -> eax
    call    writei32

    // Вместо операции выше мы могли бы сделать так:
    // Но лучше использовать lea, поскольку в таком случае не
    // сохраняется промежуточное значение -> работает более эффективно
    mov     $arr, %eax
    shl     $2, %edx
    add     %edx, %eax
    call    writei32

    call    finish

arr:
    .int    5
    .int    6
    // 200 int elements
    .skip   800
