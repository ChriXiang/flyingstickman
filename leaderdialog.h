#ifndef LEADERDIALOG_H
#define LEADERDIALOG_H

#include <QDialog>
#include <iostream>
#include "config.h"
#include "leaderboard.h"

class QAbstractButton;


namespace Ui {
class LeaderDialog;
}

class LeaderDialog : public QDialog {
    Q_OBJECT

public:
    explicit LeaderDialog(bool *paused, QWidget *parent = nullptr);
    ~LeaderDialog();

    virtual void setUpUI();

private slots:
    void on_resume_clicked();

private:
    Ui::LeaderDialog *ui;
    LeaderBoard lb;
    bool *paused;

};
#endif // LEADERDIALOG_H
