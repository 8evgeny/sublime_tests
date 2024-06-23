#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define YELLOW attron(COLOR_PAIR(1));
#define GREEN attron(COLOR_PAIR(2));
#define WHITE attron(COLOR_PAIR(3));
#define RED attron(COLOR_PAIR(4));
#define BLUE attron(COLOR_PAIR(5));
#define MAGENTA attron(COLOR_PAIR(6));
#define CYAN attron(COLOR_PAIR(7));

#include <QMainWindow>

void answers();
void answer(uint num, std::string qw1, std::string qw2, std::string qw3, std::string qw4);
std::string letter(int r, int l , float k);
void main_logic();

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Ui::MainWindow *getUi() const;
    void setUi(Ui::MainWindow *newUi);

private slots:
    void on_name_field_editingFinished();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
