#include "login.h"
#include "ui_login.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QString>
#include <QtSql/QSqlDriver>
#include <QMessageBox>
#include <QDebug>

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
   ui->setupUi(this);

   QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
   db.setDatabaseName("C:/Users/beoo/Documents/Kursishi2/baza.db");
   db.open()?qDebug()<<"DB Ulandi!":qDebug()<<("DB ulanmadi! :( ");

}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
    QString msg="Login Yoki Parolda Xa'tolik!!",rol;
    QString login = ui->lineEdit->text().trimmed();
    QString parol = ui->lineEdit_2->text().trimmed();
    if(login.size()>0&&parol.size()>0){
        QSqlQuery q;
        QString sql="SELECT rol FROM users WHERE login='"+login+"' AND parol='"+parol+"'";
        q.prepare(sql);
        q.exec();

        while(q.next()){
            rol = q.value(0).toString();
            msg="Tizimga "+rol+" bo'lib kirdingiz!";
        }

        QMessageBox::information(this,"login",msg,QMessageBox::Ok,QMessageBox::Cancel);

        if(rol=="admin"){
            this->close();
            admin_page.show();
        }else
        if(rol=="user"){
            this->close();
            user_page.show();
        }

    }
}
