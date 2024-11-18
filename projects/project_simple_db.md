# Проект: Упрощенная База Данных (SimpleDB)

## Описание проекта
**SimpleDB** — это минималистичная реляционная база данных, написанная на C/С++, поддерживающая базовые операции: создание таблиц, вставка, удаление, обновление и поиск записей. 

## Требуемый функционал
1. **Создание таблиц**
   - Возможность создания таблиц с именем и набором столбцов (для простоты можно поддерживать только `INT` и `TEXT`).
   - Каждая таблица хранится в отдельном файле с записями и метаданными.

2. **CRUD-операции**
   - **Insert:** Добавление новой записи в таблицу.
   - **Select:** Поиск и вывод записей с фильтрацией по значению столбца.
   - **Update:** Обновление значений в записи по условию.
   - **Delete:** Удаление записи по условию.

3. **Индексация**
   - Поддержка индексов на целочисленных столбцах для ускорения поиска.
   - Индексы хранятся отдельно и обновляются при изменении данных.

4. **Интерфейс командной строки с SQL-подобным синтаксисом**
   - Простые команды для управления базой данных, например:
     ```sql
     CREATE TABLE users (id INT, name TEXT);
     INSERT INTO users (id, name) VALUES (1, 'Admin');
     SELECT * FROM users WHERE id = 1;
     ```

5. **Сериализация данных**
   - Хранение данных в бинарных файлах для ускоренного доступа и экономии места.
   - Записи сериализуются и десериализуются при чтении и записи в файл.

6. **Журналирование транзакций (опционально)**
   - Журналирование основных операций для восстановления данных в случае сбоя.

## Пример использования
```bash
# Запуск SimpleDB
./simpledb

# Создание таблицы
simpledb> CREATE TABLE users (id INT, name TEXT);

# Добавление записи
simpledb> INSERT INTO users (id, name) VALUES (1, 'Admin');

# Поиск записи
simpledb> SELECT * FROM users WHERE id = 1;

# Обновление записи
simpledb> UPDATE users SET name = 'Super Admin' WHERE id = 1;

# Удаление записи
simpledb> DELETE FROM users WHERE id = 1;
```

## Definition of Done
1-5 пункты из требуемого функционала реализованы и работают

## Полезные ссылки
[Как создать свою СУБД с нуля и не сойти с ума](https://habr.com/ru/articles/709234/)
