#include <iostream>
#include "strategy.h"
#include "portfolio.h"
#include "service.h"




void Strategy:: Strategy1(double userPercentChoice, std::string chosenStock, Portfolio& portfolio) {

	double newStockPrice = Service::CalculateNewStockPrice(chosenStock, userPercentChoice, portfolio);

	if (userPercentChoice > 0)
	{
		if (userPercentChoice >= 5 && userPercentChoice <= 20) {

			portfolio.SellEarliest(chosenStock, newStockPrice);
			
		}

	}

	else if (userPercentChoice < 0)
	{

		if (userPercentChoice >= -1 && userPercentChoice <= -0.5) {

			portfolio.Buy(chosenStock,newStockPrice);
						
		}

		else if (userPercentChoice >= -3 && userPercentChoice <= -1.1) {
			
			portfolio.SellLatest(chosenStock, newStockPrice);
			
		}

	}

	else
		std::cout << "No trading has taken place." << std::endl;

};

