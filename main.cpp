#include "classes.h"


int main(int argc, char* argv[])
{
	std::deque<std::string> usersQueue{};
	
	std::string startTime; // время старта работы
	std::string endTime; // время окончания работы
	unsigned hourlyPay{}; // почасовая оплата
	std::vector<unsigned> revenueForTable; // создаем динамический массив(вектор) для подсчета прибыли
	std::vector < std::pair<bool, std::string> > tablesReady; // вектор для состояния столов содержит два значения - bool (занят или нет), string - занят кем.
	std::vector <std::string> startTimePlaying; // вектор для времени начала игры
	//std::string fileName = argv[1]; // считываем строку с именем файла
	
	std::string fileName = "C:\\Users\\dsmet\\source\\repos\\Yadro_C++\\Yadro_C++\\test_file.txt";

	std::fstream fileReader; // поток для работы с файлом
	fileReader.open(fileName, std::ios::in); // открываем файл на чтение
	std::string data{}; // переменная для считываемых данных
	unsigned strNum{};

	//


	if (fileReader.is_open()) {

		while (std::getline(fileReader, data)) {

			if (strNum == 0) 
				TimeOps::tableQuantityCheck(data, revenueForTable, tablesReady, startTimePlaying);
			
			if (strNum == 1) {

				TimeOps::worktimeCheck(data, startTime, endTime);

			}
			if (strNum == 2) {
				if (NumOps::posCheck(NumOps::intConv(data)))
					hourlyPay = NumOps::intConv(data);
				else
					exit(1);

			}
			if (strNum == 3) {
				std::cout << startTime << std::endl; // открытие клуба
				std::cout << data << std::endl;
				ActionOps::actionCheck(data, startTime, tablesReady, usersQueue, startTimePlaying, revenueForTable);
			}

			if (strNum > 3) {

				std::cout << data << std::endl;
				ActionOps::actionCheck(data, startTime, tablesReady, usersQueue, startTimePlaying, revenueForTable);
				
			}
			strNum++;

		}

		fileReader.close();

	}

	for (auto& client : usersQueue)
		std::cout << endTime << " 11 " << client << std::endl;
	for (unsigned i{}; i < tablesReady.size(); i++) {

		if (tablesReady[i].first) {
			revenueForTable[i] = TimeOps::hourToMinutesConvertation(endTime) - TimeOps::hourToMinutesConvertation(startTimePlaying[i]);
			std::cout << endTime << " 11 " << tablesReady[i].second << std::endl;
		
		}
	}
	std::cout << endTime << std::endl;

	for (unsigned i{}; i < revenueForTable.size(); i++) {

		std::cout << i + 1 << " " << NumOps::incomeCounter(&hourlyPay, &revenueForTable[i]) << " " << TimeOps::minutesToHourConvertation(revenueForTable[i]) << std::endl;

	}


}