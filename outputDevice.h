#ifndef OUTPUTDEVICE_H
#define OUTPUTDEVICE_H

#include <QBuffer>


class OutputDevice : public QBuffer
{
    Q_OBJECT

public:
    explicit OutputDevice(QObject *parent = Q_NULLPTR);
    ~OutputDevice();

    void Start();
    void Stop();

    qint64 readData(char *data, qint64 maxlen);
    qint64 writeData(const char *data, qint64 len);
    qint64 bytesAvailable();
};

#endif // OUTPUTDEVICE_H
