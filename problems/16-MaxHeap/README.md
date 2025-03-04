B\*. Приоритетная очередь с удалением — База 2023 1 сем. Задание 2. Алгоритмы — Яндекс.КонтестВаше участие в соревновании завершено. Вы можете дорешивать задачи и отправлять решения вне соревнования

# B\*. Приоритетная очередь с удалением

| Ограничение времени | 1.5 секунд |
| --- | --- |
| Ограничение памяти | 64Mb |
| Ввод | стандартный ввод или input.txt |
| Вывод | стандартный вывод или output.txt |

Требуется реализовать приоритетную очередь с помощью бинарной пирамиды, поддерживающую три операции: добавить элемент, извлечь
максимальный элемент и удалить заданный элемент. При просеивании нельзя совершать лишние перемещения (например, в случае равенства
элементов). Если при просеивании вниз, рассматриваемый элемент можно перемещать как влево вниз, так и вправо вниз, то следует
выбрать направление влево.

## Формат ввода

В первой строке вводятся два числа — максимальный размер приоритетной очереди N и количество запросов M, (1 ≤ M,N ≤ 105). Далее идут M строк, в каждой строке — по одному запросу. Первое число в запросе задает его тип, остальные числа (если есть)
— параметры запроса. Тип 1 — извлечь максимальный (без параметров). Тип 2 — добавить данный элемент в очередь. Запрос имеет
один параметр — число из диапазона \[-109;109\]. Тип 3 — удалить элемент по индексу (индексы нумеруются с единицы).

## Формат вывода

В ответ на запрос типа 1 следует вывести: Если извлекать было нечего (очередь пуста), то -1. Иначе — два числа, первое — индекс
конечного положения элемента после его просеивания (если удален последний элемент и просеивать нечего то вывести 0), второе
— значение извлеченного элемента.

В ответ на запрос типа 2 следует вывести: Если добавить нельзя (нет места, т.к. в очередь уже N элементов), то -1. Иначе —
индекс добавленного элемента.

В ответ на запрос типа 3 следует вывести: Если элемента с таким индексом нет и удаление невозможно, то -1. Иначе — значение
удаленного элемента.

После выполнения всех запросов требуется вывести пирамиду в её конечном состоянии

## Пример

| Ввод Скопировать ввод | Вывод Скопировать вывод |
| --- | --- |
| `4 10 1 2 9 2 4 2 9 2 9 2 7 1 3 4 2 1 3 3 ` | `-1 1 2 3 2 -1 2 9 -1 4 9 9 4 1  ` |
