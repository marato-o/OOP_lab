#ifndef CREATETABLE_H
#define CREATETABLE_H

#include "QDialog"


QT_BEGIN_NAMESPACE
namespace Ui {class CreateTable;}
QT_END_NAMESPACE

class CreateTable : public QDialog
{
    Q_OBJECT

public:
    explicit CreateTable(QWidget *parent = nullptr);
    ~CreateTable();
    QString GetName() const;

private slots:
    void on_CancelButton_clicked();
    void on_CreateButton_clicked();

private:
    Ui::CreateTable *ui;
    QString name;
};

#endif // CREATETABLE_H
