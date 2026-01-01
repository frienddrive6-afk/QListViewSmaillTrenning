#include "MainWindow.h"

#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QWidget>
#include <QString>
#include <QScrollArea>
#include <QCheckBox>
#include <QSplitter>
#include <QListView>
#include <QStringListModel>


MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent)
{
    setUI();
}

void MainWindow::setUI()
{
    setWindowTitle("Тренинг");
    resize(800, 600);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* m_mainLayout = new QVBoxLayout(centralWidget);
    m_mainLayout->setAlignment(Qt::AlignTop);

    QSplitter* splitter = new QSplitter(Qt::Horizontal);
    m_mainLayout->addWidget(splitter);

    QWidget* leftWidget = new QWidget(splitter);
    splitter->addWidget(leftWidget);
    QVBoxLayout* leftLayout = new QVBoxLayout(leftWidget);

    QWidget* rightWidget = new QWidget(splitter);
    splitter->addWidget(rightWidget);
    QVBoxLayout* rightLayout = new QVBoxLayout(rightWidget);

    //listView
    QListView* listView = new QListView(leftWidget);
    listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    listView->setSelectionMode(QAbstractItemView::ExtendedSelection);

    listView->setFlow(QListView::TopToBottom); 
    listView->setWrapping(false); 

    listView->setResizeMode(QListView::Adjust);

    listView->setUniformItemSizes(true);

    listView->setStyleSheet(
        "QListView::item {"
        "   height: 50px;"    
        "   padding: 5px;"    
        "}"
    );

    leftLayout->addWidget(listView);
    QStringListModel* model = new QStringListModel(this);
    m_data<<"23423423423"<<"sfsdsdfsdfcvxcv"<<"2342342346dfsdf";
    model->setStringList(m_data);
    listView->setModel(model);

    QLabel* label = new QLabel("Выбрано: нет",rightWidget);
    rightLayout->addWidget(label);
    QPushButton* button = new QPushButton("Удалить выделенное",rightWidget);
    rightLayout->addWidget(button);

    splitter->setStretchFactor(0, 6);
    splitter->setStretchFactor(1, 3);



    // connect(listView, &QListView::clicked, [=](const QModelIndex& index)
    // {
    //     label->setText("Нажал " + QString::number(index.row()) + " Выбрано " + index.data().toString());
    // });

    connect(listView->selectionModel(), &QItemSelectionModel::selectionChanged,[=](){
        
        QModelIndexList indexes = listView->selectionModel()->selectedIndexes();

        if(indexes.size() == 1)
        {
            label->setText("Нажал " + QString::number(indexes[0].row()) + " Выбрано " + indexes[0].data().toString());  
        }else
        {
            label->setText("Выбрано объектов: " + QString::number(indexes.size()));
        }

    });

    connect(button, &QPushButton::clicked, [=](){

        QModelIndexList indexes = listView->selectionModel()->selectedIndexes();

        if(indexes.size() > 0)
        {
            std::sort(indexes.begin(), indexes.end(),[](const QModelIndex &a, const QModelIndex &b ){
                return a.row() > b.row();
            });

            for(const QModelIndex& index : indexes)
            {
                model->removeRow(index.row());
            }

            m_data = model->stringList();

            // for(QString str : m_data)
            // {
            //     qDebug() << str;
            // }
            // qDebug()<<'\n';
        }

    });

}