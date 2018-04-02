#include <QtDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QtMath>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "generator.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_audioOutput(0),
    m_audioOutputIdx(0),
    m_audioOutputFreq(8000)
{
    ui->setupUi(this);

    m_playDevice = new OutputDevice();
    ModeSelected();
    InitAudioDevice();

    connect(ui->m_rBtnImpulse, &QRadioButton::clicked, this, ModeSelected);//выбираем импульсный режим набора
    connect(ui->m_rBtnTone, &QRadioButton::clicked, this, ModeSelected);//выбираем тональный режим набора
    connect(ui->m_actionChoiceAudioOutput, &QAction::triggered, this, ChoiceAudioOutputDeviceIdx);//выбираем устройство воспроизведения
    connect(ui->m_pBtnResetDTMF, &QPushButton::clicked, this, ResetDTMF);//сбрасываем группы частот к дефолтным

    connect(ui->m_pBtn_1, &QPushButton::clicked, this, NumberClick);//нажимаем 1
    connect(ui->m_pBtn_2, &QPushButton::clicked, this, NumberClick);//нажимаем 2
    connect(ui->m_pBtn_3, &QPushButton::clicked, this, NumberClick);//нажимаем 3
    connect(ui->m_pBtn_4, &QPushButton::clicked, this, NumberClick);//нажимаем 4
    connect(ui->m_pBtn_5, &QPushButton::clicked, this, NumberClick);//нажимаем 5
    connect(ui->m_pBtn_6, &QPushButton::clicked, this, NumberClick);//нажимаем 6
    connect(ui->m_pBtn_7, &QPushButton::clicked, this, NumberClick);//нажимаем 7
    connect(ui->m_pBtn_8, &QPushButton::clicked, this, NumberClick);//нажимаем 8
    connect(ui->m_pBtn_9, &QPushButton::clicked, this, NumberClick);//нажимаем 9
    connect(ui->m_pBtn_0, &QPushButton::clicked, this, NumberClick);//нажимаем 0
    connect(ui->m_pBtn_mul, &QPushButton::clicked, this, NumberClick);//нажимаем *
    connect(ui->m_pBtn_hash, &QPushButton::clicked, this, NumberClick);//нажимаем #

    connect(ui->m_vSliderSoundVolume, &QSlider::valueChanged, this, VolumeChanged);//меням громкость звуковой карты
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ModeSelected()
{
    if(ui->m_rBtnImpulse->isChecked()) {
        m_dialMode = DialMode::MD_IMPULSE;
        ui->m_frameImpulse->show();
        ui->m_frameTone->hide();
        ui->m_gBoxParametrs->setTitle("Параметры импульсного набора");
    }

    if(ui->m_rBtnTone->isChecked()) {
        m_dialMode = DialMode::MD_TONE;
        ui->m_frameImpulse->hide();
        ui->m_frameTone->show();
        ui->m_gBoxParametrs->setTitle("Параметры тонального набора");
    }
}

void MainWindow::AudioOutputStateChanged(QAudio::State newState)
{
    switch (newState) {
        case QAudio::IdleState:
            m_audioOutput->stop();
            m_playDevice->Stop();
            break;

        case QAudio::StoppedState:
            if (m_audioOutput->error() != QAudio::NoError) {
                //для ошибок
            }
            break;
        case QAudio::ActiveState:
            break;
        default:
            break;
    }
}

void MainWindow::ChoiceAudioOutputDeviceIdx()
{
    m_dialog.exec();
    m_audioOutputIdx = m_dialog.GetOutputDeviceIdx();
    m_audioOutputFreq = m_dialog.GetFrequency();
    delete m_audioOutput;
    InitAudioDevice();
}

void MainWindow::ResetDTMF()
{
    //Частоты группы 1
    ui->m_spinBox_697Hz->setValue(697);
    ui->m_spinBox_770Hz->setValue(770);
    ui->m_spinBox_852Hz->setValue(852);
    ui->m_spinBox_941Hz->setValue(941);

    //Частоты группы 2
    ui->m_spinBox_1209Hz->setValue(1209);
    ui->m_spinBox_1336Hz->setValue(1336);
    ui->m_spinBox_1477Hz->setValue(1477);
}

void MainWindow::NumberClick()
{
    QPushButton *btn = static_cast<QPushButton*>(sender());

    //для импульсного набора
    if(m_dialMode == MD_IMPULSE) {
        double impulsesInSec = ui->m_dSpinBoxImpulseCount->value();
        double pause = ui->m_dSpinBoxImpulsePause->value();

        if(btn == ui->m_pBtn_1) {
            Generator::GeneratePulse(impulsesInSec, 1, m_audioFormat, m_buffer);
            Generator::AddPause(pause, m_audioFormat, m_buffer);
            PlayBuffer();
            return;
        }

        if(btn == ui->m_pBtn_2) {
            Generator::GeneratePulse(impulsesInSec, 2, m_audioFormat, m_buffer);
            Generator::AddPause(pause, m_audioFormat, m_buffer);
            PlayBuffer();
            return;
        }

        if(btn == ui->m_pBtn_3) {
            Generator::GeneratePulse(impulsesInSec, 3, m_audioFormat, m_buffer);
            Generator::AddPause(pause, m_audioFormat, m_buffer);
            PlayBuffer();
            return;
        }

        if(btn == ui->m_pBtn_4) {
            Generator::GeneratePulse(impulsesInSec, 4, m_audioFormat, m_buffer);
            Generator::AddPause(pause, m_audioFormat, m_buffer);
            PlayBuffer();
            return;
        }

        if(btn == ui->m_pBtn_5) {
            Generator::GeneratePulse(impulsesInSec, 5, m_audioFormat, m_buffer);
            Generator::AddPause(pause, m_audioFormat, m_buffer);
            PlayBuffer();
            return;
        }

        if(btn == ui->m_pBtn_6) {
            Generator::GeneratePulse(impulsesInSec, 6, m_audioFormat, m_buffer);
            Generator::AddPause(pause, m_audioFormat, m_buffer);
            PlayBuffer();
            return;
        }

        if(btn == ui->m_pBtn_7) {
            Generator::GeneratePulse(impulsesInSec, 7, m_audioFormat, m_buffer);
            Generator::AddPause(pause, m_audioFormat, m_buffer);
            PlayBuffer();
            return;
        }

        if(btn == ui->m_pBtn_8) {
            Generator::GeneratePulse(impulsesInSec, 8, m_audioFormat, m_buffer);
            Generator::AddPause(pause, m_audioFormat, m_buffer);
            PlayBuffer();
            return;
        }

        if(btn == ui->m_pBtn_9) {
            Generator::GeneratePulse(impulsesInSec, 9, m_audioFormat, m_buffer);
            Generator::AddPause(pause, m_audioFormat, m_buffer);
            PlayBuffer();
            return;
        }

        if(btn == ui->m_pBtn_0) {
            Generator::GeneratePulse(impulsesInSec, 10, m_audioFormat, m_buffer);
            Generator::AddPause(pause, m_audioFormat, m_buffer);
            PlayBuffer();
            return;
        }
    }

    //для тонового набора
    if(m_dialMode == MD_TONE) {

        size_t duration = ui->m_spinBoxToneDuration->value();
        size_t pause = ui->m_spinBoxTonePause->value();

        if(btn == ui->m_pBtn_1) {
            size_t loFreq = ui->m_spinBox_697Hz->value();
            size_t hiFreq = ui->m_spinBox_1209Hz->value();

            Generator::GenerateTone(loFreq, hiFreq, duration, m_audioFormat, m_buffer);
            Generator::AddPause(pause, m_audioFormat, m_buffer);
            PlayBuffer();
            return;
        }

        if(btn == ui->m_pBtn_2) {
            size_t loFreq = ui->m_spinBox_697Hz->value();
            size_t hiFreq = ui->m_spinBox_1336Hz->value();

            Generator::GenerateTone(loFreq, hiFreq, duration, m_audioFormat, m_buffer);
            Generator::AddPause(pause, m_audioFormat, m_buffer);
            PlayBuffer();
            return;
        }

        if(btn == ui->m_pBtn_3) {
            size_t loFreq = ui->m_spinBox_697Hz->value();
            size_t hiFreq = ui->m_spinBox_1477Hz->value();

            Generator::GenerateTone(loFreq, hiFreq, duration, m_audioFormat, m_buffer);
            Generator::AddPause(pause, m_audioFormat, m_buffer);
            PlayBuffer();
            return;
        }

        if(btn == ui->m_pBtn_4) {
            size_t loFreq = ui->m_spinBox_770Hz->value();
            size_t hiFreq = ui->m_spinBox_1209Hz->value();

            Generator::GenerateTone(loFreq, hiFreq, duration, m_audioFormat, m_buffer);
            Generator::AddPause(pause, m_audioFormat, m_buffer);
            PlayBuffer();
            return;
        }

        if(btn == ui->m_pBtn_5) {
            size_t loFreq = ui->m_spinBox_770Hz->value();
            size_t hiFreq = ui->m_spinBox_1336Hz->value();

            Generator::GenerateTone(loFreq, hiFreq, duration, m_audioFormat, m_buffer);
            Generator::AddPause(pause, m_audioFormat, m_buffer);
            PlayBuffer();
            return;
        }

        if(btn == ui->m_pBtn_6) {
            size_t loFreq = ui->m_spinBox_770Hz->value();
            size_t hiFreq = ui->m_spinBox_1477Hz->value();

            Generator::GenerateTone(loFreq, hiFreq, duration, m_audioFormat, m_buffer);
            Generator::AddPause(pause, m_audioFormat, m_buffer);
            PlayBuffer();
            return;
        }

        if(btn == ui->m_pBtn_7) {
            size_t loFreq = ui->m_spinBox_852Hz->value();
            size_t hiFreq = ui->m_spinBox_1209Hz->value();

            Generator::GenerateTone(loFreq, hiFreq, duration, m_audioFormat, m_buffer);
            Generator::AddPause(pause, m_audioFormat, m_buffer);
            PlayBuffer();
            return;
        }

        if(btn == ui->m_pBtn_8) {
            size_t loFreq = ui->m_spinBox_852Hz->value();
            size_t hiFreq = ui->m_spinBox_1336Hz->value();

            Generator::GenerateTone(loFreq, hiFreq, duration, m_audioFormat, m_buffer);
            Generator::AddPause(pause, m_audioFormat, m_buffer);
            PlayBuffer();
            return;
        }

        if(btn == ui->m_pBtn_9) {
            size_t loFreq = ui->m_spinBox_852Hz->value();
            size_t hiFreq = ui->m_spinBox_1477Hz->value();

            Generator::GenerateTone(loFreq, hiFreq, duration, m_audioFormat, m_buffer);
            Generator::AddPause(pause, m_audioFormat, m_buffer);
            PlayBuffer();
            return;
        }

        if(btn == ui->m_pBtn_0) {
            size_t loFreq = ui->m_spinBox_941Hz->value();
            size_t hiFreq = ui->m_spinBox_1336Hz->value();

            Generator::GenerateTone(loFreq, hiFreq, duration, m_audioFormat, m_buffer);
            Generator::AddPause(pause, m_audioFormat, m_buffer);
            PlayBuffer();
            return;
        }

        if(btn == ui->m_pBtn_mul) {
            size_t loFreq = ui->m_spinBox_941Hz->value();
            size_t hiFreq = ui->m_spinBox_1209Hz->value();

            Generator::GenerateTone(loFreq, hiFreq, duration, m_audioFormat, m_buffer);
            Generator::AddPause(pause, m_audioFormat, m_buffer);
            PlayBuffer();
            return;
        }

        if(btn == ui->m_pBtn_hash) {
            size_t loFreq = ui->m_spinBox_941Hz->value();
            size_t hiFreq = ui->m_spinBox_1477Hz->value();

            Generator::GenerateTone(loFreq, hiFreq, duration, m_audioFormat, m_buffer);
            Generator::AddPause(pause, m_audioFormat, m_buffer);
            PlayBuffer();
            return;
        }
    }
}

void MainWindow::VolumeChanged(int volume)
{
    if(!m_audioOutput)
        return;

    qreal soundVolume = static_cast<qreal>(volume) / ui->m_vSliderSoundVolume->maximum();
    m_audioOutput->setVolume(soundVolume);
}

void MainWindow::InitAudioDevice()
{
    if(QAudioDeviceInfo::availableDevices(QAudio::AudioOutput).size() == 0) {
        QMessageBox::warning(this, "Ошибка устройств воспроизведения.",
                             "В системе не найдено ни одно устройство для воспроизведения",
                             QMessageBox::Ok);
        m_audioOutput = 0;
        return;
    }

    SetAudioFormat(m_audioFormat);

    QAudioDeviceInfo info(QAudioDeviceInfo::availableDevices(QAudio::AudioOutput)[m_audioOutputIdx]);
    if (!info.isFormatSupported(m_audioFormat)) {
        //format = info.nearestFormat(format);
        m_audioOutput = 0;
        return;
    }

    m_audioOutput = new QAudioOutput(info, m_audioFormat, this);
    VolumeChanged(ui->m_vSliderSoundVolume->value());

    connect(m_audioOutput, SIGNAL(stateChanged(QAudio::State)), this, SLOT(AudioOutputStateChanged(QAudio::State)));
}

void MainWindow::SetAudioFormat(QAudioFormat &format)
{
    format.setSampleRate(m_audioOutputFreq);
    format.setChannelCount(1);
    format.setSampleSize(32);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::Float);
}

void MainWindow::PlayBuffer()
{
    if(!m_audioOutput) {
        QMessageBox::warning(this, "Ошибка воспроизведения.",
                             "Устройство воспроизведения не опознано или не поддерживает текущий формат воспроизведения:"
                             "\n\nSampleRate: " + QString::number(m_audioFormat.sampleRate()) +
                             "\nChannelCount: " + QString::number(m_audioFormat.channelCount()) +
                             "\nSampleSize: " + QString::number(m_audioFormat.sampleSize()) +
                             "\nCodec: " + m_audioFormat.codec(),
                             QMessageBox::Ok);
        return;
    }

    if(m_audioOutput->state() != QAudio::ActiveState) {
        m_playDevice->setBuffer(&m_buffer);
        m_playDevice->Start();
        m_audioOutput->start(m_playDevice);
    }
}

