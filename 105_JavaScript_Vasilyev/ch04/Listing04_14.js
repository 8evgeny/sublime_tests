// Пустой объект с прототипом:
var A={}
// Пустой объект без прототипа:
var B=Object.create(null)
// Пустой объект с явно указанным прототипом:
var C=Object.create(B)
// Добавление свойства number в объект B:
B.number=100
// Добавление свойства name в прототип верхнего уровня:
Object.prototype.name="Объект А"
// Отображение свойств объектов:
show(A)
show(B)
show(C)
// Функция для отображения свойств объекта:
function show(obj){
   for(var s in obj){
      document.write(s+" -> "+obj[s])
   }
   document.write("<br>")
}