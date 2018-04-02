#ifndef DIALOGCHOICEAUDIO_H
#define DIALOGCHOICEAUDIO_H

#include <QDialog>


namespace Ui {
class DialogChoiceAudio;
}

class DialogChoiceAudio : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChoiceAudio(QWidget *parent = 0);
    ~DialogChoiceAudio();

    int exec();

    size_t GetOutputDeviceIdx();
    size_t GetFrequency();

private slots:
    void on_buttonBox_accepted();//OK
    void on_buttonBox_rejected();//Cancel

private:
    Ui::DialogChoiceAudio *ui;

    size_t m_audioOutputIdx;//индекс выбраного устройства воспроизведения
    size_t m_audioOutputFrequency;//частота дискретизации
    size_t m_frequencyIdx;//индекс частоты дискретизации в списке
};

#endif // DIALOGCHOICEAUDIO_H
