#include "dependency_check.h"
#include <cctype>
#include <regex>

using namespace boost::filesystem;
using namespace std;

// 从给定的输入流中读取 C++ 代码, 并提取全部的 #include 包含的文件名
void get_includes_from(
    istream & input,
    vector<string> & output_std_header,
    vector<string> & output_cur_header
) {
    // 用于匹配的正则表达式
    static const regex
        // 匹配引号型的 include 指令
        inc_cur_pat(R"regex(\s*#\s*include\s*"([^":\*\?<>|]+)".*)regex"),
        // 匹配尖括号型的 include 指令
        inc_std_pat(R"regex(\s*#\s*include\s*<([^":\*\?<>|]+)>.*)regex"),
        // 匹配注释的开始
        comment_beg(R"regex([^/]*/\*.*)regex"),
        // 匹配注释的结束, 用括号括起来的部分可能含有一个 include 指令
        comment_end(R"regex([^\*]*\*/(.*))regex");

    // 行的缓冲区, 结果缓冲区
    string line;
    smatch res;

    bool in_block_comment = false;

    while (getline(input, line))
    {
        if (in_block_comment)
        {
            // 匹配到注释结尾, 就退出注释块
            if (regex_match(line, res, comment_end))
            {
                in_block_comment = false;
                // 把注释部分去掉, 留下可能还含有指令的部分
                line = regex_replace(line, comment_end, "$1");
            }
            // 忽略注释中的一切行
            else
                continue;
        }

        bool success = regex_match(line, res, inc_std_pat);
        // 匹配成功, res 中的下标为 1 的元素是头文件名
        if (success)
            output_std_header.push_back(res[1]);
        else
        {
            success = regex_match(line, res, inc_cur_pat);
            if (success)
                output_cur_header.push_back(res[1]);
        }

        // 尝试匹配一个注释开头
        if (regex_match(line, res, comment_beg))
            in_block_comment = true;
    }
}

// 用给定的根目录来把所有输入中的相对路径变成绝对路径
vector<path> make_abs_path(const vector<string> & dirs, const path & base)
{
    vector<path> res;

    for (auto & d : dirs)
    {
        path p = d;
        if (p.is_relative())
            p = base / p;
        res.push_back(p);
    }

    return res;
}
