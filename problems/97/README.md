J. Еще раз Дейкстра — База 2024 2 сем. Задание 3. Алгоритмы — Яндекс.КонтестВаше участие в соревновании завершено. Вы можете дорешивать задачи и отправлять решения вне соревнования

# J. Еще раз Дейкстра

| Ограничение времени | 1 секунда |
| --- | --- |
| Ограничение памяти | 128Mb |
| Ввод | стандартный ввод или input.txt |
| Вывод | стандартный вывод или output.txt |

Дан ориентированный граф, рёбрам которого приписаны некоторые неотрицательные веса (длины). Найти длину кратчайшего пути из
вершины s в вершину t.

## Формат ввода

В первой строке заданы три числа: число вершин в графе N (N ≤ 2 ⋅ 103), номера вершин s и t. Далее идёт матрица смежности графа, то есть N строк, в каждой из которых записано N чисел. j-е число в i-й строке матрицы смежности задает длину ребра, ведущего из i-й вершину в j-ю. Длины могут принимать любые значения от 0 до 106, число -1 означает отсутствие соответствующего ребра. Гарантируется, что на главной диагонали матрицы стоят нули.

## Формат вывода

Выведите одно число — минимальную длину пути. Если пути не существует, выведите -1.

## Пример

| Ввод Скопировать ввод | Вывод Скопировать вывод |
| --- | --- |
| `3 1 2 0 -1 3 7 0 1 2 -1 0 ` | `-1 ` |
