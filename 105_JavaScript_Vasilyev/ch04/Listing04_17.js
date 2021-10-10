// Создание объекта:
var A={number:100}
// Добавление свойства в прототип:
Object.prototype.name="объект А"
for(var a in A){
   document.write(a+" | ")
}
// Проверка наличия у объекта свойств:
test('"toString" in A')
test('"valueOf" in A')
test('"constructor" in A')
// Функция для проверки наличия свойства у объекта:
function test(txt){
   document.write("<br>"+txt+" -> "+eval(txt))
}