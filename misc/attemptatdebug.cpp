#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

void initializeTxtFile();
void displayAppointment();
void deleteAll();
void setAppointment();
void displayStuff(string[], int);
string getPassKey();
class NewAppointment
{
	/*int month = 01;
	 int day = 01;
	 int year = 2000;
	 int hour = 12;
	 int minute = 00;
	 string amOrPM = "AM";*/
public:
	ifstream txtFile;
	int month;
	int day;
	int year;
	int hour;
	int minute;
	string input;
	string reasonForVisit;
	string amOrPM;
	
	NewAppointment()
	{
		cout << "When is the appointment? (MM/DD/YYYY HH:MM AM or PM): ";
		cin.ignore();
		getline(cin, input);
		cout << "What is the purpose for the appointment? ";
		getline(cin, reasonForVisit);
	}
};
int main()
{
	//Initialize variables
	int selection = 0;
	
	//Initialize text file
	//initializeTxtFile();
	
	//Prompt user for input and save input in selection variable
	cout << "Select an option from the menu:\n1: [not currently functional] Set appointment (customers or professionals)\n2: [not currently functional] Display appointment schedule (Day, Week, Month, Year, etc.)\n3: Delete all appointments (further confirmation required)\n4: End program\n\nSelection: ";
	cin >> selection;
	
	//execute function based on user input
	switch (selection)
	{
		case 1: setAppointment();
			break;
			
		case 2: displayAppointment();
			break;
			
		case 3: deleteAll();
			break;
			
		case 4: return 0;
			break;
			
		default: return 0;
			break;
			
			
	}
	
}

void setAppointment()
{
	ofstream writeToFile;
	string input = "";
	
	NewAppointment appt;
	
	writeToFile.open("appointments.txt", ios::app);
	if (writeToFile.is_open())
	{
		writeToFile << appt.input << "[" << appt.reasonForVisit << "]\n";
	}
	writeToFile.close();
}
void displayAppointment()
{	
	int appTime = 0;
	string currentMonth = "";
	string currentYear = "";
	string currentDay = "";
	string selection[3] = {"", "", ""};
	
	
	//getline(cin, appointment);
	cout << "Which appointments would you like to view?\n(1) Day  \n(2) Month  \n(3) Year  \n(4) All appointments" << endl;
	cin >> appTime;
	
	switch (appTime) 
	{
		case 1:
			cout << "Enter todays date (DD): ";
			cin.ignore();
			getline(cin, currentDay);
			selection[appTime] = currentDay;
			cout << "current day is: " << selection[appTime] << "\n";
			break;
		case 2:
			cout << "Enter the current month (MM): ";
			cin.ignore();
			getline(cin, currentMonth);
			selection[appTime] = currentMonth;
			cout << "current month is: " << selection[appTime] << "\n";
			break;
		case 3:
			cout << "Enter the current year (YYYY): ";
			cin.ignore();
			getline(cin, currentYear);
			selection[appTime] = currentYear;
			cout << "current year is: " << selection[appTime] << "\n";
			break;
		case 4:
			
			break;
		default:
			
			break;
	}
	cout << "Params: 1: " << selection << " 2: " << appTime;
	displayStuff(selection, appTime);
	
		
	//endif
	
}
void displayStuff(string *selection, int sub)
{
	string appointment = "";
	string month = "";
	
	string year = "";
	
	string day = "";
	
	string hour = "";
	string minute = "";
	string amOrPm = "";
	int x = 1;
	ifstream display;
	
	display.open("appointments.txt");
	//if: checking if file is open
	if (display.is_open())
	{
		while (!display.eof())
		{
			getline(display, month, '/');
			getline(display, day, '/');
			getline(display, year, ' ');
			getline(display, hour, ':');
			getline(display, minute, ' ');
			getline(display, amOrPm, '[');
			getline(display, appointment, ']');
			string select[3] = {day, month, year};
			cout << "1: " << selection[sub] << " || " << "2: " << select[sub];
			if (selection[sub] == select[sub])
			{
				cout << "Appointment #" << x << " Is on " << month << "/" << day << "/" << year << " at " << hour << ":" << minute << ". The reason for this visit is: " << appointment;
			}
			else if (sub == 4)
			{
				cout << "Appointment #" << x << " Is on " << month << "/" << day << "/" << year << " at " << hour << ":" << minute << ". The reason for this visit is: " << appointment;
			}
			++x;
		}
	}
	else 
	{
		cout << "The file could not be opened at this time. Please try again." << endl;
	}
}

//function to initialize text file if it is the first time the program is run
void initializeTxtFile()
{
	int x = 0;
	ofstream initialization;
	initialization.open("appointments.txt", ios::out);
	if (initialization.is_open() == false)
	{
		cout << "\nText file initialization failed. Retrying...\n\n";
		initializeTxtFile();
		++x;
	}
	else
	{
		if (x > 0)
		{
			cout << "Successful!\n";
		}
		if (x >= 5)
		{
			cout << "Initialization failed";
		}
		initialization.close();
	}
}

void deleteAll()
{
	string secondConfirmation = getPassKey();
	if (secondConfirmation == "YeS")
	{
		cout << "\n\nAlright you asked for it...\nDeleting contents of the txt file...\n\nReturning to main function...\n\n";
		
		//delete commands
		ofstream ofs;
		ofs.open("appointments.txt", ofstream::out | ofstream::trunc);
		ofs.close();
		
		main();
	}
	else
	{
		cout << "\n\n\n\nPhew, that was a close one! Returning to main menu...\n\n\n\n";
		main();
	}
}

string getPassKey()
{
	string secondConfirmation = "";
	string passKey = "test key";
	string passkeyInput = "";
	char confirmation = 'n';
	
	cout << "\nAre you sure you want to DELETE ALL APPOINTMENTS AND EMPTY THE FILE?\nY/N: ";
	cin >> confirmation;
	
	if (confirmation == 'Y')
	{
		cout << "\nEnter the passkey: ";
		cin.ignore();
		getline(cin, passkeyInput);
		
		if (passkeyInput == passKey)
		{
			cout << "\nAre you absolutely sure you want to DELETE ALL APPOINTMENTS AND EMPTY THE FILE?\nYES/N: ";
			getline(cin, secondConfirmation);
		}
		else 
		{
			cout << "\n\n\n\nIncorrect pass key.\nReturning to main menu...\n\n\n\n";
			main();
		}
	}
	else 
	{
		cout << "\n\n\n\nPhew, that was a close one! Returning to main menu...\n\n\n\n";
		main();
	}
	
	return secondConfirmation;
}
