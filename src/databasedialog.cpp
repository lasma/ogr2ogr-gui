#include "inc/databasedialog.h"
#include "ui_databasedialog.h"
#include "iostream"

DatabaseDialog::DatabaseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatabaseDialog)
{
    ui->setupUi(this);
}

DatabaseDialog::~DatabaseDialog()
{
    std::cout << "~DatabaseDialog" << std::endl;
    delete ui;
}


//void Inf::InitSlots( void )
//{
//	QObject::connect( btnConnect, SIGNAL( clicked() ), this, SLOT( evtBtnConnect( void ) ) );

//	QObject::connect( radAllTables, SIGNAL( clicked() ), this, SLOT( evtRadAllTables( void ) ) );

//	QObject::connect( radNonTables, SIGNAL( clicked() ), this, SLOT( evtRadNonTables( void ) ) );

//	QObject::connect( btnCancel, SIGNAL( clicked() ), this, SLOT( evtBtnCancel( void ) ) );

//	QObject::connect( btnAccept, SIGNAL( clicked() ), this, SLOT( evtBtnAccept( void ) ) );
//}
