#ifndef ALGO_CALCULATOR_H
#define ALGO_CALCULATOR_H

#include <string>
#include <queue>
#include <stack>
#include <unordered_map>

typedef long long ll;
using std::string, std::queue, std::stack, std::to_string, std::unordered_map;

ll reverse_polish_notation(queue<string> q) {
    stack<ll> s;
    while (q.size() > 1 || !s.empty()) {
        if (q.front().size() > 1 || isdigit(q.front()[0])) {
            s.push(stoll(q.front()));
            q.pop();
        } else {
            ll x, y;
            x = s.top();
            s.pop();
            y = s.top();
            s.pop();
            switch (q.front()[0]) {
                case '+':
                    q.front() = to_string(x + y);
                    break;
                case '*':
                    q.front() = to_string(x * y);
                    break;
                case '-':
                    q.front() = to_string(x - y);
                    break;
                case '/':
                    q.front() = to_string(x / y);
                    break;
            }
        }
    }
    return stoll(q.front());
}

ll reverse_polish_notation(const string &s) {
    queue<string> q;
    ll cn = 0;
    for (ll i = 0; i < s.size(); i++) {
        char x = s[i];
        if (x == ' ') continue;
        if (isdigit(x)) {
            cn *= 10;
            cn += x - '0';
            if (i + 1 < s.size() && isdigit(s[i + 1])) continue;
            q.push(to_string(cn));
            cn = 0;
        } else {
            string st;
            st = x;
            q.push(st);
        }
    }
    return reverse_polish_notation(q);
}

ll shunting_yard(const string &expr, const unordered_map<char, int> &precedence = {
        {'+', 0},
        {'-', 0},
        {'*', 1},
        {'/', 1},
}) {
    ll cn = 0;
    queue<string> output_queue;
    stack<char> op_stack;
    for (ll i = 0; i < expr.size(); i++) {
        char c = expr[i];
        if (c == ' ') continue;
        if (isdigit(c)) {
            cn *= 10;
            cn += c - '0';
            if (i + 1 < expr.size() && isdigit(expr[i + 1])) continue;
            else {
                output_queue.push(to_string(cn));
                cn = 0;
            }
        } else if (precedence.find(c) != precedence.end()) {
            while (!op_stack.empty()
                   && op_stack.top() != '('
                   && (precedence.find(op_stack.top())->second > precedence.find(c)->second
                       || (true && precedence.find(op_stack.top())->second ==
                                   precedence.find(c)->second)) // true is left associative, change this if use of exp
                    ) {
                string s;
                s = op_stack.top();
                op_stack.pop();
                output_queue.push(s);
            }
            op_stack.push(c);
        } else if (c == '(') {
            op_stack.push(c);
        } else if (c == ')') {
            while (op_stack.top() != '(') {
                string s;
                s = op_stack.top();
                op_stack.pop();
                output_queue.push(s);
            }
            if (op_stack.top() == '(') op_stack.pop();
        }
    }
    while (!op_stack.empty()) {
        string s;
        s = op_stack.top();
        op_stack.pop();
        output_queue.push(s);
    }

    return reverse_polish_notation(output_queue);
}


#endif //ALGO_CALCULATOR_H
