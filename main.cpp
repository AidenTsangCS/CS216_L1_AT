#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <fstream>
using namespace std;

const string INPUT_FILE = "in_numberList.txt";
const string OUTPUT_FILE = "out_userChoices.txt";
const int MAX_SIZE = 100;
const int COL_WIDTH = 10;

void displayMenu();
int getMenuChoice();
void clearInputStream(const string& message);

void readData(const string& filename,
              int div5[], int& count5,
              int div7[], int& count7,
              int other[], int& countOther,
              int maxSize);

double sumArray(const int arr[], int size);
double averageArray(const int arr[], int size);
double medianArray(const int arr[], int size);
void bubbleSortDescending(int arr[], int size);
void copyArray(const int source[], int dest[], int size);

void printArrayValues(ostream& out, const int arr[], int size);
void printArrayStats(ostream& out, const string& label, const int arr[], int size);
void printSortedArray(ostream& out, const string& label, const int arr[], int size);

int main()
{
    int div5[MAX_SIZE], div7[MAX_SIZE], other[MAX_SIZE];
    int count5 = 0, count7 = 0, countOther = 0;

    readData(INPUT_FILE, div5, count5, div7, count7, other, countOther, MAX_SIZE);

    ofstream outFile(OUTPUT_FILE, ios::app);
    if (!outFile)
    {
        cout << "\nWarning: could not open " << OUTPUT_FILE << " for writing.\n";
    }

    bool quit = false;
    while (!quit)
    {
        displayMenu();
        int choice = getMenuChoice();

        switch (choice)
        {
        case 1:
            cout << "\n ARRAY CONTENTS AND STATISTICS \n";
            outFile << "\n ARRAY CONTENTS AND STATISTICS \n";
            printArrayStats(cout, "Multiples of 5", div5, count5);
            printArrayStats(outFile, "Multiples of 5", div5, count5);
            printArrayStats(cout, "Multiples of 7", div7, count7);
            printArrayStats(outFile, "Multiples of 7", div7, count7);
            printArrayStats(cout, "Neither (other)", other, countOther);
            printArrayStats(outFile, "Neither (other)", other, countOther);
            break;
        case 2:
            cout << "\n ARRAYS SORTED DESCENDING \n";
            outFile << "\n ARRAYS SORTED DESCENDING \n";
            printSortedArray(cout, "Multiples of 5", div5, count5);
            printSortedArray(outFile, "Multiples of 5", div5, count5);
            printSortedArray(cout, "Multiples of 7", div7, count7);
            printSortedArray(outFile, "Multiples of 7", div7, count7);
            printSortedArray(cout, "Neither (other)", other, countOther);
            printSortedArray(outFile, "Neither (other)", other, countOther);
            break;
        case 3:
            cout << "\nAre you sure you want to quit? (y/n): ";
            char confirm;
            cin >> confirm;
            if (confirm == 'y')
            {
                cout << "\nQuitting program. Goodbye!\n";
                outFile << "\nQuitting program. Goodbye!\n";
                quit = true;
            }
            break;
        default:
            cout << "\nInvalid choice. Enter 1, 2, or 3.\n";
            break;
        }
    }

    outFile.close();
    return 0;
}

void displayMenu()
{
    cout << "\n MAIN MENU \n";
    cout << "1. Print arrays with average, median, and sum\n";
    cout << "2. Print arrays sorted in descending order\n";
    cout << "3. Quit\n";
    cout << "Enter your choice: ";
}

int getMenuChoice()
{
    int choice = 0;
    while (!(cin >> choice))
    {
        clearInputStream("Invalid input. Enter a number (1-3): ");
    }
    return choice;
}

void clearInputStream(const string& message)
{
    cout << message;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void readData(const string& filename,
              int div5[], int& count5,
              int div7[], int& count7,
              int other[], int& countOther,
              int maxSize)
{
    ifstream inFile(filename);
    if (!inFile)
    {
        cout << "\nWarning: could not open " << filename
             << ". Starting with empty arrays.\n";
        return;
    }

    int val = 0;
    while (inFile >> val)
    {
        if (val % 5 == 0)
        {
            if (count5 < maxSize)
                div5[count5++] = val;
            else
                cout << "\nWarning: multiples-of-5 array is full. Value " << val << " was dropped.\n";
        }
        else if (val % 7 == 0)
        {
            if (count7 < maxSize)
                div7[count7++] = val;
            else
                cout << "\nWarning: multiples-of-7 array is full. Value " << val << " was dropped.\n";
        }
        else
        {
            if (countOther < maxSize)
                other[countOther++] = val;
            else
                cout << "\nWarning: 'other' array is full. Value " << val << " was dropped.\n";
        }
    }

    inFile.close();
}

double sumArray(const int arr[], int size)
{
    double total = 0;
    for (int i = 0; i < size; i++)
        total += arr[i];
    return total;
}

double averageArray(const int arr[], int size)
{
    return sumArray(arr, size) / size;
}

double medianArray(const int arr[], int size)
{
    int sorted[MAX_SIZE];
    copyArray(arr, sorted, size);
    bubbleSortDescending(sorted, size);

    int mid = size / 2;
    if (size % 2 == 0)
        return (sorted[mid - 1] + sorted[mid]) / 2.0;
    else
        return sorted[mid];
}

void bubbleSortDescending(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (arr[j] < arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void copyArray(const int source[], int dest[], int size)
{
    for (int i = 0; i < size; i++)
        dest[i] = source[i];
}

void printArrayValues(ostream& out, const int arr[], int size)
{
    if (size == 0)
    {
        out << left << setw(20) << "Values:" << "(no values stored)\n";
        return;
    }

    out << left << setw(20) << "Values:";
    for (int i = 0; i < size; i++)
        out << right << setw(COL_WIDTH) << arr[i];
    out << "\n";
}

void printArrayStats(ostream& out, const string& label, const int arr[], int size)
{
    out << "\n--- " << label << " (" << size << " value(s)) ---\n";
    printArrayValues(out, arr, size);

    if (size == 0)
    {
        out << left << setw(20) << "" << "No statistics available (array is empty).\n";
        return;
    }

    double sum = sumArray(arr, size);
    double avg = averageArray(arr, size);
    double med = medianArray(arr, size);

    out << fixed << setprecision(2);
    out << left << setw(20) << "Sum:"     << right << setw(COL_WIDTH) << sum << "\n";
    out << left << setw(20) << "Average:" << right << setw(COL_WIDTH) << avg << "\n";
    out << left << setw(20) << "Median:"  << right << setw(COL_WIDTH) << med << "\n";
}

void printSortedArray(ostream& out, const string& label, const int arr[], int size)
{
    out << "\n--- " << label << " sorted (descending) (" << size << " value(s)) ---\n";

    int sorted[MAX_SIZE];
    copyArray(arr, sorted, size);
    bubbleSortDescending(sorted, size);
    printArrayValues(out, sorted, size);
}

/* TEST RUN
aidentsang@Aidens-MacBook-Pro CS216_L1_AT % "/Users/aidentsang/Pierce college Labs C++/CS216_L1_AT/main"

 MAIN MENU 
1. Print arrays with average, median, and sum
2. Print arrays sorted in descending order
3. Quit
Enter your choice: 1

 ARRAY CONTENTS AND STATISTICS 

--- Multiples of 5 (9 value(s)) ---
Values:                     10        35        50       100        25        60         5        45        70
Sum:                    400.00
Average:                 44.44
Median:                  45.00

--- Multiples of 7 (6 value(s)) ---
Values:                     21        14        49        28         7        63
Sum:                    182.00
Average:                 30.33
Median:                  24.50

--- Neither (other) (5 value(s)) ---
Values:                      8        17        33        18        39
Sum:                    115.00
Average:                 23.00
Median:                  18.00

 MAIN MENU 
1. Print arrays with average, median, and sum
2. Print arrays sorted in descending order
3. Quit
Enter your choice: 2

 ARRAYS SORTED DESCENDING 

--- Multiples of 5 sorted (descending) (9 value(s)) ---
Values:                    100        70        60        50        45        35        25        10         5

--- Multiples of 7 sorted (descending) (6 value(s)) ---
Values:                     63        49        28        21        14         7

--- Neither (other) sorted (descending) (5 value(s)) ---
Values:                     39        33        18        17         8

 MAIN MENU 
1. Print arrays with average, median, and sum
2. Print arrays sorted in descending order
3. Quit
Enter your choice: 3

Are you sure you want to quit? (y/n): n

 MAIN MENU 
1. Print arrays with average, median, and sum
2. Print arrays sorted in descending order
3. Quit
Enter your choice: 2

 ARRAYS SORTED DESCENDING 

--- Multiples of 5 sorted (descending) (9 value(s)) ---
Values:                    100        70        60        50        45        35        25        10         5

--- Multiples of 7 sorted (descending) (6 value(s)) ---
Values:                     63        49        28        21        14         7

--- Neither (other) sorted (descending) (5 value(s)) ---
Values:                     39        33        18        17         8

 MAIN MENU 
1. Print arrays with average, median, and sum
2. Print arrays sorted in descending order
3. Quit
Enter your choice: 1

 ARRAY CONTENTS AND STATISTICS 

--- Multiples of 5 (9 value(s)) ---
Values:                     10        35        50       100        25        60         5        45        70
Sum:                    400.00
Average:                 44.44
Median:                  45.00

--- Multiples of 7 (6 value(s)) ---
Values:                     21        14        49        28         7        63
Sum:                    182.00
Average:                 30.33
Median:                  24.50

--- Neither (other) (5 value(s)) ---
Values:                      8        17        33        18        39
Sum:                    115.00
Average:                 23.00
Median:                  18.00

 MAIN MENU 
1. Print arrays with average, median, and sum
2. Print arrays sorted in descending order
3. Quit
Enter your choice: `
Invalid input. Enter a number (1-3): 0

Invalid choice. Enter 1, 2, or 3.

 MAIN MENU 
1. Print arrays with average, median, and sum
2. Print arrays sorted in descending order
3. Quit
Enter your choice: 0

Invalid choice. Enter 1, 2, or 3.

 MAIN MENU 
1. Print arrays with average, median, and sum
2. Print arrays sorted in descending order
3. Quit
Enter your choice: -3

Invalid choice. Enter 1, 2, or 3.

 MAIN MENU 
1. Print arrays with average, median, and sum
2. Print arrays sorted in descending order
3. Quit
Enter your choice: 3

Are you sure you want to quit? (y/n): y

Quitting program. Goodbye!
aidentsang@Aidens-MacBook-Pro CS216_L1_AT % */
