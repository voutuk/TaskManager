#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

struct TaskData {
    int size = 0;
    const int ROWS = 3;
    int* priority = new int[size];
    int* index = new int[size];
    int* createDateSize = new int[size];
    int* deadlineSize = new int[size];
    int** createDate = new int* [ROWS];
    int** deadline = new int* [ROWS];
    string* name = new string[size];
    string* description = new string[size];

};
void txtColor(HANDLE color, int fg, int bg, string txt) {
    SetConsoleTextAttribute(color, fg | bg);
    cout << txt;
}
template <typename Type>
void pushBack(Type*& arr, int& size, Type value) {
    Type* arrNew = new Type[size];
    for (int i = 0; i < size - 1; i++) { arrNew[i] = arr[i]; }
    arrNew[size - 1] = value;
    delete[] arr;
    arr = arrNew;
}

void cout1(TaskData task, int i, HANDLE color) {
    int tmp = task.index[i];
    int tmp2 = task.priority[i];
    string deadline = to_string(task.deadline[0][i]) + "/" + to_string(task.deadline[1][i]) + "/" + to_string(task.deadline[2][i]);
    string create = to_string(task.createDate[0][i]) + "/" + to_string(task.createDate[1][i]) + "/" + to_string(task.createDate[2][i]);

    int str1 = 3 + task.name[i].length();
    while ((task.index[i] /= 10) > 0) str1++;
    int str2 = task.description[i].length() + 2;
    int str3 = 4 + deadline.length();
    while ((task.priority[i] /= 10) > 0) str3++;
    int str4 = create.length() + 2;
    int max = max(str2, max(str3, max(str4, str1)));
    cout << "+";
    for (int i = 0; i < max; i++) { txtColor(color, rand() % 16, 192, "-"); }
    txtColor(color, 15, 192, "+");
    cout << endl << "| " << tmp << " " << task.name[i];
    for (int i = 0; i < max - str1; i++) { cout << " "; }
    cout << "|" << endl << "| " << task.description[i];
    for (int i = 0; i < max - str2; i++) { cout << " "; }
    cout << " |" << endl << "| " << tmp2 << " " << deadline;
    for (int i = 0; i < max - str3; i++) { cout << " "; }
    cout << " |" << endl << "| " << create;
    for (int i = 0; i < max - str4; i++) { cout << " "; }
    cout << " |" << endl << "+";
    for (int i = 0; i < max; i++) { txtColor(color, rand() % 16, 192, "-"); }
    txtColor(color, 15, 192, "+");
}

void pushBack2D(int**& arr, int ROWS, int& COLS, int data1, int data2, int data3) {
    //++COLS;
    int** tmp_arr = new int* [ROWS];
    for (int i = 0; i < ROWS; i++) {
        tmp_arr[i] = new int[COLS];
        for (int j = 0; j < COLS - 1; j++) { tmp_arr[i][j] = arr[i][j]; }
    }

    tmp_arr[0][COLS - 1] = data1;
    tmp_arr[1][COLS - 1] = data2;
    tmp_arr[2][COLS - 1] = data3;

    delete[] arr;
    arr = tmp_arr;
}

template <typename Type>
void del(Type*& arr, int& size, int index) {
    //size--;
    Type* arrNew = new Type[size];
    for (int i = 0; i < size; i++) {
        if (i < index) { arrNew[i] = arr[i]; }
        else if (i >= index) { arrNew[i] = arr[i + 1]; }
    }
    delete[] arr;
    arr = arrNew;
}

void del2D(int**& arr, int ROWS, int& COLS, int ind) {
    //--COLS;
    int** tmp_arr = new int* [ROWS];
    for (int i = 0; i < ROWS; i++) {
        tmp_arr[i] = new int[COLS];
        for (int j = 0; j < COLS; j++) {
            if (i < ind) { tmp_arr[i][j] = arr[i][j]; }
            else if (i >= ind) { tmp_arr[i][j] = arr[i][j + 1]; }
        }
    }
    delete[] arr;
    arr = tmp_arr;
}

int dateSort(int d, int m, int y) {
    int days_max[12]{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int days = d;
    for (int i = y; i >= 1; i--) {
        for (int j = 0; j < m; j++) { days += days_max[m - 1]; }
    }
    return days;
}

template <typename Type>
bool sort(TaskData& task, Type data, int sort = 0) {
    for (int step = 0; step < task.size - 1; ++step) {
        for (int i = 0; i < task.size - 1; i++) {
            if (sort == 0) {
                if (data[i] > data[i + 1]) {
                    swap(task.priority[i], task.priority[i + 1]);
                    swap(task.index[i], task.index[i + 1]);
                    swap(task.createDateSize[i], task.createDateSize[i + 1]);
                    swap(task.deadlineSize[i], task.deadlineSize[i + 1]);
                    swap(task.createDate[i], task.createDate[i + 1]);
                    swap(task.deadline[i], task.deadline[i + 1]);
                    swap(task.name[i], task.name[i + 1]);
                    swap(task.description[i], task.description[i + 1]);
                }
            }
            else {
                if (data[i] < data[i + 1]) {
                    swap(task.priority[i], task.priority[i + 1]);
                    swap(task.index[i], task.index[i + 1]);
                    swap(task.createDateSize[i], task.createDateSize[i + 1]);
                    swap(task.deadlineSize[i], task.deadlineSize[i + 1]);
                    swap(task.createDate[i], task.createDate[i + 1]);
                    swap(task.deadline[i], task.deadline[i + 1]);
                    swap(task.name[i], task.name[i + 1]);
                    swap(task.description[i], task.description[i + 1]);
                }
            }

        }
    }
    return true;
}

bool validateDate(string date, int& d, int& m, int& y) { // ПЕРЕРОБИТИ
    int size = date.length();
    int* arr = new int[size];

    int asciiNumber[10]{ 48, 49, 50, 51, 52, 53, 54, 55, 56, 57 };
    int daysMax[12]{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    for (int i = 0; i < size + 1; i++) { arr[i] = -1; }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 10; j++) {
            if (date[i] == asciiNumber[j]) { arr[i] = j; }
        }
    }

    if (arr[2] == -1 && arr[5] == -1) {
        d = arr[0] * 10 + arr[1], m = arr[3] * 10 + arr[4];
        y = arr[6] * 1000 + arr[7] * 100 + arr[8] * 10 + arr[9];
    }
    else if (arr[1] == -1 && arr[4] == -1) {
        d = arr[0], m = arr[2] * 10 + arr[3];
        y = arr[5] * 1000 + arr[6] * 100 + arr[7] * 10 + arr[8];
    }
    else if (arr[2] == -1 && arr[4] == -1) {
        d = arr[0] * 10 + arr[1], m = arr[3];
        y = arr[5] * 1000 + arr[6] * 100 + arr[7] * 10 + arr[8];
    }
    else if (arr[1] == -1 && arr[3] == -1) {
        d = arr[0], m = arr[2];
        y = arr[4] * 1000 + arr[5] * 100 + arr[6] * 10 + arr[7];
    }
    else { return false; }
    int tmp = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == -1) { ++tmp; }
    }
    if (y % 4 == 0) { daysMax[1] = 29; }
    if (m < 1 || m > 12 || d < 1 || d > daysMax[m - 1] || y < 1 || tmp > 2) { return false; }
    return true;
}

bool createTask(TaskData& task, string newName, string newData, int newPriority, string newDate) {
    if (newPriority < 1 || newPriority > 5) { return false; }
    int d, m, y;
    if (validateDate(newDate, d, m, y) == false) { return false; } // Valitade date
    task.size++;
    pushBack(task.name, task.size, newName);
    pushBack(task.description, task.size, newData);
    pushBack(task.priority, task.size, newPriority);
    pushBack2D(task.deadline, task.ROWS, task.size, d, m, y);
    pushBack2D(task.createDate, task.ROWS, task.size, 1, 04, 1996);
    pushBack(task.index, task.size, task.size);
    pushBack(task.createDateSize, task.size, dateSort(1, 04, 1996));
    pushBack(task.deadlineSize, task.size, dateSort(d, m, y));
    return true;
}

bool coutTask(TaskData task, HANDLE color) {
    string tmp;
    cout << "[A] Назва \n[B] Дедлайн \n[C] Дата створення \n[D] День \n[E] Неділя \n[F] Місяць" << endl;
    cin.ignore();
    getline(cin, tmp);
    if (tmp.find("A") != -1) { sort(task, task.name); }
    else if (tmp.find("C") != -1) { sort(task, task.createDateSize); }
    else if (tmp.find("B") != -1) { sort(task, task.deadlineSize); }
    int d = task.createDate[0][0], m = task.createDate[1][0], y = task.createDate[2][0], d1, m1, y1;  // Переписать
    int daysMax[12]{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (y % 4 == 0) { daysMax[1] = 29; }
    if (tmp.find("D") != -1) {
        for (int i = 0; i < task.size; i++) {
            if (task.deadline[0][i] == d && task.deadline[1][i] == m && task.deadline[2][i] == y) {
                cout1(task, i, color);
                cout << endl;
            }
        }
    }
    else if (tmp.find("E") != -1) {
        if (d + 7 > daysMax[m - 1]) {
            d1 = d + 7 - daysMax[m - 1], y1 = y;
            if (m == 11) { m1 = 0, y1 = y + 1; }
            else { m1 = m + 1; }
            for (int i = 0; i < task.size; i++) {
                if (task.deadline[0][i] > d && task.deadline[0][i] < d1 && task.deadline[1][i] == m1 && task.deadline[2][i] == y1) {
                    cout1(task, i, color);
                    cout << endl;

                }
            }
        }
        else {
            d1 = d + 7;
            for (int i = 0; i < task.size; i++) {
                if (task.deadline[0][i] > d && task.deadline[0][i] < d1 && task.deadline[1][i] == m && task.deadline[2][i] == y) {
                    cout1(task, i, color);
                    cout << endl;

                }
            }
        }
    }
    else if (tmp.find("F") != -1) {
        y1 = y;
        if (m == 11) { m1 = 0, y1 = y + 1; }
        else { m1 = m + 1; }
        for (int i = 0; i < task.size; i++) {
            if (task.deadline[1][i] > m && task.deadline[1][i] < m1 && task.deadline[2][i] == y1) {
                cout1(task, i, color);
                cout << endl;
            }
        }
    }
    else {
        for (int i = 0; i < task.size; i++) {
            cout1(task, i, color);
            cout << endl;
        }
    }

    return true;
}


bool deleteTask(TaskData& task, int number) {
    for (int i = 0; i < task.size; i++) {
        if (task.index[i] == number) {
            --task.size;
            del(task.name, task.size, i);
            del(task.description, task.size, i);
            del(task.priority, task.size, i);
            del2D(task.deadline, task.ROWS, task.size, i);
            del2D(task.createDate, task.ROWS, task.size, i);
            del(task.index, task.size, i);
            del(task.createDateSize, task.size, i);
            del(task.deadlineSize, task.size, i);
            return true;
        }
    }
    return false;
}

bool editTask(TaskData& task, int number, string editName, string editDescription, int editPriority, string editNewDate) {
    for (int i = 0; i < task.size; i++) {
        if (task.index[i] == number) {
            if (editName != "") { task.name[i] = editName; }
            if (editDescription != "") { task.description[i] = editDescription; }
            if (editPriority != 0) {
                if (editPriority < 1 || editPriority > 5) { return false; }
                task.priority[i] = editPriority;
            }
            if (editNewDate != "") {
                int d1, m1, y1;
                if (validateDate(editNewDate, d1, m1, y1) == false) { return false; }
                task.deadline[0][i] = d1;
                task.deadline[1][i] = m1;
                task.deadline[2][i] = y1;
            }
            return true;
        }
    }
    return false;
}

bool findTask(TaskData& task, string search) {
    int d, m, y;
    bool a = validateDate(search, d, m, y);
    for (int i = 0; i < task.size; i++) {
        if (task.name[i].find(search) != -1) {
            cout << " === Task index " << task.index[i] << " === " << endl;
            cout << "Task name: " << task.name[i] << endl << "Task description: " << task.description[i] << endl << "Task priority: " << task.priority[i] << endl << "Deadline: " << task.deadline[0][i] << "/" << task.deadline[1][i] << "/" << task.deadline[2][i] << endl << "Create task date: " << task.createDate[0][i] << "/" << task.createDate[1][i] << "/" << task.createDate[2][i] << endl;
        }
        if (task.description[i].find(search) != -1) {
            cout << " === Task index " << task.index[i] << " === " << endl;
            cout << "Task name: " << task.name[i] << endl << "Task description: " << task.description[i] << endl << "Task priority: " << task.priority[i] << endl << "Deadline: " << task.deadline[0][i] << "/" << task.deadline[1][i] << "/" << task.deadline[2][i] << endl << "Create task date: " << task.createDate[0][i] << "/" << task.createDate[1][i] << "/" << task.createDate[2][i] << endl;
        }
        if (task.priority[i] == stoi(search)) {
            cout << " === Task index " << task.index[i] << " === " << endl;
            cout << "Task name: " << task.name[i] << endl << "Task description: " << task.description[i] << endl << "Task priority: " << task.priority[i] << endl << "Deadline: " << task.deadline[0][i] << "/" << task.deadline[1][i] << "/" << task.deadline[2][i] << endl << "Create task date: " << task.createDate[0][i] << "/" << task.createDate[1][i] << "/" << task.createDate[2][i] << endl;
        }
        if (a == true) {
            if (task.deadline[0][i] == d && task.deadline[1][i] == m && task.deadline[2][i] == y) {
                cout << " === Task index " << task.index[i] << " === " << endl;
                cout << "Task name: " << task.name[i] << endl << "Task description: " << task.description[i] << endl << "Task priority: " << task.priority[i] << endl << "Deadline: " << task.deadline[0][i] << "/" << task.deadline[1][i] << "/" << task.deadline[2][i] << endl << "Create task date: " << task.createDate[0][i] << "/" << task.createDate[1][i] << "/" << task.createDate[2][i] << endl;
            } if (task.createDate[0][i] == d && task.createDate[1][i] == m && task.createDate[2][i] == y) {
                cout << " === Task index " << task.index[i] << " === " << endl;
                cout << "Task name: " << task.name[i] << endl << "Task description: " << task.description[i] << endl << "Task priority: " << task.priority[i] << endl << "Deadline: " << task.deadline[0][i] << "/" << task.deadline[1][i] << "/" << task.deadline[2][i] << endl << "Create task date: " << task.createDate[0][i] << "/" << task.createDate[1][i] << "/" << task.createDate[2][i] << endl;
            }
        }
    }
    return true;
}
int startProgram(int language) {
    string tmp;
    do{
        system("cls");
        cout << "The settings file is not found, so you need to create a new one. \n1. Ukrainian \n2. English \nChoose a language: ";
        getline(cin, tmp);
    } while (tmp != "1" && tmp != "2");
    if (tmp == "1") { language = 1; }
    else { language = 2; }

    while (tmp != "y" && tmp != "Y") {
        system("cls");
        cout << "1. Біла \n2. Чорна \n3. Червона \n4. Синя \n5. Жовта \n Виберіть тему: ";
        getline(cin, tmp);
        if (tmp == "1") { system("color F0"); }
        else if (tmp == "2") { system("color 0F"); }
        else if (tmp == "3") { system("color CF"); }
        else if (tmp == "4") { system("color 9F"); }
        else if (tmp == "5") { system("color E0"); }
    }
    system("cls");
    return language;
}

int main()
{
    int language = 0;
    startProgram(language);
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    TaskData task;

    for (int i = 0; i < task.ROWS; i++) {
        task.deadline[i] = new int[task.size];
        task.createDate[i] = new int[task.size];
    }

    while (1) {
        system("cls");
        cout << " === TEST MENU === " << endl;
        cout << "1. New task" << endl << "2. Delete task" << endl << "3. Edit task" << endl << "4. Cout task test" << endl << "5. Find task" << endl << "6. Cout task" << endl;
        int tmp;
        cout << "Enter num: ";
        cin >> tmp;
        string newName, newData, newDate, find;
        int newPriority;

        switch (tmp)
        {
        case 1:
            system("cls");
            do {
                cout << endl << " === Нове завдання === " << endl << endl;
                cout << "Enter name: ";
                cin.ignore();
                getline(cin, newName);
                cout << "Enter description: ";
                getline(cin, newData);
                cout << "Enter priority: ";
                cin >> newPriority;
                cin.ignore();
                cout << "Enter deadline: ";
                getline(cin, newDate);
            } while (createTask(task, newName, newData, newPriority, newDate) == false);
            break;
        case 2:
            system("cls");
            cout << " === Delete task === " << endl << endl;
            cout << "Enter index task: ";
            cin >> tmp;
            if (deleteTask(task, tmp) == false) { cout << "Упс ви ввели неправельні данні!" << endl; }
            break;
        case 3:
            system("cls");
            cout << " === Edit task === " << endl << endl;
            cout << "Enter index task: ";
            cin >> tmp;
            cout << "Enter name: ";
            cin >> newName;
            cout << "Enter description: ";
            cin >> newData;
            cout << "Enter priority: ";
            cin >> newPriority;
            cout << "Enter deadline: ";
            cin >> newDate;
            if (editTask(task, tmp, newName, newData, newPriority, newDate) == false) { cout << "Упс ви ввели неправельні данні!" << endl; }
            break;
        case 4:
            system("cls");
            cout << " === Cout task TEST === " << endl << endl;
            coutTask(task, color);
            system("pause");
            break;
            /*
            case 5:
                system("cls");
                cout << " === Find task === " << endl << endl;
                cout << "Enter: ";
                cin >> find;
                findTask(task, find);
                pause();
                break;
            case 6:
                system("cls");
                cout << " === Cout task === " << endl << endl;
                coutTaskUpd(task, 2);
                pause();
                break;
            */
        default:
            // Delete
            return 0;
        }
    }

}






