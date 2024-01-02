#ifndef __Chapter9_6_LoadCsv__StringUtil__
#define __Chapter9_6_LoadCsv__StringUtil__

class StringUtil
{
public:

    // �������ڽ��ַ�������ָ���ķָ������в�֣����ز�ֺ���ַ����б�
    StrVec split(const std::string& rSSrcStr, const std::string& rSSep)
    {
        StrVec stringList;  // ����һ���ַ����б����ڴ洢��ֺ���ַ���

        int size = rSSrcStr.size();  // ��ȡԴ�ַ����ĳ���

        std::string str(rSSrcStr);  // ��Դ�ַ���������һ���µ��ַ�����

        int startIndex = 0;  // ������ʼ����

        int endIndex = 0;  // �����������

        endIndex = str.find(rSSep);  // ���ַ����в��ҵ�һ���ָ�����λ��

        std::string splitStr = "";  // ����һ�����ַ������ڴ洢��ֳ������ַ���

        while (endIndex > 0)  // ѭ��ִ�в�ֲ�����ֱ��û���ҵ��ָ���Ϊֹ
        {
            splitStr = str.substr(startIndex, endIndex);  // ��ȡ����ʼ��������������֮������ַ���

            stringList.push_back(splitStr);  // ����ֳ������ַ�����ӵ��ַ����б���

            str = std::string(str.substr(endIndex + 1, size));  // ����Դ�ַ�����ȥ���Ѿ���ֵĲ���

            endIndex = str.find(rSSep);  // �ڸ��º��Դ�ַ����в�����һ���ָ�����λ��
        }

        if (str.compare("") != 0) {  // �������ʣ����ַ���û�б���֣�������ӵ��ַ����б���
            stringList.push_back(str);
        }
        return stringList;  // ���ز�ֺ���ַ����б�
    }
};


#endif