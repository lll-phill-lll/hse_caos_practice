# 10 Семинар 31.01.2023 Yabloko

## Код:

* [Делаем свой sleep через PIT](timer.c)
* [Добавляем поддержку shift и заглавных букв в клавиатуру](keyboard.c)


## Поддержка shift:

[Документация по использованию клавиатуры](https://wiki.osdev.org/PS2_Keyboard)

У нас есть событие, что на клавишу нажали, а также есть событие, что клавишу отжали.

И на то и на другое событие происходит прерывание. Поэтому можем детектировать ситуацию, что shift нажали, но не отпустили

а после этого нажали еще один символ. Тогда выводим модифицированный шифтом символ: а -> A.

## Sleep:

[Документация по Programmable Interval Timer](https://wiki.osdev.org/Programmable_Interval_Timer)

Чтобы сделать sleep, запустим таймер, который время от времени будет присылать нам прерывания.

Чтобы его запустить, нужно отправить на порт `0x43` 8 бит с описаниием режима работы таймера.

А затем в порт `0x40` отправить изначальное значение таймера. Это значение должно быть 16 битным, а загружать в порт можно

только 8 бит. Поэтому загружать нужно два раза. Девайс ожидает, что сначала придут 8 нижних бит, а следом 8 верхних.
