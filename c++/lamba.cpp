/*
c++ lamba
[capture list] (params list) mutable exception-> return type { function body }
各项具体含义如下

capture list：捕获外部变量列表
params list：形参列表
mutable指示符：用来说用是否可以修改捕获的变量
exception：异常设定
return type：返回类型
function body：函数体
此外，我们还可以省略其中的某些成分来声明“不完整”的Lambda表达式
1 	[capture list] (params list) -> return type {function body}
2 	[capture list] (params list) {function body}
3 	[capture list] {function body}
[]中填写的值:
空， 不使用该参数；
=。函数体内可以使用Lambda所在作用范围内所有可见的局部变量（包括Lambda所在类的this），并且是值传递方式（相当于编译器自动为我们按值传递了所有局部变量）。
&。函数体内可以使用Lambda所在作用范围内所有可见的局部变量（包括Lambda所在类的this），并且是引用传递方式（相当于编译器自动为我们按引用传递了所有局部变量）。
this。函数体内可以使用Lambda所在类中的成员变量。
a。将a按值进行传递。按值进行传递时，函数体内不能修改传递进来的a的拷贝，因为默认情况下函数是const的。要修改传递进来的a的拷贝，可以添加mutable修饰符。
&a。将a按引用进行传递。
a, &b。将a按值进行传递，b按引用进行传递。
=，&a, &b。除a和b按引用进行传递外，其他参数都按值进行传递。
&, a, b。除a和b按值进行传递外，其他参数都按引用进行传递。
*/
#include <iostream>
#include <thread>

void test_lamba()
{
	char s[]="Hello World!";  
	int uppercase = 0; //modified by the lambda  
	//因为c++中无匿名函数所以常当做匿名函数使用 
	for (char v :s)
	{
		[&](){
			if (isupper((v)))
			{
				uppercase++;
			}
		}();
	}
	std::cout<< uppercase<<" uppercase letters in: "<<s<<std::endl; 
}
void test_container_of()
{
#undef offsetof
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

/**
 * container_of - cast a member of a structure out to the containing structure
 *
 * @ptr:	the pointer to the member.
 * @type:       the type of the container struct this is embedded in.
 * @member:     the name of the member within the struct.
 *
 */
/*
//c
#define container_of(ptr, typea, member) ({		      \
	const typeof(((typea *)0)->member)*__mptr = (ptr);    \
	(typea *)((char *)__mptr - offsetof(typea, member)); })
*/
//c++
#define container_of(ptr, type, member) [&]()->type * { \
	const decltype(((type *)0)->member)*__mptr = (ptr);    \
	return (type *)((char *)__mptr - offsetof(type, member)); }();
	//在c++中使用c中的container_of会报错，只能通过lamba表达式和decltype进行替换使得该宏功能能正常使用
}
int main(int argc, char *argv[]) 
{
	std::cout<<"hello world!"<<std::endl;
	test_lamba();
	std::this_thread::sleep_for(std::chrono::seconds(2));
	return 0;
}
