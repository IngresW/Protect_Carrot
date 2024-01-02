#ifndef __Chapter14_2_CardDefence01__CsvUtil__
#define __Chapter14_2_CardDefence01__CsvUtil__

#include <vector>
#include <map>
#include <string>

typedef std::vector<std::string> StrVec;  // �ַ����������ͣ����ڴ洢һά�ַ�������

typedef std::vector<StrVec> StrDict;  // �ַ����ֵ����ͣ����ڴ洢��ά�ַ�������

typedef std::map<std::string, StrDict> CsvMap;  // CSV�ֵ����ͣ����ڴ洢���CSV�ļ�

class CsvUtil
{
public:
    static CsvUtil* getInstance();  // ��ȡCsvUtil�ĵ���ʵ��

    static void destroyInstance();  // ����CsvUtil�ĵ���ʵ��

    /**
     *  ���CSV�ļ����ֵ�
     *
     *  @param sPath CSV�ļ�·��
     */
    virtual void addFileData(const std::string& rSPath);

    /**
     *  ���ֵ���ɾ��CSV�ļ�
     *
     *  @param sPath CSV�ļ�·��
     */
    virtual void releaseFile(const std::string& rSPath);

    /**
     *  ��ָ����CSV�ļ��л�ȡĳ��ĳ�е�ֵ
     *
     *  @param rRow        �к�
     *  @param rCol        �к�
     *  @param csvFilePath CSV�ļ�·��
     *
     *  @return ָ��λ�õ��ַ���ֵ������ֵ�򸡵���ֵ�����λ�ò������򷵻ؿ��ַ���
     */
    virtual std::string getText(const int& rRow, const int& rCol, const std::string& rSCsvFilePath);
    virtual int getInt(const int& rRow, const int& rCol, const std::string& rSCsvFilePath);
    virtual double getDouble(const int& rRow, const int& rCol, const std::string& rSCsvFilePath);

    /**
     *  ��ȡָ��CSV�ļ���ĳ�е�����
     *
     *  @param iRow          �к�
     *  @param rSCsvFilePath CSV�ļ�·��
     *
     *  @return ָ���е�����
     */
    virtual StrVec getRowData(const int& rIRow, const std::string& rSCsvFilePath);

    /**
     *  ��ȡָ��CSV�ļ�������������������tuple<int, int>����ʽ����
     *
     *  @param rSCsvFilePath CSV�ļ�·��
     *
     *  @return CSV�ļ�������������
     */
    virtual std::tuple<int, int> getFileRowColNum(const std::string& rSCsvFilePath);

    /**
     *  ��ָ����CSV�ļ��в���Ŀ��ֵ���ڵ��к�
     *
     *  @param rSValue       Ŀ��ֵ
     *  @param rIValueCol    Ŀ��ֵ���ڵ��к�
     *  @param rSCsvFilePath CSV�ļ�·��
     *
     *  @return Ŀ��ֵ���ڵ��к�
     */
    virtual int findValueInWithLine(const std::string& rSValue, const int& rIValueCol, const std::string& rSCsvFilePath);

protected:
    /**
     *  ��ȡָ��CSV�ļ����ַ����ֵ�
     *
     *  @param rSCsvFilePath CSV�ļ�·��
     *
     *  @return CSV�ļ����ַ����ֵ�
     */
    virtual StrDict& getFileDict(const std::string& rSCsvFilePath);

    virtual ~CsvUtil();

private:
    CsvUtil();

    CsvUtil(const CsvUtil& rCsvUtil) = delete;

    CsvUtil& operator=(const CsvUtil& rCsvUtil) = delete;

private:
    static CsvUtil* _gInstance;  // CsvUtil�ĵ���ʵ��ָ��

    /**
     *
     */
    CsvMap* _pCsvMap;  // CSV�ļ��ֵ�ָ��
};

#endif /* defined(__Chapter14_2_CardDefence01__CsvUtil__) */