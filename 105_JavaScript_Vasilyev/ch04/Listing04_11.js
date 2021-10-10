// Объект для использования в качестве прототипа:
var X={
   color:"красный",
   number:123,
   show:function(arg){
      document.write("<b>"+arg+"</b>: ")
      for(var s in this){
         if(s!="show"){
            document.write(s+" -> "+this[s]+" | ")
         }
      }
      document.write("<br>")
   }
} // Окончание описания объекта-прототипа
// Первый объект:
var A=Object.create(X)
// Второй объект:
var B=Object.create(X)
// Проверяем свойства объектов:
showAll()
// Присваиваем новые значения свойствам объектов:
A.color="желтый"
A.number=321
B.color="зеленый"
// Проверяем свойства объектов:
showAll()
// Добавление свойства name в объект-прототип:
X.name="прототип"
// Добавление свойства state в первый объект:
A.state=true
// Проверяем свойства объектов:
showAll()
// Удаляем свойство number объекта-прототипа:
delete X.number
// Удаляем свойство color первого объекта:
delete A.color
// Проверяем свойства объектов:
showAll()
// Функция для отображения свойств объектов:
function showAll(){
   X.show("X")
   A.show("A")
   B.show("B")
   document.write("<hr>")
}