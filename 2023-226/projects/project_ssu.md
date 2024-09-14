# SSU -- Sock-Some-UDP

---

Проект свободен: нет

Участники: Жамойдин Тимофей

Предложен студентами: да

Ссылка на репозиторий: https://github.com/h0tmi/sock-some-udp

---
A simple streaming udp gateway socket utility that can handle multiple streams and manipulate received data. This project is a part of my CAOS university course. I've tried to learn some networking technologies, c++ cli applications development and unix systems during development.
***
## Project inspiration
During the develompent of applications it's easier to have proxy shell between your UI and backend. The goal of the project is to create this layer and separate frontend and backend development providing a relaible service with handlers that backend and frintend can use.
***
## Interface
``` $ ssu -h ```

Usage: ssu sockgw

```-v``` -- verbose Output extra verbose information

```-L``` -- logging-level=ARG Logging Level

```-c``` -- client Start sample client

```-u``` -- udptarget Start a UDP target server

```-g``` -- gateway [ARG] Gateway Stream Socket Port Number

```-t``` -- target [ARG] Target UDP Socket Port Number

***
## Exaples of usage
**TBD**
