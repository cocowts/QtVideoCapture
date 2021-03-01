#include "mainwindow.h"

#include <QCameraInfo>
#include <QDir>
#include <QGroupBox>
#include <QSplitter>
#include <QStringLiteral>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    initUi();
    initControl();
}

MainWindow::~MainWindow()
{ }

void MainWindow::initUi()
{
    m_videoLabel.setAlignment(Qt::AlignCenter);
    m_videoLabel.setPixmap(QPixmap(":/img/src/camera.jpg"));
    m_videosListBox.setEditable(true);
    m_videosListBox.setToolTip(QStringLiteral("可用的摄像头列表"));
    m_videoResolutionBox.setToolTip(QStringLiteral("可用的分辨率"));
    m_switchBtn.setText(QStringLiteral("打开"));
    m_takePictureBtn.setText(QStringLiteral("拍照"));
    m_takeVideoBtn.setText(QStringLiteral("开始录像"));
    m_pathBtn.setText(QStringLiteral("保存路径"));
    m_scanDevBtn.setText(QStringLiteral("硬件扫描"));
    m_pathEdit.setText(QDir::currentPath());
    m_pathEdit.setEnabled(false);
    m_takePictureBtn.setEnabled(false);
    m_takeVideoBtn.setEnabled(false);

    QGroupBox *lhsGroupBox = new QGroupBox(QStringLiteral("视频窗口"));
    QVBoxLayout *lhsLayout = new QVBoxLayout;
    lhsLayout->addWidget(&m_videoLabel);
    lhsGroupBox->setLayout(lhsLayout);

    QGroupBox *rhsGroupBox = new QGroupBox(QStringLiteral("控制区"));
    QVBoxLayout *rhsLayout = new QVBoxLayout;
    rhsLayout->addWidget(&m_videosListBox);
    rhsLayout->addWidget(&m_videoResolutionBox);
    rhsLayout->addWidget(&m_switchBtn);
    rhsLayout->addWidget(&m_takePictureBtn);
    rhsLayout->addWidget(&m_takeVideoBtn);
    rhsLayout->addWidget(&m_pathBtn);
    rhsLayout->addWidget(&m_scanDevBtn);
    rhsLayout->addStretch();
    rhsGroupBox->setLayout(rhsLayout);
    rhsGroupBox->setMinimumWidth(150);

    QSplitter *mainSpliter = new QSplitter(Qt::Horizontal, this);
    mainSpliter->addWidget(lhsGroupBox);
    mainSpliter->addWidget(rhsGroupBox);
    mainSpliter->setStretchFactor(0,5);
    mainSpliter->setStretchFactor(1,0);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(mainSpliter);
    mainLayout->addWidget(&m_pathEdit);
    mainLayout->setContentsMargins(10, 10, 10, 5);
    setLayout(mainLayout);
    setWindowTitle(QStringLiteral("OpencvDemo"));
    setWindowIcon(QIcon(":/img/src/logo.png"));
}

