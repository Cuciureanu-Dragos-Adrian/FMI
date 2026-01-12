--ORDER
drop table rezervare;
drop table agent;
drop table agentie;
drop table recenzie;
drop table client;
drop table camera;
drop table tip_camera;
drop table angajat;
drop table tip_job;
drop table carac_hotel;
drop table caracteristica;
drop table hotel;
drop table locatie;
drop table critic;



--1 LOCATIE
create table locatie
(
loc_id number(10),
tara varchar2(20),
oras varchar2(20),
adresa varchar2(50),
constraint locatie_pk primary key(loc_id)
);


--2 CRITIC
create table critic
(
critic_id number(10),
nr_stele number(10),
nume varchar2(20),
constraint critic_pk primary key(critic_id)
);


--3 HOTEL
create table hotel
(
hotel_id number(10),
loc_id number(10),
critic_id number(10),
nume varchar2(20),
adresa_email varchar2(20),
descriere varchar2(255),
site_hotel varchar2(255),
constraint hotel_pk primary key(hotel_id),
constraint hotel_locatie_fk foreign key (loc_id) references locatie(loc_id),
constraint hotel_critic_fk foreign key (critic_id) references critic(critic_id)
);


--4 CARACTERISTICA
create table caracteristica
(
caracteristica_id number(10),
nume_caracteristica varchar2(20),
descriere_caracteristica varchar2(255),
constraint caracteristica_pk primary key(caracteristica_id)
);


--5 CARACTERISTICA_HOTEL
create table carac_hotel
(
hotel_id number(10),
caracteristica_id number(10),
constraint carac_hotel_pk primary key (hotel_id, caracteristica_id),
constraint carac_hotel_hotel_fk foreign key (hotel_id) references hotel(hotel_id),
constraint carac_hotel_caracteristica_fk foreign key (caracteristica_id) references caracteristica(caracteristica_id)
);


--6 TIP_JOB
create table tip_job
(
job_id number(10),
nume_job varchar2(20),
salariu_job number(10),
constraint tip_job_pk primary key(job_id),
constraint check_salariu_job check (salariu_job >= 0)
);


--7 ANGAJAT
create table angajat
(
angajat_id number(10),
hotel_id number(10),
job_id number(10),
nume varchar2(20),
prenume varchar2(20),
constraint angajat_pk primary key(angajat_id),
constraint angajat_hotel_fk foreign key (hotel_id) references hotel(hotel_id),
constraint angajat_tip_job_fk foreign key (job_id) references tip_job(job_id)
);


--8 TIP_CAMERA
create table tip_camera
(
tip_camera_id number(10),
nume_tip_camera varchar2(20),
nr_camere number(10),
descriere varchar2(255),
constraint tip_camera_pk primary key(tip_camera_id)
);


--9 CAMERA
create table camera
(
camera_id number(10),
tip_camera_id number(10),
hotel_id number(10),
numar_camera number(10),
etaj_camera number(10),
constraint camera_pk primary key(camera_id),
constraint camera_hotel_fk foreign key (hotel_id) references hotel(hotel_id),
constraint camera_tip_camera_fk foreign key (tip_camera_id) references tip_camera(tip_camera_id)
);


--10 CLIENT
create table client
(
client_id number(10),
nume varchar2(20),
prenume varchar2(20),
adresa_email varchar2(20),
constraint client_pk primary key(client_id)
);


--11 RECENZIE
create table recenzie
(
recenzie_id number(10),
client_id number(10),
sumar varchar2(20),
descriere varchar2(20),
constraint recenzie_pk primary key(recenzie_id),
constraint recenzie_client_fk foreign key (client_id) references client(client_id)
);


--12 AGENTIE
create table agentie
(
agentie_id number(10),
nr_rezervari_facute number(10),
adresa_email varchar2(20),
constraint agentie_pk primary key(agentie_id),
constraint check_nr_rezervari_facute check (nr_rezervari_facute >= 0)
);


--13 AGENT
create table agent
(
agent_id number(10),
agentie_id number(10),
nume varchar2(20),
prenume varchar2(20),
adresa_email varchar2(20),
constraint agent_pk primary key(agent_id),
constraint agent_agentie_fk foreign key (agentie_id) references agentie(agentie_id)
);


--14 REZERVARE
create table rezervare
(
rezervare_id number(10),
client_id number(10),
agent_id number(10),
camera_id number(10),
data_inceput date,
data_final date,
suma_achitata number(10),
constraint rezervare_pk primary key(rezervare_id, client_id, agent_id, camera_id),
constraint rezervare_client_fk foreign key (client_id) references client(client_id),
constraint rezervare_agent_fk foreign key (agent_id) references agent(agent_id),
constraint rezervare_camera_fk foreign key (camera_id) references camera(camera_id),
constraint check_suma_achitata check (suma_achitata >= 0)
);


--1 introducere date in critic
create sequence valori
start with 1
increment by 1
minvalue 0
maxvalue 1000
nocycle;

delete from critic;

insert into critic values(valori.nextval, 2, 'Giuseppe');
insert into critic values(valori.nextval, 4, 'Giuseppe');
insert into critic values(valori.nextval, 5, 'Giuseppe');
insert into critic values(valori.nextval, 3, 'Arta');
insert into critic values(valori.nextval, 4, 'Kabs');
insert into critic values(valori.nextval, 7, 'Alias');

drop sequence valori;

select * from critic;



--2 introducere date in locatie
create sequence valori
start with 1
increment by 1
minvalue 0
maxvalue 1000
nocycle;

delete from locatie;

insert into locatie values(valori.nextval, 'Romania', 'Bucuresti', 'str. Caiman nr. 3');
insert into locatie values(valori.nextval, 'Egipt', 'Cairo', 'str. Kaizo nr. 2');
insert into locatie values(valori.nextval, 'Japonia', 'Kyoto', 'str. Kawla nr. 5');
insert into locatie values(valori.nextval, 'Franta', 'Lyon', 'str. Defile');
insert into locatie values(valori.nextval, 'EA', 'Dubai', 'str. Richez');
insert into locatie values(valori.nextval, 'Belgia', 'Gent', 'Complex Omega');

drop sequence valori;

select * from locatie;



--3 introducere date in hotel
create sequence valori
start with 1
increment by 1
minvalue 0
maxvalue 1000
nocycle;

delete from hotel;

insert into hotel values(valori.nextval, 1, 2, 'Trivago', 'hotel1@gmail.com', 'best hotel', 'hotel1.com');
insert into hotel values(valori.nextval, 2, 4, 'Cairon', 'hotel2@gmail.com', 'best hotel', 'hotel2.com');
insert into hotel values(valori.nextval, 4, 5, 'Le francois', 'hotel3@gmail.com', 'best hotel', 'hotel3.com');
insert into hotel values(valori.nextval, 6, 1, 'Hotel G1', 'hotel4@gmail.com', 'best hotel', 'hotel4.com');
insert into hotel values(valori.nextval, 6, 3, 'Hotel G2', 'hotel5@gmail.com', 'best hotel', 'hotel5.com');
insert into hotel values(valori.nextval, 5, 6, 'Burn Haj', 'hotel6@gmail.com', 'the actual best hotel', 'hotel6.com');

drop sequence valori;

select * from hotel;


--4 introducere date in caracteristica
create sequence valori
start with 1
increment by 1
minvalue 0
maxvalue 1000
nocycle;

delete from caracteristica;

insert into caracteristica values(valori.nextval, 'piscina', 'piscina de 20 de oameni');
insert into caracteristica values(valori.nextval, 'piscina', 'piscina de 30 de oameni');
insert into caracteristica values(valori.nextval, 'mini-piscina', 'piscina de 10 de copii');
insert into caracteristica values(valori.nextval, 'parcare', 'parcare de 15 masini');
insert into caracteristica values(valori.nextval, 'jacuzzi', 'relaxare');
insert into caracteristica values(valori.nextval, 'heliport', 'pt cei mai buni');
insert into caracteristica values(valori.nextval, 'sauna', 'tehnic full spa');
insert into caracteristica values(valori.nextval, 'aqua-park', 'o distratie bine meritata');

drop sequence valori;

select * from caracteristica;


--5  introducere date in carac_hotel
create sequence valori
start with 1
increment by 1
minvalue 0
maxvalue 1000
nocycle;

delete from carac_hotel;

insert into carac_hotel values(1, 1);
insert into carac_hotel values(1, 3);
insert into carac_hotel values(1, 4);
insert into carac_hotel values(1, 7);
insert into carac_hotel values(6, 1);
insert into carac_hotel values(6, 2);
insert into carac_hotel values(6, 3);
insert into carac_hotel values(6, 4);
insert into carac_hotel values(6, 5);
insert into carac_hotel values(6, 6);
insert into carac_hotel values(6, 7);
insert into carac_hotel values(6, 8);
insert into carac_hotel values(2, 1);
insert into carac_hotel values(2, 4);
insert into carac_hotel values(3, 1);
insert into carac_hotel values(3, 4);
insert into carac_hotel values(4, 1);
insert into carac_hotel values(4, 4);
insert into carac_hotel values(5, 1);
insert into carac_hotel values(5, 4);

drop sequence valori;

select * from carac_hotel
order by 1;


--6 introducere date in tip_job
create sequence valori
start with 1
increment by 1
minvalue 0
maxvalue 1000
nocycle;

delete from tip_job;

insert into tip_job values(valori.nextval, 'menajera', 1800);
insert into tip_job values(valori.nextval, 'barman', 3200);
insert into tip_job values(valori.nextval, 'receptioner', 2300);
insert into tip_job values(valori.nextval, 'hamal', 2200);
insert into tip_job values(valori.nextval, 'bucatar chef', 2700);
insert into tip_job values(valori.nextval, 'valet', 2200);
insert into tip_job values(valori.nextval, 'manager', 12000);

drop sequence valori;

select * from tip_job;


--7 introducere date in angajat
create sequence valori
start with 1
increment by 1
minvalue 0
maxvalue 1000
nocycle;

delete from angajat;

insert into angajat values(valori.nextval, 6, 1, 'Nume1', 'Prenume1');
insert into angajat values(valori.nextval, 6, 2, 'Nume2', 'Prenume2');
insert into angajat values(valori.nextval, 6, 3, 'Nume3', 'Prenume3');
insert into angajat values(valori.nextval, 6, 4, 'Nume4', 'Prenume4');
insert into angajat values(valori.nextval, 6, 5, 'Nume5', 'Prenume5');
insert into angajat values(valori.nextval, 6, 6, 'Nume6', 'Prenume6');
insert into angajat values(valori.nextval, 6, 7, 'eu', 'tot eu');
insert into angajat values(valori.nextval, 1, 1, 'Hadirca', 'Denis');
insert into angajat values(valori.nextval, 1, 2, 'Nelu', 'Cristi');
insert into angajat values(valori.nextval, 1, 3, 'Podaru', 'Edi');
insert into angajat values(valori.nextval, 1, 4, 'Gruisterul', 'Gruia');
insert into angajat values(valori.nextval, 1, 5, 'Pod', 'Alex');
insert into angajat values(valori.nextval, 1, 6, 'Fane', 'Fane');
insert into angajat values(valori.nextval, 1, 7, 'Lene', 'Adi');

drop sequence valori;

select * from angajat;


--8 introducere date in tip_camera
create sequence valori
start with 1
increment by 1
minvalue 0
maxvalue 1000
nocycle;

delete from tip_camera;

insert into tip_camera values(valori.nextval, 'Normal', 2, 'cazare normala');
insert into tip_camera values(valori.nextval, 'Mini', 1, 'cazare');
insert into tip_camera values(valori.nextval, 'Apartament', 3, 'cazare pt o familie');
insert into tip_camera values(valori.nextval, 'Extra', 3, 'cazare pt cei instariti');
insert into tip_camera values(valori.nextval, 'Royal', 4, 'cazare doar pt cei mai buni');

drop sequence valori;

select * from tip_camera;


--9 introducere date in camera
create sequence valori
start with 1
increment by 1
minvalue 0
maxvalue 1000
nocycle;

delete from camera;

insert into camera values(valori.nextval, 1, 1, 111, 1);
insert into camera values(valori.nextval, 2, 1, 112, 1);
insert into camera values(valori.nextval, 3, 1, 113, 1);
insert into camera values(valori.nextval, 4, 1, 211, 2);
insert into camera values(valori.nextval, 1, 6, 111, 1);
insert into camera values(valori.nextval, 2, 6, 112, 1);
insert into camera values(valori.nextval, 3, 6, 113, 1);
insert into camera values(valori.nextval, 4, 6, 211, 2);
insert into camera values(valori.nextval, 5, 6, 311, 3);

drop sequence valori;

select * from camera;


--10 introducere date in client
create sequence valori
start with 1
increment by 1
minvalue 0
maxvalue 1000
nocycle;

delete from client;

insert into client values(valori.nextval, 'Popescu', 'Petru', 'petru@gmail.com');
insert into client values(valori.nextval, 'Barda', 'Nicu', 'nicui@gmail.com');
insert into client values(valori.nextval, 'Gruia', 'Gruia', 'gr@gmail.com');
insert into client values(valori.nextval, 'Beca', 'Bunu', 'b1@gmail.com');
insert into client values(valori.nextval, 'Reda', 'Bdoi', 'b2@gmail.com');
insert into client values(valori.nextval, 'Extea', 'Btrei', 'b3@gmail.com');
insert into client values(valori.nextval, 'Alasa', 'Bpatru', 'b4@gmail.com');

drop sequence valori;

select * from client
order by 1;


--11 introducere date in recenzie
create sequence valori
start with 1
increment by 1
minvalue 0
maxvalue 1000
nocycle;

delete from recenzie;

insert into recenzie values(valori.nextval, 1, 'ok', 'a fost ok');
insert into recenzie values(valori.nextval, 1, 'bun', 'mi-a placut');
insert into recenzie values(valori.nextval, 3, 'rau', 'a fost nasol');
insert into recenzie values(valori.nextval, 3, 'bun', 'm-am razgandit');
insert into recenzie values(valori.nextval, 3, 'ok', 'de fapt, poate');

drop sequence valori;

select * from recenzie
order by 1;


--12 introducere date in agentie
create sequence valori
start with 1
increment by 1
minvalue 0
maxvalue 1000
nocycle;

delete from agentie;

insert into agentie values(valori.nextval, 12, 'agentie1@gmail.com');
insert into agentie values(valori.nextval, 5, 'agentie2@gmail.com');
insert into agentie values(valori.nextval, 0, 'agentie3@gmail.com');
insert into agentie values(valori.nextval, 0, 'agentie4@gmail.com');
insert into agentie values(valori.nextval, 0, 'agentie5@gmail.com');

drop sequence valori;

select * from agentie
order by 1;


--13 introducere date in agent
create sequence valori
start with 1
increment by 1
minvalue 0
maxvalue 1000
nocycle;

delete from agent;

insert into agent values(valori.nextval, 1, 'Arox', 'Aunu', 'a1@gmail.com');
insert into agent values(valori.nextval, 1, 'Tevas', 'Adoi', 'a2@gmail.com');
insert into agent values(valori.nextval, 1, 'Osfa', 'Atrie', 'a3@gmail.com');
insert into agent values(valori.nextval, 2, 'Pierce', 'Apatru', 'a4@gmail.com');
insert into agent values(valori.nextval, 2, 'Likan', 'Acinci', 'a5@gmail.com');

drop sequence valori;

select * from agent
order by 1;


--14 introducere date in rezervare
create sequence valori
start with 1
increment by 1
minvalue 0
maxvalue 1000
nocycle;

delete from rezervare;

insert into rezervare values(valori.nextval, 2, 2, 1, 
to_date('14-10-2021', 'DD-MM-YYYY'), to_date('19-10-2021', 'DD-MM-YYYY'), 1200);
insert into rezervare values(valori.nextval, 1, 4, 3,
to_date('4-9-2021', 'DD-MM-YYYY'), to_date('14-9-2021', 'DD-MM-YYYY'), 1500);
insert into rezervare values(valori.nextval, 3, 3, 4,
to_date('1-10-2021', 'DD-MM-YYYY'), to_date('14-10-2021', 'DD-MM-YYYY'), 1800);
insert into rezervare values(valori.nextval, 4, 1, 8,
to_date('14-8-2021', 'DD-MM-YYYY'), to_date('14-9-2021', 'DD-MM-YYYY'), 10000);
insert into rezervare values(valori.nextval, 7, 1, 9,
to_date('14-9-2021', 'DD-MM-YYYY'), to_date('10-10-2021', 'DD-MM-YYYY'), 15000);
insert into rezervare values(valori.nextval, 6, 2, 9,
to_date('18-9-2021', 'DD-MM-YYYY'), to_date('10-10-2021', 'DD-MM-YYYY'), 14000);
insert into rezervare values(valori.nextval, 5, 4, 9,
to_date('14-10-2021', 'DD-MM-YYYY'), to_date('30-10-2021', 'DD-MM-YYYY'), null);
insert into rezervare values(valori.nextval, 7, 1, 9,
to_date('14-9-2022', 'DD-MM-YYYY'), to_date('10-10-2022', 'DD-MM-YYYY'), 18000);
insert into rezervare values(valori.nextval, 6, 2, 9,
to_date('18-9-2022', 'DD-MM-YYYY'), to_date('10-10-2022', 'DD-MM-YYYY'), 16000);
insert into rezervare values(valori.nextval, 5, 1, 9,
to_date('14-10-2022', 'DD-MM-YYYY'), to_date('30-10-2022', 'DD-MM-YYYY'), 12000);

drop sequence valori;

select * from rezervare
order by 1;









