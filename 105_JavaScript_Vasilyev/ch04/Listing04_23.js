// Создание объекта:
var z={re:3,im:4}
// Добавление в объект свойства abs с режимом доступа:
Object.defineProperty(z,"abs",{
   get:function(){
      return Math.sqrt(this.re*this.re+this.im*this.im)
   }
})
// Отображение результата вычислений:
document.write("z = "+z.re+" + "+z.im+"i<br>")
document.write("|z| = "+z.abs)