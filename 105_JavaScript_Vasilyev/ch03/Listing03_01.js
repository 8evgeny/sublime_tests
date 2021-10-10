makeHeader("Знакомимся с функциями")
// Функция для генерирования случайных чисел и записи
// и в текстовую строку:
function getRandText(n){
   var txt="Случайные целые числа (от 1 до 10):<br>* "
   for(var k=1;k<=n;k++){
      txt+=myRand()+" * "
   }
   txt+="<br>"
   return txt
}
// Отображение 20-ти случайных чисел:
document.write(getRandText(20))
// Функция для генерирования случайных целых чисел:
function myRand(){
   return 1+Math.floor(10*Math.random())
}
// Функция для отображения заголовка:
function makeHeader(t){
   document.write("<h4>"+t+"</h4>")
}