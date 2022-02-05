#include "table_file.h"

const string &table_file::getSourceFile() const {
    return source_file;
}

void table_file::setSourceFile(const string &sourceFile) {
    source_file = sourceFile;
}
