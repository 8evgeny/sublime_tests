// Описание функции:
function f(x){
   // Если x<0
   if(x<0){
      return 0
   }
   // Если x>=0
   else{
      // Если x<2
      if(x<2){
         return x*x
      }
      // Если x>=2
      else{
         // Если x<5
         if(x<5){
            return 6-x
         }
         // Если x>=5
         else{
            return 1
         }
      }
   }
} // Окончание описания функции

document.write("<h4>Кусочно-гладкая функция</h4>")
// Добавление графика функции в документ:
document.write('<img src="function.jpg" width="500" height="300"><br>')
// Переменная для записи значения аргумента:
var z
// Значение аргумента - случайное число (от -2 до 7):
z=9*Math.random()-2
document.write("Случайный аргумент:  <b>"+z+"</b><br>")
// Вызов функции:
document.write("Значение функции:  <b>"+f(z)+"</b>")