#include <stdio.h>
#include <io.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const char *to_search=".\\*";        //�����ҵ��ļ���֧��ͨ���


int main()
{
	string location_base=".\\";
	vector<string> location;

	long handle;                                                //���ڲ��ҵľ��
	struct _finddata_t fileinfo;                               //�ļ���Ϣ�Ľṹ��
	handle=_findfirst(to_search,&fileinfo);                    //��һ�β���
	int i=0;

	if(-1==handle)return -1;
	printf("%s\n",fileinfo.name);                              //��ӡ���ҵ����ļ����ļ���
	cout<<location_base+fileinfo.name<<endl;
	location.push_back(location_base+fileinfo.name);
	while(_findnext(handle,&fileinfo)==0)                      //ѭ�������������ϵ��ļ���֪���Ҳ���������Ϊֹ
	{
		printf("%s\n",fileinfo.name);
		//location[i]=location_base;

		cout<<location_base+fileinfo.name<<endl;
		location.push_back(location_base+fileinfo.name);
	}
	
	cout<<location.size()<<endl;
	_findclose(handle);                                      //�رվ��

	return 0;
}