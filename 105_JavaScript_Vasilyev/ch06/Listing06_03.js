// �������� ������:
var A=[2,5,9,1,0,3,7,8,6,4]
// ��������������� ����������:
var num
// �������� �����:
for(var k=0;k<A.length;k++){
   // �������� ����������:
   num=A[k]
   // ������ try-����:
   try{
      if(num==0){
         // ������������ ������. ������ ������ - �����:
         throw "������� ��������"
      }
      // ������� �����������, ���� �� ������������� ������:
      document.write("�������� �� ���� �����: "+num+"<br>")
   }
   // ��������� ������ (������ ������ - �����):
   catch(e){
      document.write("��������: "+e+"<hr>")
      // ���������� �������� ����� � �������
      // � ���������� �����:
      continue
   }
   // ������ try-����:
   try{
      if(num%3==0){
         // ������������ ������. ������ ������
         // ��������� ������������� Error:
         throw new Error("����� ������� �� ���")
      }
   }
   // ��������� ������ (������ ������ ������������� Error):
   catch(e){
      document.write(e.message)
   }
   // ����������� �������������� �����:
   document.write("<hr>")
} // ���������� ��������� �����