
#include <stdlib.h>

#include <mysql/mysql.h>

#include "sql.h"
#include "cfgfile.h"


void * sql_create()
{
	MYSQL *mysql;
	char *dbserv;
	char *dbuser;
	char *dbpass;
	char *dbname;

	dbserv = cfg_find("sql.host");
	dbuser = cfg_find("sql.user");
	dbpass = cfg_find("sql.pass");
	dbname = cfg_find("sql.database");

	mysql = mysql_init(NULL);

	if ( !mysql_real_connect(mysql, dbserv, dbuser, dbpass, dbname,
		0, NULL, 0) ) {
		/* Failed to connect to the MySQL server */
		mysql_close(mysql);
		return NULL;
	}

	return mysql;
}

void sql_close(void *sql)
{
	if (sql) {
		mysql_close((MYSQL *)sql);
	}
}

int sql_query(void *sql, char *query, void **res)
{
	int err;

	err = mysql_query((MYSQL *)sql, query);
	if (err) return err;

	if (res) {
		*res = mysql_store_result((MYSQL *)sql);
	}

	return 0;
}

char **sql_fetch_result(void *res)
{
	return mysql_fetch_row((MYSQL_RES *)res);
}

void sql_free_result(void *res)
{
	if (!res) return;

	mysql_free_result((MYSQL_RES *)res);
}
