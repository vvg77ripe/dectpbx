
void * sql_create();
void sql_close(void *sql);

int sql_query(void *sql, char *query, void **res);
char **sql_fetch_result(void *res);
void sql_free_result(void *res);
