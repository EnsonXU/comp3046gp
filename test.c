#include "stdafx.h"  
  
#include<omp.h>  
  
#include<iostream>  
  
usingnamespace std;  
  
  
//循环测试函数  
void test()  
{  
for(int i=0;i<10000;i++)  
{  
  
}  
}  
  
  
int _tmain(int argc,_TCHAR* argv[])  
{  
cout<<"这是一个串行测试程序!\n";  
double start = omp_get_wtime( );//获取起始时间  
  
for(int i = 0; i < 10000; i++)  
{   
test();  
}  
  
double end = omp_get_wtime( );  
  
cout<<"计算耗时为："<<end -start<<"\n";  
  
cin>>end;  
  
return 0;  
}  