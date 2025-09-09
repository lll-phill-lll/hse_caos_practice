# Введение. Как поставить линукс на свою машину. Простые команды.

## Запись
[[к](01-intro)][[yt](https://youtu.be/Hk1x05fBTKw)][[vk](https://vkvideo.ru/video-221776054_456239058)]

## Ставим линукс

Virtual Box, Docker, WSL - http://wiki.cs.hse.ru/CAOS-2023/24
Qemu - http://wiki.cs.hse.ru/CAOS-2021

### Docker + vscode

Установить докер: [мак](https://docs.docker.com/desktop/setup/install/mac-install/), [windows](https://docs.docker.com/desktop/setup/install/windows-install/)

Для запуска в первый раз нужно выполнить:
`docker run -it --platform linux/amd64 -v ~/caos:/caos -w /caos --name x86 ubuntu:24.04`

- `docker run -it` - запустить в интерактивном режиме - откроется командная строка контейнера. Чтобы запустить в режиме демона (чтобы работало фоном) нужно `-it` поменять на `-d`
- `--platform linux/amd64` запустит контейнер под amd64 (x86_64)
- `-v ~/caos:/caos` свяжет папку `~/caos` на вашем компе с папкой `/caos` внутри контейнера. Это будет общая папка. Изменения будут синхронизироваться между убунту и вашим компьютером.
- `-w /caos` при запуске зайти сразу в папку `/caos`

Для остановки нужно или закрыть терминал, или выполнить `exit`. Если запустили в режиме демона, то нужно выполнить `docker stop x86`.

При повторном запуске нужно выполнить `docker start -ai x86`. 

В vscode (https://code.visualstudio.com/) нужно зайти во вкладку extensions и там установить расширение `dev containers`.

Сбоку появится иконка компьютера. Нужно на нее нажать и выбрать в списке наш контейнер x86. Далее рядом с ним нажать на стрелку вправо.

После нужно зайти в папку `/caos`: `File -> Open Folder -> /caos`.

Теперь можно тут создавать файлы и они будут создаваться в папке `caos` и будут доступны из linux, с вашего компьютера и из vscode. Компиляция будет происходить на линуксе

## Qemu (мак)

вроде на винде тоже можно, но я не проверял( 

1. Если у вас еще нет `brew`, то установите по ссылке: https://brew.sh/

2. Далее в терминале: `brew install qemu`

3. `brew list qemu` - смотрим, куда qemu установился. Нас интересует `x86_64`. В моем случае это `/opt/homebrew/Cellar/qemu/10.1.0/bin/qemu-system-x86_64`.

4. сохраняем себе скрипт в файл `run_qemu.sh`:

```
QEMU_PATH=/opt/homebrew/Cellar/qemu/10.1.0/bin/qemu-system-x86_64

FS_IMAGE_PATH=xubuntu_caos_2021.qcow2

CPU_COUNT=4
MEMORY_MB=4096

${QEMU_PATH} \
        -smp ${CPU_COUNT} \
        -m ${MEMORY_MB} \
        -name xubuntu_caos_2021 \
        -hda ${FS_IMAGE_PATH} \
        -vga virtio \
        -display default,show-cursor=on \
        -usb \
        -accel tcg \
        -chardev qemu-vdagent,id=ch1,name=vdagent,clipboard=on \
        -device virtio-serial-pci \
        -device virtserialport,chardev=ch1,id=ch1,name=com.redhat.spice.0
```

Вместо `QEMU_PATH` нужно поставить путь до `qemu-system-x86_64`, который мы нашли на предудыщем шаге. Файл `xubuntu_caos_2021.qcow2` нужно положить рядом со скриптом. За файлом обращайтесь ко мне.

При желании можно увеличить CPU и MEMORY_MB, это количество ядер и оперативной памяти, которые вы выделяете под линукс.


5. `chmod +x run_qemu.sh` - разрешаем скрипту выполняться
6. `./run_qemu.sh`
7. чтобы сделать окно больше, нужно в настройках самого линукса в display выбрать другое разрешение
8. пароль и пользователь xubuntu


## Терминал

	ls - вывести содержимое текущей директории 
	ls -l - вывести подробное содержимое директории
	ls -a - вывести все, включая скрытые файлы
	ls <path_to_dir> - вывести содержимое директории path_to_dir
	pwd - вывести текущую директорию
	cd <path_to_dir> - сменить директорию
	cd .. - вернуться на уровень назад
	cat file - вывести содержимое файла file
	mkdir <dir_name> - создать директорию
	mkdir -p <dirs_path> - создать путь из директорий a/b/c
	touch <filename> - создать файл
	echo "abc" - вывести abc
	echo -e "abc\nabc" - интерпретировать \n как новую строку
	man <command> - получить справку по команде
	echo "abc" > file - поместить строку "abc" в файл file
	wc -l <filename> - вывести количество строк в файле filename
	cat <filename> | wc -l - другой способ посчитать количество строк в файле

## vim

#### Поучиться использованию вима:

1. vimtutor - ввести в терминале
2. https://vim-adventures.com/ - игра 

#### куда я жмал?

1. hjkl - влево, вниз, вправо, влево
2. esc - перейти в normal режим 
3. i - перейти в режим ввода
4. :w - сохранить изменения
5. :q - выйти
6. :q! - выйти без сохранения последних изменений
7. :wq - сохранить и выйти

Более полный список штук: https://vim.rtorr.com/
## tmux

	tmux attach -t <name> || tmux new -s <name> - Открыть сессию name, если такой нет, то создать

|| - означает, что следующая команда будет запущена только если предыдущая завершилась неудачно

	CTRL+B % - открыть еще одну панель справа
	CTRL+B " - открыть еще одну панель снизу
	CTRL+B x - закрыть текущую панель
	CTRL+B z - открыть/закрыть текущую панель на весь экран

более полный список штук: https://gist.github.com/MohamedAlaa/2961058
