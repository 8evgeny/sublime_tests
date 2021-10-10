// Создание объекта obj со свойствами name и age,
// а также методом show():
var obj={name:"Иван Петров",
         age:38,
         show:function(){
            document.write("<b>Имя</b>: "+this.name+"<br>")
            document.write("<b>Возраст</b>: "+this.age+"<br>")
         }
}
// Отображение значений свойств объекта:
obj.show()
// Новые значения свойств объекта:
obj.name="Петр Иванов"
obj.age++
// Отображение новых значений свойств объекта:
obj.show()