#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(":memory:");
    model = new QSqlQueryModel();
    mydb.open();
    QSqlQuery query("CREATE TABLE IF NOT EXISTS Inventory (name TEXT, price INTEGER, wholesale INTEGER, manufacturer TEXT, countItem INTEGER, PRIMARY KEY(name))");
    query.exec();
    ui->setupUi(this);

    refresh();
}

MainWindow::~MainWindow()
{
    delete ui;
    mydb.close();

}

//Ben Katin
void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    mydb.close();
    mydb.setDatabaseName(":memory:");
    mydb.open();
    QSqlQuery query("CREATE TABLE IF NOT EXISTS Inventory (name TEXT, price INTEGER, wholesale INTEGER, manufacturer TEXT, countItem INTEGER, PRIMARY KEY(name))");
    query.exec();

    refresh();
}
//Kendall Fischer
void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open File");
    QFile file(filename);
    currentFile = filename;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
    }else{
        mydb.close();
        mydb.setDatabaseName(currentFile);
        mydb.open();

        refresh();
    }
}
//Michael Briones
void MainWindow::on_searchButton_released()
{
    QString input = ui->searchBox->text();
    QSqlQuery query(mydb);
    query.prepare("SELECT name AS Name, price AS Price, wholesale AS Wholesale, manufacturer AS Manufacturer, countItem AS Count FROM Inventory WHERE name LIKE '%'||:name||'%'");
    query.bindValue(":name", input);
    query.exec();

    model->setQuery(query);
    ui->tableView->setModel(model);

}
//Garret Mook
void MainWindow::on_clearButton_released()
{
    ui->searchBox->clear();
    refresh();
}
//Michael Briones
void MainWindow::on_actionSave_triggered()
{

}
//Michael Briones
void MainWindow::on_searchBox_returnPressed()
{
    on_searchButton_released();
}
//Christopher Wong
void MainWindow::on_insertButton_released()
{
    QString name = ui->nameBox->text();
    double price = ui->priceBox->text().toDouble();
    double wholesale = ui->wholesaleBox->text().toDouble();
    QString manufacturer = ui->manufacturerBox->text();
    double count = ui->countBox->text().toDouble();

    QSqlQuery query(mydb);
    query.prepare("INSERT INTO Inventory (name, price, wholesale, manufacturer, countItem) VALUES (:name, :price, :wholesale, :manufacturer, :count)" );
    query.bindValue(":name", name);
    query.bindValue(":price", price);
    query.bindValue(":wholesale", wholesale);
    query.bindValue(":manufacturer", manufacturer);
    query.bindValue(":count", count);
    query.exec();

    refresh();
}

//Garret Mook
void MainWindow::on_deleteButton_released()
{

        QString name = ui->nameBox->text();

        QSqlQuery query(mydb);
        query.prepare("DELETE FROM Inventory WHERE name = :name" );
        query.bindValue(":name", name);
        query.exec();

        refresh();
}
//Christopher Wong
void MainWindow::on_modifyButton_released()
{

        bool priceState, wholesaleState, manufacturerState, countState;
        priceState = wholesaleState = manufacturerState = countState = false;

        QString name = ui->nameBox->text();
        double price = ui->priceBox->text().toDouble();
        double wholesale = ui->wholesaleBox->text().toDouble();
        QString manufacturer = ui->manufacturerBox->text();
        double count = ui->countBox->text().toDouble();

        if(price != 0)
            priceState = true;
        if(wholesale != 0)
            wholesaleState = true;
        if(manufacturer != "")
            manufacturerState = true;
        if(count != 0)
            countState = true;

        //nameState && priceState && wholesaleState && manufacturerState && countState;

        QSqlQuery query(mydb);
        if(priceState){
                query.prepare("UPDATE Inventory SET price = :price WHERE name = :name");
                query.bindValue(":name", name);
                query.bindValue(":price", price);
                query.exec();
            }
            if(wholesaleState){
                query.prepare("UPDATE Inventory SET wholesale = :wholesale WHERE name = :name");
                query.bindValue(":name", name);
                query.bindValue(":wholesale", wholesale);
                query.exec();
            }
            if(manufacturerState){
                query.prepare("UPDATE Inventory SET manufacturer = :manufacturer WHERE name = :name");
                query.bindValue(":name", name);
                query.bindValue(":manufacturer", manufacturer);
                query.exec();
            }
            if(countState){
                query.prepare("UPDATE Inventory SET countItem = :count WHERE name = :name");
                query.bindValue(":name", name);
                query.bindValue(":count", count);
                query.exec();
            }


            refresh();
}
//used to refresh view to default
void MainWindow::refresh(){
    model->setQuery("SELECT name AS Name, price AS Price, wholesale AS Wholesale, manufacturer AS Manufacturer, countItem AS Count FROM Inventory");
    ui->tableView->setModel(model);
}
