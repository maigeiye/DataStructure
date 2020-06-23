# LinkList

### 概念

链式线性表，即链表，顾名思义这个线性表是通过链子将所有元素连在一起的，存储空间在内存不必连续，元素可以零散的分布在内存中，通过指针作为链子将每个元素连接起来



### 模型

> 节点

链表的存储单元，由两个部分组成：

- 数据域（存储元素）
- 指针域（存储下一个节点的指针）

> 链表

链表由三个部分组成：

- 头结点
- 尾节点
- 长度（元素个数）

头节点是链表第一个节点之前设置的节点，该节点的数据域为空，指针域存储指向第一个节点的指针，当链表为空表的时候，头结点的指针域也是空；

尾节点不是必要的，在没有尾节点的情况下要找到链表的最后一个节点就必须从头结点出发寻找，所以设置尾节点可以很方便的找到链表的终端；



### 操作

初始化：获取一个空节点，将链表的头结点和尾节点都指定为该节点，长度赋值0，即完成一个链表的初始化；

插入：

- 在p、q节点之间插入s节点，改变p、s节点的指针域即可；

```c
p->next = s;
s->next = q;
```

- 在链表末尾追加节点s，把尾节点的指针域指定为节点s的地址，再把尾节点指定为s即可；

```c
L->tail->next = s;
L->tail = s;
```

删除：

- 删除p、q之间的s节点，改变p节点指针域，释放s节点即可；

```c
p->next = q;
free(s);
s->next = NULL;
```

- 删除链表最后一个节点，把尾节点前移，释放被删节点即可；

```c
//找到尾节点的前一个节点p
p->next = NULL;
L->tail = p;
```



### 算法（Java）

链表节点

```java
public class ListNode {
    int val;
    ListNode next;
    ListNode(int x) { val = x; }
}
```



- 移除未排序链表中的重复节点，保留最开始出现的节点

> 设置两个引用，第一个用来遍历链表，第二个用来遍历第一个引用指向的节点后的节点，如果和第一个引用指向的节点的值相同就删掉，这种做法可以不去另外用哈希表的空间来去重，用时间换空间

```java
class Solution {
    public ListNode removeDuplicateNodes(ListNode head) {
        if (head == null || head.next == null) {
            return head;
        }
        ListNode node = head;
        while (node != null) {
            ListNode p = node;
            while (p.next != null) {
                if (p.next.val == node.val) {
                    p.next = p.next.next;
                } else {
                    p = p.next;
                }
            }
            node = node.next;
        }
        return head;
    }
}
```



- 返回倒数第k个节点的值

> 快慢指针问题，设置两个引用，然后将其中一个引用指向第k个节点，另一个指向头结点，然后同时移动两个引用，当指向第k个节点的引用移到最后一个节点时，另一个节点则会正好指向倒数第k个节点

```java
class Solution {
    public int kthToLast(ListNode head, int k) {
        ListNode cur = head, pre = head;
        for (int i = 1; i < k; i++) {
            pre = pre.next;
        }
        while (pre.next != null) {
            cur = cur.next;
            pre = pre.next;
        }
        return cur.val;
    }
}
```



- 删除链表中间的某个节点（只能访问该节点，不提供链表）

> 不提供链表要怎么删除这个节点呢，根本找不到前驱，其实换个思路就解决了，既然删不了这个节点，那就把后面的所有节点往前推，把这个节点的值覆盖掉即可

```java
class Solution {
    public void deleteNode(ListNode node) {
        node.val = node.next.val;
        node.next = node.next.next;
    }
}
```

