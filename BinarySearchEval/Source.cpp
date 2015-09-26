////////////////////////////////////////////////////////////////////////// 
//       Name: Jeremy Nims
// Assignment: MP2 - Part 1 - Binary Search Test
//     Course: CPS 272, Wed 5:30
//////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <ctime>
#include <algorithm>

using namespace std;

const int ARRSIZE = 50000, RANDOMVALUES = 100000, RANDOMLIMIT = 200000;

template <typename T>
int binarySearch(const T arr[], int first, int last, const T& target);
void populateArray(int arr[], int sz);
void selectionSort(int num[], int sz);

void main()
{
    int table[ARRSIZE] = { 0 };
    int sumBinSearchSuccess = 0, 
        sumBinSearchFail = 0, 
        success = 0, 
        searchResult = 0;

    srand(time(NULL));

    populateArray(table, sizeof(table) / sizeof(table[0]));

    for (int i = 0; i < RANDOMVALUES; ++i)
    {
        searchResult = binarySearch(
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
            sumBinSearchFail += -1 * searchResult; // add the negative of the result
    }

    cout << "Empirical average case: "
        << (sumBinSearchSuccess / static_cast<double>(success))
        << endl << endl;

    cout << "Empirical worst case: "
        << (sumBinSearchFail / static_cast<double>(RANDOMVALUES - success))
        << endl << endl;

    cout << "Theoretical bound for worse case: "
        << 2.0 * (1.0 + int(log(static_cast<double>(ARRSIZE)) / log(2.0)))
        << endl << endl;
}

template <typename T>
int binarySearch(const T arr[], int first, int last, const T& target)
{
    int mid = 0, comparisons = 0;

    while (first <= last)
    {
        mid = (first + last) / 2;
        if (target == arr[mid])
        {
            comparisons++;
            return comparisons; // success
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
    return comparisons *= -1;  // failure (return the negative of comparisons)
}

void populateArray(int arr[], int sz)
{
    for (int i = 0; i < sz; i++)
        arr[i] = rand() % RANDOMLIMIT - 1;
    selectionSort(arr, sz);
}

void selectionSort(int num[], const int sz)
{
	int i, j, first, temp;
	for (i = sz - 1; i > 0; i--)
	{
		first = 0;                 
		for (j = 1; j <= i; j++)   
		{
			if (num[j] > num[first])
				first = j;
		}
		temp = num[first];
		num[first] = num[i];
		num[i] = temp;
	}
	return;
}