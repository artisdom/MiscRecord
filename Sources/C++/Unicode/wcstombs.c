#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 50

int main()
{
   size_t ret;
   char *MB = (char *)malloc( BUFFER_SIZE );
   wchar_t *WC = L"http://www.w3cschool.cc";

   /* ת�����ַ��ַ��� */
   ret = wcstombs(MB, WC, BUFFER_SIZE);
   
   printf("Ҫת�����ַ��� = %u\n", ret);
   printf("���ֽ��ַ� = %s\n\n", MB);
   
   return(0);
}