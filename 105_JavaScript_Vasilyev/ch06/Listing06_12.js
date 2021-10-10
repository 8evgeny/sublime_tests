// Функция результатом возвращает функцию,
// переданную аргументом:
function caller(func){
   return func
}
// Функция отображает значение переданного ей аргумента:
function show(txt){
   document.write(txt+"<br>")
}
// Объект со свойством text, методом hi()
// и переопределенным методом toString():
var obj={text:"объект obj",hi:function(){
      document.write(this.text+"<br>")
   },
   toString:function(){
      return this.text
   }
}
// Вызов функций show() через функцию caller():
caller(show)("функция show()")
obj.hi() // Вызов метода объекта
// Неудачная попытка вызвать 
// метод hi() через функцию caller():
caller(obj.hi)()
// Вызов метода hi() через функцию caller():
caller(obj.hi.bind(obj))()
// Определение новой функции на основе метода:
var powerOfTwo=Math.pow.bind(Math,2)
var n=5
document.write("2<sup>"+n+"</sup> = "+powerOfTwo(n)+"<br>")
// Вспомогательная функция с ключевым словом this в теле:
function f(x){
   return this+x
}
// Определение новых функций на основе
// вспомогательной функции:
var one=f.bind(10)
var two=f.bind(obj)
// Вызов функций:
document.write(one(5)+"<br>")
document.write(two(" - это он")+"<br>")
// Новое значение свойства text объекта obj:
obj.text="тот же объект"
// Вызов функции:
document.write(two(" - новое значение")+"<br>")