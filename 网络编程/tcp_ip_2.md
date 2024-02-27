参考 3-Linux多线程服务端编程  使用muduo C++网络库.pdf

# 第一章 线程安全的对象生命期管理

编写线程安全的类不是难事，用同步原语( synchronization primitives)保护内部状态即可。但是对象的生与死不能由对象自身拥有的mutex (互斥器）来保护。如何避免对象析构时可能存在的race condition(竞态条件)是C++多线程编程面临的基本问题，可以借助Boost库中的shared_ptr和 weak_ptr 1完美解决。这也是实现线程安全的Observer模式的必备技术。

## 1.1 当析构函数遇到多线程