/*
 * (input-parameters) => expression
 * (input-parameters) => { statement; }
 * 仅当 lambda 只有一个输入参数时，括号才是可选的；否则括号是必需的。 括号内的两个或更多输入参数使用逗号加以分隔：
 * 有时，编译器难以或无法推断输入类型。 如果出现这种情况，你可以按以下示例中所示方式显式指定类型
 * 表达式lamba：
 * //返回s的长度是否>x
 * (int x, string s) => s.Length > x
 * 经过试验c#的lamba必须先赋值给委托然后才能进行调用，并不能将调用和申明写在一起
 * 如以下语法是错误的
 *  ```
   delegate void Action();
   Action act = ()=>
            {
                Console.WriteLine("aaa");
            }();
 * ```
 * lamba需要注意的是延后执行如:
 * ```
    //此段函数的意思是开个新的线程执行... 注意这都是委托，和回调一样，需要的时候才会执行
    //lamba当做函数参数传入,需要特别注意调用时间
    Task.Factory.StartNew(() =>
                        {
                            Thread.Sleep(0);
                            view.data.Percent = 100;
                        });
 * ```
 * 
 */
/*
 *     //在wpf中的用法 (UI线程不允许其他线程操作，如果要对UI操作只能通过向Dispatcher投递异步或同步任务)
 *     //如下例子中startNew内部new了该操作所以可以直接填写lamba方法,而begininvoke则不允许
 *     Task.Factory.StartNew(() =>
            {
                //do work
                Thread.Sleep(3000);
                Dispatcher.BeginInvoke(new Action(()=>
                {
                    m_bCloseByMe = true;
                    this.Close();
                }));
                
                Dispatcher.BeginInvoke((Action)delegate()
                {
                    m_bCloseByMe = true;
                    this.Close();
                });
                 
            });
 * */
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace ConsoleApplication2
{
    class Program
    {
        delegate int del(int i);
        delegate void TestDelegate(string s);
        delegate void Action();
        void test_lamba()
        {
            del myDelegate = x => x * x;
            int i = 0;
            int j = myDelegate(5); //j = 25 

            myDelegate = (int x) => {
                //公用外部的变量
                i = 5;
                return x * x;
            };
            j = myDelegate(5);
            Console.WriteLine("i:"+i.ToString()+"j:"+j.ToString());
            TestDelegate xelegate =  (string n) =>{
                Console.WriteLine(n);
            };
            xelegate("rr");
            Action act = ()=>
            {
                Console.WriteLine("aaa");
            };
            act();
        }
        static void Main(string[] args)
        {
            Program p = new Program();
            p.test_lamba();
            Thread.Sleep(1000);
        }
    }
}
