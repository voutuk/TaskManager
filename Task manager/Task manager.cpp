#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#pragma warning(disable : 4996)
using namespace std;

struct Task {
    int name_s = 0, data_s = 0, priority_s = 0, ROWS_D = 3, COLS_D = 0;
    string* name = new string[name_s];
    string* data = new string[data_s];
    int* priority = new int[priority_s];
    int** create_date = new int* [ROWS_D];
    int** end_date = new int* [ROWS_D];

};

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

bool validate_date(string date, int& d, int& m, int& y) {
    int size = date.length() + 1;
    int* sablon = new int[size]; // ! 

    int ascii[10]{ 48, 49, 50, 51, 52, 53, 54, 55, 56, 57 };
    int days_max[12]{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    for (int i = 0; i < size + 1; i++) { sablon[i] = -1; }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 10; j++) {
            if (date[i] == ascii[j]) { sablon[i] = j; }
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
    return true;
}

bool create_task(Task& task_data, string new_name, string new_data, int new_priority, string new_date) {
    if (new_priority < 1 || new_priority > 5) { return false; } // Priority
    int d, m, y;
    if (validate_date(new_date, d, m, y) == false) { return false; } // Valitade date

    task_data.name = push_back(task_data.name, task_data.name_s, new_name); // Add name
    task_data.data = push_back(task_data.data, task_data.data_s, new_data); // Add description
    task_data.priority = push_back(task_data.priority, task_data.priority_s, new_priority); // Add priority
    task_data.end_date = push_back_2D(task_data.end_date, task_data.ROWS_D, task_data.COLS_D, d, m, y); // Add deadline
    time_t t = time(NULL);
    tm tm = *localtime(&t);
    task_data.create_date = push_back_2D(task_data.create_date, task_data.ROWS_D, task_data.COLS_D, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900); // Add create task day

    return true;
}

bool cout_task(Task task_data) {
    for (int i = 0; i < task_data.name_s; i++) {
        cout << " === Task index " << i << " === " << endl;
        cout << "Task name: " << task_data.name[i] << endl << "Task description: " << task_data.data[i] << endl << "Task priority: " << task_data.priority[i] << endl << "Deadline: " << task_data.end_date[0][i] << "/" << task_data.end_date[1][i] << "/" << task_data.end_date[2][i] << endl << "Create task date: " << task_data.create_date[0][i] << "/" << task_data.create_date[1][i] << "/" << task_data.create_date[2][i] << endl;
    }
    return true;
}

bool cout_task_upd(Task task_data, int visible) {
    int d = 13, m = 11, y = 2022, d1, m1, y1;
    int days_max[12]{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (y % 4 == 0) { days_max[1] = 29; }

    if (visible == 1) {
        for (int i = 0; i < task_data.name_s; i++) {
            if (task_data.end_date[0][i] == d && task_data.end_date[1][i] == m && task_data.end_date[2][i] == y) {
                cout << " === Task index " << i << " === " << endl;
                cout << "Task name: " << task_data.name[i] << endl << "Task description: " << task_data.data[i] << endl << "Task priority: " << task_data.priority[i] << endl << "Deadline: " << task_data.end_date[0][i] << "/" << task_data.end_date[1][i] << "/" << task_data.end_date[2][i] << endl << "Create task date: " << task_data.create_date[0][i] << "/" << task_data.create_date[1][i] << "/" << task_data.create_date[2][i] << endl;
            }
        }
    }
    else if (visible == 2) {
        if (d + 7 > days_max[m - 1]) {
            d1 = d + 7 - days_max[m - 1], y1 = y;
            if (m == 11) { m1 = 0, y1 = y + 1; }
            else { m1 = m + 1; }

            for (int i = 0; i < task_data.name_s; i++) {
                if (task_data.end_date[0][i] > d && task_data.end_date[0][i] < d1 && task_data.end_date[1][i] == m1 && task_data.end_date[2][i] == y1) {
                    cout << " === Task index " << i << " === " << endl;
                    cout << "Task name: " << task_data.name[i] << endl << "Task description: " << task_data.data[i] << endl << "Task priority: " << task_data.priority[i] << endl << "Deadline: " << task_data.end_date[0][i] << "/" << task_data.end_date[1][i] << "/" << task_data.end_date[2][i] << endl << "Create task date: " << task_data.create_date[0][i] << "/" << task_data.create_date[1][i] << "/" << task_data.create_date[2][i] << endl;
                }
            }
        }
        else {
            d1 = d + 7;
            for (int i = 0; i < task_data.name_s; i++) {
                if (task_data.end_date[0][i] > d && task_data.end_date[0][i] < d1 && task_data.end_date[1][i] == m && task_data.end_date[2][i] == y) {
                    cout << " === Task index " << i << " === " << endl;
                    cout << "Task name: " << task_data.name[i] << endl << "Task description: " << task_data.data[i] << endl << "Task priority: " << task_data.priority[i] << endl << "Deadline: " << task_data.end_date[0][i] << "/" << task_data.end_date[1][i] << "/" << task_data.end_date[2][i] << endl << "Create task date: " << task_data.create_date[0][i] << "/" << task_data.create_date[1][i] << "/" << task_data.create_date[2][i] << endl;
                }
            }
        }

    }
    else if (visible == 3) {
        y1 = y;
        if (m == 11) { m1 = 0, y1 = y + 1; }
        else { m1 = m + 1; }
        for (int i = 0; i < task_data.name_s; i++) {
            if (task_data.end_date[1][i] > m && task_data.end_date[1][i] < m1 && task_data.end_date[2][i] == y1) {
                cout << " === Task index " << i << " === " << endl;
                cout << "Task name: " << task_data.name[i] << endl << "Task description: " << task_data.data[i] << endl << "Task priority: " << task_data.priority[i] << endl << "Deadline: " << task_data.end_date[0][i] << "/" << task_data.end_date[1][i] << "/" << task_data.end_date[2][i] << endl << "Create task date: " << task_data.create_date[0][i] << "/" << task_data.create_date[1][i] << "/" << task_data.create_date[2][i] << endl;
            }
        }
    }

    return true;
}

bool delete_task(Task& task_data, int index) {
    if (index < 0 || index > task_data.name_s) { return false; }
    task_data.name = del(task_data.name, task_data.name_s, index);
    task_data.data = del(task_data.data, task_data.data_s, index);
    task_data.priority = del(task_data.priority, task_data.priority_s, index);
    task_data.end_date = del_2D(task_data.end_date, task_data.ROWS_D, task_data.COLS_D, index);
    task_data.create_date = del_2D(task_data.create_date, task_data.ROWS_D, task_data.COLS_D, index);

    return true;
}

bool edit_task(Task& task_data, int index, string edit_name, string edit_data, int edit_priority, string edit_new_date) {
    if (index < 0 || index > task_data.name_s) { return false; }
    if (edit_name != " ") { task_data.name[index] = edit_name; }
    if (edit_data != " ") { task_data.data[index] = edit_data; }
    if (edit_priority != -1) {
        if (edit_priority < 1 || edit_priority > 5) { return false; }
        task_data.priority[index] = edit_priority;
    }
    if (edit_new_date != " ") {
        int d, m, y;
        if (validate_date(edit_new_date, d, m, y) == false) { return false; } // Valitade date
        task_data.end_date[0][index] = d;
        task_data.end_date[1][index] = m;
        task_data.end_date[2][index] = y;
    }

    return true;
}

bool find_task(Task& task_data, string search) {
    for (size_t i = 0; i < task_data.name_s; i++) {
        if (task_data.name[i].find(search) < task_data.name[i].length()) { cout << "Task name: " << task_data.name[i] << endl; }
        if (task_data.data[i].find(search) < task_data.data[i].length()) { cout << "Task name: " << task_data.data[i] << endl; }
        string priority[5]{ "1", "2", "3", "4", "5" };
        for (int i = 0; i < 5; i++) {
            if (search == priority[i]) {

            }
        }
        //skip priority

    }
    return true;
}

bool sort_task(Task task_data, int search) {
    Task find;
    for (int i = 0; i < task_data.name_s; i++) {
        find.name[i] = task_data.name[i];
        find.data[i] = task_data.data[i];
        find.priority[i] = task_data.priority[i];
    }
    /*
    for (int i = 0; i < task_data.name_s; i++) {
        find.name[i] = task_data.name[i];
        find.data[i] = task_data.data[i];
        find.priority[i] = task_data.priority[i];
    }
    //
    for (int i = 0; i < task_data.ROWS_D; i++) {
        find.end_date[i] = new int[task_data.COLS_D];
        for (int j = 0; j < task_data.COLS_D; j++) { find.end_date[i][j] = task_data.end_date[i][j]; }
        find.create_date[i] = new int[task_data.COLS_D];
        for (int j = 0; j < task_data.COLS_D; j++) { find.create_date[i][j] = task_data.create_date[i][j]; }
    }

    if (search == 1) {
        for (int step = 0; step < task_data.name_s - 1; ++step) {
            for (int i = 0; i < task_data.name_s - 1; i++) {
                if (find.name[i] > find.name[i + 1]) { // UP / DOWN
                    swap(find.name[i], find.name[i + 1]);
                    swap(find.priority[i], find.priority[i + 1]);
                    swap(find.data[i], find.data[i + 1]);
                    swap(find.end_date[i], find.end_date[i + 1]);
                    swap(find.create_date[i], find.create_date[i + 1]);
                }
            }
        }
    }
    for (int i = 0; i < task_data.name_s; i++) {
        cout << " === Task index " << i << " === " << endl;
        cout << "Task name: " << find.name[i] << endl << "Task description: " << find.data[i] << endl << "Task priority: " << find.priority[i] << endl << "Deadline: " << find.end_date[0][i] << "/" << find.end_date[1][i] << "/" << find.end_date[2][i] << endl << "Create task date: " << find.create_date[0][i] << "/" << find.create_date[1][i] << "/" << find.create_date[2][i] << endl;
    }*/
    return true;
}


int main()
{
    Task task_data;
    for (int i = 0; i < task_data.ROWS_D; i++) {
        task_data.end_date[i] = new int[task_data.COLS_D];
        task_data.create_date[i] = new int[task_data.COLS_D];
    }

    while (1) {
        system("cls");
        cout << " === TEST MENU === " << endl;
        cout << "1. New task" << endl << "2. Delete task" << endl << "3. Edit task" << endl << "4. Cout task test" << endl << "5. Find task" << endl << "6. Cout task" << endl;
        int tmp;
        cout << "Enter num: ";
        cin >> tmp;
        //
        string new_name, new_data, new_date, find;
        int new_priority;

        switch (tmp)
        {
        case 1:
            system("cls");
            cout << " === Create task === " << endl << endl;
            cout << "Enter name: ";
            cin >> new_name;
            cout << "Enter description: ";
            cin >> new_data;
            cout << "Enter priority: ";
            cin >> new_priority;
            cout << "Enter deadline: ";
            cin >> new_date;
            if (create_task(task_data, new_name, new_data, new_priority, new_date) == false) { cout << "Oops incorrect data!" << endl; }
            break;
        case 2:
            system("cls");
            cout << " === Delete task === " << endl << endl;
            cout << "Enter index task: ";
            cin >> tmp;
            if (delete_task(task_data, tmp) == false) { cout << "Oops incorrect data!"; }
            break;
        case 3:
            system("cls");
            cout << " === Edit task === " << endl << endl;
            cout << "Enter index task: ";
            cin >> tmp;
            cout << "Enter name: ";
            cin >> new_name;
            cout << "Enter description: ";
            cin >> new_data;
            cout << "Enter priority: ";
            cin >> new_priority;
            cout << "Enter deadline: ";
            cin >> new_date;
            if (edit_task(task_data, tmp, new_name, new_data, new_priority, new_date) == false) { cout << "Oops incorrect data!"; }
            break;
        case 4:
            system("cls");
            cout << " === Cout task TEST === " << endl << endl;
            cout_task(task_data);
            system("pause");
            break;
        case 5:
            system("cls");
            cout << " === Find task === " << endl << endl;
            cout << "Enter: ";
            cin >> find;
            find_task(task_data, find);
            system("pause");
            break;
        case 6:
            system("cls");
            cout << " === Cout task === " << endl << endl;
            cout_task_upd(task_data, 2);
            system("pause");
            break;
        case 7:
            system("cls");
            cout << " === Sort task === " << endl << endl;
            sort_task(task_data, 1);
            system("pause");
            break;
        default:
            delete[] task_data.name;
            delete[] task_data.data;
            delete[] task_data.priority;
            for (int i = 0; i < task_data.ROWS_D; i++) {
                delete[] task_data.end_date[i];
                delete[] task_data.create_date[i];
            }
            delete[] task_data.end_date;
            delete[] task_data.create_date;
            return 0;
        }
    }


    //delete
    /*delete[] task_data.name;
    delete[] task_data.data;
    delete[] task_data.priority;
    for (int i = 0; i < task_data.ROWS_D; i++) {
        delete[] task_data.end_date[i];
        delete[] task_data.create_date[i];
    }
    delete[] task_data.end_date;
    delete[] task_data.create_date;*/

}

