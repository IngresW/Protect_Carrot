#include "CsvUtil.h"
#include "FileLoadUtil.h"
#include "StringUtil.h"

CsvUtil* CsvUtil::_gInstance;  // ��̬��Ա�����Ķ���

CsvUtil::CsvUtil() :_pCsvMap(nullptr)
{
    _pCsvMap = new CsvMap();  // ����CsvMap����
}

CsvUtil::~CsvUtil()
{
    CC_SAFE_DELETE(_pCsvMap);  // �ͷ�_pCsvMap���ڴ�
}

CsvUtil* CsvUtil::getInstance()
{
    if (!_gInstance)  // ���ʵ���Ƿ��Ѿ�����
        _gInstance = new CsvUtil();  // ����ʵ��
    return _gInstance;  // ����ʵ��ָ��
}

void CsvUtil::destroyInstance()
{
    if (_gInstance) CC_SAFE_DELETE(_gInstance);  // ����ʵ��
}

void CsvUtil::addFileData(const std::string& rSCsvFilePath)
{
    if (std::string("") == rSCsvFilePath) return;  // ���CSV�ļ�·���Ƿ�Ϊ��

    FileLoadUtil tFileLoadUtil;  // ����FileLoadUtil����
    auto linesVec = tFileLoadUtil.getDataLines(rSCsvFilePath);  // ���ļ��л�ȡ������
    StrVec strsVec;
    StrDict dict;
    StringUtil tStringUtil;

    for (const auto& linesVecIter : linesVec)  // ����������
    {
        strsVec = tStringUtil.split(linesVecIter.c_str(), ",");  // �������а����Ų�ֳ��ַ����б�
        dict.push_back(strsVec);  // ����ֺ���ַ����б���ӵ��ֵ���
    }
    _pCsvMap->insert(std::make_pair(std::string(rSCsvFilePath), dict));  // ����CSV�ļ�·�����ֵ�ļ�ֵ�Ե�CsvMap��
}

void CsvUtil::releaseFile(const std::string& rSCsvFilePath)
{
    _pCsvMap->erase(rSCsvFilePath);  // ��CsvMap��ɾ��ָ����CSV�ļ�·��
}

std::tuple<int, int> CsvUtil::getFileRowColNum(const std::string& rSCsvFilePath)
{
    auto tDict = getFileDict(rSCsvFilePath);  // ��ȡָ��CSV�ļ�·�����ֵ�
    int iRowNum = tDict.size();  // ��ȡ�ֵ������
    int iColNum = (*(tDict.begin())).size();  // ��ȡ�ֵ��е�һ�е�����
    return std::make_tuple(iColNum, iRowNum - 1);  // ����������������Ԫ��
}

std::string CsvUtil::getText(const int& rRow, const int& rCol, const std::string& rSCsvFilePath)
{
    const auto dict = getFileDict(rSCsvFilePath);  // ��ȡָ��CSV�ļ�·�����ֵ�

    const auto lineDatas = dict.at(rRow);  // ��ȡָ���е�����

    return lineDatas.at(rCol);  // ����ָ�����е�����
}

int CsvUtil::getInt(const int& rRow, const int& rCol, const std::string& rSCsvFilePath)
{
    return atoi(getText(rRow, rCol, rSCsvFilePath).c_str());  // ���ַ���ת��Ϊ����������
}

double CsvUtil::getDouble(const int& rRow, const int& rCol, const std::string& rSCsvFilePath)
{
    return atof(getText(rRow, rCol, rSCsvFilePath).c_str());  // ���ַ���ת��Ϊ������������
}

StrVec CsvUtil::getRowData(const int& rIRow, const std::string& rSCsvFilePath)
{
    auto tRow = std::get<1>(getFileRowColNum(rSCsvFilePath));  // ��ȡָ��CSV�ļ�·��������

    if (rIRow > tRow) return StrVec();  // ���ָ�����������������������򷵻ؿյ��ַ����б�

    return  _pCsvMap->at(rSCsvFilePath).at(rIRow);  // ����ָ���е�����
}

StrDict& CsvUtil::getFileDict(const std::string& rSCsvFilePath)
{
    return _pCsvMap->at(rSCsvFilePath);  // ����ָ��CSV�ļ�·�����ֵ�
}

int CsvUtil::findValueInWithLine(const std::string& rSValue, const int& rIValueCol, const std::string& rSCsvFilePath)
{
    auto iRowCount = std::get<1>(getFileRowColNum(rSCsvFilePath));  // ��ȡָ��CSV�ļ�·��������

    auto ret = -1;  // ��ʼ������ֵΪ-1
    std::string findValue(rSValue);  // ��Ҫ���ҵ�ֵ�洢��findValue��

    for (int iRow = 0; iRow < iRowCount; ++iRow)  // ����ÿһ��
    {
        std::string tmpValue = getText(iRow, rIValueCol, rSCsvFilePath);  // ��ȡ��ǰ��ָ���е�ֵ
        if (findValue == tmpValue)  // ����ҵ���ƥ���ֵ
        {
            ret = iRow;  // ���·���ֵΪ��ǰ�е�����
            break;  // ��ֹѭ��
        }
    }
    return ret;  // �����ҵ��������������δ�ҵ��򷵻�-1
}