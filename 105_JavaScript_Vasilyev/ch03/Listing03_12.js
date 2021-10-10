// Функция для вычисления чисел Фибоначчи:
function fibs(n){
   // Первое или второе число:
   if(n==1||n==2){
      return 1
   }
   // Прочие числа:
   else{
      return fibs(n-1)+fibs(n-2)
   }
}
document.write("<h4>Числа Фибоначчи</h4>")
// Вычисление чисел Фибоначчи:
for(var k=1;k<=10;k++){
   document.write(fibs(k)+"  ")
}