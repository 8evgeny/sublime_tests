// Первый объект (создается на основе Math):
var A=Object.create(Math)
// Второй объект (создается на основе A):
var B=Object.create(A)
// Третий объект (создается на основе B):
var C=Object.create(B)
// Четвертый объект (создается на основе C):
var D=Object.create(C)
// Добавление метода f() в прототип объекта A:
Object.getPrototypeOf(A).f=function(x){
   return 2*x+1
}
// Переменная с целочисленным значением:
var t=2
// Вызов метода f() из объекта Math:
document.write("Функция f("+t+") = "+Math.f(t)+"<br>")
// Новое значение переменной t:
t=3
// Вызов метода f() из объекта D:
document.write("Функция f("+t+") = "+D.f(t)+"<br>")
// Ссылка на прототип прототипа объекта D:
var obj=Object.getPrototypeOf(Object.getPrototypeOf(D))
// Проверка равенства объектов:
document.write("obj == B -> "+(obj==B)+"<br>")