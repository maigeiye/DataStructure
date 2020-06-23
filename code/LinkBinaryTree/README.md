# LinkBinaryTree

### 算法（Java）

树节点

```java
public class TreeNode {
	int val;
	TreeNode left;
    TreeNode right;
	TreeNode(int x) { val = x; }
}
```



- 构建二叉树（根据前序和中序）

> 前序第一个值为树的根节点的值，然后在中序找出根节点的位置，在中序中，根节点左边的值全部为左子树的值，根节点右边的值全部为右子树的值，然后根据在中序中得到的左子树和右子树的范围可以确定左子树和右子树在前序中的范围，这样就得到了左子树和右子树的前序和中序，然后通过递归来创建左子树和右子树，如：
>
> 前序： <u>1</u> (中) <u>2  4  5</u> (左) <u>3  6  7</u> (右)
>
> 中序： <u>4  2  5</u> (左) <u>1</u> (中) <u>6  3  7</u> (右)

```java
class Solution {
    public TreeNode buildTree(int[] preorder, int[] inorder) {
        if (preorder.length == 0) return null;
        int rootVal = preorder[0], rootIndex = 0;
        for (int i = 0; i < inorder.length; i++) {
            if (inorder[i] == rootVal) {
                rootIndex = i;
                break;
            }
        }
        TreeNode tree = new TreeNode(rootVal);
        tree.left = buildTree(Arrays.copyOfRange(preorder, 1, rootIndex + 1), Arrays.copyOfRange(inorder, 0, rootIndex));
        tree.right = buildTree(Arrays.copyOfRange(preorder, rootIndex + 1, preorder.length), Arrays.copyOfRange(inorder, rootIndex + 1, inorder.length));
        return tree;
    }
}
```

