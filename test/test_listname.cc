#include <cstdio>
#include <ssandbox/utils/listfile.h>
using namespace std;

int main() {
    ssandbox::io::list_file_reader r("test.list");
    auto res = r.read();
    for (auto x : res)
        printf("'%s'\n", x.c_str());
    return 0;
}