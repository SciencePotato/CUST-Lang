    ifstream inputFile ("testFiles/basictTest.txt");
    string line;
    if (inputFile.is_open()) {
        while (inputFile) {
            getline(inputFile, line);
            cout << line << '\n';
        }
    } 