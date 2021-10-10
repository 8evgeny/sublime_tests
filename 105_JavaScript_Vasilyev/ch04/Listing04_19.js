// Создание пустого объекта:
var A={}
// Добавление свойства number:
Object.defineProperty(A,"number",{value:100,enumerable:true,writable:true,configurable:true})
// Объект-дескриптор нового свойства:
var descriptor={value:"объект А",enumerable:true,writable:true,configurable:true}
// Добавление свойства name:
Object.defineProperty(A,"name",descriptor)
// Отображение свойств объекта A:
show(A)
// Изменение атрибутов свойства number:
Object.defineProperty(A,"number",{value:200,enumerable:false})
// Отображение свойств объекта A:
show(A)
// Отображение значения свойства number:
document.write("A.number = "+A.number)
// Функция для отображения свойств объекта:
function show(obj){
   document.write("{|")
   for(var s in obj){
      document.write(" <b>"+s+"</b> : "+obj[s]+" |")
   }
   document.write("}<br>")
}