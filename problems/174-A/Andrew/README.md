 A\*. Копатыч и искусство легких касаний — База 2023 3 сем. Задание 1\. RMQ/RSQ — Яндекс.КонтестВаше участие в соревновании завершено. Вы можете дорешивать задачи и отправлять решения вне соревнования


A\*. Копатыч и искусство легких касаний
=======================================




| Ограничение времени | 1 секунда |
| --- | --- |
| Ограничение памяти | 16\.0 Мб |
| Ввод | стандартный ввод или input.txt |
| Вывод | стандартный вывод или output.txt |






*Если честно, то в жизни мне повезло лишь однажды: когда я встретил вас — моих друзей.*


За окном rain, на душе pain, а смешарики устраивают смотр ледяных скульптур! Правила конкурса следующие: статуи выставляются в ряд, каждый смешарик голосует за понравившиеся ему бюсты. После этого Копатыч, как единственный независимый судья (независимый, потому что проспал весь творческий процесс) пытается определить лучшую ледяную композицию.


По мнению медведя композицией может быть любой подотрезок из ряда скульптур (Копатыч сельский житель и плохо разбирается в искусстве). Также Копатыч верит в то, что лучшая композиция — композиция, у скульптур в которой суммарное количество голосов максимально.


Помогите Копатычу написать программу, которая по его запросу будет говорить суммарное количество голосов за ледяную композицию.




Формат ввода
------------




В первой строке вводится одно натуральное число NN (1≤N≤105)(1≤N≤105) — количество скульптур, выставленных в ряд.


Во второй строке вводятся NN чисел от 1 до 105105 — количество голосов у скульптур в ряду.


В третьей строке вводится одно натуральное число KK (1≤K≤3⋅104)(1≤K≤3⋅104) — количество запросов Копатыча.


В следующих KK строках вводится по два числа — номера левого и правого концов композиции (считается, что скульптуры нумеруются с единицы).




Формат вывода
-------------




Для каждого запроса выведите сумму чисел соответствующей композиции скульптур. Числа выводите в одну строку через пробел.




Пример
------





| Ввод Скопировать ввод | Вывод Скопировать вывод |
| --- | --- |
| ``` 5 4 4 8 7 8 2 1 2 1 3  ``` | ``` 8 16   ``` |



Примечания
----------




Сложность решения должна быть O(N\+K)O(N\+K).




Язык