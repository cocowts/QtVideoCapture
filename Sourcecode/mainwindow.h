#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

#include "camara.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initUi();
    void initControl();

    void scanCamDevs();

private:
    QLabel      m_videoLabel;
    QComboBox   m_videosListBox;
    QComboBox   m_videoResolutionBox;
    QPushButton m_switchBtn;
    QPushButton m_takePictureBtn;
    QPushButton m_takeVideoBtn;
    QPushButton m_pathBtn;
    QPushButton m_scanDevBtn;
    QLineEdit   m_pathEdit;

    Camara      m_camara;
};
#endif // MAINWINDOW_H
