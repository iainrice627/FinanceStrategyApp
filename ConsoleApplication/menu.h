#ifndef MENU_H
#define MENU_H

#include<map>
#include<iostream>
#include "portfolio.h"
//#include "service.h"

//std::map<std::string, double> Menu::stocksAndValues;
using Dictionary = std::map<std::string, double>;

class Menu {

private:

	//static const int capacity = 100;
	//static std::string stocksList[capacity];
	//static int size;

	static std::map<std::string, double> stocksAndValues;


public:


	static void DisplayMenuOptions();
	static int ListenMenuChoice();
	static bool DetermineAction(int selection, Portfolio& portfolio);
	static bool Option1(Portfolio& portfolio);
	static bool Option2(Portfolio& portfolio);
	static bool Option3(std::string clientID);
	static bool Option4(Portfolio& portfolio);
	static bool Option5(Portfolio& portfolio);
	static void DisplayStockList();
	static void LoadDictionary(Portfolio& portfolio);
	static bool CheckStockList(std::string userChosenStock);
	//static std::map<std::string,double> GetStocksandValues();
	static Dictionary& GetStocksandValues();

	static void TESTDisplayMenuOptions();
	static bool TESTDetermineAction(int selection, Portfolio& portfolio);
	static bool TESTOption5();




};








#endif 

