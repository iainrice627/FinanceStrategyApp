#ifndef SERVICE_H
#define SERVICE_H

#include <iostream>
#include "portfolio.h"
#include <vector>



class Service {

private:

public:

	static std::string GetTime();
	static std::string DateTime(time_t time, const char* format);
	static double CalculateNewStockPrice(std::string chosenStock, int userPercentChoice, Portfolio& portfolio);
	static Stock CreateStock(std::string name, int number_of_shares, double price_of_purchase, std::string clientID);
	static std::string GenerateStockID(std::string name, std::string clientID, std:: string date_of_purchase);
	static void LoadPortfolio(Portfolio& portfolio);
	static void SavePortfolio(Portfolio& portfolio);
	static std::vector<std::string> GetClients();
	static std::string DisplayClients();
	static std::string SelectClient();


};



#endif
