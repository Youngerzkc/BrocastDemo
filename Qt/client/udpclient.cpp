#include "udpclient.h"
#include <QDebug>
#include "QVBoxLayout"

UdpClient::UdpClient( QWidget *parent, Qt::WindowFlags  f )
    : QDialog( parent, f )
{  
    setWindowTitle(tr("UDP Client"));

   QVBoxLayout *vbMain = new QVBoxLayout( this );

 	TextEditReceive = new QTextEdit( this); 
    vbMain->addWidget( TextEditReceive );    
       
    PushButtonClose = new QPushButton( this);
    PushButtonClose->setText( tr( "Close" ) );  
    vbMain->addWidget( PushButtonClose );

    connect(PushButtonClose,SIGNAL(clicked()),this,SLOT(PushButtonClose_clicked()));	
        port = 8302;

        udpSocket=new QUdpSocket;
            //socket再加入组播之前，需要先绑定网络地址和端口
        //QHostAddress::AnyIPv4 根据不同版本的qt要进行修改
            if(!udpSocket->bind(QHostAddress::Any,62224,QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint))
                qDebug()<<"bind failed--";
            //socket调用joinMulticastGroup加入组播
            if(!udpSocket->joinMulticastGroup(QHostAddress("224.2.2.2")))
                qDebug()<<"joinMuticastGroup failed--";

        //udpSocket = new QUdpSocket(this);
       connect(udpSocket, SIGNAL(readyRead()),this, SLOT(dataReceived()));

}

UdpClient::~UdpClient()
{
}
                                                                             
void UdpClient::PushButtonClose_clicked()                     
{          
	accept();
}

void UdpClient::dataReceived()
{
    while (udpSocket->hasPendingDatagrams()) 
    {
	 	QByteArray datagram;
	 	datagram.resize(udpSocket->pendingDatagramSize());

	 	udpSocket->readDatagram(datagram.data(), datagram.size());
	
        QString msg=datagram.data();
        msg=msg.append("\n");

		TextEditReceive->insertPlainText(msg);
    }
}
