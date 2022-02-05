#ifndef ESTESQL_SYNTAX_QUERY_H
#define ESTESQL_SYNTAX_QUERY_H

#define CREATE_TABLE_SYNTAX "Error: Invalid SQL syntax\nCREATE TABLE table_name(column_name TYPE,column_name TYPE,column_name TYPE,...);\nTYPE is long long(int), unsigned long long(primary key), double(float) or string(string_size)\n"
#define CREATE_DB_SYNTAX "Error: Invalid SQL syntax\nCREATE DATABASE|DB database_name;"

#define DROP_TABLE_SYNTAX "Error: Invalid SQL syntax\DROP TABLE table_name;"
#define DROP_DB_SYNTAX "Error: Invalid SQL syntax\DROP DATABASE|DB database_name;"

#endif //ESTESQL_SYNTAX_QUERY_H
