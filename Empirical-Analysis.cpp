#include <chrono>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;
using namespace std::chrono;

void generateTestData(int *&ptr, int size, string arrange = "random")
{
  ptr = new int[size];
  if (arrange == "random")
  {
    for (int i = 0; i < size; i++)
      ptr[i] = rand() % (2 * size);
  }
  else if (arrange == "reverseOrder")
  {
    for (int i = 0, j = size; i < size; i++)
      ptr[i] = j--;
  }
}

void bubbleSort(int arr[], int n)
{
  int i, j;
  bool swapped;
  for (i = 0; i < n - 1; i++)
  {
    swapped = false;
    for (j = 0; j < n - i - 1; j++)
    {
      if (arr[j] > arr[j + 1])
      {
        swap(arr[j], arr[j + 1]);
        swapped = true;
      }
    }
    if (swapped == false)
      break;
  }
}

void selectionSort(int arr[], int n)
{
  int i, j, min_idx;
  for (i = 0; i < n - 1; i++)
  {
    min_idx = i;
    for (j = i + 1; j < n; j++)
    {
      if (arr[j] < arr[min_idx])
        min_idx = j;
    }
    if (min_idx != i)
      swap(arr[min_idx], arr[i]);
  }
}

void merge(int array[], int const left, int const mid,
           int const right)
{
  int const subArrayOne = mid - left + 1;
  int const subArrayTwo = right - mid;
  auto *leftArray = new int[subArrayOne],
       *rightArray = new int[subArrayTwo];
  for (auto i = 0; i < subArrayOne; i++)
    leftArray[i] = array[left + i];
  for (auto j = 0; j < subArrayTwo; j++)
    rightArray[j] = array[mid + 1 + j];
  auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
  int indexOfMergedArray = left;
  while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo)
  {
    if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo])
    {
      array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
      indexOfSubArrayOne++;
    }
    else
    {
      array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
      indexOfSubArrayTwo++;
    }
    indexOfMergedArray++;
  }
  while (indexOfSubArrayOne < subArrayOne)
  {
    array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
    indexOfSubArrayOne++;
    indexOfMergedArray++;
  }
  while (indexOfSubArrayTwo < subArrayTwo)
  {
    array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
    indexOfSubArrayTwo++;
    indexOfMergedArray++;
  }
  delete[] leftArray;
  delete[] rightArray;
}

void mergeSort(int array[], int const begin, int const end)
{
  if (begin >= end)
    return;
  int mid = begin + (end - begin) / 2;
  mergeSort(array, begin, mid);
  mergeSort(array, mid + 1, end);
  merge(array, begin, mid, end);
}

int partition(int arr[], int low, int high)
{
  int pivot = arr[high];
  int i = (low - 1);
  for (int j = low; j <= high; j++)
  {
    if (arr[j] < pivot)
    {
      i++;
      swap(arr[i], arr[j]);
    }
  }
  swap(arr[i + 1], arr[high]);
  return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
  if (low < high)
  {
    int pi = partition(arr, low, high);
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  }
}

int main()
{
  srand(time(0));
  int sizes[12] = {10, 100, 500, 1000, 5000, 10000, 20000, 50000, 80000, 100000, 150000, 200000};
  int *data;
  for (auto size : sizes)
  {
    cout << "Problem size is: [" << size << "]\n";
    generateTestData(data, size);
    // bubbleSort
    auto startBubble = high_resolution_clock::now();
    bubbleSort(data, size);
    auto stopBubble = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stopBubble - startBubble);
    cout << "Bubble Sort:" << (double)(duration.count() / 1000.0) << endl;
    // selectionSort
    auto startSelection =
        high_resolution_clock::now();
    selectionSort(data, size);
    auto stopSelection = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stopSelection - startSelection);
    cout << "Selection Sort: " << (double)(duration.count() / 1000.0) << endl;
    // mergeSort
    auto startMerge = high_resolution_clock::now();
    mergeSort(data, 0, size - 1);
    auto stopMerge = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stopMerge - startMerge);
    cout << "Merge Sort: " << (double)(duration.count() / 1000.0) << endl;
    // quickSort
    auto startQuick = high_resolution_clock::now();
    quickSort(data, 0, size - 1);
    auto stopQuick = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stopQuick - startQuick);
    cout << "Quick Sort: " << (double)(duration.count() / 1000.0) << endl;
    delete[] data;
    cout << "\n\n";
  }
  return 0;
}