#ifndef GENDIALOG_H
#define GENDIALOG_H

#include <QDialog>

namespace Ui {
class GenDialog;
}

class GenDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GenDialog(QWidget *parent = nullptr);
    ~GenDialog();

    QString GetFirstName();
    QString GetSecondName();
    QString GetNewName();

private slots:
    void on_CreateButton_clicked();
    void on_CancelButton_clicked();

private:
    Ui::GenDialog *ui;
    QString first_name;
    QString second_name;
    QString new_name;
};

#endif // GENDIALOG_H
