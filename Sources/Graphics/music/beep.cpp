/*����������С���ǡ������򻨡��������ѡ�����ѧ�衷��һ��Ǯ�������������׺�һ��Ц����ͯ������ͬ�����㡷��С�ܺ������ޡ�*/
#include<stdio.h>
#include<windows.h>
int main(void)
{
	int choice;
	void play_xiaoxingxing(void);
	void play_molihua(void);
	void play_zhaopengyou(void);
	void play_shangxuege(void);
	void play_yifenqian(void);
	void play_zhengfu(void);
	void play_canghaiyishengxiao(void);
	void play_tonghua(void);
	void play_tongzhuodeni(void);
	void play_xiaoxiongheyangwawa(void);
	while(1) {
		printf("��ѡ����Ҫ�������Ŀ��\n");
		printf("��1����С���ǡ�\n");
		printf("��2�������򻨡�\n");
		printf("��3���������ѡ�\n");
		printf("��4������ѧ�衷\n");
		printf("��5����һ��Ǯ��\n");
		printf("��6����������\n");
		printf("��7�����׺�һ��Ц��\n");
		printf("��8����ͯ����\n");
		printf("��9����ͬ�����㡷\n");
		printf("��10����С�ܺ������ޡ�\n");
		printf("��0���˳�����\n");
		printf("\n");
		printf("��ѡ��");
		scanf("%d",&choice);
		switch(choice) {
		case 1:
			play_xiaoxingxing();
			break;
		case 2:
			play_molihua();
			break;
		case 3:
			play_zhaopengyou();
			break;
		case 4:
			play_shangxuege();
			break;
		case 5:
			play_yifenqian();
			break;
		case 6:
			play_zhengfu();
			break;
		case 7:
			play_canghaiyishengxiao();
			break;
		case 8:
			play_tonghua();
			break;
		case 9:
			play_tongzhuodeni();
			break;
		case 10:
			play_xiaoxiongheyangwawa();
			break;
		case 0:
			break;
		default:
			printf("������������ȷ���룡\n");
		}
		Beep(0,1000);//��ͣһ����
		printf("\n");
		if(choice==0) {
			printf("\nллʹ�ã��ټ���");
			Beep(0,1000);//��ͣһ����
			break;
		}
	}
	return 0;
}

/*�������ּ���������t����Ӧ��Ƶ��*/
int notation_frequency(int t)
{
	switch (t) {
		/*��������:1,2,3,4,5,6,7*/
	case 1:
		return 523;
	case 2:
		return 587;
	case 3:
		return 659;
	case 4:
		return 698;
	case 5:
		return 784;
	case 6:
		return 880;
	case 7:
		return 988;
		/*��������:-1,-2,-3,-4,-5,-6,-7*/
	case -1:
		return 262;
	case -2:
		return 294;
	case -3:
		return 330;
	case -4:
		return 349;
	case -5:
		return 392;
	case -6:
		return 440;
	case -7:
		return 494;
		/*��������:11,12,13,14,15,16,17*/
	case 11:
		return 1047;
	case 12:
		return 1175;
	case 13:
		return 1319;
	case 14:
		return 1397;
	case 15:
		return 1568;
	case 16:
		return 1760;
	case 17:
		return 1976;
		/*����:0,���Ϸ���ֵ*/
	default:
		return 0;
	}
}

/*���ࡶС���ǡ�*/
void play_xiaoxingxing(void)
{
	int i;
	int _xiaoxingxing[48]= {
		1,1,5,5,6,6,5,0,
		4,4,3,3,2,2,1,0,
		5,5,4,4,3,3,2,0,
		5,5,4,4,3,3,2,0,
		1,1,5,5,6,6,5,0,
		4,4,3,3,2,2,1,0
	};//С��������
	int notation_frequency(int t);
	printf("������������С���ǡ�����\n");
	Beep(0,1000);//��ͣһ����
	for (i=0; i<=47; i++) {
		if(_xiaoxingxing[i]==0) printf("\n");
		else printf("%d",_xiaoxingxing[i]);
		Beep(notation_frequency(_xiaoxingxing[i]),1000);
	}
	printf("������ϣ�лл���ͣ�\n");
}

/*���ࡶ���򻨡�*/
void play_molihua(void)
{
	int i,t;
	int _molihua[72]= {
		3,3,5,6,11,11,6,5,0,
		5,6,5,0,
		3,3,5,6,11,11,6,5,0,
		5,6,5,0,
		5,5,5,3,5,6,0,
		6,6,5,0,
		3,2,3,5,0,
		3,2,1,0,
		1,2,1,0,
		3,2,1,2,0,
		3,5,6,11,6,5,0,
		5,2,3,5,3,2,1,2,1,0
	};//��������
	int notation_frequency(int t);
	printf("���������������򻨡�����\n");
	Beep(0,1000);//��ͣһ����
	for (i=0; i<=71; i++) {
		t=_molihua[i];
		if(t<0) t=-t;
		t=t%10;
		if(t==0) printf("\n");
		else printf("%d",t);
		Beep(notation_frequency(_molihua[i]),1000);
	}
	printf("������ϣ�лл���ͣ�\n");
}

/*���ࡶ�����ѡ�*/
void play_zhaopengyou(void)
{
	int i,t;
	int _zhaopengyou[32]= {
		5,6,5,6,5,6,5,0,
		5,11,7,6,5,5,3,0,
		5,5,3,3,5,5,3,0,
		2,4,3,2,1,2,1,0,
	};//����������
	int notation_frequency(int t);
	printf("�����������������ѡ�����\n");
	Beep(0,1000);//��ͣһ����
	for (i=0; i<=31; i++) {
		t=_zhaopengyou[i];
		if(t<0) t=-t;
		t=t%10;
		if(t==0) printf("\n");
		else printf("%d",t);
		Beep(notation_frequency(_zhaopengyou[i]),1000);
	}
	printf("������ϣ�лл���ͣ�\n");
}

/*���ࡶ��ѧ�衷*/
void play_shangxuege(void)
{
	int i,t;
	int _shangxuege[30]= {
		1,2,3,1,5,0,
		6,6,11,6,5,0,
		6,6,11,0,
		5,6,3,0,
		6,5,3,5,3,1,2,3,1,0
	};//����������
	int notation_frequency(int t);
	printf("��������������ѧ�衷����\n");
	Beep(0,1000);//��ͣһ����
	for (i=0; i<=29; i++) {
		t=_shangxuege[i];
		if(t<0) t=-t;
		t=t%10;
		if(t==0) printf("\n");
		else printf("%d",t);
		Beep(notation_frequency(_shangxuege[i]),1000);
	}
	printf("������ϣ�лл���ͣ�\n");
}

/*���ࡶһ��Ǯ��*/
void play_yifenqian(void)
{
	int i,t;
	int _yifenqian[52]= {
		5,11,6,11,5,0,
		3,5,2,3,5,0,
		3,5,6,11,5,6,5,3,5,1,0,
		3,2,0,
		3,2,1,2,3, 0,
		6,5,3,5,6,0,
		5,11,11,6,5,6,3,0,
		5,2,3,2,1,0
	};//����������
	int notation_frequency(int t);
	printf("������������һ��Ǯ������\n");
	Beep(0,1000);//��ͣһ����
	for (i=0; i<=51; i++) {
		t=_yifenqian[i];
		if(t<0) t=-t;
		t=t%10;
		if(t==0) printf("\n");
		else printf("%d",t);
		Beep(notation_frequency(_yifenqian[i]),1000);
	}
	printf("������ϣ�лл���ͣ�\n");
}

/*���ࡶ������*/
void play_zhengfu(void)
{
	int i,t;
	int _zhengfu[33]= {
		5,11,7,5,5,6,5,0,
		5,11,7,5,6,3,6,0,
		6,6,6,5,3,3,4,0,
		4,4,4,5,6,3,2,2,0,
	};//��������
	int notation_frequency(int t);
	printf("����������������������\n");
	Beep(0,1000);//��ͣһ����
	for (i=0; i<=32; i++) {
		t=_zhengfu[i];
		if(t<0) t=-t;
		t=t%10;
		if(t==0) printf("\n");
		else printf("%d",t);
		Beep(notation_frequency(_zhengfu[i]),1000);
	}
	printf("������ϣ�лл���ͣ�\n");
}

/*���ࡶ�׺�һ��Ц��*/
void play_canghaiyishengxiao(void)
{
	int i,t;
	int _canghaiyishengxiao[31]= {
		12,12,1,6,5,4,0,
		6,5,4,2,1,0,
		1,2,1,2,4,4,5,6,11,0,
		12,12,11,6,5,4,5,0
	};//�׺�һ��Ц����
	int notation_frequency(int t);
	printf("�������������׺�һ��Ц������\n");
	Beep(0,1000);//��ͣһ����
	for (i=0; i<=30; i++) {
		t=_canghaiyishengxiao[i];
		if(t<0) t=-t;
		t=t%10;
		if(t==0) printf("\n");
		else printf("%d",t);
		Beep(notation_frequency(_canghaiyishengxiao[i]),1000);
	}
	printf("������ϣ�лл���ͣ�\n");
}
/*���ࡶͯ����*/
void play_tonghua(void)
{
	int i,t;
	int _tonghua[46]= {
		5,4,3,0,
		3,4,3,0,
		3,4,3,4,3,2,1,0,
		1,3,5,6,0,
		6,6,5,2,2,4,3,0,
		1,3,5,6,0,
		6,6,7,6,5,4,3,4,3,2,1,0,
	};//ͯ������
	int notation_frequency(int t);
	printf("������������ͯ��������\n");
	Beep(0,1000);//��ͣһ����
	for (i=0; i<=45; i++) {
		t=_tonghua[i];
		if(t<0) t=-t;
		t=t%10;
		if(t==0) printf("\n");
		else printf("%d",t);
		Beep(notation_frequency(_tonghua[i]),1000);
	}
	printf("������ϣ�лл���ͣ�\n");
}
/*���ࡶͬ�����㡷*/
void play_tongzhuodeni(void)
{
	int i,t;
	int _tongzhuodeni[71]= {
		5,5,5,5,3,4,5,7,0,
		6,6,6,6,4,6,5,0,
		5,5,5,5,7,6,5,4,0,
		4,4,4,4,3,2,1,0,
		11,11,11,11,5,6,11,11,11,11,0,
		12,12,12,12,11,7,6,0,
		7,7,7,7,7,11,12,0,
		5,0,
		7,7,11,12,11,7,11,0,
	};//ͬ����������
	int notation_frequency(int t);
	printf("������������ͬ�����㡷����\n");
	Beep(0,1000);//��ͣһ����
	for (i=0; i<=70; i++) {
		t=_tongzhuodeni[i];
		if(t<0) t=-t;
		t=t%10;
		if(t==0) printf("\n");
		else printf("%d",t);
		Beep(notation_frequency(_tongzhuodeni[i]),1000);
	}
	printf("������ϣ�лл���ͣ�\n");
}
/*���ࡶС�ܺ������ޡ�*/
void play_xiaoxiongheyangwawa(void)
{
	int i,t;
	int _xiaoxiongheyangwawa[77]= {
		1,0,
		2,3,4,5,5,5,4,3,4,4,4,3,2,1,3,5,1,0,
		2,3,4,5,5,5,4,3,4,4,4,3,2,1,3,1,6,0,
		6,6,5,4,5,5,5,4,3,4,4,4,3,2,1,3,5,6,0,
		6,6,5,4,5,5,5,4,3,4,0,
		4,4,3,2,1,0,
		3,1,0,
	};//С�ܺ�����������
	int notation_frequency(int t);
	printf("������������С�ܺ������ޡ�����\n");
	Beep(0,1000);//��ͣһ����
	for (i=0; i<=76; i++) {
		t=_xiaoxiongheyangwawa[i];
		if(t<0) t=-t;
		t=t%10;
		if(t==0) printf("\n");
		else printf("%d",t);
		Beep(notation_frequency(_xiaoxiongheyangwawa[i]),1000);
	}
	printf("������ϣ�лл���ͣ�\n");
}