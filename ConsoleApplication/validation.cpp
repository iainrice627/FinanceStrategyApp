#include<iostream>
#include "validation.h"
#include <string>
#include "menu.h"
#include "portfolio.h"
#include <regex>


void Validation:: ValidLoginUserName(std::string username) {

	//if it is null?

}

void Validation:: ValidLoginPassword(std::string password) {

	//if it is null?

}

std::string Validation::ValidClientID(std::string clientID) {

	
	std::regex pattern(R"(^[A-Z]{2}[0-9]{5}$)");

	std::smatch match;

	try {

		if (std::regex_match(clientID, match, pattern)) {

			return clientID;
		}
		else
		{

			throw std::runtime_error("Client ID format is invalid.");
		}
	}
	catch(const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;

		//recall the show login page. 
	}




}


int  Validation::ValidMenuSelection(int selection) {


		if (selection >= 1 && selection <= 5)
		{
			return selection;
		}
		else
		{
			std::cout << std::endl;
			throw std::runtime_error("Invalid Selection");
			std::cout << "Invalid input: " << selection << std::endl;
			std::cout << "Enter either 1 2 3 4 or 5." << std::endl;
			std::cout << std::endl;
		}
	

}


std::string Validation::ValidStock(std::string userChosenStock) {

		if (!Menu::CheckStockList(userChosenStock))
			throw std::runtime_error("Invalid stock ID");

		return userChosenStock;

}

double Validation:: ValidPercentage(double userPercentChoice) {


		if (userPercentChoice <= 999 && userPercentChoice >= -999) 
		{

			return userPercentChoice;

		}
		else 
		{
			throw std::runtime_error("Not a valid percentage input");
			std::cout << "Error: The percetnage is limited to under 1000 or above -1000. Input was " << userPercentChoice << std::endl;

		}

}

double Validation:: GetDouble()
{
	double value;

	while (true)
	{
		std::cout << "Enter percentage: ";

		if (std::cin >> value)
			return value;   

		else {

			std::cout << "Error: please enter a numeric value.\n";

			std::cin.clear();              // clear fail state
			std::cin.ignore(10000, '\n');  // discard invalid characters
		}
		
	}
}


int Validation::GetInterger() {

	int value;

	while (true)

	{
		std::cout << "Enter Number of shares: ";
		if (std::cin >> value)
			return value;

		else if (value <= 0) {

			std::cout << "Error: please enter a numeric value greater than 0.\n";

			std::cin.clear();              // clear fail state
			std::cin.ignore(10000, '\n');  // discard invalid characters
		}

		else {

			std::cout << "Error: please enter a numeric value.\n";

			std::cin.clear();              
			std::cin.ignore(10000, '\n');  

		}

	}
}



int Validation::ValidNumberOfShares(int number_of_shares, std::string chosenStock, Portfolio& portfolio) {

	 
	double percentagePortfolio = CheckPurchaseAsPercentageofPortfolio(number_of_shares, chosenStock, portfolio);

		if (percentagePortfolio <= 10) {

			return number_of_shares;
		}
		else {
			std::cout << std::endl;
			std::cout << "This prgoram prevents purchases that make stock ownership beyond 10% of this portfolio." << std::endl;
			std::cout << "Your order would make " << chosenStock << " " << percentagePortfolio << "% of your whole portfolio." << std::endl;
			return number_of_shares == 0;

		}

}


std::string Validation::ValidGenerateStockID(std::string stockID) {

	
	  std::regex pattern(
		  R"REG(^([A-Z]{1,5}(\.[A-Z])?)-([0-3][0-9][0-1][0-9][0-9]{4})-([A-Z]{2}[0-9]{5})$)REG"
	  );



	std::smatch match;

	try {

		if (std::regex_match(stockID, match, pattern))
		{
			return stockID;
		}
		else 
		{
			throw std::runtime_error("Stock ID format is invalid.");
		}
	}
	catch (const std::exception& e) {

		std::cout << "Error: Stock ID does not match expected pattern." << e.what() << std::endl;
		std::cout << "Error: stockID produced " << stockID << ".  Correct example version = AMZN-30042026-IR12345" << std::endl;

	}


}


std::string  Validation::ValidDateString(std::string formattedTime) {

	std::regex pattern(R"(^([0-3][0-9]/[0-1][0-9]/[0-9]{4})$)");

	std::smatch match;
	
		if (!std::regex_match(formattedTime, match, pattern))
		{
			throw std::runtime_error("Date format is invalid.Correct example version = 30/04/2026");
		}
		
		
	return formattedTime;

	//does not check 32 days or 15months or years in the past or future


}




void Validation::StockConstructor(std::string name, int number_of_shares, double price_of_purchase) {

	
	ValidName(name);
	

}

void Validation::ValidName(std::string name) {


	if (name == "") {
		throw std::runtime_error("Name is invalid. Name must have some value");
		
	}

	ValidStock(name);


}


double Validation::CheckPurchaseAsPercentageofPortfolio(int number_of_shares, std::string chosenStock, Portfolio& portfolio) {

	
	int totalSharesStock = portfolio.GetTotalSharesOfStock(chosenStock);
	
	int totalSharesPortfolio = portfolio.GetTotalSharesPortfolio();
	
	int futureTotalShares = totalSharesPortfolio + number_of_shares;
	
	int futureStockTotalShares = totalSharesStock + number_of_shares;

	double newPercentage = (100.0 * futureStockTotalShares / futureTotalShares);

	return newPercentage;


	

	

}