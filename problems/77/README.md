O. Магнитные подушки — База 2024 2 сем. Задание 2. Алгоритмы — Яндекс.Контест

# O. Магнитные подушки

| Ограничение времени | 2 секунды                        |
| ------------------- | -------------------------------- |
| Ограничение памяти  | 129Mb                            |
| Ввод                | стандартный ввод или input.txt   |
| Вывод               | стандартный вывод или output.txt |

Город будущего застроен небоскребами, для передвижения между которыми и парковки транспорта многие тройки небоскребов соединены
треугольной подушкой из однополярных магнитов. Каждая подушка соединяет ровно 3 небоскреба и вид сверху на нее представляет
собой треугольник, с вершинами в небоскребах. Это позволяет беспрепятственно передвигаться между соответствующими небоскребами.
Подушки можно делать на разных уровнях, поэтому один небоскреб может быть соединен различными подушками с парами других, причем
два небоскреба могут соединять несколько подушек (как с разными третьими небоскребами, так и с одинаковым). Например, возможны
две подушки на разных уровнях между небоскребами 1, 2 и 3, и, кроме того, магнитная подушка между 1, 2, 5.

Система магнитных подушек организована так, что с их помощью можно добираться от одного небоскреба, до любого другого в этом
городе (с одной подушки на другую можно перемещаться внутри небоскреба), но поддержание каждой из них требует больших затрат
энергии.

Требуется написать программу, которая определит, какие из магнитных подушек нельзя удалять из подушечной системы города, так
как удаление даже только этой подушки может привести к тому, что найдутся небоскребы из которых теперь нельзя добраться до
некоторых других небоскребов, и жителям станет очень грустно.

## Формат ввода

В первой строке входного файла находятся числа N и M — количество небоскребов в городе и количество работающих магнитных подушек соответственно (3 ≤ N ≤ 100000, 1 ≤ M ≤ 100000).

В каждой из следующих M строк через пробел записаны три числа — номера небоскребов, соединенных подушкой. Небоскребы пронумерованы от 1 до N.

Гарантируется, что имеющиеся воздушные подушки позволяют перемещаться от одного небоскреба до любого другого.

## Формат вывода

Выведите в выходной файл сначала количество тех магнитных подушек, отключение которых невозможно без нарушения сообщения в
городе, а потом их номера.

Нумерация должна соответствовать тому порядку, в котором подушки перечислены во входном файле. Нумерация начинается с единицы.

### Пример 1

| Ввод Скопировать ввод | Вывод Скопировать вывод |
| --------------------- | ----------------------- |
| `3 1 1 2 3 `          | `1 1  `                 |

### Пример 2

| Ввод Скопировать ввод | Вывод Скопировать вывод |
| --------------------- | ----------------------- |
| `3 2 1 2 3 3 2 1 `    | `0 `                    |

### Пример 3

| Ввод Скопировать ввод          | Вывод Скопировать вывод |
| ------------------------------ | ----------------------- |
| `5 4 1 2 3 2 4 3 1 2 4 3 5 1 ` | `1 4  `                 |
