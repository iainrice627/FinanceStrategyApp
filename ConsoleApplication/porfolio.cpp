#include <iostream>
#include "portfolio.h"
#include "queue.h"
#include "stack.h"
#include "service.h"
#include "validation.h"


Portfolio::Portfolio(std::string clientId) 

{
	this->size = 0;
	this->total_porfolio_value = 0.0;
	this->total_spent = 0.0;
	this->credit = 0.0;
	this->netGains = 0.0;
	this->clientID = clientId;
}

Portfolio::Portfolio(double total_porfolio_value, double total_spent, double credit, int size, double netGains)

{
	
	this->total_porfolio_value = total_porfolio_value;
	this->total_spent = total_spent;
	this->credit = credit;
	this->size = size;
	this->netGains = netGains;
	
}

void Portfolio:: SetClientID(std::string clientID) {

	Validation::ValidClientID(clientID);
	this->clientID = clientID;
}


int Portfolio:: GetSizePortfolio() {

	return size;

}


void Portfolio:: DisplayPortfolio()
{
	UpdatePortfolioValue();
	UpdateNetGainsLossValue();
	UpdateTotalSpent();


	std::cout << std::endl;
	std::cout << "CLIENT PORTFOLIO: " << clientID <<std::endl;
	std::cout << std::endl;
	std::cout << "Portfolio Value: " << total_porfolio_value << std::endl;
	std::cout << "Portfolio Size: " << size << std::endl;
	std::cout << "Portfolio Total Spent: " << total_spent << std::endl;
	std::cout << "Portfolio Net Gains: " << netGains << std::endl;
	std::cout << "Portfolio Credit: " << credit << std::endl;
	std::cout << std::endl;

	for (int i = 0; i < size; ++i) {

		
		Stock stock = portfolio_stocks[i];

		std::cout << stock.stockID << " | " << stock.name << " | " << stock.number_of_shares << " | " << stock.date_of_purchase << " | " << stock.price_of_purchase << " | " << stock.current_value << " | " << stock.clientID << std::endl;
		
	}

}




void Portfolio:: RemoveStock(int index) {

	if (index != -1) {  

		for (int i = index; i < size - 1; ++i) {  
			portfolio_stocks[i] = portfolio_stocks[i + 1];  
		}

		portfolio_stocks[size - 1] = Stock();   
		size--;
	}

}


void Portfolio:: AddStock(Stock stock) {

	try {
		if (this->size < capacity) {

			portfolio_stocks[this->size] = stock;

			this->size++;
		}
		else {

			throw std::runtime_error("Porfolio size is at maximum capacity. No more stocks can be purchased and added");
			
			return; 
		}
	}
	catch (const std::exception& e) {

		std::cout << " Error: " << e.what() << std:: endl;
		std::cout << "Error. Cannot add anymore. Max capacity reached" << std::endl;

	}
	

	

	
}
void Portfolio::UpdateTotalSpent() {

	total_spent = 0;
	for (int i = 0; i < size; ++i) {

		double spend = portfolio_stocks[i].price_of_purchase;
		total_spent += spend;

	}
	
}



void Portfolio::UpdatePortfolioValue() {

	total_porfolio_value = 0;
	for (int i = 0; i < size; ++i) {

		double stock_value = portfolio_stocks[i].current_value;
		total_porfolio_value += stock_value;

	}
	
}


void Portfolio::UpdateNetGainsLossValue() {


	for (int i = 0; i < size; ++i) {

		double netGain = portfolio_stocks[i].current_value - portfolio_stocks[i].price_of_purchase;

		netGains += netGain;
		
	}

}


void Portfolio::UpdateCurrentValueStock(double newStockPrice, std::string chosenStock) {

	for (int i =0; i < size; ++i) {

		if (portfolio_stocks[i].name == chosenStock) {
			portfolio_stocks[i].current_value = newStockPrice;
		}

	}




}


void Portfolio::SellEarliest(std::string chosenStock, double newStockPrice)
{
	int portfolioSize = GetSizePortfolio();

	Queue<int>stocksIndices(size);

	for (int i = 0; i < size; ++i) {

		if (portfolio_stocks[i].name == chosenStock) {
			Stock stock = portfolio_stocks[i];
			stocksIndices.add(i); 
			stock.current_value = newStockPrice;
			
		}

	}
	
	int index;
	stocksIndices.remove(index);
	Stock stock = portfolio_stocks[index];
	double profit = stock.current_value - stock.price_of_purchase;
	std::cout << "The oldest stock of " << stock.name << ", with " << stock.number_of_shares << " shares, has been sold for " << stock.current_value << ", with a net gain of " << profit << "." << std::endl;
	UpdateCurrentValueStock(newStockPrice, chosenStock);
	UpdatePortfolioValue();
	AddCreditValue(newStockPrice);
	RemoveStock(index);

}



void Portfolio::SellLatest(std::string chosenStock, double newStockPrice)
{
	
	Stack<int>stocksIndices(size);

	for (int i = 0; i < size; ++i) {

		if (portfolio_stocks[i].name == chosenStock) {
			
			Stock stock = portfolio_stocks[i];
			stocksIndices.push(i);
			stock.current_value = newStockPrice;


		}
	}

	int index;
	stocksIndices.pop(index);
	Stock stock = portfolio_stocks[index];
	double profit = stock.current_value - stock.price_of_purchase;
	std::cout << "The most recent stock of " << stock.name << ", with " << stock.number_of_shares << " shares, has been sold for " << stock.current_value << ", with a net gain of " << profit << "." << std::endl;
	UpdateCurrentValueStock(newStockPrice, chosenStock);
	UpdatePortfolioValue();
	AddCreditValue(newStockPrice);
	RemoveStock(index);

	 

}


void Portfolio:: Buy(std::string chosenStock, double newStockPrice)
{
	
	int number_of_shares;
	int numShares = 0;
	std::string clientID = GetClientID();

	while(numShares == 0) {

		std::cout << "How many shares do you want to buy?: " << std::endl;
		number_of_shares = Validation::GetInterger();
		numShares = Validation::ValidNumberOfShares(number_of_shares, chosenStock, *this);

	}
	

	Stock stock = Service::CreateStock(chosenStock, numShares, newStockPrice, clientID);
	AddStock(stock);
	DeductCreditValue(newStockPrice);
	UpdateCurrentValueStock(newStockPrice, chosenStock);
	double pricePerShare =  stock.number_of_shares / stock.price_of_purchase;
	std::cout << std::endl;
	std::cout << stock.number_of_shares << " shares of stock " << stock.name << " has been bought for " << stock.price_of_purchase << " at " << pricePerShare << " per share." << std::endl;
}


Stock Portfolio:: AccessSpecificStock(int index) {

	return portfolio_stocks[index];

}


void Portfolio::SetStockAt(int latestIndex, Stock latestStock) {

	portfolio_stocks[latestIndex] = latestStock;

}



void Portfolio::DeductCreditValue(double newStockPrice) {

	credit -= newStockPrice;

}


void Portfolio:: AddCreditValue(double salePrice) {

	credit += salePrice;

}


void Portfolio::DisplayStock() {

	std::string userChosenStock;
	std::cout << "" << std::endl;
	std::cout << "Enter the name of a stock from your portfolio." << std::endl;
	std::cout << std::endl;
	std::cin >> userChosenStock;
	std::cout << std::endl;
	std::string chosenStock = Validation::ValidStock(userChosenStock);
	
	if (chosenStock == "") {
		return;

	}

	Queue<int>stocksIndices(size);
	int count = 0;
	while (count < size) {

		Stock stock = portfolio_stocks[count];

		if (stock.name == chosenStock && stock.clientID == clientID) {
			stocksIndices.add(count);
			
		}
		count += 1;
	}

	std::cout << std::endl;
	std::cout << "View details of all the Stocks below" << std::endl;
	std::cout << std::endl;

	while (!stocksIndices.empty()) {

		int index;
		stocksIndices.remove(index);
		Stock stock = portfolio_stocks[index];

		std::cout << "StockID: " << stock.stockID << std::endl;
		std::cout << "Name:  " << stock.name << std::endl;
		std::cout << "Number of shares:  " << stock.number_of_shares << std::endl;
		std::cout << "Date of purchase: " << stock.date_of_purchase << std::endl;
		std::cout << "Price: " << stock.price_of_purchase << std::endl;
		std::cout << "Current Value: " << stock.current_value << std::endl;
		std::cout << "ClientID: " << stock.clientID << std::endl;
		std::cout << "" << std::endl;
		std::cout << "" << std::endl;

	}
}


std::string Portfolio:: GetClientID() {

	return clientID;
}

Stock* Portfolio:: GetPortfolioStocks() {

	return portfolio_stocks;  
}



int Portfolio:: GetTotalSharesPortfolio() {


	int sharesBucket = 0;

	for (int i = 0; i < size; ++i) {

		sharesBucket += portfolio_stocks[i].number_of_shares;


	}

	return sharesBucket;


}


int Portfolio:: GetTotalSharesOfStock(std::string chosenStock) {


	int sharesBucket = 0;

	for (int i = 0; i < size; ++i) {

		if (portfolio_stocks[i].name == chosenStock) {

			sharesBucket += portfolio_stocks[i].number_of_shares;
		}

	}

	return sharesBucket;
}


double Portfolio::GetTotalPorfolioValue() {

	return total_porfolio_value;
}

double Portfolio::GetTotalSpent() {

	return total_spent;

}

double Portfolio::GetCredit() {

	return credit;

}




