#include <iostream>
#include "app/app.h"

using namespace std;

int main(int argc, char const *argv[]) {
    (new app())->start(argc, argv);
    return 0;
}
