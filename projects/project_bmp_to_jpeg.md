# Проект "Конвертер BMP изображений в JPEG"

---
Проект свободен: нет

Участники: Гончаров Михаил, Кирилл Векшин, Яна Либина

Предложен студентами: да

Ссылка на репозиторий:
https://github.com/yalibina/bmp_to_jpeg/tree/main

---

##### Задача

В наше время средний объем файлов, ежедневно проходящих через электронные девайсы, всё время растет, в связи с чем возникают такие проблемы, как нехватка интернет трафика и памяти на устройствах, низкая скорость загрузки файлов и прочие. Решений и оптимизаций на эту тему существует много, но этот проект заостряет внимание на форматах изображений BMP и JPEG. BMP формат позволяет хранить изображение в "сыром" виде без сжатия, из чего, с одной стороны, следует превосходное качество изображения, с другой стороны, его большой размер. JPEG позволяет хранить изображение в сжатом виде с настраиваемой степенью потерий качества, засчет нетривиальных математических алгоритмов. В рамках этого проекта будет реализована возможность конвертировать изображение из BMP в JPEG, тем самым сжимая его. 

##### Основная цель
Разобраться, как устроены файлы формата BMP и JPEG изнутри, изучить алгоритмы сжатия и шифрования информации об изображении, реализовать их в виде конвертации BMP в JPEG.

##### Функционал

В консоль программе подается строка "read_path save_path". Программа считывает изображение, лежащее по пути read_path, и сохраняет сжатый результат по пути save_path. Параметр -q n задает пользовательскую степень сжатия, n - целое неотрицательное число. 

Внутри программы будут реализованы:
1. Считывание BMP файлов и запись JPEG файлов
2. Алгоритм сжатия "сырых" изображений (в формате массива RGB-элементов)

##### Стек технологий
1. С++