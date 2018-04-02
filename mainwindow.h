#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAudio>
#include <QAudioOutput>
#include <QKeyEvent>
#include <QMainWindow>

#include "outputDevice.h"
#include "dialogChoiceAudio.h"

enum DialMode {
    MD_IMPULSE = 0,
    MD_TONE = 1
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:

private slots:
    void ModeSelected();//выбираем режим набора
    void AudioOutputStateChanged(QAudio::State newState);//статус устройства воспроизведения
    void ChoiceAudioOutputDeviceIdx();//выбор устройства воспроизведения
    void ResetDTMF();//сброс групп частот для тонального набора
    void NumberClick();//обработка события набора номера, для двух режимов набора
    void VolumeChanged(int volume);//задаем громкость звуковой карты

private:
    void InitAudioDevice();//Инциализация устройства воспроизведения
    void SetAudioFormat(QAudioFormat &format);//Установка формата аудио данных
    void PlayBuffer();//воспроизвести текущий(сформированный) аудиобуфер

    Ui::MainWindow *ui;

    QAudioFormat m_audioFormat;//формат аудио
    QAudioOutput *m_audioOutput;//устройство воспроизведения
    OutputDevice *m_playDevice;//устройство для передачи аудио буфера в устройство воспроизведения

    QByteArray m_buffer;//аудио буфер
    size_t m_audioOutputIdx;//индекс устройства воспроизведения в ОС
    size_t m_audioOutputFreq;//частота дискретизации
    DialMode m_dialMode;//режим набора

    DialogChoiceAudio m_dialog;//диалоговое окно - выбора устройства воспроизведения
};

#endif // MAINWINDOW_H
