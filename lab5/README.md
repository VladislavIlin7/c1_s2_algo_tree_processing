## Лабораторная работа №5

### Кратчайшие пути во взвешенном графе

ФИО: Ильин Владислав Александрович

Группа: М8О-102БВ-25

#### Постановка задачи:

Считать ориентированный взвешенный граф из файла и сохранить его в виде матрицы смежности.
С помощью алгоритма Флойда-Уоршелла найти кратчайшие расстояния между всеми парами вершин.
Дополнительно восстановить кратчайший путь между двумя вершинами и проверить наличие отрицательного цикла.

#### Описание работ:

Граф хранится как матрица смежности. Если ребра нет, в ячейке находится `INF`.
На главной диагонали стоят нули.

Алгоритм Флойда-Уоршелла перебирает каждую вершину как промежуточную и проверяет, можно ли улучшить путь:

```text
dist[i][j] > dist[i][k] + dist[k][j]
```

Если путь через `k` короче, расстояние обновляется. Для восстановления маршрута используется матрица `next`.

#### Запуск:

```commandline
cmake --build cmake-build-debug --target lab5
.\cmake-build-debug\lab5.exe lab5\input.txt lab5\output.txt
```

Для запуска тестов:

```commandline
cmake --build cmake-build-debug --target lab5_tests
.\cmake-build-debug\lab5_tests.exe
```

Для запуска бенчмарков:

```commandline
cmake --build cmake-build-debug --target lab5_benchmark
.\cmake-build-debug\lab5_benchmark.exe
```

#### Формат входных данных:

```text
n m
u v w
```

`n` - количество вершин, `m` - количество ребер, `u v w` - ребро из `u` в `v` с весом `w`.

#### Пример работы:

```text
Input:
Matrix (5 x 5):
     0     4     1   INF    10
   INF     0   INF     1   INF
   INF     2     0     5   INF
   INF   INF   INF     0     3
   INF   INF   INF     2     0

Result:
Shortest distances:
          0     1     2     3     4
  0 |     0     3     1     4     7
  1 |   INF     0   INF     1     4
  2 |   INF     2     0     3     6
  3 |   INF   INF   INF     0     3
  4 |   INF   INF   INF     2     0

Path:
0 -> 4, length = 7: 0 -> 2 -> 1 -> 3 -> 4
```

#### Unit-тесты:

Тесты написаны через GTest в файле `tests.cpp`.

Проверяется:

1. Создание графа.
2. Добавление ориентированного ребра.
3. Расчет кратчайших расстояний.
4. Недостижимые вершины.
5. Отрицательный цикл.

#### Бенчмарки:

Бенчмарк написан через Google Benchmark в файле `benchmark.cpp`.

```text
CPU Model: AMD Ryzen 5 7640HS w/ Radeon 760M Graphics
Logical CPU threads: 12
RAM Memory: 31.2 GB
OS: Windows x64
Compiler: GCC 15.2.0 / MinGW
```

```text
------------------------------------------------------------------------------------
Benchmark                                          Time             CPU   Iterations
------------------------------------------------------------------------------------
BM_FloydWarshall/vertices:10/edges:30           5924 ns         5859 ns       112000
BM_FloydWarshall/vertices:25/edges:125         52442 ns        50000 ns        10000
BM_FloydWarshall/vertices:50/edges:500        373205 ns       357492 ns         1792
BM_FloydWarshall/vertices:75/edges:1125      1189075 ns      1171875 ns          560
BM_FloydWarshall/vertices:100/edges:2500     2796858 ns      2780720 ns          236
BM_FloydWarshall/vertices:150/edges:5000     9036855 ns      9166667 ns           75
BM_FloydWarshall/vertices:200/edges:10000   21343488 ns     21139706 ns           34
BM_FloydWarshall_BigO                           2.67 N^3        2.66 N^3
BM_FloydWarshall_RMS                               1 %             2 %
```

Все результаты сохранены в файле `report.json`.

#### Сложность:

```text
Время: O(n^3)
Память: O(n^2)
```

#### Выводы

В ходе лабораторной работы был реализован алгоритм Флойда-Уоршелла.
Были изучены матрица смежности, поиск кратчайших путей, восстановление пути,
обнаружение отрицательного цикла, unit-тестирование и benchmarking.
