// Функция - конструктор объектов:
function Fellow(name,age){
   // Значение свойства name:
   this.name=name
   // Значение свойства age:
   this.age=age
   // Метод show():
   this.show=function(){
      document.write("<b>Имя</b>: "+this.name+"<br>")
      document.write("<b>Возраст</b>: "+this.age+"<br>")
   }
}
// Создание объектов с помощью конструктора:
var objA=new Fellow("Иван Петров",38)
var objB=new Fellow("Петр Иванов",39)
// Проверка значений полей объектов:
objA.show()
objB.show()