document.write("<h4>Удаление свойств и методов</h4>")
// Создание объекта:
var colors={
   red:"красный",
   yellow:"желтый",
   green:"зеленый",
   show:function(){
      with(document){
         write("Свойства и методы объекта:<br>")
         for(var s in this){
            write(s+" | ")
         }
         write("<hr>")
      }
   }
} // Окончание описания объекта
// Отображение списка свойств:
colors.show()
// Удаление свойства red:
delete colors.red
// Отображение списка свойств:
colors.show()
// Удаление свойства yellow:
delete colors.yellow
// Отображение списка свойств:
colors.show()
// Удаление метода show():
delete colors.show
// Проверка наличия у объекта метода show:
var tst='"show" in colors'
document.write(tst+" -> "+eval(tst)+"<br>")
// Проверка наличия у объекта свойства green:
tst='"green" in colors'
document.write(tst+" -> "+eval(tst))