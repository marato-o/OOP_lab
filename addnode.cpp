#include "addnode.h"
#include "ui_addnode.h"

AddNode::AddNode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNode)
{
    ui->setupUi(this);
    setModal(true);
}

AddNode::~AddNode()
{
    delete ui;
}

QString AddNode::GetValue()
{
    return value;
}

void AddNode::on_AddButton_clicked()
{
    if (!ui-> value_line->displayText().isEmpty()){
        value = ui->value_line->text();
        accept();
        this->close();
    }
}

void AddNode::on_CancelButton_clicked()
{
    reject();
    this->close();
}

