#include <iostream>
#include <fstream>
#include "dependency_check.h"

using namespace std;
using namespace boost::filesystem;

int main()
{
    std::ifstream input("main.cpp");

    vector<string> inc_std, inc_cur;

    get_includes_from(input, inc_std, inc_cur);
    auto && paths_cur = make_abs_path(inc_cur, current_path());
    auto && paths_std = make_abs_path(inc_std, path(""));
    for (auto p : paths_cur)
        cout << p.generic_string() << endl;
    for (auto p : paths_std)
        cout << p.generic_string() << endl;

    return 0;
}
