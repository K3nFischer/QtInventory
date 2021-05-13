#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "editablesqlmodel.h"
#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QTableView>
#include <QSql>
#include <QtSql>
#include <QSqlQuery>
#include <QSqlQueryModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //opens new file
    void on_actionNew_triggered();
    //opens from file
    void on_actionOpen_triggered();
    //search
    void on_searchButton_released();
    //resets view
    void on_clearButton_released();
    //enter button press for search
    void on_searchBox_returnPressed();
    //inserts item into database
    void on_insertButton_released();
    //deletes item from database
    void on_deleteButton_released();
    //modifies item in database
    void on_modifyButton_released();
    //refreshes view
    void refresh();

private:
    Ui::MainWindow *ui;
    QString currentFile = "";
    QSqlDatabase mydb;
    EditableSqlModel *model;
};
#endif // MAINWINDOW_H
