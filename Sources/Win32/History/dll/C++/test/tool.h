// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� TOOL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// TOOL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef TOOL_EXPORTS
#define TOOL_API  /**extern "C"*/ __declspec(dllexport)
#else
#define TOOL_API /**extern "C"*/ //__declspec(dllimport)
#endif

//ɾ��tool.def�ļ�����Ŀ=������=��������=������=��ģ�鶨���ļ�
// �����Ǵ� tool.dll ������
class TOOL_API Ctool {
public:
	Ctool(void);
	
	//���Ե����������еĺ���,��������������publicȨ�ޣ��ſ��Ը������������
	/**TOOL_API*/ int sub(int a,int b);
	int div(int a,int b);
};

extern TOOL_API int ntool;

TOOL_API int /**_stdcall */ fntool(void);//��������޸ĵ���Լ��������_stdcall(WINAPI),pascal,__cdecl __fastcall

TOOL_API int   add(int a,int b);

TOOL_API int mul(int a,int b);

extern "C" TOOL_API Ctool* GetCTool(); //��ȡ��TestDll�Ķ���
