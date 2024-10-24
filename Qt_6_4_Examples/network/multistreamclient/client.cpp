// Copyright (C) 2016 Alex Trotsenko <alex1973tr@gmail.com>
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include <QtWidgets>
#include <QtNetwork>

#include "client.h"
#include "movieconsumer.h"
#include "timeconsumer.h"
#include "chatconsumer.h"

#include "../shared/sctpchannels.h"

Client::Client(QWidget *parent)
    : QDialog(parent)
    , consumers(SctpChannels::NumberOfChannels)
{
    setWindowTitle(tr("Multi-stream Client"));

    sctpSocket = new QSctpSocket(this);

    QLabel *hostLabel = new QLabel(tr("&Server name:"));
    QLabel *portLabel = new QLabel(tr("S&erver port:"));

    hostCombo = new QComboBox;
    hostCombo->setEditable(true);
    // find out name of this machine
    QString name = QHostInfo::localHostName();
    if (!name.isEmpty()) {
        hostCombo->addItem(name);
        QString domain = QHostInfo::localDomainName();
        if (!domain.isEmpty())
            hostCombo->addItem(name + QChar('.') + domain);
    }
    if (name != QString("localhost"))
        hostCombo->addItem(QString("localhost"));
    // find out IP addresses of this machine
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // add non-localhost addresses
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (!ipAddressesList.at(i).isLoopback())
            hostCombo->addItem(ipAddressesList.at(i).toString());
    }
    // add localhost addresses
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i).isLoopback())
            hostCombo->addItem(ipAddressesList.at(i).toString());
    }

    portLineEdit = new QLineEdit;
    portLineEdit->setValidator(new QIntValidator(1, 65535, this));

    hostLabel->setBuddy(hostCombo);
    portLabel->setBuddy(portLineEdit);

    connectButton = new QPushButton(tr("Connect"));
    connectButton->setDefault(true);
    connectButton->setEnabled(false);

    QPushButton *quitButton = new QPushButton(tr("Quit"));
    quitButton->setAutoDefault(false);

    QDialogButtonBox *buttonBox = new QDialogButtonBox;
    buttonBox->addButton(connectButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::AcceptRole);

    QLabel *movieLabel = new QLabel(tr("Movie stream:"));
    consumers[SctpChannels::Movie] = new MovieConsumer(this);
    QLabel *timeLabel = new QLabel(tr("Time stream:"));
    consumers[SctpChannels::Time] = new TimeConsumer(this);
    QLabel *chatLabel = new QLabel(tr("&Chat:"));
    consumers[SctpChannels::Chat] = new ChatConsumer(this);
    chatLabel->setBuddy(consumers[SctpChannels::Chat]->widget());

    connect(hostCombo, &QComboBox::editTextChanged, this, &Client::enableConnectButton);
    connect(portLineEdit, &QLineEdit::textChanged, this, &Client::enableConnectButton);
    connect(connectButton, &QPushButton::clicked, this, &Client::requestConnect);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &Client::accept);
    connect(sctpSocket, &QSctpSocket::connected, this, &Client::connected);
    connect(sctpSocket, &QSctpSocket::disconnected, this, &Client::disconnected);
    connect(sctpSocket, &QSctpSocket::channelReadyRead, this, &Client::readDatagram);
    connect(sctpSocket, &QSctpSocket::errorOccurred, this, &Client::displayError);
    connect(consumers[SctpChannels::Time], &Consumer::writeDatagram, this, &Client::writeDatagram);
    connect(consumers[SctpChannels::Chat], &Consumer::writeDatagram, this, &Client::writeDatagram);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(hostLabel, 0, 0);
    mainLayout->addWidget(hostCombo, 0, 1);
    mainLayout->addWidget(portLabel, 1, 0);
    mainLayout->addWidget(portLineEdit, 1, 1);
    mainLayout->addWidget(buttonBox, 2, 0, 1, 2);
    mainLayout->addWidget(movieLabel, 3, 0);
    mainLayout->addWidget(timeLabel, 3, 1);
    mainLayout->addWidget(consumers[SctpChannels::Movie]->widget(), 4, 0);
    mainLayout->addWidget(consumers[SctpChannels::Time]->widget(), 4, 1);
    mainLayout->addWidget(chatLabel, 5, 0);
    mainLayout->addWidget(consumers[SctpChannels::Chat]->widget(), 6, 0, 1, 2);
    setLayout(mainLayout);

    portLineEdit->setFocus();
}

Client::~Client()
{
    delete sctpSocket;
}

void Client::connected()
{
    consumers[SctpChannels::Chat]->widget()->setFocus();
}

void Client::disconnected()
{
    for (Consumer *consumer : consumers)
        consumer->serverDisconnected();

    sctpSocket->close();
}

void Client::requestConnect()
{
    connectButton->setEnabled(false);
    sctpSocket->abort();
    sctpSocket->connectToHost(hostCombo->currentText(),
                              portLineEdit->text().toInt());
}

void Client::readDatagram(int channel)
{
    sctpSocket->setCurrentReadChannel(channel);
    consumers[channel]->readDatagram(sctpSocket->readDatagram().data());
}

void Client::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("Multi-stream Client"),
                                 tr("The host was not found. Please check the "
                                    "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("Multi-stream Client"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the multi-stream server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        break;
    default:
        QMessageBox::information(this, tr("Multi-stream Client"),
                                 tr("The following error occurred: %1.")
                                 .arg(sctpSocket->errorString()));
    }

    enableConnectButton();
}

void Client::enableConnectButton()
{
    connectButton->setEnabled(!hostCombo->currentText().isEmpty() &&
                              !portLineEdit->text().isEmpty());
}

void Client::writeDatagram(const QByteArray &ba)
{
    if (sctpSocket->isValid() && sctpSocket->state() == QAbstractSocket::ConnectedState) {
        sctpSocket->setCurrentWriteChannel(consumers.indexOf(static_cast<Consumer *>(sender())));
        sctpSocket->writeDatagram(ba);
    }
}
