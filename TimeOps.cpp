#include "classes.h"

bool TimeOps::isValidTimeFormat(std::string& time) {
    std::regex timeFormat(R"(^([01]\d|2[0-3]):([0-5]\d)$)");
    return std::regex_match(time, timeFormat);
}

void TimeOps::tableQuantityCheck(std::string& data, std::vector<unsigned>& revenueVec, std::vector<std::pair<bool, std::string>>& tableReady, std::vector<std::string>& playingStartTime) {
    int tableQuantity = NumOps::intConv(data);
    if (tableQuantity > 0) {
        revenueVec.reserve(tableQuantity);
        tableReady.reserve(tableQuantity);
        playingStartTime.reserve(tableQuantity);
        for (unsigned i = 0; i < tableQuantity; ++i) {
            revenueVec.emplace_back(0);
            tableReady.emplace_back(std::pair<bool, std::string>{false, "null"});
            playingStartTime.emplace_back("00:00");
        }
        
    }
    else {
        std::cout << "Negative tables quantity!" << std::endl;
        exit(1); // если первая строка не проходит проверку, срабатывает ошибка
    }
}

void TimeOps::worktimeCheck(std::string& data, std::string& start, std::string& end) {
    std::istringstream timeStream(data);
    std::string startTime, endTime;
    timeStream >> startTime >> endTime;
    if (hourToMinutesConvertation(startTime) > hourToMinutesConvertation(endTime) || !isValidTimeFormat(startTime) || !isValidTimeFormat(endTime)) {
        std::cout << "You started after ended!" << std::endl;
        exit(1);
    }
    start = startTime;
    end = endTime;
}

int TimeOps::hourToMinutesConvertation(std::string& time) {
    return stringToMinutes(time);
}

std::string TimeOps::minutesToHourConvertation(int totalMinutes) {
    if (totalMinutes < 0 || totalMinutes > 1439) {
        std::cout << "Invalid minutes!" << std::endl;
        exit(1);
    }
    unsigned hours = totalMinutes / 60;
    unsigned minutes = totalMinutes % 60;
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hours << ":"
        << std::setw(2) << std::setfill('0') << minutes;
    return oss.str();
}

int TimeOps::stringToMinutes(std::string& time) {
    unsigned hours, minutes;
    char colon;
    std::istringstream iss(time);
    iss >> hours >> colon >> minutes;
    unsigned allMinutes = hours * 60 + minutes;
    if (allMinutes > 1439) {
        std::cout << "Too many minutes!" << std::endl;
        exit(1);
    }
    return allMinutes;
}