#ifndef READDIALOG_H
#define READDIALOG_H

#include <QDialog>

namespace Ui {
class ReadDialog;
}

class ReadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReadDialog(QWidget *parent = nullptr);
    ~ReadDialog();
    QString GetName();
    QString GetPath();

private slots:
    void on_ReadButton_clicked();

    void on_CancelButton_clicked();

private:
    Ui::ReadDialog *ui;
    QString name;
    QString path;
};

#endif // READDIALOG_H
