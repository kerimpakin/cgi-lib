#ifndef CMSQL_H_
#define CMSQL_H_ 1

#include <libpq-fe.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <cmstdio.h>
//g++ main.cc -lpq -D__POSIX__ -I/usr/include/pgsql

inline char *make_sql_string_variable(int i)
{
	char str[20];
	
	memset(str, 0, sizeof str);
	
	sprintf(str, "'%l'", (int )i);
	
	return str;
	
}

inline char *make_sql_string_variable(char *sqlvar)
{
	
	#define QUOTATION_LEN 2
	#define NULL_LEN 1
	char *tmp_s;
	char *new_sqlvar;
	
	sqlvar = strrep(sqlvar, "'", "''");
	
	tmp_s = sqlvar;
	
	sqlvar = strrep(sqlvar, "\\", "\\\\");
	
	free(tmp_s);
	
	new_sqlvar = (char *)malloc(sizeof(char) * strlen(sqlvar) + QUOTATION_LEN  + NULL_LEN);	
	
	sprintf(new_sqlvar,"'%s'",sqlvar);
	
	return new_sqlvar;

}

char *make_sql_boolean_variable(char *sqlvar)
{

	if( !strcmp(sqlvar, "0") )
		return "FALSE";
	else return "TRUE";
}

char *make_sql_sentences(char *word = NULL , char *extn = "", bool clear = 0){
	
	#define SPACE_LEN 1
	#define NULL_LEN 1
	
	
	char *tmp;
	int old_len;
	static int len;
	static char *word_alloc;
	
	/* 
	 * resetting our functions 
	 * static variables 
	 */

	if( clear ) {
		len = 0;
		free(word_alloc);
		return word_alloc = NULL;
	}
		
	
	old_len = len;
				
	if( word_alloc != NULL && word != NULL )
		len += strlen(word_alloc) + strlen(word) + strlen(extn) + SPACE_LEN + NULL_LEN;
	else if( word != NULL ){
		
		len += strlen(word) + strlen(extn) + SPACE_LEN + NULL_LEN;
	}else	return word_alloc;
		
	tmp = (char *) malloc(sizeof(char) * len);
	
	if( tmp == NULL ){
		len = old_len;
		return word_alloc;
	}
	
	if( word_alloc == NULL )//for null bug
		word_alloc = "";
	
	sprintf(tmp ,"%s %s%s", word_alloc, word, extn);
	
	//free(word_alloc);
	
	word_alloc = tmp;
	
	return word_alloc;
	
}

inline char *make_sql_sentences(int num, char *extn = "")
{	
	#define _WORD_SIZE 10
	char word[_WORD_SIZE];
	snprintf(word, _WORD_SIZE, "%d", num);
	make_sql_sentences(word, extn);
	#undef _WORD_SIZE
}

class CMPGSQL{
	
	private:
	
		PGconn *conn;
		PGresult *res;
	
		int cmerror;
		int cursor;
		int rowlen;
		int fieldlen;
		char *cmdrowstr;
		int cmdrow;//number of rows affected by INSERT,UPDATE,DELETE
		char *dbname;
		char *conn_str;
		
	public:
	
	CMPGSQL(char *connection_str){
		
		cursor = 0;
		
		conn_str = connection_str;
		
		this->cmerror = 0;
		
		conn = PQconnectdb(connection_str);
		
		if( conn == NULL)
			this->cmerror = -1;
			
	}
	
	CMPGSQL(char *connection_str, char *sql_clause){
		
		cursor = 0;//Setting up our cursor position beginning
		
		conn_str = connection_str;
		
		this->cmerror = 0;
		
		conn = PQconnectdb(connection_str);
		
		if( conn == NULL )
			this->cmerror = -1;		
		
		res = PQexec(conn, sql_clause);
		
		dbname = PQdb(conn);
		
		rowlen = PQntuples(res);
		
		fieldlen = PQnfields(res);
		
		cmdrowstr = PQcmdTuples(res);
		
		if( strcmp(cmdrowstr,"") )
			cmdrow = atoi(cmdrowstr);
		else	cmdrow = 0;
		
		
	}
	
	int SQLExec(char *sql_clause){
		
		PQclear(res);
		
		cursor = 0;
		
		res = PQexec(conn, sql_clause);
		
		dbname = PQdb(conn);
		
		rowlen = PQntuples(res);
		
		fieldlen = PQnfields(res);
		
		cmdrowstr = PQcmdTuples(res);
		
		if( strcmp(cmdrowstr, "") )
			cmdrow = atoi(cmdrowstr);
		else	cmdrow = 0;
		
		return cmdrow;
	}
	
	~CMPGSQL(){  PQclear(res); PQfinish(conn); }
	
	inline int RowLen(){  return PQntuples(res);}
	
	inline int TupleLen(){ return PQntuples(res); }
	
	inline int FieldLen(){ return PQnfields(res); }
	
	inline char *Value(char *fieldname){ return PQgetvalue(res, cursor, PQfnumber(res, fieldname) );}
	
	int SetCursorPosition(int pos){ if( pos < 0 && pos > rowlen ) return 0;  return cursor = pos; }
	
	int EOD(){ if( rowlen == cursor ) {return 0L;} return 1L;}
	
	int BOD(){ if( cursor == 0 ) return cursor = 0; return 1; }
	
	void MoveNext(){ if( cursor < rowlen )cursor++; }
	
	void MovePrevious(){ if( cursor >= 0  ) cursor--; }
	
	inline void MoveLast(){ cursor = --rowlen; }

	inline void MoveFirst(){ cursor = 0; }
	
	inline int IsBinary(){ return PQbinaryTuples(res); }
	
	inline int CmdRows(){ return cmdrow; }
	
	inline int CmdTuples(){ return cmdrow; }
	
	char *DBName(){ return dbname; }
	
	
};

#endif /* CMSQL_H_ */
