#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

struct CodeToken {
    int value;
    string token1;
    string token2;
    string function_name;
};

vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int write_file(string data) {
    ofstream file("run.cpp");
    if (file.is_open()) {
        file << data;
        file.close();
    } else {
        cerr << "unable to open file";
        return 1;
    }
    return 0;
}

int process(vector<string> content) {
    CodeToken Code;
    for (string token : content) {
        if (Code.value == 1) {
            if (Code.token1 == "function") {
                Code.function_name = token;
                Code.value = 2;
                string data = "int " + Code.function_name + "(void) {";
                cout << data;
                write_file(data);
            }
        }
        if (Code.value == 0) {
            if (token == "func") {
                Code.token1 == "function";
                Code.value = 1;
            }
        }
    }
    return 0;
}

int main() {
    write_file("#include <iostream>\n#include <string>\n#include <vector>\n#include <sstream>\n#include <fstream>\nusing namespace std;\n");
    ifstream file("test.txt");
    CodeToken Code;
    Code.value = 0;
    string content, line;
    if (file.is_open()) {
        while (getline(file, line)) {
            content += line;
        }
    } else {
        cerr << "file not found";
        return 0;
    }
    vector<string> data = split(content, ' ');
    process(data);
}
