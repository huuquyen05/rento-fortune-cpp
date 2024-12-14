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
#include "load.h"

void Load::loadPlayer(){
    std::vector<playerRecord> records;
    std::ifstream file("../GameRec/playerRec.csv");
    std::string line;
    bool isHeader = true;
    while (std::getline(file, line)) {
        if (isHeader) {
            isHeader = false;
            continue;
        }
        std::istringstream stream(line);
        playerRecord record;
        std::string value;
        std::getline(stream, record.player, ',');
        std::getline(stream, value, ',');
        record.position = std::stoi(value);
        std::getline(stream, value, ',');
        record.inJail = (value == "1"); 
        std::getline(stream, value, ',');
        record.outOFJailCard = std::stoi(value);
        std::getline(stream, value, ',');
        record.money = std::stoi(value);
        std::getline(stream, value, ',');
        record.bankruptcy = (value == "1"); 
        std::getline(stream, record.inTurn, ',');
        records.push_back(record);
    }
    file.close();
}   

