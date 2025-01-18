
# Yet another git tutorial

Текстовый конспект пары. Он будет немного отличаться от рассказанного, потому что у меня есть чуть больше времени спокойно обдумать все. Но в целом идейно все остается таким же. 

Инструкции будут делиться на 3 группы: нужные для работы одному, для работы в команде и более прокаченные, но менее нужные. Соответственно они будут называться lvl1, lvl5, lvl100 по непонятным причинам.

Каждый из нас проходил путь боли, когда пишешь какой-то проект, он уже становится достаточно большим и тут в какой-то момент перестает работать. Изменений сделано много, как искать ошибку? Эх, вот бы можно было откатиться на последнюю работающую версию. Системы контроля версий [vcs](https://ru.wikipedia.org/wiki/%D0%A1%D0%B8%D1%81%D1%82%D0%B5%D0%BC%D0%B0_%D1%83%D0%BF%D1%80%D0%B0%D0%B2%D0%BB%D0%B5%D0%BD%D0%B8%D1%8F_%D0%B2%D0%B5%D1%80%D1%81%D0%B8%D1%8F%D0%BC%D0%B8) решают эту и многие другие проблемы. Поговорим про одну из самых популярных (как минимум в open source мира) - git.

# Git. lvl-1

**_Цель_**: хотим писать проект, сохранять его промежуточные состояния не боясь чего-то потерять. Хотим проект держать где-то удаленно, например, на гитхабе. Коммитим в одиночестве.
**_Ключевые слова_**:

1. `git init`
2. `git commit`
3. `git add`
4. 
5. `git status`
6. `git log`
7. `git push`
8. `git pull`
9. `git fetch`


Создаем простой проект. Создаем директорию `mkdir MegaOmegaProject` и переходим в нее `cd MegaOmegaProject`. Тут и будем писать наш код.

Смастерим файлик main.cpp:
```cpp
#include <iostream>

int main() {
	std::cout << "Hello, world!" << std::endl;
}
```

Написали пока немного, но уже переживаем, что можем что-то потерять. Гит, настало твое время. Делаем `git init`.

>[!IMPORTANT] Важная команда
>`git init` - создать git репозиторий в текущей директории. [Документация](https://git-scm.com/docs/git-init/ru)

Эта команда инициализирует гит. В директории появляется поддиректория `.git`, в которой и будет находиться вся магия.

```zsh
$ ls -a
.  ..  .git  main.cpp
```

Посмотрим состояние репозитория с помощью команды `git status`:
>[!IMPORTANT] Важная команда
>`git status` - показать текущее состояние репозитория. [Документация](https://git-scm.com/docs/git-status)

```bash
$ git status
On branch master

No commits yet

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        main.cpp

nothing added to commit but untracked files present (use "git add" to track)
```
Наш `main.cpp` помечен как untracked. Это значит, что гит за ним не следит.

>[!TIP]
>Иногда бывает полезно использовать `git status -uno`, который не показывает untracked файлы, если их много. 

Чтобы гит начал отслеживать изменения в этом файле, нужно добавить его в индекс. Или же сделать `git add main.cpp`

>[!IMPORTANT] Важная команда
>`git add` - добавить файл в индекс. Можно использовать по-разному. `git add filename` - добавить файл `filename`. `git add .` - добавить содержимое текущей директории. `git add *.cpp` - добавить только файлы с расширением .cpp. `git add *` - добавить все файлы. Добавлять нужно аккуратно, потому что можно случайно добавить лишние файлы. Чтобы этого избежать, можно добавить специальный `.gitignore` файл. В котором перечислить, какие файлы нужно игнорировать. Сам файл `.gitignore` нужно будет тоже закоммитить. [Документация git add](https://git-scm.com/docs/git-add/ru) [Документация .gitignore](https://git-scm.com/docs/gitignore)

Теперь `git status` выдает следующее:
```bash
$ git status
On branch master

No commits yet

Changes to be committed:
  (use "git rm --cached <file>..." to unstage)
        new file:   main.cpp
```
Теперь мы готовы сделать первый чекпоинт - сохранить текущее состояние нашего проекта. Для этого нужно выполнить `git commit`.

```bash
$ git commit
Author identity unknown

*** Please tell me who you are.

Run

  git config --global user.email "you@example.com"
  git config --global user.name "Your Name"

to set your account's default identity.
Omit --global to set the identity only in this repository.

fatal: empty ident name (for <mfilitov@caos-new-git.ru-central1.internal>) not allowed
```
О нет, ошибка. Гит не знает кто мы. А для того, чтобы сохранить состояние нужно указать имя и почту. Они ни на что серьезное не влияют, так что можно указывать любые. Однако, если хочется сохранить свое авторство, то лучше указать что-то настоящее. Выполним команды, которые просит git. 

>[!NOTE]
> `--global` означает, что настройка будет применена для всей системы. Если не указывать этот аргумент, то мы зададим автора коммитов только для заданного репозитория. Может быть удобно, если хочется в разные репозитории коммитить с разных аккаунтов.

Выполним:
```
$ git config --global user.email "lol@kek.com"
$ git config --global user.name "Misha"
```

И попробуем создать коммит еще раз `git commit`. 

О нет! Открылся текстовый редактор нано. Так мы далеко не уедем. Надо поменять еще одну настройку гита. Выходим из Nano, нажав `Ctrl + X` и просим гит, открывать какие-то более приличные редакторы кода. 
```
$ git config --global core.editor "nvim"
```

Попробуем в третий раз закоммитить `git commit`:
```bash

# Please enter the commit message for your changes. Lines starting
# with '#' will be ignored, and an empty message aborts the commit.
#
# On branch master
#
# Initial commit
#
# Changes to be committed:
#       new file:   main.cpp
#
```

Открылся nvim и нас просят ввести commit message. Сообщение коммита - какой-то небольшой кусочек текста, описывающий текущие изменения. Напишем "Initial commit" и закроем редактор.

```
[master (root-commit) 8950e8b] Initial commit
 1 file changed, 7 insertions(+)
 create mode 100644 main.cpp
```

Ура, успех. Мы сделали свой первый коммит.

> [!IMPORTANT] Важная команда
>`git commit` - Сохранить изменения в файлах, добавленных в индекс. [Документация](https://git-scm.com/docs/git-commit/ru)










# Git. lvl-5

# Git. lvl-100


