#ifndef SOUN_PLAYER_H
#define SOUN_PLAYER_H


class SoundPlayer : public QObject
{
    Q_OBJECT

    public:
        SoundPlayer(Ui::ChatRoomWindow *ui, const QString &soundFilePath)
            : ui(ui)
        {
            soundEffect.setSource(QUrl::fromLocalFile(soundFilePath));
            soundEffect.setVolume(1.0); // Defina o volume desejado
        }

    public slots:
        void playSound()
        {
            soundEffect.play();
        }

    private:
        Ui::ChatRoomWindow *ui;
        QSoundEffect soundEffect;
};

#endif // SOUN_PLAYER_H
