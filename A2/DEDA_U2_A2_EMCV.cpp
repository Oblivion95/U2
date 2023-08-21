
#include <iostream>
#include <string>
// #include <fstream>

#define NO_DATA -1
#define MAX_SIZE 10

using namespace std;

enum Options {
  LINEAR = 1,
  BINARY,
  INTERPOLATION,
  EXIT
};

template <class T>
class Search {
  private:
    T array[MAX_SIZE];
    T sortedArray[MAX_SIZE];
    bool sorted = false;
    int iterations = 0;

  public:
  Search() {
    int data = 0;

    for (int i = 0; i < MAX_SIZE; i++) {
      cout << "Ingrese el valor " << i + 1 << ": ",
      cin >> data;

      if (isInArray(data)) {
        cout << "El valor " << data << " ya existe en el arreglo\n";
        i--;
        continue;
      }

      if (isOdd(data)) {
        cout << "El valor " << data << " es impar\n";
        i--;
        continue;
      }
      
      if (isNegative(data)) {
	cout << "El valor " << data  << " es negativo\n";      
      }

      array[i] = data;
      sortedArray[i] = data;
      cout << "\n";
    }


    cout << "Arreglo inicializado: \n";
    printArray();
  }

  int interpolationSearch(int key, int low, int high) {
    if (!sorted) {
      sort();
      sorted = true;
    }

    printIteration();

    if (sortedArray[low] > key || sortedArray[high] < key)
      return NO_DATA;

    iterations++;

    int position = low + (key - sortedArray[low]) * (high - low) / (sortedArray[high] - sortedArray[low]);

    if (sortedArray[position] == key)
      return position;

    if (sortedArray[position] > key)
      high = position - 1;
    else
      low = position + 1;

    return interpolationSearch(key, low, high);
  }

  int binarySearch(int key, int low, int high) {
    if (!sorted) {
      sort();
      sorted = true;
    }

    printIteration();

    if (sortedArray[low] > key || sortedArray[high] < key)
      return NO_DATA;

    iterations++;

    int mid = (low + high) / 2;

    if (sortedArray[mid] == key)
      return mid;

    if (sortedArray[mid] > key)
      high = mid - 1;
    else
      low = mid + 1;

    return binarySearch(key, low, high);
  }

  int linearSearch(int key) {
    int i = 0;

    while (i < MAX_SIZE && array[i] != key)  {
      iterations++;
      printIteration();
      i++;
    }

    return i < MAX_SIZE ? i : NO_DATA;
  }

  void printIteration() {
    cout << "Iteración: " << iterations << "\n";
  }

  int getIterations() {
    return iterations;
  }

  void setIterations(int iterations) {
    this->iterations = iterations;
  }

  void printArray() {
    for (int i = 0; i < MAX_SIZE; i++)
      cout << array[i] << "\n";
  }

    void printTotalIterations() {
      cout << "Total de iteraciones: " << iterations << "\n";
    }

  private:
    void sort() {
      for (int i = MAX_SIZE - 1; i >= 1; i--) {
        for (int j = 0; j < i; j++) {
          if (sortedArray[j] > sortedArray[j + 1]) {
            int temp = sortedArray[j];
            sortedArray[j] = sortedArray[j + 1];
            sortedArray[j + 1] = temp;
          }
        }
      }
    }

  bool isInArray(int key) {
    for (int i = 0; i < MAX_SIZE; i++) {
      if (array[i] == key)
        return true;
    }

    return false;
  }

  bool isOdd(int number) {
    return number % 2 == 1;
  }
  
  bool isNegative(int number) {
  	return number < 0;
  }
};

Options menu () {
  int opcion;

  cout << "*******Menú de opciones*******\n";

  cout << "1. Busqueda lineal\n";
  cout << "2. Busqueda binaria\n";
  cout << "3. Busqueda por interpolación\n";
  cout << "4. Salir\n";

  cout << "Ingrese una opción: ";

  cin >> opcion;

  return (Options)opcion;
}

void initArray(int array[]) {
  for (int i = 0; i < MAX_SIZE; i++) {

    cout << "Ingrese el valor " << i + 1 << ": ";
    cin >> array[i];
  }
}

int main() {
  Search<int> search;
  int key;
  auto index = NO_DATA;

  do {
    cout << "Ingrese el valor a buscar: ";
    cin >> key;
    index = NO_DATA;
    search.setIterations(0);

    switch(menu()) {
      case LINEAR:
        index = search.linearSearch(key);

        cout << "El valor " + to_string(key) + (index != NO_DATA ? " se encuentra en la posición: " + to_string(index) : " no se encuentra en el arreglo");
        cout << "\n";

        break;
      case BINARY:
        index = search.binarySearch(key, 0, MAX_SIZE - 1);

        cout << "El valor " + to_string(key) + (index != NO_DATA ? " se encuentra en la posición: " + to_string(index) : " no se encuentra en el arreglo");
        cout << "\n";

        break;

      case INTERPOLATION:
        index = search.interpolationSearch(key, 0, MAX_SIZE - 1);

        cout << "El valor " + to_string(key) + (index != NO_DATA ? " se encuentra en la posición: " + to_string(index) : " no se encuentra en el arreglo");
        cout << "\n";

        break;

      case EXIT:
        return 0;
    }
  } while (true);
}
