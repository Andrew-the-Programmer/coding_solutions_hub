D. Расстояния — База 2024 2 сем. Задание 1. Алгоритмы — Яндекс.КонтестВаше участие в соревновании завершено. Вы можете дорешивать задачи и отправлять решения вне соревнования

# D. Расстояния

| Ограничение времени | 0.1 секунда |
| --- | --- |
| Ограничение памяти | 8Mb |
| Ввод | стандартный ввод или input.txt |
| Вывод | стандартный вывод или output.txt |

Даны три точки A, B и C. Необходимо подсчитать расстояния от точки C до прямой, луча и отрезка, образованного точками A и B.

## Формат ввода

В первой строке входного файла даны два целых числа — координаты точки C. Во двух следующих строках в таком же формате заданы точки A и B (A ≠ B).

Все числа во входном файле по модулю не превосодят 10 000.

## Формат вывода

В первой строке выходного файла выведите одно вещественное число — расстояние от точки C до прямой. В следующих двух строках выведите соответственно расстояния до луча AB (A — начало луча) и до отрезка AB. Все числа выводить с точностью не менее 10-6. Луч строится по направлению от точки A к точке B.

## Пример

| Ввод Скопировать ввод | Вывод Скопировать вывод |
| --- | --- |
| `3 0 1 1 2 1 ` | `1.000000000 1.000000000 1.414213562 ` |
