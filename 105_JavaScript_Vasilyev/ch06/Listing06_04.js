// Оператор цикла:
for(var x=-1;x<=1;x+=2){
   // Внешний try-catch блок:
   try{
   document.write("Начало внешнего <code>try-catch</code> блока<br>")
      // Внутренний try-catch блок:
      try{
         document.write("Начало внутреннего <code>try-catch</code> блока<br>")
         // Создание массива (возможна ошибка RangeError):
         var A=new Array(x)
         // Некорректная команда:
         var B=C
      }
      // Внутренний обработчик:
      catch(e){
         // Если ошибка RangeError:
         if(e.name=="RangeError"){
            e.message="Неверный размер массива (ошибка <code>RangeError</code>)"
            // Повторное генерирование исключения:
            throw e
         }
         document.write("Некорректное присваивание<br>")
      }
      // Блок выполняется в любом случае:
      finally{
         document.write("Завершение внутреннего <code>try-catch</code> блока<br>")
      }
      document.write("Ошибки <code>RangeError</code> не было<br>")
   }
   // Внешний обработчик:
   catch(err){
      document.write(err.message+"<br>")
   }
   document.write("Завершение внешнего <code>try-catch</code> блока<hr>")
} // Завершение оператора цикла