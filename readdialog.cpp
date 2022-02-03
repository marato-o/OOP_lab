#include "readdialog.h"
#include "ui_readdialog.h"

ReadDialog::ReadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReadDialog)
{
    ui->setupUi(this);
    setModal(true);
}

ReadDialog::~ReadDialog()
{
    delete ui;
}

QString ReadDialog::GetName()
{
    return name;
}

QString ReadDialog::GetPath()
{
    return path;
}

void ReadDialog::on_ReadButton_clicked()
{
    if (!ui-> name_line->displayText().isEmpty() && !ui-> path_line->displayText().isEmpty()){
        name = ui->name_line->text();
        path = ui->path_line->text();
        accept();
        this->close();
    }
}


void ReadDialog::on_CancelButton_clicked()
{
    reject();
    this->close();
}

