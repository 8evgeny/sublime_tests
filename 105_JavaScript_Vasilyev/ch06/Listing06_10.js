// Функция для вычисления суммы аргументов:
function sum(){
   // Локальная переменная для вычисления суммы:
   var s
   // Начальное значение локальной переменной:
   if((arguments.length>0)&&(typeof(arguments[0])=="string")){
      s=""
   }
   else{
      s=0
   }
   // Вычисление суммы:
   for(var k=0;k<arguments.length;k++){
      s+=arguments[k]
   }
   // Результат:
   return s
}
// Примеры вызова функции:
document.write("Сумма чисел: "+sum(1,4,2,7,3)+"<br>")
document.write("Сумма чисел: "+sum(1,2,3)+"<br>")
document.write("Сумма чисел: "+sum()+"<br>")
document.write("Сумма слов: "+sum("один"," четыре"," два"," семь"," три"))