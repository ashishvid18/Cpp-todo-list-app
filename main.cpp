#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

class ToDoList {
private:
    vector<string> tasks;                 // Stores all tasks
    const string filename = "tasks.txt";  // File for saving tasks

public:
    ToDoList() { loadTasks(); }

    void addTask(const string& task) {
        if (task.empty()) {
            cout << "Task cannot be empty.\n";
            return;
        }
        tasks.push_back(task);
        cout << "✓ Task added.\n";
    }

    void viewTasks() const {
        if (tasks.empty()) {
            cout << "No tasks found.\n";
            return;
        }
        cout << "\n--- Your To-Do List ---\n";
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << (i + 1) << ". " << tasks[i] << '\n';
        }
    }

    void removeTask(int index) {
        if (index < 1 || index > static_cast<int>(tasks.size())) {
            cout << "Invalid task number.\n";
            return;
        }
        tasks.erase(tasks.begin() + (index - 1));
        cout << "✓ Task removed.\n";
    }

    void saveTasks() const {
        ofstream file(filename);
        if (!file) {
            cout << "Error: Could not open file for saving.\n";
            return;
        }
        for (const auto& task : tasks) file << task << '\n';
    }

    void loadTasks() {
        ifstream file(filename);
        if (!file) return; // No existing file yet
        string task;
        while (getline(file, task)) {
            if (!task.empty()) tasks.push_back(task);
        }
    }

    ~ToDoList() { saveTasks(); }
};

static void clearCin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    ToDoList todo;
    int choice = 0;

    while (true) {
        cout << "\n====== TO-DO LIST MENU ======\n"
             << "1. Add Task\n"
             << "2. View Tasks\n"
             << "3. Remove Task\n"
             << "4. Exit\n"
             << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Please enter a number (1-4).\n";
            clearCin();
            continue;
        }
        clearCin();

        if (choice == 1) {
            cout << "Enter task: ";
            string task;
            getline(cin, task);
            todo.addTask(task);
        } else if (choice == 2) {
            todo.viewTasks();
        } else if (choice == 3) {
            cout << "Enter task number to remove: ";
            int idx;
            if (!(cin >> idx)) {
                cout << "Please enter a valid number.\n";
                clearCin();
                continue;
            }
            clearCin();
            todo.removeTask(idx);
        } else if (choice == 4) {
            cout << "Exiting... Tasks saved.\n";
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
