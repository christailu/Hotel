//---------------------------------------------------
//Name: Christelle Mbemba
//Course-Sectio: CS 155-section
//Project: #4
// Due date: 16/11/2022
//Resources: notes from class, tutoring
//Description:  the Program is simulating a booking system, the user can book from 
//				three different Hotel. the program will print an output receipt
//-----------------------------------------------------

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

// constant for the the percentage of taxes (4% of taxes in this case)
double const TAXE = 0.04;

//Functions Declarations
void displayHotels();
int getHotelChoice();
bool readRoomPrices( int userChoice, string& hotelName, double& oneQueen, double& twoQueen,
                    double& oneKing, double& twoKing, double& luxury);
void displayRoomPrices(string hotelName, double oneQueen, double twoQueen,
                    double oneKing, double twoKing, double luxury);
int getRoomChoice();


int getNumRooms();
int getNumNight();
double addToOrder(double costOfRoom, int nightBooked, int roomBooked, double& subTotal );
double calculateTaxes( double subAmount);
void printReceipt(string hotelName, int numberOfRoom, int numberOfNight, double costOfRoom,
                  double subTotal, double taxeFee, ofstream& receipt );

//*********************************
// driver ** main function **
//*********************************
int main(){
	int selection = 1;
	int roomSelection;
	int numberOfRoom;
	int numberOfNight;
	string hotelName;
    double oneQueen, twoQueen, oneKing, twoKing, luxury;
	double costOfTheRoom;
	double subTotal;
	double taxeFee;
	
	// variable for the output file
	ofstream receipt("OutCIM.txt");
	
	displayHotels();	
	selection = getHotelChoice();
    	
	//condition to exit the program
	while (selection != 0){
		readRoomPrices(selection, hotelName, oneQueen, twoQueen,oneKing, twoKing, luxury);
        displayRoomPrices(hotelName, oneQueen, twoQueen, oneKing, twoKing, luxury);
		roomSelection = getRoomChoice();
		numberOfRoom = getNumRooms();
		numberOfNight = getNumNight();
		
		//condition to determine the cost of the rooms
		if (roomSelection == 1){
			costOfTheRoom = oneQueen;
        }
		else if (roomSelection == 2){
			costOfTheRoom = twoQueen;
     	}		
		else if (roomSelection == 3){
	        costOfTheRoom = oneKing;			
		}	
		else if (roomSelection == 4){
			costOfTheRoom = twoKing;	
			
		}
		else if (roomSelection == 5){
			costOfTheRoom = luxury;
		
		}	
		addToOrder(costOfTheRoom, numberOfNight, numberOfRoom, subTotal);
	    taxeFee = calculateTaxes(subTotal);				
       	printReceipt (hotelName, numberOfRoom, numberOfNight, costOfTheRoom, subTotal, taxeFee, receipt);	
		

       	displayHotels();
		selection = getHotelChoice();
     
    }
    
	return 0;
}

// **************************************************************
//displayHotels
// display the menu (different hotel where the user can make a reservation)
//returns: none
//parameters: none
//pass by reference parameters: none
// **************************************************************
void displayHotels(){

	cout << "Welcocme to the Hilton Honnors Booking System!"<< endl;
	cout << "Choose an option beloow:" << endl<< endl;
	cout << "1 - Embassy Suites" << endl;
	cout << "2 - Hilton Garden" << endl;
	cout << "3 - DoubleTree" << endl;
	cout << "0 - End of the Day: Stop Processing" << endl<< endl;
}


// **************************************************************
//getHotelChoice
//ask users their choice from the menu (which hotel) where they want to book from.
//returns: userChoice
//parameters: none
//pass by reference parameters: none
// **************************************************************
int getHotelChoice(){
	int userChoice;
	cout << "Which hotel would you like to book with?: ";
	cin >> userChoice;
	
	// conditions for users to choose a value between 0 and 3 	
	while (userChoice < 0 || userChoice > 3){
		cout << "Please, choose a valid option: ";
		cin >> userChoice;	
	}
	
	cout << endl<< endl;
	
	return userChoice;	
}

// **************************************************************
//readRoomPrices
//check users choice and determine which file to open
//returns: none
//parameters: userChoice, hotelName, oneQueen, twoQueen, oneKing, twoKing, luxury
//pass by reference parameters: hotelName, oneQueen, twoQueen, oneKing, twoKing, luxury
// **************************************************************
bool readRoomPrices(int userChoice, string& name, double& oneQueen, double& twoQueen,
                    double& oneKing, double& twoKing, double& luxury){
    
    //condition to check at the user's choice to determine which file to open
	if (userChoice <= 3 || userChoice >= 0 ){
		if(userChoice == 1){
			//open the file
			ifstream Embassyfile("Embassy.txt");
			name = "Embassy Suites";
			Embassyfile >> oneQueen;
			Embassyfile >> twoQueen;
			Embassyfile >> oneKing;
			Embassyfile >> twoKing;
			Embassyfile >> luxury;	
			
			// close the file
			Embassyfile.close();			
		}
		
	
		else if(userChoice == 2){
			//open the file
			ifstream Hiltonfile("Hilton_Garden.txt");
			name = "Hilton Garden";
			Hiltonfile >> oneQueen;
			Hiltonfile >> twoQueen;
			Hiltonfile >> oneKing;
			Hiltonfile >> twoKing;
			Hiltonfile >> luxury;
			
			//close the file
			Hiltonfile.close();
		}	
		
		else if(userChoice == 3){
			//open the file
			ifstream Treefile("DoubleTree.txt");
			name = "DoubleTree";
			Treefile >> oneQueen;
			Treefile >> twoQueen;
			Treefile >> oneKing;
			Treefile >> twoKing;
			Treefile >> luxury;	
			
			//close the file
			Treefile.close();				
		}	
		
	   return true;
	}
    else
       return false;
}

// **************************************************************
//displayRoomPrices
//display the the different hotel types and their prices according to users 's choice
//returns: none
//parameters:hotelName, oneQueen, twoQueen, oneKing, twoKing, luxury
//pass by reference parameters: none
// **************************************************************
void displayRoomPrices(string hotelName, double oneQueen, double twoQueen,
                    double oneKing, double twoKing, double luxury){
    int userChoice;
    readRoomPrices(userChoice, hotelName, oneQueen, twoQueen,
                   oneKing, twoKing, luxury);

   
	cout << "Welcome to " << hotelName << endl;
	
	cout << "1 - 1 Queen: $" <<  oneQueen << endl;
	cout << "2 - 2 Queen: $" << twoQueen <<endl;
	cout << "3 - 1 King: $" << oneKing << endl;
	cout << "4 - 2 Kings: $" << twoKing << endl;
	cout << "5 - Luxury Suites for 2: $" << luxury<< endl;
	cout << endl << endl;
	
}

// **************************************************************
//getRoomChoice
// ask users the type of room they wnat to book 
//returns: roomChoice
//parameters:none
//pass by reference parameters: none
// **************************************************************
int getRoomChoice(){
	int roomChoice;
	cout << "Select your Room: ";
	cin >> roomChoice;
	
	//condition for users to choose between 0 and 5 
	while (roomChoice > 5 || roomChoice < 0){
		cout << "Please, Enter a valid Room: ";
		cin >> roomChoice;
	}
		
	return roomChoice;
}

// **************************************************************
//getNumRoom
// ask users number of room they wnat to book 
//returns: numRoom
//parameters:none
//pass by reference parameters: none
// **************************************************************
int getNumRooms(){
	int numRooms;
	cout << "Enter the number of rooms: ";
	cin >> numRooms;
	
	while (numRooms < 0){
		cout << "Please, Enter a valid number:";
		cin >> numRooms;
	}
		
	return numRooms;
}

// **************************************************************
//getNumNight
// ask users number of night they wnat to book 
//returns: numNumNight
//parameters:none
//pass by reference parameters: none
// **************************************************************
int getNumNight(){
	int numNight;
	cout << "Enter the number of nights: ";
	cin >> numNight;
	
	while(numNight < 0){
		cout << "Please, Enter a Valid Number: ";
		cin >> numNight;
	}
	cout << endl;
	return numNight;
}

// **************************************************************
//addToOrder
// Display a message telling the user rhey have successfully book a room 
//returns: subTotal
//parameters:none
//pass by reference parameters: subTotal
// **************************************************************
double addToOrder(double costOfRoom, int nightBooked, int roomBooked, double& subTotal ){
 					
        cout << setprecision(2) << fixed;
        subTotal = nightBooked * roomBooked * costOfRoom;
        cout << "Room successfully booked!"<< endl << endl;
   
	return subTotal;
}

// **************************************************************
//calculateTaxes
// calculate the taxe on the booking
//returns: taxe
//parameters:subTotal
//pass by reference parameters: none
// **************************************************************
double calculateTaxes( double subTotal){
	double taxe;
	cout << setprecision(2) << fixed;
	taxe = TAXE * subTotal;

	return taxe;
}

// **************************************************************
//printReceipt
// write the current customer reseipt to the output file 
//returns: none
//parameters: hotelName, numberOfRoom,  numberOfNight,  costOfRoom,
//                   subTotal,  taxeFee, receipt 
//pass by reference parameters: receipt
// **************************************************************
void printReceipt(string hotelName, int numberOfRoom, int numberOfNight, double costOfRoom,
                  double subTotal, double taxeFee, ofstream& receipt ){
   
	receipt << hotelName << endl << endl;
	receipt << "Number of Rooms:" << numberOfRoom << endl;
	receipt << "Number of Nights : "<< numberOfNight << endl;
	receipt << "Room Price: $" << costOfRoom << endl;
	receipt << "Subtotal: $" << subTotal << endl;
	receipt << "Tax: $" << taxeFee << endl << endl;
	cout << setprecision(2) << fixed;
	receipt << "Total: $" << subTotal + taxeFee << endl;
	receipt << "**************************************************"<< endl << endl;        	
	
}