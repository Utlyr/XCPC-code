##### 矩阵树定理是一个基于线性代数工具，解决图上生成树计数相关问题的工具。
#### 基础定义：
1. 图的关联矩阵：  
对于一个n个点（第i个点记为$v_i$），m条边（第j条边记为$e_j$）的无向图，定义关联矩阵M为：
$$
M_{i,j}=\left\{\begin{matrix} 
  1,e_j是v_i的出边 \\  
  -1，e_j是v_i的入边 \\
  0,otherwise.
\end{matrix}\right. 
$$
显然，大小是n x m的
2. 拉普拉斯（基尔霍夫）矩阵:  
拉普拉斯矩阵 L 定义为：  
$$
L_{i,j}=\left\{\begin{matrix} 
  deg(v_i),i=j \\
  -cnt(v_i,v_j),otherwise.
\end{matrix}\right. 
$$
其中，deg(v)是点v的度数，$cnt(v_i,v_j)$表示$v_i$ <-> $v_j$的数量。  
计算公式：  
$$ L = MM^{T} $$
#### 矩阵树定理：
$记L_0为L去掉第k行、第k列后的矩阵(k任意取),则该无向图的生成树个数为det(L_0).$
#### 在有向图上的扩展：

