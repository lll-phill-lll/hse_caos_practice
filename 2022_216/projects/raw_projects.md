1. **Github messenger** [необычное использование привычных технологий]. Сделать мессенджер, с помощью которого можно переписываться используя гитхаб. Для человека это выглядит как мессенджер (в терминале или нет).
А имплементация использует команды гита, чтобы отправлять сообщения (например, через коммиты). Должны поддерживаться комнаты, разные диалоги и тп.
2. **Следим за спиной** [допонительные устройства]. Нужно какое-то устройство, которое имеет гироскоп, например, joycon. Написать плагин для IDE (vscode, idea, vim), который подключается к joycon.
И следит за тем, чтобы во время программирования стина была ровная. Допустим, джойкон прикрепляется на шапку или на лоб. Когда положение гироскопа показывает
что программист скривил спину, то отображается уведомление в IDE или производится вибрация (опять же для ситуации с джойконом).
3. **Ascii video call** [приколы в терминале]. 2 компьютера подключаются друг к другу по сети. У обоих включается камера и осуществляется передача картинки друг другу.
Должно получиться что-то вроде видео звонка, только без звука и отображая картинку ascii символами.
4. ** Rescue files** [распределенные системы]. Приложение, которое спасает файл. Пусть у нас в локальной сети есть сколько-то компьютеров и на каких-то из них запущено наше приложение. При вызове команды
приложения на данном компьютере приложение должно сделать следующее: разбить поданный на вход файл на части, пройтись по всем доступным компьютерам в локальной
сети и проверить, на каких из них запущено приложение, после этого загрузить части файла на эти компьютеры (с избыточностью). Во время загрузки компьютеры могут
становиться недоступны, в таком случае части файла должны перераспределяться. После этого должна быть возможность скачать этот файл обратно. Во время скачивания некоторые
компьютеры могут быть уже недоступны, а доступные могут становиться недоступными.
5. **Png encoding** [повторяем существующие алгоритмы]. На вход приложению дается картинка в сыром виде: 3х мерный массив размера HxWx3 в котором для каждого пикселя определены RGB компоненты. Требуется сжать картинку
в png и сохранить ее.
6. **Good first issue** [коммитим]. Также можно найти issue в гитхабе, например, используя [goodfirstissue.dev](https://goodfirstissue.dev/). И сделать pull request. Issue предварительно нужно согласовать.
