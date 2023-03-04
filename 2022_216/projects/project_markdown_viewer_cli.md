# Markdown Viewer in CLI

---

Проект свободен: нет

Участники: Колчин Андрей

Предложен студентами: да

Ссылка на репозиторий: https://git.sr.ht/~kaathewise/hare-regex

---

## Task

Create a markdown viewer, which would render markdown documents
leveraging the ANSI escape codes and UTF-8 symbol formatting.


## Number of Developers

One.


## Functionality


### Markdown

 - Normalize paragraphs of text.

 - Style text emphasis and links.

 - Render headers, including visual flair for high-level headers.

 - Render block quotes, horizontal rules, lists, and task lists with
   tables from GFM.

 - Style code blocks with syntax highlighting.


### Config

The program should have a configuration file, which would allow to
specify colors, text width, number of spaces between sentences, use of
non-standard symbols (e. g. tick emojis in task lists), header styles,
and more.


### VI

Navigation inside the viewer should support vi-like movement.
Potentially, a vi-like console can be added to change the main config
options on the fly.
