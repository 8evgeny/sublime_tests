#include <graphics.h>
#include <conio.h>
main()
{
initwindow (440, 300);
setfillstyle (1, 9);
bar (100,100,300,200); // синий прямоугольник
setcolor (13); // с фиолетовой рамкой
rectangle (100,100,300,200);
moveto (100,100); // крыша-ломаная
lineto (200, 50);
lineto (300,100);
setfillstyle (1, 14); // зальем крышу желтым
floodfill (200, 75, 13);
setcolor (15);
circle (200, 150,50); // белая окружность
setfillstyle (1, 10);
floodfill (200,150, 15); // зеленая заливка
setcolor (12);
//outtextxy (100, 230, "Sharik's house.");
getch();
closegraph();
}
