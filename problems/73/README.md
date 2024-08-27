 K. Разноцветный граф — База 2024 2 сем. Задание 2\. Алгоритмы — Яндекс.Контест



K. Разноцветный граф
====================




| Ограничение времени | 1\.5 секунд |
| --- | --- |
| Ограничение памяти | 256Mb |
| Ввод | стандартный ввод или input.txt |
| Вывод | стандартный вывод или output.txt |





Даны N точек, занумерованных числами ![](data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAGYAAAAdCAYAAABYOhlgAAADKklEQVR4Xu2YP0h6URTHTVChhDCqoT+LODhEDQ4t2V5NgUtrY0tN0S4ELgUuYUuCrjm1OLnV1GKINTSIBlFiQUsWcX6/c3v38Tze+7TeVd7v/d4HLj6/57zDvef7fN73POBiSzxUcLEHrjE2xTXGprjG2BShMV9fX3B2dgazs7Pg8QhT+qJcLsPBwQEsLS3B2NgY+P1+CIfDsLOzA41Gg6b/82Cv+PB6vVAsFmmKjjGXj454x7e/YLHFxUWIx+PCE34CnouGnJ6ewuPjI7RaLcjn8xAKhWBychKq1So9xRHwvk1NTfW8AGX97VIjkQicn5+zYxXGHB8fUxmy2SyLbWxs0JAjwLWtra2xz5WVFfj8/KQpOrL+dqkfHx/6sQpj6vU6leHp6YnFgsEgDTkCXFuz2YT5+Xl2vL+/T1N0ZP0VqxpWjZHx+vrK6k5PT9OQI+A9u7q6Ap/PByMjI3BxcUGyvpH1V6xqDMqYUqnE6m5vb9OQIzD27OjoiH2fmJiAWq1myPpG1l+xqjEoYxKJBLuN3d/f05AjoD3b3Nxk2vLycsdfBUJzOWJVYxDGFAoFVjOXy9GQY6A9w1s3Piagvre31xGjuRyxqqHamMvLS7Z9TqVSNOQoRD27vr6GQCDAYnhxckS5iFjVUGlMpVJhzy/JZJKGHIesZycnJyw2Pj6u38ZluWJVQ5UxuGXGreP/YApi1rOtrS0Wj8Vi8P7+Ls0VqxoqjHl5eYGFhQWhKVZr2xWzdb29vUE0GmU5+GpKlitWNXoZgw+KdJdhBK+I1dVVoSkIrd2rnpHn52fTJ2qOyrx+50fXRbm5uYHR0VHT/opVDbMTb29v2UvJ9fV1GtLBbTGvIRucfupx7u7uWC5uQ81QmfeT+cl6ZgRfEtMeGOlSaePo4Dw8PMDMzAzMzc1JrzR6rmhw+qnHwReD+OZ7d3eXhjpQmdfP/OjajOsTgQ/Yshyx+gPS6TS0220q/xrV9VQzrPlZNubw8JBKllBdTzXDmp8lY/DnnclkqPxrVNdTzTDnZ8kYvHpk99vfoLqeaoY5P0vGuAwO1xib4hpjU1xjbIprjE35A+w/1ArsW/DXAAAAAElFTkSuQmCC). От каждой точки с меньшим номером к каждой точке с большим номером ведет стрелка красного или синего цвета. Раскраска стрелок
 называется однотонной, если нет двух таких точек A и B, что от A до B можно добраться как только по красным стрелкам, так и только по синим.
 

Ваша задача — по заданной раскраске определить, является ли она однотонной.



Формат ввода
------------



В первой строке входных данных содержится единственное число N (3 ≤ N ≤ 5000\).
 

В следующих N \- 1 строках идет описание раскраски. В (i\+1\)\-й строке записано (N \- i) символов R (красный) или B (синий), соответствующих цвету стрелок, выходящих из точки i и входящих в точки (i\+1\), (i\+2\), …, N соответственно.
 



Формат вывода
-------------



Выведите YES, если приведенная раскраска является однотонной, и NO в противном случае.
 


### Пример 1




| Ввод Скопировать ввод | Вывод Скопировать вывод |
| --- | --- |
| ``` 3 RB R  ``` | ``` NO  ``` |


### Пример 2




| Ввод Скопировать ввод | Вывод Скопировать вывод |
| --- | --- |
| ``` 3 RR R  ``` | ``` YES  ``` |


Примечания
----------



Используйте быстрый ввод


