S. Двусвязная атака — База 2024 2 сем. Задание 2. Алгоритмы — Яндекс.Контест

# S. Двусвязная атака

| Ограничение времени | 1 секунда                        |
| ------------------- | -------------------------------- |
| Ограничение памяти  | 256Mb                            |
| Ввод                | стандартный ввод или input.txt   |
| Вывод               | стандартный вывод или output.txt |

Вселенная состоит из планет, между некоторыми есть подходящие для гиперпрыжков гипертоннели (они двусторонние). В ходе битвы
с Империей повстанцы выяснили, что Империя может уничтожать некоторые гипертоннели, например, взрывая внутри них астероиды,
от чьих обломков нельзя увернуться на таких скоростях.

Повстанцы знают, что в ходе их атаки Звезде Смерти хватит времени ровно на одно уничтожение гипертоннеля. Поэтому они хотят
построить некоторые гипертоннели, чтобы сеть осталась все еще связной после удара Звезды Смерти. Ваша задача — узнать, сколько их надо построить.

Учитывая то, что система гипертоннелей оптимальна, в ней нет бессмысленных кратных ребер и петель.

## Формат ввода

Первая строка содержит два числа n (3 ≤ n ≤ 5000) — количество планет и m (1 ≤ m ≤ 100000) — количество построенных гипертоннелей. Следующие m строк содержат два числа vi, ui (1 ≤ vi, ui ≤ n) — описание гипертоннелей.

## Формат вывода

Выведите минимальное количество гипертоннелей, которые нужно достроить, чтобы атака состоялась.

## Пример

| Ввод Скопировать ввод | Вывод Скопировать вывод |
| --------------------- | ----------------------- |
| `4 3 1 2 2 3 2 4 `    | `2 `                    |
