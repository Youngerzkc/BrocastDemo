#include "udpserver.h"
#include "QVBoxLayout"
#include "QPushButton"
UdpServer::UdpServer( QWidget *parent, Qt::WindowFlags  f )
    : QDialog( parent, f )
{  
    setWindowTitle(tr("UDP Server"));

    QVBoxLayout *vbMain = new QVBoxLayout( this );

    LabelTimer = new QLabel( this );
    LabelTimer->setText(tr("Timer:"));
    vbMain->addWidget( LabelTimer );
   
    LineEditText = new QLineEdit(this);
    vbMain->addWidget( LineEditText );
           
    PushButtonStart = new QPushButton( this);
    PushButtonStart->setText( tr( "Start" ) );  
    vbMain->addWidget( PushButtonStart );

    connect(PushButtonStart,SIGNAL(clicked()),this,SLOT(PushButtonStart_clicked()));	

    port = 8300;

	isStarted=false;
	
	udpSocket = new QUdpSocket(this); 
	
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
}

UdpServer::~UdpServer()
{
}
                                                                             
void UdpServer::PushButtonStart_clicked()                     
{          
	if(!isStarted)
	{      	      
            timer -> start(1000);
	    isStarted = true;
	    PushButtonStart->setText(tr("Stop"));
	}
	else
	{
		timer -> stop();
		isStarted = false;
		PushButtonStart->setText(tr("Start"));
	}
}

void UdpServer::timeout()                     
{                          

        QString s=QTime::currentTime().toString();
                int re=udpSocket->writeDatagram(s.toUtf8(),QHostAddress("224.2.2.2"),62224);
               if(re==-1)
                   qDebug()<<"send failed--";
               else
                   qDebug()<<"send ok--"<<s;
}
