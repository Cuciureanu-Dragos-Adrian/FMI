set serveroutput on;

--6
variable departament varchar2(35)
variable angajati number

begin
    select department_name, count(*) 
    into :departament, :angajati
    from employees e, departments d
    where e.department_id = d.department_id
    group by department_name
    having count(*) = (select max(count(*))
                        from employees
                        group by department_id);
    dbms_output.put_line('Departamentul '|| :departament || ' cu ' || :angajati || ' angajati' );
end;
/
print departament
print angajati


--2.b am folosit denumirea la tabel tot octombrie chiar daca suntem in noiembrie acum si datele sunt din noiembrie
drop table octombrie_dac;
create table octombrie_dac(id number, data date);

declare
    d date := trunc(sysdate, 'mm');
    n number := extract(day from last_day(sysdate));
begin
    for i in 1..n loop
          insert into octombrie_dac values (i, d);
          d := d+1;
    end loop;
end;

commit;
select * from octombrie_dac;


select t.data, count(*) as "numar Imprumuturi"
from octombrie_dac t
group by t.data
order by 1;


--3
declare
    nr number(10);
    nr_persoane number(10);
    name VARCHAR(101) := '&name';
    
begin
    select count(*) into nr_persoane
    from member
    where lower(name) = lower(last_name);

    if nr_persoane = 0 then
        dbms_output.put_line('Nu exista niciun membru cu numele dat');
    elsif nr_persoane > 1 then
        dbms_output.put_line('Exista mai multi membrii cu acelasi nume');
    else
        select count(distinct r.title_id) into nr
        from rental r, member m
        where r.member_id = m.member_id
        and lower(name) = lower(m.last_name);
        dbms_output.put_line(upper(name) || ': '|| nr || ' titluri imprumutate');
    end if;
end;


--4
declare
    nr number(10);
    nr_titluri number(10);
    procent number(10);
    name VARCHAR(101) := '&name';
    
begin
    select count(distinct t.title) into nr_titluri
    from title t;

    select count(distinct r.title_id) into nr
    from rental r, member m
    where r.member_id = m.member_id
    and lower(name) = lower(m.last_name);
    
    procent := (nr/nr_titluri) * 100;
    
    if (procent > 75) then
        dbms_output.put_line('Categoria 1: ' || upper(name) || ': '|| nr || ' din '|| nr_titluri || ' titluri imprumutate');
    elsif (procent > 50) then
        dbms_output.put_line('Categoria 2: ' || upper(name) || ': '|| nr || ' din '|| nr_titluri || ' titluri imprumutate');
    elsif (procent > 25) then
        dbms_output.put_line('Categoria 3: ' || upper(name) || ': '|| nr || ' din '|| nr_titluri || ' titluri imprumutate');
    else
        dbms_output.put_line('Categoria 4: ' || upper(name) || ': '|| nr || ' din '|| nr_titluri || ' titluri imprumutate');
    end if;
end;


--5
drop table mmember_dac;
create table member_dac as select * from member;

commit;
select * from member_dac;

alter table member_dac
add discount number(10);

declare
    nr number(10);
    nr_titluri number(10);
    procent number(10);
    cod number(10) := '&cod';
    
begin
    select count(distinct t.title) into nr_titluri
    from title t;

    select count(distinct r.title_id) into nr
    from rental r, member m
    where r.member_id = m.member_id
    and cod = m.member_id;
    
    procent := (nr/nr_titluri) * 100;
    
    if (procent > 75) then
        update member_dac
        set discount = 10
        where member_id = cod;
        commit;
        dbms_output.put_line('coloana discount a fost modificata cu succes');
    elsif (procent > 50) then
        update member_dac
        set discount = 5
        where member_id = cod;
        commit;
        dbms_output.put_line('coloana discount a fost modificata cu succes');
    elsif (procent > 25) then
        update member_dac
        set discount = 3
        where member_id = cod;
        commit;
        dbms_output.put_line('coloana discount a fost modificata cu succes');
    else
        update member_dac
        set discount = 0
        where member_id = cod;
        commit;
        dbms_output.put_line('coloana discount a fost modificata cu succes');
    end if;
end;





