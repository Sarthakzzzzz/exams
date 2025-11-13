#include <bits/stdc++.h>
using namespace std;

struct MOT {
	string mnemonic;
	string opcode;
	int length;
};


struct Symbol {
    string label;
    int address;
};

struct Intermediate {
    int lc;
    string opcode;
    string operand;
};

int main() {
    vector<MOT> mot = {
        {"MOVER", "04", 1}, {"MOVEM", "05", 1},
        {"ADD", "01", 1}, {"SUB", "02", 1}
    };

    vector<Symbol> symtab;
    vector<Intermediate> ic;

    vector<vector<string>> lines = {
        {"-", "START", "100"},
        {"-", "MOVER", "AREG,A"},
        {"-", "ADD", "BREG,='5'"},
        {"-", "MOVEM", "AREG,B"},
        {"A", "DS", "1"},
        {"B", "DS", "1"},
        {"-", "END", "-"}
    };

    int lc = 0;
    for (auto &tokens : lines) {
        string label = tokens[0], opcode = tokens[1], operand = tokens[2];
        if (opcode == "START") {
            lc = stoi(operand);
            ic.push_back({lc, "AD,01", operand});
        } 
        else if (opcode == "END") {
            ic.push_back({lc, "AD,02", ""});
            break;
        }
        else {
            if (label != "-") symtab.push_back({label, lc});

            auto it = find_if(mot.begin(), mot.end(), [&](MOT m){return m.mnemonic == opcode;});
            if (it != mot.end()) {
                ic.push_back({lc, "IS," + it->opcode, operand});
                lc += it->length;
            }
            else if (opcode == "DS" || opcode == "DC") {
                ic.push_back({lc, "DL," + string(opcode=="DS"?"01":"02"), operand});
                lc++;
            }
        }
    }

    cout << "\nSymbol Table:\n";
    cout << "----------------\n";
    cout << "Symbol\tAddress\n";
    for (auto &s : symtab)
        cout << s.label << "\t" << s.address << "\n";

    cout << "\nIntermediate Code:\n";
    cout << "-------------------\n";
    cout << "LC\tOpcode\tOperand\n";
    for (auto &i : ic)
        cout << i.lc << "\t" << i.opcode << "\t" << i.operand << "\n";
} 
