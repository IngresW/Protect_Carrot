#ifndef __Chapter9_6_LoadCsv__StringUtil__
#define __Chapter9_6_LoadCsv__StringUtil__

class StringUtil
{
public:

    // 函数用于将字符串按照指定的分隔符进行拆分，返回拆分后的字符串列表
    StrVec split(const std::string& rSSrcStr, const std::string& rSSep)
    {
        StrVec stringList;  // 定义一个字符串列表用于存储拆分后的字符串

        int size = rSSrcStr.size();  // 获取源字符串的长度

        std::string str(rSSrcStr);  // 将源字符串拷贝到一个新的字符串中

        int startIndex = 0;  // 定义起始索引

        int endIndex = 0;  // 定义结束索引

        endIndex = str.find(rSSep);  // 在字符串中查找第一个分隔符的位置

        std::string splitStr = "";  // 定义一个空字符串用于存储拆分出的子字符串

        while (endIndex > 0)  // 循环执行拆分操作，直到没有找到分隔符为止
        {
            splitStr = str.substr(startIndex, endIndex);  // 提取从起始索引到结束索引之间的子字符串

            stringList.push_back(splitStr);  // 将拆分出的子字符串添加到字符串列表中

            str = std::string(str.substr(endIndex + 1, size));  // 更新源字符串，去除已经拆分的部分

            endIndex = str.find(rSSep);  // 在更新后的源字符串中查找下一个分隔符的位置
        }

        if (str.compare("") != 0) {  // 如果还有剩余的字符串没有被拆分，则将其添加到字符串列表中
            stringList.push_back(str);
        }
        return stringList;  // 返回拆分后的字符串列表
    }
};


#endif