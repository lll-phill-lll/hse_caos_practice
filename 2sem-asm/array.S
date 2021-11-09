    .global main
main:
    call readi32 // read index
    mov %eax, %ebx
    call readi32 // read value
    mov %eax, %edx

    mov $arr, %edi // move address of arr to edi use $
    shl $2, %ebx
    add %ebx, %edi
    mov (%edi), %eax
    // same as:   mov (%edi, %ebx, 4), %eax   -- edi + ebx * 4 -> eax
    // or:        mov arr(%edi, %ebx, 4), %eax  -- addr(arr) + edi + ebx * 4 -> eax
    // our case:  mov arr(, %ebx, 4), %eax      -- addr(arr) + ebx * 4 -> eax


    call writei32

    mov %edx, (%edi) // move to address from edi

    jmp main

    call finish

    .data
arr:
    .skip 800 // 200 value 4 bytes each (int)

