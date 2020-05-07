# A Simple Calculator


## 缘起

写这么一个计算器最初就是为了羞辱一下舍友，他老人家写了半天的计算器竟然只能算整数的加减乘除！


## 基本使用

目前支持3种使用方式：**交互模式**、**读取标准输入并计算**、**读取命令行参数字符串并计算**。

假设编译后二进制文件名为`calc`，以下为详细说明。

### 交互模式

*注意：编译时需要 `readline`库，否则请将宏`USE_READLINE` 定义为 `false`。*

不使用任何命令行参数启动`calc`以进入交互模式。

进入交互模式后，会有命令提示符“ `>` ”，在此命令提示符后面输入计算表达式并按回车键以进行计算。计算结果会在下一行打印。如果编译时使用了 `readline`库，那么在输入表达式时可以用默认快捷键左右移动光标或调出历史输入。

此模式下可以使用保存变量和取变量值的功能（“`=`”和“`$`”操作符）。

输入“`^D`”（`Control`+`D`）以退出程序。

示例：
```
bash $ clac
> 1 + 1
    = 2
> sin($pi / 2)
    = 1
```

### 读取标准输入并计算

使用任何命令行参数“`-`”启动`calc`以进入该模式。

使用方法和交互模式类似，但没有命令提示符和美观的结果输出。

示例：
```
# a) basic
bash $ clac -
(1 + 2) * 3
9
sin($pi*2.5)
1

# b) using pipe
bash $ echo 1+2 | calc -
3

# c) from file, to file
bash $ cat in.txt | calc - > out.txt
```

### 读取命令行参数字符串并计算

直接将表达式作为命令行参数，以进入该模式。

不必刻意地将表达式写在一个字符串内。例如，“`calc 1 + 1`”、“`calc 1+1`”、“`clac '1 + 1'`”的计算结果是一样的。

需要特别注意的是，某些语法可能和正在使用的shell有冲突，需要转义。例如，“`calc \$pi`”或“`calc '$pi'`”应当可以正确地运行，但是“`calc $pi`”却可能发生错误，因为对于大多数shell来说，“`$pi`”表示从shell中寻找“pi”这个变量，而在此处我们希望从本程序的存储中寻找变量“pi”。

本模式只能执行一条计算语句。


## 计算表达式

### 词法

有3种词法元素：**数字(Number)**、**操作符(Operator)** 和 **符号(Symbol)**。

#### 数字

目前只支持形如“123”或“45.6”的字面形式。

数字一律存储为浮点数。

#### 操作符

操作符只能有一个字符（1字节）。

目前支持的主要操作符有：四则运算符和乘方符 `+ - * / ^`；括号 `( )`；保存变量符和取变量值符 `= $`。

特殊操作符有：取反“`~`”（可用“`-`”表示）；参数列表分隔“`,`”（仅用于函数的参数列表）。

#### 符号

1到7个英文/数字字符（不以数字开头）。用来表示函数或变量。

变量“`ans`”记录了上一次计算结果。

### 表达式

#### 优先级

优先级与数学表达式中计算符号的优先级一致。

取反符号“`~`”和取值符号“`$`”有最高优先级。保存变量符“`=`”优先级最低。

例如，“`val=-1+2*3/4^$pi`” 即为 “`val=((-1)+((2*3)/(4^$pi)))`”，或是  $\mathrm{val}\leftarrow -1 + \frac{2\times 3}{4^{\pi}}$。

#### 函数调用

函数调用形式为 `FnName (ArgList)`。其中，参数列表中各个参数用“`,`”隔开。如果参数形式十分简单，可用空白字符隔开，但不建议这么做。

例如：
```
sin(2 * $pi * 0.5)
log(6 ^ (12 / 2), 1 + 2 + 3)
pow(2 10)
```


## C动态库

动态库为 `bin/libcalc.so`。
头文件 `inc/dlapi.h` 中提供了可以被C程序调用的接口：
“`void * calc_init(void)`”、“`double calc_evaluate(void *, const char *)`”和“`void calc_cleanup(void *)`”。
其中，“`void * calc_init(void)`”和“`void calc_cleanup(void *)`”用于创建和清理计算器；“`double calc_evaluate(void *, const char *)`”用于执行计算。

如果需要用Python调用此动态库，可用参考`test/tst_dl.py`。
