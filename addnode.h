#ifndef ADDNODE_H
#define ADDNODE_H

#include <QDialog>

namespace Ui {
class AddNode;
}

class AddNode : public QDialog
{
    Q_OBJECT

public:
    explicit AddNode(QWidget *parent = nullptr);
    ~AddNode();
    QString GetValue();


private slots:
    void on_AddButton_clicked();

    void on_CancelButton_clicked();

private:
    Ui::AddNode *ui;
    QString value;
};

#endif // ADDNODE_H
