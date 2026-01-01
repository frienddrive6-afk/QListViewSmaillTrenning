#pragma once

#include <QMainWindow>

class QVBoxLayout;
class QListWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    QVBoxLayout* m_mainLayout;
    QList<QString> m_data;

    void setUI();






};