#include "file_set_up.h"

void file_set_up::set_up_source_file(const string& source_file) {

    definition_file::get_instance()->set_current_table_name(source_file);
    content_file::get_instance()->set_current_table_name(source_file);
    index_file::get_instance()->set_current_table_name(source_file);
    key_file::get_instance()->set_current_table_name(source_file);

}
