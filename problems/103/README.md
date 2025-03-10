P. Химия — База 2024 2 сем. Задание 3. Алгоритмы — Яндекс.КонтестВаше участие в соревновании завершено. Вы можете дорешивать задачи и отправлять решения вне соревнования

# P. Химия

| Ограничение времени | 0.5 секунд |
| --- | --- |
| Ограничение памяти | 16Mb |
| Ввод | стандартный ввод или input.txt |
| Вывод | стандартный вывод или output.txt |

Вася и Сережа играют в следующую игру. В некоторых клетках клетчатого листка Сережа рисует один из символов H, O, N или C, после чего Вася должен провести между некоторыми находящимися в соседних клетках символами линии так, чтобы получилось корректное
изображение химической молекулы. К сожалению, Сережа любит рисовать много символов, и Вася не может сразу определить, возможно
ли вообще нарисовать линии нужным способом. Помогите ему написать программу, которая даст ответ на этот вопрос.

В этой задаче проведенные между символами химических элементов линии будем считать корректным изображением молекулы, если
они удовлетворяют следующим условиям:

- каждая линия соединяет символы, нарисованные в соседних (по стороне) клетках;
- между каждой парой символов проведено не более одной линии;
- от каждого элемента отходит ровно столько линий, какова валентность этого элемента (1 для H, 2 для O, 3 для N, 4 для C);
- пустые клетки ни с чем не соединены;
- хотя бы в одной клетке нарисован какой-то символ.

## Формат ввода

Первая строка входного файла содержит два натуральных числа n и m (1 ≤ n, m ≤ 50) — размеры листочка, на котором рисует Сережа.

Далее следуют n строк по m символов в каждой, задающих конфигурацию химических элементов, которую нарисовал Сережа; пустые клетки задаются символом
«.».

## Формат вывода

В выходной файл выведите одно слово Valid, если линии провести требуемым образом можно, и Invalid, если нельзя.

### Пример 1

| Ввод Скопировать ввод | Вывод Скопировать вывод |
| --- | --- |
| `3 4 HOH. NCOH OO.. ` | `Valid ` |

### Пример 2

| Ввод Скопировать ввод | Вывод Скопировать вывод |
| --- | --- |
| `3 4 HOH. NCOH OONH ` | `Invalid ` |
