/*
 * To compile this file, enter the following command in the root directory of the project 
 * (where the Makefile and Readme files both reside):
 * 
 *      g++ src/test/TestSplit.cpp src/main/StringUtils.cpp -I src/main -o bin/TestSplit
 * 
 * This should create the binary TestSplit in the bin folder.
 * 
 * The binary can be run with a command of the form
 * 
 *      bin/TestSplit "<string>" "<delimiters>" <limit>
 * 
 * where <string> and <delimiters> are both strings enclosed in double quotes, and <limit> is an integer.
 * 
 * For example,
 * 
 *      bin/TestSplit "Hello world, hello solar system, hello Milky Way, hello universe." ",. " 12
 * 
 * This will run two test cases.
 * 
 * In the first test case, the limit is ignored.
 * 
 * In the second test case, the string will be split on the delimiters ',' and '.' and ' ', a maximum of 11 times,
 * resulting in a vector that has a maximum size of 12.
 * 
 * The contents of the vector are printed at the end of each test.
 */

#include "StringUtils.h"
#include <iostream>

void run_test(string& str, const string& delimiters)
{
    cout << "==================================================================" << endl;
    cout << "User inputs:" << endl;
    cout << "==================================================================" << endl;
    cout << "String: " << "\"" + str + "\"" << endl;
    cout << "Delimiters: " << "\"" + delimiters + "\"" << endl;
    cout << "==================================================================" << endl;
    cout << "Testing the StringUtils::split(str, delimiters) function..." << endl;
    cout << "==================================================================" << endl;
    vector<string> buffer = StringUtils::split(str, delimiters);
    for (int i = 0; i < buffer.size(); i++)
    {
        cout << i << ": " << buffer[i] << endl;
    }
}

void run_test(string& str, const string& delimiters, int limit)
{
    cout << "==================================================================" << endl;
    cout << "User inputs:" << endl;
    cout << "==================================================================" << endl;
    cout << "String: " << "\"" + str + "\"" << endl;
    cout << "Delimiters: " << "\"" + delimiters + "\"" << endl;
    cout << "Limit: " << limit << endl;
    cout << "==================================================================" << endl;
    cout << "Testing the StringUtils::split(str, delimiters, limit) function..." << endl;
    cout << "==================================================================" << endl;
    vector<string> buffer = StringUtils::split(str, delimiters, limit);
    for (int i = 0; i < buffer.size(); i++)
    {
        cout << i << ": " << buffer[i] << endl;
    }
}

int main(int argc, char **argv)
{
    if (argc < 3 || argc > 4)
    {
        printf("Usage: %s <string> <delimiters> [<limit>]\n", argv[0]);
        return 0;
    }

    string str = string(argv[1]);
    const string delimiters = string(argv[2]);

    if (argc == 3)
    {
        run_test(str, delimiters);
    }
    else
    {
        int limit = atoi(argv[3]);
        run_test(str, delimiters, limit);
    }

    return 0;
}