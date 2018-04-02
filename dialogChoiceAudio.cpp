#include "dialogChoiceAudio.h"
#include "ui_dialogChoiceAudio.h"

#include <QAudioDeviceInfo>

DialogChoiceAudio::DialogChoiceAudio(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChoiceAudio),
    m_audioOutputIdx(0)
{
    ui->setupUi(this);

    //создаем список аудио устройств воспроизведения в comboBox
    size_t oDeviceCount = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput).size();
    for(size_t i = 0; i < oDeviceCount; ++i){
        ui->m_comboBoxAudioOutput->addItem(QAudioDeviceInfo::availableDevices(QAudio::AudioOutput)[i].deviceName());
    }
}

DialogChoiceAudio::~DialogChoiceAudio()
{
    delete ui;
}

int DialogChoiceAudio::exec()
{
    m_frequencyIdx = ui->m_comboBoxFreq->currentIndex();
    return QDialog::exec();
}

size_t DialogChoiceAudio::GetOutputDeviceIdx()
{
    return m_audioOutputIdx;
}

size_t DialogChoiceAudio::GetFrequency()
{
    return m_audioOutputFrequency;
}

void DialogChoiceAudio::on_buttonBox_accepted()
{
    m_audioOutputIdx = ui->m_comboBoxAudioOutput->currentIndex();
    m_audioOutputFrequency = ui->m_comboBoxFreq->currentText().toInt();
}

void DialogChoiceAudio::on_buttonBox_rejected()
{
    ui->m_comboBoxAudioOutput->setCurrentIndex(m_audioOutputIdx);
    ui->m_comboBoxFreq->setCurrentIndex(m_frequencyIdx);
}
