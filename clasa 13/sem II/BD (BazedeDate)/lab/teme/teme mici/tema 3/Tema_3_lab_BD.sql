--lab5 19
drop table angajati_dac;
commit;

create table 
angajati_dac(cod_ang number(4), 
nume varchar2(20) not null, 
prenume varchar2(20), 
email char(15), 
data_ang date default sysdate, 
job varchar2(15), 
cod_sef number(4), 
salariu number(8, 2) not null,
cod_dep number(2),
comision number(2,2),
constraint fk_cod_ang primary key(cod_ang), 
constraint u_email unique(email),
constraint ck_dept_prof check(cod_dep > 0),
constraint fk_cod_sef_prof foreign key(cod_sef) 
references angajati_prof(cod_ang),
constraint un_cod_prenume unique(nume,prenume),
constraint ck_salariu_comision_prof check(salariu > comision * 100),
constraint fk_cod_dept_prof foreign key(cod_dep)
references departamente_prof(cod_dep));

commit;

select * from angajati_dac;
describe angajati_dac;


--lab5 24
alter table angajati_prof
modify email not null;


-- lab6 9
select e.last_name, d.department_id, j.job_id
from employees e, jobs j, departments d, locations l
where e.job_id = j.job_id
and e.department_id = d.department_id
and d.location_id = l.location_id
and lower(l.city) = 'toronto';


--lab6 16
select distinct d.department_name,
(select city from locations where location_id = d.location_id) as "Locatie",
nvl((select count(department_id) 
    from employees 
    group by department_id 
    having department_id = d.department_id),0) as "Numar angajati",
nvl((select avg(salary) 
    from employees 
    group by department_id 
    having department_id = d.department_id),0) as "Salariu mediu"
from departments d;
