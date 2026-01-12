set serveroutput on;

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

--select * 
--from critic;



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

delete from hotel;

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

delete from caracteristica;

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

delete from tip_job;

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

delete from angajat;

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

delete from tip_camera;

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

--select * 
--from camera;


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

delete from agentie;

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

delete from agent;

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

delete from recenzie;

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




--problema 6: afisati fiecare client(nume, prenume, id) impreuna cu rezervarile pe care le-a efectuat 
--si cu suma valorilor acestora

--problema 7: afisati pentru fiecare job lista angajatiilor si in ce hotel lucreaza acestia in ordinea salariilor, 
--daca doi au acelasi salariu se afla pe acelasi loc, tratati cazul in care nu exista niciun angajat pe acel post

--problema 8: returnati numarul distinc de agenti care au ajutat la realizarea de o rezervare intr-o locatie data ca parametru

--problema 9: afisati clientii ce si-au rezervat o camera intr-un hotel ce detine o caracteristica data ca parametru 
--(ordonati dupa id si dupa suma achitata), tratati cazul in care nu exista niciun client

--problema 10: realizati un trigger de tip LMD la nivel de comanda, care permite ca tabelul 
--'ANGAJAT' sa nu poata fi updatat in weekend sau daca minutul este impar

--problema 11: realizati un trigger de tip LMD la nivel de linie, astfel incat de fiecare data cand se introduce o
--noua rezervare sa se mareasca numarul de rezervari facute pentru agentia ce a ajutat la realizarea acesteia

--problema 12: realizati un trigger de tip LDD care care pastreaza in tabela "log_comenzi" comenzile realizate
--in baza de date, retinandu-se utilizatorul, comanda realizata, tabel unde s-a realizat si data respectiva

--problema 14.1: realizati un trigger ce calculeaza pentru tabela 'TIP_ANGAJAT' cel mai mic si cel mai mare salariu

--problema 14.2: realizati un trigger ce nu lasa la update sau insert ca salariul unui angajat sa fie mai mare de 10 ori decat
--cel mai mic pentru a nu exista o dispersie prea mare, in cazul in care depaseste acea suma, va fi setata ca fiind ea


create or replace package CDA_proiect_SGBD
is
--problema 6
    procedure problema6;
    
--problema 7
    procedure problema7;

--problema 8
    function problema8(nume_oras locatie.oras%type) return number;

--problema 9
    procedure problema9(nume_carac caracteristica.nume_caracteristica%type);
end;
/

create or replace package body CDA_proiect_SGBD
is
--problema 6
    procedure problema6 is
    
        nr_clienti number;
        nr_rezervari number;
        idx_rezervare number;
        pret_om number;
    
        type client_record is record
            (id client.client_id%type,
            nume client.nume%type,
            prenume client.prenume%type);
        type tip_clienti is table of client_record;
        clienti tip_clienti := tip_clienti();
        
        type rezervare_record is record
            (id rezervare.rezervare_id%type,
            data_inceput rezervare.data_inceput%type,
            data_final rezervare.data_final%type,
            pret rezervare.suma_achitata%type);
        type tip_rezervare is varray(1000) of rezervare_record;
        rezervari tip_rezervare := tip_rezervare();
    
    begin
        select count(*) 
        into nr_clienti
        from client;
        
        clienti.extend(nr_clienti);
        
        select c.client_id, c.nume, c.prenume
        bulk collect into clienti
        from client c;
        
        for i in clienti.first..clienti.last loop
            idx_rezervare := 1;
            pret_om := 0;
            
            select count(*) 
            into nr_rezervari
            from rezervare r
            where r.client_id = clienti(i).id;
            
            dbms_output.put_line('Clientul ' || clienti(i).nume || ' ' || clienti(i).prenume || ' cu id-ul ' 
            || clienti(i).id || ' a avut ' || nr_rezervari || ' rezervari:');
            
            rezervari.extend(nr_rezervari);
            
            select r.rezervare_id, r.data_inceput, r.data_final, r.suma_achitata
            bulk collect into rezervari
            from rezervare r
            where r.client_id = clienti(i).id;
            
            for j in rezervari.first..rezervari.last loop
                dbms_output.put_line(idx_rezervare || '. Rezervarea cu id-ul ' || rezervari(j).id || ' in perioada ' ||
                rezervari(j).data_inceput || ' ' || rezervari(j).data_final || ' a costat ' || nvl(rezervari(j).pret, 0));
                
                pret_om := pret_om + nvl(rezervari(j).pret, 0);
                idx_rezervare := idx_rezervare + 1;
            end loop;
            
            rezervari.trim(nr_rezervari);
            
            dbms_output.put_line('Pretul total fiind de ' || pret_om);
            dbms_output.new_line();
        end loop;
    end;
    
    
--problema 7
    procedure problema7 is
    
        counter number;
        nume_job tip_job.nume_job%type;
        nume_angajat angajat.nume%type;
        nume_hotel hotel.nume%type;
        salariu_angajat angajat.salariu%type;
        salariu_anterior angajat.salariu%type;
        
        type refcursor is ref cursor;
        referinta_cursor refcursor;
        
        cursor c is 
            select j2.nume_job, cursor
                (select a.nume, a.salariu, h.nume
                from angajat a, tip_job j, hotel h
                where j.job_id = a.job_id 
                and j.job_id = j2.job_id
                and h.hotel_id = a.hotel_id
                order by a.salariu desc)
            from tip_job j2;
            
    begin
        open c;
        loop
            fetch c into nume_job, referinta_cursor;
            exit when c%notfound;
            
            dbms_output.put_line(nume_job || ':');
            
            counter := 0;
            salariu_anterior := -1;
            
            loop 
                fetch referinta_cursor into nume_angajat, salariu_angajat, nume_hotel;
                exit when referinta_cursor%notfound;
                
                if salariu_angajat <> salariu_anterior then
                    counter := counter + 1;
                    salariu_anterior := salariu_angajat;
                end if;
                
                dbms_output.put_line(counter || '. ' || nume_angajat || ' ' || salariu_angajat || ' ' || nume_hotel);
            end loop;
            
            if counter = 0 then 
                dbms_output.put_line('Nu exista niciun angajat.');
            end if;
            
            dbms_output.new_line();
            
        end loop;
        close c;
    end;
    
    
--problema 8
    function problema8(nume_oras locatie.oras%type) 
        return number is
        
        nr_clienti number;
        id_locatie hotel.hotel_id%type;
    
    begin
        select l.loc_id
        into id_locatie
        from locatie l
        where l.oras = nume_oras;
        
        select count(distinct a.agent_id)
        into nr_clienti
        from locatie l, hotel h, camera c, rezervare r, agent a
        where l.loc_id = h.loc_id
        and h.hotel_id = c.hotel_id
        and r.camera_id = c.camera_id
        and r.agent_id = a.agent_id
        and l.loc_id = id_locatie;
        
        return nr_clienti;
        
        exception
            when no_data_found then
                raise_application_error(-20000, 'nu exista orasul cu numele dat');
            when too_many_rows then
                raise_application_error(-20001, 'exista mai multe orase cu numele dat');
            when others then
                raise_application_error(-20002, 'alta eroare!');
    end;    
    
    
--problema 9
    procedure problema9(nume_carac caracteristica.nume_caracteristica%type) is
    
        counter number := 1;
        id_carac caracteristica.caracteristica_id%type;
    
        type client_record is record
            (id client.client_id%type,
            nume client.nume%type,
            nume_hotel hotel.nume%type,
            pret rezervare.suma_achitata%type);
        type tip_clienti is table of client_record;
        clienti tip_clienti := tip_clienti();
    
    begin
        select c.caracteristica_id
        into id_carac
        from caracteristica c
        where c.nume_caracteristica = nume_carac;
    
        select cl.client_id, cl.nume, h.nume, nvl(r.suma_achitata, 0)
        bulk collect into clienti
        from caracteristica car, carac_hotel ch, hotel h, camera cam, rezervare r, client cl
        where car.caracteristica_id = ch.caracteristica_id
        and ch.hotel_id = h.hotel_id
        and h.hotel_id = cam.hotel_id
        and cam.camera_id = r.camera_id
        and r.client_id = cl.client_id
        and car.caracteristica_id = id_carac
        order by cl.client_id, nvl(r.suma_achitata, 0);
        
        dbms_output.put_line('Caracteristica: ' || nume_carac);
    
        if clienti.count() = 0 then
            dbms_output.put_line('Nu exista clienti care au rezervat o camera la un hotel cu o astfel de caracteristica');
        else
            for i in clienti.first..clienti.last loop
                dbms_output.put_line(counter || '. Clientul '|| clienti(i).nume || ' cu id-ul ' || clienti(i).id ||
                ' a rezervat o camera la hotelul ' || clienti(i).nume_hotel || ' pentru ' || clienti(i).pret);
                
                counter := counter + 1;
            end loop;
        end if;
    
        exception
            when no_data_found then
                raise_application_error(-20000, 'nu exista caractersitica de hotel cu numele dat');
            when too_many_rows then
                raise_application_error(-20001, 'exista mai multe caracteristici de hotel cu numele dat');
            when others then
                raise_application_error(-20002, 'alta eroare!');
    end;
end;
/




--testare probleme
--declare
--    x number;
--    
--begin 
--problema 6
    --CDA_proiect_SGBD.problema6;
    
--problema 7
    --CDA_proiect_SGBD.problema7;
    
--problema 8
    --caz care functioneaza
    --x := CDA_proiect_SGBD.problema8('Dubai');
    --dbms_output.put_line(x || ' agenti');
    
    --caz nu exista orasul
    --x := CDA_proiect_SGBD.problema8('Lyon');
    
    --caz in care exista mai multe orase cu acelasi nume
    --x := CDA_proiect_SGBD.problema8('Paris');

--problem 9
    --caz care functioneaza
    --CDA_proiect_SGBD.problema9('parcare');
    
    --caz in nu exista caracteristica
    --CDA_proiect_SGBD.problema9('a');
    
    --caz in care exista mai multe caracteristici cu acelasi nume
    --CDA_proiect_SGBD.problema9('piscina');
    
    --caz in care nu exista clienti ce au rezervat o camera cu o astfel de caracteristica
    --CDA_proiect_SGBD.problema9('submarin');
--end;




--problema 10
create or replace trigger trigger_problema10
    before update on angajat

declare
    minut number(4);
    zi number(4);

begin
    minut := to_number(to_char(sysdate,'MI'));
    zi := to_number(to_char(sysdate,'D'));
    
    if (zi not between 2 and 6) then
        raise_application_error(-20001, 'tabelul nu poate fi updatat, deoarece este weekend');
    elsif (mod(minut, 2) = 1) then
        raise_application_error(-20002, 'tabelul nu poate fi updatat, deoarece minutul este par');
    end if;
end trigger_problema10;
/




--problema 11
create or replace trigger trigger_problema11
    after insert or delete on rezervare
    for each row

declare
    agentie_idd number(4);

begin
    if inserting then
        select ag.agentie_id
        into agentie_idd
        from agent a, agentie ag
        where a.agentie_id = ag.agentie_id
        and a.agent_id = :new.agent_id;
    
        update agentie 
        set nr_rezervari_facute = nr_rezervari_facute + 1 
        where agentie_id = agentie_idd;
        
    elsif deleting then
        select ag.agentie_id
        into agentie_idd
        from agent a, agentie ag
        where a.agentie_id = ag.agentie_id
        and a.agent_id = :old.agent_id;
    
        update agentie 
        set nr_rezervari_facute = nr_rezervari_facute - 1 
        where agentie_id = agentie_idd;

    end if;
end trigger_problema11;
/




--problema 12
drop table comenzi_log;

create table comenzi_log
(
    utilizator varchar2(30),
    comanda varchar2(20),
    tabel varchar2(30),
    data date
);


create or replace trigger trigger_problema12
    before create or alter or drop on database
    
begin
    insert into comenzi_log values (sys.login_user, sys.sysevent, sys.dictionary_obj_name, sysdate);
end;
/




--problema 14
create or replace package problema14 is 
    
    function get_numar_angajati (id tip_job.job_id%type) return number;
    function get_salariu_minim (id tip_job.job_id%type) return number;
    function get_salariu_maxim (id tip_job.job_id%type) return number;
    
    procedure initializeaza;
    procedure adauga_angajat(p_angajat_id angajat.angajat_id%type, p_salariu angajat.salariu%type, p_job_id tip_job.job_id%type);
    procedure sterge_angajat(p_angajat_id angajat.angajat_id%type, p_salariu angajat.salariu%type, p_job_id tip_job.job_id%type);
    procedure valideaza_stergere;    
    procedure valideaza_modificare;
    
end;
/

create or replace package body problema14 is
    type record_angajati is record (r_angajat_id angajat.angajat_id%type, r_salariu angajat.salariu%type, r_job_id tip_job.job_id%type);
    type tablou_angajati is table of record_angajati index by pls_integer;  
    
    t_angajati tablou_angajati;
    t_stersi tablou_angajati;
    
    modificare_in_proces boolean := false;
    
    
    function get_numar_angajati (id tip_job.job_id%type) 
        return number is
        
        numar_angajati number(10);
        
    begin
        select count(*)
        into numar_angajati
        from angajat a
        where a.job_id = id;
        
        return numar_angajati;
    end;
    
    
    function get_salariu_minim (id tip_job.job_id%type) 
        return number is
        
        salariu_minim number(10);
        
    begin
        select min(a.salariu)
        into salariu_minim
        from angajat a
        where a.job_id = id;
        
        return salariu_minim;
    end;
    
    
    function get_salariu_maxim (id tip_job.job_id%type) 
        return number is
        
        salariu_maxim number(10);
        
    begin
        select max(a.salariu)
        into salariu_maxim
        from angajat a
        where a.job_id = id;
        
        return salariu_maxim;
    end;
    
    
    procedure initializeaza is
    begin
        t_angajati.delete;
        t_stersi.delete;
    end;
    
    
    procedure adauga_angajat(p_angajat_id angajat.angajat_id%type, 
                             p_salariu angajat.salariu%type,
                             p_job_id tip_job.job_id%type) is
                          
        id pls_integer := t_angajati.count + 1;
        
    begin
        if modificare_in_proces = false then
            t_angajati(id).r_angajat_id := p_angajat_id;
            t_angajati(id).r_salariu := p_salariu;
            t_angajati(id).r_job_id := p_job_id;
        end if;
    end;
    
    
    procedure sterge_angajat(p_angajat_id angajat.angajat_id%type, 
                             p_salariu angajat.salariu%type,
                             p_job_id tip_job.job_id%type) is
                          
        id pls_integer := t_stersi.count + 1;
        
    begin
        if modificare_in_proces = false then
            t_stersi(id).r_angajat_id := p_angajat_id;
            t_stersi(id).r_salariu := p_salariu;
            t_stersi(id).r_job_id := p_job_id;
        end if;
    end;
   
   
    procedure valideaza_modificare is
        id pls_integer;
        p_salariu_maxim tip_job.salariu_maxim%type;
        p_salariu_minim tip_job.salariu_minim%type;
        p_job_id tip_job.job_id%type;
    
    begin
        if modificare_in_proces = false then
            modificare_in_proces := true;
            
            while t_angajati.count > 0 loop
                id := t_angajati.first;
                
                p_job_id := t_angajati(id).r_job_id;
                
                select tj.salariu_maxim 
                into p_salariu_maxim 
                from tip_job tj
                where tj.job_id = p_job_id;
                
                select tj.salariu_minim 
                into p_salariu_minim 
                from tip_job tj
                where tj.job_id = p_job_id;
                
                if p_salariu_maxim is null then 
                    update tip_job 
                    set 
                    salariu_minim = get_salariu_minim(p_job_id),
                    salariu_maxim = get_salariu_maxim(p_job_id)
                    where job_id = p_job_id;
                end if;
                    
                if p_salariu_minim > t_angajati(id).r_salariu then
                    update tip_job
                    set salariu_minim = get_salariu_minim(p_job_id)
                    where job_id = p_job_id;
                    
                elsif p_salariu_maxim < t_angajati(id).r_salariu then
                    update tip_job 
                    set salariu_maxim = get_salariu_maxim(p_job_id)
                    where job_id = p_job_id;
                        
                end if;
                
                update tip_job
                set numar_angajati = get_numar_angajati(p_job_id)
                where job_id = p_job_id;
                
                t_angajati.delete(t_angajati.first);
            end loop;
            
            modificare_in_proces := false;       
        end if;
    end;
    
    
    procedure valideaza_stergere is
        id pls_integer;
        p_salariu_maxim tip_job.salariu_maxim%type;
        p_salariu_minim tip_job.salariu_minim%type;
        p_job_id tip_job.job_id%type;
            
    begin  
    
        if modificare_in_proces = false then
            modificare_in_proces := true;
            
            while t_stersi.count > 0 loop
            
                id := t_stersi.first;
            
                p_job_id := t_stersi(id).r_job_id;

                update tip_job
                set 
                salariu_minim = get_salariu_minim(p_job_id),
                salariu_maxim = get_salariu_maxim(p_job_id),
                numar_angajati = get_numar_angajati(p_job_id)
                where job_id = p_job_id;
                
                t_stersi.delete(t_stersi.first);
            end loop;
            
            modificare_in_proces := false;
        end if;
    end;     
end;
/


create or replace trigger problema14_inainte_modificare
    before insert or update or delete on angajat
    
begin
    lock table angajat in exclusive mode;
    problema14.initializeaza;
end;
/


create or replace trigger problema14_dupa_modificare
    after insert or update or delete on angajat
    for each row
    
begin
    if inserting or updating then
        problema14.adauga_angajat(:new.angajat_id, :new.salariu, :new.job_id);
    else
        problema14.sterge_angajat(:old.angajat_id, :old.salariu, :old.job_id);
    end if;
end;
/


create or replace trigger problema14_executa_modificare
    after insert or update or delete on angajat
    
begin
    if inserting or updating then
        problema14.valideaza_modificare;
    else
        problema14.valideaza_stergere;
    end if;
end;
/




--compound trigger
create or replace trigger trigger_salariu_maxim_angajat    
for update or insert on angajat    
compound trigger    

    type id_salariu is record 
        (id angajat.angajat_id%type, 
        salariu angajat.salariu%type);    
    type informatii_linie is table of id_salariu index by pls_integer;    
    angajati informatii_linie;    
    
    after each row is    
    begin  
        angajati(angajati.count + 1).id := :new.angajat_id;    
        angajati(angajati.count).salariu := :new.salariu;
    end after each row;    
    
    after statement is    
        salariu_maxim angajat.salariu%type;  
        
    begin      
        select min (salariu) * 10    
        into salariu_maxim    
        from angajat;     
       
        for i in 1 .. angajati.count loop                                      
            if salariu_maxim < angajati(i).salariu then    
                update angajat    
                    set salariu = salariu_maxim    
                    where angajat_id = angajati(i).id;    
            end if;    
        end loop; 
   end after statement;    
end trigger_salariu_maxim_angajat;




--verificare triggere


--trigger problema 10
update angajat
set salariu = 10001
where nume = 'Lene';


--trigger problema 11
insert into rezervare values(13, 6, 4, 8, 
to_date('18-9-2023', 'DD-MM-YYYY'), to_date('10-10-2023', 'DD-MM-YYYY'), 9000);


--trigger problema 12
create table test 
(
test_id number(4)
);

alter table test
add nume varchar2(30);

alter table test
drop column nume;

drop table test;

select * 
from comenzi_log;

drop trigger trigger_problema12;


--trigger problema 14
insert into angajat values(31, 6, 8, 'Nume', 'Prenume', 500);
insert into angajat values(32, 6, 8, 'Nume', 'Prenume', 600);

delete from angajat
where angajat_id = 32;

rollback;


--compound trigger
update angajat
set salariu = 10001
where nume = 'Lene';

