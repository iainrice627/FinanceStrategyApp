#Finance Strategy Console App

This is another university assignment using C++.  The task was to use Stacks and Queues and a simple Data Array to manage 'Stock's.  Essentially objects with values weer kept in a class array. 
The program presents a menu with choices. The main feature of the app is to chnage the value of the stock, and depending on that input call on some actions such as buy and sell stocks.  
There are other features such as viewing the portfolio of all the stocks the user owns, viewing details aof a specifc stock, and testing a strategy without making permanent changes.

The queues and stacks are templates so they can be used for different types of objects or types of variables. There are further features and alternative interpretations of the assignment that have been added to this versino.
Each portfolio belongs to an individual cleint so only stocks that belong to the client are loaded into the program for th user to see. the user need to select the client at the start of the program. 
There are text files that contain the records of all the stocs being handled by the program.  The stock reecrds are all contained in one text file. These stocks belong to various clients. 
The program will read the file and extract only the records that belong to the client. 

It was orginally a project that forbade the use of libraries but libraries have been added in some classes as new features were added.

The fundamentals have been completed, hwoever there is a list of jobs to complete the ongoing project.

#To do

new code - when change value of stock not in porfolio - read file find all stocks name and get most recent current value. use to create new proce. read file and change write over the part of current value with new price.
create randomID numner for Id gnerator and insert random number code into stockID
update Regex for stockID
write code for updating CREDIT - portfolio
write code for Update currentValueStock
write caode for save portfolio
update the client login so a input that doesnt match list is not accepted. 
create the login and password feature using the client list and somehow passwords (gernally figure out user authentication)
create a back feature to exit an option at any point to return to menu.
create option 3 practice feature.
change the whole insert percentage change and use a way to get live change in prices of real prices.- turning the feature into a webapplication.
change the get date and time to prevent dates above 31 days or in the future.
review validation of constuctors
create and run test project mehtods.
consider a better GUI. - turn into a GUI using some framwork eg .NET
replace text files with a SQL database.  

#update 

Problems - no updates on current value happening. not impacting the saved values in text files.
Actions -inserted code to access a MySQL database - kept on local harddrive for now. Also using a dictionary to store the lsits of stocks and included their value per share and kept in Menu class.
Intention is to use the dictionary to get calues, calcualte sales and buys prices from the values and ensure the update methods pass values and not 0's

#To do

contonue to repair the calcualte and update values for all the stocks in runtime and in database, when values are changed.
update the client login so a input that doesnt match list is not accepted. 
create the login and password feature using the client list and somehow passwords (gernally figure out user authentication)
create a back feature to exit an option at any point to return to menu.
create option 3 practice feature.
change the whole insert percentage change and use a way to get live change in prices of real prices.- turning the feature into a webapplication.
change the get date and time to prevent dates above 31 days or in the future.
create and run test project mehtods.
consider a better GUI. - turn into a GUI using some framwork eg .NET
