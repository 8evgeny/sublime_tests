#include <QtWidgets>

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    QWidget *window = new QWidget;
    window->setWindowTitle("Программа-ползунок");
    QSpinBox *spin = new QSpinBox;
    QSlider *sliderH = new QSlider(Qt::Horizontal);
    QSlider *sliderV = new QSlider(Qt::Vertical);
    QPushButton *button = new QPushButton("Выход из программы");
    spin->setRange(0,150);
    sliderH->setRange(0,150);
    sliderV->setRange(0,150);
    QObject::connect(spin, SIGNAL(valueChanged(int)), sliderH, SLOT(setValue(int)));
    QObject::connect(sliderH, SIGNAL(valueChanged(int)), spin, SLOT(setValue(int)));
    QObject::connect(spin, SIGNAL(valueChanged(int)), sliderV, SLOT(setValue(int)));
    QObject::connect(sliderV, SIGNAL(valueChanged(int)), spin, SLOT(setValue(int)));
    QObject::connect(button, SIGNAL(clicked(bool)), &a, SLOT(quit()));
    spin->setValue(50);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(spin);
    layout->addWidget(sliderH);
    layout->addWidget(sliderV);
    layout->addWidget(button);
    window->setLayout(layout);
    window->show();
    return a.exec();
}
