#include <iostream>
#include "stock.h"
#include "portfolio.h"


//stock defualt constructor
Stock::Stock() : name(""),number_of_shares(0),price_of_purchase(0.0),clientID(""),stockID(""),date_of_purchase(""),current_value(0.0)
{

	
}



//stock constructor 
Stock::Stock(std::string name, int number_of_shares, double price_of_purchase, std::string clientID, std::string stockID, std::string date_of_purchase, double current_value) {
	this->stockID = stockID;
	this->name = name;
	this->number_of_shares = number_of_shares;
	this->date_of_purchase = date_of_purchase;
	this->price_of_purchase = price_of_purchase;
	this->current_value = current_value;
	this->clientID = clientID;

}


