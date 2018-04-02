#ifndef GENERATOR_H
#define GENERATOR_H

#include <QByteArray>
#include <QAudioFormat>

class Generator
{

public:
    Generator();
    static void GenerateTone(size_t loFreq, size_t hiFreq, double duration, const QAudioFormat &format, QByteArray &buffer);
    static void GeneratePulse(double implsesInSec, size_t impulsesCount, const QAudioFormat &format, QByteArray &buffer);
    static void AddPause(double duration, const QAudioFormat &format, QByteArray &buffer);
};

#endif // GENERATOR_H
