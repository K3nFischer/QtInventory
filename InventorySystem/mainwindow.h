#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QTableView>
#include <QSql>
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
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_searchButton_released();

    void on_clearButton_released();

    void on_actionSave_triggered();

    void on_searchBox_returnPressed();

    void on_insertButton_released();

    void on_deleteButton_released();

private:
    Ui::MainWindow *ui;
    QString currentFile = "";
    QSqlDatabase mydb;
    QSqlQueryModel *model;
};
#endif // MAINWINDOW_H
