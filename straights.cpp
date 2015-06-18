#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    string firstArg = "";
    if(argc > 1)
    {
        firstArg = string(argv[1]);
    }
    cout<<firstArg<<endl;
    return 0;
}
