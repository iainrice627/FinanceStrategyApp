#Finance Strategy Console App

This is another university assignment using C++.  The task was to use Stacks and Queues and a simple Data Array to manage 'Stock's.  Essentially objects with values were kept in a class array. 
The program presents a menu with choices. The main feature of the app is to change the value of the stock and, depending on that input, call on some actions such as 'buy' and 'sell' stocks.  
There are other features such as viewing the portfolio of all the stocks the user owns, viewing details a of a specifc stock, and testing a strategy without making permanent changes.

The queues and stacks are templates so they can be used for different types of objects or types of variables. There are further features and alternative interpretations of the assignment that have been added to this version.

The user needs to select the client at the start of the program, which will load a portfolio.  A list of clients is kept on a text file, and is read by the program and displayed to the user.
Each portfolio in the program belongs to an individual client, so only the stocks that belong to that client are loaded into the program for the user to see.  The program deliberatly does not load any data that belongs to other clients.  All the clients records are kept in a MySQL database (which is a local storage and wont work if this were to be downloaded. You would need to implement this on your local drive, but the text files for loading data are within this respository called stocksDB.csv and stocksList.csv.  The program using SQL langauage to find the relavent records for this client, the program updates them and it will save the changes into the database. 

It was orginally a project that forbade the use of libraries but libraries have been added in some classes as new features were added, such as using regex for validatrion or Mysql libraries.


The fundamentals have been completed, however there is a list of jobs to complete the ongoing project.



====new code + new business logic=====/n
-when we change value of stock, it is done in the program and not in the database - to change databsde too we need to read databse, find all stocks name and get most recent current value. use to create new price. read database and change/write over the part of current value with new price.  Thoughts - We sould change the values in the dictionary, but we could also leave this so every time a new user is loaded their values of their stocks are re-calculated each time they are uploaded.  This would mean leaving clients that are not loaded in with records in the database that are out of date. Because this system only relies on manual inputs to change the stock values, this could be ok, but if this were trying to work with live feeds of a constantly changing stock price, we would want regular updates in the database and triggers from the database if someones stock was depreciating or going up in value, with a prompt/message to the user or client for an 'advised strategy'.  
=======I wont be implementing this as it is an entirely new project, which would require some web application approach using APIs to get stock price updates and some sort of way to keep a program running and live for 24 hours or how ever long stock prices get changed.  Further extenstions to view stocks from other markets would be interesting.  ======


#To do
#
create the login and password feature using the client list and somehow passwords (gernally figure out user authentication)

change the get date and time to prevent dates above 31 days or in the future.

create and run test project mehtods.

consider a better GUI. - turn into a GUI using some framwork eg .NET


