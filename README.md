# 2D-Sort

**This project provides an algorithm to sort given 2D points according to specific pattern.**

1. Pattern 0
![Image](https://github.com/Chen-Si-An/2D-Sort/blob/main/Sort_0.bmp)

![Image](https://github.com/Chen-Si-An/2D-Sort/blob/main/Result_0.bmp)

2. Pattern 1
![Image](https://github.com/Chen-Si-An/2D-Sort/blob/main/Sort_1.bmp)

![Image](https://github.com/Chen-Si-An/2D-Sort/blob/main/Result_1.bmp)

3. Pattern 2
![Image](https://github.com/Chen-Si-An/2D-Sort/blob/main/Sort_2.bmp)

![Image](https://github.com/Chen-Si-An/2D-Sort/blob/main/Result_2.bmp)

4. Pattern 3
![Image](https://github.com/Chen-Si-An/2D-Sort/blob/main/Sort_3.bmp)

![Image](https://github.com/Chen-Si-An/2D-Sort/blob/main/Result_3.bmp)

**This algorithm can offer selection of custom comparator, which not necessarily satisfies stringent compare required by STL sort.**

**Moreover, this algorithm demonstrates a better performance compared to stable_sort() provided by STL through using OpenMP.**

* Environment: CPU 11th Gen Intel(R) i7-11700 (8 cores), Debug

 Number of Points  |    2D Sort   | stable_sort from STL
:----------------: |   :-------:  | :--------------------:
   1001 * 1001     |   0.351 sec  |       0.401 sec
   2001 * 2001     |   1.442 sec  |       1.619 sec 
   5001 * 5001     |   8.171 sec  |      10.816 sec  
  10001 * 10001    |  33.803 sec  |      56.846 sec  
