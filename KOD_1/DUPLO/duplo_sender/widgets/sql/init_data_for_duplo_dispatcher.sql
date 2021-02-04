CREATE EXTENSION IF NOT EXISTS "uuid-ossp";



CREATE TABLE "violation_order" (

  "guid" UUID NOT NULL,
  "camera" varchar(255) NOT NULL,
  "camera_place" TEXT NOT NULL,
  "line_number" int NOT NULL,
  "violation_code" int NOT NULL,
  "registration_number" varchar(255) NOT NULL,
  "country" varchar(255) NOT NULL, 
  "timestamp" bigint NOT NULL,
  "latitude" decimal NOT NULL,
  "longitude" decimal NOT NULL,
  "recognition_accuracy" decimal NOT NULL,
  "speed" int NOT NULL,
  "speed_limit" int NOT NULL,
  "direction" int NOT NULL,
 
  "photo_ts" varchar(255) NOT NULL,
  "photo_grz" varchar(255) NOT NULL,
  "additional_data" varchar(255) ARRAY NOT NULL,

   "duplo_status" varchar(255) NOT NULL,
   "timestamp_send_xml" timestamp DEFAULT now()
--example:
--ata_for_duplo_dispatcher=# insert into violation_order  values(uuid_generate_v4(),'1','tut',1,8,'45RUS','rus',123456,1.25,2.45,89.0,87,80,1,'/home/user/1.jpg','/2.jpg','{"3.mpeg4","4.jpg"}','OK');

);










