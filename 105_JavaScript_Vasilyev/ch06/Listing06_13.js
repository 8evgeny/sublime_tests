// Функция с одним аргументом:
function zero(txt){
   document.write("<b>"+txt+"</b><hr>")
}
// Метод toString() для объекта функции zero():
zero.toString=function(){
   var t="Название функции - zero<br>"
   t+="Количество аргументов - "+this.length+"<br>"
   return t
}
// Метод с одним аргументом:
function one(txt){
   document.write("<b>"+txt+"</b><br>")
   for(var s in this){
      document.write(this[s]+"<br>")
   }
   document.write("<hr>")
}
// Метод toString() для объекта метода one():
one.toString=function(){
   var t="Метод one()<br>"
   t+="Количество аргументов - "+this.length+"<br>"
   return t
}
// Пустой массив:
var A=[]
// Первый (начальный) элемент массива:
A[0]=zero
// Второй (с индексом один) элемент массива:
A[1]=one
// Вызов функции (первый элемент массива):
A[0]("Начальный элемент массива")
// Вызов метода (второй элемент массива):
A[1]("Элемент с единичным индексом")
