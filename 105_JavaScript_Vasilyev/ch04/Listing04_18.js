// Создание объекта:
var A={number:100}
// Дескриптор свойства number:
var descriptor=Object.getOwnPropertyDescriptor(A,"number")
// Отображение свойств объекта A:
show(A)
// Отображение свойств объекта descriptor:
show(descriptor)
// Функция для отображения свойств объекта:
function show(obj){
   document.write("{| ")
   for(var s in obj){
      document.write(" <b>"+s+"</b> : "+obj[s]+" |")
   }
   document.write("}<br>")
}