H. Следующий (Splay) — База 2023 1 сем. Задание 2. Алгоритмы — Яндекс.КонтестВаше участие в соревновании завершено. Вы можете дорешивать задачи и отправлять решения вне соревнования

# H. Следующий (Splay)

| Ограничение времени | 1 секунда |
| --- | --- |
| Ограничение памяти | 64Mb |
| Ввод | стандартный ввод или input.txt |
| Вывод | стандартный вывод или output.txt |

Реализуйте структуру данных, которая поддерживает множество S целых чисел, с котором разрешается производить следующие операции:

- add(i) — добавить в множество S число i (если он там уже есть, то множество не меняется);
- next(i) — вывести минимальный элемент множества, не меньший i. Если искомый элемент в структуре отсутствует, необходимо вывести -1.

## Формат ввода

Исходно множество S пусто. Первая строка входного файла содержит n — количество операций (1≤ n≤ 300000). Следующие n строк содержат операции. Каждая операция имеет вид либо «+ i», либо «? i». Операция «? i» задает запрос next(i).

Если операция «+ i» идет во входном файле в начале или после другой операции «+», то она задает операцию add(i). Если же она идет после запроса «?», и результат этого запроса был y, то выполняется операция ![](data:image/png;base64,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).

Во всех запросах и операциях добавления параметры лежат в интервале от 0 до 109.

## Формат вывода

Для каждого запроса выведите одно число — ответ на запрос.

## Пример

| Ввод Скопировать ввод | Вывод Скопировать вывод |
| --- | --- |
| `6 + 1 + 3 + 3 ? 2 + 1 ? 4 ` | `3 4 ` |

## Примечания

Решайте задачу с помощью Splay-дерева
