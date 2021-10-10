// Функция для вычисления производной:
function diff(f,x,dx){
   // Результат функции:
   return (f(x+dx)-f(x))/dx
}
// Функция для передачи аргументом:
function G(x){
   // Значение функции:
   return x*x+x
}
// Точное значение производной:
function g(x){
   return 2*x+1
}
document.write("<h4>Вычисление производной</h4>")
// Вычисление производной:
for(var z=0;z<=2;z+=0.5){
   document.write(g(z)+"  vs.  "+diff(G,z,0.001)+"<br>")
}