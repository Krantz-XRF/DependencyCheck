#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <boost/filesystem.hpp>

// 从给定的输入流中读取 C++ 代码, 并提取全部的 #include 包含的文件名
void get_includes_from(
    std::istream & input,
    std::vector<std::string> & output_std_header,
    std::vector<std::string> & output_cur_header
);
// 用给定的根目录来把所有输入中的相对路径变成绝对路径
std::vector<boost::filesystem::path>
    make_abs_path(const std::vector<std::string> & dirs, const boost::filesystem::path & base);
// 根据目标文件和依赖文件, 决定目标是否过期
bool is_up_to_date(const std::vector<boost::filesystem::path> & dep, const boost::filesystem::path & targ);
