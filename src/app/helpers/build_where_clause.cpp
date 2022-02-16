#include "build_where_clause.h"

where_clause build_where_clause::build_where(const string& query, const string& syntaxe_exception, const vector<string>& columns_name_from_file) {

    where_clause where_clause_result;

    smatch smatch_where;
    string where_regex("where [a-z0-9_-]+( )?(<=|>=|=|<>|>|<)( )?[a-z0-9_-]+( (and|or) [a-z0-9_-]+( )?(<=|>=|=|<>|>|<)( )?[a-z0-9_-]+)*");
    regex_search(query, smatch_where, regex(where_regex));
    string where_str = smatch_where[0];

    where_str = string_utilities::erase_substring(where_str, "where ");

    int occurrences_and = 0;
    string::size_type pos = 0;
    string target_and = "and";
    while ((pos = where_str.find(target_and, pos )) != string::npos) {
        ++occurrences_and;
        pos += target_and.length();
    }

    int occurrences_or = 0;
    pos = 0;
    string target_or = "or";
    while ((pos = where_str.find(target_or, pos )) != string::npos) {
        ++occurrences_or;
        pos += target_or.length();
    }

    if ((occurrences_and != 0) && (occurrences_or != 0)) {
        throw slq_invalid_syntax_exception(syntaxe_exception);
    }

    if (occurrences_or != 0) {
        where_clause_result.set_type("or");
    } else {
        where_clause_result.set_type("and");
    }

    vector<pair<string, vector<string>>> elements;

    int iterator_int=1;
    smatch match_boolean_clause;
    string rgx_where_boolean_clause = "[a-z0-9_-]+( )?(<=|>=|=|<>|>|<)( )?[a-z0-9_-]+";
    while (regex_search(where_str, match_boolean_clause, regex(rgx_where_boolean_clause))) {
        string boolean_clause_str = match_boolean_clause.str(0);

        boolean_clause_str = string_utilities::erase_substring(boolean_clause_str, " ");
        smatch match_operator;
        string operators = "(<=|>=|=|<>|>|<)";
        regex_search(boolean_clause_str, match_operator, regex(operators));
        string op = match_operator.str(0);

        boolean_clause_str = regex_replace(boolean_clause_str, regex(match_operator.str(0)), " ");
        vector<string> elem = string_utilities::convert_string_to_vector_delimiter(boolean_clause_str, SPACE_DELIMITER);

        elements.emplace_back(op, elem);

        iterator_int++;

        // suffix to find the rest of the string.
        where_str = match_boolean_clause.suffix().str();
    }

    // check column_names of where clause
    for (const auto & element : elements){
//        cout << element.first.c_str() << " | " << element.second.at(0) << endl;
        if (!(std::find(columns_name_from_file.begin(), columns_name_from_file.end(), element.second.at(0)) != columns_name_from_file.end())) {
            throw column_non_existing_exception();
        }
    }

    where_clause_result.set_elements(elements);

    return where_clause_result;

}