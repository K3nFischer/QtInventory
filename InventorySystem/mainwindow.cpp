#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
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
//Michael Briones
void MainWindow::on_actionNew_triggered()
{
    ui->statusMessage->clear();
    QString filename = QFileDialog::getSaveFileName(this, tr("New File"), "", tr("Data Base File (*.db);;All Files ()"));
        QFile file(filename);
        currentFile = filename;

            mydb.close();
            mydb.setDatabaseName(currentFile);
            mydb.open();
            QSqlQuery query1("DROP TABLE IF EXISTS Inventory");
            query1.exec();
            QSqlQuery query2("CREATE TABLE IF NOT EXISTS Inventory (name TEXT, price INTEGER, wholesale INTEGER, manufacturer TEXT, countItem INTEGER, PRIMARY KEY(name))");
            query2.exec();
            refresh();
}
//Kendall Fischer
void MainWindow::on_actionOpen_triggered()
{
    ui->statusMessage->clear();
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Data Base File (*.db);;All Files ()"));
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
    ui->statusMessage->clear();
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
    if( query.exec() ){
        ui->statusMessage->setText("Successfully inserted item");
    } else {
        ui->statusMessage->setText("Could not insert item");
    }

    refresh();
}

//Garret Mook
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
        if( query.exec() ){
            ui->statusMessage->setText("Successfully deleted item");
        } else {
            ui->statusMessage->setText("Could not delete item");
        }

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
        ui->nameBox->clear();
        ui->priceBox->clear();
        ui->wholesaleBox->clear();
        ui->manufacturerBox->clear();
        ui->countBox->clear();

        bool priceOK = false;
        bool wholeOK = false;
        bool manufactureOK = false;
        bool countOK = false;
        QSqlQuery query(mydb);
        if(priceState){
                query.prepare("UPDATE Inventory SET price = :price WHERE name = :name");
                query.bindValue(":name", name);
                query.bindValue(":price", price);
                priceOK = query.exec();
            }
            if(wholesaleState){
                query.prepare("UPDATE Inventory SET wholesale = :wholesale WHERE name = :name");
                query.bindValue(":name", name);
                query.bindValue(":wholesale", wholesale);
                wholeOK = query.exec();
            }
            if(manufacturerState){
                query.prepare("UPDATE Inventory SET manufacturer = :manufacturer WHERE name = :name");
                query.bindValue(":name", name);
                query.bindValue(":manufacturer", manufacturer);
                manufactureOK = query.exec();
            }
            if(countState){
                query.prepare("UPDATE Inventory SET countItem = :count WHERE name = :name");
                query.bindValue(":name", name);
                query.bindValue(":count", count);
                countOK = query.exec();
            }
        if(priceOK || wholeOK || manufactureOK || countOK){
            ui->statusMessage->setText("Successfully modified item");
        } else {
            ui->statusMessage->setText("Could not modify item");
        }

        refresh();
}
//used to refresh view to default
void MainWindow::refresh(){
    model->setQuery("SELECT name AS Name, price AS Price, wholesale AS Wholesale, manufacturer AS Manufacturer, countItem AS Count FROM Inventory");
    ui->tableView->setModel(model);
}


