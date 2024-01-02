#ifndef __Chapter9_6_LoadCsv__FileLoadUtil__
#define __Chapter9_6_LoadCsv__FileLoadUtil__

#include "cocos2d.h"
#include "StringUtil.h"

class FileLoadUtil
{
public:

    // �������ڴ�ָ����CSV�ļ��л�ȡ�����У�������һ���ַ����б�
    StrVec getDataLines(const std::string& rSCsvFilePath)
    {
        StrVec linesList;  // ����һ���ַ����б����ڴ洢������

        if (!cocos2d::FileUtils::getInstance()->isFileExist(rSCsvFilePath))  // ���CSV�ļ��Ƿ����
            return linesList;  // ����ļ������ڣ���ֱ�ӷ��ؿյ��ַ����б�

        ssize_t pSize = 0;  // �ļ���С

        StringUtil tStringUtil;  // ����һ��StringUtil���������ַ�������

        unsigned char* chDatas = cocos2d::FileUtils::getInstance()->getFileData(rSCsvFilePath, "r", &pSize);  // ���ļ��ж�ȡ����

        if (chDatas) linesList = tStringUtil.split((char*)chDatas, "\n");  // ʹ��StringUtil��split���������ݰ��в��

        return linesList;  // ���������е��ַ����б�
    }
};

#endif