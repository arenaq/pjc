/* 
 * File:   DomaciUkol1.cpp
 * Author: Petr Kuška
 *
 * Created on 11. listopadu 2015, 10:06
 */

#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

int main() {
    map<char, int> priorities;
    priorities['+'] = 2;
    priorities['-'] = 2;
    priorities['*'] = 3;
    priorities['/'] = 3;
    priorities['%'] = 3;
    priorities['~'] = 4;

    string s;
    getline(cin, s);

    string in;
    for (int i = 0; i < s.length(); i++) {
        if (s.at(i) != ' ') in += s.at(i);
    }

    string postfix = "";
    vector<char> stack;

    int i = 0;
    bool space = false;
    while (i < in.length()) {
        char c = in.at(i);
        if (isdigit(c)) {
            // CISLA
            postfix += c;
            space = true;
        } else {
            // OPERATORY
            switch (c) {
                case '(':
                    stack.push_back(c);
                    break;
                case ')':
                {
                    char o = stack.back();
                    stack.pop_back();
                    while (o != '(') {
                        if (space) {
                            postfix += ' ';
                            space = false;
                        }
                        postfix += o;
                        postfix += ' ';
                        o = stack.back();
                        stack.pop_back();
                    }
                    space = false;
                }
                    break;
                default:
                {
                    if (priorities[c] <= 0) break;
                    if (space) {
                        postfix += ' ';
                        space = false;
                    }
                    if (c == '-' and (i == 0 or (!isdigit(in.at(i - 1))) && in.at(i - 1) != ')')) c = '~';
                    while (!stack.empty()) {
                        char o = stack.back();
                        if (o != '(') {
                            if (priorities[c] <= priorities[o]) {
                                postfix += o;
                                postfix += ' ';
                                stack.pop_back();
                            } else {
                                break;
                            }
                        } else {
                            break;
                        }
                    }
                    stack.push_back(c);
                    break;
                }
            }
        }
        i++;
    }
    if (space) {
        postfix += ' ';
        space = false;
    }
    while (!stack.empty()) {
        char o = stack.back();
        if (o != '(') {
            postfix += o;
            postfix += ' ';
        }
        stack.pop_back();
    }

    cout << postfix << "=";

    // vypocet vysledku
    vector<int> result;
    int n = 0;
    i = 0;
    bool interrupted = true;
    while (i < postfix.length()) {
        char c = postfix.at(i++);
        if (isdigit(c)) {
            // CISLA
            if (interrupted) {
                n = c - '0';
                interrupted = false;
            } else {
                n = n * 10 + (c - '0');
            }
        } else {
            // OPERATORY
            if (!interrupted) result.push_back(n);
            interrupted = true;
            if (c == ' ') continue;

            int y = result.back();
            result.pop_back();
            int x = result.back();
            result.pop_back();
            switch (c) {
                case '+':
                    result.push_back(x + y);
                    break;
                case '-':
                    result.push_back(x - y);
                    break;
                case '*':
                    result.push_back(x * y);
                    break;
                case '/':
                    if (y == 0) {
                        cout << " Error. Division by zero." << endl;
                        return 1;
                    }
                    result.push_back(x / y);
                    break;
                case '%':
                    result.push_back(x % y);
                    break;
                case '~':
                    result.push_back(x);
                    result.push_back(-y);
                    break;
                default:
                    break;
            }
        }
    }

    if (result.size() == 1) {
        cout << " " << result.back() << endl;
        result.clear();
    } else {
        cout << " Error. Incorrect input." << endl;
        return 1;
    }

    return 0;
}
