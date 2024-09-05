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
    void drawPoints();
    void r1l1();
    void r2l2();
    void r3l3();
    void r4l4();
    void r5l5();
    void r6l6();
    void r7l7();
    void r8l8();
    void r9l9();
    void r10l10();
    void r11l11();
    void r12l12();
    void on_button_save_clicked();
    void on_button_load_clicked();
    void saveData();
    float calcCornerLine(float input);
    void on_Izmereniye_editingFinished();
    void calculateLetters();
    std::string calculateLetter(float r, float l);
    void diagnostic();
    void channel_P();
    void channel_MC();
    void channel_C();
    void channel_IG();
    void channel_TR();
    void channel_GI();
    void channel_RP();
    void channel_F();
    void channel_R();
    void channel_V();
    void channel_VB();
    void channel_E();

    void on_textEdit_textChanged();


private:
    Ui::MainWindow *ui;
    QString name_field{""};
    QString  Date;
    std::string  nameOutFile;
    float averadge;
    float averadgeY;
    float hight;
    float low;
    float delta = 0.0;
    std::string Channel_P, Channel_MC, Channel_C, Channel_IG, Channel_TR, Channel_GI, Channel_RP, Channel_F, Channel_R, Channel_V, Channel_VB, Channel_E;
    unsigned int izmereniye{1};
    unsigned int  r1x{123}, l1x{181};
    unsigned int  r2x{208}, l2x{267};
    unsigned int  r3x{294}, l3x{353};
    unsigned int  r4x{380}, l4x{439};
    unsigned int  r5x{466}, l5x{524};
    unsigned int  r6x{551}, l6x{610};
    unsigned int  r7x{638}, l7x{696};
    unsigned int  r8x{724}, l8x{782};
    unsigned int  r9x{809}, l9x{868};
    unsigned int  r10x{896}, l10x{954};
    unsigned int  r11x{981}, l11x{1040};
    unsigned int  r12x{1067}, l12x{1126};
    unsigned int  corner_x_begin{80}, corner_x_end{1150};
    unsigned int  r1y{0}, r2y{0}, r3y{0}, r4y{0}, r5y{0}, r6y{0}, r7y{0}, r8y{0}, r9y{0}, r10y{0}, r11y{0}, r12y{0};
    unsigned int  l1y{0}, l2y{0}, l3y{0}, l4y{0}, l5y{0}, l6y{0}, l7y{0}, l8y{0}, l9y{0}, l10y{0}, l11y{0}, l12y{0};
    unsigned int  r1{0}, r2{0}, r3{0}, r4{0}, r5{0}, r6{0}, r7{0}, r8{0}, r9{0}, r10{0}, r11{0}, r12{0};
    unsigned int  l1{0}, l2{0}, l3{0}, l4{0}, l5{0}, l6{0}, l7{0}, l8{0}, l9{0}, l10{0}, l11{0}, l12{0};
    std::string diagnosic_message {"\nДиагноз:\n"};
    std::string comment_message {""};
};

#endif // MAINWINDOW_H
