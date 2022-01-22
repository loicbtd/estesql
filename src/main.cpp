#include <iostream>
#include <filesystem>

using namespace std;
using namespace filesystem;


int main(int argc, char const *argv[]) {

    cout << "Hello World !" << endl;
    filesystem:: create_directories("directory");

    return 0;

}
