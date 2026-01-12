drop table recenzie;
drop table rezervare;
drop table agent;
drop table agentie;
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
numar_angajati number(10),
salariu_minim number(10),
salariu_maxim number(10),
constraint tip_job_pk primary key(job_id)
);


--7 ANGAJAT
create table angajat
(
angajat_id number(10),
hotel_id number(10),
job_id number(10),
nume varchar2(20),
prenume varchar2(20),
salariu number(10),
constraint angajat_pk primary key(angajat_id),
constraint angajat_hotel_fk foreign key (hotel_id) references hotel(hotel_id),
constraint angajat_tip_job_fk foreign key (job_id) references tip_job(job_id),
constraint check_salariu check (salariu >= 0)
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


--11 AGENTIE
create table agentie
(
agentie_id number(10),
nr_rezervari_facute number(10),
adresa_email varchar2(20),
constraint agentie_pk primary key(agentie_id),
constraint check_nr_rezervari_facute check (nr_rezervari_facute >= 0)
);


--12 AGENT
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


--13 REZERVARE
create table rezervare
(
rezervare_id number(10),
client_id number(10),
agent_id number(10),
camera_id number(10),
data_inceput date,
data_final date,
suma_achitata number(10),
constraint rezervare_pk primary key(rezervare_id),
constraint rezervare_client_fk foreign key (client_id) references client(client_id),
constraint rezervare_agent_fk foreign key (agent_id) references agent(agent_id),
constraint rezervare_camera_fk foreign key (camera_id) references camera(camera_id),
constraint check_suma_achitata check (suma_achitata >= 0)
);


--14 RECENZIE
create table recenzie
(
recenzie_id number(10),
rezervare_id number(10),
sumar varchar2(20),
descriere varchar2(20),
constraint recenzie_pk primary key(recenzie_id),
constraint recenzie_rezervare_fk foreign key (rezervare_id) references rezervare(rezervare_id)
);