// Текущая дата и время:
var today=new Date()
// Следующий день:
var tomorrow=new Date(today)
tomorrow.setDate(tomorrow.getDate()+1)
// Предыдущий день:
var yesterday=new Date(today)
yesterday.setDate(yesterday.getDate()-1)
// Через месяц:
var monthAfter=new Date(Date.now())
monthAfter.setMonth(monthAfter.getMonth()+1)
// Через год:
var yearAfter=new Date(Date.now())
yearAfter.setFullYear(yearAfter.getFullYear()+1)
// Отображение дат:
document.write("<b>Сегодня:</b> "+today+"<br>")
document.write("<u>Год:</u> "+today.getFullYear()+"<br>")
document.write("<u>Дата:</u> "+today.toLocaleDateString()+"<br>")
document.write("<u>Время:</u> "+today.toLocaleTimeString()+"<br>")
document.write("<b>Завтра:</b> "+tomorrow+"<br>")
document.write("<b>Вчера:</b> "+yesterday+"<br>")
document.write("<b>Через месяц:</b> "+monthAfter+"<br>")
document.write("<b>Через год:</b> "+yearAfter+"<br>")
// Время встречи (явно задаем дату и время):
var meeting=new Date(2015,8,30,8,0,0)
// Отображение дат:
document.write("<b>Сегодня:</b> "+today.toLocaleString()+"<br>")
document.write("<b>Время и дата встречи:</b> "+meeting.toLocaleString()+"<br>")
// Изменение даты:
meeting.setDate(meeting.getDate()+1)
// Отображение новой даты:
document.write("<b>Новое время и дата встречи:</b> "+meeting.toLocaleString()+"<br>")
// Время до встречи (в миллисекундах):
document.write("<u>До встречи:</u> "+(meeting-today)+" миллисекунд<br>")
// Время до встречи (в днях):
document.write("<u>До встречи:</u> "+Math.round((meeting-today)/1000/60/60/24)+" дней<br>")