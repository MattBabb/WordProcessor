#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//Includes added by Matthew
#include <QtCore>
#include <QtGui>
#include <QFileDialog>
#include "linklist.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();

    void on_actionWord_Count_triggered();

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_As_triggered();

    void on_actionCopy_triggered();

    void on_actionCut_triggered();

    void on_actionPaste_triggered();

    void on_actionRedo_triggered();

    void on_actionUndo_triggered();

    void on_actionSpell_Check_triggered();

    void on_actionAbout_triggered();

    void on_actionCharacter_Count_triggered();

private:
    Ui::MainWindow *ui;

    //'filename' string added by Matthew
    QString filename;
};

#endif // MAINWINDOW_H
