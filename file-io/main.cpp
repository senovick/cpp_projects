#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream iFile;
    ofstream oFile;
    string line;
    // Open the file
    iFile.open("input.txt");
    if(!iFile.is_open())
    {
        cout << "Error opening input file!\n";
        return 1;
    }

    // Open the output file
    oFile.open("output.txt");
    if(!oFile.is_open())
    {
        cout << "Error opening output file\n";
    }

    while(getline(iFile, line))
    {
        oFile << line << endl;
    }

    iFile.close();
    oFile.close();
    
    return 0;
}