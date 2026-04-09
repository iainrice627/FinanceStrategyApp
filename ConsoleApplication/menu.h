#ifndef MENU_H
#define MENU_H


#include<iostream>
#include "portfolio.h"
#include "service.h"


class Menu {

private:

	static const int capacity = 100;
	static std::string stocksList[capacity];
	static int size;

public:


	static void DisplayMenuOptions();
	static int ListenMenuChoice();
	static bool DetermineAction(int selection, Portfolio& portfolio);
	static bool Option1(Portfolio& portfolio);
	static bool Option2(Portfolio& portfolio);
	static bool Option3();
	static bool Option4(Portfolio& portfolio);
	static bool Option5(Portfolio& portfolio);
	static void DisplayStockList();
	static void LoadStockList();
	static bool CheckStockList(std::string userChosenStock);





};








#endif 

