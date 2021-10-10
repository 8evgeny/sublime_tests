// Исходная текстовая строка:
var text="Мы изучаем JavaScript"
document.write("<b>"+text+"</b><br>")
// Обращение к символам строки через индекс:
for(var k=11;k<text.length;k++){
   document.write(text[k])
}
// Использование метода slice():
document.write("<br>"+text.slice(0,10))
document.write("<br>"+text.slice(11))
// Использование метода substring():
document.write("<br>"+text.substring(11))
// Использование метода substr():
document.write("<br>"+text.substr(11))
// Использование метода toUpperCase():
document.write("<br>"+text.toUpperCase())
// Использование метода toLowerCase():
document.write("<br>"+text.toLowerCase())
// Использование метода search():
document.write("<br>"+text.search("Java"))
// Использование метода replace():
document.write("<br>"+text.replace("изучаем","любим"))
// Исходная строка не изменилась:
document.write("<br><b>"+text+"</b>")
