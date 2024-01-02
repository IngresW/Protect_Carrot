#include "SaveGameManager.h"

SaveData SaveGameManagement::saveSlots[3];
int SaveGameManagement::choosedSlot = -1;

USING_NS_CC;

void SaveGameManagement::LoadSaveData()
{
    for (int i = 1; i <= 3; i++)
    {
        std::string filePath = ("savegame_" + std::to_string(i) + ".xml");
        SaveData loadedData = LoadSaveDataFromFile(filePath);
        saveSlots[i - 1] = loadedData;
    }
}

bool SaveGameManagement::SaveSaveData()
{
    for (int i = 1; i <= 3; i++)
    {
        std::string filePath = "savegame_" + std::to_string(i) + ".xml";
        bool success = SaveSaveDataToFile(filePath, saveSlots[i - 1]);
        if (!success)
        {
            //std::cout << "Failed to save data to file " << filePath << std::endl;
            CCLOG("Failed to save data to file ");
            return false;
        }
    }
    return true;
}

SaveData SaveGameManagement::GetSaveData(int index)
{
    if (index >= 1 && index <= 3)
    {
        return saveSlots[index - 1];
    }
    else
    {
        std::cout << "Invalid save data index: " << index << std::endl;
        return SaveData(); // 返回一个默认的空 SaveData
    }
}

SaveData SaveGameManagement::LoadSaveDataFromFile(const std::string& fileName)
{
    SaveData gameData;
    tinyxml2::XMLDocument xmlDoc;
    if (xmlDoc.LoadFile(fileName.c_str()) == XML_SUCCESS) {
        XMLElement* rootElement = xmlDoc.FirstChildElement("SaveData");
        if (rootElement) {
            XMLElement* saveDataElement = rootElement->FirstChildElement("SaveData");
            if (saveDataElement) {
                XMLElement* characterNameElement = saveDataElement->FirstChildElement("CharacterName");
                if (characterNameElement) {
                    gameData.characterName = characterNameElement->GetText();
                }

                XMLElement* levelProgressElement = saveDataElement->FirstChildElement("LevelProgress");
                if (levelProgressElement) {
                    std::string levelProgressText = levelProgressElement->GetText();
                    gameData.levelProgress = std::stoi(levelProgressText);
                }

                XMLElement* characterUnlockProgressElement = saveDataElement->FirstChildElement("characterUnlockProgress");
                if (characterUnlockProgressElement) {
                    std::string characterUnlockProgressText = characterUnlockProgressElement->GetText();
                    gameData.characterUnlockProgress = std::stoi(characterUnlockProgressText);
                }

                XMLElement* coinCountElement = saveDataElement->FirstChildElement("coinCount");
                if (coinCountElement) {
                    std::string coinCountText = coinCountElement->GetText();
                    gameData.coinCount = std::stoi(coinCountText);
                }
            }
        }
    }
    else
        return SaveData();
    return gameData;
}

bool SaveGameManagement::SaveSaveDataToFile(const std::string& filePath, const SaveData& data) {
    tinyxml2::XMLDocument doc;
    XMLDeclaration* declaration = doc.NewDeclaration();
    doc.LinkEndChild(declaration);

    XMLElement* root = doc.NewElement("SaveData");
    doc.LinkEndChild(root);

    XMLElement* saveDataNode = doc.NewElement("SaveData");
    root->LinkEndChild(saveDataNode);

    XMLElement* characterNameNode = doc.NewElement("CharacterName");
    XMLText* characterNameText = doc.NewText(data.characterName.c_str());
    characterNameNode->LinkEndChild(characterNameText);
    saveDataNode->LinkEndChild(characterNameNode);

    XMLElement* levelProgressNode = doc.NewElement("LevelProgress");
    char levelProgressStr[16];
    sprintf(levelProgressStr, "%d", data.levelProgress);
    XMLText* levelProgressText = doc.NewText(levelProgressStr);
    levelProgressNode->LinkEndChild(levelProgressText);
    saveDataNode->LinkEndChild(levelProgressNode);

    XMLElement* characterUnlockProgressNode = doc.NewElement("characterUnlockProgress");
    char characterUnlockProgressStr[16];
    sprintf(characterUnlockProgressStr, "%d", data.characterUnlockProgress);
    XMLText* characterUnlockProgressText = doc.NewText(characterUnlockProgressStr);
    characterUnlockProgressNode->LinkEndChild(characterUnlockProgressText);
    saveDataNode->LinkEndChild(characterUnlockProgressNode);

    XMLElement* coinCountNode = doc.NewElement("coinCount");
    char coinCountStr[16];
    sprintf(coinCountStr, "%d", data.coinCount);
    XMLText* coinCountText = doc.NewText(coinCountStr);
    coinCountNode->LinkEndChild(coinCountText);
    saveDataNode->LinkEndChild(coinCountNode);
    // 其他保存数据的代码

    doc.SaveFile(filePath.c_str());
    return true;
}

int SaveGameManagement::GetEmptySlot()
{
    int num = 0;
    for (int i = 0; i < 3; i++)
    {
        if (saveSlots[i].characterName != "NULL")
            num++;
    }
    return num;
}

void SaveGameManagement::createNewSlot(const std::string& character_Name)
{
    int num = GetEmptySlot();
    if (num >= 3)
    {
        std::cerr << "当前存档已满，请先清理存档" << std::endl;
    }
    else
    {
        SaveData newdata;
        newdata.characterName = character_Name;

        saveSlots[num] = newdata;
    }
}

void SaveGameManagement::deleteSlot(const int index)
{
    saveSlots[index - 1] = SaveData();
}

std::string SaveGameManagement::DisplayForLoad(const int i)
{
    /*if (saveSlots[i].characterName.empty())
        return "NULL";*/
    std::string labelText = ""/*"Save Slot " + std::to_string(i + 1) + ":\n"*/;
    labelText += "Character Name: " + saveSlots[i].characterName + "\n";
    labelText += "Level Progress: " + std::to_string(saveSlots[i].levelProgress) + "\n";
    labelText += "CoinCount: " + std::to_string(saveSlots[i].coinCount) + "\n";
    return labelText;
}

void SaveGameManagement::chooseSlot(const int i)
{
    choosedSlot = i;
}