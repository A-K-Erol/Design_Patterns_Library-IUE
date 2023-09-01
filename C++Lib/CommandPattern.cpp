#include <vector>
#include <iostream>
using namespace std;

//The classes and/or objects participating in this pattern are:
//
//1. Command  (Command)
//		- declares an interface for executing an operation.
//2. ConcreteCommand  (CalculatorCommand)
//		- defines a binding between a Receiver object and an action.
//		- implements Execute by invoking the corresponding operation(s) on Receiver
//3. Client  (Calculator Application)
//		- creates a ConcreteCommand object and sets its receiver.
//4. Invoker  (User)
//		- asks the command to carry out the request
//5. Receiver  (Calculator)
//		- knows how to perform the operations associated with carrying out
//		  a request. Any class may serve as a Receiver.
//
//

//"Command"
class Command{
public:
    virtual void Execute() = 0;
    virtual void UnExecute() = 0;
};

// "Receiver"
class Calculator{
private:
public:
    int current_value;
    Calculator(){
        current_value = 0;
    }
    void Action(char _operator, int operand){
        switch (_operator){
            case '+': current_value += operand; break;
            case '-': current_value -= operand; break;
            case '*': current_value *= operand; break;
            case '/': current_value /= operand; break;
            default: break;
        }
        cout << "Current value: " << current_value <<
        " (following "<< _operator << " " << operand << ")" << endl;
    }
};

// "Concrete Command"
class CalculatorCommand : public Command{
public:
    // Constructor
    CalculatorCommand(Calculator *calculator, char op, int operand){
        _calculator = calculator;
        _operator = op;
        _operand = operand;
    }

    void Execute() final {
        _calculator->Action(_operator, _operand);
    }

    void UnExecute() final {
        _calculator->Action(Undo(_operator), _operand);
    }
private:
    Calculator *_calculator;
    char _operator;
    int _operand;

    //Private helper function to get the inverse operation
    static char Undo(char _operator){
        switch (_operator){
            case '*': return '/';
            case '/': return '*';
            case '+': return '-';
            case '-': return '+';
            default: return ' ';
        }
    }
};

// "Invoker"
class User {
public:
    User() { current = 0; }
    void Redo(int levels) {
        cout << "\n---- Redo " << levels << " levels" << endl;
        // Perform redo operations
        for (int i = 0; i < levels; i++) {
            if (current < _commands.size()) {
                Command *command= _commands.at(current++);
                command->Execute();
            }
        }
    }

    void Undo(int levels) {
        cout << "\n---- Undo " << levels << " levels " << endl;
        // Perform undo operations
        for (int i = 0; i < levels; i++) {
            if (current > 0) {
                Command *command = _commands.at(--current);
                command->UnExecute();
            }
        }
    }


    void Compute(Command *command) {
        command->Execute();
        // Add command to undo list
        _commands.push_back(command);
        current++;
    }

    // initializers
private:
    int current;
    vector<Command *> _commands;
};

int main (){
    //Create user and let them compute
    Command *command;

    User *user;
    user = new User();

    Calculator *calculator;
    calculator = new Calculator();

    //series of 4 operations: ((((0 + 100) - 50) * 10) / 2) = 250
    command = new CalculatorCommand(calculator, '+', 100);
    user->Compute(command);
    command = new CalculatorCommand(calculator, '-', 50);
    user->Compute(command);
    command = new CalculatorCommand(calculator, '*', 10);
    user->Compute(command);
    command = new CalculatorCommand(calculator, '/', 2);
    user->Compute(command);


    // Undo 4 commands
    user->Undo(4);
    // Redo 2 commands
    user->Redo(2);
}
