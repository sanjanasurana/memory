#include <iostream>
#include <ctime> ///used to return current time
#include <cstdlib>
#include <chrono> ///used to make use of the sleep command
#include <thread>
#include <fstream>
#include <string>
#include <stdio.h>

using namespace std;

class Node
{
    public:
    char data;
    Node* next;

    Node(char val)
    {
        data = val;
        next = nullptr;
    }
};

class LinkedList
{
    public:
    Node* start;

    LinkedList()
    {
        start = nullptr;
    }

    ///enter the 5 elements entered by the user randomly into 10 spaces of the LL
    void insertRandomly(char data)
    {
        Node* newNode = new Node(data);

        if (start == nullptr)
        {
            start = newNode;
        }
        else
        {
            int listSize = 0;
            Node* temp = start;
            while (temp)
            {
                listSize++;
                temp = temp -> next;
            }

            int randomPosition = rand() % (listSize + 1);
            if (randomPosition == 0)
            {
                newNode -> next = start;
                start = newNode;
            }
            else
            {
                temp = start;
                for (int i = 1; i < randomPosition; i++)
                {
                    temp = temp -> next;
                }
                newNode -> next = temp -> next;
                temp -> next = newNode;
            }
        }
    }

    ///print the values of the list
    void printList()
    {
        Node* temp = start;
        while (temp)
        {
            cout << temp -> data << " ";
            temp = temp -> next;
        }
    }

    ///deconstructor used to release all the resources help by the class
    ~LinkedList()
    {
        while (start)
        {
            Node* temp1 = start;
            start = start -> next;
            delete temp1;
        }
    }

    ///count and return the no.of nodes present in the list
    int count_nodes()
    {
        Node* temp = start;
        int count = 0;
        while(temp != NULL)
        {
            count++;
            temp = temp -> next;
        }
        return count;
    }

    ///delete the guessed letters from the LL
    void deletePosition(int position)
    {
       if (position == 0) //for first node
       {
           Node* temp = start;
           start = start -> next;
           delete temp;
       }
       else //for all the other nodes
       {
           int count = 0;
           Node* curr = start;

           while (count != position - 1)
           {
               curr = curr -> next;
               count++;
           }

           Node* actualNode = curr -> next;
           curr -> next = actualNode -> next;
           delete actualNode;
       }
    }

    ///get what data has been stored in the node at the position entered by the user
    char getnodedata(int pos)
    {
        Node* temp = start;
        int count=0;
        while(temp != NULL)
        {
            if(count == pos)
            {
                return temp -> data;
            }
            else
            {
                temp = temp -> next;
                count++;
            }
        }
    }
};

int main()
{
    srand(static_cast<unsigned>(time(0))); ///random non negative number generator according to the current time
    LinkedList linkedlist; ///object of the LinkedList class
    char characters[5];

    cout << "Enter the 5 characters u want to make a part of the memory game "<<endl;
    for (int i = 0; i < 5; i++)
    {
        cin >> characters[i];
    }

    for (int i = 0; i < 5; i++)
    {
        linkedlist.insertRandomly(characters[i]); ///put the number at 2 random spaces in the linked list
        linkedlist.insertRandomly(characters[i]);
    }

    cout<<"Your will now be shown the randomly generated sequence for a short amount of time"<<endl;
    linkedlist.printList();                                 //print the randomized LL
    cout << endl;

    this_thread::sleep_for(chrono::seconds(5));  ///shows the above output constantly for 5 seconds
    system("CLS");  //clear the screen after showing output for 5 seconds

    int pos1,pos2;
    char alphabet1,alphabet2;
    int flag=5;
    int no_of_asterisks;
    while (flag != 0)
    {
        no_of_asterisks = linkedlist.count_nodes();
        for(int i=0;i<no_of_asterisks;i++)
        {
            cout<<"* ";
        }
        cout<<endl;
        cout<<"Enter the 2 positions of which the character matches"<<endl;
        cin>>pos1>>pos2;
        if(pos1 >= 1 && pos1 <= 10 && pos2 >= 1 && pos2 <= 10) //to check if alphabets are present within the given range
        {
            alphabet1 = linkedlist.getnodedata(pos1-1);
            alphabet2 = linkedlist.getnodedata(pos2-1);
            if(alphabet1 == alphabet2)
            {
                flag--;
                cout<<flag<<endl;
                cout<<"The alphabets at the two positions entered match"<<endl;
                linkedlist.deletePosition(pos1-1);

                ///if condition needed cause if pos2 was bigger then the index of pos2 would change as pos1 is deleted first
                if (pos1 - 1 < pos2 - 1)
                {
                    linkedlist.deletePosition(pos2 - 2);
                } else
                {
                    linkedlist.deletePosition(pos2 - 1);
                }
            }
            else
            {
                cout<<"The alphabets at the 2 positions entered do not match"<<endl;
            }
        }
        else
        {
            cout<<"Entered positions are not valid as the positions should be between 1 and 10"<<endl;
        }
    }

    cout << endl << "CONGRATULATIONS !!! YOU WON THE GAME !!!" << endl;
    return 0;
}
