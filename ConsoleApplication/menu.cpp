#include <iostream>
#include <fstream>
#include <string>
#include "menu.h"
#include "strategy.h"
#include "validation.h"
#include "service.h"




Dictionary Menu::stocksAndValues;

void Menu::DisplayMenuOptions()

{
	std::cout << std::endl;
	std::cout << "Select one of the options in the Menu by pressing 1, 2, 3, 4 or 5." << std::endl;
	std::cout << std::endl;
	std::cout << "Option 1: Enter Stock Performance" << std::endl;
	std::cout << "Option 2: Find Stock" << std::endl;
	std::cout << "Option 3: Test Data" << std::endl;
	std::cout << "Option 4: Show Portfolio" << std::endl;
	std::cout << "OPtion 5: Exit" << std::endl;
	std::cout << std::endl;

}

int Menu::ListenMenuChoice() {

	while (true) {

		int selection;
		std::cin >> selection;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "Input failed. Try again." << std::endl;
			continue;
		}

		return Validation::ValidMenuSelection(selection);
	}
			
}

void Menu::TESTDisplayMenuOptions()

{
	std::cout << std::endl;
	std::cout << "Select one of the options in the Menu by pressing 1, 2, 3, 4 or 5." << std::endl;
	std::cout << std::endl;
	std::cout << "Option 1: Enter Stock Performance" << std::endl;
	std::cout << "Option 2: Find Stock" << std::endl;
	std::cout << std::endl;
	std::cout << "Option 4: Show Portfolio" << std::endl;
	std::cout << "OPtion 5: Exit" << std::endl;
	std::cout << std::endl;

}







bool Menu::DetermineAction(int selection, Portfolio& portfolio) {

	
		if (selection == 1) {

			return Option1(portfolio);
		}

		else if (selection == 2) {

			return Option2(portfolio);
		}

		else if (selection == 3) {

			return  Option3(portfolio.GetClientID());

		}

		else if (selection == 4) {

			return Option4(portfolio);

		}

		else if (selection == 5) {

			return Option5(portfolio);
			
		}

		else {

			return true;

		}


}



bool Menu::TESTDetermineAction(int selection, Portfolio& portfolio) {


	if (selection == 1) {

		return Option1(portfolio);
	}

	else if (selection == 2) {

		return Option2(portfolio);
	}

	else if (selection == 4) {

		return Option4(portfolio);

	}

	else if (selection == 5) {

		return TESTOption5();

	}

	else {

		return true;

	}


}

//void Menu::DisplayStockList() {
//
//	std::cout << std::endl;
//	std::cout << "List of available Stocks to purchase and sell." << std::endl;
//	std::cout << std::endl;
//
//	for (int i = 0; i < size; i++) {
//		
//		std::string name = stocksList[i];
//		std::cout << name << std::endl;
//
//	}
//}

void Menu::DisplayStockList() {


	std::cout << std::endl;
	std::cout << "List of available Stocks to purchase and sell." << std::endl;
	std::cout << std::endl;

	for (auto it : stocksAndValues) {

		std::cout << it.first << ": " << it.second << std:: endl;

	}


}



bool Menu::Option1(Portfolio& portfolio)
{

	std::cout << std::endl;
	std::cout << "This program does not automatically change the value of stocks by listening to a live feed of updated stock prices. To determine your strategy you should enter your stock and the change of value, as a % from the last price." << std::endl;
	std::cout << "For example: You need to know 1) the price this program holds for the stock. 2)know the new prIce, 3) calculate the % change and 4) input that percentage chnage when prompted." << std::endl;
	std::cout << std::endl;
	//we should insert the new value of the stock and automatically workout the percetnage chnange rther than insert the percentage change.
	std::cout << "See a list of the available stocks."  << std::endl;
	std::cout << std::endl;
	DisplayStockList();
	std::cout << std::endl;

	/// memeory errror. corruption of userChosenStock happening in and around cin. comeing out wrong. _Ptr is overwritten with the bytes "AMZN"

	std::string userChosenStock = "";
	std::cout <<"Enter the name of an available stock." << std::endl;
	std::cin >> userChosenStock;
	


	std::string chosenStock = Validation::ValidStock(userChosenStock);
	std::cout << "Enter the 'change in value' as a percantage(%), of your chosen stock. eg 1.0, 0.5, -1.5, 20.0, -20.0 etc.  " << std::endl;
	double userPercentChoice = Validation::GetDouble();
	double percentChoice = Validation::ValidPercentage(userPercentChoice);

	
	Strategy:: Strategy1(percentChoice, chosenStock, portfolio);

	
	return true;
	
}


bool Menu::Option2(Portfolio& portfolio)

{

	portfolio.DisplayStock(); 

	return true;

}


bool Menu::Option3(std::string clientID)

{
	// load database into a testportfolio object
	
	Portfolio testPortfolio(clientID);

	Portfolio& refportfolio = testPortfolio;

	Service::LoadPortfolioSQL2(refportfolio);
	Menu::LoadDictionary(refportfolio);

	while (true) {
		try {
			Menu::TESTDisplayMenuOptions();
			int selection = Menu::ListenMenuChoice();
			bool status = Menu::TESTDetermineAction(selection, refportfolio);

			if (!status)
				break;
		}
		catch (const std::exception& e) {
			std::cout << std::endl;
			std::cout << "Error: " << e.what() << std::endl;
			std::cout << "Returning to menu..." << std::endl;

		}

	}


	// 
	// 
	//Practice(); //????
	// we need to create some test objects and re call all the methods but save to these new test objects, so we are not impacting the real version and then not save the changes made.
	return true;

}

bool Menu::Option4(Portfolio& portfolio)

{
	portfolio.DisplayPortfolio();  

	return true;
}



bool Menu::Option5(Portfolio& portfolio)

{

	/*Service::SavePortfolio(portfolio);*/
	Service::SavePortfolioSQL2(portfolio);

	std::cout << std::endl;
	std::cout << "Logging Out User and Reloading login page" << std::endl;
	return false;

}


bool Menu::TESTOption5()

{

	std::cout << std::endl;
	std::cout << "Logging Out User and Reloading login page" << std::endl;
	return false;

}


//void Menu::LoadStockList() {
//
//	
//	std::ifstream stockListFile;
//	
//	stockListFile.open("stockList.txt");
//
//	if (stockListFile.is_open()) {
//
//		std::string lines;
//
//		while (getline(stockListFile, lines)) {
//			if (size >= capacity) {
//				std::cerr << "Stock list exceeds 100 entries\n";
//				break;
//			}
//			stocksList[size] = lines;
//			size++;
//
//		}
//
//	}
//	
//	stockListFile.close();
//
//}

void Menu::LoadDictionary(Portfolio& portfolio) {

	MYSQL* connection = Service::ConnectToDatabase(portfolio);

	

	if (mysql_query(connection, "USE Portfoliodb") != 0) {
		std::cout << "SQL USE command failed: " << mysql_error(connection) << std::endl;
		mysql_close(connection);
		return;
	}

	std::string query = "SELECT stockName, value FROM stocksvalue;";

	if (mysql_query(connection, query.c_str()) != 0) {
		std::cout << "SELECT failed: " << mysql_error(connection) << "\n";
		mysql_close(connection);
		return;

	}

	MYSQL_RES* result = mysql_store_result(connection);

	if (result == nullptr) {
		std::cout << " No result set: " << mysql_error(connection) << std::endl;
		mysql_close(connection);
		return;

	}

	MYSQL_ROW row;

	while ((row = mysql_fetch_row(result)) != NULL) {
	
		stocksAndValues[row[0]] = atof(row[1]);
	
	}

	mysql_free_result(result);
	mysql_close(connection);


}


//bool Menu::CheckStockList(std::string userChosenStock) {
//
//
//	for (auto it : stocksAndValues) {
//
//		if (it.first != userChosenStock) {
//
//			//do nothing
//			}
//
//			else {
//
//					return true;
//			}
//
//	}
//
//}

bool Menu::CheckStockList(std::string userChosenStock) {
	for (auto it : stocksAndValues) {
		if (it.first == userChosenStock) {
			return true;
		}
	}
	return false;
}



Dictionary& Menu::GetStocksandValues() {

	return stocksAndValues;



}






