#include "leaderdialog.h"

#include "ui_leaderdialog.h"

LeaderDialog::LeaderDialog(bool *paused, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LeaderDialog),
    lb(),
    paused(paused)
{
ui->setupUi(this);
//this->setStyleSheet("background-color: #FFFFFF;"); //White
this->setFixedSize(this->width(), this->height());
setUpUI();
}

LeaderDialog::~LeaderDialog() {
    delete ui;
}


//Sets up the pause screen by leader board
void LeaderDialog::setUpUI() {

    std::vector<std::pair<std::string, int>> leaders = lb.getLeaders();
    for (unsigned int i = 1; i <= leaders.size(); i++){
        if (i > 10) break;
        switch (i) {
        case 1:
            ui->num_1->setText(QString::number(i));
            ui->name_1->setText(QString::fromStdString(leaders[i-1].first));
            ui->score_1->setText(QString::number(leaders[i-1].second));
            break;
        case 2:
            ui->num_2->setText(QString::number(i));
            ui->name_2->setText(QString::fromStdString(leaders[i-1].first));
            ui->score_2->setText(QString::number(leaders[i-1].second));
            break;
        case 3:
            ui->num_3->setText(QString::number(i));
            ui->name_3->setText(QString::fromStdString(leaders[i-1].first));
            ui->score_3->setText(QString::number(leaders[i-1].second));
            break;
        case 4:
            ui->num_4->setText(QString::number(i));
            ui->name_4->setText(QString::fromStdString(leaders[i-1].first));
            ui->score_4->setText(QString::number(leaders[i-1].second));
            break;
        case 5:
            ui->num_5->setText(QString::number(i));
            ui->name_5->setText(QString::fromStdString(leaders[i-1].first));
            ui->score_5->setText(QString::number(leaders[i-1].second));
            break;
        case 6:
            ui->num_6->setText(QString::number(i));
            ui->name_6->setText(QString::fromStdString(leaders[i-1].first));
            ui->score_6->setText(QString::number(leaders[i-1].second));
            break;
        case 7:
            ui->num_7->setText(QString::number(i));
            ui->name_7->setText(QString::fromStdString(leaders[i-1].first));
            ui->score_7->setText(QString::number(leaders[i-1].second));
            break;
        case 8:
            ui->num_8->setText(QString::number(i));
            ui->name_8->setText(QString::fromStdString(leaders[i-1].first));
            ui->score_8->setText(QString::number(leaders[i-1].second));
            break;
        case 9:
            ui->num_9->setText(QString::number(i));
            ui->name_9->setText(QString::fromStdString(leaders[i-1].first));
            ui->score_9->setText(QString::number(leaders[i-1].second));
            break;
        case 10:
            ui->num_10->setText(QString::number(i));
            ui->name_10->setText(QString::fromStdString(leaders[i-1].first));
            ui->score_10->setText(QString::number(leaders[i-1].second));
            break;
        default:
            break;
        }

    }
}

void LeaderDialog::on_resume_clicked() {

    *this->paused = false;
    close();
}

