K\*. Как собрать друзей по-быстрому — База 2023 3 сем. Задание 1. RMQ/RSQ — Яндекс.КонтестВаше участие в соревновании завершено. Вы можете дорешивать задачи и отправлять решения вне соревнования

# K\*. Как собрать друзей по-быстрому

| Ограничение времени | 2 секунды |
| --- | --- |
| Ограничение памяти | 29Mb |
| Ввод | стандартный ввод или input.txt |
| Вывод | стандартный вывод или output.txt |

Честно говоря, я не то чтобы заболела, просто появилась возможность покататься на кроватке, ну и грех было не воспользоваться.

Собирать гостей — большая наука. Одного радушия порой маловато, требуется выдумка и недюжинная смелость. Поэтому Нюша берётся
за дело: притворившись больной, она просит друзей навестить её. Реализуйте структуру данных, которая поддерживает множество
S целых чисел порядковых номеров смешариков (это число показывает, каким смешарик пришел на фан-встречу: пятым, десятым, пятидесятым…), с которым разрешается производить следующие операции:

- add(i) — добавить в множество гостей S число i  — настроение пришедшего к Нюше смешарика (если оно там уже есть, то множество не меняется);
- sum(l, r) — вывести сумму всех элементов x из S, которые удовлетворяют неравенству l ≤ x ≤ r. Нюша хочет знать как зависит настроение смешарика от времени, от его порядковой позиции в списке гостей.

## Формат ввода

Исходно множество S пусто. Первая строка входного файла содержит n — количество операций (1 ≤ n ≤ 3 ⋅ 105). Следующие n строк содержат операции. Каждая операция имеет вид либо «+ i», либо «? l r». Операция «+ i» задает запрос add(i). Операция «? l r» задает запрос sum(l, r).

Во всех запросах и операциях добавления параметры лежат в интервале от 0 до 109.

## Формат вывода

Для каждого запроса выведите одно число — ответ на запрос.

## Пример

| Ввод Скопировать ввод | Вывод Скопировать вывод |
| --- | --- |
| `6 + 1 + 3 + 3 ? 2 4 + 4 ? 2 4 ` | `3 7 ` |
