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
    void on_dateEdit_dateChanged(const QDate &date);
    void on_r_1_editingFinished();
    void on_r_2_editingFinished();
    void on_r_3_editingFinished();
    void on_r_4_editingFinished();
    void on_r_5_editingFinished();
    void on_r_6_editingFinished();
    void on_r_7_editingFinished();
    void on_r_8_editingFinished();
    void on_r_9_editingFinished();
    void on_r_10_editingFinished();
    void on_r_11_editingFinished();
    void on_r_12_editingFinished();
    void on_l_1_editingFinished();
    void on_l_2_editingFinished();
    void on_l_3_editingFinished();
    void on_l_4_editingFinished();
    void on_l_5_editingFinished();
    void on_l_6_editingFinished();
    void on_l_7_editingFinished();
    void on_l_8_editingFinished();
    void on_l_9_editingFinished();
    void on_l_10_editingFinished();
    void on_l_11_editingFinished();
    void on_l_12_editingFinished();
void paintEvent(QPaintEvent *event);

    void on_button_exit_clicked();
    void on_name_field_textActivated(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QString name_field;
    QString  Date;
    unsigned int  r1{0}, r2{0}, r3{0}, r4{0}, r5{0}, r6{0}, r7{0}, r8{0}, r9{0}, r10{0}, r11{0}, r12{0};
    unsigned int  l1{0}, l2{0}, l3{0}, l4{0}, l5{0}, l6{0}, l7{0}, l8{0}, l9{0}, l10{0}, l11{0}, l12{0};
};

#endif // MAINWINDOW_H
