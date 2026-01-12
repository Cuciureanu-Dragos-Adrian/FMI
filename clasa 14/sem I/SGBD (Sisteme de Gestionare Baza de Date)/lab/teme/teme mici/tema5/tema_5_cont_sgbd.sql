set serveroutput on;


--10.1 cursor clasic
declare
    depno number := 0;
    cod number;
    departament varchar2(20);
    nume varchar2(20);
    
    cursor c is
        select d.department_id cod, d.department_name departament, e.last_name nume
        from departments d
        left outer join employees e on d.department_id = e.department_id
        where d.department_id in (10, 20, 30, 40)
        group by d.department_id, d.department_name, e.last_name
        order by d.department_id;
    
begin
    open c;

    loop
        fetch c into cod, departament, nume;
        exit when c%NOTFOUND;

        if depno = cod then
            dbms_output.put_line(nume);
        else
            depno := cod;
            dbms_output.new_line;
            dbms_output.put_line('Departamentul ' || departament || ', id ' || cod || ':');
            dbms_output.put_line(nume);
        end if;
    end loop;

    close c;
end;


--10.2 ciclu cursor
declare
    depno number := 0;

    cursor c is
        select d.department_id cod, d.department_name departament, e.last_name nume
        from departments d
        left outer join employees e on d.department_id = e.department_id
        where d.department_id in (10, 20, 30, 40)
        group by d.department_id, d.department_name, e.last_name
        order by d.department_id;

begin
    for dep in c loop
        if depno = dep.cod then
            
            dbms_output.put_line(dep.nume);
        else
            depno := dep.cod;
            dbms_output.new_line;
            dbms_output.put_line('Departamentul ' || dep.departament || ', id ' || dep.cod || ':');
            dbms_output.put_line(dep.nume);
        end if;
    end loop;
end;




--1
--a cursor clasic
declare 
    numar_joburi number;
    counter number(5);
    titlu_job jobs.job_title%type;
    nume_angajat employees.first_name%type;
    salariu_angajat employees.salary%type;
    
    type tip_joburi is table of jobs.job_id%type;
    joburi tip_joburi := tip_joburi();
    
    cursor c (job_curent jobs.job_id%type) is 
        select e.last_name, e.salary
        from employees e, jobs j
        where j.job_id = e.job_id 
        and j.job_id = job_curent;
        
begin
    select count(*) into numar_joburi 
    from jobs;
    
    joburi.extend(numar_joburi);
    
    select j.job_id bulk collect into joburi 
    from jobs j;
    
    for i in joburi.first..joburi.last loop   
        select job_title
        into titlu_job
        from jobs j
        where j.job_id = joburi(i);
        
        dbms_output.put_line(titlu_job || ':');
        counter := 0;
        
        open c(joburi(i));
        loop
            fetch c into nume_angajat, salariu_angajat;
            exit when c%notfound;
            dbms_output.put_line(nume_angajat || ' ' || salariu_angajat);
            counter := counter + 1;
        end loop;
        close c;
        
        if counter = 0 then 
            dbms_output.put_line('Nu exista niciun angajat.');
        end if;
        
        dbms_output.new_line();
    end loop;
end;
/
    
--b ciclu cursoare
declare 
    numar_joburi number;
    counter number(5);
    titlu_job jobs.job_title%type;
    
    type tip_joburi is table of jobs.job_id%type;
    joburi tip_joburi := tip_joburi();
    
    cursor c (job_curent jobs.job_id%type)is 
        select e.last_name last_name, e.salary salary
        from employees e, jobs j
        where j.job_id = e.job_id 
        and j.job_id = job_curent;
        
begin
    select count(*) into numar_joburi 
    from jobs;
    
    joburi.extend(numar_joburi);
    
    select j.job_id bulk collect into joburi 
    from jobs j;
    
    for i in joburi.first..joburi.last loop 
        select job_title
        into titlu_job
        from jobs j
        where j.job_id = joburi(i);
        
        dbms_output.put_line(titlu_job || ':');
        counter := 0;
        
        for j in c(joburi(i)) loop
            exit when c%notfound;
            dbms_output.put_line(j.last_name || ' ' || j.salary);
            counter := counter + 1;
        end loop;
        
        if counter = 0 then 
            dbms_output.put_line('Nu exista niciun angajat.');
        end if;
        
        dbms_output.new_line();
    end loop;
end;
/
    
--c ciclu cursor
declare 
    numar_joburi number;
    counter number(5);
    titlu_job jobs.job_title%type;
    
    type tip_joburi is table of jobs.job_id%type;
    joburi tip_joburi := tip_joburi();
    
begin
    select count(*) into numar_joburi 
    from jobs;
    
    joburi.extend(numar_joburi);
    
    select j.job_id bulk collect into joburi 
    from jobs j;
    
    for i in joburi.first..joburi.last loop  
        select job_title
        into titlu_job
        from jobs j
        where j.job_id = joburi(i);
        
        dbms_output.put_line(titlu_job);
        counter := 0;
        
        for j in (select e.last_name last_name, e.salary salary
                    from employees e, jobs j
                    where j.job_id = e.job_id and
                    j.job_id = joburi(i)) 
                    
        loop
            dbms_output.put_line(j.last_name || ' ' || j.salary);
            counter := counter + 1;
        end loop;
        
        if counter = 0 then 
            dbms_output.put_line('Nu exista niciun angajat.');
        end if;
        
        dbms_output.new_line();
    end loop;
end;
/


--d expresii cursor
declare 
    counter number;
    titlu_job jobs.job_title%type;
    nume_angajat employees.first_name%type;
    salariu_angajat employees.salary%type;
    
    type refcursor is ref cursor;
    referinta_cursor refcursor;
    
    
    cursor c is 
        select j2.job_title, cursor
            (select e.last_name, e.salary
            from employees e, jobs j
            where j.job_id = e.job_id 
            and j.job_id = j2.job_id)
        from jobs j2;
        
begin
    open c;
    loop
        fetch c into titlu_job, referinta_cursor;
        exit when c%notfound;
        
        dbms_output.put_line(titlu_job || ':');
        counter := 0;
        
        loop 
            fetch referinta_cursor into nume_angajat, salariu_angajat;
            exit when referinta_cursor%notfound;
            
            dbms_output.put_line(nume_angajat || ' ' || salariu_angajat);
            counter := counter + 1;
        end loop;
        
        if counter = 0 then 
            dbms_output.put_line('Nu exista niciun angajat.');
        end if;
        
        dbms_output.new_line();
        
    end loop;
    close c;
end;
/




--2
declare 
    numar_salariati number;
    counter number;
    numar_joburi number;
    titlu_job jobs.job_title%type;
    nume_angajat employees.first_name%type;
    salariu_angajat employees.salary%type;
    salariu_total_job number(10, 2);
    salariu_mediu_job number(10, 2);
    salariu_total number(10, 2) := 0;
    salariu_mediu number(10, 2) := 0;
    counter_total number := 0;
    
    type tip_joburi is table of jobs.job_id%type;
    joburi tip_joburi := tip_joburi();
    
    cursor c (job_curent jobs.job_id%type)is 
        select e.last_name, e.salary
        from employees e, jobs j
        where j.job_id = e.job_id 
        and j.job_id = job_curent;
        
begin
    select count(*) into numar_joburi 
    from jobs;
    
    joburi.extend(numar_joburi);
    
    select j.job_id bulk collect into joburi 
    from jobs j;
    
    for i in joburi.first..joburi.last loop   
        select job_title
        into titlu_job
        from jobs j
        where j.job_id = joburi(i); 
        
        counter := 0;
        salariu_total_job := 0;
        
        select count(*)
        into numar_salariati
        from employees e, jobs j
        where e.job_id = j.job_id 
        and j.job_id = joburi(i);
        
        if numar_salariati = 0 then
            dbms_output.put_line('Nu lucreaza niciun angajat pe postul de ' || titlu_job);
        elsif numar_salariati = 1 then
            dbms_output.put_line(titlu_job || ' are un angajat:');
        else
            dbms_output.put_line(titlu_job || ' are ' || numar_salariati || ' angajati:');
        end if;
        
        open c(joburi(i));
        loop
            fetch c into nume_angajat, salariu_angajat;
            exit when c%notfound;
            
            dbms_output.put_line(counter + 1 || ' ' || nume_angajat || ' ' || salariu_angajat);
            counter := counter + 1;
            
            salariu_total_job := salariu_total_job + salariu_angajat;
        end loop;
        close c;
        
        counter_total := counter_total + numar_salariati;
        salariu_total := salariu_total + salariu_total_job;
        
        if counter = 0 then 
            dbms_output.put_line('Nu exista niciun angajat.');
        else
            salariu_mediu_job := salariu_total_job / counter;
            dbms_output.put_line('Salariul total ' || salariu_total_job);
            dbms_output.put_line('Salariul mediu ' || salariu_mediu_job);
        end if;
        
        dbms_output.new_line();
        
    end loop;
    
    salariu_mediu := salariu_total / counter_total;
    
    dbms_output.new_line();
    dbms_output.put_line('Numarul total de angajati ' || counter_total);
    dbms_output.put_line('Salariul total ' || salariu_total);
    dbms_output.put_line('Salariul mediu ' || salariu_mediu);
end;
/
    
    
    
    
--3
declare 
    numar_salariati number;
    counter number;
    numar_joburi number;
    titlu_job jobs.job_title%type;
    nume_angajat employees.first_name%type;
    salariu_angajat employees.salary%type;
    comision_angajat employees.commission_pct%type;
    procent_salariu number(10, 2);
    salariu_total_job number(10, 2);
    salariu_mediu_job number(10, 2);
    salariu_total number(10, 2) := 0;
    salariu_mediu number(10, 2) := 0;
    counter_total number := 0;
    
    type tip_joburi is table of jobs.job_id%type;
    joburi tip_joburi := tip_joburi();
    
    cursor c (job_curent jobs.job_id%type)is 
        select e.last_name, e.salary, e.commission_pct
        from employees e, jobs j
        where j.job_id = e.job_id 
        and j.job_id = job_curent;
        
begin
    select count(*) into numar_joburi 
    from jobs;
    
    joburi.extend(numar_joburi);
    
    select j.job_id bulk collect into joburi 
    from jobs j;
    
    for i in joburi.first..joburi.last loop   
        select job_title
        into titlu_job
        from jobs j
        where j.job_id = joburi(i); 
        
        counter := 0;
        salariu_total_job := 0;
        
        select count(*)
        into numar_salariati
        from employees e, jobs j
        where e.job_id = j.job_id 
        and j.job_id = joburi(i);
        
        select sum(salary) + sum(salary * nvl(commission_pct, 0))
        into salariu_total_job
        from employees
        group by job_id
        having job_id = joburi(i);
        
        select sum(salary) + sum(salary * nvl(commission_pct, 0))
        into salariu_total
        from employees;
        
        if numar_salariati = 0 then
            dbms_output.put_line('Nu lucreaza niciun angajat pe postul de ' || titlu_job);
        elsif numar_salariati = 1 then
            dbms_output.put_line(titlu_job || ' are un angajat:');
        else
            dbms_output.put_line(titlu_job || ' are ' || numar_salariati || ' angajati:');
        end if;
        
        open c(joburi(i));
        loop
            fetch c into nume_angajat, salariu_angajat, comision_angajat;
            exit when c%notfound;
            
            salariu_angajat := salariu_angajat + salariu_angajat * nvl(comision_angajat, 0);
            procent_salariu := salariu_angajat / salariu_total * 100;
            
            dbms_output.put_line(counter + 1 || ' ' || nume_angajat || ' ' || salariu_angajat || ', ' || to_char(procent_salariu, '0.00') || '% din total');
            counter := counter + 1;
        end loop;
        close c;
        
        counter_total := counter_total + numar_salariati;
        
        if counter = 0 then 
            dbms_output.put_line('Nu exista niciun angajat.');
        else
            salariu_mediu_job := salariu_total_job / counter;
            dbms_output.put_line('Salariul total cu comision ' || salariu_total_job);
            dbms_output.put_line('Salariul mediu cu comision ' || salariu_mediu_job);
        end if;
        
        dbms_output.new_line();
        
    end loop;
    
    salariu_mediu := salariu_total / counter_total;
    
    dbms_output.new_line();
    dbms_output.put_line('Numarul total de angajati ' || counter_total);
    dbms_output.put_line('Salariul total cu comision al tuturor angajatilor ' || salariu_total);
    dbms_output.put_line('Salariul mediu cu comision al tuturor angajatilor ' || salariu_mediu);
end;
/




--4
declare 
    numar_salariati number;
    counter number;
    numar_joburi number;
    titlu_job jobs.job_title%type;
    nume_angajat employees.first_name%type;
    salariu_angajat employees.salary%type;
    comision_angajat employees.commission_pct%type;
    procent_salariu number(10, 2);
    salariu_total_job number(10, 2);
    salariu_mediu_job number(10, 2);
    salariu_total number(10, 2) := 0;
    salariu_mediu number(10, 2) := 0;
    counter_total number := 0;
    
    type tip_joburi is table of jobs.job_id%type;
    joburi tip_joburi := tip_joburi();
    
    cursor c (job_curent jobs.job_id%type)is 
        select e.last_name, e.salary, e.commission_pct
        from employees e, jobs j
        where j.job_id = e.job_id 
        and j.job_id = job_curent
        order by (e.salary + e.salary * nvl(e.commission_pct, 0)) desc;
        
begin
    select count(*) into numar_joburi 
    from jobs;
    
    joburi.extend(numar_joburi);
    
    select j.job_id bulk collect into joburi 
    from jobs j;
    
    for i in joburi.first..joburi.last loop   
        select job_title
        into titlu_job
        from jobs j
        where j.job_id = joburi(i); 
        
        counter := 0;
        salariu_total_job := 0;
        
        select count(*)
        into numar_salariati
        from employees e, jobs j
        where e.job_id = j.job_id 
        and j.job_id = joburi(i);
        
        select sum(salary) + sum(salary * nvl(commission_pct, 0))
        into salariu_total_job
        from employees
        group by job_id
        having job_id = joburi(i);
        
        select sum(salary) + sum(salary * nvl(commission_pct, 0))
        into salariu_total
        from employees;
        
        if numar_salariati < 5 then
            dbms_output.put_line(titlu_job || ' are mai putin de 5 angajati:');
        else
            dbms_output.put_line(titlu_job || ' are ' || numar_salariati || ' angajati:');
        end if;
        
        open c(joburi(i));
        loop
            fetch c into nume_angajat, salariu_angajat, comision_angajat;
            exit when c%notfound or c%rowcount > 5;
            
            salariu_angajat := salariu_angajat + salariu_angajat * nvl(comision_angajat, 0);
            procent_salariu := salariu_angajat / salariu_total * 100;
            
            dbms_output.put_line(counter + 1 || ' ' || nume_angajat || ' ' || salariu_angajat || ', ' || to_char(procent_salariu, '0.00') || '% din total');
            counter := counter + 1;
        end loop;
        close c;
        
        counter_total := counter_total + numar_salariati;
        
        if counter = 0 then 
            dbms_output.put_line('Nu exista niciun angajat.');
        else
            salariu_mediu_job := salariu_total_job / counter;
            dbms_output.put_line('Salariul total cu comision ' || salariu_total_job);
            dbms_output.put_line('Salariul mediu cu comision ' || salariu_mediu_job);
        end if;
        
        dbms_output.new_line();
        
    end loop;
    
    salariu_mediu := salariu_total / counter_total;
    
    dbms_output.new_line();
    dbms_output.put_line('Numarul total de angajati ' || counter_total);
    dbms_output.put_line('Salariul total cu comision al tuturor angajatilor ' || salariu_total);
    dbms_output.put_line('Salariul mediu cu comision al tuturor angajatilor ' || salariu_mediu);
end;
/




--5
declare 
    numar_salariati number;
    counter number;
    numar_joburi number;
    titlu_job jobs.job_title%type;
    nume_angajat employees.first_name%type;
    salariu_angajat employees.salary%type;
    salariu_precedent employees.salary%type;
    comision_angajat employees.commission_pct%type;
    procent_salariu number(10, 2);
    salariu_total_job number(10, 2);
    salariu_mediu_job number(10, 2);
    salariu_total number(10, 2) := 0;
    salariu_mediu number(10, 2) := 0;
    counter_total number := 0;
    
    type tip_joburi is table of jobs.job_id%type;
    joburi tip_joburi := tip_joburi();
    
    cursor c (job_curent jobs.job_id%type)is 
        select e.last_name, e.salary, e.commission_pct
        from employees e, jobs j
        where j.job_id = e.job_id 
        and j.job_id = job_curent
        order by (e.salary + e.salary * nvl(e.commission_pct, 0)) desc;
        
begin
    select count(*) into numar_joburi 
    from jobs;
    
    joburi.extend(numar_joburi);
    
    select j.job_id bulk collect into joburi 
    from jobs j;
    
    for i in joburi.first..joburi.last loop   
        select job_title
        into titlu_job
        from jobs j
        where j.job_id = joburi(i); 
        
        counter := 0;
        salariu_total_job := 0;
        
        select count(*)
        into numar_salariati
        from employees e, jobs j
        where e.job_id = j.job_id 
        and j.job_id = joburi(i);
        
        select sum(salary) + sum(salary * nvl(commission_pct, 0))
        into salariu_total_job
        from employees
        group by job_id
        having job_id = joburi(i);
        
        select sum(salary) + sum(salary * nvl(commission_pct, 0))
        into salariu_total
        from employees;
        
        if numar_salariati < 5 then
            dbms_output.put_line(titlu_job || ' are mai putin de 5 angajati:');
        else
            dbms_output.put_line(titlu_job || ' are ' || numar_salariati || ' angajati:');
        end if;
        
        open c(joburi(i));
        loop
            fetch c into nume_angajat, salariu_angajat, comision_angajat;
            exit when c%notfound or counter > 4;
            
            if counter = 0 then 
                counter := counter + 1;
                salariu_precedent := salariu_angajat;
            elsif salariu_precedent != salariu_angajat then
                counter := counter + 1;
                salariu_precedent := salariu_angajat;
            end if;
            
            salariu_angajat := salariu_angajat + salariu_angajat * nvl(comision_angajat, 0);
            procent_salariu := salariu_angajat / salariu_total * 100;
            
            dbms_output.put_line(counter || ' ' || nume_angajat || ' ' || salariu_angajat || ', ' || to_char(procent_salariu, '0.00') || '% din total');
            
        end loop;
        close c;
        
        counter_total := counter_total + numar_salariati;
        
        if counter = 0 then 
            dbms_output.put_line('Nu exista niciun angajat.');
        else
            salariu_mediu_job := salariu_total_job / counter;
            dbms_output.put_line('Salariul total cu comision ' || salariu_total_job);
            dbms_output.put_line('Salariul mediu cu comision ' || salariu_mediu_job);
        end if;
        
        dbms_output.new_line();
        
    end loop;
    
    salariu_mediu := salariu_total / counter_total;
    
    dbms_output.new_line();
    dbms_output.put_line('Numarul total de angajati ' || counter_total);
    dbms_output.put_line('Salariul total cu comision al tuturor angajatilor ' || salariu_total);
    dbms_output.put_line('Salariul mediu cu comision al tuturor angajatilor ' || salariu_mediu);
end;
/