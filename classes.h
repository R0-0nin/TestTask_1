#pragma once

#ifndef CLASSES_H
#define CLASSES_H
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <map>
#include <iomanip>
#include <queue>

class ActionOps {
public:
    static void actionCheck(std::string& action, std::string& startTime, std::vector<std::pair<bool, std::string>>& tablesStates, std::deque<std::string>& usersQueue, std::vector <std::string>& startTimePlaying, std::vector<unsigned>& revenueForTable);
    static std::string errorCreator(std::string& time, std::string& errorString);

private:
    static std::string errors[5];
    static std::string incomingIds[4];
    static std::string outcomingIds[3];
    static bool clientPlays(std::string client, std::vector<std::pair<bool, std::string>>& tableStates);
    static bool ifThereFreeTables(std::vector<std::pair<bool, std::string>>& tableStates);
    static void clientCheck(std::deque<std::string>& usersQueue, std::string& client, std::string& time, bool& messageAlready, std::string& actionId, std::vector<std::pair<bool, std::string>>& tablesStates, std::vector<std::string>& timeStart, std::vector<unsigned>& playMinutes);
    static void timeCheck(std::string& actionTime, std::string& startTime, bool& messageAlready);
    static void tableCheck(std::string& actionTime, unsigned table, std::vector<std::pair<bool, std::string>>& tableStates, std::string& actionId, std::string& client, bool& messageAlready, std::deque<std::string>& usersQueue, std::vector<std::string>& timeStart);
};

class TimeOps { // класс для операций со временем

public:
    static bool isValidTimeFormat(std::string& time);
    static void tableQuantityCheck(std::string& data, std::vector<unsigned>& revenueVec, std::vector<std::pair<bool, std::string>>& tableReady, std::vector<std::string>& playingStartTime);
    static void worktimeCheck(std::string& data, std::string& start, std::string& end);
    static int hourToMinutesConvertation(std::string& time);
    static std::string minutesToHourConvertation(int totalMinutes);
    static int stringToMinutes(std::string& time);

};

class NumOps {
public:
    static unsigned incomeCounter(unsigned* defaultRev, unsigned* minutes);
    static int intConv(std::string& num);
    static bool posCheck(int num);
};

#endif // MYCLASS_H
