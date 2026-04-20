#include <iostream>
#include "service.h"
#include "portfolio.h"
#include "menu.h"
#include "strategy.h"
#include "validation.h"

int main()
{


	//a login process will ask for user authentication. when the user confirmed we will havea  clientID.
	//choose the client from the list
	
	std::string clientID = Service::DisplayClients();
		

	Portfolio portfolio(clientID);
	Portfolio& refportfolio = portfolio;

	//set the DB passwrod
	portfolio.SubmitDBPassword();


	Service::LoadPortfolioSQL2(refportfolio);
	Menu::LoadDictionary(refportfolio);
	

	while (true) {
		try {
			Menu::DisplayMenuOptions();
			int selection = Menu::ListenMenuChoice();
			bool status = Menu::DetermineAction(selection, refportfolio);

			if (!status)
				break;
		}
		catch (const std::exception& e) {
			std::cout << std::endl;
			std::cout << "Error: " << e.what() << std::endl;
			std::cout << "Returning to menu..." << std::endl;
			
		}

	}
	
		
		



}
