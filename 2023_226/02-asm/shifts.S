    .global main
main:
    call    readi32

beg:

// all shifts use CF

// ----- SHift logical Left/Right -----
shl:
    shl     $1, %eax
shr:
    shr     $1, %eax

// l: 0001 -> 0010; 1001 -> 0010
// r: 0001 -> 0000; 1001 -> 0100

// ----- Shift Arithmetic Left/Right -----
// same as shl
sal:
    sal     $1, %eax
sar:
    sar     $1, %eax
// l: 0001 -> 0010; 1001 -> 0010
// r (+): 0001 -> 0000; 1001 -> 0100
// r (-): 1 -> 11; 1001 -> 1100

// ----- ROtate Left/Right -----
rol:
    rol     $1, %eax
ror:
    ror     $1, %eax

// l: 0001 -> 0010; 1001 -> 0011
// r: 0001 -> 1000; 1001 -> 1100

// ----- Rotate Carry Left/Right -----
// l: 1001 (CF=X) -> 001X (CF=1)
rcl:
    rcl     $1, %eax
rcr:
    rcr     $1, %eax

fin:
    call    writei32
    call    finish
