#include "CSinDB.h"
CSinDB * CSinDB::pSinDB=NULL;
sqlite3 *CSinDB::db=NULL;


//��Ϊһ������ֻ��һ�����ݿ⣬���Կ���д��
CSinDB::CSinDB(const char *acName,sqlite3 **d)
{
	int iResult =sqlite3_open(acName,d);
	if (iResult==SQLITE_OK)
	{
		//printf("open successs\n");
	}
	else
	{
		printf("%s",sqlite3_errmsg(db));
	}
}
CSinDB::~CSinDB()
{
	sqlite3_close(CSinDB::db);

}


//����ֻ���һ��ʵ��
CSinDB *CSinDB::GetSinDB()
{
	if (CSinDB::pSinDB==NULL)
	{
		CSinDB::pSinDB=new CSinDB("mydb",&CSinDB::db);
	}
//	printf("get singledb");
	return CSinDB::pSinDB;
}

int CSinDB::DoOpera(const char *sql, sqlite3_callback CallBack, void *canshu)
{
		int i;
		i=sqlite3_exec(db,sql,CallBack,canshu,&errmsg);
		return i;
}
char *CSinDB::GetErrmsg()
{
	return errmsg;
}


////////////////////
CGarbo::~CGarbo()
	{
	if (CSinDB::pSinDB!=NULL)
		{
		delete CSinDB::pSinDB;
	//	printf("xigou");
		}
	}