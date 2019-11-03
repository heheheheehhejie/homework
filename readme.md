### 一个小小的尝试
敝校新生研讨课的大作业，test_evolution版本更适合阅读

由于我不想上网抄文章，所以自己写了个小东西
+ 对于一个长度为160的01序列，将每两位作为一个单位，一共80个单位
+ 每个单位的贡献分两种情况，即其二进制表示的十进制数是否为3，是3就+140，否则-10
+ 现在希望得到一个总贡献尽量大的01序列
+ 我试图使用进化算法来解决这个问题

#### 有关选材
+ 用普通的f(x)类函数求极值也可以体现进化算法的效果
+ 但是纯随机同样可以达成求极值的效果
+ 所以我构造了一个更符合进化这个主题的函数
+ 就我写的这两个版本而言，一个大小为50的种群进化100次之后可以稳稳地拿到7000分以上
+ 而30万次随机最高也没有超过6000

#### 有关测试
+ 随机数的生成为了保证均匀随机，使用了C++11的一些东西，所以编译器要支持C++11
+ test_evolution.cpp需要输入测试次数，作用是将50的群落进化100次的效果和纯随机300000次做对比
+ flexible版本是可以输入种群大小和进化次数
+ 还是详见代码吧
