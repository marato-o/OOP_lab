#ifndef WRITEDIALOG_H
#define WRITEDIALOG_H

#include <QDialog>

namespace Ui {
class WriteDialog;
}

class WriteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WriteDialog(QWidget *parent = nullptr);
    ~WriteDialog();
    QString GetPath();

private slots:
    void on_ExportButton_clicked();

    void on_CancelButton_clicked();

private:
    Ui::WriteDialog *ui;
    QString path;
};

#endif // WRITEDIALOG_H
