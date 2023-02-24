#include <iostream>
#include <limits>
#include <time.h>

using namespace std;

class SkipList {
    struct Node {
        Node **NextNodes;
        int counter;
        int packet;

        Node(int packet) {
            this->packet = packet;
            NextNodes = new Node *[10];
            counter = 1;
        }
    };

    int Floor = 0;

    Node *Left = new Node(std::numeric_limits<int>::min());



public:
    bool searchElement(int data) {  //searching
        Node *pointer = Left;

        for (int i = Floor; i >= 0; i--)
            while (pointer->NextNodes[i] && pointer->NextNodes[i]->packet < data)
                pointer = pointer->NextNodes[i];

        pointer = pointer->NextNodes[0];

        return pointer && pointer->packet == data;
    }


    void deleteElement(int packet) {   //deleting
        Node *previous[10];
        Node *pointer = Left;


        for (auto &previous2 : previous)
            previous2 = nullptr;

        for (int i = 9; i >= 0; i--) {
            while (pointer->NextNodes[i] && pointer->NextNodes[i]->packet < packet)
                pointer = pointer->NextNodes[i];
            previous[i] = pointer;
        }
        pointer = pointer->NextNodes[0];

        if (pointer && pointer->packet == packet) {
            for (int i = 0; i <= Floor && previous[i]->NextNodes[i] == pointer; i++)
                previous[i]->NextNodes[i] = pointer->NextNodes[i];
            delete pointer;

            for (; Floor > 0 && !Left->NextNodes[Floor]; Floor--);
        } else
            cout << "error" << endl;
    }


    void print() {  //printing
        if (!Left->NextNodes[0]) {
            cout << "empty" << endl;
            return;
        }
        for (Node *p = Left->NextNodes[0]; p; p = p->NextNodes[0])
            for (int i = 0; i < p->counter; i++)
                cout << p->packet << " ";
        cout << endl;
    }

    int Rand_Floor() {  //creates random floor for the given node
        for (int i = 0; i < 10; i++)
            if (rand() % 4 != 0)
                return i;
        return 0;
    }

    void ElementAdder(int packet) {    //adds element
        Node *previous[10];
        Node *pointer = Left;

        for (auto &i : previous)
            i = nullptr;

        for (int i = 9; i >= 0; i--) {
            while (pointer->NextNodes[i] && pointer->NextNodes[i]->packet < packet)
                pointer = pointer->NextNodes[i];
            previous[i] = pointer;
        }
        pointer = pointer->NextNodes[0];

        if (!pointer || pointer->packet != packet) {
            int level = Rand_Floor();

            if (this->Floor < level) {
                for (int i = this->Floor + 1; i <= level; i++)
                    previous[i] = Left;
                this->Floor = level;
            }

            Node *AddedNode = new Node(packet);

            for (int i = 0; i <= level; i++) {
                AddedNode->NextNodes[i] = previous[i]->NextNodes[i];
                previous[i]->NextNodes[i] = AddedNode;
            }
        } else if (pointer->packet == packet)
            pointer->counter++;
    }

};

int main() {

    srand(time(NULL));

    SkipList skipList;

    string command;
    int data;
    while (cin >> command) {
        if (command == "Search") {
            cin >> data;
            cout << (skipList.searchElement(data) ? "true" : "false") << endl;
        } else if (command == "Insert") {
            cin >> data;
            skipList.ElementAdder(data);
        } else if (command == "Delete") {
            cin >> data;
            skipList.deleteElement(data);
        } else if (command == "Print") {
            skipList.print();
        }
    }
}
