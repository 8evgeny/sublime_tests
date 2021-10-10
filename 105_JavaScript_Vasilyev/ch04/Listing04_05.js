// Создание пустого объекта:
var obj={}
// Добавление свойства name:
obj.name="Иван Петров"
// Добавление свойства age:
obj.age=38
// Добавление метода show():
obj.show=function(){
   document.write("<b>Имя</b>: "+this.name+"<br>")
   document.write("<b>Возраст</b>: "+this.age+"<br>")
}
// Отображение значений свойств объекта:
obj.show()