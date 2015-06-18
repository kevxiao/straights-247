#include <iostream>
#include <vector>
#include "Controllers/DeckController.h"
#include "Models/DeckModel.h"
#include "Models/Card.h"

using namespace std;

int main(int argc, char* argv[])
{
    string firstArg = "";
    if(argc > 1)
    {
        firstArg = string(argv[1]);
    }
    cout<<firstArg<<endl;
    DeckController deckController;
    vector<Card *> deck = deckController.getCards();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 13; ++j) {
            cout << *deck[13 * i + j] << " ";
        }
        cout << endl;
    }
    deckController.shuffle(44);
    deck = deckController.getCards();
    cout << "shuffled:" << endl;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 13; ++j) {
            cout << *deck[13 * i + j] << " ";
        }
        cout << endl;
    }
    return 0;
}
