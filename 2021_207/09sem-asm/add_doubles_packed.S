    .text
    .global main
main:
        push    %ebp
        mov     %esp, %ebp

        movupd  x, %xmm0
        movupd  y, %xmm1


        // addps:

        // float A[4];
        // float B[4];

        // B[0] = A[0] + B[0]
        // B[1] = A[1] + B[1]
        // B[2] = A[2] + B[2]
        // B[3] = A[3] + B[3]


        // haddps:

        // float A[4];
        // float B[4];

        // B[0] = B[0] + B[1];
        // B[1] = B[2] + B[3];
        // B[2] = A[0] + A[1];
        // B[3] = A[2] + A[3];


        haddpd   %xmm1, %xmm0

        // sub     $8, %esp
        // movhpd  %xmm0, (%esp)
        // sub     $8, %esp
        // movlpd  %xmm0, (%esp)

        sub     $16, %esp
        movupd  %xmm0, (%esp)

        push    $printf_format

        call    printf

        mov     %ebp, %esp
        pop     %ebp

    .data
x:
    .double    1.1, 2.2
y:
    .double    3.3, 4.4


printf_format:
    .string "%lf, %lf\n"
