// Конструктор для объекта ошибки:
function MyError(id,message){
   // Свойство id:
   this.id=id
   // Свойство message:
   this.message=message || "Ошибка пользовательского типа"
}
// Прототип для объектов ошибки пользовательского типа:
MyError.prototype=Object.create(Error.prototype)
// Свойство name прототипа:
MyError.prototype.name="MyError"
// Метод toString() прототипа:
MyError.prototype.toString=function(){
   // Локальная переменная с текстовым значением:
   var t=this.message+": "+this.name+". "
   t+="Код ошибки: "+this.id+"."
   // Результат метода:
   return t
}
// Конструктор для объектов ошибок пользовательского типа:
MyError.prototype.constructor=MyError
// Контролируемый код (внешний блок):
try{
   // Контролируемый код (внутренний блок):
   try{
      // Генерирование исключения пользовательского типа:
      throw new MyError(200,"Рукотворная ошибка")
   }
   // Обработка исключения (внутренний блок):
   catch(e){
      document.write(e+"<br>")
      // Генерирование ошибки:
      throw new e.constructor(100)
   }
}
// Обработка исключения (внешний блок):
catch(e){
   document.write(e)
}