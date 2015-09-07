#include <iostream>
#include <ctime>

using namespace std;

const int ARRSIZE = 50000, RANDOMVALUES = 100000, RANDOMLIMIT = 200000;

template <typename T>
int binarySearch(const T arr[], int first, int last, const T& target)
{
    int mid, comparisons;

    while (first <= last)
    {
        mid = (first + last) / 2;
        if (target == arr[mid])
        {
            comparisons++;
            return comparisons;
        }
        if (target > arr[mid])
        {
            comparisons += 2;
            first = mid + 1;
        }
        else
        {
            comparisons += 2;
            last = mid - 1;
        }
    }
    return comparisons *= -1;
}

void populateArray(int arr[], int sz)
{
    for (int i = 0; i < sz; i++)
        arr[i] = rand() % RANDOMLIMIT - 1;
}

void main()
{
    int table[ARRSIZE] = { 0 };
    int sumBinSearchSuccess = 0, sumBinSearchFail = 0, success = 0;

    srand(time(NULL));

    populateArray(table, sizeof(table) / sizeof(table[0]));

    for (int i = 0; i < RANDOMVALUES; ++i)
    {
        int searchResult = binarySearch(
            table,
            0,
            sizeof(table) / sizeof(table[0]) - 1,
            rand() % (RANDOMLIMIT - 1));
        if (searchResult > 0)
        {
            sumBinSearchSuccess += searchResult;
            success++;
        }
        else if (searchResult < 0)
            sumBinSearchFail += searchResult;
    }
    cout << sumBinSearchSuccess << endl << sumBinSearchFail << endl << endl;

    //Empirical average case:
    cout << "Actual average: " << sumBinSearchSuccess / static_cast<double>(success) << endl << endl;
    //Empirical worst case:
    cout << "Actual worst: " << (sumBinSearchFail / static_cast<double>(RANDOMVALUES - success)) << endl << endl;
    //Theoretical bound for worse case:
    cout << "Expected worst: " << 2.0 * (1.0 + int(log(static_cast<double>(ARRSIZE)) / log(2.0))) << endl << endl;

}