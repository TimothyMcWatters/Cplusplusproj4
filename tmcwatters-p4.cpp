/****************************
Timothy McWatters
tmcwatters-p4.cpp
programming in C++ project 4

Program to read a pre-specified file containing: 
1) salespersons' names 2) daily sales for some number of weeks. 
It will create an output file 
with a file name you have gotten from the user 
that will hold a summary of sales data.
*****************************/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

void readingFile(istream& inputFile, ostream& outputFile);
int numSalesPeople(istream& inputFile);
void lastName(istream& inputFile, ostream& outputFile);
int numWeeks(istream& inputFile);
double individualSalesWeek(istream& inputFile);
double printIndividualWeeks(istream& inputFile, ostream& outputFile, int weeks);
void printGrandTotals(istream& inputFile, ostream& outputFile, int weeks, double totalSales);
void newLine(istream& inputFile);
void space(istream& inputFile);
void outputFileName(char name[]);

int main()
{
   int numberElements = 50;
   char fileName[numberElements];
   ofstream outputFile;
   ifstream inputFile;

   outputFileName(fileName);
   outputFile.open(fileName); // Associates outputFile with the name input by the user
   // If opening the output file fails, ERROR message and program closes.
   if (outputFile.fail( )) {
      cout << "Output file opening failed!" << endl;
      exit(1);
   }
   
   inputFile.open("temperatures.txt"); // Associates inputFile with "Sales.txt"
   // If opening the output file fails, ERROR message and program closes.
   if (inputFile.fail( )) {
      cout << "Input file opening failed!" << endl;
      exit(1);
   }

   
   readingFile(inputFile, outputFile);
   
   outputFile.close(); // Disassociates outputFile   
   inputFile.close(); // Disassociates inputFile
   
   return 0;
}

// Function to control the input and output from/to files calling other functions
void readingFile(istream& inputFile, ostream& outputFile)
{ 
   int peopleCount; // Number of sales people
   int weeksPerPerson; // Weeks each sales person is processing
   int totalWeeks = 0;
   double salesPersonsSales = 0.0;
   double totalSales = 0.0;

   peopleCount = numSalesPeople(inputFile);
   outputFile << "There were " << peopleCount << " sales people processed.\n" << endl;
   
   // For loop to calculate data on each sales person.
   for (int i = 0; i < peopleCount; i++) { 
      lastName(inputFile, outputFile);
   
      weeksPerPerson = numWeeks(inputFile);
      totalWeeks += weeksPerPerson;
   
      salesPersonsSales = printIndividualWeeks(inputFile, outputFile, weeksPerPerson);
      totalSales += salesPersonsSales;
   }
   
   printGrandTotals(inputFile, outputFile, totalWeeks, totalSales);

   return;
}

// Function to count the number of sales people to process
int numSalesPeople(istream& inputFile)
{
   int peopleCount;
   
   inputFile >> peopleCount;
   
   return peopleCount;
}

// Function to print the last names to file   
void lastName(istream& inputFile, ostream& outputFile)
{
   char nameLetter;
   
   newLine(inputFile);
   space(inputFile);
   space(inputFile);

   do {
      inputFile.get(nameLetter);
      outputFile << nameLetter;
   } while (nameLetter != '\n');

   return;
}

// Function to count the weeks processed for each sales person
int numWeeks(istream& inputFile)
{
   int weeksProcessed;
   
   inputFile >> weeksProcessed;
   
   return weeksProcessed;
}

// Function to read the sales data for each sales person,
// and calculate each persons totals per week.
double individualSalesWeek(istream& inputFile)
{
   int numDaySales = 5;
   double daySales[numDaySales];
   double sales = 0.0;

   for (int i = 0; i < numDaySales; i++) {
      inputFile >> daySales[i];
      }

   for (int k = 0; k < numDaySales; k++) {
      sales += daySales[k];
   }
      
   return sales;
}

// Function to print each sales persons weekly numbers, 
// and calculates their total sales.
double printIndividualWeeks(istream& inputFile, ostream& outputFile, int weeks)
{
   double sales = 0.0;
   double totalSales = 0.0;
   
   for (int i = 1; i <= weeks; i++) {
      sales = individualSalesWeek(inputFile);
      outputFile.setf(ios::fixed);
      outputFile.setf(ios::showpoint);
      outputFile.setf(ios::left);
      outputFile << setw(25) << "\tTotal sales for week " << i << setw(5) << ":" << setprecision(2) << setw(5) << sales << endl;
      outputFile << setw(25) << "\tAverage sales for week " << i << setw(5) << ":" << setprecision(2) << setw(5) << sales / 5 << endl;
      totalSales += sales;
   }
   outputFile << endl;

   return totalSales;
}

// Function to print the Store Wide totals
void printGrandTotals(istream& inputFile, ostream& outputFile, int weeks, double totalSales)
{
   outputFile.setf(ios::fixed);
   outputFile.setf(ios::showpoint);
   outputFile << "Store Wide:" << endl;
   outputFile << "\tAverage sales per week were $" << setprecision(2) << totalSales / weeks << ", over " << weeks << " weeks of sales processed." << endl;
   outputFile << "\tGrand Total Sales were: $" << setprecision(2) << totalSales << endl;
   
   return;
}

// Function to read the next input after a newline,
// but ignoring the input after its called up to the newline.
void newLine(istream& inputFile)
{
   char nameLetter;
   do {
      inputFile.get(nameLetter);
   } while (nameLetter != '\n');
   
   return;
}

// Function to read the next input after a space
// but ignoring the input after its called up to the space.
void space(istream& inputFile)
{
   char nameLetter;
   do {
      inputFile.get(nameLetter);
   } while (nameLetter != ' ');

   return;
}

// Creates the name for the output file based on user input
void outputFileName(char name[])
{
   cout << "What do you want to call the output file (up to 49 characters)? " << endl;
   cin >> name;
   return;
}
