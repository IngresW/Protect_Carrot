#ifndef __Chapter9_6_LoadCsv__FileLoadUtil__
#define __Chapter9_6_LoadCsv__FileLoadUtil__

#include "cocos2d.h"
#include "StringUtil.h"

class FileLoadUtil
{
public:

    // 函数用于从指定的CSV文件中获取数据行，并返回一个字符串列表
    StrVec getDataLines(const std::string& rSCsvFilePath)
    {
        StrVec linesList;  // 定义一个字符串列表用于存储数据行

        if (!cocos2d::FileUtils::getInstance()->isFileExist(rSCsvFilePath))  // 检查CSV文件是否存在
            return linesList;  // 如果文件不存在，则直接返回空的字符串列表

        ssize_t pSize = 0;  // 文件大小

        StringUtil tStringUtil;  // 创建一个StringUtil对象用于字符串操作

        unsigned char* chDatas = cocos2d::FileUtils::getInstance()->getFileData(rSCsvFilePath, "r", &pSize);  // 从文件中读取数据

        if (chDatas) linesList = tStringUtil.split((char*)chDatas, "\n");  // 使用StringUtil的split函数将数据按行拆分

        return linesList;  // 返回数据行的字符串列表
    }
};

#endif