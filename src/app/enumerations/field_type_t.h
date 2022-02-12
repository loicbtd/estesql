#ifndef ESTESQL_FIELD_TYPE_T_H
#define ESTESQL_FIELD_TYPE_T_H

enum field_type_t {
    PRIMARY_KEY = 1,
    INT = 2,
    FLOAT = 3,
    TEXT = 4,
};

static const char *enum_field_type_str[] =
        { "int", "float", "text", "primary_key" };

#endif //ESTESQL_FIELD_TYPE_T_H
