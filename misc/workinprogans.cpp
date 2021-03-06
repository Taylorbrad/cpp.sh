#include <iostream>
#include <string>
#include <fstream>

using namespace std;
int productNum;
class NewProduct
{
public:
	//variable declarations for the properties of objects created with the NewProduct constructor
	double price;
	int barcodeID;
	string productName;
	
	NewProduct() //Constructor to create new item and set properties
	{
		
		//Set product properties from user input
		cout << "\n---Example-Run---\n\n" << "Input price of item: ";
		cin >> price;
		cout << "Input barcode number of item: ";
		cin >> barcodeID;
		cout << "Input the product name: ";
		cin.ignore();
		getline(cin, productName);
		cout << "\n------------------------------------\n\n";
		
	}
	
};
//Function Definitions
void searchProduct();
void addNewProduct();
void displayAllProducts();
void customerTransaction();
//Begin main function
int main()
{
	int menuSelection = 0;
	cout << "\n MAIN MENU\n1: Customer transaction\n" << "2: Add new product to database\n" << "3: Search for product (ID or Name)\n" << "4: Display all products\n" << "0: End program\n\n" << "Enter option: ";
	cin >> menuSelection;
	if (menuSelection == 1)
	{
		customerTransaction();
	}
	else if (menuSelection == 2)
	{
		addNewProduct();
	}
	else if (menuSelection == 3)
	{
		searchProduct();
	}
	else if (menuSelection == 4)
	{
		displayAllProducts();
	}
	else if (menuSelection == 0)
	{
		cout << "\n------------------------------------\nEnding program...\n------------------------------------\n";
		return 0;
	}
}
void customerTransaction()
{
	//debug string to test running lines
	string debugLine = "\nline";
	//initialize variables
	ifstream searchForCart;
	double cartTotal[50];
	double runningTotal = 0;
	int itemNum = 0;
	string productName;
	string idNum;
	string price;
	string productToAdd;
	string noProductError = "NO PRODUCT FOUND WITH THIS NAME\n\n";
	
	for (int x = 0; x < 50 || x != 0; ++x)
	{
		cout << "Enter product name to add to cart (enter STOP to finalize cart): ";
		
		if (x == 0)
		cin.ignore();
		
		getline(cin, productToAdd);
		
		searchForCart.open("products.txt", ios::in);
		//cout << debugLine << "b4ifisopen\n";
		if (searchForCart.is_open())
		{
			int testForProduct = 0;
			//cout << debugLine << "b4while !search...\n";
			while(!searchForCart.eof())
			{
				//cout << debugLine << "b4getlines\n";
				getline(searchForCart, productName, ',');
				getline(searchForCart, idNum, ',');
				getline(searchForCart, price);
				
				//cout << productName << "  /" << productToAdd << "/";
				if (productName == productToAdd)
				{
					//cout << debugLine << "if add price\n";
					cartTotal[itemNum] = stod(price);
					//cout << cartTotal[itemNum] << "..." << stod(price);
					++itemNum;
					++testForProduct;
					runningTotal += stod(price);
					cout << "The running total is: $" << runningTotal << "\n";
				}
				
			}
			if (testForProduct == 0 && productToAdd != "STOP")
				cout << "------------------------------------\nNo product matched this name.\nRemember it is case-sensitive\n------------------------------------\n";
		//cout << debugLine << "after is open\n"; 
		
		}
	
		else
		{
			cout << "\n------------------------------------\nUnable to open file!\n------------------------------------\n\n";
		}
	
		/*if (itemNum == 0)
		{
			cout << noProductError;
		}*/
		int tempLineNum = itemNum - 1;
		//cout << cartTotal[tempLineNum] << "..." << stod(price);
		searchForCart.close();
		//cout << "\n\n" << productToAdd;
		if (productToAdd == "STOP")
		{
			double totalOrder;
			for(int y = 0; y < itemNum; ++y)
			{
				//cout << cartTotal[y] << "\n\n";
				totalOrder += cartTotal[y];
			}
			cout << "\nThe total order is: $" << totalOrder << "\n\n";
			main();
		}
	}
}
void addNewProduct()
{
	NewProduct product;	//create new 'product' with NewProduct constructor
	ofstream outFile;	//create new ofstream object for writing new object
	
	outFile.open("products.txt", ios::app); //Open products.txt with the outFile object
	if (outFile.is_open()){ //check if file is opened properly, then write properties to file, or output error.
		
		outFile << product.productName << "," << product.barcodeID << "," << product.price << "\n";
	}
	else {
		cout << "\n------------------------------------\nIssue writing new product to file\n------------------------------------\n\n";
	}
	main(); //call back to main function to repeat the program.
}

void displayAllProducts()
{
	int lineNum = 0;
	ifstream outFile;
	outFile.open("products.txt", ios::out);
	string line;
	if (outFile.is_open())
	{
		cout << "\n\nItem List:\n------------------------------------\n   Name, ID, Price\n";
		while(getline(outFile, line))
		{
			++lineNum;
			cout << lineNum << ": " << line << endl;
		}
		cout << "------------------------------------\n\n";
		outFile.close();
	}
	else
	{
		cout << "\n------------------------------------\nUnable to open file!\n------------------------------------\n";
	}
	
	main();
	
}

void searchProduct() //Function
{
	//declare variables
	int itemNum = 0;
	string productName;
	string idNum;
	string price;
	string searchString;
	string productProperties;
	ifstream searchTxt;
	
	
	//prompt user for search term
	cout << "Enter product name: ";
	cin.ignore();
	getline(cin, searchString);
	
	searchTxt.open("products.txt", ios::in);
	
	if (searchTxt.is_open())
	{
		cout << "\nItem(s):\n------------------------------------\n";
		while(!searchTxt.eof())
		{
			getline(searchTxt, productName, ',');
			getline(searchTxt, idNum, ',');
			getline(searchTxt, price);
			productProperties = "NO PRODUCT FOUND WITH THIS NAME\n\n";
			if (productName == searchString)
			{
				++itemNum;
				productProperties = "Name: " + productName + ", ID Number: #" + idNum + ", Price: $" + price + "\n";
				cout << itemNum << ": " << productProperties;
			}
		}
		cout << "------------------------------------\n\n";
	}
	else 
	{
		cout << "\n------------------------------------\nUnable to open file!\n------------------------------------\n\n";
	}
	if (itemNum == 0)
	{
		cout << productProperties;
	}
	main();
}
