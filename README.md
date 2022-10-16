# C++对象模型分析

class是一种特殊的struct

- 在内存中class依旧是变量的集合
- class与struct遵循相同的内存对齐规则
- class中的成员函数和成员变量是分开存放的
  - 每个对象有独立的成员变量
  - 所有对象共享类中的成员函数

运行时的对象退化为结构体的形式

- 所有成员变量在内存中依次排布
- 成员变量之间可能存在内存空隙
- 可以通过内存地址直接访问成员变量
- 访问权限关键字在运行时失效

总结

- 类中的成员函数位于代码段中
- 调用成员函数时对象地址作为隐式参数传递
- 成员函数通过对象地址访问成员变量
- C++语法隐藏了对象地址传递过程

在C++编译器的内部类可以理解为结构体
子类是由父类的成员叠加子类中新定义的成员得到的

C++多台的实现原理

- 当类中声明虚函数时，编译器会在类中生成一个虚函数表
- 虚函数表是一个存储成员函数地址的数据结构
- 虚函数是由编译器自动生成于维护的
- virtual 成员函数会被编译器放入到虚函数表中
- 存在虚函数时，每个对象中都有一个虚函数表指针指向该类的虚函数表

C语言如何实现类？

- 定义一个结构体，结构体中的变量就是成员变量。
- 将成员函数第一个参数设置为结构体指针，那么必须使用对应的结构体才能调用这些函数

C语言如何实现继承？

- 继承的本质是变量的叠加，在子类中定义一个父类对象，通过该对象访问父类成员。
- 此时可以再对子类定义一些其他函数，以及对函数进行重载（C语言不能函数同名，因此名字有区别）

C语言如何实现多态？

- C++中多态的实现依赖于虚函数表
- 如果要实现多态，需要在基类中增加一个指针成员，指向虚函数表
- 同时在类中还需要定义一个父类的虚函数表和子类的虚函数表。
- 当构建对象的时候，根据构造函数的不同将虚函数表指针指向不同的虚函数表。
- 在调用相应的虚函数的时候，只能通过函数指针表进行调用

![avatar](./resource/memory.png)
