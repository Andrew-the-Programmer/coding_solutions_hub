H. Внутри или нет? — База 2024 2 сем. Задание 1. Алгоритмы — Яндекс.КонтестВаше участие в соревновании завершено. Вы можете дорешивать задачи и отправлять решения вне соревнования

# H. Внутри или нет?

| Ограничение времени | 0.5 секунд |
| --- | --- |
| Ограничение памяти | 16Mb |
| Ввод | стандартный ввод или input.txt |
| Вывод | стандартный вывод или output.txt |

Проверьте, лежит ли точка внутри многоугольника.

## Формат ввода

В первой строке вводятся три целых числа – N (![](data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAKAAAAAcCAYAAADmx7QjAAAFWklEQVR4Xu2aWyilXxTAGQ2RCLnEUCSXUUrjPiRPeKBErvEw4UHCpFzmyYPbk9cJU/NsBhEeFA9ueRBySbk9DJOocQm5s/6t5b9P7PNd/c9xfPP/fnX6zt5rnc86a61vn7X2ZgU6OhbEip/Q0XlJ9ATUsSh6AupYFD0BdSyKUQKurq5CU1MTxMfHg7OzM9jZ2YG/vz9kZ2fDxMQEr/5iWFlZGV5v3ryBkZERXsXAY132shR3d3fw/ft38PHxUWTH79+/obS0FN69ewe2trZ0xTHOC6F1fSOPoJMcHBzg69evsLe3BycnJzA6OgqhoaEk+/btG/+RF4UllLu7u+iXYigJuDnBhyQ8PBwSExMVPQgrKyvg6uoKcXFxMD8/DxcXF3TFsZubG8n/Jn3EyCPopPb2dn4aZmdnSebn58eLns3GxgaUlZVBYWEhLxIFbUhLS6NrQkIC3Nzc8CoG5AKuFrX2BgYGQm9vL72XS0D8Hu/fvwcPDw84PDx8IsMxzoeFhRm+r9b1GUYeQSdtb2/z07QSoszJyYkXqWZubg5ycnIgKSkJBgcH4f7+nlcRBW348+cP+Pr60vva2lpexYBUwNXwXHuvr68N7+USsLu7m+QNDQ28iMB5lP/48YPGWtdniHuEY3h4mG6QlZXFixQzNjYGKSkpkJ6eDtPT07xYESyIMzMz8PbtW7C2toahoSFO6wGpgCvBFPYy5BIwLy+P5Pg3hcAyCOWoh2hdnyHuEXh4gnE17OrqoporOTmZ6kI1YBHe09NDTU1RUZFgHaCGx0HEUgHHWHf8+vXrkdYDUgEXw9T2MuQSMCgoiOQ7Ozu8iMA4oDw4OJjGWtdniHpkeXnZ4DRcaT5//qwq+a6urihxIyIioLKyUjBBngMfxMzMTJqLiYl58pOH8LpSmMteBvOlGI6OjiTHwl2I8/NzkrMSSOv6DHGP/Mv+/j6Mj49DRkYG2NvbCzYoPLhqeHt7Q0VFBdVrpoQP4vHxMQQEBNB8dXX1ExmvK4Y57WXIJSBuLaEcV2AhcB7lNjY2NNa6PkPcIwJgB4g3wS0aKW5vb2nvKyoqCqqqqgSbmuciFERsEnC/EmV9fX2GeSFdIcxpL0MuAdWuIFrXZ4h7RIC1tTW6SUhICC8SBLvFgYEB6h6Li4tNUk+JBREfCpTh5vnW1hbNiemKYQ57GXIJqLaG0ro+Q9wjAlxeXtJNcIdbLZOTk9RN4k/51NQUL1aMVBDz8/NJ/uHDB4Otz8VU9jLkEjA3N5fkSrtIreszjDyCSmIF+Pr6Osm9vLx40ROWlpagoKCAdsF5cFXB1QU7ajV7agypIJ6entLqjDrl5eWSuo8xp70MtEXKHraP9uXLF15E8PtoWtdnGHkElZqbm/lpor6+nuR4ticHnpzg+XFqaqrgU4FLMjYNsbGxhtMCJUgFEcHuHY8S5QLOYy57GXL2YAePD4+npyccHR09keEY5/E4lJ0kaF2fYeQRdBJuuzQ2NsLm5iYVlbjy1dXVUQeDv+HYGSsFP1tSUgIfP36Enz9/GnVJBwcH0N/f/2ROCqkgMrChkAu4GKa2l6HEnsXFRXBxcaG/vbCwQGUEXnGM87hS/036iJFHsKOsqamByMhIKugx6bBziY6OhpaWFjg7O+M/oojd3V06NsP7dnZ2knFqYAF8/JLi06dPsjpS/Fd7Ed5e/iUErrT4AOB/z+BCgFccSxX3WtYX9oIZwX271tZW2vBta2uj8WtGa/ZqjRdPQAauKB0dHdSxYoBfO1qzVytYLAEZWGOZcr/N3GjN3teOxRNQ5/+NnoA6FkVPQB2LoiegjkXRE1DHovwDAPiwjDOm7csAAAAASUVORK5CYII=)) и координаты точки. Далее в N строках задается по паре целых чисел – координаты очередной вершины простого многоугольника в порядке обхода по или против часовой стрелки.

## Формат вывода

Выведите одну строку: «YES», если заданная точка содержится в приведённом многоугольнике или на его границе, и «NO» в противном случае.

## Пример

| Ввод Скопировать ввод | Вывод Скопировать вывод |
| --- | --- |
| `3 2 3 1 1 10 2 2 8 ` | `YES ` |
