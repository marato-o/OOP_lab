#include "finddialog.h"
#include "ui_finddialog.h"

FindDialog::FindDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindDialog)
{
    ui->setupUi(this);
    setModal(true);
}

FindDialog::~FindDialog()
{
    delete ui;
}

void FindDialog::on_CancelButton_clicked()
{
    reject();
    this->close();
}


void FindDialog::on_FindButton_clicked()
{
    if (!ui-> value_line->displayText().isEmpty()){
        value = ui->value_line->text();
        accept();
        this->close();
    }
}

QString FindDialog::GetValue()
{
    return value;
}

