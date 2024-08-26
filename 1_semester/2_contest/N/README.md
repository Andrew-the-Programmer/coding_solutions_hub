 N. MinMidMax — База 2023 1 сем. Задание 2\. Алгоритмы — Яндекс.КонтестВаше участие в соревновании завершено. Вы можете дорешивать задачи и отправлять решения вне соревнования



N. MinMidMax
============




| Ограничение времени | 1 секунда |
| --- | --- |
| Ограничение памяти | 64Mb |
| Ввод | стандартный ввод или input.txt |
| Вывод | стандартный вывод или output.txt |





Реализуйте структуру данных для хранения различных целых чисел, которая поддерживает 4 операции: 
 * «add x\> — Добавить в структуру элемент x (1 ≤ x ≤ 109);
* «min» — Извлечь из структуры минимальный элемент;
* «max» — Извлечь из структуры максимальный элемент;
* «mid» — Извлечь из структуры медианный элемент (в случае чётности размера структуры следует вывести левый медианный элемент, то есть
 если в структуре хранится n элементов a0 ≤ a1 ≤ … ≤ an\-1, то процедура извлекает элемент ![](data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACgAAAAgCAYAAABgrToAAAAB+0lEQVR4Xu2VTcsBURiGJ1mIJJSFYs2CYikpsmPjB9j5Abay8hP8AlmRwpYsKMlGpIidhWJj6ysf99ucojnHzDvv2xjNwlWnxnM/z3EZ4+CgcTi2oDW+gkr5CirlRbDf7yOdTsPlckGv18NutyORSGAwGLCtH+FFkOM4hEIhzGYzHA4HDIdD+P1+Itvtdtl21REVXCwWVG00GpF6JBKh6p/gRVCMy+VCBE0mExspolKpwGazsWWKF8FqtYpYLAan0wmdTkfEhOudeL1e2T2pNJ/Pk4FkMon5fI7z+fzMpAQf9UKhQO5wLpdjWyQ5nU6iewqhUqvVSga2262wTJAS5OHrvV6PfCiz2czGvyK15wMqtVgsZGC9XgvLWK1WsoL3+/15zcOfAOVyGaVSiVr1el04KrnnAyrNZrNkIB6Pk7txPB4xmUwQDodlBcWu/4JcP5Ver1cUi0X4fD4YjUbydUWjUbTb7acguyFbF+uRgp0VQzrRCIoEN5sNeSzetVqtFvsWygQ/gaqCjUYDHo8HBoMBgUAAnU6HbZFFVUH+4W82m+RArtVqcDgcbIssqgoK2e12CAaDbFmWjwjebjfyI5hOp2wki+qC+/0emUwG4/GYjf6EqoL8MZRKpbBcLsnr3w5kKf4/8Q/cbjf1b6E5wXfwFVTKV1Apmhf8Ad/Kwko2yStZAAAAAElFTkSuQmCC)).





Формат ввода
------------



В первой строке входных данных записано единственное число M (1 ≤ M ≤ 200000\) — количество команд. В следующих М строках дано по одной команде из тех, что идут выше.
 


Формат вывода
-------------



На каждый запрос «min», «max» и «mid» выведите значение извлечённого элемента.


Пример
------




| Ввод Скопировать ввод | Вывод Скопировать вывод |
| --- | --- |
| ``` 6 add 3 add 1 add 2 min mid mid  ``` | ``` 1 2 3  ``` |


