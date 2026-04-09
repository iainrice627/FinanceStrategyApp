#ifndef STOCK_H
#define STOCK_H

#include<iostream>




class Stock {

private:

	

public:
	std::string stockID;
	std::string name;
	int number_of_shares;
	std::string date_of_purchase;
	double price_of_purchase;
	double current_value;
	std::string clientID;
	

	Stock();

	Stock(std::string name, int number_of_shares, double price_of_purchase, std::string clientID, std::string stockID, std::string date_of_purchase,double current_value);


	
	


};

#endif
