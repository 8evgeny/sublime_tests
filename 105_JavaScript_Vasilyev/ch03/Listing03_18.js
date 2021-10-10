// Объявляются переменные:
var k,n=6,rnd,color
// Оператор цикла:
for(k=1;k<=n;k++){
   // Генерирование случайного числа:
   rnd=Math.random()
   // Создание функции:
   if(rnd<0.2){
      color=function(){
               document.write("Красный<br>")
            }
   }
   else{
      if(rnd<0.5){
         color=function(){
                  document.write("Желтый<br>")
               }
      }
      else{
         color=function(){
                  document.write("Зеленый<br>")
               }
      }
   }
   // Вызов случайной функции:
   color()
}