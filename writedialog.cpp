#include "writedialog.h"
#include "ui_writedialog.h"

WriteDialog::WriteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WriteDialog)
{
    ui->setupUi(this);
    setModal(true);
}

WriteDialog::~WriteDialog()
{
    delete ui;
}

QString WriteDialog::GetPath()
{
    return path;
}

void WriteDialog::on_ExportButton_clicked()
{
    if (!ui-> path_line->displayText().isEmpty()){
        path = ui->path_line->text();
        accept();
        this->close();
    }
}


void WriteDialog::on_CancelButton_clicked()
{
    reject();
    this->close();
}

