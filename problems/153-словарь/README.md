E. Словарь — База 2024 2 сем. Задание 2. C++ — Яндекс.Контест

# E. Словарь

| Ограничение времени | 1 секунда |
| --- | --- |
| Ограничение памяти | 256Mb |
| Ввод | стандартный ввод или input.txt |
| Вывод | стандартный вывод или output.txt |

Вам дан словарь, состоящий из пар слов. Каждое слово является синонимом к парному ему слову. Все слова в словаре различны.
Для каждого данного слова определите его синоним.

Для решения данной задачи используйте std::unordered_map

## Формат ввода

Программа получает на вход количество пар синонимов N (0 ≤ N ≤ 105). Далее следует N строк, каждая строка содержит ровно два слова-синонима.

Затем идет число Q (1 ≤ Q ≤ 105) — количество запросов к словарю. Далее на каждой следующей из Q строк идет слово, к которому надо вывести синоним.

## Формат вывода

Программа должна вывести синонимы к данным слову на отдельных строках.

## Пример

| Ввод Скопировать ввод | Вывод Скопировать вывод |
| --- | --- |
| `3 car plane mouse cat base stream 3 plane stream base ` | `car base stream ` |

## Примечания

Подумайте, почему бы не использовать std::map. Используйте быстрый ввод.

[Скачать условие задачи](https://contest.yandex.ru/contest/61173/download/E/)
