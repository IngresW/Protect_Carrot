#ifndef __Chapter14_2_CardDefence01__CsvUtil__
#define __Chapter14_2_CardDefence01__CsvUtil__

#include <vector>
#include <map>
#include <string>

typedef std::vector<std::string> StrVec;  // 字符串向量类型，用于存储一维字符串数组

typedef std::vector<StrVec> StrDict;  // 字符串字典类型，用于存储二维字符串数组

typedef std::map<std::string, StrDict> CsvMap;  // CSV字典类型，用于存储多个CSV文件

class CsvUtil
{
public:
    static CsvUtil* getInstance();  // 获取CsvUtil的单例实例

    static void destroyInstance();  // 销毁CsvUtil的单例实例

    /**
     *  添加CSV文件到字典
     *
     *  @param sPath CSV文件路径
     */
    virtual void addFileData(const std::string& rSPath);

    /**
     *  从字典中删除CSV文件
     *
     *  @param sPath CSV文件路径
     */
    virtual void releaseFile(const std::string& rSPath);

    /**
     *  从指定的CSV文件中获取某行某列的值
     *
     *  @param rRow        行号
     *  @param rCol        列号
     *  @param csvFilePath CSV文件路径
     *
     *  @return 指定位置的字符串值、整数值或浮点数值，如果位置不存在则返回空字符串
     */
    virtual std::string getText(const int& rRow, const int& rCol, const std::string& rSCsvFilePath);
    virtual int getInt(const int& rRow, const int& rCol, const std::string& rSCsvFilePath);
    virtual double getDouble(const int& rRow, const int& rCol, const std::string& rSCsvFilePath);

    /**
     *  获取指定CSV文件中某行的数据
     *
     *  @param iRow          行号
     *  @param rSCsvFilePath CSV文件路径
     *
     *  @return 指定行的数据
     */
    virtual StrVec getRowData(const int& rIRow, const std::string& rSCsvFilePath);

    /**
     *  获取指定CSV文件的行数和列数，并以tuple<int, int>的形式返回
     *
     *  @param rSCsvFilePath CSV文件路径
     *
     *  @return CSV文件的行数和列数
     */
    virtual std::tuple<int, int> getFileRowColNum(const std::string& rSCsvFilePath);

    /**
     *  在指定的CSV文件中查找目标值所在的行号
     *
     *  @param rSValue       目标值
     *  @param rIValueCol    目标值所在的列号
     *  @param rSCsvFilePath CSV文件路径
     *
     *  @return 目标值所在的行号
     */
    virtual int findValueInWithLine(const std::string& rSValue, const int& rIValueCol, const std::string& rSCsvFilePath);

protected:
    /**
     *  获取指定CSV文件的字符串字典
     *
     *  @param rSCsvFilePath CSV文件路径
     *
     *  @return CSV文件的字符串字典
     */
    virtual StrDict& getFileDict(const std::string& rSCsvFilePath);

    virtual ~CsvUtil();

private:
    CsvUtil();

    CsvUtil(const CsvUtil& rCsvUtil) = delete;

    CsvUtil& operator=(const CsvUtil& rCsvUtil) = delete;

private:
    static CsvUtil* _gInstance;  // CsvUtil的单例实例指针

    /**
     *
     */
    CsvMap* _pCsvMap;  // CSV文件字典指针
};

#endif /* defined(__Chapter14_2_CardDefence01__CsvUtil__) */