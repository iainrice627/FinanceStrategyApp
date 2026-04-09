
#ifndef PORTFOLIO_H
#define PORTFOLIO_H
#include <iostream>
#include "stock.h"
#include "queue.h"
//#include "service.h"




class Portfolio {

private:
	static const int capacity = 100;
	Stock portfolio_stocks[capacity];
	int size;
	double total_porfolio_value;
	double total_spent;
	double credit;
	std::string clientID;
	double netGains;
	

public:
	
	Portfolio(std::string clientId);

	Portfolio(double total_porfolio_value, double total_spent, double credit, int size, double netGains);

	int GetSizePortfolio();
	double GetTotalPorfolioValue();
	double GetCredit();
	double GetTotalSpent();
	std::string GetClientID();
	Stock* GetPortfolioStocks();

	void SetClientID(std::string clientID);
	
	void DisplayPortfolio();
	void SellEarliest(std::string chosenStock, double newStockPrice);
	void SellLatest(std::string chosenStock, double newStockPrice);
	void Buy(std::string chosenStock, double newStockPrice);
	
	Stock AccessSpecificStock(int index);
	void RemoveStock(int index);
	void AddStock(Stock stock);
	void SetStockAt(int latestIndex, Stock latestStock);
	void DisplayStock();

	void UpdatePortfolioValue();
	void UpdateNetGainsLossValue();
	void UpdateTotalSpent();
	void UpdateCredit();
	void UpdateCurrentValueStock(double newStockPrice);
	void DeductCreditValue(double newStockPrice);
	void AddCreditValue(double salePrice);
	
	
	
	
	
	int GetTotalSharesPortfolio();
	int GetTotalSharesOfStock(std::string chosenStock);
	
	





};


#endif
