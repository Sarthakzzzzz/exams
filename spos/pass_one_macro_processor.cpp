#include <bits/stdc++.h>
using namespace std;

struct MNTEntry { string name; int mdtIndex; };
struct MDTEntry { string line; };
struct ALAEntry { vector<string> args; };

int main() {
    vector<MNTEntry> MNT;
    vector<MDTEntry> MDT;
    ALAEntry ALA;

    vector<string> input = {
        "MACRO",
        "INCR &ARG1,&ARG2",
        "ADD &ARG1,&ARG2",
        "MEND",
        "START",
        "INCR A,B",
        "END"
    };

    bool inMacro = false;
    int mdtp = 0;
    vector<string> intermediate;

    for (string line : input) {
        stringstream ss(line);
        string first; ss >> first;

        if (first == "MACRO") {
            inMacro = true;
            continue;
        }

        if (inMacro) {
            if (line.find("MEND") != string::npos) {
                MDT.push_back({"MEND"});
                inMacro = false;
                continue;
            }

            // Macro header (name + args)
            if (line.find("&") != string::npos) {
                string name, arg;
                ss >> name;
                name = first; // first token is macro name
                string rest; getline(ss, rest);

                // Extract args
                int start = line.find(' ');
                string args = line.substr(start + 1);
                stringstream s2(args);
                string temp;
                while (getline(s2, temp, ',')) ALA.args.push_back(temp);

                MNT.push_back({name, (int)MDT.size()});
                MDT.push_back({line});
            } else MDT.push_back({line});
        }
        else intermediate.push_back(line);
    }

    cout << "\n--- PASS-I OUTPUT ---\n";

    cout << "\nMNT (Macro Name Table)\n----------------------\n";
    for (auto &m : MNT)
        cout << m.name << "\t" << m.mdtIndex << "\n";

    cout << "\nMDT (Macro Definition Table)\n----------------------------\n";
    for (int i = 0; i < MDT.size(); i++)
        cout << i << "\t" << MDT[i].line << "\n";

    cout << "\nALA (Argument List Array)\n-------------------------\n";
    for (int i = 0; i < ALA.args.size(); i++)
        cout << i + 1 << "\t" << ALA.args[i] << "\n";

    cout << "\nIntermediate Code (without macros)\n----------------------------------\n";
    for (auto &l : intermediate)
        cout << l << "\n";

    return 0;
}
