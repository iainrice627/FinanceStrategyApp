#include "pch.h"
#include "CppUnitTest.h"
#include "portfolio.h"
#include "menu.h"
#include "service.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestConstructor)
		{
			//set up
			std::string clientId = "AB12345";
			int size = 0;
			double total_porfolio_value = 0.0;
			double total_spent = 0.0;
			double credit = 0.0;
			std::string clientID = clientId;

			//do something
			Portfolio portfolio(clientID);

			//check it worked
			Assert::AreEqual(size, portfolio.GetSizePortfolio());
			Assert::AreEqual(total_porfolio_value, portfolio.GetTotalPorfolioValue());
			Assert::AreEqual(total_spent, portfolio.GetTotalSpent());
			Assert::AreEqual(credit, portfolio.GetCredit());
			Assert::AreEqual(clientId, portfolio.GetClientID());


		}

		TEST_METHOD(TestSellEarliest) 
		{
			//set up values we need for this function to work.
			std::string clientID = "AB12345";
			Portfolio portfolio(clientID);
			std::string chosenStock = "AMZ";
			int userPercentChoice = 5; // THERE ARE MULTIPLE ONES WE WANT TO INSERT. I WANT TO SUBMIT 5 AND 20.
			Service::LoadPortfolio(portfolio);
			Menu::LoadStockList();
			double newStockPrice = Service::CalculateNewStockPrice(chosenStock, userPercentChoice, portfolio);
		
			//expected answers we expect from the function - to check against.
			// we need to know what index it should be. int index = 50;
			// we need to know new exoected portfoliovalue  
			// we need to know the new expected credit value
			// we need to know which index/stock gets removed from portfolio list.
			

			//do something
			portfolio.SellEarliest(chosenStock, newStockPrice);
			
			//check it worked

			//assert that the expected answer equals what the function did.






		}

		TEST_METHOD(TestSellLatest)
		{

			std::string clientID = "AB12345";
			Portfolio portfolio(clientID);
			Service::LoadPortfolio(portfolio);
			Menu::LoadStockList();

			//INDEX 52

		}

		TEST_METHOD(TestBuy)
		{

			std::string clientID = "AB12345";
			Portfolio portfolio(clientID);
			Service::LoadPortfolio(portfolio);
			Menu::LoadStockList();

			//NEW ONE AT INDEX 53



		}






	};
}
