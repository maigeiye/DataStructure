# 排序

### 冒泡排序

```c
void BubbleSort(int array[], int length) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length - 1 - i; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}
```



### 选择排序

```c
void SelectSort(int array[], int length) {
    for (int i = 0; i < length; i++) {
        int min = i;
        for (int j = i + 1; j < length; j++) {
            if (array[j] < array[min]) {
                min = j;
            }
        }
        int temp = array[i];
        array[i] = array[min];
        array[min] = temp;
    }
}
```



### 插入排序

```c
void InsertSort(int array[], int length) {
    int i;
    int j;
    int temp;
    for (i = 1; i < length; i++) {
        temp = array[i];
        for (j = i - 1; j >= 0 && array[j] > temp; j--) {
            array[j + 1] = array[j];
        }
        array[j + 1] = temp;
    }
}
```



### 快速排序

1. 选择一个基准元素
2. 通过正逆序遍历使数列所有比基准小的元素放在基准前面反之放在后面
3. 递归地让基准两边的子数列继续重复1、2步操作

```C
void QuickSort(int array[], int start, int end) {
    int num = array[start];
    if (start >= end)
        return;
    int i = start;
    int j = end;
    while (i != j ) {
        while (i < j && array[j] >= num) {      
            j--;
        }
        if (array[j] < num) {
            array[i] = array[j];   
        }
        while (i < j && array[i] < num) {
            i++;
        }
        if (array[i] > num) {
            array[j] = array[i];
        }
    }
    array[i] = num;
    QuickSort(array, start, i - 1);
    QuickSort(array, j + 1, end);
}
```



### 堆排序

1. 构建大顶堆（父节点比子节点大的完全二叉树）
2. 交换堆顶元素和末尾元素，除去末尾元素剩下的元素继续构造大顶堆
3. 数列长度减一得到的子数列重复第二步，直到子数列长度为1

```c
void HeapSort(int array[], int length) {
    // 构造大顶堆
    BuildHeap(array, length);
    for (int i = length - 1; i > 0; i--) {
        // 交换堆顶元素和末尾元素，此时数列中最大的元素就已放在数列末尾了
        int temp = array[i];
        array[i] = array[0];
        array[0] = temp;
        // 剩下的元素继续构造大顶堆
        BuildHeap(array, i);
    }
}

void BuildHeap(int array[], int length) {
    for (int i = length / 2 - 1; i >= 0; i--) {
        int temp = array[i];
        for (int j = i * 2 + 1; j < length; j = j * 2 + 1) {
            if (j + 1 < length && array[j] < array[j + 1]) {
                j++;
            }
            if (array[j] > temp) {
                array[i] = array[j];
                i = j;
            } else {
                break;
            }
        }
        array[i] = temp;
    }
}
```



### 归并排序

1. 递归均分数列，直到每个子数列只有一个元素，就可以认为每个子数列都是有序的
2. 将两个有序的字数列合并成一个有序的子数列

```c
void MergeSort(int array[], int start, int end) {
    // 数列只有一个元素时必为有序
    if (start == end)
        return;
    int mid = (start + end) >> 1;
    // 递归均分数列
    MergeSort(array, start, mid);
    MergeSort(array, mid + 1, end);
    // 合并两个有序数列
    int temp[end - start + 1];
    int i = start;
    int j = mid + 1;
    int k = 0;
    while (i <= mid && j <= end) {
        if (array[i] <= array[j]) {
            temp[k++] = array[i++];
        } else {
            temp[k++] = array[j++];
        }
    }
    while (i <= mid) {
        temp[k++] = array[i++];
    }
    while (j <= end) {
        temp[k++] = array[j++];
    }
    for (int i = 0; i < end - start + 1; i++) {
        array[start + i] = temp[i];
    }
}
```

