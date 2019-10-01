#include "lossdialog.h"

#include "ui_lossdialog.h"

LossDialog::LossDialog(int score,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LossDialog),
    score(score)
{
ui->setupUi(this);
this->setFixedSize(this->width(), this->height());
setUpUI();
}

LossDialog::~LossDialog() {
    delete ui;
}

// show the score of current player
void LossDialog::setUpUI(){
    ui->score_label->setText(QString::number(score));
}

void LossDialog::on_quitButton_clicked(){
    close();
    exit(0);
}
