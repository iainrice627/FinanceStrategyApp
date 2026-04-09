#ifndef VALIDATION_H
#define VALIDATION_H

#include<iostream>
#include "portfolio.h"


class Validation {

private:


public:

	static void ValidLoginUserName(std::string username);
	static void ValidLoginPassword(std::string password);
	static std:: string  ValidClientID(std::string clientID);
	static int ValidMenuSelection(int selection);
	static std::string ValidStock(std::string userChosenStock);
	static double ValidPercentage(double userPercentChoice);
	static int ValidNumberOfShares(int number_of_shares, std::string chosenStock, Portfolio& portfolio);
	static std::string ValidGenerateStockID(std::string stockID);
	static std::string ValidDateString(std::string formattedTime);
	static double GetDouble();
	static int GetInterger();
	static double CheckPurchaseAsPercentageofPortfolio(int number_of_shares, std::string chosenStock, Portfolio& portfolio);
	static void StockConstructor(std::string name, int number_of_shares, double price_of_purchase);
	static void PortfolioConstructor(int size, double total_porfolio_value, double total_spent, double credit, std::string clientID);
	//static void ClientConstructor();
	static void ValidName(std::string name);
	static void ValidPriceOfPurchase(double price_of_purchase);
	static void ValidSize(int size);
	static void ValidPortfolioValue(double total_portfolio_value);
	static void ValidTotalSpent(double total_spent);
	static void ValidCredit(double credit);




};




#endif