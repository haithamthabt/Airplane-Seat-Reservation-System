// Purpose: To implement a seat reservation for a passenger airplane.
// Author's Name: Haitham Thab
// Creation Date: 03/26/2015
// Modification Date: 04/10/2015

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <windows.h> // this is used for the sleep code in the quit function

using namespace std;

void displayMenu(); // this functions displays the menu of options
void readChart(); // this function's job is to read the file into the arrays
void displayChart(); // this function's job is to display the chart that is created of the arrays
void reserveSeat(); // this function's job is to reserve a seat entered by the user
void cancelReservation(); // this function's job is to cancel a seat entered by the user
void saveChartToFile(); // this functions job is to save the chart into a file
void showStatistics(); // this function's job is to show statistics
void help(); // this function's job is to display a detailed message on how to use the program
void quit(); // this function's job is to display a thank you message and terminates
void displayInvalid(); // this function's job is to display the invalid messegae in case if other numbers than 1-7 entered 
void extractSeatNum(int&, int&, string&); // this function's job is to extract the seat number

int choice; // choice number

const int ROWS = 99; // maximum number of rows in the airplan
const int COLS = 8; // maximum number of columns in the airplan
char chart[ROWS][COLS]; //this array is for letters only
int chart2[ROWS]; // this array for the number of rows

int numOfRows; // number of rows in the airplan
int numOfCols; // number of columns in the airplan

ifstream myInputFile; // name of the veriable of the file we import
ofstream myOutputFile; // name of the veriable of the file we export

int main()
{
	myInputFile.open("chartIn.txt");	// to open the file 
	readChart(); // read file and store values in the array 
	myInputFile.close(); // close the file

	do
	{
		displayMenu();

		switch (choice)
		{
		case 1:
			displayChart();
			break;
		case 2:
			reserveSeat();
			break;
		case 3:
			cancelReservation();
			break;
		case 4:
			saveChartToFile();
			break;
		case 5:
			showStatistics();
			break;
		case 6:
			help();
			break;
		case 7:
			quit();
			break;
		default:
			displayInvalid();
			break;
		}

		cout << endl;	// to give an extra line before the next display

	} while (choice != 7);

	//system("Pause"); note that, this omited because I am using the sleep code inside the quit function
	return 0;
}

// Purpose of the function: To display the menu options
// Author's Name: Haitham Thabt
// Creation Date: 04/10/2015
// Modification Date: 04/10/2015
void displayMenu()
{
	cout << "----------------------------Menu --------------------------" << endl;
	cout << "1. Display Seat Chart" << endl;
	cout << "2. Reserve Seat" << endl;
	cout << "3. Cancel Reservation" << endl;
	cout << "4. Save Seat Chart to File" << endl;
	cout << "5. Statistics" << endl;
	cout << "6. Help" << endl;
	cout << "7. Quit" << endl;
	cout << "Please Enter You Choice (1-7): ";
	cin >> choice;
	cout << "-----------------------------------------------------------" << endl;
}


// Purpose of the function: To read the seat chart file and then assign it to the arrays
// Author's Name: Haitham Thabt
// Creation Date: 03/29/2015
// Modification Date: 04/10/2015
void readChart()
{
	int rowNumber;

	myInputFile >> numOfRows >> numOfCols; // this reads the first two numbers on the top of the file we import
										   // which are the number of rows and number of columns

	while (!myInputFile.eof())
	{
		myInputFile >> rowNumber;
		chart2[rowNumber] = rowNumber; // this reads the numbers of rows and will put it inside the chart2 array 

		for (int j = 0; j < numOfCols; j++)
			myInputFile >> chart[rowNumber][j]; // this reads the letters and stores then inside the chart array
	}

}


// Purpose of the function: To display the chart that is created of the arrays
// Author's Name: Haitham Thabt
// Creation Date: 03/29/2015
// Modification Date: 04/10/2015
void displayChart()
{
	for (int i = 0; i < numOfRows; i++) // this indicates the rows
	{
		// this if function is to put spaces between the numbers and the letters A's
		if (chart2[i + 1] >= 10) // since the first line in file indacates the number of rows and columns, then +1 is to start from the next line
			cout << chart2[i + 1] << " ";
		else
			cout << chart2[i + 1] << "  ";

		for (int j = 0; j < numOfCols; j++) // this indicates the colums
			cout << chart[i + 1][j] << "  ";

		cout << endl;
	}
}


// Purpose of the function: To reserve a seat entered by the user
// Author's Name: Haitham Thabt
// Creation Date: 03/29/2015
// Modification Date: 04/10/2015
void reserveSeat()
{
	int rowR, colR;
	string seatR;

	cout << "Please enter the desired seat number as (e.g., 3A, 7D, etc.): ";
	cin >> seatR;

	extractSeatNum(rowR, colR, seatR); // this function to extract the seat number

	if (chart[rowR][colR] != 'X') // if the function is not resereved
	{
		chart[rowR][colR] = 'X';
		cout << "Seat " << seatR << " was successfully reserved." << endl;
	}
	else
	{
		cout << "Sorry! seat " << seatR << " is not available. Please choose another seat" << endl;
	}

}


// Purpose of the function:  To cancel a seat entered by the user
// Author's Name: Haitham Thabt
// Creation Date: 03/29/2015
// Modification Date: 04/10/2015
void cancelReservation()
{
	int rowC, colC;
	string seatC;

	cout << "Please enter the seat number you want to cancel (e.g., 3A, 7D, etc.): ";
	cin >> seatC;

	extractSeatNum(rowC, colC, seatC);

	if (chart[rowC][colC] != 'X') // if the seat is not resereved
		cout << "The seat " << seatC << " that you to cancel has not been initially reserved" << endl;
	else
	{
		switch (colC) // assinging the index of the letter to the letter
		{
		case 0:
			chart[rowC][0] = 'A';
			break;
		case 1:
			chart[rowC][1] = 'B';
			break;
		case 2:
			chart[rowC][2] = 'C';
			break;
		case 3:
			chart[rowC][3] = 'D';
			break;
		case 4:
			chart[rowC][4] = 'E';
			break;
		case 5:
			chart[rowC][5] = 'F';
			break;
		case 6:
			chart[rowC][6] = 'G';
			break;
		case 7:
			chart[rowC][7] = 'H';
			break;
		default:
			break;
		}

		cout << "Seat " << seatC << " was successfully canceled." << endl;
	}

}


// Purpose of the function: To save the chart that is created into a file
// Author's Name: Haitham Thabt
// Creation Date: 03/29/2015
// Modification Date: 04/10/2015
void saveChartToFile()
{
	string fileName;

	cout << "please name the file with its extention as (e.g., file.txt, chart.txt, etc.): ";
	cin >> fileName;

	myOutputFile.open(fileName); // opens that file

	for (int i = 0; i < numOfRows; i++)
	{
		// this if function is to put spaces between the numbers and the letters A's
		if (chart2[i + 1] >= 10) // again the +1 is becasuse the top line with 0 index in the file, indicates the number of rows and columns
			myOutputFile << chart2[i + 1] << " ";
		else
			myOutputFile << chart2[i + 1] << "  ";



		for (int j = 0; j < numOfCols; j++)
			myOutputFile << chart[i + 1][j] << "  ";

		myOutputFile << endl;
	}

	cout << endl;
	cout << "File has been saved as " << fileName;

	myOutputFile.close(); // closes the file

}


// Purpose of the function: To show statistics
// Author's Name: Haitham Thabt
// Creation Date: 03/29/2015
// Modification Date: 04/10/2015
void showStatistics()
{
	int totalSeatsNum = 0;
	int totalSeatsResereved = 0;
	float totalAvailableSeats = 0;
	int totalWindowSeats = 0;
	int totalAisleSeats = 0;
	float PerOfReserevedSeats;

	char rightWindowSeat; // this is a place holder for the right column

	switch (numOfCols) // this code to store the data for the right column
	{
	case 2:
		rightWindowSeat = 'B';
		break;
	case 3:
		rightWindowSeat = 'C';
		break;
	case 4:
		rightWindowSeat = 'D';
		break;
	case 5:
		rightWindowSeat = 'E';
		break;
	case 6:
		rightWindowSeat = 'F';
		break;
	case 7:
		rightWindowSeat = 'G';
		break;
	case 8:
		rightWindowSeat = 'H';
		break;
	default:
		break;
	}


	for (int i = 0; i < numOfRows; i++)
	{
		for (int j = 0; j < numOfCols; j++)
		{
			totalSeatsNum++;	// to count total num of seats

			if (chart[i + 1][j] == 'X')
				totalSeatsResereved++;	// to count resreved seats
			else
				totalAvailableSeats++;	// to count available seats

			if (chart[i + 1][j] == 'A' || chart[i + 1][j] == rightWindowSeat)
				totalWindowSeats++;	// to count window seats

			if (chart[i + 1][j] != 'A' && chart[i + 1][j] != 'X' && chart[i + 1][j] != rightWindowSeat)
				totalAisleSeats++;	// to count aisle seats

		}
	}

	PerOfReserevedSeats = totalSeatsResereved / totalAvailableSeats * 100.0; // percentage of resereved seats

	cout << "Number of available seats is: " << totalAvailableSeats << endl;
	cout << "Percentage of seats that are reserved: " << PerOfReserevedSeats << "%" << endl;
	cout << "Number of window seats that are available: " << totalWindowSeats << endl;
	cout << "Number of aisle seats that are available: " << totalAisleSeats << endl;

}


// Purpose of the function:  to display a detailed message on how to use the program
// Author's Name: Haitham Thabt
// Creation Date: 03/29/2015
// Modification Date: 04/10/2015
void help()
{
	cout << " Press a number between one and seven" << endl;
	cout << "Press 1 to display the seat chart" << endl
		<< "Press 2 to to reserve a seat. You need to enter seat number as (e.g., 3A, 7D, etc.) " << endl
		<< "Press 3 to to to cancel a seat. You need to enter seat number as (e.g., 3A, 7D, etc.)" << endl
		<< "Press 4 to to save the chart into a file. Enter file name with its extention as (e.g., file.txt, chart.txt, etc.)s " << endl
		<< "Press 5 to to display the following statistics: Number of available seats, percentage of seats that are reserved, list of window seats that are available, list of aisle seats that are available." << endl
		<< "Press 6 to to display help and a detailed message on how to use the program" << endl
		<< "Press 7 to quit and terminate the program" << endl;
}


// Purpose of the function: To display a thank you message and then terminates the program after 5 seconds
// Author's Name: Haitham Thabt
// Creation Date: 03/29/2015
// Modification Date: 04/10/2015
void quit()
{
	cout << "Thank you for using our program";
	Sleep(5000); // to terminates after 5 seconds of choosing the quit option

}


// Purpose of the function: To display Invalid choice if any other numbers than 1-7 entered
// Author's Name: Haitham Thabt
// Creation Date: 03/29/2015
// Modification Date: 03/29/2015
void displayInvalid()
{
	cout << "Invalid choice. You need to select an option between 1 and 7" << endl;

}


// Purpose of the function: To read the seat number and then convert it to chars and ints
// Author's Name: Haitham Thabt
// Creation Date: 04/10/2015
// Modification Date: 04/10/2015
void extractSeatNum(int& row, int& col, string& seat)
{
	string fragment1, fragment2; // two fragmnets in a string such as 7D has 7 and D

	if (seat.length() == 2)
	{
		fragment1 = seat.substr(0, 1); // extract the first fragment such as 7 in 7D
		fragment2 = seat.substr(1, 1); // to extract the second fragment such as D in 7D
	}
	else if (seat.length() == 3)
	{
		fragment1 = seat.substr(0, 2); // extract the first fragment such as 10 in 10A
		fragment2 = seat.substr(2, 1); // to extract the second fragment such as A in 10A
	}
	else
	{
		cout << "invalid seat";

		row = -1;
		col = -1;
	}

	row = atoi(fragment1.c_str()); // this to convert the string numbers to int numbers

	switch (fragment2.at(0)) // this to convert the letter to the index of the columns
	{
	case 'A':
	case 'a':
		col = 0;
		break;
	case 'B':
	case 'b':
		col = 1;
		break;
	case 'C':
	case 'c':
		col = 2;
		break;
	case 'D':
	case 'd':
		col = 3;
		break;
	case 'E':
	case 'e':
		col = 4;
		break;
	case 'F':
	case 'f':
		col = 5;
		break;
	case 'G':
	case 'g':
		col = 6;
		break;
	case 'H':
	case 'h':
		col = 7;
		break;
	default:
		break;
	}

	//cout << "fragments are: " << fragment1 << " and " << fragment2 << endl; // TO TEST THE FUNCTION
	//cout << "This corresponds to Row " << row << " and column " << col << " in the array" << endl; // TO TEST THE FUNCTION

}


