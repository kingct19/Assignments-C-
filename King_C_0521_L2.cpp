#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define MAX_NODES 10

typedef struct Employees
{
    char name;
    Employees *backups;
} Employee;

Employee *manager = NULL;

bool searchEmployee(char key)
{
    Employee *current = manager;

    if (current == NULL)
    {
        return false;
    }

    if (current->name == key)
    {
        return true;
    }

    else
    {
        current = current->backups;
        while (current != manager)
        {
            if (current->name == key)
            {
                return true;
            }
            current = current->backups;
        }
    }
    return false;
}

void insert(char name)
{
    Employee *current = manager;
    Employee *newEmployee = (Employee *)malloc(sizeof(Employee));
    newEmployee->name = name;

    if (current == NULL)
    {
        newEmployee->backups = newEmployee;
        manager = newEmployee;
    }
    else
    {
        while (current->backups != manager)
        {
            current = current->backups;
        }
        current->backups = newEmployee;
    }
}

void generate_backup_plan()
{
    for (int i = 0; i < MAX_NODES; i++)
    {
        bool not_unique = true;

        do
        {
            char random = 'A' + rand() % 26;
            if (searchEmployee(random) == false)
            {
                insert(random);
                not_unique = false;
            }
        } while (not_unique);
    }
}

void display()
{
    Employee *current;
    current = manager;

    bool first_time = true;
    while (first_time || current != manager)
    {
        cout << current->name << "->";
        current = current->backups;

        if (current == manager)
        {
            cout << current->name << ".\n";
        }
        else
        {
            cout << current->name << ",";
        }
        first_time = false;
    }
}

char findbackup(char name)
{
    Employee *current = manager;
    if (current == NULL)
    {
        return '\0';
    }
    if (current->name == name)
    {
        return current->backups->name;
    }
    else
    {
        current = current->backups;
        while (current != manager)
        {
            if (current->name == name)
            {
                return current->backups->name;
            }
            current = current->backups;
        }
    }
    return '\0';
}

char getMangerName()
{
    return manager->name;
}

int main()
{
    srand(time(0));

    generate_backup_plan();
    cout << "Backup Plan: \n";
    cout << "Manager: " << getMangerName() << endl;

    display();

    char input;

    do
    {
        cout << "backu search for:";
        cin >> input;

        if (input != '-')
        {
            if (searchEmployee(input))
            {
                char backup = findbackup(input);
                cout << "Backup for " << input << " is " << backup << ".\n";
            }
            else
            {
                cout << "Employee not found" << input << ".\n";
            }
        }

        else
        {
            cout << "Goodbye!\n";
        }

    } while (input != '-');
    return 0;
}