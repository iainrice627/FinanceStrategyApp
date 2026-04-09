#include "service.h"
#include <iostream>
#include "ctime"
#include "stock.h"
#include "stack.h"
#include "portfolio.h"
#include <fstream>
#include <string>
#include <sstream>
#include "validation.h"
#include <vector>


Stock Service::CreateStock(std::string name, int number_of_shares, double price_of_purchase, std::string clientID) {


    
    std::string date_of_purchase = GetTime();
    std::string stockID = GenerateStockID(name, clientID, date_of_purchase);
    double current_value = price_of_purchase;
    Validation::ValidDateString(date_of_purchase);
    Validation::ValidGenerateStockID(stockID);
    Validation::ValidClientID(clientID);
    Validation::StockConstructor(name, number_of_shares, price_of_purchase);

    Stock stock(name, number_of_shares, price_of_purchase, clientID, stockID, date_of_purchase, current_value);

    return stock;
}




void Service::LoadPortfolio(Portfolio& portfolio) {


    std::ifstream fin;

    fin.open("stocksDB2.txt");

    if (fin.is_open()) {

        Stock stock;
        std::string line;

        while (std::getline(fin, line)) {

            std::stringstream stream(line);

            stream >> stock.stockID >> stock.name >> stock.number_of_shares >> stock.date_of_purchase >> stock.price_of_purchase >> stock.current_value >> stock.clientID;
            
           if (stock.clientID == portfolio.GetClientID()) {

                portfolio.AddStock(stock);
            }
            
        }

        fin.close();

    }
    else {
    
        std::cout << "Error!: Portfolio not loaded\n";
    }




}



void Service::SavePortfolio(Portfolio& portfolio) {

    //save the portfoliolist to the database of the other records.
    //there will already be records for this record but there now may be edits and new stocks with the client id to add. we want to overwrite any existing ones with our ones, but only with this client id, and then add to the end any new ones.
    //we probably need to read the file first, and compare the two things. the list in the program and the contents of this while text file.
    //where are the record that have this client ID, what lines in the text file are they in. i can use stock id to pair ones in program to text file.
    // copy the stockIDs from program file and overwrite the lines that have the same stockID.
    // if there are new stockIDs in the porgram file, that are not in the text file, then add to the bottom of the text file in empty lines.

    // you can then create a copy bu creating a new thing fout. and a textcopy . fout.open copything will create a file if its not there.
    //instead of fin.get(ch); to get the characters.its fout.put(ch); to put each character in.


}




std::string Service::DateTime(time_t time, const char* format)
{
    char buffer[90];
    struct tm timeinfo;
    
    localtime_s(&timeinfo, &time);  

    strftime(buffer, sizeof(buffer), format, &timeinfo);
    return buffer;
}



std::string Service::GetTime() {


	std::time_t now = std::time(nullptr);

	//const char* format = "%Y-%m-%d %H:%M:%S";
    const char* format = "%d/%m/%Y";


	std::string formattedTime = DateTime(now, format); 

    return formattedTime;
}


//=================

//https://www.geeksforgeeks.org/cpp/date-and-time-parsing-in-cpp/



std::string Service::GenerateStockID(std::string name, std::string clientID, std:: string date_of_purchase) {

    date_of_purchase.erase(2, 1);
    date_of_purchase.erase(4, 1);
   //inset a random number here. call a random number genrator

    std::string stockID = name + "-" + date_of_purchase + "-" + clientID;

    return stockID;

}


double Service::CalculateNewStockPrice(std::string chosenStock, int userPercentChoice, Portfolio& portfolio) {

  

    int size = portfolio.GetSizePortfolio();
    
    Stack<int>stocksIndices(size);

    for (int i = 0; i < size; ++i) {

        Stock stock = portfolio.AccessSpecificStock(i); 

        if(stock.name == chosenStock){

            stocksIndices.push(i);
        }

    }

    if (stocksIndices.empty())
    {
        return 0.0;
    }

    int latestIndex;
    
    stocksIndices.pop(latestIndex);  
    
    Stock latestStock = portfolio.AccessSpecificStock(latestIndex);  

    double basePrice = latestStock.price_of_purchase;

    double newStockPrice = basePrice + (basePrice * (userPercentChoice / 100.0));

    latestStock.current_value = newStockPrice;

    portfolio.SetStockAt(latestIndex, latestStock);

    return newStockPrice;
}


std::vector<std::string> Service::GetClients() {

    std::ifstream clientsFile;

    clientsFile.open("clientList.txt");

    if (clientsFile.is_open()) {

        std::string lines;
        std::vector<std::string> clients;

        while (getline(clientsFile, lines)) {

            clients.push_back(lines);
        }
        return clients;
    }

    else {

        std::cout << "Error: Could not open file" << std::endl;

    }

    clientsFile.close();

}

std::string Service::DisplayClients() {

    std::cout << std::endl;
    std::cout << "Select the client, whose portfolio is to be managed." << std::endl;
    std::cout << std::endl;
    std::vector<std::string> clients;

    clients = Service::GetClients();

    int size = clients.size();

    for(int i = 0; i < size; ++i) {

        std::cout << clients[i] << std::endl;

    }

    std::cout << std::endl;
    std::string selection = Service::SelectClient();

    return selection;

}

std::string Service::SelectClient() {

    std::string clientID;

    std::cin >> clientID;

    //validation of user input.

    return clientID;


}







