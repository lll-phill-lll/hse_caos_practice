
# Загрузка / сохранение

fld   [x]              -> push floating-point x в FPU stack
fild  [x]              -> push integer x в FPU stack

fst   [x]              -> записать st(0) в память
fstp  [x]              -> записать st(0) в память и pop

fld   st(i)            -> push копии st(i)
fxch  st(i)            -> swap(st(0), st(i))

fld1                   -> push 1.0
fldz                   -> push 0.0
fldpi                  -> push pi

# Арифметика

fadd  st(0), st(i)     -> st(0) = st(0) + st(i)
fsub  st(0), st(i)     -> st(0) = st(0) - st(i)
fmul  st(0), st(i)     -> st(0) = st(0) * st(i)
fdiv  st(0), st(i)     -> st(0) = st(0) / st(i)

faddp st(1), st(0)     -> st(1) += st(0), pop
fsubp st(1), st(0)     -> st(1) -= st(0), pop
fmulp st(1), st(0)     -> st(1) *= st(0), pop
fdivp st(1), st(0)     -> st(1) /= st(0), pop

fiadd [x]               -> st(0) += integer x
fisub [x]               -> st(0) -= integer x
fimul [x]               -> st(0) *= integer x
fidiv [x]               -> st(0) /= integer x

fsqrt                   -> st(0) = sqrt(st(0))
fabs                    -> st(0) = abs(st(0))
fchs                    -> st(0) = -st(0)


# Сравнения

fucomi  st(0), st(i)    -> сравнить st(0) ? st(i), выставить ZF/PF/CF
fucomip st(0), st(i)    -> то же + pop

jb   -> <
je   -> ==
ja   -> >
jp   -> unordered (NaN)

