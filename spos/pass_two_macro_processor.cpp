#include <bits/stdc++.h>
using namespace std;

struct MNTEntry { string name; int mdtIndex; };
struct MDTEntry { string line; };
struct ALAEntry { vector<string> args; };

int main() {
    // Pretend these come from Pass-I output
    vector<MNTEntry> MNT = {{"INCR", 0}};
    vector<MDTEntry> MDT = {
        {"INCR &ARG1,&ARG2"},
        {"ADD &ARG1,&ARG2"},
        {"MEND"}
    };
    ALAEntry ALA = {{"&ARG1","&ARG2"}};

    vector<string> intermediate = {
        "START",
        "INCR A,B",
        "END"
    };

    cout << "\n--- PASS-II OUTPUT (Expanded Code) ---\n";

    for (string line : intermediate) {
        stringstream ss(line);
        string mnemonic; ss >> mnemonic;

        bool isMacro = false;
        for (auto &m : MNT)
            if (mnemonic == m.name) {
                isMacro = true;
                string argsStr; getline(ss, argsStr);
                argsStr.erase(remove(argsStr.begin(), argsStr.end(), ' '), argsStr.end());

                vector<string> actualArgs;
                string temp;
                stringstream s2(argsStr);
                while (getline(s2, temp, ',')) actualArgs.push_back(temp);

                // Expand macro body
                for (int i = m.mdtIndex + 1; MDT[i].line != "MEND"; i++) {
                    string expanded = MDT[i].line;
                    for (int j = 0; j < ALA.args.size(); j++) {
                        size_t pos;
                        while ((pos = expanded.find(ALA.args[j])) != string::npos)
                            expanded.replace(pos, ALA.args[j].length(), actualArgs[j]);
                    }
                    cout << expanded << endl;
                }
                break;
            }

        if (!isMacro)
            cout << line << endl;
    }
    return 0;
}
