#include <iostream>
#include <cstring>

class Node
{
public:
    char data;
    Node *next;

    Node(char val) : data(val), next(nullptr) {}
};

class Stack
{
private:
    Node *top;

public:
    Stack() : top(nullptr) {}

    bool isEmpty()
    {
        return top == nullptr;
    }

    void push(char val)
    {
        Node *newNode = new Node(val);
        newNode->next = top;
        top = newNode;
    }

    char pop()
    {
        if (!isEmpty())
        {
            char val = top->data;
            Node *temp = top;
            top = top->next;
            delete temp;
            return val;
        }
        else
        {
            return '\0';
        }
    }

    char peek()
    {
        return (top != nullptr) ? top->data : '\0';
    }
};

bool areParenthesesMatched(const char *expression)
{
    Stack stack;

    for (int i = 0; i < strlen(expression); ++i)
    {
        if (expression[i] == '(')
        {
            stack.push(expression[i]);
        }
        else if (expression[i] == ')')
        {
            if (stack.isEmpty() || stack.pop() != '(')
            {
                return false;
            }
        }
    }

    return stack.isEmpty();
}

int main()
{
    while (true)
    {
        char expression[50];
        std::cout << "Enter an expression: ";
        std::cin.getline(expression, sizeof(expression));

        if (strcmp(expression, "exit") == 0)
        {
            std::cout << "Bye" << std::endl;
            break;
        }

        bool result = areParenthesesMatched(expression);

        if (result)
        {
            std::cout << "True" << std::endl;
        }
        else
        {
            std::cout << "False" << std::endl;
        }
    }

    return 0;
}
