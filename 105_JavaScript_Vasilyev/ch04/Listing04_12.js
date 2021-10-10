// Вспомогательная текстовая переменная: 
var txt='"name" in Math'
// Проверка наличия свойства name у объекта Math:
document.write(txt+" -> "+eval(txt)+"<br>")
// Первый объект:
var A={color:"красный"}
// Второй объект:
var B=new Object()
// Добавление свойства number в объект B:
B.number=100
// Отображаются свойства объектов:
showAll()
// Добавляется свойство name в прототип Object.prototype:
Object.prototype.name="объект А"
// Проверка наличия свойства name у объекта Math:
document.write(txt+" -> "+eval(txt)+"<br>")
// Отображаются свойства объектов:
showAll()
// Добавляется свойство name в объект B:
B.name="объект B"
// Отображается значение свойства name объекта Math:
document.write("Math.name -> "+Math.name+"<br>")
// Отображаются свойства объектов:
showAll()
// Удаление свойства name у прототипа Object.prototype:
delete Object.prototype.name
// Проверка наличия свойства name у объекта Math:
document.write(txt+" -> "+eval(txt)+"<br>")
// Отображаются свойства объектов:
showAll()
// Функции для отображения свойств объектов:
function show(obj){
   for(var s in obj){
      document.write(s+" -> "+obj[s]+" | ")
   }       
   document.write("<br>")
}
function showAll(){
   document.write("Объект А: ")
   show(A)
   document.write("Объект B: ")
   show(B)
   document.write("<br>")
}