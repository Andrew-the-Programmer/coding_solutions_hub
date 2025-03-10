A. Тетрадка — База 2023 1 сем. Задание 1. C++ — Яндекс.КонтестВаше участие в соревновании завершено. Вы можете дорешивать задачи и отправлять решения вне соревнования

# A. Тетрадка

| Ограничение времени | 1 секунда |
| --- | --- |
| Ограничение памяти | 256Mb |
| Ввод | стандартный ввод или input.txt |
| Вывод | стандартный вывод или output.txt |

Проектная работа Виталика по компьютерному зрению заключается в распознавании типа тетрадки по небольшому ее участку (в клетку,
в линейку, в вертикальную линейку). Однако времени обучать нейросеть у Виталика нет, поэтому он попросил вас помочь ему написать
программу на C++, которая бы делала это без привлечения искусственного интеллекта (почему вы согласились на это, и почему
эта задача обязательна, легенда умалчивает).

Часть тетрадки представляет собой двумерную таблицу из нулей и единиц, где единица — закрашенный участок, а нуль — незакрашенный. Вертикальной линией считается столбец, в котором стоят только единицы, горизонтальной — строка, второй стоят только единицы. Гарантируется, что тетрадь изначально пустая, то есть единица обязательно является частью
какой-то линии.

Тетрадь в горизонтальную линейку состоит только из горизонтальных линий, в вертикальную линейку — только из вертикальных линий, в клетку — из линий обоих типов. Причем расстояния между всеми параллельными линиями одинаковы (клетки - обязательно квадраты), и между
ними обязательно есть пустоты (не могут располагаться вплотную).

По заданному участку выведите тип тетради, если его возможно однозначно определить.

## Формат ввода

В первой строке даны целые числа n и m (1 ≤ n, m ≤ 1 000) — количество строк и столбцов в видимом участке. Далле следует n строк по m целых чисел ai, j (0 ≤ ai,j ≤ 1) — видимый участок тетради.

## Формат вывода

В качестве ответа выведите:

«Square», если тетрадка в клетку; «Line», если тетрадка в линейку; «Vertical line», если тетрадка в вертикальную линейку;
«?», если невозможно однозначно определить, к какому типу относится данная тетрадь.

### Пример 1

| Ввод Скопировать ввод | Вывод Скопировать вывод |
| --- | --- |
| `3 5 00100 11111 00100 ` | `Square ` |

### Пример 2

| Ввод Скопировать ввод | Вывод Скопировать вывод |
| --- | --- |
| `4 5 11111 00000 11111 00000 ` | `Line ` |

### Пример 3

| Ввод Скопировать ввод | Вывод Скопировать вывод |
| --- | --- |
| `5 5 00000 00000 11111 00000 00000 ` | `? ` |
