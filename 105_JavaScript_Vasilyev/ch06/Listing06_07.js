// Метод toString() определяется
// в прототипе верхнего уровня:
Object.prototype.toString=function(){
   var t="<u>Собственные свойства объекта:</u><br>"
   for(var s in this){
      t+="<b>"+s+"</b>: "+this[s]+"</br>"
   }
   return t
}
// Метод valueOf() определяется
// в прототипе верхнего уровня:
Object.prototype.valueOf=function(){
   return Object.keys(this).length
}
// Первый объект:
var A={one:100,two:200,three:300,four:400,five:500}
// Неявный вызов метода toString() при отображении
// свойств объекта:
document.write(A)
// Неявный вызов метода valueOf() для определения
// количества собственных свойств у объекта:
document.write("Количество свойств в объекте - "+A+"<br>")
// Второй объект:
var B={first:"первый",second:"второй",third:"третий"}
// Неявный вызов метода toString() при отображении
// свойств объекта:
document.write(B)
// Неявный вызов метода valueOf() для определения
// количества собственных свойств у объекта:
document.write("Количество свойств в объекте - "+B+"<br>")
// Функция-конструктор:
function Person(name,age,gender){
   // Локальная переменная:
   var g
   // Определение значения локальной переменной:
   if(gender){
      g="муж."
   }
   else{
      g="жен."
   }
   // Значение свойства name:
   this.name=name
   // Значение свойства age:
   this.age=age
   // Свойство gender доступно только для считывания:
   Object.defineProperty(this,"gender",{
      get:function(){
         return g
      }
   })
}
// Определение метода toString() для
// прототипа конструктора Person:
Person.prototype.toString=function(){
   var t="<u>Персональные данные:</u><br>"
   t+="<b>Имя:</b> "+this.name+"<br>"
   // Неявный вызов метода valueOf():
   t+="<b>Возраст:</b> "+this+" лет<br>"
   t+="<b>Пол:</b> "+this.gender+"<br>"
   return t
}
// Определение метода valueOf() для
// прототипа конструктора Person:
Person.prototype.valueOf=function(){
   return this.age
}
// Объекты создаются с помощью конструктора Person:
var X=new Person("Ирина",20,false)
var Y=new Person("Андрей",25,true)
// Неявный вызов метода toString() для объектов, созданных
// с помощью конструктора Person:
document.write(X)
document.write(Y)
// Неявный вызов метода valueOf() для объектов, созданных
// с помощью конструктора Person:
document.write("Возраст Ирины - "+X+" лет<br>")
document.write("Возраст Андрея - "+Y+" лет")