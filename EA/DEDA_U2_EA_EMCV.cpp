#include <iostream>
#include <string>
#define MAX_STUDENTS 10
#define NO_DATA -1

using namespace std;

enum Options {
  ADD_STUDENTS = 1,
  SORT_DATA,
  FIND_RECORD,
  EXIT
};

enum SortOptions {
  BUBBLE_SORT = 1,
  SELECTION_SORT,
  INSERTION_SORT,
  QUICK_SORT,
  BACK_SORT
};

enum SearchOptions {
  LINEAR_SEARCH = 1,
  BINARY_SEARCH,
  INTERPOLATION_SEARCH,
  BACK_SEARCH
};

class Classroom {
  private:
    string students[MAX_STUDENTS];
    float notes[MAX_STUDENTS];
    int size = 0;
    bool sorted = false;
    int iterations = 0;

  public:
    void fillData() {
      cout << "Ingrese los estuduantes: \n";

      for (int i = 0; i < MAX_STUDENTS; i++) {
        cout << "Ingrese el nombre del estudiante " << i + 1 << ": ";
        // cin.ignore();
        while (getchar() != '\n');
        getline(cin, students[i], '\n');
        cout << "Ingrese la calificación del estudiante " << i + 1 << ": ";

        do {
          cin >> notes[i];
        } while (isNoteNotInRange(notes[i]));

        size++;
      }
    }

    void bubbleSort() {
      if (sorted) return;

      iterations = 0;

      int i, j;
      string auxStudent;
      float auxNote;

      for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
          if (notes[j] > notes[j + 1]) {
            auxNote = notes[j];
            notes[j] = notes[j + 1];
            notes[j + 1] = auxNote;

            auxStudent = students[j];
            students[j] = students[j + 1];
            students[j + 1] = auxStudent;

            iterations++;
          }
        }
      }

      sorted = true;
    }

    void selectionSort() {
      if (sorted) return;

      iterations = 0;

      int i, j, minIndex;
      string auxStudent;
      float auxNote;

      for (i = 0; i < size - 1; i++) {
        minIndex = i;

        for (j = i + 1; j < size; j++) {
          if (notes[j] < notes[minIndex]) {
            minIndex = j;
          }
        }

        auxNote = notes[minIndex];
        notes[minIndex] = notes[i];
        notes[i] = auxNote;

        auxStudent = students[minIndex];
        students[minIndex] = students[i];
        students[i] = auxStudent;

        iterations++;
      }

      sorted = true;
    }

    void insertionSort() {
      if (sorted) return;

      iterations = 0;

      int i, j;
      string auxStudent;
      float auxNote;

      for (i = 1; i < size; i++) {
        auxNote = notes[i];
        auxStudent = students[i];
        j = i - 1;

        while (j >= 0 && notes[j] > auxNote) {
          notes[j + 1] = notes[j];
          students[j + 1] = students[j];
          j--;

          iterations++;
        }

        notes[j + 1] = auxNote;
        students[j + 1] = auxStudent;
      }

      sorted = true;
    }

    // void partition() {
    //   int i, j;
    //   string auxStudent;
    //   float auxNote;

    //   i = -1;
    //   j = size;

    //   while (true) {
    //     do {
    //       i++;
    //     } while (notes[i] < notes[size - 1]);

    //     do {
    //       j--;
    //     } while (notes[j] > notes[size - 1]);

    //     if (i >= j) {
    //       break;
    //     }

    //     auxNote = notes[i];
    //     notes[i] = notes[j];
    //     notes[j] = auxNote;

    //     auxStudent = students[i];
    //     students[i] = students[j];
    //     students[j] = auxStudent;
    //   }

    //   auxNote = notes[i];
    //   notes[i] = notes[size - 1];
    //   notes[size - 1] = auxNote;

    //   auxStudent = students[i];
    //   students[i] = students[size - 1];
    //   students[size - 1] = auxStudent;
    // }

    // void quickSort(int left, int right) {
    //   int i, j;
    //   string auxStudent;
    //   float auxNote;

    //   i = left;
    //   j = right;

    //   partition();

    //   if (left < j) {
    //     quickSort(left, j);
    //   }

    //   if (i < right) {
    //     quickSort(i, right);
    //   }
    // }

    int partition(int left, int right) {
      int i, j;
      string auxStudent;
      float auxNote;

      i = left;
      j = right;

      while (true) {
        do {
          i++;
        } while (notes[i] < notes[right]);

        do {
          j--;
        } while (notes[j] > notes[right]);

        if (i >= j) {
          break;
        }

        auxNote = notes[i];
        notes[i] = notes[j];
        notes[j] = auxNote;

        auxStudent = students[i];
        students[i] = students[j];
        students[j] = auxStudent;
      }

      auxNote = notes[i];
      notes[i] = notes[right];
      notes[right] = auxNote;

      auxStudent = students[i];
      students[i] = students[right];
      students[right] = auxStudent;

      iterations++;

      return i;
    }

    void quickSort(int left, int right) {
      int pivot;

      if (sorted) return;

      if (left < right) {
        pivot = partition(left, right);
        quickSort(left, pivot - 1);
        quickSort(pivot + 1, right);
      }

      sorted = true;
    }

    void sortByName() {
      int i, j;
      string auxStudent;
      float auxNote;

      for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
          if (students[j] > students[j + 1]) {
            auxNote = notes[j];
            notes[j] = notes[j + 1];
            notes[j + 1] = auxNote;

            auxStudent = students[j];
            students[j] = students[j + 1];
            students[j + 1] = auxStudent;
          }
        }
      }
    }

    int interpolationSearch(string name) {

    iterations = 0;

    int low = 0;
    int high = size - 1;

    sortByName();

    cout << "name: " << name.length() << students[low].length() << endl;

    cout << "name: " << (low <= high) << (name >= students[low]) << (name <= students[high]) << endl;

    while (low <= high && name >= students[low] && name <= students[high]) {
        int d = (static_cast<int>(high - low) / (students[high].length() - students[low].length() ? students[high].length() - students[low].length() : 1));
        int l = name.length() - students[low].length() < 0  ? name.length() - students[low].length() : 1;
        int pos = low + d * l;

        cout << "pos: " << pos << endl;

        cout << "pos: " << pos << endl;

        int comparison = name.compare(students[pos]);

        if (comparison == 0) return pos;

        if (comparison < 0) {
            high = pos - 1;
        } else {
            low = pos + 1;
        }

        iterations++;
    }

    return NO_DATA; // Not found
  }

    int linearSearch(string name) {
      for (int i = 0; i < size; i++) {
        if (name == students[i]) {
          return i;
        }
      }

      return NO_DATA;
    }

    int binarySearch(string name) {
      int low, high, mid;

      low = 0;
      high = size - 1;

      sortByName();

      cout << "name: " << name << endl;

      while (low <= high) {
        mid = (low + high) / 2;

        cout << "mid: " << mid << endl;

        if (students[mid] == name) {
          return mid;
        } else if (students[mid] < name) {
          low = mid + 1;
        } else {
          high = mid - 1;
        }
      }

      return NO_DATA;
    }

    void sort(SortOptions option) {
      if (isEmpty()) {
        cout << "No hay datos para ordenar" << endl;
        return;
      }

      switch(option) {
        case BUBBLE_SORT:
          bubbleSort();
          break;

        case SELECTION_SORT:
          selectionSort();
          break;

        case INSERTION_SORT:
          insertionSort();
          break;

        case QUICK_SORT:
          iterations = 0;

          quickSort(0, size - 1);
          break;

        case BACK_SORT:
          return;

        default:
          cout << "Opción inválida" << endl;
          return;
      }

      cout << "Datos ordenados por calificación: " << endl;
      showData();
      showIterations();
    }

    void search(SearchOptions option, string name) {
      int index;

      if (isEmpty()) {
        cout << "No hay datos para buscar" << endl;
        return;
      }

      switch(option) {
        case LINEAR_SEARCH:

          index = linearSearch(name);
          break;

        case BINARY_SEARCH:
          bubbleSort();
          index = binarySearch(name);
          break;

        case INTERPOLATION_SEARCH:
          bubbleSort();
          index = interpolationSearch(name);
          break;
        case BACK_SEARCH:
          return;

        default:
          cout << "Opción inválida" << endl;
          return;
      }

      if (index == NO_DATA) {
        cout << "No se encontró el registro" << endl;
      } else {
        cout << "Registro encontrado" << endl;
        cout << "Nombre: " << students[index] << endl;
        cout << "Calificación: " << notes[index] << endl;
        cout << "Iteraciones: " << iterations << endl;
        cout << "posición: " << index << endl;
      }
    }

    bool isEmpty() {
      return size == 0;
    }

    bool isSorted() {
      return true;
    }

    void showData() {
      cout << "Estudiantes" << endl;

      for (int i = 0; i < size; i++) {
        cout << "Nombre: " << students[i] << endl;
        cout << "Calificación: " << notes[i] << endl;
      }
    }

    void showIterations() {
      cout << "Iteraciones: " << iterations << endl;
    }

    bool isNoteNotInRange(float note) {
      bool isNotInRange = note < 0 || note > 10;

      if (isNotInRange) {
        cout << "La calificación debe estar entre 0 y 10. Intente de nuevo: ";
      }

      return isNotInRange;
    }
};

Options showMenu() {
  int option;

  cout << "1. Ingresar estudiantes" << endl;
  cout << "2. Ordenar datos" << endl;
  cout << "3. Buscar registro" << endl;
  cout << "4. Salir" << endl;
  cout << "Ingrese una opción: ";
  cin >> option;

  return (Options)option;
}

SortOptions showSortMenu() {
  int option;

  cout << "1. Ordenar por burbuja" << endl;
  cout << "2. Ordenar por selección" << endl;
  cout << "3. Ordenar por inserción" << endl;
  cout << "4. Ordenar por quicksort" << endl;
  cout << "5. Regresar" << endl;
  cout << "Ingrese una opción: ";
  cin >> option;

  return (SortOptions)option;
}

SearchOptions showSearchMenu() {
  int option;

  cout << "1. Buscar por búsqueda lineal" << endl;
  cout << "2. Buscar por búsqueda binaria" << endl;
  cout << "3. Buscar por búsqueda por interpolación" << endl;
  cout << "4. Regresar" << endl;
  cout << "Ingrese una opción: ";
  cin >> option;

  return (SearchOptions)option;
}


int main() {
  Classroom classroom;

  do {
    switch(showMenu()) {
      case ADD_STUDENTS:
        classroom.fillData();
        break;

      case SORT_DATA:
        classroom.sort(showSortMenu());
        break;

      case FIND_RECORD: {
        while (getchar() != '\n');

        string name;
        cout << "Ingrese el nombre del alumno: ";
        getline(cin, name, '\n');

        classroom.search(showSearchMenu(), name);
        break;
      }

      case EXIT:
        return 0;

      default:
        cout << "Opción inválida" << endl;
        break;
    }
  } while(true);
  return 0;
}
