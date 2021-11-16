USE [limdb]
GO
/****** Object:  StoredProcedure [dbo].[TOTAL_PLAN_PBC]    Script Date: 09.02.2021 10:15:39 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO







ALTER procedure [dbo].[TOTAL_PLAN_PBC]
  @dtDate datetime, 
  @dtDateTo datetime,
  @Date1 datetime,
  @num_of_day numeric
as
  
 declare 
		@ZAGRUZ_O_TEMPL1 decimal (28,3),
		@ZAGRUZ_O_TEMPL2 decimal (28,3),
		@ZAGRUZ_O_TEMPL3 decimal (28,3),
		@ZAGRUZ_O_TEMPL4 decimal (28,3),
		@ZAGRUZ_O_TEMPL5 decimal (28,3),
		@ZAGRUZ_O_TEMPL6 decimal (28,3),
		@ZAGRUZ_O_TEMPL7 decimal (28,3),
		@ZAGRUZ_O_TEMPL8 decimal (28,3),
		@ZAGRUZ_O_TEMPL9 decimal (28,3),
		@ZAGRUZ_O_TEMPL10 decimal (28,3),
		@ZAGRUZ_O_TEMPL11 decimal (28,3),
		@ZAGRUZ_O_TEMPL12 decimal (28,3),
		@ZAGRUZ_O_TEMPL13 decimal (28,3),
		@ZAGRUZ_O_TEMPL14 decimal (28,3),
		@ZAGRUZ_O_TEMPL15 decimal (28,3),
		@ZAGRUZ_O_TEMPL16 decimal (28,3),

		@ZAGRUZ_O_TEMPL17 decimal (28,3),

--колбуса / компакты
		@ZAGRUZ_O_TEMPL18 decimal (28,3),
		@ZAGRUZ_O_TEMPL19 decimal (28,3),
		@ZAGRUZ_O_TEMPL20 decimal (28,3),
		@ZAGRUZ_O_TEMPL21 decimal (28,3),
		@ZAGRUZ_O_TEMPL22 decimal (28,3),
--Престо/Полимат/ST-100 / ST-400
		@ZAGRUZ_O_TEMPL23 decimal (28,3),
		@ZAGRUZ_O_TEMPL24 decimal (28,3),
		@ZAGRUZ_O_TEMPL25 decimal (28,3),
		@ZAGRUZ_O_TEMPL26 decimal (28,3),
--Биндер/Евробинд
		@ZAGRUZ_O_TEMPL27 decimal (28,3),
		@ZAGRUZ_O_TEMPL28 decimal (28,3),

--Газета/Прочее
		@ZAGRUZ_O_TEMPL29 decimal (28,3),
		@ZAGRUZ_O_TEMPL30 decimal (28,3),
		@ZAGRUZ_O_TEMPL31 decimal (28,3),


		@FACT1 decimal (28,3),
		@FACT2 decimal (28,3),
		@FACT3 decimal (28,3),
		@FACT4 decimal (28,3),
		@FACT5 decimal (28,3),
		@FACT6 decimal (28,3),
		@FACT7 decimal (28,3),
		@FACT8 decimal (28,3),
		@FACT9 decimal (28,3),
		@FACT10 decimal (28,3),
		@FACT11 decimal (28,3),
		@FACT12 decimal (28,3),
		@FACT13 decimal (28,3),
		@FACT14 decimal (28,3),
		@FACT15 decimal (28,3),
		@FACT16 decimal (28,3),
		@FACT17 decimal (28,3),


--колбуса / компакты
		@FACT18 decimal (28,3),
		@FACT19 decimal (28,3),
		@FACT20 decimal (28,3),
		@FACT21 decimal (28,3),
		@FACT22 decimal (28,3),
--Престо/Полимат/ST-100 / ST-400
		@FACT23 decimal (28,3),
		@FACT24 decimal (28,3),
		@FACT25 decimal (28,3),
		@FACT26 decimal (28,3),
--Биндер/Евробинд
		@FACT27 decimal (28,3),
		@FACT28 decimal (28,3),

--Газета/Прочее
		@FACT29 decimal (28,3),
		@FACT30 decimal (28,3),
		@FACT31 decimal (28,3),

		@RD1 decimal (28,3),
		@RD2 decimal (28,3),
		@RD3 decimal (28,3),
		@RD4 decimal (28,3),
		@RD5 decimal (28,3),
		@RD6 decimal (28,3),
		@RD7 decimal (28,3),
		@RD8 decimal (28,3),
		@RD9 decimal (28,3),
		@RD10 decimal (28,3),
		@RD11 decimal (28,3),	
		@RD12 decimal (28,3),
		@RD13 decimal (28,3),
		@RD14 decimal (28,3),
		@RD15 decimal (28,3),
		@RD16 decimal (28,3),

		@RD17 decimal (28,3),

--колбуса / компакты
		@RD18 decimal (28,3),
		@RD19 decimal (28,3),
		@RD20 decimal (28,3),
		@RD21 decimal (28,3),
		@RD22 decimal (28,3),
--Престо/Полимат/ST-100 / ST-400
		@RD23 decimal (28,3),
		@RD24 decimal (28,3),
		@RD25 decimal (28,3),
		@RD26 decimal (28,3),
--Биндер/Евробинд
		@RD27 decimal (28,3),
		@RD28 decimal (28,3),

--Газета/Прочее
		@RD29 decimal (28,3),
		@RD30 decimal (28,3),
		@RD31 decimal (28,3),-- Horizont 


		@TMP  decimal (28,3)


begin		

select @ZAGRUZ_O_TEMPL17 = NULL

CREATE TABLE #PBC
(
 UORD  numeric       ,
 ORD   numeric       ,		
 UNZ   numeric        ,                  
 NUM   varchar (255)   ,             
 NAIM  varchar (255)    ,                                                                                                                                                                                                           
 ID_OPER numeric (10)    ,                             
 OPERNAME varchar (255)   ,                                                                                                                                                                                                                                                   
 QTY   decimal (28,3)      ,                            
 QTYTYPE   varchar (255)    ,                                     
 MEASNAME  varchar (255)     ,                                                                                                                                                                                                                                                                                          
 DEPT     varchar (255)       ,                                                                                                                                                                                                                                               
 ID_ORG    numeric             ,                 
 PROPS1     varchar (255)       ,                                                                                                                                                                                                                                               
 SUM1       decimal (28,3)       ,                        
 TIR         numeric (10)         ,                 
 DATE1 datetime,
 DATE2 datetime

)  


CREATE TABLE #SPK_PLANPOSTAVOK_UNIVERSAL_WITH_COMPONENTS
(
UNZ numeric(10),
SKREP varchar(255),
NOMER varchar(255),
NAIM varchar(255),
TIR numeric(10),
FORMAT varchar(255),
Obyom  varchar(255) ,
Pereplet varchar(255),
CLASS varchar(255),
NUM_OF_RYAD  numeric(10),                                                                                                                                                                                                                                                   
NUM_OF_STOP numeric(10),                                                                                                                                                                                                                                                          
Qty      decimal(15,3),                                     
Lst_Pripress  decimal(15,3) ,                         
Lst_Pripress_EKZ decimal(15,3)                       ,
Rol_Pripress    decimal(15,3)                        ,
Tisnenie decimal(15,3)                                ,
DA        decimal(15,3)                               ,
KD          decimal(15,3)                            ,
SAB     decimal(15,3)                                ,
EWROPAL   decimal(15,3)                              ,
ST_UP    numeric(10),                                 
Izdatel  varchar(255),                       
Plenka     varchar(255),                                                                                                                                                                                                                                                         
Klass_Formata  numeric(10),                   
Primechanie varchar(255), 
Grupa numeric(10), 
STOIMOST    decimal(15,3)                               ,
SEBEST   decimal(15,3)                                  ,
NDS     decimal(15,3) ,                                                                                                                                                                                                                                                         
MATERIAL   varchar(255),                                                                                                                                                                                                                                                     
LESSE       decimal(15,3)                               ,
QTY_PERF      decimal(15,3)                             ,
PACK         decimal(15,3)  ,
NOTE  varchar(255),
QTY_FOR_TERMOPL  decimal(15,3)                       ,
IS_TERMOPL  decimal(15,3),
KURSIV    decimal(15,3)   ,                           
QTY_FOR_COST    decimal(15,3)                           ,
MATERIAL_OBL   varchar(255),                                                                                                                                                                                                                                                
PRINT_MASH_TEXT  varchar(255),                                                                                                                                         
IS_APL_EXISTS  numeric(10),
GROUP_FIELD   varchar(255),                                                                                                                                                                                                                                                   
POLY_COST   decimal(15,5),                             
sun_ob   decimal(15,3)    ,                            
M       numeric(10),                                
chislo_tetr numeric(10),                             
kras    varchar(255),                                                                                                                                                                                                                                                        
trud   decimal(15,3)                                     ,                                                                                                                                                                                                                       
mater   decimal(15,3)                                                                                                                                                                                                            


)
insert into #SPK_PLANPOSTAVOK_UNIVERSAL_WITH_COMPONENTS
exec SPK_PLANPOSTAVOK_UNIVERSAL_WITH_COMPONENTS;1 303782, @dtDate, @dtDate,0,0,'','по типу переплета'


CREATE TABLE #PBC_TEMPLAN
(UNZ                 numeric (10),
 NOMER				 varchar (255),                                                                                                                                                                                                                                                         
 NAIM				 varchar (255),                                                                                                                                                                                                                                                        
 TIR				 numeric (10),                                                                                                                                                                                                                                                       
 FORMAT				 varchar (255) ,                                                                                                                                                                                                                                                      
Obyom				 varchar (255),                                                                                                                                                                                                                                                       
Pereplet			 varchar (255),                                                                                                                                                                                                                                                     
CLASS				 numeric (10) ,                                                                                                                                                                                                                                           
NUM_OF_RYAD			 numeric (10) ,                                                                                                                                                                                                                                        
NUM_OF_STOP			 numeric (10) ,                                                                                                                                                                                                                                       
Qty					 decimal (28,3) ,                
Lst_Pripress         decimal (28,3) ,              
Lst_Pripress_EKZ     decimal (28,3) ,            
Rol_Pripress         decimal (28,3) ,            
Tisnenie             decimal (28,3) ,           
DA                   decimal (28,3) ,         
KD                   decimal (28,3) ,      
SAB                  decimal (28,3) ,  
EWROPAL              decimal (28,3) ,  
ST_UP                numeric (10)   ,
Izdatel              varchar (255)     ,
Plenka               varchar (255)      ,                                                                                                                                                                                                                              
Klass_Formata        numeric (10)        ,                                                                                                                                                                                                                            
Primechanie          varchar (255) ,
Grupa                numeric (10)   ,
STOIMOST             decimal (28,3)  ,        
SEBEST               decimal (28,3)   ,        
NDS                  decimal (28,3)    ,                                                                                                                                                                                                                              
MATERIAL             varchar (255)      ,                                                                                                                                                                                                                          
LESSE                numeric (10)        ,
                                                                                                                                                                                                               
QTY_PERF             decimal (28,3)       , 
CHISLO_TETR_W_BLOCKE  numeric (10) ,        
PACK				 numeric (10)   ,
NOTE				 varchar (255)

)

CREATE TABLE #FROM_SVODKA_EQUIP (
UORD numeric (10) ,        
UNZ numeric (10) ,        
NUM varchar (255),
NAIM varchar (255),
EQUIP varchar (255),
ID_EQUIP numeric (10) ,
QTY decimal (28,3) ,
QTY_TIR decimal (28,3) ,
DEPT varchar (255),
ID_ORG numeric (10), 
TIR numeric (10) ,
DT1 datetime ,
DT2 datetime ,
ST decimal (28,3),
QTY_OF_MATERIAL decimal (28,3),
comment varchar (255),
QTY_OF_MATERIAL2 decimal (28,3),
COMMENT2 varchar (255),
ID_EQUIP1 numeric (10),
pln decimal (28,3),
CHISLO_TETRADEY decimal (28,3),
QTY_OF_MATERIAL3 decimal (28,3),
COMMENT3 varchar (255),
LOTT decimal(20,5),
KOTT decimal(20,5)
)









insert into #FROM_SVODKA_EQUIP 
exec ZAK_VED_EQUIP_smolensk @dtDate,@dtDateTo,303782

delete from #FROM_SVODKA_EQUIP where 

(SELECT top 1 ID_ZAK_SETOPER from ZAK_TPOPER where ID_ZAK_HEAD = UNZ)=22564504 and 
(SELECT count ('1') from ZAK_TPOPER where ID_ZAK_HEAD = UNZ)=1

--select @dtDate,@dtDateTo
INSERT into #PBC
exec ZAK_VED_OPER_smolensk;1 @dtDate,@dtDateTo,303782
delete from #PBC where 

(SELECT top 1 ID_ZAK_SETOPER from ZAK_TPOPER where ID_ZAK_HEAD = UNZ)=22564504 and 
(SELECT count ('1') from ZAK_TPOPER where ID_ZAK_HEAD = UNZ)=1


 /******************************/
  select @FACT30 = sum(
 QTY*coalesce(ob,0)*
  (cast ( (left (FORMAT	,charindex ('*',FORMAT	)-1) ) as numeric ) * 
cast (left (right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)),
charindex('/',right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)))-1) as numeric))/5400 )
from
 (
 select w.QTY as QTY
 ,
 (
SELECT sum (cast (VALUE as decimal (28,3))) from ZAK_PROPS where OBJECTID in
(
select ID_ZAK_VIDS from ZAK_VIDS where o.UNZ=ZAK_VIDS.UNZ
) and CODE=511
) as ob,
(SELECT VALUE from ZAK_PROPS where OBJECTID=o.UNZ and CODE = 110) as FORMAT
 
 from ZAK_OPER o
left join ZAK_WORK w on w.ID_ZAK_OPER=o.ID
left join ZAK_PROPS p164 on p164.CODE=164 and p164.OBJECTID=o.UNZ
inner join ZAK_HEAD h on h.UNZ = o.UNZ
 where o.ID_OPER=2097846 and
 w.W_DATA between @dtDate and @dtDateTo+1-0.00001 and p164.VALUE in ('Газета') and

 not (h.KLIENT in ('Просвещение','Полиграф Трейд')) and not (upper(h.NAIM)like '%ТЕРМОУП%')
 ) as jjj
 

 






   select @FACT29 = sum(
 QTY*coalesce(ob,0)*
  (cast ( (left (FORMAT	,charindex ('*',FORMAT	)-1) ) as numeric ) * 
cast (left (right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)),
charindex('/',right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)))-1) as numeric))/5400 )
from
 (
 select w.QTY as QTY
 ,
 (
SELECT min (cast (VALUE as decimal (28,3))) from ZAK_PROPS where OBJECTID in
(
select ID_ZAK_VIDS from ZAK_VIDS where o.UNZ=ZAK_VIDS.UNZ
) and CODE=511
) as ob,
(SELECT VALUE from ZAK_PROPS where OBJECTID=o.UNZ and CODE = 110) as FORMAT
 
 from ZAK_OPER o
left join ZAK_WORK w on w.ID_ZAK_OPER=o.ID
left join ZAK_PROPS p164 on p164.CODE=164 and p164.OBJECTID=o.UNZ
inner join ZAK_HEAD h on h.UNZ = o.UNZ
 where o.ID_OPER=2097846 and p164.VALUE in ('Папка с карточками' , 'Листы','') and
 w.W_DATA between @dtDate and (@dtDateTo+1)-0.00001  and

 not (h.KLIENT in ('Просвещение','Полиграф Трейд')) and not (upper(h.NAIM)like '%ТЕРМОУП%')
 ) as jjj




 --select 'Прочие',@FACT29,'Газета', @FACT30

 /*
 select *,
  (cast ( (left (FORMAT	,charindex ('*',FORMAT	)-1) ) as numeric ) * 
cast (left (right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)),
charindex('/',right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)))-1) as numeric))/5400 
from
 (
 select w.QTY as QTY
 ,
 (
SELECT sum (cast (VALUE as decimal (28,3))) from ZAK_PROPS where OBJECTID in
(
select ID_ZAK_VIDS from ZAK_VIDS where o.UNZ=ZAK_VIDS.UNZ
) and CODE=511
) as ob,
(SELECT VALUE from ZAK_PROPS where OBJECTID=o.UNZ and CODE = 110) as FORMAT
 
 from ZAK_OPER o
left join ZAK_WORK w on w.ID_ZAK_OPER=o.ID
left join ZAK_PROPS p130 on p130.CODE=130  and  p130.OBJECTID=UNZ
inner join ZAK_HEAD h on h.UNZ = o.UNZ
 where o.ID_OPER=2097846 and
 w.W_DATA between @dtDate and @dtDateTo  and p130.VALUE in ('Газета') and

 not (h.KLIENT in ('Просвещение','Полиграф Трейд')) and not (upper(h.NAIM)like '%ТЕРМОУП%')
 ) as jjj

 order by  FORMAT

   select *,
    (cast ( (left (FORMAT	,charindex ('*',FORMAT	)-1) ) as numeric ) * 
cast (left (right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)),
charindex('/',right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)))-1) as numeric))/5400 
from
 (
 select w.QTY as QTY
 ,
 (
SELECT sum (cast (VALUE as decimal (28,3))) from ZAK_PROPS where OBJECTID in
(
select ID_ZAK_VIDS from ZAK_VIDS where o.UNZ=ZAK_VIDS.UNZ
) and CODE=511
) as ob,
(SELECT VALUE from ZAK_PROPS where OBJECTID=o.UNZ and CODE = 110) as FORMAT
 
 from ZAK_OPER o
left join ZAK_WORK w on w.ID_ZAK_OPER=o.ID
left join ZAK_PROPS p130 on p130.CODE=130 and  p130.OBJECTID=UNZ
inner join ZAK_HEAD h on h.UNZ = o.UNZ
 where o.ID_OPER=2097846 and
 w.W_DATA between @dtDate and @dtDateTo and p130.VALUE in ('Папка с карточками' , 'Листы','') and

 not (h.KLIENT in ('Просвещение','Полиграф Трейд')) and not (upper(h.NAIM)like '%ТЕРМОУП%')
 ) as jjj
  order by  FORMAT
  */
 --select 'Прочие',@FACT29,'Газета', @


 /******************************/


SELECT 
@FACT1 = sum ( QTY ) from #PBC p where PROPS1
 in ('Интегральные переплетные крышки' , '№ 7','Блоки') and 
QTYTYPE = 'за период' and ID_OPER=2097846 and 
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM) like '%ТЕРМОУП%')





--4170932 Колбус 4:
SELECT 
@FACT18 = sum ( QTY ) from #FROM_SVODKA_EQUIP p 
left join ZAK_PROPS p164 on p164.CODE=164 and p164.OBJECTID = p.UNZ
where p164.VALUE
 in ('Интегральные переплетные крышки' , '№ 7','Блоки') 
and ID_EQUIP=4170932 and 
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM) like '%ТЕРМОУП%')


--4170933 Колбус 5:
SELECT 
@FACT19 = sum ( QTY ) from #FROM_SVODKA_EQUIP p 
left join ZAK_PROPS p164 on p164.CODE=164 and p164.OBJECTID = p.UNZ
where p164.VALUE
 in ('Интегральные переплетные крышки' , '№ 7','Блоки') 
and ID_EQUIP=4170933 and 
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM) like '%ТЕРМОУП%')


--9246942	Компакт-60:
SELECT 
@FACT20 = sum ( QTY ) from #FROM_SVODKA_EQUIP p 
left join ZAK_PROPS p164 on p164.CODE=164 and p164.OBJECTID = p.UNZ
where p164.VALUE
 in ('Интегральные переплетные крышки' , '№ 7','Блоки') 
and ID_EQUIP=9246942 and 
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM) like '%ТЕРМОУП%')

--67214251	Компакт-30 (№1)  - Компакт-30:
SELECT 
@FACT21 = sum ( QTY ) from #FROM_SVODKA_EQUIP p 
left join ZAK_PROPS p164 on p164.CODE=164 and p164.OBJECTID = p.UNZ
where p164.VALUE
 in ('Интегральные переплетные крышки' , '№ 7','Блоки') 
and ID_EQUIP=67214251 and 
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM) like '%ТЕРМОУП%')

--67214251	Компакт-30 (№2)  - Компакт-30-BF:
SELECT 
@FACT22 = sum ( QTY ) from #FROM_SVODKA_EQUIP p 
left join ZAK_PROPS p164 on p164.CODE=164 and p164.OBJECTID = p.UNZ
where p164.VALUE
 in ('Интегральные переплетные крышки' , '№ 7','Блоки') 
and ID_EQUIP=135655108 and 
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM) like '%ТЕРМОУП%')



--1106418	Полимат
SELECT 
@FACT23 = sum ( QTY ) from #FROM_SVODKA_EQUIP p 
left join ZAK_PROPS p164 on p164.CODE=164 and p164.OBJECTID = p.UNZ
where p164.VALUE
 in ('№ 1') 
and ID_EQUIP=1106418 and 
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM) like '%ТЕРМОУП%')


--1106420	Престо
SELECT 
@FACT24 = sum ( QTY ) from #FROM_SVODKA_EQUIP p 
left join ZAK_PROPS p164 on p164.CODE=164 and p164.OBJECTID = p.UNZ
where p164.VALUE
 in ('№ 1') 
and ID_EQUIP=1106420 and 
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM) like '%ТЕРМОУП%')

--16808553	ST-100
SELECT 
@FACT25 = sum ( QTY ) from #FROM_SVODKA_EQUIP p 
left join ZAK_PROPS p164 on p164.CODE=164 and p164.OBJECTID = p.UNZ
where p164.VALUE
 in ('№ 1') 
and ID_EQUIP=16808553 and 
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM) like '%ТЕРМОУП%')


--150435859	ST-400
SELECT 
@FACT26 = sum ( QTY ) from #FROM_SVODKA_EQUIP p 
left join ZAK_PROPS p164 on p164.CODE=164 and p164.OBJECTID = p.UNZ
where p164.VALUE
 in ('№ 1') 
and ID_EQUIP=150435859 and 
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM) like '%ТЕРМОУП%')


--1663761	Рацио-Биндер-470
SELECT 
@FACT27 = sum ( QTY ) from #FROM_SVODKA_EQUIP p 
left join ZAK_PROPS p164 on p164.CODE=164 and p164.OBJECTID = p.UNZ
where p164.VALUE
 in ('№ 3') 
and ID_EQUIP=1663761 and 
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM) like '%ТЕРМОУП%')

--119073033	Евробинд ПРО
SELECT 
@FACT28 = sum ( QTY ) from #FROM_SVODKA_EQUIP p 
left join ZAK_PROPS p164 on p164.CODE=164 and p164.OBJECTID = p.UNZ
where p164.VALUE
 in ('№ 3') 
and ID_EQUIP=119073033 and 
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM) like '%ТЕРМОУП%')


--Horizon+BQ
SELECT 
@FACT31 = sum ( QTY ) from #FROM_SVODKA_EQUIP p 
left join ZAK_PROPS p164 on p164.CODE=164 and p164.OBJECTID = p.UNZ
where p164.VALUE
 in ('№ 3') 
and ID_EQUIP=241666927 and 
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM) like '%ТЕРМОУП%')



SELECT 
@FACT2 = sum ( QTY ) from #PBC where PROPS1
 in ('Интегральные переплетные крышки' , '№ 7','Блоки') and 
QTYTYPE = 'за период' and ID_OPER=1099966


SELECT 
@FACT5 = sum ( QTY ) from #PBC p where PROPS1
 in ('№ 1') and 
QTYTYPE = 'за период' and ID_OPER=2097846 
and 
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM)like '%ТЕРМОУП%')

 --Сдача


SELECT 
@FACT6 = sum ( QTY ) from #PBC where PROPS1
 in ('№ 1') and 
QTYTYPE = 'за период' and ID_OPER=4223890 --ВШРа

SELECT 
@FACT9 = sum ( QTY ) from #PBC p where PROPS1
 in ('№ 3') and 
QTYTYPE = 'за период' and ID_OPER=2097846 and
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM)like '%ТЕРМОУП%')

 --Сдача


SELECT 
@FACT10 = sum ( QTY ) from #PBC where PROPS1
 in ('№ 3') and 
QTYTYPE = 'за период' and ID_OPER=1106339 --Крытьё




/*******************/


SELECT  @FACT3 = sum ( QTY  * cast(p182.VALUE as decimal(25,5))  * cast(p183.VALUE as decimal(25,5)) * cast(p258.VALUE as decimal(25,5)) / 5400 )
 from #PBC p 
   left join ZAK_PROPS p258 on p258.CODE=258 and p258.OBJECTID= p.UNZ 

   left join ZAK_PROPS p182 on p182.CODE=182 and p182.OBJECTID= p.UNZ 
   left join ZAK_PROPS p183 on p183.CODE=183 and p183.OBJECTID= p.UNZ 

 where PROPS1 in ('Интегральные переплетные крышки' , '№ 7','Блоки') and 
QTYTYPE = 'за период' and ID_OPER=2097846 and
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(p.NAIM)like '%ТЕРМОУП%')
and (coalesce(p258.VALUE,'') != ''  and ISNUMERIC(p258.VALUE) = 1)
/*group by p.UNZ,
p182.VALUE,
p183.VALUE,
p258.VALUE */

/*******************/






/*расчитаем факт по сдачи в листах оттисках для твердого переплёта*/
SELECT 
@FACT3 = @FACT3 + sum(coalesce(summa,0)*coalesce(ob,0)*coalesce(koef,0))
from
(
SELECT  UNZ,summa, 
 (cast ( (left (FORMAT	,charindex ('*',FORMAT	)-1) ) as numeric ) * 
cast (left (right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)),
charindex('/',right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)))-1) as numeric))/5400 as koef,

(
SELECT sum (cast (VALUE as decimal (28,3))) from ZAK_PROPS where OBJECTID in
(
select ID_ZAK_VIDS from ZAK_VIDS where s.UNZ=ZAK_VIDS.UNZ
) and CODE=511
) ob
from
(
SELECT 
UNZ,sum ( QTY ) summa,(SELECT VALUE from ZAK_PROPS where OBJECTID=UNZ and CODE = 110) as FORMAT
 from #PBC p 
  left join ZAK_PROPS p258 on p258.CODE=258 and p258.OBJECTID= p.UNZ 
 where PROPS1

 in ('Интегральные переплетные крышки' , '№ 7','Блоки') and 
QTYTYPE = 'за период' and ID_OPER=2097846 and
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM)like '%ТЕРМОУП%') and coalesce(p258.VALUE,'') = '' 

group by UNZ
) s
) s2



/******************************************************************/
/*расчитаем факт по обработке блоков в листах оттисках для твердого переплёта*/


SELECT  @FACT3 = sum ( QTY  * cast(p182.VALUE as decimal(25,5))  * cast(p183.VALUE as decimal(25,5)) * cast(p258.VALUE as decimal(25,5)) / 5400 )
 from #PBC p 
   left join ZAK_PROPS p258 on p258.CODE=258 and p258.OBJECTID= p.UNZ 

   left join ZAK_PROPS p182 on p182.CODE=182 and p182.OBJECTID= p.UNZ 
   left join ZAK_PROPS p183 on p183.CODE=183 and p183.OBJECTID= p.UNZ 

 where PROPS1 in ('Интегральные переплетные крышки' , '№ 7','Блоки') and 
QTYTYPE = 'за период' and ID_OPER=1099966 and
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(p.NAIM)like '%ТЕРМОУП%')
and (coalesce(p258.VALUE,'') != ''  and ISNUMERIC(p258.VALUE) = 1)
/*group by p.UNZ,
p182.VALUE,
p183.VALUE,
p258.VALUE */

/*******************/

/*расчитаем факт по сдачи в листах оттисках для твердого переплёта*/


SELECT  @FACT4 = sum ( QTY  * cast(p182.VALUE as decimal(25,5))  * cast(p183.VALUE as decimal(25,5)) * cast(p258.VALUE as decimal(25,5)) / 5400 )
 from #PBC p 
   left join ZAK_PROPS p258 on p258.CODE=258 and p258.OBJECTID= p.UNZ 

   left join ZAK_PROPS p182 on p182.CODE=182 and p182.OBJECTID= p.UNZ 
   left join ZAK_PROPS p183 on p183.CODE=183 and p183.OBJECTID= p.UNZ 

 where PROPS1 in ('Интегральные переплетные крышки' , '№ 7','Блоки') and 
QTYTYPE = 'за период' and ID_OPER=1099966 and
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(p.NAIM)like '%ТЕРМОУП%')
and (coalesce(p258.VALUE,'') != ''  and ISNUMERIC(p258.VALUE) = 1)
/*group by p.UNZ,
p182.VALUE,
p183.VALUE,
p258.VALUE */

/*******************/

/*расчитаем факт по сдачи в листах оттисках для твердого переплёта*/
SELECT 
@FACT4 = @FACT4 + sum(coalesce(summa,0)*coalesce(ob,0)*coalesce(koef,0))
from
(
SELECT  UNZ,summa, 
 (cast ( (left (FORMAT	,charindex ('*',FORMAT	)-1) ) as numeric ) * 
cast (left (right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)),
charindex('/',right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)))-1) as numeric))/5400 as koef,

(
SELECT sum (cast (VALUE as decimal (28,3))) from ZAK_PROPS where OBJECTID in
(
select ID_ZAK_VIDS from ZAK_VIDS where s.UNZ=ZAK_VIDS.UNZ
) and CODE=511
) ob
from
(
SELECT 
UNZ,sum ( QTY ) summa,(SELECT VALUE from ZAK_PROPS where OBJECTID=UNZ and CODE = 110) as FORMAT
 from #PBC p 
  left join ZAK_PROPS p258 on p258.CODE=258 and p258.OBJECTID= p.UNZ 
 where PROPS1

 in ('Интегральные переплетные крышки' , '№ 7','Блоки') and 
QTYTYPE = 'за период' and ID_OPER=1099966 and
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM)like '%ТЕРМОУП%') and coalesce(p258.VALUE,'') = '' 

group by UNZ
) s
) s2


/******************************************************************/

/*расчитаем факт по сдачи в листах оттисках для № 1*/
SELECT 
@FACT7 = sum(coalesce(summa,0)*coalesce(ob,0)*coalesce(koef,0))
from
(
SELECT  UNZ,summa, 
 (cast ( (left (FORMAT	,charindex ('*',FORMAT	)-1) ) as numeric ) * 
cast (left (right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)),
charindex('/',right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)))-1) as numeric))/5400 as koef,

(
SELECT sum (cast (VALUE as decimal (28,3))) from ZAK_PROPS where OBJECTID in
(
select ID_ZAK_VIDS from ZAK_VIDS where s.UNZ=ZAK_VIDS.UNZ
) and CODE=511
) ob
from
(
SELECT 
UNZ,sum ( QTY ) summa,(SELECT VALUE from ZAK_PROPS where OBJECTID=UNZ and CODE = 110) as FORMAT
 from #PBC p where PROPS1
 in ('№ 1') and 
QTYTYPE = 'за период' and ID_OPER=2097846 
and 
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM)like '%ТЕРМОУП%')

group by UNZ
) s
) s2
/******************************************************************/
/*расчитаем факт по обработке ВШРА в листах оттисках для переплёта № 1*/
SELECT 
@FACT8 = sum(coalesce(summa,0)*coalesce(ob,0)*coalesce(koef,0))
from
(
SELECT  UNZ,summa, 
 (cast ( (left (FORMAT	,charindex ('*',FORMAT	)-1) ) as numeric ) * 
cast (left (right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)),
charindex('/',right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)))-1) as numeric))/5400 as koef,

(
SELECT sum (cast (VALUE as decimal (28,3))) from ZAK_PROPS where OBJECTID in
(
select ID_ZAK_VIDS from ZAK_VIDS where s.UNZ=ZAK_VIDS.UNZ
) and CODE=511
) ob
from
(
SELECT 
UNZ,sum ( QTY ) summa,(SELECT VALUE from ZAK_PROPS where OBJECTID=UNZ and CODE = 110) as FORMAT
 from #PBC where PROPS1
 in ('№ 1') and 
QTYTYPE = 'за период' and ID_OPER=4223890
group by UNZ
) s
) s2
/******************************************************************/




--прочее

select @RD29 =
 QTY*ob*
  (cast ( (left (FORMAT	,charindex ('*',FORMAT	)-1) ) as numeric ) * 
cast (left (right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)),
charindex('/',right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)))-1) as numeric))/5400 
from
 (
 select w.QTY as QTY
 ,
 (
SELECT min (cast (VALUE as decimal (28,3))) from ZAK_PROPS where OBJECTID in
(
select ID_ZAK_VIDS from ZAK_VIDS where o.UNZ=ZAK_VIDS.UNZ
) and CODE=511
) as ob,

(SELECT VALUE from ZAK_PROPS where OBJECTID=o.UNZ and CODE = 110) as FORMAT
 
 from ZAK_OPER o
left join ZAK_WORK w on w.ID_ZAK_OPER=o.ID
left join ZAK_PROPS p164 on p164.CODE=164 and p164.OBJECTID=o.UNZ
inner join ZAK_HEAD h on h.UNZ = o.UNZ
 where 
 
  p164.VALUE in ('Папка с карточками' , 'Листы','') and
 o.ID_OPER=2097846 and
 w.W_DATA between @Date1 and @Date1+1 and

 not (h.KLIENT in ('Просвещение','Полиграф Трейд')) and not (upper(h.NAIM)like '%ТЕРМОУП%')
 ) as jjj





 



--газета


  select @RD30 =
 QTY*ob*
  (cast ( (left (FORMAT	,charindex ('*',FORMAT	)-1) ) as numeric ) * 
cast (left (right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)),
charindex('/',right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)))-1) as numeric))/5400 
from
 (
 select w.QTY as QTY
 ,
 (
SELECT sum (cast (VALUE as decimal (28,3))) from ZAK_PROPS where OBJECTID in
(
select ID_ZAK_VIDS from ZAK_VIDS where o.UNZ=ZAK_VIDS.UNZ
) and CODE=511
) as ob,
(SELECT VALUE from ZAK_PROPS where OBJECTID=o.UNZ and CODE = 110) as FORMAT
 
 from ZAK_OPER o
left join ZAK_WORK w on w.ID_ZAK_OPER=o.ID
left join ZAK_PROPS p164 on p164.CODE=164 and  p164.OBJECTID=UNZ 
inner join ZAK_HEAD h on h.UNZ = o.UNZ
 where o.ID_OPER=2097846 and p164.VALUE in ('Газета') and
 w.W_DATA between @Date1 and @Date1+1 and

 not (h.KLIENT in ('Просвещение','Полиграф Трейд')) and not (upper(h.NAIM)like '%ТЕРМОУП%')
 ) as jjj





/*расчитаем факт по сдачи в листах оттисках для № 3*/
SELECT 
@FACT11 = sum(coalesce(summa,0)*coalesce(ob,0)*coalesce(koef,0))
from
(
SELECT  UNZ,summa, 
 (cast ( (left (FORMAT	,charindex ('*',FORMAT	)-1) ) as numeric ) * 
cast (left (right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)),
charindex('/',right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)))-1) as numeric))/5400 as koef,

(
SELECT sum (cast (VALUE as decimal (28,3))) from ZAK_PROPS where OBJECTID in
(
select ID_ZAK_VIDS from ZAK_VIDS where s.UNZ=ZAK_VIDS.UNZ
) and CODE=511
) ob
from
(
SELECT 
UNZ,sum ( QTY ) summa,(SELECT VALUE from ZAK_PROPS where OBJECTID=UNZ and CODE = 110) as FORMAT
 from #PBC p where PROPS1
 in ('№ 3') and 
QTYTYPE = 'за период' and ID_OPER=2097846 and
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM)like '%ТЕРМОУП%')

group by UNZ
) s
) s2
/******************************************************************/
/*расчитаем факт по обработке ВШРА в листах оттисках для переплёта № 3*/
SELECT 
@FACT12 = sum(coalesce(summa,0)*coalesce(ob,0)*coalesce(koef,0))
from
(
SELECT  UNZ,summa, 
 (cast ( (left (FORMAT	,charindex ('*',FORMAT	)-1) ) as numeric ) * 
cast (left (right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)),
charindex('/',right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)))-1) as numeric))/5400 as koef,

(
SELECT sum (cast (VALUE as decimal (28,3))) from ZAK_PROPS where OBJECTID in
(
select ID_ZAK_VIDS from ZAK_VIDS where s.UNZ=ZAK_VIDS.UNZ
) and CODE=511
) ob
from
(
SELECT 
UNZ,sum ( QTY ) summa,(SELECT VALUE from ZAK_PROPS where OBJECTID=UNZ and CODE = 110) as FORMAT
 from #PBC where PROPS1
 in ('№ 3') and 
QTYTYPE = 'за период' and ID_OPER=1106339
group by UNZ
) s
) s2
/******************************************************************/
SELECT 
@FACT17 = sum ( QTY 

--* (cast(p885.VALUE as numeric(10)) +1)

) from #PBC p
left join ZAK_PROPS p127 on p127.CODE=127 and p127.OBJECTID = p.UNZ 
left join ZAK_PROPS p885 on p885.CODE=885 and p885.OBJECTID = p.UNZ 

where 
QTYTYPE = 'за период' and ID_OPER in (1090724 ,206745094)
and coalesce(p127.VALUE,'')='Сшитые блоки'
--шитье


/*asdf*/






insert into  #PBC_TEMPLAN
exec SPK_ZAK_REP_PLAN_PO_12;1 303782,@dtDate,@dtDateTo ,0,0,''


/*******загрузка по темплану твёрдый переплёт**************/
/*расчитаем в экземлярах : */
select @ZAGRUZ_O_TEMPL1 = coalesce (sum (Qty	) ,0) from #PBC_TEMPLAN 
where Pereplet in ('Интегральные переплетные крышки' , '№ 7','Блоки') --and 
/*загрузка по темпланe в листах оттисках твердый переплет */
set
@ZAGRUZ_O_TEMPL3 = @ZAGRUZ_O_TEMPL1 * 0.375 +
(
select    
sum (Qty *
 cast ( (left (FORMAT	,charindex ('*',FORMAT	)-1) ) as numeric ) * 
cast (left (right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)),
charindex('/',right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)))-1) as numeric) * Obyom /5400)
from #PBC_TEMPLAN 
where Pereplet in ('Интегральные переплетные крышки' , '№ 7','Блоки') 
)
/*******загрузка по темплану твёрдый переплёт******Конец********/



select    @ZAGRUZ_O_TEMPL29  = 
sum (Qty *
 cast ( (left (FORMAT	,charindex ('*',FORMAT	)-1) ) as numeric ) * 
cast (left (right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)),
charindex('/',right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)))-1) as numeric) * sun_ob /5400)
from #SPK_PLANPOSTAVOK_UNIVERSAL_WITH_COMPONENTS
where Pereplet in ('Папка с карточками' , 'Листы','') 

/*
select    *
from #SPK_PLANPOSTAVOK_UNIVERSAL_WITH_COMPONENTS
where Pereplet in ('Папка с карточками' , 'Листы','') 
*/

select    @ZAGRUZ_O_TEMPL30  = 
sum (Qty *
 cast ( (left (FORMAT	,charindex ('*',FORMAT	)-1) ) as numeric ) * 
cast (left (right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)),
charindex('/',right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)))-1) as numeric) * sun_ob /5400)
from #SPK_PLANPOSTAVOK_UNIVERSAL_WITH_COMPONENTS
where Pereplet in ('Газета') 


/*******загрузка по темплану переплёт № 1**************/
/*расчитаем в экземлярах : */
select @ZAGRUZ_O_TEMPL5 = coalesce (sum (Qty	) ,0) from #PBC_TEMPLAN 
where Pereplet in ('№ 1') --and 
/*загрузка по темпланe в листах оттисках твердый переплет */
set
@ZAGRUZ_O_TEMPL7 = @ZAGRUZ_O_TEMPL5 * 0.125 +
(
select    
sum (Qty *
 cast ( (left (FORMAT	,charindex ('*',FORMAT	)-1) ) as numeric ) * 
cast (left (right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)),
charindex('/',right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)))-1) as numeric) * Obyom /5400)
from #PBC_TEMPLAN 
where Pereplet in ('№ 1') 
)
/*******загрузка по темплану переплёт №1******Конец********/


/*******загрузка по темплану переплёт № 3**************/
/*расчитаем в экземлярах : */
select @ZAGRUZ_O_TEMPL9 = coalesce (sum (Qty	) ,0) from #PBC_TEMPLAN 
where Pereplet in ('№ 3') --and 

select @ZAGRUZ_O_TEMPL17 = sum( Qty  ) from #PBC_TEMPLAN 
--case when (select count( '1' )   from ZAK_TPOPER where ID_ZAK_HEAD =236169389
 --and ID_ZAK_SETOPER = 1099966) > 0  then 'y' else 'n' end
left join ZAK_PROPS p127 on p127.CODE=127 and p127.OBJECTID=UNZ
where (Pereplet in ('Интегральные переплетные крышки' , '№ 7')) or (Pereplet = 'Блоки'  and (select case when (select count( '1' )   from ZAK_TPOPER where ID_ZAK_HEAD = UNZ
 and ID_ZAK_SETOPER = 1099966) > 0  then 'y' else 'n' end) = 'y' ) or (Pereplet ='№ 3' and p127.VALUE='Сшитые блоки' )

--select  @ZAGRUZ_O_TEMPL17

--@ZAGRUZ_O_TEMPL17 = sum((CHISLO_TETR_W_BLOCKE+1) * Qty  ) from #PBC_TEMPLAN 

--select '@ZAGRUZ_O_TEMPL17',@ZAGRUZ_O_TEMPL17

/*загрузка по темпланe в листах оттисках твердый переплет */
set
@ZAGRUZ_O_TEMPL11 = @ZAGRUZ_O_TEMPL9 * 0.25 +
(
select    
sum (Qty *
 cast ( (left (FORMAT	,charindex ('*',FORMAT	)-1) ) as numeric ) * 
cast (left (right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)),
charindex('/',right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)))-1) as numeric) * Obyom /5400)
from #PBC_TEMPLAN 
where Pereplet in ('№ 3') 
)
/*******загрузка по темплану переплёт №3******Конец********/








/****************************/
truncate table #FROM_SVODKA_EQUIP 

insert into #FROM_SVODKA_EQUIP 
exec ZAK_VED_EQUIP_smolensk @Date1,@Date1,303782

delete from #FROM_SVODKA_EQUIP where 

(SELECT top 1 ID_ZAK_SETOPER from ZAK_TPOPER where ID_ZAK_HEAD = UNZ)=22564504 and 
(SELECT count ('1') from ZAK_TPOPER where ID_ZAK_HEAD = UNZ)=1

--4170932 Колбус 4:
SELECT 
@RD18 = sum ( QTY ) from #FROM_SVODKA_EQUIP p 
left join ZAK_PROPS p164 on p164.CODE=164 and p164.OBJECTID = p.UNZ
where p164.VALUE
 in ('Интегральные переплетные крышки' , '№ 7','Блоки') 
and ID_EQUIP=4170932 and 
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM) like '%ТЕРМОУП%')


--4170933 Колбус 5:
SELECT 
@RD19 = sum ( QTY ) from #FROM_SVODKA_EQUIP p 
left join ZAK_PROPS p164 on p164.CODE=164 and p164.OBJECTID = p.UNZ
where p164.VALUE
 in ('Интегральные переплетные крышки' , '№ 7','Блоки') 
and ID_EQUIP=4170933 and 
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM) like '%ТЕРМОУП%')


--9246942	Компакт-60:
SELECT 
@RD20 = sum ( QTY ) from #FROM_SVODKA_EQUIP p 
left join ZAK_PROPS p164 on p164.CODE=164 and p164.OBJECTID = p.UNZ
where p164.VALUE
 in ('Интегральные переплетные крышки' , '№ 7','Блоки') 
and ID_EQUIP=9246942 and 
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM) like '%ТЕРМОУП%')

--67214251	Компакт-30 (№1)  - Компакт-30:
SELECT 
@RD21 = sum ( QTY ) from #FROM_SVODKA_EQUIP p 
left join ZAK_PROPS p164 on p164.CODE=164 and p164.OBJECTID = p.UNZ
where p164.VALUE
 in ('Интегральные переплетные крышки' , '№ 7','Блоки') 
and ID_EQUIP=67214251 and 
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM) like '%ТЕРМОУП%')

--135655108	Компакт-30 (№2)  - Компакт-30-BF:
SELECT 
@RD22 = sum ( QTY ) from #FROM_SVODKA_EQUIP p 
left join ZAK_PROPS p164 on p164.CODE=164 and p164.OBJECTID = p.UNZ
where p164.VALUE
 in ('Интегральные переплетные крышки' , '№ 7','Блоки') 
and ID_EQUIP=135655108 and 
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM) like '%ТЕРМОУП%')



--1106418	Полимат
SELECT 
@RD23 = sum ( QTY ) from #FROM_SVODKA_EQUIP p 
left join ZAK_PROPS p164 on p164.CODE=164 and p164.OBJECTID = p.UNZ
where p164.VALUE
 in ('№ 1') 
and ID_EQUIP=1106418 and 
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM) like '%ТЕРМОУП%')


--1106420	Престо
SELECT 
@RD24 = sum ( QTY ) from #FROM_SVODKA_EQUIP p 
left join ZAK_PROPS p164 on p164.CODE=164 and p164.OBJECTID = p.UNZ
where p164.VALUE
 in ('№ 1') 
and ID_EQUIP=1106420 and 
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM) like '%ТЕРМОУП%')

--16808553	ST-100
SELECT 
@RD25 = sum ( QTY ) from #FROM_SVODKA_EQUIP p 
left join ZAK_PROPS p164 on p164.CODE=164 and p164.OBJECTID = p.UNZ
where p164.VALUE
 in ('№ 1') 
and ID_EQUIP=16808553 and 
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM) like '%ТЕРМОУП%')


--150435859	ST-400
SELECT 
@RD26 = sum ( QTY ) from #FROM_SVODKA_EQUIP p 
left join ZAK_PROPS p164 on p164.CODE=164 and p164.OBJECTID = p.UNZ
where p164.VALUE
 in ('№ 1') 
and ID_EQUIP=150435859 and 
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM) like '%ТЕРМОУП%')


--1663761	Рацио-Биндер-470
SELECT 
@RD27 = sum ( QTY ) from #FROM_SVODKA_EQUIP p 
left join ZAK_PROPS p164 on p164.CODE=164 and p164.OBJECTID = p.UNZ
where p164.VALUE
 in ('№ 3') 
and ID_EQUIP=1663761 and 
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM) like '%ТЕРМОУП%')

--119073033	Евробинд ПРО
SELECT 
@RD28 = sum ( QTY ) from #FROM_SVODKA_EQUIP p 
left join ZAK_PROPS p164 on p164.CODE=164 and p164.OBJECTID = p.UNZ
where p164.VALUE
 in ('№ 3') 
and ID_EQUIP=119073033 and 
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM) like '%ТЕРМОУП%')


SELECT 
@RD31 = sum ( QTY ) from #FROM_SVODKA_EQUIP p 
left join ZAK_PROPS p164 on p164.CODE=164 and p164.OBJECTID = p.UNZ
where p164.VALUE
 in ('№ 3') 
and ID_EQUIP=241666927 and 
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM) like '%ТЕРМОУП%')


/****************************/

truncate table #PBC

INSERT into #PBC
exec ZAK_VED_OPER_smolensk;1 @Date1,@Date1,303782
delete from #PBC where 

(SELECT top 1 ID_ZAK_SETOPER from ZAK_TPOPER where ID_ZAK_HEAD = UNZ)=22564504 and 
(SELECT count ('1') from ZAK_TPOPER where ID_ZAK_HEAD = UNZ)=1
/*********************************************************/
/*расчитаем рд Сдача в экземлярах для твердого переплёта*/
SELECT 
@RD1 = sum ( QTY ) from #PBC p where PROPS1
 in ('Интегральные переплетные крышки' , '№ 7','Блоки','Блоки, № 7') and 
QTYTYPE = 'за период' and ID_OPER=2097846 and
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM)like '%ТЕРМОУП%')

/*******************************************************/
/*расчитаем рд АПЛ в экземлярах для твердого переплёта*/
SELECT 
@RD2 = sum ( QTY ) from #PBC where PROPS1
 in ('Интегральные переплетные крышки' , '№ 7','Блоки','Блоки, № 7') and 
QTYTYPE = 'за период' and ID_OPER=1099966 
/****************************************************/

/*расчитаем рд в листах оттисках для твердого переплёта Сдачу*/


SELECT  @RD3 = sum ( QTY  * cast(p182.VALUE as decimal(25,5))  * cast(p183.VALUE as decimal(25,5)) * cast(p258.VALUE as decimal(25,5)) / 5400 )
 from #PBC p 
   left join ZAK_PROPS p258 on p258.CODE=258 and p258.OBJECTID= p.UNZ 

   left join ZAK_PROPS p182 on p182.CODE=182 and p182.OBJECTID= p.UNZ 
   left join ZAK_PROPS p183 on p183.CODE=183 and p183.OBJECTID= p.UNZ 

 where PROPS1 in ('Интегральные переплетные крышки' , '№ 7','Блоки') and 
QTYTYPE = 'за период' and ID_OPER=2097846 and
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(p.NAIM)like '%ТЕРМОУП%')
and (coalesce(p258.VALUE,'') != ''  and ISNUMERIC(p258.VALUE) = 1)



SELECT 
@RD3 =@RD3 +  sum(coalesce(summa,0)*coalesce(ob,0)*coalesce(koef,0))
from
(
SELECT  UNZ,summa, 
 (cast ( (left (FORMAT	,charindex ('*',FORMAT	)-1) ) as numeric ) * 
cast (left (right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)),
charindex('/',right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)))-1) as numeric))/5400 as koef,

(
SELECT sum (cast (VALUE as decimal (28,3))) from ZAK_PROPS where OBJECTID in
(
select ID_ZAK_VIDS from ZAK_VIDS where s.UNZ=ZAK_VIDS.UNZ
) and CODE=511

) ob
from
(
SELECT 
UNZ,sum ( QTY ) summa,(SELECT VALUE from ZAK_PROPS where OBJECTID=UNZ and CODE = 110) as FORMAT
 from #PBC p 
   left join ZAK_PROPS p258 on p258.CODE=258 and p258.OBJECTID= p.UNZ 
 where PROPS1
 in ('Интегральные переплетные крышки' , '№ 7','Блоки','Блоки, № 7') and 
QTYTYPE = 'за период' and ID_OPER=2097846 and
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM)like '%ТЕРМОУП%') and coalesce(p258.VALUE,'') = '' 

group by UNZ
) s
) s2
/******************************************************************/

/*расчитаем рд в листах оттисках для твердого переплёта Обработка блоков*/

SELECT  @RD4 = sum ( QTY  * cast(p182.VALUE as decimal(25,5))  * cast(p183.VALUE as decimal(25,5)) * cast(p258.VALUE as decimal(25,5)) / 5400 )
 from #PBC p 
   left join ZAK_PROPS p258 on p258.CODE=258 and p258.OBJECTID= p.UNZ 

   left join ZAK_PROPS p182 on p182.CODE=182 and p182.OBJECTID= p.UNZ 
   left join ZAK_PROPS p183 on p183.CODE=183 and p183.OBJECTID= p.UNZ 

 where PROPS1 in ('Интегральные переплетные крышки' , '№ 7','Блоки') and 
QTYTYPE = 'за период' and ID_OPER=1099966 and
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(p.NAIM)like '%ТЕРМОУП%')
and (coalesce(p258.VALUE,'') != ''  and ISNUMERIC(p258.VALUE) = 1)
/*group by p.UNZ,
p182.VALUE,
p183.VALUE,
p258.VALUE */

/*******************/

/*расчитаем факт по сдачи в листах оттисках для твердого переплёта*/
SELECT 
 @RD4  =  @RD4  + sum(coalesce(summa,0)*coalesce(ob,0)*coalesce(koef,0))
from
(
SELECT  UNZ,summa, 
 (cast ( (left (FORMAT	,charindex ('*',FORMAT	)-1) ) as numeric ) * 
cast (left (right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)),
charindex('/',right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)))-1) as numeric))/5400 as koef,

(
SELECT sum (cast (VALUE as decimal (28,3))) from ZAK_PROPS where OBJECTID in
(
select ID_ZAK_VIDS from ZAK_VIDS where s.UNZ=ZAK_VIDS.UNZ
) and CODE=511
) ob
from
(
SELECT 
UNZ,sum ( QTY ) summa,(SELECT VALUE from ZAK_PROPS where OBJECTID=UNZ and CODE = 110) as FORMAT
 from #PBC p 
  left join ZAK_PROPS p258 on p258.CODE=258 and p258.OBJECTID= p.UNZ 
 where PROPS1

 in ('Интегральные переплетные крышки' , '№ 7','Блоки') and 
QTYTYPE = 'за период' and ID_OPER=1099966 and
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM)like '%ТЕРМОУП%') and coalesce(p258.VALUE,'') = '' 

group by UNZ
) s
) s2


/******************************************************************/

/*расчитаем рд Сдача в экземлярах для переплёта №1*/
SELECT 
@RD5 = sum ( QTY ) from #PBC p where PROPS1
 in ('№ 1') and 
QTYTYPE = 'за период' and ID_OPER=2097846 and 
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM)like '%ТЕРМОУП%')

/*******************************************************/
/*расчитаем рд ВШРА в экземлярах для переплёта № 1*/
SELECT 
@RD6 = sum ( QTY ) from #PBC where PROPS1
 in ('№ 1') and 
QTYTYPE = 'за период' and ID_OPER=4223890 
/********************************************************/

/*расчитаем рд в листах оттисках для №1 переплёта Сдача*/

SELECT 
@RD7= sum(coalesce(summa,0)*coalesce(ob,0)*coalesce(koef,0))
--coalesce(summa,0),coalesce(ob,0),coalesce(koef,0)
--UNZ,summa,ob,koef



from
(
SELECT  UNZ,summa, 
 (cast ( (left (FORMAT	,charindex ('*',FORMAT	)-1) ) as numeric ) * 
cast (left (right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)),
charindex('/',right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)))-1) as numeric))/5400 as koef,

(
SELECT sum (cast (VALUE as decimal (28,3))) from ZAK_PROPS where OBJECTID in
(
select ID_ZAK_VIDS from ZAK_VIDS where s.UNZ=ZAK_VIDS.UNZ
) and CODE=511

) ob
from
(
SELECT 
UNZ,sum ( QTY ) summa,(SELECT VALUE from ZAK_PROPS where OBJECTID=UNZ and CODE = 110) as FORMAT
 from #PBC p where PROPS1
 in ('№ 1') and 
QTYTYPE = 'за период' and ID_OPER=2097846 and
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM)like '%ТЕРМОУП%')

group by UNZ
) s
) s2
/******************************************************************/

/*расчитаем рд в листах оттисках для № 1 переплёта ВШРА*/

SELECT 
@RD8= sum(coalesce(summa,0)*coalesce(ob,0)*coalesce(koef,0))
--coalesce(summa,0),coalesce(ob,0),coalesce(koef,0)
--UNZ,summa,ob,koef



from
(
SELECT  UNZ,summa, 
 (cast ( (left (FORMAT	,charindex ('*',FORMAT	)-1) ) as numeric ) * 
cast (left (right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)),
charindex('/',right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)))-1) as numeric))/5400 as koef,

(
SELECT sum (cast (VALUE as decimal (28,3))) from ZAK_PROPS where OBJECTID in
(
select ID_ZAK_VIDS from ZAK_VIDS where s.UNZ=ZAK_VIDS.UNZ
) and CODE=511

) ob
from
(
SELECT 
UNZ,sum ( QTY ) summa,(SELECT VALUE from ZAK_PROPS where OBJECTID=UNZ and CODE = 110) as FORMAT
 from #PBC where PROPS1
 in ('№ 1') and 
QTYTYPE = 'за период' and ID_OPER=4223890
group by UNZ
) s
) s2
/******************************************************************/

/*расчитаем рд Сдача в экземлярах для переплёта №3*/
SELECT 
@RD9 = sum ( QTY ) from #PBC p where PROPS1
 in ('№ 3') and 
QTYTYPE = 'за период' and ID_OPER=2097846 and
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM)like '%ТЕРМОУП%')

/*******************************************************/
/*расчитаем рд ВШРА в экземлярах для переплёта № 3*/
SELECT 
@RD10 = sum ( QTY ) from #PBC where PROPS1
 in ('№ 3') and 
QTYTYPE = 'за период' and ID_OPER=1106339 
/********************************************************/

/*расчитаем рд в листах оттисках для №3 переплёта Сдача*/

/*
SELECT 
@RD17 = sum ( QTY ) from #PBC where 
QTYTYPE = 'за период' and ID_OPER=1090724 --шитье
*/

SELECT 
@RD17 = sum ( QTY 

--* (cast(p885.VALUE as numeric(10)) +1) 

) from #PBC p
left join ZAK_PROPS p127 on p127.CODE=127 and p127.OBJECTID = p.UNZ 
left join ZAK_PROPS p885 on p885.CODE=885 and p885.OBJECTID = p.UNZ 

where 
QTYTYPE = 'за период' and ID_OPER in (1090724 ,206745094)
and coalesce(p127.VALUE,'')='Сшитые блоки'
--шитье


SELECT 
@RD11= sum(coalesce(summa,0)*coalesce(ob,0)*coalesce(koef,0))
--coalesce(summa,0),coalesce(ob,0),coalesce(koef,0)
--UNZ,summa,ob,koef



from
(
SELECT  UNZ,summa, 
 (cast ( (left (FORMAT	,charindex ('*',FORMAT	)-1) ) as numeric ) * 
cast (left (right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)),
charindex('/',right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)))-1) as numeric))/5400 as koef,

(
SELECT sum (cast (VALUE as decimal (28,3))) from ZAK_PROPS where OBJECTID in
(
select ID_ZAK_VIDS from ZAK_VIDS where s.UNZ=ZAK_VIDS.UNZ
) and CODE=511

) ob
from
(
SELECT 
UNZ,sum ( QTY ) summa,(SELECT VALUE from ZAK_PROPS where OBJECTID=UNZ and CODE = 110) as FORMAT
 from #PBC p where PROPS1
 in ('№ 3') and 
QTYTYPE = 'за период' and ID_OPER=2097846 and
not ((SELECT KLIENT from ZAK_HEAD z where z.UNZ=p.UNZ) in ('Просвещение','Полиграф Трейд')
and upper(NAIM)like '%ТЕРМОУП%')

group by UNZ
) s
) s2
/******************************************************************/

/*расчитаем рд в листах оттисках для № 3 переплёта крытьё*/

SELECT 
@RD12= sum(coalesce(summa,0)*coalesce(ob,0)*coalesce(koef,0))
--coalesce(summa,0),coalesce(ob,0),coalesce(koef,0)
--UNZ,summa,ob,koef



from
(
SELECT  UNZ,summa, 
 (cast ( (left (FORMAT	,charindex ('*',FORMAT	)-1) ) as numeric ) * 
cast (left (right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)),
charindex('/',right (FORMAT	 ,len (FORMAT	)-charindex ('*',FORMAT	)))-1) as numeric))/5400 as koef,

(
SELECT sum (cast (VALUE as decimal (28,3))) from ZAK_PROPS where OBJECTID in
(
select ID_ZAK_VIDS from ZAK_VIDS where s.UNZ=ZAK_VIDS.UNZ
) and CODE=511

) ob
from
(
SELECT 
UNZ,sum ( QTY ) summa,(SELECT VALUE from ZAK_PROPS where OBJECTID=UNZ and CODE = 110) as FORMAT
 from #PBC where PROPS1
 in ('№ 3') and 
QTYTYPE = 'за период' and ID_OPER=1106339
group by UNZ
) s
) s2
/******************************************************************/
--select @FACT3 as FACT3
--select @FACT4 as FACT4
insert SPK_RESULT 


select 3,27 as NUMER,EQUIP,UNIT,CHANCE,(@ZAGRUZ_O_TEMPL1 / POW)*100 PERCENT_ZAG,POW,@ZAGRUZ_O_TEMPL1 as TMPLAN,@FACT1 as FACT,
cast((case when @ZAGRUZ_O_TEMPL1>0 then  @FACT1 * 100 /  @ZAGRUZ_O_TEMPL1 end) as decimal(18,3))  as PROC_VIP,


cast( (@ZAGRUZ_O_TEMPL1 /  @num_of_day ) as decimal(18,3))



ZADANIE_NA_DEN,
@RD1 as RD
from (select EQUIP,UNIT,POW,CHANCE from SPK_CONST where ID=17) tab1

union

select 3,28,EQUIP,UNIT,CHANCE,(@ZAGRUZ_O_TEMPL1 / POW)*100 PERCENT_ZAG,POW,@ZAGRUZ_O_TEMPL1 as TMPLAN,@FACT2 as FACT,


cast( (case when @ZAGRUZ_O_TEMPL1>0 then @FACT2 * 100 /  @ZAGRUZ_O_TEMPL1 end) as decimal(18,3)) as PROC_VIP,


cast((@ZAGRUZ_O_TEMPL1 /  @num_of_day ) as decimal(18,3)) ZADANIE_NA_DEN,
@RD2
from (select EQUIP,UNIT,POW,CHANCE from SPK_CONST where ID=18) tab1
union








select 3,29,  EQUIP,UNIT,CHANCE,(@ZAGRUZ_O_TEMPL18 / POW)*100 PERCENT_ZAG,POW,@ZAGRUZ_O_TEMPL18 as TMPLAN,@FACT18 as FACT,

cast(
(case when @ZAGRUZ_O_TEMPL18>0 then  @FACT18 * 100 /  @ZAGRUZ_O_TEMPL18 end) as decimal(18,3))

as PROC_VIP,

cast((@ZAGRUZ_O_TEMPL18 /  @num_of_day ) as decimal(18,3)) 


ZADANIE_NA_DEN,
@RD18
from (select EQUIP,UNIT,POW,CHANCE from SPK_CONST where ID=36) tab1

union

select 3,30,EQUIP,UNIT,CHANCE,(@ZAGRUZ_O_TEMPL19 / POW)*100 PERCENT_ZAG,POW,@ZAGRUZ_O_TEMPL19 as TMPLAN,@FACT19 as FACT,


cast((case when @ZAGRUZ_O_TEMPL19>0 then  @FACT19 * 100 /  @ZAGRUZ_O_TEMPL19 end) as decimal(18,3)) 


as PROC_VIP,cast((@ZAGRUZ_O_TEMPL19 /  @num_of_day ) as decimal(18,3))  ZADANIE_NA_DEN,
@RD19
from (select EQUIP,UNIT,POW,CHANCE from SPK_CONST where ID=37) tab1

union

select 3,31, EQUIP,UNIT,CHANCE,(@ZAGRUZ_O_TEMPL20 / POW)*100 PERCENT_ZAG,POW,@ZAGRUZ_O_TEMPL20 as TMPLAN,@FACT20 as FACT,
cast( 
(case when @ZAGRUZ_O_TEMPL20>0 then  @FACT20 * 100 /  @ZAGRUZ_O_TEMPL20 end) 
as decimal(18,3))
as PROC_VIP,
cast( 
(@ZAGRUZ_O_TEMPL20 /  @num_of_day ) 
as decimal(18,3))
ZADANIE_NA_DEN,
@RD20
from (select EQUIP,UNIT,POW,CHANCE from SPK_CONST where ID=38) tab1

union

select 3,32, EQUIP,UNIT,CHANCE,(@ZAGRUZ_O_TEMPL21 / POW)*100 PERCENT_ZAG,POW,@ZAGRUZ_O_TEMPL21 as TMPLAN,@FACT21 as FACT,

cast( 
(case when @ZAGRUZ_O_TEMPL21>0 then  @FACT21 * 100 /  @ZAGRUZ_O_TEMPL21 end) 
as decimal(18,3))
as PROC_VIP,
cast( 
(@ZAGRUZ_O_TEMPL21 /  @num_of_day ) 
as decimal(18,3))
ZADANIE_NA_DEN,
@RD21
from (select EQUIP,UNIT,POW,CHANCE from SPK_CONST where ID=39) tab1



union

select 3,33,EQUIP,UNIT,CHANCE,(@ZAGRUZ_O_TEMPL22 / POW)*100 PERCENT_ZAG,POW,@ZAGRUZ_O_TEMPL22 as TMPLAN,@FACT22 as FACT,


cast( (case when @ZAGRUZ_O_TEMPL22>0 then  @FACT22 * 100 /  @ZAGRUZ_O_TEMPL22 end) as decimal(18,3)) as PROC_VIP,

cast((@ZAGRUZ_O_TEMPL22 /  @num_of_day ) as decimal(18,3)) ZADANIE_NA_DEN,
@RD22
from (select EQUIP,UNIT,POW,CHANCE from SPK_CONST where ID=40) tab1



union
select 3,34,EQUIP,UNIT,null,null as PERCENT_ZAG,POW,@ZAGRUZ_O_TEMPL3 as TMPLAN,@FACT3 as FACT,

cast(
(case when @ZAGRUZ_O_TEMPL3>0 then @FACT3 * 100 /  @ZAGRUZ_O_TEMPL3 end) as decimal(18,3)) as PROC_VIP,


cast((@ZAGRUZ_O_TEMPL3 /  @num_of_day ) as decimal(18,3)) ZADANIE_NA_DEN,
@RD3
from (select EQUIP,UNIT,POW,CHANCE from SPK_CONST where ID=19) tab1
union

--БР. №1 изгот
select 3,35,EQUIP,UNIT,null,null as PERCENT_ZAG,POW,@ZAGRUZ_O_TEMPL3 as TMPLAN,@FACT4 as FACT,
cast((case when @ZAGRUZ_O_TEMPL3>0 then  @FACT4 * 100 /  @ZAGRUZ_O_TEMPL3 end) as decimal(18,3)) as PROC_VIP,

cast((@ZAGRUZ_O_TEMPL3 /  @num_of_day ) as decimal(18,3))    ZADANIE_NA_DEN,
@RD4
from (select EQUIP,UNIT,POW,CHANCE from SPK_CONST where ID=20) tab1

union

--БР. №1 сдано
select 3,36,NULL,Null,Null,Null,Null,Null,Null,Null,Null,Null
union
select 3,37,EQUIP,UNIT,POW,(@ZAGRUZ_O_TEMPL5 / CHANCE)*100 PERCENT_ZAG,CHANCE,@ZAGRUZ_O_TEMPL5 as TMPLAN,@FACT5 as FACT,
cast((case when @ZAGRUZ_O_TEMPL5>0 then @FACT5 * 100 /  @ZAGRUZ_O_TEMPL5 end) as decimal(18,3))  as PROC_VIP,

cast((@ZAGRUZ_O_TEMPL5 /  @num_of_day ) as decimal(18,3))  ZADANIE_NA_DEN,
@RD5
from (select EQUIP,UNIT,POW,CHANCE from SPK_CONST where ID=21) tab1

union

--изготовл №1
select 3,38,EQUIP,UNIT,null,null as PERCENT_ZAG,POW,@ZAGRUZ_O_TEMPL5 as TMPLAN,@FACT6 as FACT,
cast((case when @ZAGRUZ_O_TEMPL5>0 then @FACT6 * 100 /  @ZAGRUZ_O_TEMPL5 end) as decimal(18,3))  as PROC_VIP,

cast((@ZAGRUZ_O_TEMPL5 /  @num_of_day ) as decimal(18,3)) ZADANIE_NA_DEN,
@RD6
from (select EQUIP,UNIT,POW,CHANCE from SPK_CONST where ID=22) tab1

union

-- полимат
select 3,39,EQUIP,UNIT,CHANCE,(@ZAGRUZ_O_TEMPL23 / POW)*100 PERCENT_ZAG,POW,@ZAGRUZ_O_TEMPL23 as TMPLAN,@FACT23 as FACT,
cast((case when @ZAGRUZ_O_TEMPL23>0 then  @FACT23 * 100 /  @ZAGRUZ_O_TEMPL23 end) as decimal(18,3)) as PROC_VIP,

cast((@ZAGRUZ_O_TEMPL23 /  @num_of_day ) as decimal(18,3)) ZADANIE_NA_DEN,


@RD23
from (select EQUIP,UNIT,POW,CHANCE from SPK_CONST where ID=41) tab1
/***********************************************************************************************/
union
--престо
select 3,40,EQUIP,UNIT,CHANCE,(@ZAGRUZ_O_TEMPL24 / POW)*100 PERCENT_ZAG,POW,@ZAGRUZ_O_TEMPL24 as TMPLAN,@FACT24 as FACT,
cast((case when @ZAGRUZ_O_TEMPL24>0 then  @FACT24 * 100 /  @ZAGRUZ_O_TEMPL24 end)  as decimal(18,3))

as PROC_VIP,cast((@ZAGRUZ_O_TEMPL24 /  @num_of_day ) as decimal(18,3)) ZADANIE_NA_DEN,
@RD24
from (select EQUIP,UNIT,POW,CHANCE from SPK_CONST where ID=42) tab1


union

--ST-100
select 3,41,EQUIP,UNIT,CHANCE,(@ZAGRUZ_O_TEMPL25 / POW)*100 PERCENT_ZAG,POW,@ZAGRUZ_O_TEMPL25 as TMPLAN,@FACT25 as FACT,
cast((case when @ZAGRUZ_O_TEMPL25>0 then  @FACT25 * 100 /  @ZAGRUZ_O_TEMPL25 end) as decimal(18,3)) as PROC_VIP,

cast((@ZAGRUZ_O_TEMPL25 /  @num_of_day ) as decimal(18,3)) ZADANIE_NA_DEN,


@RD25
from (select EQUIP,UNIT,POW,CHANCE from SPK_CONST where ID=43) tab1


union


--ST-400
select 3,42,EQUIP,UNIT,CHANCE,(@ZAGRUZ_O_TEMPL26 / POW)*100 PERCENT_ZAG,POW,@ZAGRUZ_O_TEMPL26 as TMPLAN,@FACT26 as FACT,
cast((case when @ZAGRUZ_O_TEMPL26>0 then  @FACT26 * 100 /  @ZAGRUZ_O_TEMPL26 end) as decimal(18,3)) as PROC_VIP,

cast((@ZAGRUZ_O_TEMPL26 /  @num_of_day ) as decimal(18,3)) ZADANIE_NA_DEN,
@RD26
from (select EQUIP,UNIT,POW,CHANCE from SPK_CONST where ID=44) tab1

union
select 3,43,EQUIP,UNIT,null,null as PERCENT_ZAG,POW,@ZAGRUZ_O_TEMPL7 as TMPLAN,@FACT7 as FACT,
cast((case when @ZAGRUZ_O_TEMPL7>0 then  @FACT7 * 100 /  @ZAGRUZ_O_TEMPL7 end) as decimal(18,3))  as PROC_VIP,cast((@ZAGRUZ_O_TEMPL7 /  @num_of_day ) as decimal(18,3)) ZADANIE_NA_DEN,
@RD7
from (select EQUIP,UNIT,POW,CHANCE from SPK_CONST where ID=27) tab1





union
--сдано 
select 3,43,EQUIP,UNIT,null,null as PERCENT_ZAG,POW,@ZAGRUZ_O_TEMPL7 as TMPLAN,@FACT7 as FACT,

cast((case when @ZAGRUZ_O_TEMPL7>0 then  @FACT7 * 100 /  @ZAGRUZ_O_TEMPL7 end) as decimal(18,3))  as PROC_VIP

,cast((@ZAGRUZ_O_TEMPL7 /  @num_of_day ) as decimal(18,3)) ZADANIE_NA_DEN,
@RD7
from (select EQUIP,UNIT,POW,CHANCE from SPK_CONST where ID=27) tab1





union
--изготовл
select 3,44,EQUIP,UNIT,null,null as PERCENT_ZAG,POW,@ZAGRUZ_O_TEMPL7 as TMPLAN,@FACT8 as FACT,
cast((case when @ZAGRUZ_O_TEMPL7>0 then  @FACT8 * 100 /  @ZAGRUZ_O_TEMPL7 end)  as decimal(18,3)) as PROC_VIP,cast(  (@ZAGRUZ_O_TEMPL7 /  @num_of_day ) as decimal(18,3)) ZADANIE_NA_DEN,
@RD8
from (select EQUIP,UNIT,POW,CHANCE from SPK_CONST where ID=28) tab1

union





select 3,45,NULL,Null,Null,Null,Null,Null,Null,Null,Null,Null
union

--БР. №3 сдано
select 3,46,EQUIP,UNIT,POW,(@ZAGRUZ_O_TEMPL9 / CHANCE)*100 PERCENT_ZAG,CHANCE,@ZAGRUZ_O_TEMPL9 as TMPLAN,@FACT9 as FACT,

cast( (case when @ZAGRUZ_O_TEMPL9>0 then @FACT9 * 100 /  @ZAGRUZ_O_TEMPL9 end) as decimal(18,3)) as PROC_VIP,



cast( (@ZAGRUZ_O_TEMPL9 /  @num_of_day )  as decimal(18,3)) ZADANIE_NA_DEN,
@RD9
from (select EQUIP,UNIT,POW,CHANCE from SPK_CONST where ID=25) tab1
union

select 3,47,EQUIP,UNIT,null,null as PERCENT_ZAG,POW,@ZAGRUZ_O_TEMPL9 as TMPLAN,@FACT10 as FACT,


cast((case when @ZAGRUZ_O_TEMPL9>0 then @FACT10 * 100 /  @ZAGRUZ_O_TEMPL9 end) as decimal(18,3)) as PROC_VIP


,cast( (@ZAGRUZ_O_TEMPL9 /  @num_of_day )  as decimal(18,3)) ZADANIE_NA_DEN,
@RD10
from (select EQUIP,UNIT,POW,CHANCE from SPK_CONST where ID=26) tab1
union
/***************/

--в том числе Рацио-Биндер
select 3,48,EQUIP,UNIT,CHANCE,(@ZAGRUZ_O_TEMPL27 / POW)*100 PERCENT_ZAG,POW,@ZAGRUZ_O_TEMPL27 as TMPLAN,@FACT27 as FACT,
cast( (case when @ZAGRUZ_O_TEMPL27>0 then  @FACT27 * 100 /  @ZAGRUZ_O_TEMPL27 end) as decimal(18,3)) as PROC_VIP,cast((@ZAGRUZ_O_TEMPL27 /  @num_of_day ) as decimal(18,3)) ZADANIE_NA_DEN,
@RD27
from (select EQUIP,UNIT,POW,CHANCE from SPK_CONST where ID=45) tab1


union


--EUROBIND
select 3,49,EQUIP,UNIT,CHANCE,(@ZAGRUZ_O_TEMPL28 / POW)*100 PERCENT_ZAG,POW,@ZAGRUZ_O_TEMPL28 as TMPLAN,@FACT28 as FACT,

cast( (case when @ZAGRUZ_O_TEMPL28>0 then  @FACT28 * 100 /  @ZAGRUZ_O_TEMPL28 end)  as decimal(18,3)) as PROC_VIP, cast((@ZAGRUZ_O_TEMPL28 /  @num_of_day ) as decimal(18,3)) ZADANIE_NA_DEN,
@RD28
from (select EQUIP,UNIT,POW,CHANCE from SPK_CONST where ID=46) tab1

union

--Horizont
select 3,49.0001,'Horizont+BQ',NULL,NULL,NULL,NULL,@ZAGRUZ_O_TEMPL31 as TMPLAN,@FACT31 as FACT,

cast( (case when @ZAGRUZ_O_TEMPL31>0 then  @FACT31 * 100 /  @ZAGRUZ_O_TEMPL31 end)  as decimal(18,3)) as PROC_VIP, cast((@ZAGRUZ_O_TEMPL31 /  @num_of_day ) as decimal(18,3)) ZADANIE_NA_DEN,
@RD31


union

--сдано
select 3,50,EQUIP,UNIT,null,null as PERCENT_ZAG,POW,@ZAGRUZ_O_TEMPL11 as TMPLAN,@FACT11 as FACT,
cast( (case when @ZAGRUZ_O_TEMPL11>0 then @FACT11 * 100 /  @ZAGRUZ_O_TEMPL11 end ) as decimal(18,3)) as PROC_VIP, cast((@ZAGRUZ_O_TEMPL11 /  @num_of_day )  as decimal(18,3)) ZADANIE_NA_DEN,
@RD11
from (select EQUIP,UNIT,POW,CHANCE from SPK_CONST where ID=23) tab1
union
--изготовл
select 3,51,EQUIP,UNIT,null,null as PERCENT_ZAG,POW,@ZAGRUZ_O_TEMPL11 as TMPLAN,@FACT12 as FACT,


cast( (case when @ZAGRUZ_O_TEMPL11>0 then @FACT12 * 100 /  @ZAGRUZ_O_TEMPL11 end) as decimal(18,3)) as PROC_VIP  ,


cast((@ZAGRUZ_O_TEMPL11 /  @num_of_day ) as decimal(18,3)) ZADANIE_NA_DEN,
@RD12
from (select EQUIP,UNIT,POW,CHANCE from SPK_CONST where ID=24) tab1

/***************/

union

/************************************************************/



select 3,55,NULL,Null,Null,Null,Null,Null,Null,Null,Null,Null


union
SELECT 3,56 as NUMER,'Всего по цеху' , 'тыс л/отт' 
,null,null ,null ,sum (TMPLAN)  ,SUM (FACT) ,cast (SUM (FACT) as decimal (28,3))/ 
cast (sum (TMPLAN) as decimal (28,3))*100   ,sum(ZADANIE_NA_DEN) ,
sum (RD)
from
 (

 select @ZAGRUZ_O_TEMPL11 as TMPLAN,@FACT11 as FACT,


cast((case when @ZAGRUZ_O_TEMPL11>0 then @FACT11 * 100 /  @ZAGRUZ_O_TEMPL11 end ) as decimal(18,3)) as PROC_VIP


,


cast((@ZAGRUZ_O_TEMPL11 /  @num_of_day ) as decimal(18,3))  ZADANIE_NA_DEN,
@RD11 as RD


union
select @ZAGRUZ_O_TEMPL7 as TMPLAN,@FACT7 as FACT,

cast((case when @ZAGRUZ_O_TEMPL7>0 then  @FACT7 * 100 /  @ZAGRUZ_O_TEMPL7 end) as decimal(18,3)) as PROC_VIP,


cast((@ZAGRUZ_O_TEMPL7 /  @num_of_day ) as decimal(18,3)) ZADANIE_NA_DEN,
@RD7 as RD

union

select @ZAGRUZ_O_TEMPL3 as TMPLAN,@FACT3 as FACT,
cast((case when @ZAGRUZ_O_TEMPL3>0 then @FACT3 * 100 /  @ZAGRUZ_O_TEMPL3 end)  as decimal(18,3)) as PROC_VIP,cast((@ZAGRUZ_O_TEMPL3 /  @num_of_day ) as decimal(18,3))  ZADANIE_NA_DEN,
@RD3 AS RD




) as nnn




union
select 3,25,EQUIP,UNIT,null,null as PERCENT_ZAG,POW,@ZAGRUZ_O_TEMPL17 as TMPLAN ,@FACT17  as FACT,

cast( (case when @ZAGRUZ_O_TEMPL17>0 then @FACT17 * 100 /  @ZAGRUZ_O_TEMPL17 end ) as decimal(18,3))


as PROC_VIP, 


cast((@ZAGRUZ_O_TEMPL17 /  @num_of_day ) as decimal(18,3))  ZADANIE_NA_DEN,
@RD17
from (select EQUIP,UNIT,POW,CHANCE from SPK_CONST where ID=35) tab1 --шитье





insert into SPK_RESULT
select 3,53,'Газеты' , 'тыс л/отт', NULL,NULL,NULL,@ZAGRUZ_O_TEMPL30 ,@FACT30,0,0,@RD30
union
select 3,52,'прочая' , 'тыс л/отт', NULL,NULL,NULL,@ZAGRUZ_O_TEMPL29,@FACT29,0,0,@RD29

/****************/
declare @NUMs TABLE  (NUM varchar(255))

insert into @NUMs
 select 
 h.NUM 


 from ZAK_OPER o
left join ZAK_WORK w on w.ID_ZAK_OPER=o.ID
left join ZAK_PROPS p164 on p164.CODE=164 and p164.OBJECTID=o.UNZ
inner join ZAK_HEAD h on h.UNZ = o.UNZ
 where 
 
  p164.VALUE in ('Папка с карточками' , 'Листы','') and
 o.ID_OPER=2097846 and
 w.W_DATA between @Date1 and @Date1+1 and

 not (h.KLIENT in ('Просвещение','Полиграф Трейд')) and not (upper(h.NAIM)like '%ТЕРМОУП%')
 and

(  
SELECT count (distinct VALUE ) from ZAK_PROPS where OBJECTID in
(
select ID_ZAK_VIDS from ZAK_VIDS where o.UNZ=ZAK_VIDS.UNZ
) and CODE=511
) > 1 


union
select h.NUM 


 from ZAK_OPER o
left join ZAK_WORK w on w.ID_ZAK_OPER=o.ID
left join ZAK_PROPS p164 on p164.CODE=164 and p164.OBJECTID=o.UNZ
inner join ZAK_HEAD h on h.UNZ = o.UNZ
 where 
 
  p164.VALUE in ('Папка с карточками' , 'Листы','') and
 o.ID_OPER=2097846 and
 w.W_DATA between @dtDate and (@dtDateTo+1)-0.00001 and

 not (h.KLIENT in ('Просвещение','Полиграф Трейд')) and not (upper(h.NAIM)like '%ТЕРМОУП%')
 and
 (  
SELECT count (distinct VALUE ) from ZAK_PROPS where OBJECTID in
(
select ID_ZAK_VIDS from ZAK_VIDS where o.UNZ=ZAK_VIDS.UNZ
) and CODE=511
) > 1 



 /****************/

if (select count('1') from @NUMs) > 0 
begin
--проверка на случай если листы (или другая прочая продукция) имеет в деталях разный объем. в этом случае в расчете листов оттисков берётся минимальный объем(расчет выше)
--а тут выводится в таблицу предупреждение , что объемы разные 

insert into SPK_RESULT
select 3,1000,'Ниже заказы "Прочие" у которых разные объемы в деталях"' , NULL, NULL,NULL,NULL,NULL ,NULL,NULL,NULL,NULL

insert into SPK_RESULT
select 3,1001,NUM , NULL, NULL,NULL,NULL,NULL ,NULL,NULL,NULL,NULL
from @NUMs 



end


drop TABLE #PBC
drop TABLE #PBC_TEMPLAN
end



/*
go



exec SPK_TOTAL_PLAN1
		19,
        '08.02.2021',
        6



*/