#include <QtMath>

#include "generator.h"

Generator::Generator()
{

}

void Generator::GenerateTone(size_t loFreq, size_t hiFreq, double duration, const QAudioFormat &format, QByteArray &buffer)
{
    int sampleRate = format.sampleRate();
    size_t samplesCount =  sampleRate * duration / 1000;//необходимое кол-во выборок (samples)

    buffer.clear();
    buffer.resize(static_cast<int>(samplesCount * sizeof(float)));

    float loPeriod = 2 * M_PI * loFreq;
    float hiPeriod = 2 * M_PI * hiFreq;

    float amplitude = 0.5;

    for(size_t i = 0; i < samplesCount; ++i){
        float loSample = amplitude * qSin(loPeriod * i / sampleRate);
        float hiSample = amplitude * qSin(hiPeriod * i / sampleRate);
        float summ = loSample + hiSample;
        memcpy(buffer.data() + i*sizeof(float), &summ, sizeof(float));
    }
}

void Generator::GeneratePulse(double implsesInSec, size_t impulsesCount, const QAudioFormat &format, QByteArray &buffer)
{
    int sampleRate = format.sampleRate();
    size_t samplesCount =  sampleRate * impulsesCount / implsesInSec;//необходимое кол-во выборок (samples)

    buffer.clear();
    buffer.resize(static_cast<int>(samplesCount * sizeof(float)));

    size_t sectionsCount = impulsesCount + impulsesCount - 1;//кол-во секций
    size_t sectionSize = samplesCount / sectionsCount;//размер секции в выборках

    for(size_t i = 0; i < sectionsCount; ++i){
        float level = 0;
        if(i % 2 == 0)
            level = 0.5;
        for(size_t j = i*sectionSize; j < i*sectionSize + sectionSize; ++j){
            memcpy(buffer.data() + j*sizeof(float), &level, sizeof(float));
        }
    }
}

void Generator::AddPause(double duration, const QAudioFormat &format, QByteArray &buffer)
{
    int sampleRate = format.sampleRate();
    size_t samplesCount =  sampleRate * duration / 1000;//необходимое кол-во выборок (samples)

    size_t lastSize = buffer.size();

    float pauseLevel = 0;

    buffer.resize(lastSize + static_cast<int>(samplesCount * sizeof(float)));
    for(size_t i = 0; i < samplesCount; ++i){
        memcpy(buffer.data() + lastSize + i*sizeof(float), &pauseLevel, sizeof(float));
    }
}
