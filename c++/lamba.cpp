/*
c++ lamba
[capture list] (params list) mutable exception-> return type { function body }
������庬������

capture list�������ⲿ�����б�
params list���β��б�
mutableָʾ��������˵���Ƿ�����޸Ĳ���ı���
exception���쳣�趨
return type����������
function body��������
���⣬���ǻ�����ʡ�����е�ĳЩ�ɷ�������������������Lambda���ʽ
1 	[capture list] (params list) -> return type {function body}
2 	[capture list] (params list) {function body}
3 	[capture list] {function body}
[]����д��ֵ:
�գ� ��ʹ�øò�����
=���������ڿ���ʹ��Lambda�������÷�Χ�����пɼ��ľֲ�����������Lambda�������this����������ֵ���ݷ�ʽ���൱�ڱ������Զ�Ϊ���ǰ�ֵ���������оֲ���������
&���������ڿ���ʹ��Lambda�������÷�Χ�����пɼ��ľֲ�����������Lambda�������this�������������ô��ݷ�ʽ���൱�ڱ������Զ�Ϊ���ǰ����ô��������оֲ���������
this���������ڿ���ʹ��Lambda�������еĳ�Ա������
a����a��ֵ���д��ݡ���ֵ���д���ʱ���������ڲ����޸Ĵ��ݽ�����a�Ŀ�������ΪĬ������º�����const�ġ�Ҫ�޸Ĵ��ݽ�����a�Ŀ������������mutable���η���
&a����a�����ý��д��ݡ�
a, &b����a��ֵ���д��ݣ�b�����ý��д��ݡ�
=��&a, &b����a��b�����ý��д����⣬������������ֵ���д��ݡ�
&, a, b����a��b��ֵ���д����⣬���������������ý��д��ݡ�
*/
#include <iostream>
#include <thread>

void test_lamba()
{
	char s[]="Hello World!";  
	int uppercase = 0; //modified by the lambda  
	//��Ϊc++���������������Գ�������������ʹ�� 
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
	//��c++��ʹ��c�е�container_of�ᱨ��ֻ��ͨ��lamba���ʽ��decltype�����滻ʹ�øú깦��������ʹ��
}
int main(int argc, char *argv[]) 
{
	std::cout<<"hello world!"<<std::endl;
	test_lamba();
	std::this_thread::sleep_for(std::chrono::seconds(2));
	return 0;
}
