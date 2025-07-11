#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QList>

class ChatServer : public QTcpServer
{
    Q_OBJECT

signals:
    void newMessageReceived(const QString &message);

public:
    explicit ChatServer(QObject *parent = nullptr);             //explicit 명시적 선언 및 생성자 선언, 생성시 초기화.
    ~ChatServer();                                              //소멸자 선언
    bool startServer(quint16 port = 12345);                     // 외부에서 호출시 지정하지 않으면, 12345 고정
                                                                //0~1023 well-known 포트(관리자 권한 필요), 1024~49151 등록된 포트, 49152~65535 등록된 포트 사설 포트
    void broadcastMessage(const QString &message);

protected:
    void incomingConnection(qintptr socketDescriptor) override;    // 새로운 클라이언트가 접속할 때 실행되는 함수

private slots:
    void onReadyRead();                                         //클라이언트 접속시작을 처리 할 슬롯
    void onDisconnected();                                      //클라이언트 접속종료를 처리 할 슬롯

private:
    QList<QTcpSocket*>m_clients;                                //채팅에서 참여자 목록을 저장할 리스트
};

#endif // CHATSERVER_H

