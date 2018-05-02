#ifndef _csinDB_20140528_h
#define _csinDB_20140528_h

#include <sqlite3.h>
#include <stdio.h>

//���ݿⵥ��
class CSinDB
{
public:
	static CSinDB *GetSinDB();
	int DoOpera(const char *sql,sqlite3_callback CallBack, void *);
	char *GetErrmsg();
protected:
private:
	CSinDB(const char *,sqlite3 **db);
	~CSinDB();

	static CSinDB *pSinDB;

	char *errmsg;
	static sqlite3 *db;


	friend class CGarbo;
};


//����������
class CGarbo
{
public:
	 static CGarbo cGar;
	
	~CGarbo();

protected:
private:
};

#endif