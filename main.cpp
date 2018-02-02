#include "mainwindow.h"
#include <QApplication>
#include "linklist.h"

//Linked list added by Matthew
LinkList dictionary;

bool openDictionary(LinkList &dictionary);

int main(int argc, char *argv[])
{
    //Load dictionary for spell check at program launch
    openDictionary(dictionary);


    QApplication a(argc, argv);
    MainWindow w;
    w.show();



    return a.exec();
}


bool openDictionary(LinkList &dictionary)
{
    ifstream fin;
    string word;

    //opens the dictionary input stream
    fin.open("dictionary.txt");

    if(!fin)
    {

        //checks for input from dictionary file
        cout << "Error Loading Dictionary" << endl;
        return false;
    }

    while(fin >> word)
    {

        //while there is valid input, insert into linked list
        dictionary.insert(word);
    }

    fin.close();
    //close input stream

    return true;

}

