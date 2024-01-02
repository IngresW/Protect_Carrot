#include "CsvUtil.h"
#include "FileLoadUtil.h"
#include "StringUtil.h"

CsvUtil* CsvUtil::_gInstance;  // 静态成员变量的定义

CsvUtil::CsvUtil() :_pCsvMap(nullptr)
{
    _pCsvMap = new CsvMap();  // 创建CsvMap对象
}

CsvUtil::~CsvUtil()
{
    CC_SAFE_DELETE(_pCsvMap);  // 释放_pCsvMap的内存
}

CsvUtil* CsvUtil::getInstance()
{
    if (!_gInstance)  // 检查实例是否已经存在
        _gInstance = new CsvUtil();  // 创建实例
    return _gInstance;  // 返回实例指针
}

void CsvUtil::destroyInstance()
{
    if (_gInstance) CC_SAFE_DELETE(_gInstance);  // 销毁实例
}

void CsvUtil::addFileData(const std::string& rSCsvFilePath)
{
    if (std::string("") == rSCsvFilePath) return;  // 检查CSV文件路径是否为空

    FileLoadUtil tFileLoadUtil;  // 创建FileLoadUtil对象
    auto linesVec = tFileLoadUtil.getDataLines(rSCsvFilePath);  // 从文件中获取数据行
    StrVec strsVec;
    StrDict dict;
    StringUtil tStringUtil;

    for (const auto& linesVecIter : linesVec)  // 遍历数据行
    {
        strsVec = tStringUtil.split(linesVecIter.c_str(), ",");  // 将数据行按逗号拆分成字符串列表
        dict.push_back(strsVec);  // 将拆分后的字符串列表添加到字典中
    }
    _pCsvMap->insert(std::make_pair(std::string(rSCsvFilePath), dict));  // 插入CSV文件路径和字典的键值对到CsvMap中
}

void CsvUtil::releaseFile(const std::string& rSCsvFilePath)
{
    _pCsvMap->erase(rSCsvFilePath);  // 从CsvMap中删除指定的CSV文件路径
}

std::tuple<int, int> CsvUtil::getFileRowColNum(const std::string& rSCsvFilePath)
{
    auto tDict = getFileDict(rSCsvFilePath);  // 获取指定CSV文件路径的字典
    int iRowNum = tDict.size();  // 获取字典的行数
    int iColNum = (*(tDict.begin())).size();  // 获取字典中第一行的列数
    return std::make_tuple(iColNum, iRowNum - 1);  // 返回列数和行数的元组
}

std::string CsvUtil::getText(const int& rRow, const int& rCol, const std::string& rSCsvFilePath)
{
    const auto dict = getFileDict(rSCsvFilePath);  // 获取指定CSV文件路径的字典

    const auto lineDatas = dict.at(rRow);  // 获取指定行的数据

    return lineDatas.at(rCol);  // 返回指定行列的数据
}

int CsvUtil::getInt(const int& rRow, const int& rCol, const std::string& rSCsvFilePath)
{
    return atoi(getText(rRow, rCol, rSCsvFilePath).c_str());  // 将字符串转换为整数并返回
}

double CsvUtil::getDouble(const int& rRow, const int& rCol, const std::string& rSCsvFilePath)
{
    return atof(getText(rRow, rCol, rSCsvFilePath).c_str());  // 将字符串转换为浮点数并返回
}

StrVec CsvUtil::getRowData(const int& rIRow, const std::string& rSCsvFilePath)
{
    auto tRow = std::get<1>(getFileRowColNum(rSCsvFilePath));  // 获取指定CSV文件路径的行数

    if (rIRow > tRow) return StrVec();  // 如果指定的行数超过了总行数，则返回空的字符串列表

    return  _pCsvMap->at(rSCsvFilePath).at(rIRow);  // 返回指定行的数据
}

StrDict& CsvUtil::getFileDict(const std::string& rSCsvFilePath)
{
    return _pCsvMap->at(rSCsvFilePath);  // 返回指定CSV文件路径的字典
}

int CsvUtil::findValueInWithLine(const std::string& rSValue, const int& rIValueCol, const std::string& rSCsvFilePath)
{
    auto iRowCount = std::get<1>(getFileRowColNum(rSCsvFilePath));  // 获取指定CSV文件路径的行数

    auto ret = -1;  // 初始化返回值为-1
    std::string findValue(rSValue);  // 将要查找的值存储在findValue中

    for (int iRow = 0; iRow < iRowCount; ++iRow)  // 遍历每一行
    {
        std::string tmpValue = getText(iRow, rIValueCol, rSCsvFilePath);  // 获取当前行指定列的值
        if (findValue == tmpValue)  // 如果找到了匹配的值
        {
            ret = iRow;  // 更新返回值为当前行的索引
            break;  // 终止循环
        }
    }
    return ret;  // 返回找到的行索引，如果未找到则返回-1
}