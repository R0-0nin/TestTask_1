#include "classes.h"

std::string ActionOps::errors[5] = { "YouShallNotPass", "NotOpenYet", "PlaceIsBusy", "ClientUnknown", "ICanWaitNoLonger!" };
std::string ActionOps::incomingIds[4] = { "1", "2", "3", "4" };
std::string ActionOps::outcomingIds[3] = { "11", "12", "13" };

bool ActionOps::clientPlays(std::string client, std::vector<std::pair<bool, std::string>>& tableStates) {

    for (auto& table : tableStates) {

        if (table.second == client)
            return true;

    }
    return false;
}

bool ActionOps::ifThereFreeTables(std::vector<std::pair<bool, std::string>>& tableStates) {
    for (auto& table : tableStates) {
        if (!table.first) {
            return true;
        }
    }
    return false;
}

void ActionOps::clientCheck(std::deque<std::string>& usersQueue, std::string& client, std::string& time, bool& messageAlready, std::string& actionId, std::vector<std::pair<bool, std::string>>& tablesStates, std::vector<std::string>& timeStart, std::vector<unsigned>& playMinutes) {
    bool clientInList = std::find(usersQueue.begin(), usersQueue.end(), client) != usersQueue.end();
    bool clientPlaysState = clientPlays(client, tablesStates);

    if (clientInList && actionId == incomingIds[0] && !messageAlready) {
        std::cout << errorCreator(time, errors[0]) << std::endl;
        messageAlready = true;
    }

    if (!clientInList && !clientPlaysState && actionId != incomingIds[0] && !messageAlready) {
        std::cout << errorCreator(time, errors[0]) << std::endl;
        messageAlready = true;
    }

    if (!clientInList && actionId == incomingIds[0] && !messageAlready) {
        usersQueue.push_back(client);
        messageAlready = true;
    }

    if ((clientInList || clientPlaysState) && actionId == incomingIds[3]) {
        usersQueue.erase(std::remove(usersQueue.begin(), usersQueue.end(), client), usersQueue.end());
        messageAlready = true;
        for (unsigned i{}; i < tablesStates.size(); i++) {

            if (tablesStates[i].second == client) {

                tablesStates[i].first = false;
                tablesStates[i].second = "null";
                playMinutes[i] += TimeOps::hourToMinutesConvertation(time) - TimeOps::hourToMinutesConvertation(timeStart[i]);
                if (usersQueue.size() > 0) {

                    tablesStates[i].first = true;
                    tablesStates[i].second = usersQueue.front();
                    usersQueue.pop_front();
                    std::cout << time << " " << outcomingIds[1] << " " << client << " " << i + 1 << std::endl;
                    timeStart[i] = time;

                }

            }

        }
    }

}

void ActionOps::timeCheck(std::string& actionTime, std::string& startTime, bool& messageAlready) {
    if (TimeOps::hourToMinutesConvertation(actionTime) < TimeOps::hourToMinutesConvertation(startTime) && !messageAlready) {
        std::cout << errorCreator(actionTime, errors[1]) << std::endl;
        messageAlready = true;
    }
}

void ActionOps::tableCheck(std::string& actionTime, unsigned table, std::vector<std::pair<bool, std::string>>& tableStates, std::string& actionId, std::string& client, bool& messageAlready, std::deque<std::string>& usersQueue, std::vector<std::string>& timeStart) {
    
    bool tablesFree = ifThereFreeTables(tableStates);
    bool notTable = (table == 0);
    if (!notTable)
        table--;

    if (tableStates[table].first && actionId == "2" && !messageAlready && !notTable) {
        std::cout << errorCreator(actionTime, errors[2]) << std::endl;
        messageAlready = true;
    }

    if (!tableStates[table].first && actionId == "2" && !notTable) {
        tableStates[table].first = true;
        tableStates[table].second = client;
        timeStart[table] = actionTime;
        usersQueue.erase(std::remove(usersQueue.begin(), usersQueue.end(), client), usersQueue.end());
    }

    if (tablesFree && actionId == "3" && !messageAlready) {
        std::cout << errorCreator(actionTime, errors[4]) << std::endl;
        messageAlready = true;
    }
    else if (!tablesFree && tableStates.size() < usersQueue.size() && !messageAlready) {
        std::cout << errorCreator(actionTime, errors[3]) << std::endl;
        messageAlready = true;
    }
}

void ActionOps::actionCheck(std::string& action, std::string& startTime, std::vector<std::pair<bool, std::string>>& tablesStates, std::deque<std::string>& usersQueue, std::vector <std::string>& startTimePlaying, std::vector<unsigned>& revenueForTable) {
    bool messageAlready = false;
    std::string time, actionId, client;
    unsigned table = 0;
    std::istringstream iss(action);
    iss >> time >> actionId >> client >> table;

    timeCheck(time, startTime, messageAlready);
    clientCheck(usersQueue, client, time, messageAlready, actionId, tablesStates, startTimePlaying, revenueForTable);
    tableCheck(time, table, tablesStates, actionId, client, messageAlready, usersQueue, startTimePlaying);
}

std::string ActionOps::errorCreator(std::string& time, std::string& errorString) {
    return (time + " " + outcomingIds[2] + " " + errorString);
}