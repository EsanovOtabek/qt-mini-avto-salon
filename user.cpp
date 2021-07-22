#include "user.h"
#include "ui_user.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QMessageBox>
#include <QDebug>
#include <QTime>
#include <QDate>

User::User(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::User)
{
    ui->setupUi(this);
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/beoo/Documents/Kursishi2/baza.db");
    db.open()?qDebug()<<"DB Ulandi!":qDebug()<<("DB ulanmadi! :( ");

     ui->lineEdit_5->hide();

    QSqlQuery q;
    QString sql="SELECT * FROM cars";
    q.prepare(sql);
    q.exec();
    while(q.next()){
        QString name = q.value(1).toString();
        ui->listWidget->addItem(name);
    }



}

User::~User()
{
    delete ui;
}

void User::on_listWidget_currentTextChanged(const QString &name)
{
    QString nomi,rusumi,soni,narxi,sql,id;
    ui->lineEdit->setText(name);

    QSqlQuery q;
    sql="SELECT * FROM cars WHERE name='"+name+"'";
    q.prepare(sql);
    q.exec();
    if(q.next()){
        id=q.value(0).toString();
        rusumi=q.value(2).toString();
        soni=q.value(3).toString();
        narxi=q.value(4).toString();
    }

    ui->lineEdit_2->setText(rusumi);
    ui->lineEdit_3->setText(soni);
    ui->lineEdit_4->setText(narxi);
    ui->lineEdit_5->setText(id);
}

void User::on_pushButton_clicked()
{
    QString name=ui->lineEdit->text();
    QString soni=ui->lineEdit_3->text();
    QString id=ui->lineEdit_5->text();
    QTime time=QTime::currentTime();
    QDate date=QDate::currentDate();
    QString sdate=date.toString("dd.MM.yyyy ");
    QString stime=time.toString("H:m:s");
    if(soni=="0"){
        QMessageBox::warning(this,":(","Kechirasiz salonda "+name+" avtomobillari tugagan :(",QMessageBox::Ok|QMessageBox::Cancel);
    }
    else{
        QSqlQuery q;
        QString sql="INSERT into orders (car_id,car_name,buyurtma_vaqti) VALUES ("+id+",'"+name+"','"+sdate+stime+"')";
        q.prepare(sql);
        if(q.exec()){
            QMessageBox::information(this,"Ok",""+name+" avtomobiligi buyurtma berildi!",QMessageBox::Ok|QMessageBox::Cancel);

        }
    }
}
