#include<gdbm.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/stat.h>
#include<string.h>

#define ISBN_MAX 13
#define AUTHOR_MAX 50
#define TITLE_MAX 50
#define DB_FILE_BLOCK "book_data"

typedef struct {        /*����ͼ��ṹ�� */
	char isbn[ISBN_MAX + 1];
	char author[AUTHOR_MAX + 1];
	char title[TITLE_MAX + 1];
	int numb;
} book_entry;

int main()
{
	book_entry newbook; /*�����µ�ͼ���¼������ֵ */
	memset(&newbook, '\0', sizeof(newbook));
	strncpy(newbook.isbn, "9787302184942", ISBN_MAX);
	strncpy(newbook.author, "Microsoft Research Asia", AUTHOR_MAX);
	strncpy(newbook.title, "Microsoft's Dream Works", TITLE_MAX);
	newbook.numb = 735;

	datum key, data;    /*datum�ṹ����������Ա��dptrָ��洢�����ݣ�dsize��¼���ݵĴ�С */
	key.dptr = (char *)newbook.isbn;    /*��ISBN��key */
	key.dsize = ISBN_MAX;
	data.dptr = (char *)&newbook;   /*���������ݼ�¼��value */
	data.dsize = sizeof(newbook);

	GDBM_FILE dbm_ptr;
	/*�����ݿ⣨�����ļ������ƣ����������ݿ��� */
	dbm_ptr = gdbm_open(DB_FILE_BLOCK,  /*�ļ��� */
	                    0,  /*�ļ���С����Ϊ0ʱGDBM��ʹ���ļ�ϵͳ��ͳ�ƿ��С */
	                    GDBM_WRCREAT,   /*��дģʽ��WRCREAT��д�����ݿ��ļ�������ʱ������READER����WRITERд */
	                    S_IRUSR | S_IWUSR,  /*Ȩ�ޱ�־λ */
	                    NULL    /*����ʱ�Ŀղ����ص����� */
	                   );
	/*�Ѽ�¼�������ݿ� */
	gdbm_store(dbm_ptr, /*���ݿ��� */
	           key,     /*keyֵ */
	           data,    /*valueֵ */
	           GDBM_REPLACE /*�����GDBM_INSERT������ظ���¼�����GDBM����REPLACE��ֻ�Ǹ���ԭ�ȴ��ڵ���ͬ��¼ */
	          );

	char isbnarr[ISBN_MAX + 1] = { 0 };
	char *isbn = isbnarr;
	puts("��������Ҫ��ѯͼ���ISBN��:");
	scanf("%s",isbn);
	key.dptr = (char *)isbn;
	key.dsize = ISBN_MAX;
	/*���ݿ��ѯ */
	data = gdbm_fetch(dbm_ptr, key);    /*�ν������ݿ�����keyֵ */
	if (data.dsize == 0)
		printf("���޽��\n");
	else {
		memset(&newbook, 0, sizeof(newbook));
		memcpy(&newbook, data.dptr, data.dsize);    /*�������ݿ�����ļ�¼����book_entry�ṹ�� */
		printf("%s\t%s\t%s\t%d\n", newbook.isbn, newbook.author,
		       newbook.title, newbook.numb);
	}

	/*�ر����ݿ� */
	gdbm_close(dbm_ptr);
}