#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>

namespace Ui {
class FindDialog;
}

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindDialog(QWidget *parent = nullptr);
    ~FindDialog();
    QString GetValue();

private slots:
    void on_CancelButton_clicked();
    void on_FindButton_clicked();

private:
    Ui::FindDialog *ui;
    QString value;
};

#endif // FINDDIALOG_H
