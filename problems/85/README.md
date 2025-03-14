W. Восстановление графа — База 2024 2 сем. Задание 2. Алгоритмы — Яндекс.Контест

# W. Восстановление графа

| Ограничение времени | 5 секунд |
| --- | --- |
| Ограничение памяти | 1Gb |
| Ввод | стандартный ввод или input.txt |
| Вывод | стандартный вывод или output.txt |

В Физтех-школе Прикладной Математики и Информатики студенты изучают теорию графов. К сожалению, студент Демид не очень хорош
в ней с математической точки зрения, но знает огромное множество алгоритмов в этой области. Поэтому многие теоремы он доказывает
результатами работы некоторого алгоритма и их последующей обработкой. Но однажды ему задали непосильную задачу, помочь решить
которую он просит вас. Перейдем к самой задаче.

Дан неориентированный связный граф без петель и кратных ребер на N вершинах, которые занумеровали от 1 до N. Затем на каждое ребро выписали сумму номеров вершин, которое оно соединяет, а изначальную нумерацию вершин стерли.

Для удобства работы с графом, вершины уже занумеровали от 1 до N каким-то образом, то есть формально надо найти такую перестановку p\[\], что если p\[i\] = k, то i-я вершина во входных данных имела номер k в исходном графе.

## Формат ввода

На первой строке дано два натуральных числа N, M (1 ≤ N, M ≤ 106) — количество вершин и ребер в графе. Далее на M строках идут описания ребер в виде трех чисел u, v, c (1 ≤ u, v ≤ N, u ≠ v, 3 ≤ c ≤ 2N - 1 ) — ребро между вершинами с номерами u, v с написанным на нем числом c.

## Формат вывода

Выведите массив из N чисел через пробел — искомая перестановка. Гарантируется, что ответ есть.

## Пример

| Ввод Скопировать ввод | Вывод Скопировать вывод |
| --- | --- |
| `4 5 2 4 3 3 4 5 3 1 7 1 2 5 2 3 4 ` | `4 1 3 2 ` |
