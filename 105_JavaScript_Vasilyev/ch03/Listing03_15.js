// ����� �������:
show("������� show()")
// ����������� ����������:
var f
// ���������� ������������� �������:
f=show
f("������ ��� ������� f()")
// ������� ��������� ������������� �����:
show="��������� ��������"
document.write(show+"<br>")
f("����� ������� f()")
// �������� �������:
function show(msg){
   document.write(msg+"<br>")
}