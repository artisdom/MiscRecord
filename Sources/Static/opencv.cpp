#include "cv.h"
#include "highgui.h"

#define SHAPE_LINE 1
#define SHAPE_ERASER 2

int g_style;
CvRect rect;

CvPoint g_StartPoint;
CvPoint g_EndPoint;
CvPoint p_Start;       //��¼���λ�����Ϸ���
CvPoint p_End;          //��¼���λ�����·���
bool drawing=false;       //�Ƿ��ڻ�ͼ״̬
bool erasering=false;    //�Ƿ��ڲ���״̬

void callback(int event,int x,int y,int flags,void* param);
void DrawLine(IplImage* img);
//���׻�ͼ���ߣ�ʵ���˻��ߺ���Ƥ�����ܣ���ͼ���ܻ��д��������
int main(int argc,char** argv)
{
	IplImage* img=cvCreateImage(cvSize(512,512),IPL_DEPTH_8U,3);
	cvSet(img,cvScalar(255,255,255));

	IplImage* temp=cvCloneImage(img);
	cvCopy(img,temp);

	cvNamedWindow("���׻�ͼ����");

	cvSetMouseCallback("���׻�ͼ����",callback,img);
	printf("�����Ҫѡ��ִ�еĲ���:��l�����������ߡ�,��e����������Ƥ��\n");
	char select='l';

	while(1) {
		cvCopyImage(img,temp);      //ʼ����ԭͼimage�ϻ����(������¼���)���Ƚ�image���Ƹ�temp,Ȼ������ʱͼtemp������ͼ�Ĺ���(��main�����л�����ͼ��),Ȼ����temp����ʾͼ��
		switch(select) {
		case 'l':
			g_style=SHAPE_LINE;
			break;
		case 'e':
			g_style=SHAPE_ERASER;
			break;
		case 27:
			return 0;
		}
		if(g_style==SHAPE_LINE&&drawing)     //������ڰ�ס�ƶ������л���
			cvDrawLine(temp,g_StartPoint,g_EndPoint,cvScalar(0,0,0));
		if(g_style==SHAPE_ERASER) {
			cvRectangle(temp,p_Start,p_End,cvScalar(0,0,0));  //������Ƥ���α߿�
		}
		cvShowImage("���׻�ͼ����",temp);
		select=cvWaitKey(30);
	}
	cvReleaseImage(&img);
	cvReleaseImage(&temp);
	cvDestroyWindow("���׻�ͼ����");
	return 0;
}

void callback(int event,int x,int y,int flags,void* param)
{
	IplImage* img=(IplImage*)param;

	switch(event) {
	case CV_EVENT_LBUTTONDOWN: {
		if(SHAPE_LINE==g_style) {
			drawing=true;
			g_StartPoint=cvPoint(x,y);
			g_EndPoint=g_StartPoint;   //�˴����յ�������Ϊͬ��ʼ������סǰһ��ֱ�ߵ��յ�����
		}
		if(SHAPE_ERASER==g_style) {
			erasering=true;
			//ע��߽�����Ҫ�ʵ��޸�ROI��Ч����
			rect.x=x-20;
			rect.y=y-20;      //ע������ļ���,һ��ԭ���ڴ��ڵ����Ͻ�(��Ͳ���ϵͳ�������й�,IplImage�ṹ���и�origin���Կ�������ͼ���ԭ��)
			rect.width=40;
			rect.height=40;
			p_Start.x=x-20;
			p_Start.y=y-20;
			p_End.x=x+20;
			p_End.y=y+20;
			if(x>-20&&x<532&&y>-20&&y<532) {
				cvSetImageROI(img,rect);
				cvSet(img,cvScalar(255,255,255));
				cvResetImageROI(img);
			}
		}
	}
	break;
	case CV_EVENT_MOUSEMOVE: {
		p_Start.x=x-20;
		p_Start.y=y-20;      //��ʱ��λ���λ�û���Ƥ����
		p_End.x=x+20;
		p_End.y=y+20;
		if(SHAPE_LINE==g_style) {
			if(drawing) {
				g_EndPoint=cvPoint(x,y);
			}
		}

		if(SHAPE_ERASER==g_style) {
			rect.x=x-20;
			rect.y=y-20;
			rect.width=40;
			rect.height=40;
			if(erasering) {
				if(x>-20&&x<532&&y>-20&&y<532) {
					cvSetImageROI(img,rect);
					cvSet(img,cvScalar(255,255,255));
					cvResetImageROI(img);
				}
			}
		}

	}
	break;
	case CV_EVENT_LBUTTONUP: {
		if(SHAPE_LINE==g_style) {
			drawing=false;
			cvDrawLine(img,g_StartPoint,g_EndPoint,cvScalar(255,0,0));  //(255,0,0)�˴�����������ɫ,��BGR
		}

		if(SHAPE_ERASER==g_style) {
			erasering=false;
		}
	}
	}
}