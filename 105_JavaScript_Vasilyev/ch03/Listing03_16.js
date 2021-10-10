// Первая функция:
function first(){
   document.write("Первая функция<br>")
}
// Вторая функция:
function second(){
   document.write("Вторая функция<br>")
}
// Вызов функций:
first()
second()
// Переменная:
var tmp
// Обмен значениями:
tmp=first
first=second
second=tmp
// Вызов функций:
first()
second()