C. Очередная задача с ЕГЭ — База 2024 2 сем. Задание 2. Алгоритмы — Яндекс.Контест

# C. Очередная задача с ЕГЭ

| Ограничение времени | 1 секунда |
| --- | --- |
| Ограничение памяти | 32Mb |
| Ввод | стандартный ввод или input.txt |
| Вывод | стандартный вывод или output.txt |

Витя хочет придумать новую игру с числами. В этой игре от игроков требуется преобразовывать четырехзначные числа не содержащие
нулей при помощи следующего разрешенного набора действий:

1. Можно увеличить первую цифру числа на 1, если она не равна 9.
1. Можно уменьшить последнюю цифру на 1, если она не равна 1.
1. Можно циклически сдвинуть все цифры на одну вправо.
1. Можно циклически сдвинуть все цифры на одну влево.

Например, применяя эти правила к числу 1234 можно получить числа 2234, 1233, 4123 и 2341 соответственно. Точные правила игры
Витя пока не придумал, но пока его интересует вопрос, как получить из одного числа другое за минимальное количество операций.

## Формат ввода

Во входном файле содержится два различных четырехзначных числа, каждое из которых не содержит нулей.

## Формат вывода

В первой строке вывода должна быть длина оптимальной последовательности чисел, которая описана ниже.

На второй строке необходимо вывести последовательность четырехзначных чисел, не содержащих нулей. Последовательность должна
начинаться первым из данных чисел и заканчиваться вторым из данных чисел, каждое последующее число в последовательности должно
быть получено из предыдущего числа применением одного из правил. Количество чисел в последовательности должно быть минимально
возможным.

## Пример

| Ввод Скопировать ввод | Вывод Скопировать вывод |
| --- | --- |
| `1234 4321 ` | `6 1234 2234 3234 4323 4322 4321 ` |
