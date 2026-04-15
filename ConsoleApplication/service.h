#ifndef SERVICE_H
#define SERVICE_H

#include <mysql.h>
#include <iostream>
#include "portfolio.h"
#include <vector>
//#include "menu.h"
#include <map>
using Dictionary = std::map<std::string, double>;



class Service {

private:

public:

	static std::string GetTime();
	static std::string DateTime(time_t time, const char* format);
	static double CalculateNewStockPrice(std::string chosenStock, double userPercentChoice, Portfolio& portfolio);
	static Stock CreateStock(std::string name, int number_of_shares, double price_of_purchase, std::string clientID);
	static std::string GenerateStockID(std::string name, std::string clientID, std:: string date_of_purchase);
	static MYSQL* ConnectToDatabase(Portfolio& portfolio);
	static void LoadPortfolio(Portfolio& portfolio);
	static void LoadPortfolioSQL2(Portfolio& portfolio);
	static void SavePortfolioSQL2(Portfolio& portfolio);
	static std::vector<std::string> GetClients();
	static std::string DisplayClients();
	static std::string SelectClient(std::vector<std::string> clients, int size);
	static double GetPrice(Dictionary& dictionary, std::string chosenStock);
	static void UpdateCurrentValue(Dictionary& dictionary, double newStockPrice, std::string chosenStock);


};



#endif
