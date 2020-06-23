# DFS(深度优先搜索)

这种算法可以用于遍历和搜索树或图

算法采用的思想是回溯法，按选优条件往所有方向遍历，如果一个方向不符合条件，会退回上一步重新选择方向，找到符合条件的就原路返回，这种思想用递归实现再适合不过了



- 矩阵中的路径

判断一个矩阵中是否存在一条包含字符串所有字符（按顺序）的路径，可以用DFS对矩阵进行遍历

> [["**A**", "**B**", "**C**", "E"],
>  ["S", "F", "**C**", "S"],
>  ["A", "**D**", "**E**", "E"]]
> "ABCCED"

```java
public boolean exist(char[][] board, String word) {
    char[] chs = word.toCharArray();
    for (int i = 0; i < board.length; i++) {
        for (int j = 0; j < board[0].length; j++) {
            if (board[i][j] == chs[0])
                // 如果该矩阵点的值与字符串首字符相同，则开始在矩阵中尝试获取路径
                if (dfs(board, i, j, chs, 0))
                    return true;
        }
    }
    return false;
}

public boolean dfs(char[][] board, int i, int j, char[] chs, int k) {
    // 如果越界或者该方向不符合要求就原路返回并返回false
    if (i < 0 || i >= board.length || j < 0 || j >= board[0].length || board[i][j] != chs[k])
        return false;
    // 如果路径长度和字符串长度想等，就证明找到这条路径了，原路返回并返回true
    if (k == chs.length - 1) return true;
    // 覆盖已经经过的点的值，使寻找路径的时候不会再经过这个点
    char temp = board[i][j];
    board[i][j] = '/';
    // 向四个方向继续寻找符合条件的方向，只要有一个符合条件，结果就为true
    boolean result = dfs(board, i + 1 , j , chs, k + 1)
        || dfs(board, i - 1, j, chs, k + 1)
        || dfs(board, i, j + 1, chs, k + 1)
        || dfs(board, i, j - 1, chs, k + 1);
    // 原路返回的时候再把经过的点的值还原
    board[i][j] = temp;
    // 返回这个方向的寻找结果
    return result;
}
```

