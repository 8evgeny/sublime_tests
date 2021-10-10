// Создание объекта:
var objA={name:"Иван Петров",
          age:38,
          show:function(){
             document.write("<u>Имя</u>: "+this.name+"<br>")
             document.write("<u>Возраст</u>: "+this.age+"<br>")
          }
}
// Отображение значений свойств объекта objA:
document.write("<b>Объект objA:</b><br>")
objA.show()
// Присваивание объекта значением переменной:
var objB=objA
// Отображение значений свойств объекта objB:
document.write("<b>Объект objB:</b><br>")
objB.show()
// Новые значения свойств объекта objA:
objA.name="Петр Иванов"
objA.age++
// Отображение новых значений свойств объекта objA:
document.write("<b>Объект objA:</b><br>")
objA.show()
// Отображение значений свойств объекта objB:
document.write("<b>Объект objB:</b><br>")
objB.show()