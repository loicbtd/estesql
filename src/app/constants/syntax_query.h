#ifndef ESTESQL_SYNTAX_QUERY_H
#define ESTESQL_SYNTAX_QUERY_H

#define CREATE_TABLE_SYNTAX "Error: Invalid SQL syntax\nCREATE TABLE table_name(column_name TYPE,column_name TYPE,column_name TYPE,...);\nTYPE is long long(int), unsigned long long(primary key), double(float) or string(string_size)\n"
#define CREATE_DB_SYNTAX "Error: Invalid SQL syntax\nCREATE DATABASE|DB database_name;"

#define DROP_TABLE_SYNTAX "Error: Invalid SQL syntax\nDROP TABLE table_name;"
#define DROP_DB_SYNTAX "Error: Invalid SQL syntax\nDROP DATABASE|DB database_name;"

#define SELECT_SYNTAX "Error: Invalid SQL syntax\nSELECT *|column_x,column_y FROM table_name [WHERE column_x >|<|<=|>=|=|<> column_y AND|OR column_x >|<|<=|>=|=|<> column_y]\nWarning: Use only AND or only OR in a single where clause"
#define INSERT_SYNTAX "Error: Invalid SQL syntax\nINSERT INTO table_name(column_x, column_y) VALUES (value_column_x, value_column_y)"
#define UPDATE_SYNTAX "Error: Invalid SQL syntax\nUPDATE table_name SET(column_x=new_value_column_x, column_y=new_value_column_y) [WHERE column_x >|<|<=|>=|=|<> column_y AND|OR column_x >|<|<=|>=|=|<> column_y]\nWarning: Use only AND or only OR in a single where clause"

#endif //ESTESQL_SYNTAX_QUERY_H
