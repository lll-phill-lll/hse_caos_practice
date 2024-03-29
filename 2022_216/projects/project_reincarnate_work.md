# Stress-free caos course

Игорь решает дз по акосу, но из-за непонятного условия у него могут сдавать нервы, из-за чего он может просто разбить свой ноутбук, выбросив его в окно. Через некоторое время успокоится и взять другой ноут (у него их много). Все бы ничего, но хочется не терять процесс выполнения программ, а восстанавливай их на новом устройстве.

## Чуть конкретнее

В идеале хочется, чтобы любой процесс мог быть восстановлен на другой машине с одинаковыми характеристиками. Но допустим, что держать дополнительный сервер для этого дома не хочется, а программы для курса не сильно взаимодействуют с системой. В качестве упрощения, можно написать библиотеку, которая бы реализовывала большую часть функционала для программ на с (мы же здесь пишем на си). Сделайте библиотеку разделяемой (с динамической линковкой).

В общем, хочется уметь сохранять стек работы программы, все созданные переменные в куче, инструкцию, на котором завершилось выполнение процесса, а файловая система у Игоря и так распределённая.

Разверните такой сервис. Считайте что на компе у Игоря есть спидометр, который может определить, когда нужно сохранять прогресс и отправлять процессы на сервер с их состоянием. Поэтому по сигналу клиенту нужно сохранять всю информацию про процессы, а при новом подключении восстанавливать и запускать все процессы с последнего сохраненного места.

## Клиент

Клиент работает как демон (daemon).

При запросе клиенту нужно узнать все текущие процессы и попытаться обработать каждый, до которого у него есть доступ. Если писать библиотеку, то можно отправлять процессам SIGINT, и все кто использует библиотеку успеют сохранить свое состояние перед завершением. Затем клиент собирает все данные и отправляет их на сервер, а затем завершается сам. Будьте осторожны при тестировании.

Информация с состояниями процессов на сервер просто хранится. После настройки новый ноут идет на сервер и просит всю эту информацию. После чего восстанавливает выполнение для процессов которые удалось сохранить. При этом из-за специфики задачи данные могли обработаться не до конца, некорректно или быть переданы злоумышленником, поэтому нужно развернуть окружение и запустить их в нем. Если процесс работал с какими-то файлами, то их содержимое также нужно восстановить в безопасном окружении. В качестве окружения можно просто развернуть контейнер.

Отправка всех данных на сервер должна производится как можно скорее, поэтому используйте потоки и несколько подключений.

Все переменные окружения нужно скопировать с старого ноутбука.

Будьте внимательны, что пользователь может делать со своей файловой системой что угодно и удалить все бинарники во время выполнения программы но до синхронизации с сервером. Даже исходники самой библиотеки. 

## Библиотека

По итогу библиотека должна поддерживать работу с кучей, корутины, и fork с каналами (непрочитанные данные можно потерять), чтение файлов и запись. Можно использовать привычные функции, но при этом нужно уметь восстанавливать состояние.

Содержимое файлов будут получены через распределенную файловую систему, но путь к ним нужно передавать, и копировать в окружение. Восстановить все состояния корутин, процессы, открыть файлы и сдвинуть коретки до нужного места.

Чтобы понимать запускается ли процесс первый раз, или его нужно сначала восстановить, используется переменные окружения. Новый ноут может полететь в окно еще раз, поэтому нужно также обрабатывать все процессы в окружении и новые запущенные без него.

## Сервер

Логика сервера для работы с данными простая - принимать, хранить и отправлять. Но есть также некоторые дополнительные требования, ведь мы не хотим чтобы клиент получил от нашего лица вредоносные программы, даже если он должен запускать их в безопасном окружении, мы не можем это проконтролировать. 

### Авторизация

У клиента может легко поменяться ip, поэтому мы должны сделать авторизацию. Пусть она будет по rsa ключам. У сервера изначально будет публичный ключ клиента (неважно как полученная). Сгенерируйте для тестирования отдельные пары ключей, а не используйте существующие.

Саму регистрацию можно сделать через login-password, но использовать их не будем.

При регистрации выдавайте ключевую фразу, закодированную публичным ключом клиента. Эта фраза и rsa ключи будут сохранены через распределенную файловую систему, поэтому при новом подключении просто закодируйте фразу публичным ключем сервера (он этот ключ дает свободно) и отправьте ему. При этом сервер ответит новой фразой, которую нужно использовать в дальнейшем. Фразы можно генерировать рандомно.

Причем все сообщения между клиентом и сервером должны шифроваться rsa ключами (разве что кроме самих публичных ключей). Можно использовать библиотеку OpenSSL.

### Управление сервером

При этом админ сервера не должен получить доступ к клиентским данным. И есть еще супер админ, чьи моральные ценности непоколебимы, и все процессы сервера должны запускаться только от его uid - super_uid. Запуск от другого uid должно падать. С пользователем root можно совсем не работать. Все нужные ключи чтобы дешифровать данные можно хранить в отдельном файле, и при работе с ним, с правильными доступами. Админ сервера же - отдельный пользователь и ему можно выдавать только зашифрованные данные, и обезличенную статистику (количество пользователей, сколько на каждого тратится места на диске, как долго работает, история обращения к серверу). Сделайте это через запросы к серверу или сигналы с сохранением в общедоступный файл. Также можно отправлять сигналы для сохранения полной статистики в файл, доступ к которому есть только у super_uid. Также нужна программы которая только для запуска от super_uid может расшифровать сохраненные клиентские данные. 

# По вопросам что здесь происходит

Если хотите, спрашивайте в общей группе, уточнить написанное условие - @KseniaPetrenko.
