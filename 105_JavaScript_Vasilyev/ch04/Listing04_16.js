// Конструктор:
function MyObj(){
   this.number=0
}
// Объект:
var A=new MyObj()
// Определение конструктора через объект:
var F=A.constructor
// Создание объекта:
var B=new F()
// Проверка значения свойства number объекта:
document.write("Свойство B.number = "+B.number+"<br>")
// Новый объект:
A={}
// Определение конструктора:
F=A.constructor
// Проверка объекта конструктора:
document.write("F==Object -> "+(F==Object)+"<br>")
// Создание объекта с помощью анонимного конструктора:
A=new function(){
   this.name="объект"
}()
// Определение конструктора:
F=A.constructor
// Создание объекта:
B=new F()
// Проверка значения свойства name объекта:
document.write("Свойство B.name = "+B.name)