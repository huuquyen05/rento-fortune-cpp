#include <iostream>
#include <vector>
#include <unordered_map>
#include "game.h"
#include "property.h"
#include "slot.h"
#include <string>
#include <sstream>
#include <unistd.h>
#include <filesystem>
#include <fstream>
#include "save.h"

void Save::createPlayer(std::vector<Player*> players,Player* curPlayer){
    if (!std::filesystem::exists(folderPath)){
        std::filesystem::create_directories(folderPath);
    }
    std::string filename = "playerRec.csv";
    std::string filepath = folderPath + "\\" + filename;
    std::vector<playerRecord> records;
    for(auto i:players){
        playerRecord p ={i->getName(),i->getPosition(),i->isInJail(),i->getOutJailCard(),i->getMoney(),i->isBankrupt(),curPlayer->getName()};
        records.push_back(p);
    } 
    std::ofstream file(filepath);
    file << "player,position,inJail,outOfJailCard,money,bankruptcy,inTurn\n";
    for (const auto& record : records) {
        file << record.player << ","
             << record.position << ","
             << record.inJail << ","
             << record.outOFJailCard << ","
             << record.money << ","
             << record.bankruptcy << ","
             << record.inTurn << "\n";
    }
    file.close();
}

void Save::createProperty(){
    if (!std::filesystem::exists(folderPath)){
        std::filesystem::create_directories(folderPath);
    }
    std::string filename = "propertyRec.csv";
    std::string filepath = folderPath + "\\" + filename;
    std::vector<propertyRecord> records;
    for(int i=0;i<=40;i++){
        if(typeid(slots[i])==typeid(PropertySlot*)){
            //propertyRecord p = {slots[i]->getName()}
        }
    } 
    std::ofstream file(filepath);
    file << "num,level,owner";
    for (const auto& record : records) {
        file << record.num << ","
             << record.level << ","
             << record.owner << "\n";
    }
    file.close();
}

void Save::createOther(){
    if (!std::filesystem::exists(folderPath)){
        std::filesystem::create_directories(folderPath);
    }
    std::string filename = "propertyRec.csv";
    std::string filepath = folderPath + "\\" + filename;
    std::vector<propertyRecord> records;
    for(int i=0;i<=40;i++){
        if(typeid(slots[i])==typeid(UtilitySlot*)||typeid(slots[i])==typeid(RailwayStationSlot*)){
            //propertyRecord p = {slots[i]->getName()}
        }
    } 
    std::ofstream file(filepath);
    file << "num,level,owner";
    for (const auto& record : records) {
        file << record.owner << "\n";
    }
    file.close();
}

void Save::createSavingFile(std::vector<Player*> players,Player* curPlayer){
    //createPlayer(std::vector<Player*> players,Player* curPlayer);
    createProperty();
    createOther();
}