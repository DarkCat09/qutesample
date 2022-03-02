#include <thread>
#include <chrono>
#include "QRandomGenerator"
#include "QDesktopServices"
#include "QMessageBox"
#include "mainwindow.h"
#include "ui_mainwindow.h"

QRandomGenerator64 gen(std::rand());

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_plainTextEdit_2_textChanged()
{
    //
}


void MainWindow::on_pushButton_clicked()
{
    std::thread t1([&]()
    {
        for (int i = 0; i <= 100; i+=5) {
            ui->progressBar->setValue(i);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    });
    std::thread t2([&]()
    {
        // read
        QString name = ui->plainTextEdit_2->toPlainText();
        QDate birth = ui->dateEdit_2->date();

        // compute
        QDate next = QDate::currentDate();
        next.setDate(next.year(), birth.month(), birth.day());

        // strings
        QString hello = tr("Hello %1!").arg(name);
        QString nextb = tr("Your next birthday is on: %2").arg(next.toString());

        // check if there are my data
        bool namedev = (name.contains("Andre") or name.contains("Андрей"));
        bool datedev = (birth.year() == 2009 and
                        birth.month() == 7 and
                        birth.day() == 13);
        if (namedev and datedev)
            ui->checkBox_2->setEnabled(true);

        // print
        ui->label_greeting->setText(hello);
        ui->label_birthday->setText(nextb);
        ui->lcdNumber->display(next.year() - birth.year());

        // picture
        if (ui->actionRandom_Picture->isChecked())
        {
            int randpic = -1;
            if (!ui->checkBox_2->isChecked())
                randpic = gen.bounded(1, 6);
            QString tmpl = ":/prefix/pics/%1.jpg";
            QString file = tmpl.arg(randpic);
            QPixmap pixmap(file);
            ui->label_image->setPixmap(pixmap.scaled(
                                           ui->label_image->width(),
                                           ui->label_image->height(),
                                           Qt::KeepAspectRatio
                                           )
                                       );
        }
    });
    t1.join();
    t2.join();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::exit(0);
}

void MainWindow::on_actionDeveloper_s_GitHub_triggered()
{
    QDesktopServices::openUrl(QUrl("https://github.com/DarkCat09"));
}


void MainWindow::on_actionApplication_triggered()
{
    QMessageBox msg(
                QMessageBox::Icon::Information,
                tr("About this app"),
                tr("This application written just for learning\n"
                   "Qt for Desktop and Mobile.\n"
                   "by DarkCat09"),
                QMessageBox::Ok);
    msg.exec();
}

