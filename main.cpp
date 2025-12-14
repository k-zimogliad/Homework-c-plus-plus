#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <sstream>

using namespace std;

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");
    
    string line; 
    
    while (getline(input, line)) {

        stack<double> numbers;
        stringstream ss(line);
        string token;  
        bool error = false;  
        
        while (ss >> token && !error) {
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                if (numbers.size() < 2) {
                    output << line << " = ERROR" << endl;
                    error = true;
                    break; 
                }
                
                double b = numbers.top();  
                numbers.pop();             
                double a = numbers.top();  
                numbers.pop();             
                
                
                if (token == "+") numbers.push(a + b);     
                else if (token == "-") numbers.push(a - b); 
                else if (token == "*") numbers.push(a * b); 
                else if (token == "/") {                    
            
                    if (b == 0) {
                        output << line << " = ERROR" << endl;
                        error = true;
                        break;  
                    }
                    numbers.push(a / b);
                }
            } else {
                numbers.push(stod(token));
            }
        }
        
        if (!error && numbers.size() == 1) {
            output << line << " = " << numbers.top() << endl;
        } else if (!error) {
            output << line << " = ERROR" << endl;
        }
    }
    
    input.close();
    output.close();
    return 0;  
}
