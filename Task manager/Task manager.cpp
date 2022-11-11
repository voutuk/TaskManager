#include <iostream>
#include <string>
using namespace std;

template <typename Type>
Type* push_back(Type* arr, int& size, Type value) {
    size++;
    Type* arrNew = new Type[size];
    for (int i = 0; i < size - 1; i++) { arrNew[i] = arr[i]; }
    arrNew[size - 1] = value;
    delete[] arr;
    return arrNew;
}

int** push_back_2D(int** arr, int ROWS, int& COLS, int data1, int data2, int data3) {
    ++COLS;
    int** tmp_arr = new int* [ROWS];
    for (int i = 0; i < ROWS; i++) {
        tmp_arr[i] = new int[COLS];
        for (int j = 0; j < COLS - 1; j++) { tmp_arr[i][j] = arr[i][j]; }
    }

    tmp_arr[0][COLS - 1] = data1;
    tmp_arr[1][COLS - 1] = data2;
    tmp_arr[2][COLS - 1] = data3;

    delete[] arr;
    return tmp_arr;
}

template <typename Type>
Type* del(Type* arr, int& size, int index) {
    size--;
    Type* arrNew = new Type[size];
    for (int i = 0; i < size; i++) {
        if (i < index) { arrNew[i] = arr[i]; }
        else if (i >= index) { arrNew[i] = arr[i + 1]; }
    }
    delete[] arr;
    return arrNew;
}

int** del_2D(int** arr, int ROWS, int& COLS, int ind) {
    --COLS;
    int** tmp_arr = new int* [ROWS];
    for (int i = 0; i < ROWS; i++) {
        tmp_arr[i] = new int[COLS];
        for (int j = 0; j < COLS; j++) {
            if (i < ind) { tmp_arr[i][j] = arr[i][j]; }
            else if (i >= ind) { tmp_arr[i][j] = arr[i][j + 1]; }
        }
    }
    delete[] arr;
    return tmp_arr;
}

bool create_task(string*& name, int& name_s, string*& data, int& data_s, int*& priority, int& priority_s, int**& end_date, int ROWS_D, int& COLS_D, string new_name, string new_data, int new_priority, string new_date) {
    if (new_priority < 1 || new_priority > 5) { return false; }
    //validate date 
    const int size = new_date.length();
    int sablon[size + 1], d, m, y;
    int ascii[10]{ 48, 49, 50, 51, 52, 53, 54, 55, 56, 57 };
    int days_max[12]{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    for (int i = 0; i < size + 1; i++) { sablon[i] = -1; }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 10; j++) {
            if (new_date[i] == ascii[j]) { sablon[i] = j; }
        }
    }

    if (sablon[2] == -1 && sablon[5] == -1 && sablon[10] == -1) {
        d = sablon[0] * 10 + sablon[1], m = sablon[3] * 10 + sablon[4];
        y = sablon[6] * 1000 + sablon[7] * 100 + sablon[8] * 10 + sablon[9];
    }
    else if (sablon[1] == -1 && sablon[4] == -1 && sablon[9] == -1) {
        d = sablon[0], m = sablon[2] * 10 + sablon[3];
        y = sablon[5] * 1000 + sablon[6] * 100 + sablon[7] * 10 + sablon[8];
    }
    else if (sablon[2] == -1 && sablon[4] == -1 && sablon[9] == -1) {
        d = sablon[0] * 10 + sablon[1], m = sablon[3];
        y = sablon[5] * 1000 + sablon[6] * 100 + sablon[7] * 10 + sablon[8];
    }
    else if (sablon[1] == -1 && sablon[3] == -1 && sablon[8] == -1) {
        d = sablon[0], m = sablon[2];
        y = sablon[4] * 1000 + sablon[5] * 100 + sablon[6] * 10 + sablon[7];
    }
    else { return false; }
    if (y % 4 == 0) { days_max[1] = 29; }
    if (d > 31 || m > 12 || d < 1 || m < 1 || d > days_max[m - 1] || y < 1) { return false; }

    name = push_back(name, name_s, new_name);

    data = push_back(data, data_s, new_data);

    priority = push_back(priority, priority_s, new_priority);

    end_date = push_back_2D(end_date, ROWS_D, COLS_D, d, m, y);

    return true;
}

bool cout_task(string*& name, int& name_s, string*& data, int& data_s, int*& priority, int& priority_s, int**& end_date, int ROWS_D, int& COLS_D) {
    for (int i = 0; i < name_s; i++) {
        cout << "Task index " << i << " : " << endl;
        cout << name[i] << endl << data[i] << endl << priority[i] << endl << end_date[0][i] << " " << end_date[1][i] << " " << end_date[2][i] << endl;
    }
    return true;
}

bool delete_task(string*& name, int& name_s, string*& data, int& data_s, int*& priority, int& priority_s, int**& end_date, int ROWS_D, int& COLS_D) {
    int tmp;
    cout << "Enter index: ";
    cin >> tmp;

    name = removee(name, name_s, tmp);
    data = removee(data, data_s, tmp);
    priority = removee(priority, priority_s, tmp);
    removee_2D(end_date, ROWS_D, COLS_D, tmp);
    return true;
}

bool edit_task(string*& name, int& name_s, string*& data, int& data_s, int*& priority, int& priority_s, int**& end_date, int ROWS_D, int& COLS_D) {
    int tmp, tmp2;
    cout << "Enter index: ";
    cin >> tmp;
    cout << "1. Task Name" << endl << "2. Task data " << endl << "3. TAsk priority " << endl << "4. Task Date" << endl << "Enter edit data: ";
    cin >> tmp2;
    switch (tmp2)
    {
    case 1:
        cout << "Enter task name: ";
        cin >> tmp2;
        name[tmp] = tmp2;
        break;
    case 2:
        cout << "Enter task data: ";
        cin >> tmp2;
        data[tmp] = tmp2;
        break;
    case 3:
        cout << "Enter task data: ";
        cin >> tmp2;
        data[tmp] = tmp2;
        break;
    case 4:
        cout << "Enter task data: ";
        cin >> tmp2;
        data[tmp] = tmp2;
        break;
    default:
        break;
    }
    return true;
}

int main()
{
    //create masiv
    int name_s = 0, data_s = 0, priority_s = 0, ROWS_D = 3, COLS_D = 0;
    string* name = new string[name_s];
    string* data = new string[data_s];
    int* priority = new int[priority_s];
    int** end_date = new int* [ROWS_D];
    for (int i = 0; i < ROWS_D; i++) {
        end_date[i] = new int[COLS_D];
    }
    while (1) {
        cout << " === TEST TASK MANAGER === " << endl;
        cout << "1. New task" << endl << "2. Delete task" << endl << "3. TEST Cout task" << endl;
        int tmp;
        cout << "Enter num: ";
        cin >> tmp;

        switch (tmp)
        {
        case 1:
            create_task(name, name_s, data, data_s, priority, priority_s, end_date, ROWS_D, COLS_D);
            break;
        case 2:
            delete_task(name, name_s, data, data_s, priority, priority_s, end_date, ROWS_D, COLS_D);
            break;
        case 3:
            cout_task(name, name_s, data, data_s, priority, priority_s, end_date, ROWS_D, COLS_D);
            break;
        default:
            //return 0;
            break;
        }
    }


    //delete
    delete[] name;
    delete[] data;
    delete[] priority;
    for (int i = 0; i < ROWS_D; i++) { delete[] end_date[i]; }
    delete[] end_date;
}

