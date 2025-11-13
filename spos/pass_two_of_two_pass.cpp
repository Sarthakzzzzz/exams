#include <bits/stdc++.h>
using namespace std;

// Structure to hold symbol and literal information
struct Symbol { string symbol; int address; };
struct Literal { string literal; int address; };

int main() {
    // Sample symbol and literal tables from Pass-I
    vector<Symbol> symtab = {{"A", 103}, {"B", 104}};
    vector<Literal> littab = {{"='5'", 105}};

    // Sample Intermediate Code from Pass-I
    vector<string> ic = {
        "(AD,01) (C,100)",
        "(IS,04) (1) (S,1)",
        "(IS,01) (2) (L,1)",
        "(IS,05) (1) (S,2)",
        "(DL,01) (C,1)",
        "(DL,01) (C,1)",
        "(AD,02)"
    };

    cout << "\n--- PASS-II OUTPUT (Machine Code) ---\n";
    for (string line : ic) {
        if (line.find("AD") != string::npos) continue; // assembler directives ignored

        stringstream ss(line);
        string part;
        vector<string> tokens;

        while (ss >> part) tokens.push_back(part);

        string opcode = tokens[0];
        opcode = opcode.substr(opcode.find(',') + 1, 2); // e.g., IS,04 → 04

        cout << opcode << "\t";

        for (int i = 1; i < tokens.size(); i++) {
            string tok = tokens[i];

            if (tok.find("(S,") != string::npos) {
                int idx = stoi(tok.substr(3, tok.size() - 4)) - 1;
                cout << symtab[idx].address << "\t";
            }
            else if (tok.find("(L,") != string::npos) {
                int idx = stoi(tok.substr(3, tok.size() - 4)) - 1;
                cout << littab[idx].address << "\t";
            }
            else if (tok.find("(C,") != string::npos) {
                string val = tok.substr(3, tok.size() - 4);
                cout << val << "\t";
            }
            else {
                cout << tok << "\t";
            }
        }
        cout << endl;
    }
    return 0;
}
