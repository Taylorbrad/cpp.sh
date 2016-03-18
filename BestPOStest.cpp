#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;
int productNum;
class NewProduct
{
	public:
	//Public declaration of property variables
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
	}
	
};
void searchProduct();
void addNewProduct();
void displayAllProducts();
int main()
{
    int menuSelection = 0;
    cout << "1: Customer transaction\n" << "2: Add new product to database\n" << "3: Search for a product\n" << "4: Display all products\n" << "0: End program\n\n" << "Enter option: ";
    cin >> menuSelection;
    if (menuSelection == 1)
    {
        	
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
	    cout << "\nEnding program...";
	    return 0;
	}
}

void addNewProduct()
{
	//create new 'product'
	NewProduct product;
	//create new ofstream object for writing new object
	ofstream outFile;
	
	outFile.open("products.txt", ios::app);
	if (outFile.is_open()){
	    
		outFile << product.productName << "," << product.barcodeID << "," << product.price << "\n";
	}
	else {
		cout << "Issue writing new object to file\n";
	}
	cout << "\n\n";
	main();
}

void displayAllProducts()
{
	ifstream outFile;
	outFile.open("products.txt", ios::out);
	string line;
	if (outFile.is_open())
	{
		cout << "\n\nItem List:\n";
		while(getline(outFile, line))
		{
			cout << line << endl;
		}
		cout << "\n\n";
		outFile.close();
	}
	else 
	{
	cout << "\nUnable to open file!\n\n";
	}
	
	main();
	
}

void customerTransaction()
{
	
}

void searchProduct() //Function 
{
	//declare variables
	
	string productName;
	string idNum;
	string price;
	string searchString;
	string productProperties;
	ifstream searchTxt;
	
	
	//prompt user for search term
	cout << "Search product name: ";
	cin.ignore();
	getline(cin, searchString);
	
	searchTxt.open("products.txt", ios::in);
	
	if (searchTxt.is_open())
	{
		while(!searchTxt.eof())
		{
			getline(searchTxt, productName, ',');
			getline(searchTxt, idNum, ',');
			getline(searchTxt, price);
			productProperties = "No product found with this name.\n\n";
			if (productName == searchString)
			{
				productProperties = "\nItem:\nName: " + productName + ", ID Number:" + idNum + ", Price: $" + price + "\n\n";
				cout << productProperties;
			}
		}
	}
	else 
	{
		cout << "Error opening file\n\n";
	}
	
	main();
}

/*

void getLineNum() //Find Previous line number and write next line number in txt file
{
	string lineNum;
	
	ofstream findLineNum;
	
	findLineNum.open("products.txt", ios::in)
	
	if (findLineNum.is_open())
	{
		while(!findLineNum.eof())
		{
			
		}
	}
	else 
	{
		cout << "Error opening file\n\n";
	}
}

*/