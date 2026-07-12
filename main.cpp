// Aiden Tsang
// Lab #1

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <fstream>

using namespace std;

const string INPUT_FILE = "in_numberlist.txt";
const string OUTPUT_FILE = "out_userchoices.txt";
const int MAX_SIZE = 100;
const int COL_WIDTH = 10;
const int LABEL_COL = 20;

void displayMenu();
int getMenuChoice();
void clearInputStream(const string& message);
bool confirmQuit();

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
void printAllStats(ostream& out, const int div5[], int count5,
                   const int div7[], int count7,
                   const int other[], int countOther);
void printAllSorted(ostream& out, const int div5[], int count5,
                    const int div7[], int count7,
                    const int other[], int countOther);
void writeResultsToFile(const string& filename,
                        const int div5[], int count5,
                        const int div7[], int count7,
                        const int other[], int countOther);

int main()
{
    int div5[MAX_SIZE];
    int div7[MAX_SIZE];
    int other[MAX_SIZE];
    int count5 = 0;
    int count7 = 0;
    int countOther = 0;

    readData(INPUT_FILE, div5, count5, div7, count7, other, countOther, MAX_SIZE);

    bool quit = false;
    while (!quit)
    {
        displayMenu();
        int choice = getMenuChoice();

        switch (choice)
        {
        case 1:
            printAllStats(cout, div5, count5, div7, count7, other, countOther);
            break;
        case 2:
            printAllSorted(cout, div5, count5, div7, count7, other, countOther);
            break;
        case 3:
            if (confirmQuit())
            {
                writeResultsToFile(OUTPUT_FILE, div5, count5, div7, count7, other, countOther);
                cout << "\nResults written to " << OUTPUT_FILE << ". Goodbye!\n";
                quit = true;
            }
            break;
        default:
            cout << "\nInvalid choice. Enter 1, 2, or 3.\n";
            break;
        }
    }

    return 0;
}

void displayMenu()
{
    cout << "\n MAIN MENU \n";
    cout << "1. Print arrays with average, median, and sum\n";
    cout << "2. Print arrays sorted in descending order\n";
    cout << "3. Quit and save results to a file\n";
    cout << "Enter your choice (1-3): ";
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

bool confirmQuit()
{
    char answer = ' ';

    while (answer != 'y' && answer != 'n')
    {
        cout << "\nAre you sure you want to quit? (y/n): ";
        cin >> answer;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (answer >= 'A' && answer <= 'Z')
        {
            answer = static_cast<char>(answer - 'A' + 'a');
        }

        if (answer != 'y' && answer != 'n')
        {
            cout << "Invalid input. Please enter 'y' or 'n'.\n";
        }
    }

    return answer == 'y';
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
    }
    else
    {
        int val = 0;
        while (inFile >> val)
        {
            if (val % 5 == 0)
            {
                if (count5 < maxSize)
                {
                    div5[count5] = val;
                    count5++;
                }
                else
                {
                    cout << "\nWarning: multiples-of-5 array is full. Value "
                         << val << " was dropped.\n";
                }
            }
            else if (val % 7 == 0)
            {
                if (count7 < maxSize)
                {
                    div7[count7] = val;
                    count7++;
                }
                else
                {
                    cout << "\nWarning: multiples-of-7 array is full. Value "
                         << val << " was dropped.\n";
                }
            }
            else
            {
                if (countOther < maxSize)
                {
                    other[countOther] = val;
                    countOther++;
                }
                else
                {
                    cout << "\nWarning: 'other' array is full. Value "
                         << val << " was dropped.\n";
                }
            }
        }

        inFile.close();
    }
}

double sumArray(const int arr[], int size)
{
    double total = 0;
    for (int i = 0; i < size; i++)
    {
        total += arr[i];
    }
    return total;
}

double averageArray(const int arr[], int size)
{
    return sumArray(arr, size) / size;
}

double medianArray(const int arr[], int size)
{
    int sorted[MAX_SIZE];
    double median = 0;

    copyArray(arr, sorted, size);
    bubbleSortDescending(sorted, size);

    int mid = size / 2;
    if (size % 2 == 0)
    {
        median = (sorted[mid - 1] + sorted[mid]) / 2.0;
    }
    else
    {
        median = sorted[mid];
    }

    return median;
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
    {
        dest[i] = source[i];
    }
}

void printArrayValues(ostream& out, const int arr[], int size)
{
    if (size == 0)
    {
        out << left << setw(LABEL_COL) << "Values:" << "(no values stored)\n";
    }
    else
    {
        out << left << setw(LABEL_COL) << "Values:";
        for (int i = 0; i < size; i++)
        {
            out << right << setw(COL_WIDTH) << arr[i];
        }
        out << "\n";
    }
}

void printArrayStats(ostream& out, const string& label, const int arr[], int size)
{
    out << "\n--- " << label << " (" << size << " value(s)) ---\n";
    printArrayValues(out, arr, size);

    if (size == 0)
    {
        out << left << setw(LABEL_COL) << ""
            << "No statistics available (array is empty).\n";
    }
    else
    {
        double sum = sumArray(arr, size);
        double avg = averageArray(arr, size);
        double med = medianArray(arr, size);

        out << fixed << setprecision(2);
        out << left << setw(LABEL_COL) << "Sum:"
            << right << setw(COL_WIDTH) << sum << "\n";
        out << left << setw(LABEL_COL) << "Average:"
            << right << setw(COL_WIDTH) << avg << "\n";
        out << left << setw(LABEL_COL) << "Median:"
            << right << setw(COL_WIDTH) << med << "\n";
    }
}

void printSortedArray(ostream& out, const string& label, const int arr[], int size)
{
    int sorted[MAX_SIZE];

    out << "\n--- " << label << " sorted (descending) ("
        << size << " value(s)) ---\n";

    copyArray(arr, sorted, size);
    bubbleSortDescending(sorted, size);
    printArrayValues(out, sorted, size);
}

void printAllStats(ostream& out, const int div5[], int count5,
                   const int div7[], int count7,
                   const int other[], int countOther)
{
    out << "\n ARRAY CONTENTS AND STATISTICS \n";
    printArrayStats(out, "Multiples of 5", div5, count5);
    printArrayStats(out, "Multiples of 7", div7, count7);
    printArrayStats(out, "Neither (other)", other, countOther);
}

void printAllSorted(ostream& out, const int div5[], int count5,
                    const int div7[], int count7,
                    const int other[], int countOther)
{
    out << "\n ARRAYS SORTED DESCENDING \n";
    printSortedArray(out, "Multiples of 5", div5, count5);
    printSortedArray(out, "Multiples of 7", div7, count7);
    printSortedArray(out, "Neither (other)", other, countOther);
}

void writeResultsToFile(const string& filename,
                        const int div5[], int count5,
                        const int div7[], int count7,
                        const int other[], int countOther)
{
    ofstream outFile(filename);

    if (!outFile)
    {
        cout << "\nWarning: could not open " << filename
             << " for writing. Results were not saved.\n";
    }
    else
    {
        printAllStats(outFile, div5, count5, div7, count7, other, countOther);
        printAllSorted(outFile, div5, count5, div7, count7, other, countOther);
        outFile.close();
    }
}

/* OUTPUT
aidentsang@Aidens-MacBook-Pro CS216_L1_AT % "/Users/aidentsang/Pierce college Labs C++/CS216_L1_AT/main"

 MAIN MENU 
1. Print arrays with average, median, and sum
2. Print arrays sorted in descending order
3. Quit and save results to a file
Enter your choice (1-3): 1

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
3. Quit and save results to a file
Enter your choice (1-3): 2

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
3. Quit and save results to a file
Enter your choice (1-3): 8

Invalid choice. Enter 1, 2, or 3.

 MAIN MENU 
1. Print arrays with average, median, and sum
2. Print arrays sorted in descending order
3. Quit and save results to a file
Enter your choice (1-3): !a-
Invalid input. Enter a number (1-3): 3

Are you sure you want to quit? (y/n): 1 
Invalid input. Please enter 'y' or 'n'.

Are you sure you want to quit? (y/n): n

 MAIN MENU 
1. Print arrays with average, median, and sum
2. Print arrays sorted in descending order
3. Quit and save results to a file
Enter your choice (1-3): 3

Are you sure you want to quit? (y/n): y

Results written to out_userchoices.txt. Goodbye!
aidentsang@Aidens-MacBook-Pro CS216_L1_AT % */
