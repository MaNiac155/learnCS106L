# C++ notes with CS 106L

## 1. Introduction

### Design Philosophy of C++

- Only add features if they solve an actual problem 
- Programmers should be free to choose their own style
- Compartmentalization is key
- Allow the programmer full control if they want it
- Don’t sacrifice performance except as a last resort 
- Enforce safety at compile time whenever possible

### C++ Basics

C++: Basic syntax + the STL

**The STL**:

- Tons of general functionality 

- Built in classes like maps, sets, vectors

- Accessed through the namespace `std::`

## 2. Types and Structs

### Types

`std::string`: a `cstring` type in the STL.

C++ is a statically typed language

#### Function Overloading

2 functions with same name but different types.

```c++
int half(int x) {
	std::cout << “1” << endl; // (1)
	return x / 2;
}
double half(double x) {
	cout << “2” << endl; // (2)
	return x / 2;
}
half(3) // uses version (1), returns 1
half(3.0) // uses version (2), returns 1.5
```

### Structs

**Struct**: a group of named variables each with their own type. A way to bundle different types together.

#### std::pair

An STL built-in struct with two fields of any type.

the fields can be called by `first` and `second`.

```c++
std::pair<int, string> numSuffix = {1,"st"};
cout << numSuffix.first; // 1
cout << numSuffix.second; // "st"
```

`std::make_pair(field1, field2)` is a function used to generate pair.

#### auto

`auto`: Keyword used in lieu(代替) of type when declaring a variable, tells the *compiler to **deduce*** the type.

does not mean the variable doesn't have a type.

if type is too long, use `auto`. DON'T OVERUSE! Write full name for primitive types.

```c++
std::pair<bool, std::pair<double, double>> result = quadratic(a, b, c);
// can be transfered to 
auto result = quadratic(a, b, c);
```

#### Structured binding (c++ 17)

gives value to several variables.

```c++
//Before:
auto p = std::make_pair(“s”, 5);
string a = p.first;
int b = p.second;

//After:
auto p = std::make_pair(“s”, 5);
auto [a, b] = p; // a is string, b is int

```

### HW: quadratic

<a href="./Exercises/quadratic.cpp">quadratic.cpp</a>

## 3. Initialization & References

**Uniform initialization**: curly bracket initialization. Available for all types, immediate initialization on declaration!

```cpp
std::vector<int> vec{1,3,5};
std::pair<int, string> numSuffix1{1,"st"};
Student s{"Sarah", "CA", 21};
// less common/nice for primitive types, butpossible!
int x{5};
string f{"Sarah"};


/*Careful with Vector initialization!*/
std::vector<int> vec1(3,5) //makes{5,5,5}
```

### Reference

**Reference**: An alias (another name) for a named variable.

the same variable. If Reference is changed, the original is changed too.

```c++
int a = 100;
int b = 100;
int &x=a; // a becomes a reference to x, x changes,a changes.
int x=b; // b becomes a copy of x, x changes, b doesnot change.
```



**The classic reference-copy bug 1.0**

以下代码想要给nums向量中的每一个数字都+1.

```c++
void shift(vector<std::pair<int, int>>& nums) { //size_t is commonly used for indices because 
	for (size_t i = 0; i < nums.size(); ++i) { //it’s unsigned and dynamically sized
		auto [num1, num2] = nums[i];
		num1++;
		num2++;
	}
}
```

错误：

第三行：每一次创建的是`nums[i]`的copy而不是reference, 修改时只修改了copy, 没有修改原变量.

改正: 

```c++
void shift(vector<std::pair<int, int>>& nums) {
	for (size_t i = 0; i < nums.size(); ++i) {
		auto& [num1, num2] = nums[i];
		num1++;
		num2++;
	}
}
```

**The classic reference-copy bug 2.0**

```c++
void shift(vector<std::pair<int, int>>& nums) {
	for (auto [num1, num2]: nums) {
		num1++;
		num2++;
	}
}
```

同上，第三行改成`for (auto& [num1, num2]: nums)`

#### lvalue and rvalue

<img src="D:\Download\Typora\images\C++ notes with CS 106L\image-20230701181418858.png" alt="image-20230701181418858" style="zoom:50%;" />



#### Const

specify that a variable can’t be modified



## 4. Streams

### Intro to stream

**stream**: an abstraction for input/output. Streams convert between data and the string representation of data.

`std::cout` is an output stream. It has type `std::ostream`

`std::cin` is an input stream. It has type `std::istream`

<img src="D:\Download\Typora\images\C++ notes with CS 106L\image-20230701182101601.png" alt="image-20230701182101601" style="zoom:50%;" />

### Output streams

- You can only send data to the stream 
  - Interact with the stream using the `<< ` operator 
  - Converts any type into string and sends it to the stream
- `std::cout` is the output stream that goes to the console

### Input streams

- `>>` is the stream extraction operator or simply extraction operator 

  - Used to extract data from a stream and place it into a variable

  - Receives a string from the stream and converts it to data 

  - Each ` >>` ONLY reads until the next whitespace

    - Whitespace = tab, space, newline

    - if read wrong types, it reads until wrong chars. exg: 

      ````c++
      int a; 
      cin>>a;
      // type 3.5weh
      cout<<a;
      //a=3
      ````

#### When things go wrong

```c++
int age; double hourlyWage;
cout << "Please enter your age: ";
cin >> age;
cout << "Please enter your hourly wage: ";
cin >> hourlyWage;
//what happens if first input is 2.17?

// age=2; houryWage=.17
```

正常情况：

<img src="D:\Download\Typora\images\C++ notes with CS 106L\image-20230701183233694.png" alt="image-20230701183233694" style="zoom:50%;" />

出错时：

<img src="D:\Download\Typora\images\C++ notes with CS 106L\image-20230701183252671.png" alt="image-20230701183252671" style="zoom:50%;" />

#### Another: getline

`istream& getline(istream& is, string& str, char delim);`

API:

<img src="D:\Download\Typora\images\C++ notes with CS 106L\image-20230701183446128.png" alt="image-20230701183446128" style="zoom:50%;" />

DONT USE IT WITH `cin`

### String Streams

A stream that can read from or write to a string object, Allows you to perform input/output operations on a *string* as if it were a stream.

need `#include <sstream>`

#### ostringstream

```c++
ostringstream oss("Ito-En Green Tea");
cout<<oss.str()<<endl;
oss<<"16.9 ml";
cout<<oss.str()<<endl;

// out:
// ----------
// Ito-En Green Tea
// 16.9 mlGreen Tea
```

创建时可以加入内容。可以选择模式，如'ate': at the and

<img src="D:\Download\Typora\images\C++ notes with CS 106L\image-20230701184002560.png" alt="image-20230701184002560" style="zoom:50%;" />

#### istringstream

```c++
istringstream iss("10 minute");
int num;
string unit;
iss>>num;
iss>>unit;
// num=10, unit="minute"
```

give input one by one.

```cpp
iss>>num;
iss>>unit;
// is the same as:
iss>>num>>unit;
```

回头可以看：

<img src="D:\Download\Typora\images\C++ notes with CS 106L\image-20230701184438183.png" alt="image-20230701184438183" style="zoom:33%;" />

### Exercise：stringToInteger

可以用 iss 来实现字符转换整数。

有四个状态位来表示流的状态。

- Good bit: 可以正常读/写
- Fail bit: 上一次对流进行的操作（previous operation）失败了，后续的操作全部中止/冻结（frozen）
- EOF bit: 上一次对流的操作到达buffer的末尾，the end of buffer content
- Bad bit: 当前流发生了可能无法恢复的错误
   这里面需要注意的一点是：流状态为后面三个任何一种时，后续的操作都会被中止（frozen）

<img src="D:\Download\Typora\images\C++ notes with CS 106L\81572d79c86a4f25bc561be54e56fe31tplv-k3u1fbpfcp-zoom-in-crop-mark4536000.webp" alt="image.png" style="zoom: 67%;" />

代码：<a href="./Exercises/str2int.cpp">str2int.cpp</a>

### Buffer

<img src="D:\Download\Typora\images\C++ notes with CS 106L\71587a8e53684625a10a82ee2140ca71tplv-k3u1fbpfcp-zoom-in-crop-mark4536000.webp" alt="image.png" style="zoom: 67%;" />

```cpp
    cout << "CS";
    somethingspendtime();
    cout << "106";
    somethingspendtime();
    cout << "L";
    somethingspendtime();
    cout << endl;
```

这种时候，`"CS106L"`会同时打印到控制台上。因为输入输出的开销是十分昂贵的（注：这实际上涉及到系统调用，从用户态到内核态的切换等，开销很大），因此`cout`流会在buffer满或强制刷新buffer的时候将buffer内的字符一齐输出到控制台上。

但标准错误流不会进行，std::cerr`流会直接输出。（这点和python是一样的）。

#### 自动触发buffer flush

实际上，有一些操作是会自动触发buffer的刷新的，如cin，在用户输入之前应该把cout buffer内的数据输出到控制台。

<img src="D:\Download\Typora\images\C++ notes with CS 106L\f192b718358d4718a08fe3b57a364b73tplv-k3u1fbpfcp-zoom-in-crop-mark4536000.webp" alt="image.png" style="zoom: 67%;" />

<img src="D:\Download\Typora\images\C++ notes with CS 106L\521d867e693048f9ae85b81fedb52d50tplv-k3u1fbpfcp-zoom-in-crop-mark4536000.webp" alt="image.png" style="zoom:67%;" />

这些操作符都相对比较容易查询，所以课程并不会对其进行讲解，可以自行Google。不要去背/记这些操作符，你正常使用这些操作符时完全用到哪个就去查询对应的文档。

### cin 

当提取多个输入时，第一个cin在遇到whitespace时==停下==，而不会将它输入。下一个cin会==跳过whitespace==，找到下一个非空字符并输入。

<img src="D:\Download\Typora\images\C++ notes with CS 106L\image-20230702125631012.png" alt="image-20230702125631012" style="zoom:50%;" />

坏处：输入带有空格时，会跳过空格后的内容。

修改：可以用`getline()`

```cpp
cin>>name;
//==>
getline(cin,name)
```

`getline()`读取直到换行，并且==吃掉换行符==。

`getline()` 和`cin`都会返回一个bool，代表是否成功。

读取整数：自建`getInteger()`

## 5. Containers

<img src="D:\Download\Typora\images\C++ notes with CS 106L\image-20230703105326724.png" alt="image-20230703105326724" style="zoom:50%;" />

deque: double ended queue

list: doubly linked list

#### 2 Types

- Sequence:  
  - Containers that can be accessed sequentially 
  - Anything with an inherent order goes here!
- Associative
  - Containers that don’t necessarily have a sequential order  
  - More easily searched 
  - Maps and sets go here!

### API

#### vector

![image-20230703105425901](D:\Download\Typora\images\C++ notes with CS 106L\image-20230703105425901.png)

==注意==：查找位置`i`的值有两种方法：`vec.at(i)` 和 `vec[i]`。其中第二种不进行边界检查。也就是说一个长度为3的数组，使用了`vec[8]`，编译器不会报错。除非碰到了保护的内存。

对于vector，`push_front()` 很慢。=>用`deque`. `deque` is also a data structure in stl.

#### set

![image-20230703105454430](D:\Download\Typora\images\C++ notes with CS 106L\image-20230703105454430.png)

#### map

![image-20230703105502743](D:\Download\Typora\images\C++ notes with CS 106L\image-20230703105502743.png)

### Implementation



Choosing sequence Containers 

![image-20230703110121421](D:\Download\Typora\images\C++ notes with CS 106L\image-20230703110121421.png)

choosing associative containers

![image-20230703110416511](D:\Download\Typora\images\C++ notes with CS 106L\image-20230703110416511.png)

### Container Adaptor

`Stack` and `Queue` are implemented ==based upon== primitive containers, which is called `Container Adaptor`. (AKA. wrapper)

`Stack` and `Queue` are based on `Deque`.

### Associative Containers

#### map

`std::map<T1,T2>`

 use a binary search tree as backend.

`map.get(key)` vs.` map[key]`

查找不存在的key，`map.get(key)` 返回错误，而` map[key]` 创建一个新key并赋值。

#### set

`std::set<T> `

只有一列，除了查找，都和map一样。

**there are unordered version of each container.** 

![image-20230703132156391](D:\Download\Typora\images\C++ notes with CS 106L\image-20230703132156391.png)

 

### Iterators

how to iterate in a `map` or `set`?

Iterators allow iteration over ==any== container.

type: `iterator`.

Example: a set containing `1 2 3 4`:

```cpp
set<int>::iterator iter= mySet.begin();//initialize the iterator to the first of set.
cout<< *iter <<endl;//use * to get the value.
++iter; //use the ++(prefix) operator to advance.
if(iter==mySet.end()) return;// check the end.
```

对于vector，Iterator是用指针实现的。

 `++iter`: use the iterator then increase it.

