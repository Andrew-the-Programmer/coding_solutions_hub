U. Звучное название — База 2024 3 сем. Задание 1. Строки — Яндекс.Контест

# U. Звучное название

| Ограничение времени | 3 секунды |
| --- | --- |
| Ограничение памяти | 1Gb |
| Ввод | стандартный ввод или input.txt |
| Вывод | стандартный вывод или output.txt |

— Бесподобно. Что это за блюдо?

— Это блюдо подают собакам на завтрак, Ваше Величество

Но кто обратит на это внимание на балу, если дать каждому блюду звучное название? Звучным названием считается строка, одинаково
читающаяся, как слева направо, так и справа налево.

Дан набор из N строк. Найдите среди них такие пары, которые при конкатенации дают палиндром. Более формально, найдите все пары (i, j) такие, что i ≠ j и строка si + sj является палиндромом.

Выведите все упорядоченные пары индексов (нумерация с единицы).

## Формат ввода

В первой строке дано целое число N (1 ≤ N ≤ 106) — количество строк.

Далее в N строках записано по одному слову. Длина каждого слова от 1 до 10. Слова состоят из маленьких букв английского алфавита.

## Формат вывода

В первой строке выведите число найденных пар P. Далее выведите P найденных упорядоченных пар индексов.

Выводить пары можно в произвольном порядке.

### Пример 1

| Ввод Скопировать ввод | Вывод Скопировать вывод |
| --- | --- |
| `4 a abbaa bba abb ` | `6 1 2 1 3 2 3 3 4 4 1 4 3 ` |

### Пример 2

| Ввод Скопировать ввод | Вывод Скопировать вывод |
| --- | --- |
| `4 pa lap palk pal ` | `4 1 2 2 4 3 2 4 2 ` |

### Пример 3

| Ввод Скопировать ввод | Вывод Скопировать вывод |
| --- | --- |
| `4 za az abwab bawba ` | `4 1 2 2 1 3 4 4 3 ` |

## Примечания

Генерация тестов (кроме примеров из условия):

Для генерации тестов использовался следующий алгоритм.

- Выбираются два числа N (1 ≤ n ≤ 1234567) и k (2 ≤ k ≤ 26).
- Выбираются k различных символов английского алфавита
- Генерируются N строк: сначала выбирается длина от 1 до 10 с равномерным распределением, затем генерируется строка из выбранных символов
  и длины
- Оставляем только уникальные строки (если их более 106, то 106 случайных)

Данная задача предлагалась в качестве второй по сложности во втором отборочном этапе в ШАД.

Язык
