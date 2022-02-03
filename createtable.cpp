#include "createtable.h"
#include "ui_createtable.h"

CreateTable::CreateTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateTable)
{
    ui->setupUi(this);
    setModal(true);
}

CreateTable::~CreateTable()
{
    delete ui;
}


void CreateTable::on_CancelButton_clicked()
{
    reject();
    this->close();
}


void CreateTable::on_CreateButton_clicked()
{
    if (!ui-> name->displayText().isEmpty()){
        name = ui->name->text();
        accept();
        this->close();
    }
}

QString CreateTable::GetName() const
{
    return name;
}

