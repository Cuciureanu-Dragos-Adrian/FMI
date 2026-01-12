--1 introducere date in critic
create sequence valori
start with 1
increment by 1
minvalue 0
maxvalue 1000
nocycle;

insert into critic values(valori.nextval, 2, 'Giuseppe');
insert into critic values(valori.nextval, 4, 'Giuseppe');
insert into critic values(valori.nextval, 5, 'Giuseppe');
insert into critic values(valori.nextval, 3, 'Arta');
insert into critic values(valori.nextval, 4, 'Kabs');
insert into critic values(valori.nextval, 7, 'Alias');

drop sequence valori;

--select * 
--from critic;



--2 introducere date in locatie
create sequence valori
start with 1
increment by 1
minvalue 0
maxvalue 1000
nocycle;

insert into locatie values(valori.nextval, 'Romania', 'Bucuresti', 'str. Caiman nr. 3');
insert into locatie values(valori.nextval, 'Egipt', 'Cairo', 'str. Kaizo nr. 2');
insert into locatie values(valori.nextval, 'Japonia', 'Kyoto', 'str. Kawla nr. 5');
insert into locatie values(valori.nextval, 'Franta', 'Paris', 'str. Defile');
insert into locatie values(valori.nextval, 'EA', 'Dubai', 'str. Richez');
insert into locatie values(valori.nextval, 'Belgia', 'Gent', 'Complex Omega');
insert into locatie values(valori.nextval, 'Japonia', 'Paris', 'str. mon Paris nr. 39');

drop sequence valori;

--select * 
--from locatie;



--3 introducere date in hotel
create sequence valori
start with 1
increment by 1
minvalue 0
maxvalue 1000
nocycle;

insert into hotel values(valori.nextval, 1, 2, 'Trivago', 'hotel1@gmail.com', 'best hotel', 'hotel1.com');
insert into hotel values(valori.nextval, 2, 4, 'Cairon', 'hotel2@gmail.com', 'best hotel', 'hotel2.com');
insert into hotel values(valori.nextval, 4, 5, 'Le francois', 'hotel3@gmail.com', 'best hotel', 'hotel3.com');
insert into hotel values(valori.nextval, 6, 1, 'Hotel G1', 'hotel4@gmail.com', 'best hotel', 'hotel4.com');
insert into hotel values(valori.nextval, 6, 3, 'Hotel G2', 'hotel5@gmail.com', 'best hotel', 'hotel5.com');
insert into hotel values(valori.nextval, 5, 6, 'Burn Haj', 'hotel6@gmail.com', 'the actual best hotel', 'hotel6.com');

drop sequence valori;

--select * 
--from hotel;


--4 introducere date in caracteristica
create sequence valori
start with 1
increment by 1
minvalue 0
maxvalue 1000
nocycle;

insert into caracteristica values(valori.nextval, 'piscina', 'piscina de 20 de oameni');
insert into caracteristica values(valori.nextval, 'piscina', 'piscina de 30 de oameni');
insert into caracteristica values(valori.nextval, 'mini-piscina', 'piscina de 10 de copii');
insert into caracteristica values(valori.nextval, 'parcare', 'parcare de 15 masini');
insert into caracteristica values(valori.nextval, 'jacuzzi', 'relaxare');
insert into caracteristica values(valori.nextval, 'heliport', 'pt cei mai buni');
insert into caracteristica values(valori.nextval, 'sauna', 'tehnic full spa');
insert into caracteristica values(valori.nextval, 'aqua-park', 'o distratie bine meritata');
insert into caracteristica values(valori.nextval, 'submarin', 'asa da');

drop sequence valori;

--select * 
--from caracteristica;


--5  introducere date in carac_hotel
create sequence valori
start with 1
increment by 1
minvalue 0
maxvalue 1000
nocycle;

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

--select * 
--from carac_hotel
--order by 1;


--6 introducere date in tip_job
create sequence valori
start with 1
increment by 1
minvalue 0
maxvalue 1000
nocycle;

insert into tip_job values(valori.nextval, 'menajera', 0, null, null);
insert into tip_job values(valori.nextval, 'barman', 0, null, null);
insert into tip_job values(valori.nextval, 'receptioner', 0, null, null);
insert into tip_job values(valori.nextval, 'hamal', 0, null, null);
insert into tip_job values(valori.nextval, 'bucatar chef', 0, null, null);
insert into tip_job values(valori.nextval, 'valet', 0, null, null);
insert into tip_job values(valori.nextval, 'manager', 0, null, null);
insert into tip_job values(valori.nextval, 'bagator de seama', 0, null, null);

drop sequence valori;

--select * 
--from tip_job;


--7 introducere date in angajat
create sequence valori
start with 1
increment by 1
minvalue 0
maxvalue 1000
nocycle;

insert into angajat values(valori.nextval, 6, 1, 'Nume1', 'Prenume1', 1000);
insert into angajat values(valori.nextval, 6, 2, 'Nume2', 'Prenume2', 2000);
insert into angajat values(valori.nextval, 6, 3, 'Nume3', 'Prenume3', 3000);
insert into angajat values(valori.nextval, 6, 4, 'Nume4', 'Prenume4', 4800);
insert into angajat values(valori.nextval, 6, 5, 'Nume5', 'Prenume5', 5000);
insert into angajat values(valori.nextval, 6, 6, 'Nume6', 'Prenume6', 6000);
insert into angajat values(valori.nextval, 6, 7, 'eu', 'tot eu', 10000);
insert into angajat values(valori.nextval, 1, 1, 'Hadirca', 'Denis', 1500);
insert into angajat values(valori.nextval, 1, 2, 'Nelu', 'Cristi', 3500);
insert into angajat values(valori.nextval, 1, 3, 'Podaru', 'Edi', 4200);
insert into angajat values(valori.nextval, 1, 4, 'Gruisterul', 'Gruia', 4800);
insert into angajat values(valori.nextval, 1, 5, 'Pod', 'Alex', 3000);
insert into angajat values(valori.nextval, 1, 6, 'Fane', 'Fane', 2800);
insert into angajat values(valori.nextval, 1, 7, 'Lene', 'Adi', 5000);
insert into angajat values(valori.nextval, 1, 1, 'Hadirica', 'Apyr', 1500);

drop sequence valori;

--select * 
--from angajat;


--8 introducere date in tip_camera
create sequence valori
start with 1
increment by 1
minvalue 0
maxvalue 1000
nocycle;

insert into tip_camera values(valori.nextval, 'Normal', 2, 'cazare normala');
insert into tip_camera values(valori.nextval, 'Mini', 1, 'cazare');
insert into tip_camera values(valori.nextval, 'Apartament', 3, 'cazare pt o familie');
insert into tip_camera values(valori.nextval, 'Extra', 3, 'cazare pt cei instariti');
insert into tip_camera values(valori.nextval, 'Royal', 4, 'cazare doar pt cei mai buni');

drop sequence valori;

--select * 
--from tip_camera;


--9 introducere date in camera
create sequence valori
start with 1
increment by 1
minvalue 0
maxvalue 1000
nocycle;

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

--select * 
--from camera;


--10 introducere date in client
create sequence valori
start with 1
increment by 1
minvalue 0
maxvalue 1000
nocycle;

insert into client values(valori.nextval, 'Popescu', 'Petru', 'petru@gmail.com');
insert into client values(valori.nextval, 'Barda', 'Nicu', 'nicui@gmail.com');
insert into client values(valori.nextval, 'Gruia', 'Gruia', 'gr@gmail.com');
insert into client values(valori.nextval, 'Beca', 'Bunu', 'b1@gmail.com');
insert into client values(valori.nextval, 'Reda', 'Bdoi', 'b2@gmail.com');
insert into client values(valori.nextval, 'Extea', 'Btrei', 'b3@gmail.com');
insert into client values(valori.nextval, 'Alasa', 'Bpatru', 'b4@gmail.com');

drop sequence valori;

--select * 
--from client
--order by 1;


--11 introducere date in agentie
create sequence valori
start with 1
increment by 1
minvalue 0
maxvalue 1000
nocycle;

insert into agentie values(valori.nextval, 0, 'agentie1@gmail.com');
insert into agentie values(valori.nextval, 0, 'agentie2@gmail.com');
insert into agentie values(valori.nextval, 0, 'agentie3@gmail.com');
insert into agentie values(valori.nextval, 0, 'agentie4@gmail.com');
insert into agentie values(valori.nextval, 0, 'agentie5@gmail.com');

drop sequence valori;

--select * 
--from agentie
--order by 1;


--12 introducere date in agent
create sequence valori
start with 1
increment by 1
minvalue 0
maxvalue 1000
nocycle;

insert into agent values(valori.nextval, 1, 'Arox', 'Aunu', 'a1@gmail.com');
insert into agent values(valori.nextval, 4, 'Tevas', 'Adoi', 'a2@gmail.com');
insert into agent values(valori.nextval, 1, 'Osfa', 'Atrie', 'a3@gmail.com');
insert into agent values(valori.nextval, 2, 'Pierce', 'Apatru', 'a4@gmail.com');
insert into agent values(valori.nextval, 2, 'Likan', 'Acinci', 'a5@gmail.com');

drop sequence valori;

--select * 
--from agent
--order by 1;


--13 introducere date in rezervare
create sequence valori
start with 1
increment by 1
minvalue 0
maxvalue 1000
nocycle;

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
insert into rezervare values(valori.nextval, 6, 3, 8,
to_date('18-9-2023', 'DD-MM-YYYY'), to_date('10-10-2023', 'DD-MM-YYYY'), 9000);

drop sequence valori;

--select * 
--from rezervare
--order by 1;


--14 introducere date in recenzie
create sequence valori
start with 1
increment by 1
minvalue 0
maxvalue 1000
nocycle;

insert into recenzie values(valori.nextval, 1, 'ok', 'a fost ok');
insert into recenzie values(valori.nextval, 1, 'bun', 'mi-a placut');
insert into recenzie values(valori.nextval, 3, 'rau', 'a fost nasol');
insert into recenzie values(valori.nextval, 3, 'bun', 'm-am razgandit');
insert into recenzie values(valori.nextval, 3, 'ok', 'de fapt, poate');

drop sequence valori;

--select * 
--from recenzie
--order by 1;


commit;