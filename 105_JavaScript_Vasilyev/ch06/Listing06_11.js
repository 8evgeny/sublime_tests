// Функция с указателем this описана вне объекта:
function f(text,number){
   this.text=text
   this.number=number
}
// Объекты:
var A={}
var B={show:function(){
   for(var s in this){
      document.write(s+": "+this[s]+"<br>")
   }
}}
var C={}
C.method=f
// Вызов функции:
f("функция",100)
// Вызов из объекта функции метода call():
f.call(A,"объект А",200)
// Вызов из объекта функции метода apply():
f.apply(B,["объект B",300])
// Вызов метода объекта:
C.method("объект C",400)
// Проверка значений глобальных 
// переменных и свойств объектов:
document.write(text+" | "+number+"<br>")
document.write(A.text+" | "+A.number+"<br>")
document.write(B.text+" | "+B.number+"<br>")
document.write(C.text+" | "+C.number+"<br>")
// Проверка наличия у объектов метода f():
document.write(("f" in A)+"<br>")
document.write(("f" in B)+"<br>")
document.write(("f" in C)+"<br>")
// Проверка свойств и методов объектов:
document.write("<b>Объект B:</b><br>")
B.show()
document.write("<b>Объект A:</b><br>")
B.show.call(A)
document.write("<b>Объект C:</b><br>")
B["show"].call(C)