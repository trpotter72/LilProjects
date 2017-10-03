#include <iostream>

//Checks to see if pivot is the largest value in the arr
bool isLarger (int* arr, int size, int pivot) {
  for (int i = 0; i < size; i++) {
    if (arr[i] > pivot) {
      return true;
    }
  }
  return false;
}


//Checks to see if pivot is the smallest value in the arr
bool isSmaller (int* arr, int size, int pivot) {
  for (int i = 0; i < size; i++) {
    if (arr[i] < pivot) {
      return true;
    }
  }
  return false;
}


//remove pivot function
//   Return: array with the pivot position removed
//  Inputs: array and size of array
int* removePivot(int* arr, int size) {
  if (size < 2) {
    throw("removePivot on less than 2 elements");
  }

  int* new_arr = new int[size-1];

  for (int i = 0; i < size; i++) {
    if (i != (size-1)/2 )
    {
      if (i > (size-1)/2) {
        new_arr[i-1] = arr[i];
      }
      else {
        new_arr[i] = arr[i];
      }
    }
  }
  return new_arr;
}


bool allWorstCase (int* arr, int size) {
  if (size == 2) {
    return true;
  }

  if (isLarger(arr, size, arr[(size-1)/2]) && isSmaller(arr, size, arr[(size-1)/2])) {
    return false;
  }
  else {
    int* arr_new = removePivot(arr, size);
    //delete arr;
    bool worst = allWorstCase(arr_new, size-1);
    //delete arr_new;
    return worst;
  }
}




int main() {
  int test_cases;
  std::cin >> test_cases;

  for (int test = 0; test < test_cases; test++)  {
    int array_size;
    std::cin >> array_size;
    int* arr = new int[array_size];
    for (int i = 0; i < array_size; i++) {
      std::cin >> arr[i];
    }
    std::cout << "Case #" << test+1 << ": ";
    if(allWorstCase(arr, array_size)) {
      std::cout << "YES" << std::endl;
    }
    else {
      std::cout << "NO" << std::endl;
    }
  }
}
