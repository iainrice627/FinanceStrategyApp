#include <mysql.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "ctime"

#include "stock.h"
#include "stack.h"
#include "portfolio.h"
#include "validation.h"
#include "service.h"
#include "menu.h"








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





MYSQL* Service::ConnectToDatabase(Portfolio& portfolio) {

    std::string clientID = portfolio.GetClientID();
    std::string password;
    std::cout << std::endl;
    std::cout << "Enter the password for the database: " << std::endl;
    std::cin >> password;

    MYSQL* connection = mysql_init(NULL);

    if (connection == NULL) {

        std::cout << "Connection1 failed: " << mysql_error(connection) << std::endl;
        mysql_close(connection);
        return nullptr;

    }

    if (mysql_real_connect(connection, "localhost", "root", password.c_str(), NULL, 0, NULL, 0) == NULL) {

        std::cout << "Connection2 failed: " << mysql_error(connection) << std::endl;
        mysql_close(connection);
        return nullptr;

    }

    return connection;




}


void Service::LoadPortfolioSQL2(Portfolio& portfolio) {

	MYSQL* connection = ConnectToDatabase(portfolio);

    std::string clientID = portfolio.GetClientID();

    if (mysql_query(connection, "USE Portfoliodb") != 0) {
        std::cout << "SQL USE command failed: " << mysql_error(connection) << std::endl;
        mysql_close(connection);
        return;
    }

    std::string query = "SELECT stocksID, name, number_of_shares, date_of_purchase, price_of_purchase, current_value, clientID " "FROM stocks WHERE clientID = '" + clientID + "'";

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


    while ((row = mysql_fetch_row(result)) != NULL) {   //Always fetch and test in the same while condition:

        Stock stock;

       /* stock.stockID = row[0];
        stock.name = row[1];
        stock.number_of_shares = atoi(row[2]);
        stock.date_of_purchase = row[3];
        stock.price_of_purchase = atof(row[4]);
        stock.current_value = atof(row[5]);
        stock.clientID = row[6];*/


        stock.stockID = std::string(row[0]);
        stock.name = std::string(row[1]);
        stock.number_of_shares = atoi(row[2]);
        stock.date_of_purchase = std::string(row[3]);
        stock.price_of_purchase = atof(row[4]);
        stock.current_value = atof(row[5]);
        stock.clientID = std::string(row[6]);

        portfolio.AddStock(stock);

    }

    mysql_free_result(result);
    mysql_close(connection);


}



void Service::SavePortfolioSQL2(Portfolio& portfolio) {

    MYSQL* connection = ConnectToDatabase(portfolio);

    //use connection and identify correct database.
    if (mysql_query(connection, "USE Portfoliodb") != 0) {
        std::cout << "SQL USE command failed: " << mysql_error(connection) << std::endl;
        mysql_close(connection);
        return;
    }
    
    
    //acces the list
     //std::vector<Stock> portfolioList = portfolio.GetPortfolioStocks();
     Stock* portfolioList = portfolio.GetPortfolioStocks();

     //  get the portfolio size  
     int size = portfolio.GetSizePortfolio();

     // get clientID
     std::string clientID = portfolio.GetClientID();

    

     //get a stock object, pass in its value to the stream, convert stream to string. send stream to database 
     for (int i = 0; i < size; ++i) {

         Stock stock = portfolioList[i];

         //check if the object is not in the database. then call insert for this object.

         std::string query1 = "SELECT stocksID FROM stocks WHERE stocksID = '" + stock.stockID + "'";

         if (mysql_query(connection, query1.c_str()) != 0) {

             std::cout << "SELECT failed: " << mysql_error(connection) << "\n";
             return;
            
         }

         MYSQL_RES* result = mysql_store_result(connection);
         bool exists = (mysql_num_rows(result) > 0);
         mysql_free_result(result);

         if (exists) {
         
         //update
             
             std::ostringstream oss;

             oss << "UPDATE stocks SET number_of_shares = '" << stock.number_of_shares << "', current_value = '" << stock.current_value << "' WHERE clientID = '" << stock.clientID << "' AND stocksID = '" << stock.stockID << "';";

             std::string query = oss.str();

             if (mysql_query(connection, query.c_str()) != 0) {
                 std::cout << "UPDATE failed: " << mysql_error(connection) << "\n";
                 mysql_close(connection);
                 return;

             }
             oss.str("");
             oss.clear();
         
         }

         else {
         
         //insert

             std::ostringstream oss;

             oss << "INSERT INTO stocks (stocksID, name, number_of_shares, date_of_purchase, price_of_purchase, current_value, clientID) VALUES ("<< "'" << stock.stockID << "', "<< "'" << stock.name << "', "<<stock.number_of_shares << ", "<< "'" << stock.date_of_purchase << "', "<< stock.price_of_purchase << ", "<< stock.current_value << ", " << "'" << clientID << "');";

             std::string query = oss.str();

             if (mysql_query(connection, query.c_str()) != 0) {
                 std::cout << "INSERT failed: " << mysql_error(connection) << "\n";
                 mysql_close(connection);
                 return;
             }
             oss.str("");
             oss.clear();

         }
      

     }

     std::cout << "DB updated. Closing connection" << std::endl;
     mysql_close(connection);

    
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


double Service::CalculateNewStockPrice(std::string chosenStock, double userPercentChoice, Portfolio& portfolio) {

   
    int size = portfolio.GetSizePortfolio();
    
    Stack<int>stocksIndices(size);

    for (int i = 0; i < size; ++i) {

        Stock stock = portfolio.AccessSpecificStock(i);

        if(stock.name == chosenStock){

            stocksIndices.push(i);
        }

    }

    int latestIndex;
    
    stocksIndices.pop(latestIndex);  
    
    Stock latestStock = portfolio.AccessSpecificStock(latestIndex);  


    //double basePrice = latestStock.price_of_purchase;
    
    Dictionary dictionary = Menu::GetStocksandValues();

    //find the stock in the dictinoary

    double basePrice = GetPrice(dictionary, chosenStock);

    double newStockPrice = basePrice + (basePrice * (userPercentChoice / 100.0));

    latestStock.current_value = newStockPrice;

    // need to re update the dictionary value. 

    UpdateCurrentValue(dictionary, newStockPrice, chosenStock);
    
    // make sure the stock item in this method, gets to the portfolio.
    portfolio.SetStockAt(latestIndex, latestStock);

    return newStockPrice;
}

//when a user inserts a new value, the program will choose the strategy and will act with the new price. 
//we buy at the new price. so the new items will have its price of purchase and current value set to new price.
//we sell at the new price. 
//the dictionary value fo the stock will be changed to the new price.
//we need to check if the stocks in this portfolio will have been chnaged to new current value. YES if there is another one in there. but if not it will do nothing. the dictionary will be ok but the other stocks in the database belonging to other clients will be unchanged. 
    // options - leave database alone and insert a update prices when program loads.  and then the user can use new prices after this and it get saved again the stocks list of values. means values in database could be wrong for long time, if a stock is not selected for the program.
    //optins - need some update the database method to happen as soon as the value has chnaged.


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

    //int size = clients.size();
    std::size_t size = clients.size();

    for(int i = 0; i < size; ++i) {

        std::cout << clients[i] << std::endl;

    }

    std::cout << std::endl;
    std::string selection = Service::SelectClient(clients, size);

    return selection;

}

std::string Service::SelectClient(std::vector<std::string> clients, int size) {

    std::string clientID;

    std::cin >> clientID;

    for (int i = 0; i < size; ++i) {

        if (clients[i] == clientID) {

            return clientID;
        }


    }

    std::cout << "ERROR: ClientID inputed is InValid." << std::endl;
    throw std::runtime_error("ClientID not found: " + clientID);

   


}


double Service::GetPrice(Dictionary& dictionary, std::string chosenStock) {

    auto item = dictionary.find(chosenStock);
    if (item != dictionary.end()) {

        double basePrice = item->second;
        return basePrice;
    }
    else {
        std::cout << "Stock '" << chosenStock << "' not found in dictionary.\n";
        throw std::runtime_error("Stock not found: " + chosenStock);
    }

    

}

void Service::UpdateCurrentValue(Dictionary& dictionary, double newStockPrice, std::string chosenStock) {

    auto item = dictionary.find(chosenStock);
    if (item != dictionary.end()) {

        item->second = newStockPrice;
        
    }
    else {
        std::cout << "Stock '" << chosenStock << "' not found in dictionary.\n";
        
    }

    


}

static void UpdateDatabase(double newStockPrice, std::string chosenStock) {

    // we have the double price. we have the name of the stock want to change.
    //need to conenct to the databae.
    //update all the records with same stock name, irrespective of who they belong to.
    //  do we exlcude the ones  belonging to clientID that matches the user of this program, becasue the save method will update. this could happen at the save feature. BUt a user may haev changed multiple stocks values in the progra, runtime. 
        //WHAT DOES SAVE DO?  it gets the clients stocks in question and updates thier records in DB with new values in DB. it inserts any new records created in runtime. some stocks will have been changed, others will not. 
        //how do we tell the database to update the currentvalue
        
                //when? when calcute new price called?  when saving the program and exiting?  
                // this would be easier if this was a bespoke Client database but its a global database with records nbleonging to many clients. i wonder if design of database is problem or is the point og using mysql, so we can create order.


}







