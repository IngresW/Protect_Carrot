#ifndef _SAVEGAME_MANAGER
#define _SAVEGAME_MANAGER
#include <iostream>
#include <string>
#include <fstream>
#include "cocos2d.h"
#include "tinyxml2.h"
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_iterators.hpp"

using namespace tinyxml2;
using namespace rapidxml;

// 存档数据结构
struct SaveData
{
    std::string characterName;
    int levelProgress;
    int characterUnlockProgress;
    int coinCount;

    SaveData() { characterName = "NULL"; levelProgress = 0;
    characterUnlockProgress = 0; coinCount = 0; };
};


class SaveGameManagement
{
public:
    static void LoadSaveData();

    static bool SaveSaveData();

    static SaveData GetSaveData(int index);

    static SaveData LoadSaveDataFromFile(const std::string& filePath);

    static bool SaveSaveDataToFile(const std::string& filePath, const SaveData& data);

    static int GetEmptySlot();

    static void createNewSlot(const std::string& character_Name);

    static void deleteSlot(int index);

    static std::string DisplayForLoad(int i);

    static void chooseSlot(const int i);

    static void saveSlot(const SaveData data)
    {
        saveSlots[choosedSlot] = data;
    }

protected:
    static SaveData saveSlots[3];

    static int choosedSlot;
};
#endif