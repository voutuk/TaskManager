#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>

using namespace std;
struct Date {
    int d;
    int m;
    int y;
    int size;
}; 
struct Task {
    int priority;
    int index;
    Date deadline;
    string name;
    string description;
};
struct TaskData {
    int size = 0;
    Task* tasks = new Task[size];
};


void txtColor(HANDLE color, int fg, string txt) {
    SetConsoleTextAttribute(color, fg | 240);
    cout << txt;
}

void pushBack(TaskData* task, Task newValue) {
    ++task->size;
    Task* tmpStruct = new Task[task->size];
    for (int i = 0; i < task->size - 1; i++) { tmpStruct[i] = task->tasks[i]; }
    tmpStruct[task->size - 1].priority = newValue.priority;
    tmpStruct[task->size - 1].index = newValue.index;
    tmpStruct[task->size - 1].deadline = newValue.deadline;
    tmpStruct[task->size - 1].name = newValue.name;
    tmpStruct[task->size - 1].description = newValue.description;
    delete[] task->tasks;
    task->tasks = tmpStruct;
}

int dateSize(int d, int m, int y) {
    int daysMax[12]{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int days = d;
    for (int i = y; i >= 1; i--) {
        for (int j = 0; j < m; j++) { days += daysMax[m - 1]; }
    }
    return days;
}

bool validateDate(string date, int& d, int& m, int& y) {
    string tmpD = date, tmpM = date, tmpY = date;
    char symbol[5]{ '.', ',', '/', '\\', '-' };
    int daysMax[12]{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }, tmp = 0;
    for (int i = 0; i < 5; i++) {
        int tmp1 = date.find(symbol[i]);
        if (tmp1 != -1) {
            tmpD.erase(tmp1, date.size() - tmp1), ++tmp;
            int tmp2 = date.find(symbol[i], tmp1);
            if (date.find(symbol[i], tmp1) != -1) {
                tmpM.erase(0, tmp1 + 1);
                tmpM.erase(date.find(symbol[i], tmp1), date.size() - date.find(symbol[i], tmp1)), ++tmp;
                if (date.find(symbol[i], tmp2 + 1) != -1) { tmpY.erase(0, date.find(symbol[i], tmp2 + 1) + 1); }
            }
        }
    }
    if (tmp != 2) { return false; }
    if (stoi(tmpY) % 4 == 0) { daysMax[1] = 29; }
    if (stoi(tmpM) < 1 || stoi(tmpM) > 12 || stoi(tmpD) < 1 || stoi(tmpD) > daysMax[stoi(tmpM) - 1] || stoi(tmpY) < 1) { return false; }
    d = stoi(tmpD), m = stoi(tmpM), y = stoi(tmpY);
    return true;
}

void coutTask(TaskData task, int i, HANDLE color) {

    int tmp = task.tasks[i].index;
    int tmp2 = task.tasks[i].priority;
    string deadline = to_string(task.tasks[i].deadline.d) + "/" + to_string(task.tasks[i].deadline.m) + "/" + to_string(task.tasks[i].deadline.y);
    string create = "27/11/2022"; /////////////////////////////// DATE

    int str1 = 3 + task.tasks[i].name.length();
    while ((tmp /= 10) > 0) str1++;
    int str2 = task.tasks[i].description.length() + 2;
    int str3 = 4 + deadline.length();
    while ((tmp2 /= 10) > 0) str3++;
    int str4 = create.length() + 2;
    int max = max(str2, max(str3, max(str4, str1)));

    cout << "+";
    for (int i = 0; i < max; i++) { txtColor(color, rand() % 16, "-"); }
    txtColor(color, 0, "+");
    cout << endl << "| " << task.tasks[i].index << " " << task.tasks[i].name;
    for (int i = 0; i < max - str1; i++) { cout << " "; }
    cout << "|" << endl << "| " << task.tasks[i].description;
    for (int i = 0; i < max - str2; i++) { cout << " "; }
    cout << " |" << endl << "| " << task.tasks[i].priority << " " << deadline;
    for (int i = 0; i < max - str3; i++) { cout << " "; }
    cout << " |" << endl << "| " << create;
    for (int i = 0; i < max - str4; i++) { cout << " "; }
    cout << " |" << endl << "+";
    for (int i = 0; i < max; i++) { txtColor(color, rand() % 16, "-"); }
    txtColor(color, 0, "+");
}

void delTask(TaskData& task, int index) {
    --task.size;
    Task* tmpStruct = new Task[task.size];
    for (int i = 0; i < task.size; i++) {
        if (i < index) { tmpStruct[i] = task.tasks[i]; }
        else if (i >= index) { tmpStruct[i] = task.tasks[i + 1]; }
    }
    delete[] task.tasks;
    task.tasks = tmpStruct;
}

bool sortTask(TaskData task, HANDLE color, string select) {
    if (select.find("N") != -1 || select.find("n") != -1) {
        for (int step = 0; step < task.size - 1; ++step) {
            for (int i = 0; i < task.size - 1; i++) {
                if (select.find(">") != -1) {
                    if (task.tasks[i].name < task.tasks[i + 1].name) { swap(task.tasks[i], task.tasks[i + 1]); }
                }
                else {
                    if (task.tasks[i].name > task.tasks[i + 1].name) { swap(task.tasks[i], task.tasks[i + 1]); }
                }
            }
        }
    } else if (select.find("U") != -1 || select.find("u") != -1) {
        for (int step = 0; step < task.size - 1; ++step) {
            for (int i = 0; i < task.size - 1; i++) {
                if (select.find(">") != -1) {
                    if (task.tasks[i].index < task.tasks[i + 1].index) { swap(task.tasks[i], task.tasks[i + 1]); }
                } else {
                    if (task.tasks[i].index > task.tasks[i + 1].index) { swap(task.tasks[i], task.tasks[i + 1]); }
                }
            }
        }
    } else if (select.find("P") != -1 || select.find("p") != -1) {
        for (int step = 0; step < task.size - 1; ++step) {
            for (int i = 0; i < task.size - 1; i++) {
                if (select.find(">") != -1) {
                    if (task.tasks[i].priority < task.tasks[i + 1].priority) { swap(task.tasks[i], task.tasks[i + 1]); }
                } else {
                    if (task.tasks[i].priority > task.tasks[i + 1].priority) { swap(task.tasks[i], task.tasks[i + 1]); }
                }
            }
        }
    } else if (select.find("E") != -1 || select.find("e") != -1) {
        for (int step = 0; step < task.size - 1; ++step) {
            for (int i = 0; i < task.size - 1; i++) {
                if (select.find(">") != -1) {
                    if (task.tasks[i].deadline.size < task.tasks[i + 1].deadline.size) { swap(task.tasks[i], task.tasks[i + 1]); }
                } else {
                    if (task.tasks[i].deadline.size > task.tasks[i + 1].deadline.size) { swap(task.tasks[i], task.tasks[i + 1]); }
                }
            }
        }
    }
    int d = 27, m = 11, y = 2022, d1, m1, y1;   //////////////////////////////////////////////////////////////////////// DATE
    int daysMax[12]{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (y % 4 == 0) { daysMax[1] = 29; }
    if (select.find("D") != -1 || select.find("d") != -1) {
        for (int i = 0; i < task.size; i++) {
            if (task.tasks[i].deadline.d == d && task.tasks[i].deadline.m == m && task.tasks[i].deadline.y == y) {
                coutTask(task, i, color);
                cout << endl;
            }
        }
    } else if (select.find("W") != -1 || select.find("w") != -1) {
        if (d + 7 > daysMax[m - 1]) {
            d1 = d + 7 - daysMax[m - 1], y1 = y;
            if (m == 11) { m1 = 0, y1 = y + 1; }
            else { m1 = m + 1; }
            for (int i = 0; i < task.size; i++) {
                if (task.tasks[i].deadline.d >= d && task.tasks[i].deadline.d < d1 && task.tasks[i].deadline.m == m1 && task.tasks[i].deadline.y == y1) {
                    coutTask(task, i, color);
                    cout << endl;

                }
            }
        } else {
            d1 = d + 7;
            for (int i = 0; i < task.size; i++) {
                if (task.tasks[i].deadline.d > d && task.tasks[i].deadline.d < d1 && task.tasks[i].deadline.m == m && task.tasks[i].deadline.y == y) {
                    coutTask(task, i, color);
                    cout << endl;

                }
            }
        }
    } else if (select.find("M") != -1 || select.find("M") != -1) {
        y1 = y;
        if (m == 11) { m1 = 0, y1 = y + 1; }
        else { m1 = m + 1; }
        for (int i = 0; i < task.size; i++) {
            if (task.tasks[i].deadline.m > m && task.tasks[i].deadline.m < m1 && task.tasks[i].deadline.y == y1) {
                coutTask(task, i, color);
                cout << endl;
            }
        }
    } else {
        for (int i = 0; i < task.size; i++) {
            coutTask(task, i, color);
            cout << endl;
        }
    }

    return true;
}

bool findTask(TaskData& task, HANDLE color, string search) {
    int d, m, y;
    bool a = validateDate(search, d, m, y);
    for (int i = 0; i < task.size; i++) {
        if (task.tasks[i].name.find(search) != -1) { coutTask(task, i, color); }
        if (task.tasks[i].description.find(search) != -1) { coutTask(task, i, color); }
        //if (task.priority[i] == stoi(search)) { cout1(task, i, color); }
        if (a == true) {
            if (task.tasks[i].deadline.d == d && task.tasks[i].deadline.m == m && task.tasks[i].deadline.y == y) { coutTask(task, i, color); }
        }
    }
    cout << endl;
    return true;
}

bool saveFile(ofstream& fouts, TaskData task) {
    if (fouts.is_open()) {
        fouts << task.size << endl;
        for (int i = 0; i < task.size; i++){
            fouts << task.tasks[i].priority << endl;
            fouts << task.tasks[i].name << endl;
            fouts << task.tasks[i].index << endl;
            fouts << task.tasks[i].description << endl;
            fouts << task.tasks[i].deadline.d << endl;
            fouts << task.tasks[i].deadline.m << endl;
            fouts << task.tasks[i].deadline.y << endl;
            fouts << task.tasks[i].deadline.size << endl;
        }
        return true;
    } else { return false; }
}

void openFile(TaskData& task) {
    cout << "Drag the file into the window: ";
    cout << "Drag the file into the window: ";
    getline(cin, date);
    ifstream file;
    file.open(date);
    openFile(file, task);

    string tmpSize, tmptmp;
    Task tmp;
    if (fin.is_open()) {
        getline(fin, tmpSize);
        for (int i = 0; i < stoi(tmpSize); i++) {
            getline(fin, tmptmp);
            tmp.priority = stoi(tmptmp);
            getline(fin, tmptmp);
            tmp.name = tmptmp;
            getline(fin, tmptmp);
            tmp.index = stoi(tmptmp);
            getline(fin, tmptmp);
            tmp.description = tmptmp;
            getline(fin, tmptmp);
            tmp.deadline.d = stoi(tmptmp);
            getline(fin, tmptmp);
            tmp.deadline.m = stoi(tmptmp);
            getline(fin, tmptmp);
            tmp.deadline.y = stoi(tmptmp);
            getline(fin, tmptmp);
            tmp.deadline.size = stoi(tmptmp);
            pushBack(&task, tmp);
        }
    }
    file.close();
}


int main() {
    system("color F0");
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    TaskData task;
    Task newValue;
    string date;
    int tmp, tmp2;

    while (1) {
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
        system("cls");
        cout << endl;
        cout << " ==== MENU ==== \n\n";
        cout << " 1. New task \n 2. Edit task \n 3. Delete task \n 4. Cout task \n 5. Find task \n 6. Exit \n > Enter num: ";
        cin >> tmp;
        switch (tmp) {
        case 1:
            system("cls");
            cin.ignore();
            cout << "\n ==== Create task ==== \n\n";
            cout << " Enter name: ";
            getline(cin, newValue.name);
            cout << " Enter description: ";
            getline(cin, newValue.description);
            do {
                cout << " Enter priority: ";
                cin >> newValue.priority;
            } while (newValue.priority < 1 || newValue.priority > 5);
            cin.ignore();
            int d, m, y;
            do {
                cout << " Enter deadline: ";
                getline(cin, date);
            } while (validateDate(date, d, m, y) == false);
            newValue.deadline.d = d, newValue.deadline.m = m, newValue.deadline.y = y, newValue.deadline.size = dateSize(d, m, y), newValue.index = task.size + 1;
            pushBack(&task, newValue);
            cout << " Successfully!\n";
            system("pause");
            break;
        case 10: // Debug
            system("cls");
            for (int i = 0; i < task.size; i++){
                cout << "Task index: " << task.tasks[i].index << endl;
                cout << "Name: " << task.tasks[i].name << endl;
                cout << "Description: " << task.tasks[i].description << endl;
                cout << "Priority: " << task.tasks[i].priority << endl;
                cout << "Date: " << task.tasks[i].deadline.d << "/" << task.tasks[i].deadline.m << "/" << task.tasks[i].deadline.y << " -- " << task.tasks[i].deadline.size << endl;
            }
            cout << " Successfully!\n";
            system("pause");
            break;
        case 3:
            system("cls");
            cout << "\n ==== Delete task ==== \n\n";
            while (1) {
                cout << " Enter number task: ";
                cin >> tmp;
                for (int i = 0; i < task.size; i++){
                    if (task.tasks[i].index == tmp) { 
                        delTask(task, tmp-1); 
                        tmp = 0;
                        break;
                    }
                }
                if (tmp == 0) { break; }
                cout << " Task not found, please try again :(" << endl;
                cout << " Type \"0\" to exit" << endl;
            }
            cout << " Successfully!" << endl;
            system("pause");
            break;
        case 2:
            system("cls");
            cout << "\n ==== Edit task ==== \n\n";
            cout << " 1. Name \n 2. Description \n 3. Priority \n 4. Deadline \n 5. All \n 6.Exit\n > Select an option: ";
            cin >> tmp;
            if (tmp == 0) { break; }
            cout << " Enter number task: ";
            cin >> tmp2;
            for (int i = 0; i < task.size; i++) {
                if (task.tasks[i].index == tmp2) {
                    if (tmp == 1) {
                        cin.ignore();
                        cout << " Enter name: ";
                        getline(cin, newValue.name);
                        task.tasks[i].name = newValue.name;
                        break;
                    }
                    else if (tmp == 2) {
                        cin.ignore();
                        cout << " Enter description: ";
                        getline(cin, newValue.description);
                        task.tasks[i].description = newValue.description;
                        break;
                    }
                    else if (tmp == 3) {
                        do {
                            cout << " Enter priority: ";
                            cin >> newValue.priority;
                        } while (newValue.priority < 1 || newValue.priority > 5);
                        task.tasks[i].priority = newValue.priority;
                        break;
                    }
                    else if (tmp == 4) {
                        cin.ignore();
                        do {
                            cout << " Enter deadline: ";
                            getline(cin, newValue.name);
                        } while (validateDate(newValue.name, d, m, y) == false);
                        newValue.deadline.d = d, newValue.deadline.m = m, newValue.deadline.y = y, newValue.deadline.size = dateSize(d, m, y);
                        task.tasks[i].deadline = newValue.deadline;
                        break;
                    }else if (tmp == 5) {
                        cin.ignore();
                        cout << " Enter name: ";
                        getline(cin, newValue.name);
                        task.tasks[i].name = newValue.name;

                        cout << " Enter description: ";
                        getline(cin, newValue.description);
                        task.tasks[i].description = newValue.description;

                        do {
                            cout << " Enter priority: ";
                            cin >> newValue.priority;
                        } while (newValue.priority < 1 || newValue.priority > 5);
                        task.tasks[i].priority = newValue.priority;
                        cin.ignore();
                        do {
                            cout << " Enter deadline: ";
                            getline(cin, newValue.name);
                        } while (validateDate(newValue.name, d, m, y) == false);
                        newValue.deadline.d = d, newValue.deadline.m = m, newValue.deadline.y = y, newValue.deadline.size = dateSize(d, m, y);
                        task.tasks[i].deadline = newValue.deadline;
                    }
                }
            }
            break;
        case 4:
            system("cls");
            cout << "\n ==== Cout task ==== \n\n";
            cout << " [N] Name  [E] Deadline [P] Priority [U] Number  [D] Day  [W] Week  [M] Month  [>]Z..A\n > Select an option: ";
            cin.ignore();
            getline(cin, date);
            sortTask(task, color, date);
            cout << " Successfully!" << endl;
            system("pause");
            break;
        case 5:
            system("cls");
            cout << "\n ==== Find task ==== \n\n";
            cout << " > Enter a search query: ";
            cin.ignore();
            getline(cin, date);
            findTask(task, color, date);
            cout << " Successfully!" << endl;
            system("pause");
            break;
        case 6:
            txtColor(color, 4, " Exit ");
            ofstream fout;
            fout.open("dataTask.txt");
            saveFile(fout, task);
            fout.close();
            delete[] task.tasks;
            return 0;
        }
    }

}