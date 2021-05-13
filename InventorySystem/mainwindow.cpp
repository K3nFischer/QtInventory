#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

//sets up database, model, and creates main window
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    mydb = QSqlDatabase::addDatabase("QSQLITE");

    ui->setupUi(this);
    model = new EditableSqlModel;
}

MainWindow::~MainWindow()
{
    delete ui;
    mydb.close();

}

//Creates a new database file
//Opens a windows where you can set a file name
void MainWindow::on_actionNew_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("New File"), "", tr("Data Base File (*.db);;All Files ()"));
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly | QFile::Text)){
        mydb.close();
        mydb.setDatabaseName(filename);
        mydb.open();

        QSqlQuery queryDropTable("DROP TABLE IF EXISTS Inventory");
        queryDropTable.exec();
        QSqlQuery queryCreateTable("CREATE TABLE IF NOT EXISTS Inventory (name TEXT, price INTEGER, wholesale INTEGER, manufacturer TEXT, countItem INTEGER, PRIMARY KEY(name))");
        queryCreateTable.exec();
    }

    refresh();
}

//Opens a window where you can select a file name to open
void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Data Base File (*.db);;All Files ()"));
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
    }else{
        mydb.close();
        mydb.setDatabaseName(filename);
        mydb.open();

        refresh();
    }
}

//creates a query that takes input from the searchBox
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

//resets to standard view
void MainWindow::on_clearButton_released()
{
    ui->searchBox->clear();
    refresh();
}


//allows for Enter press to activate search
void MainWindow::on_searchBox_returnPressed()
{
    on_searchButton_released();
}

//Inserts Item into the SQLite database
void MainWindow::on_insertButton_released()
{
    QString name = ui->nameBox->text();
    double price = ui->priceBox->text().toDouble();
    double wholesale = ui->wholesaleBox->text().toDouble();
    QString manufacturer = ui->manufacturerBox->text();
    double count = ui->countBox->text().toDouble();

    ui->nameBox->clear();
    ui->priceBox->clear();
    ui->wholesaleBox->clear();
    ui->manufacturerBox->clear();
    ui->countBox->clear();

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


//Deletes Item from the SQLite database
void MainWindow::on_deleteButton_released()
{
    QString name = ui->nameBox->text();

    ui->nameBox->clear();
    ui->priceBox->clear();
    ui->wholesaleBox->clear();
    ui->manufacturerBox->clear();
    ui->countBox->clear();

    QSqlQuery query(mydb);
    query.prepare("DELETE FROM Inventory WHERE name = :name" );
    query.bindValue(":name", name);
    query.exec();
}

//Takes in inputs and modifies a single field or multiple at once
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

     //nameState || priceState || wholesaleState || manufacturerState || countState;
     ui->nameBox->clear();
     ui->priceBox->clear();
     ui->wholesaleBox->clear();
     ui->manufacturerBox->clear();
     ui->countBox->clear();


     QSqlQuery query(mydb);
     if(priceState){
        query.prepare("UPDATE Inventory SET price = :price WHERE name = :name");
        query.bindValue(":name", name);
        query.bindValue(":price", price);
        query.exec();
     }if(wholesaleState){
        query.prepare("UPDATE Inventory SET wholesale = :wholesale WHERE name = :name");
        query.bindValue(":name", name);
        query.bindValue(":wholesale", wholesale);
        query.exec();
     }if(manufacturerState){
        query.prepare("UPDATE Inventory SET manufacturer = :manufacturer WHERE name = :name");
        query.bindValue(":name", name);
        query.bindValue(":manufacturer", manufacturer);
        query.exec();
     }if(countState){
        query.prepare("UPDATE Inventory SET countItem = :count WHERE name = :name");
        query.bindValue(":name", name);
        query.bindValue(":count", count);
        query.exec();
     }

     refresh();
}

//used to set view to default
void MainWindow::refresh(){
    model->setQuery("SELECT name AS Name, price AS Price, wholesale AS Wholesale, manufacturer AS Manufacturer, countItem AS Count FROM Inventory");
    ui->tableView->setModel(model);
}


