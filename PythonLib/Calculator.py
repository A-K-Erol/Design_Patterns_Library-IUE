import abc
#
# The classes and/or objects participating in this pattern are:
#
# 1. Command (Command)
#   - declares interface for executing operation
# 2. ConcreteCommand (CalculatorCommand)
#   - defines a binding between a receiver object and an action
#   - implements Execute by invoking the corresponding operations on receiver
# 3. Client (CalculatorApp)
#   - creates a ConcreteCommand object and sets its receiver
# 4. Invoker (User)
#   - asks the command to carry out the request
# 5. Receiver (Calculator)
#   - knows how to preform the operations associated with the request


# "Command" interface
class Command:
    @abc.abstractmethod
    def execute(self):
        pass

    @abc.abstractmethod
    def un_execute(self):
        pass


# 'Receiver'
class Calculator:
    def __init__(self):
        self.current_value = 0

    def action(self, _operator, operand):
        if _operator == '+':
            self.current_value += operand

        elif _operator == '-':
            self.current_value -= operand

        elif _operator == '*':
            self.current_value *= operand

        elif _operator == '/':
            self.current_value /= operand

        print("Current value " + str(self.current_value) + " (following " + _operator + " " + str(operand) + ")")
        return


# 'ConcreteCommand'
class CalculatorCommand(Command):
    # Constructor
    def __init__(self, calculator, op, operand):
        self._calculator = calculator
        self._operator = op
        self._operand = operand

    def execute(self):
        self._calculator.action(self._operator, self._operand)

    def un_execute(self):
        self._calculator.action(self.__inverse(self._operator), self._operand)

    # Private Helper function to get inverse
    def __inverse(self, _operator):
        if _operator == '+':
            return '-'

        elif _operator == '-':
            return '+'

        elif _operator == '*':
            return '/'

        elif _operator == '/':
            return '*'

        else:
            return ' '


# "Invoker"
class User:
    def __init__(self):
        self.__current = 0
        self.__commands = []

    def redo(self, levels):
        print("\n---- Redo " + str(levels) + " levels ")
        # perform redo operations
        for i in range(levels):
            if self.__current < len(self.__commands):
                command = self.__commands[self.__current]
                self.__current += 1
                command.execute()

    def undo(self, levels):
        print("\n---- Undo " + str(levels) + " levels ")
        # perform undo operations
        for i in range(levels):
            if self.__current > 0:
                command = self.__commands[self.__current - 1]
                self.__current -= 1
                command.un_execute()

    def compute(self, command):
        command.execute()
        # add command to undo list
        self.__commands.append(command)
        self.__current += 1


def command_pattern():
    # Create user and let her compute
    user = User()
    calculator = Calculator()

    command = CalculatorCommand(calculator, '+', 100)
    user.compute(command)
    command = CalculatorCommand(calculator, '-', 50)
    user.compute(command)
    command = CalculatorCommand(calculator, '*', 10)
    user.compute(command)
    command = CalculatorCommand(calculator, '/', 2)
    user.compute(command)

    # Undo 4 commands
    user.undo(4)
    # Redo 2 commands
    user.redo(2)


if __name__ == "__main__":
    command_pattern()
