#include "outputDevice.h"


OutputDevice::OutputDevice(QObject *parent) :
    QBuffer(parent)
{

}

OutputDevice::~OutputDevice()
{

}

void OutputDevice::Start()
{
    open(QIODevice::ReadOnly);
}

void OutputDevice::Stop()
{
    reset();
    close();
}

qint64 OutputDevice::readData(char *data, qint64 maxlen)
{
    qint64 total = 0;
    size_t bufferSize = buffer().size();

    if(pos() >= bufferSize)
        return total;

    if(maxlen > bufferSize)
        maxlen = bufferSize;

    if (!buffer().isEmpty()) {
        while (maxlen - total > 0) {
            const qint64 chunk = qMin((bufferSize - pos()), maxlen - total);
            memcpy(data + total, buffer().constData() + pos(), chunk);
            total += chunk;
        }
    }

    return total;
}

qint64 OutputDevice::writeData(const char *data, qint64 len)
{
    Q_UNUSED(data);
    Q_UNUSED(len);

    return 0;
}

qint64 OutputDevice::bytesAvailable()
{
    return buffer().size() + QIODevice::bytesAvailable();
}
