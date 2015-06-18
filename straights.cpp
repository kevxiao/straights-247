#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    string firstArg = "";
    if(argc > 1)
    {
        firstArg = string(argv[1]);
    }
    cout<<"Done"<<endl;
    return 0;
}
