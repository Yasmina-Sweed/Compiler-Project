#include <iostream>
#include <vector>
#include <cctype>

bool parseExpression(std::vector<char>& input, size_t& index);
bool parseTerm(std::vector<char>& input, size_t& index);
bool parseFactor(std::vector<char>& input, size_t& index);
bool parseNumber(std::vector<char>& input, size_t& index);

int main() {
    std::string userInput;
    std::cout << "Enter an arithmetic expression: ";
    std::getline(std::cin, userInput);

    std::vector<char> input;
    for (char c : userInput) {
        if (!std::isspace(c)) {
            input.push_back(c);
        }
    }

    size_t index = 0;

    if (parseExpression(input, index) && index == input.size()) {
        std::cout << "Syntax is correct." << std::endl;
    } else {
        std::cout << "Syntax error detected." << std::endl;
    }

    return 0;
}

bool parseExpression(std::vector<char>& input, size_t& index) {
    if (parseTerm(input, index)) {
        while (index < input.size() && (input[index] == '+' || input[index] == '-')) {
            char op = input[index];
            index++;
            if (!parseTerm(input, index)) {
                std::cout << "Syntax error: Expected term after operator" << std::endl;
                return false;
            }
            std::cout << "Operator: " << op << std::endl;
        }
        return true;
    }
    return false;
}

bool parseTerm(std::vector<char>& input, size_t& index) {
    if (parseFactor(input, index)) {
        while (index < input.size() && (input[index] == '*' || input[index] == '/')) {
            char op = input[index];
            index++;
            if (!parseFactor(input, index)) {
                std::cout << "Syntax error: Expected factor after operator" << std::endl;
                return false;
            }
            std::cout << "Operator: " << op << std::endl;
        }
        return true;
    }
    return false;
}

bool parseFactor(std::vector<char>& input, size_t& index) {
    if (index < input.size()) {
        if (input[index] == '(') {
            index++;
            if (parseExpression(input, index)) {
                if (index < input.size() && input[index] == ')') {
                    index++;
                    return true;
                } else {
                    std::cout << "Syntax error: Missing closing parenthesis" << std::endl;
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return parseNumber(input, index);
        }
    }
    std::cout << "Syntax error: Expected number or opening parenthesis" << std::endl;
    return false;
}

bool parseNumber(std::vector<char>& input, size_t& index) {
    if (index < input.size() && std::isdigit(input[index])) {
        std::cout << "Number: " << input[index] << std::endl;
        index++;
        return true;
    }
    std::cout << "Syntax error: Expected digit" << std::endl;
    return false;
}
