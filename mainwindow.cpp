#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "linklist.h"
#include <qlabel.h>

void preserveCap(int &caps, char word[], int &letter);
void preservePunct(int &i, int &puncTest, char &punct, char word[]);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Allows text editor field to fill and resize to window
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    //Instantiate blank file name
    filename = "";

    //Empty file for new use
    ui->textEdit->setPlainText("");

}

void MainWindow::on_actionOpen_triggered()
{
    //Create dialog box for opening files
    QString openFile = QFileDialog::getOpenFileName(this,"Open a file");

    //Check that the file is populated
    if(!openFile.isEmpty())
    {
        QFile activeFile(openFile);

        //Verify that the file can be opened
        if(activeFile.open(QFile::ReadOnly | QFile::Text))
        {
            filename = openFile;

            //Create file stream to read in
            QTextStream fin (&activeFile);
            QString text = fin.readAll();
            activeFile.close();

            //Display the file input within the UI
            ui->textEdit->setPlainText(text);
        }
    }
}

void MainWindow::on_actionSave_triggered()
{
    if(filename == "")
    {
        on_actionSave_As_triggered();
    }

    else
    {
        QFile saveFile(filename);
        if(saveFile.open(QFile::WriteOnly | QFile::Text))
        {
            QTextStream fout(&saveFile);

            fout << ui->textEdit->toPlainText();

            saveFile.flush();
            saveFile.close();
        }
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    QString file = QFileDialog::getSaveFileName(this, "Save file as...");

    if(!file.isEmpty())
    {
        filename = file;
        on_actionSave_triggered();
    }
}

void MainWindow::on_actionCopy_triggered()
{
    //Add built in copy functionality
    ui->textEdit->copy();
}

void MainWindow::on_actionCut_triggered()
{
    //Add built in cut functionality
    ui->textEdit->cut();
}

void MainWindow::on_actionPaste_triggered()
{
    //Add built in paste functionality
    ui->textEdit->paste();
}

void MainWindow::on_actionRedo_triggered()
{
    //Add built in undo functionality
    ui->textEdit->redo();
}

void MainWindow::on_actionUndo_triggered()
{
    //Add built in undo functionality
    ui->textEdit->undo();
}

void MainWindow::on_actionSpell_Check_triggered()
{
    //Bring our dictionary with us
    extern LinkList dictionary;
    QString incorrect[500];
    int wrong = 0;
    const int MAX_LEN = 40;

    //Safety check for filename
    if (filename == "")
    {
        QLabel *errorMessage = new QLabel;
        errorMessage->setMargin(20);
        errorMessage->setText("\nERROR: File must be saved first!\n");
        errorMessage->show();
    }
    else
       {
        //Open current file to create stream
        QFile file(filename);

        if(file.open(QFile::ReadOnly| QFile::Text))
        {
            //After verifying file is open, create text stream
            QTextStream check(&file);

            char word[MAX_LEN];

            //Loop while reading in from file stops at each white space and increments
            while(!check.atEnd())
            {
                //Variables used for preservation of words
                int caps = 0, letter = 0, puncTest = 0, i = 0;
                char punct = '\0';

                //Grab next word
                check >> word;

                preserveCap(caps, word, letter);
                preservePunct(i, puncTest, punct, word);

                if(dictionary.find(word) == false)
                {
                    //Add to list
                    incorrect[wrong] = word;
                    ++wrong;
                }
            }

            if(wrong == 0)
            {
                incorrect[wrong] = "None!";
            }

            //Label used for output of count results
            QLabel *spellLabel = new QLabel;
            spellLabel->setMargin(20);
            spellLabel->setText("Spell check complete.\nIncorrect words: \n\t");
            for(int i = 0; i <= wrong; ++i)
            {
                spellLabel->setText(spellLabel->text() + incorrect[i] + "\n\t");
            }
            spellLabel->show();

            //Make sure to close your file stream
            file.close();
        }
    }

}

void MainWindow::on_actionWord_Count_triggered()
{
    //Safety check for filename
    if (filename == "")
    {
        QLabel *errorMessage = new QLabel;
        errorMessage->setMargin(20);
        errorMessage->setText("\nERROR: File must be saved first!\n");
        errorMessage->show();
    }
    else
       {
        //Open current file to create stream
        QFile file(filename);

        if(file.open(QFile::ReadOnly | QFile::Text))
        {
            //After verifying file is open, create text stream
            QTextStream check(&file);
            QString word;
            int count = 0;

            //Loop while reading in from file stops at each white space and increments
            while(!check.atEnd())
            {
                check >> word;
                ++count;
            }

            //Label used for output of count results
            QLabel *wordCount = new QLabel;
            wordCount->setMargin(20);
            wordCount->setText("\nTotal number of words: " + QString::number(count) + "\n");
            wordCount->show();

            //Make sure to close your file stream
            file.close();
        }
    }
}

void MainWindow::on_actionCharacter_Count_triggered()
{
    //Safety check for filename
    if (filename == "")
    {
        QLabel *errorMessage = new QLabel;
        errorMessage->setMargin(20);
        errorMessage->setText("\nERROR: File must be saved first!\n");
        errorMessage->show();
    }
    else
       {
        //Open current file to create stream
        QFile file(filename);

        if(file.open(QFile::ReadOnly | QFile::Text))
        {
            //After verifying file is open, create text stream
            QTextStream check(&file);
            QString word;
            int count = 0;

            //Loop while reading in from file stops at each white space and sums characters
            while(!check.atEnd())
            {
                check >> word;
                count += word.length();
            }

            //Label used for output of count results
            QLabel *charCount = new QLabel;
            charCount->setMargin(20);
            charCount->setText("\nTotal number of characters (without whitespace): " + QString::number(count) + "\n");
            charCount->show();

            //Make sure to close your file stream
            file.close();
        }
    }
}

void MainWindow::on_actionAbout_triggered()
{
    QLabel *about = new QLabel;
    about->setText("Word processor created by Matthew Babb for \n"
                   "Intro to Software Engineering (CIS-320 IWU).\n"
                   "Produced using Qt Creator Community 4.5.0\n\n"
                   "Icons designed by Freepik from Flaticon.\n\n"
                   "Code will be available on Github \n"
                   "at github.com/MattBabb/WordProcessor");
    about->setMargin(20);
    about->show();
}


void preserveCap(int &caps, char word[], int &letter)
{
    caps = isupper(word[0]);
        if(caps != 0)
        //if caps is flagged as a capital letter

        {

            letter = tolower(word[0]);
            word[0] = letter;
        }
        //preserves capitalization
}

void preservePunct(int &i, int &puncTest, char &punct, char word[])
{
    while(word[i])
    //finds end of word
    {
        i++;
    }
    i--;


    puncTest = ispunct(word[i]);
    if( puncTest != 0)
    //if puncTest is flagged as having capitalization

    {
        punct = word[i];
        word[i] = '\0';
        i--;
    }
        //preserving punctuation
}
