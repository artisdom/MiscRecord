#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<gdbm.h>
#include<stdio.h>
#include<ctype.h>

#define DB_FILE_BLOCK "book_data"
#define ISBN_MAX 13
#define AUTHOR_MAX 50
#define TITLE_MAX 50
#define FILED_MAX 50        /*���������� */

typedef struct {
	char isbn[ISBN_MAX + 1];
	char author[AUTHOR_MAX + 1];
	char title[TITLE_MAX + 1];
	int numb;
} book_entry;

char *str_con(char *input, int len)
{
	int count = 0;
	do {
		input[count] = tolower(input[count]);
		count++;
	} while (count <= len);
	return input;
}

int main()
{
	GDBM_FILE dbm_ptr;
	datum key, data;
	book_entry vbook, sbook;/*vbook�洢���ݿ��е�ԭʼ��¼��sbook��ת����Сд�Ժ��*/
	char keyword[FILED_MAX];
	printf("������һ���ؼ��ֿ�ʼģ����ѯ:");
	scanf("%s",keyword);
	dbm_ptr = gdbm_open(DB_FILE_BLOCK, 0, GDBM_READER, 0, NULL);
	for (key = gdbm_firstkey(dbm_ptr); key.dptr;
	        key = gdbm_nextkey(dbm_ptr, key)) {
		data = gdbm_fetch(dbm_ptr, key);
		memcpy(&sbook, data.dptr, data.dsize);
		memcpy(&vbook, data.dptr, data.dsize);
		strcpy(keyword, str_con(keyword, FILED_MAX));
		strcpy(sbook.isbn, str_con(sbook.isbn, ISBN_MAX));
		strcpy(sbook.title, str_con(sbook.title, TITLE_MAX));
		strcpy(sbook.author, str_con(sbook.author, AUTHOR_MAX));
		if ((strstr(sbook.isbn, keyword) || strstr(sbook.title, keyword)
		        || strstr(sbook.author, keyword))) {
			printf("%s\t%s\t%s\t%d\n", vbook.isbn, vbook.author,
			       vbook.title, vbook.numb);
		} else {
			printf("���޼�¼\n");
		}
		gdbm_close(dbm_ptr);

	}
	return 0;
}