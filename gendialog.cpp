#include "gendialog.h"
#include "ui_gendialog.h"

GenDialog::GenDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GenDialog)
{
    ui->setupUi(this);
    setModal(true);
}

GenDialog::~GenDialog()
{
    delete ui;
}

QString GenDialog::GetFirstName()
{
    return first_name;
}

QString GenDialog::GetSecondName()
{
    return second_name;
}

QString GenDialog::GetNewName()
{
    return new_name;
}

void GenDialog::on_CreateButton_clicked()
{
    if (!ui-> first_line->displayText().isEmpty()
            &&!ui-> second_line->displayText().isEmpty()
            && !ui-> new_line->displayText().isEmpty()){
        first_name = ui->first_line->text();
        second_name = ui->second_line->text();
        new_name = ui->new_line->text();
        accept();
        this->close();
    }
}


void GenDialog::on_CancelButton_clicked()
{
    reject();
    this->close();
}

