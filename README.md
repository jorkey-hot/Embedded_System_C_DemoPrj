# 项目名称：PROJ_DEMO(一个通用的C工程模板)

## 一、环境
### 1 编译工具：Cmake
工程使用cmake工具作为安装编译工具，以支持跨平台编译需求，统一编译配置。  
#### 1.1 依赖工具
- 构建工具 make
- 编译器 gcc

## 二、工程组成
├─bin  
├─build  
├─component  
│  ├─pthread  
│  │  ├─inc  
│  │  └─src  
│  └─zlog  
│      ├─inc  
│      ├─lib  
│      │  ├─aarch64_linux  
│      │  └─x86_64_linux  
│      └─src  
├─c_public  
├─os  
│  ├─linux  
│  │  ├─inc  
│  │  ├─lib  
│  │  └─src  
│  ├─rtthread  
│  └─win  
└─test  


## 三、修改记录
2026.4.23 增加linux系统下，线程创建封装  
2026.4.24 开始编写Linux系统下，消息队列的封装，使用锁+条件变量和自定义链表实现消息队列，以支持线程间通信  
