#ifndef LOSSDIALOG_H
#define LOSSDIALOG_H

#include <QDialog>
#include <iostream>
#include "config.h"
#include "leaderboard.h"

class QAbstractButton;


namespace Ui {
class LossDialog;
}

class LossDialog : public QDialog {
    Q_OBJECT

public:
    explicit LossDialog(int score, QWidget *parent = nullptr);
    ~LossDialog();

    virtual void setUpUI();

private slots:
    void on_quitButton_clicked();

private:
    Ui::LossDialog *ui;
    int score;

};

#endif // LOSSDIALOG_H
