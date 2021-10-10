// Функция с результатом - функцией:
function makePolynom(a,b,c){
   // Результат функции:
   return function(x){
             // Результат анонимной функции:
             return a+b*x+c*x*x
          }
} // Окончание описания функции
// Переменные:
var P,Q
// Первый полином:
P=makePolynom(1,2,1)
// Второй полином:
Q=makePolynom(2,-1,1)
// Аргумент для полиномов:
var z=2
// Вычисление значений полиномов:
document.write("P("+z+") = "+P(z)+"<br>")
document.write("Q("+z+") = "+Q(z)+"<br>")