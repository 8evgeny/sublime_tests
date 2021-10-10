try{
   document.write("Начало выполнения <code>try</code>-блока<br>")
   var txt=prompt("Введите выражение для вычисления:")
   document.write("Результат вычисления выражения: "+eval(txt)+"<br>")
   document.write("Выполнение <code>try</code>-блока завершено<br>")
}
catch(e){
   // Название ошибки
   var name=e.name
   // Описание ошибки:
   var message=e.message
   // Текст для отображения:
   var str
   // Проверка типа ошибки:
   switch(name){
      case "ReferenceError":
         str="Некорректная ссылка"
         break
      case "SyntaxError":
         str="Синтаксическая ошибка"
         break
      default:
         str="Ошибка "+name
   }
   // Отображение характеристик ошибки:
   document.write("<b>Внимание! Произошла ошибка!</b><br>")
   document.write("<b>Тип ошибки: </b>"+str+"<br>")
   document.write("<b>Описание ошибки: </b>"+message+"<br>")
   // Для Mozilla Firefox:
   if("fileName" in e){
      document.write("<b>Файл с ошибкой: </b>"+e.fileName+"<br>")
   }
}
document.write("Выполнение сценария завершено")