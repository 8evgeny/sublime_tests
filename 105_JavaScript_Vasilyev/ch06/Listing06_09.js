// Функция для проверки количества аргументов,
// указанных при описании функции:
function testArgs(func){
   // Количество аргументов функции:
   var n=func.length
   var words
   // Определение значения текстовой переменной:
   switch(n){
      case 0:
         words="нет аргументов."
         break
      case 1:
         words="один аргумент."
         break
      case 2:
      case 3:
      case 4:
         words=n+" аргумента."
         break
      default:
         words=n+" аргументов."   
   }
   document.write("Функция "+func+": "+words+"<br>")
}
// Вспомогательная функция без аргументов:
function show(){
   document.write("Всем привет!")
}
// Вспомогательная функция с шестью аргументами:
function F(a,b,c,d,e,f){
   return a*b*c*d*e*f
}
// Проверка количества аргументов функции:
testArgs(eval)
testArgs(Math.pow)
testArgs(show)
testArgs(F)
// Функция возвращает результатом ту из функций,
// у которой при описании указано меньше аргументов:
function getFunc(f1,f2){
   if(f1.length<=f2.length){
      return f1
   }
   else{
      return f2
   }
}
// Примеры вызова функции getFunc():
var x=getFunc(Math.pow,F)(2,3)
document.write(x+"<br>")
getFunc(show,eval)()